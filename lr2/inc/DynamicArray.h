#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#define DEFAULT_CAPACITY 8

#include <cstdlib>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <type_traits>

template <typename Type>
class Array
{
public:
	Array()
	{
		capacity = DEFAULT_CAPACITY;
		arr = static_cast<Type*>(malloc(sizeof(Type) * capacity));
	}

	Array(int capacity) : capacity{ capacity }
	{
		if (capacity < 0)
			capacity = DEFAULT_CAPACITY;
		arr = static_cast<Type*>(malloc(sizeof(Type) * capacity));
	}

	Array(Array&& moved) : capacity{ moved.capacity }, length{ moved.length }, arr{ moved.arr }
	{
		moved.arr = nullptr;
		moved.capacity = 0;
		moved.length = 0;
	}

	Array(const Array& copied) : capacity{ copied.capacity }, length{ copied.length }
	{
		arr = static_cast<Type*>(malloc(sizeof(Type) * capacity));
		for (int i = 0; i < copied.length; i++)
			new(&arr[i]) Type(copied.arr[i]);
	}

	~Array()
	{
		if (arr)
		{
			for (int i = 0; i < length; i++)
				arr[i].~Type();
			length = 0;
			free(arr);
			arr = nullptr;
		}
	}

	Array& operator=(const Array& obj)
	{
		if (this != &obj)
		{
			Array temp(obj);
			std::swap(capacity, temp.capacity);
			std::swap(length, temp.length);
			std::swap(arr, temp.arr);
		}
		return *this;
	}

	int insert(const Type& value)
	{
		if (length + 1 >= capacity)
			expand();
		new(&arr[length]) Type(value);
		length++;
		return length - 1;
	}

	int insert(int index, const Type& value)
	{
		if (index < 0)
			throw std::out_of_range("Index out of range");
		if (length + 1 >= capacity)
			expand();
		for (int i = length; i > index; i--)
			new(&arr[i]) Type(std::move(arr[i - 1]));
		new(&arr[index]) Type(value);
		length++;
		return index;
	}

	void remove(int index)
	{
		if (length == 0 || index < 0 || index > length - 1)
			throw std::out_of_range("Index out of range");
		for (int i = index; i < length - 1; i++)
			arr[i] = std::move(arr[i + 1]);
		length--;
	}

	const Type& operator[](int index) const
	{
		return arr[index];
	}

	Type& operator[](int index)
	{
		return arr[index];
	}

	int size() const
	{
		return length;
	}

	class Iterator
	{
	private:
		Array<Type>& container;
		int index;
		bool isReverse;

	public:
		Iterator(Array<Type>& container, int index, bool isReverse) : container{ container }, index{ index }, isReverse{ isReverse }
		{

		}

		const Type& get() const
		{
			return container.arr[index];
		}

		void set(const Type& value)
		{
			new(&container.arr[index]) Type(value);
		}

		void next()
		{
			if (isReverse)
				index--;
			else
				index++;
		}

		bool hasNext() const
		{
			if (isReverse)
				return index > 0;
			return index < container.size() - 1;
		}
	};

	class ConstIterator
	{
	private:
		const Array<Type>& container;
		int index;
		bool isReverse;

	public:
		ConstIterator(Array<Type>& container, int index, int isReverse) : container{ container }, index{ index }, isReverse{ isReverse }
		{

		}
		const Type& get() const
		{
			return container.arr[index];
		}

		void next()
		{
			if (isReverse)
				index--;
			else
				index++;
		}

		bool hasNext() const
		{
			if (isReverse)
				return index > 0;
			return index < container.size() - 1;
		}
	};

	Iterator iterator()
	{
		return Iterator(*this, 0, false);
	}

	ConstIterator iterator() const
	{
		return ConstIterator(*this, 0, false);
	}

	Iterator reverseIterator()
	{
		return Iterator(*this, length - 1, true);
	}

	ConstIterator reverseIterator() const
	{
		return ConstIterator(*this, length - 1, true);
	}

private:
	int length = 0;
	int capacity = 0;
	Type* arr;

	void expand()
	{
		capacity *= 2;
		Type* newArr = static_cast<Type*>(std::malloc(sizeof(Type) * capacity));
		for (int i = 0; i < length; i++)
			if constexpr (std::is_move_constructible_v<Type>)
				new(&newArr[i]) Type(std::move(arr[i]));
			else
			{
				new(&newArr[i]) Type(arr[i]);
				arr[i].~Type();
			}
		free(arr);
		arr = newArr;
	}
};

#endif
