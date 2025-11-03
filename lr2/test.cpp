#include "gtest/gtest.h"
#include "inc/DynamicArray.h"
#include "inc/Simple.h"


TEST(TestConstructors, Simple)
{
	Array<int> arr;
	EXPECT_EQ(arr.size(), 0);
}

TEST(TestConstructors, SimpleWithCapacity)
{
	Array<int> arr(1);
	EXPECT_EQ(arr.size(), 0);
}

TEST(TestConstructors, Move)
{
	Array<int> moved(3);
	for (int i = 0; i < 3; i++)
		moved.insert(i);
	
	Array<int> arr(std::move(moved));
	EXPECT_EQ(arr.size(), 3);
	EXPECT_EQ(moved.size(), 0);
	EXPECT_EQ(arr[0], 0);
	EXPECT_EQ(arr[1], 1);
	EXPECT_EQ(arr[2], 2);
}

TEST(TestConstructors, Copy)
{
	Array<int> copied(3);
	for (int i = 0; i < 3; i++)
		copied.insert(i);

	Array<int> arr(copied);
	EXPECT_EQ(arr.size(), 3);
	EXPECT_EQ(arr[0], 0);
	EXPECT_EQ(arr[1], 1);
	EXPECT_EQ(arr[2], 2);
	EXPECT_EQ(copied.size(), 3);
	EXPECT_EQ(copied[0], 0);
	EXPECT_EQ(copied[1], 1);
	EXPECT_EQ(copied[2], 2);
}




TEST(TestOperations, Assignment)
{
	Array<int> left(2);
	Array<int> right(2);
	left.insert(0);
	left.insert(1);
	right.insert(2);
	right.insert(3);
	left = right;
	right.insert(4);
	EXPECT_EQ(left[0], 2);
	EXPECT_EQ(left[1], 3);
	EXPECT_EQ(right[2], 4);
	EXPECT_EQ(left.size(), 2);
}

TEST(TestOperations, InsertToEndInEmpty)
{
	Array<int> arr;
	arr.insert(1);
	EXPECT_EQ(arr.size(), 1);
	EXPECT_EQ(arr[0], 1);
}

TEST(TestOperations, InsertToIndexInEmpty)
{
	Array<int> arr;
	arr.insert(0, 1);
	EXPECT_EQ(arr.size(), 1);
	EXPECT_EQ(arr[0], 1);
}

TEST(TestOperations, InsertToEndInFull)
{
	Array<int> arr(1);
	arr.insert(0);
	arr.insert(1);
	EXPECT_EQ(arr.size(), 2);
	EXPECT_EQ(arr[0], 0);
	EXPECT_EQ(arr[1], 1);
}

TEST(TestOperations, InsertToIndexInFull)
{
	Array<int> arr(1);
	arr.insert(0);
	arr.insert(0, 1);
	EXPECT_EQ(arr.size(), 2);
	EXPECT_EQ(arr[0], 1);
	EXPECT_EQ(arr[1], 0);
}

TEST(TestOperations, InsertToNegativeIndex)
{
	Array<int> arr(1);
	arr.insert(0);
	EXPECT_THROW(arr.insert(-1, 1), std::out_of_range);
}

TEST(TestOperations, InsertSimpleClass)
{
	Array<Simple> arr(1);
	Simple test;
	arr.insert(test);
	EXPECT_EQ(arr[0].intValue, 5);
}

TEST(TestOperations, RemoveOne)
{
	Array<int> arr(1);
	arr.insert(0);
	arr.remove(0);
	EXPECT_EQ(arr.size(), 0);
}

TEST(TestOperations, RemoveFirst)
{
	Array<int> arr(2);
	arr.insert(0);
	arr.insert(1);
	arr.remove(0);
	EXPECT_EQ(arr[0], 1);
	EXPECT_EQ(arr.size(), 1);
}

TEST(TestOperations, RemoveMiddle)
{
	Array<int> arr(3);
	arr.insert(0);
	arr.insert(1);
	arr.insert(2);
	arr.remove(1);
	EXPECT_EQ(arr[0], 0);
	EXPECT_EQ(arr[1], 2);
	EXPECT_EQ(arr.size(), 2);
}

TEST(TestOperations, RemoveLast)
{
	Array<int> arr(3);
	arr.insert(0);
	arr.insert(1);
	arr.insert(2);
	arr.remove(2);
	EXPECT_EQ(arr[0], 0);
	EXPECT_EQ(arr[1], 1);
	EXPECT_EQ(arr.size(), 2);
}

TEST(TestOperations, RemoveFromIncorrectIndex)
{
	Array<int> arr(1);
	arr.insert(0);
	EXPECT_THROW(arr.remove(-1), std::out_of_range);
	EXPECT_THROW(arr.remove(1), std::out_of_range);
}

TEST(TestOperations, RemoveFromEmpty)
{
	Array<int> arr;
	EXPECT_THROW(arr.remove(1), std::out_of_range);
}



TEST(TestIterators, ForwardPass)
{
	Array<int> arr(5);
	for (int i = 0; i < 5; i++)
		arr.insert(i);
	Array<int>::Iterator iter(arr, 0, false);
	int i = 0;
	while (iter.hasNext())
	{
		EXPECT_EQ(arr[i++], iter.get());
		iter.next();
	}
}

TEST(TestIterators, ReversePass)
{
	Array<int> arr(5);
	for (int i = 0; i < 5; i++)
		arr.insert(i);
	Array<int>::Iterator iter(arr, arr.size() - 1, true);
	int i = arr.size() - 1;
	while (iter.hasNext())
	{
		EXPECT_EQ(arr[i--], iter.get());
		iter.next();
	}
}

TEST(TestIterators, ChangeValue)
{
	Array<int> arr(1);
	arr.insert(0);
	EXPECT_EQ(arr[0], 0);
	Array<int>::Iterator iter(arr, 0, false);
	iter.set(1);
	EXPECT_EQ(arr[0], 1);
}

TEST(TestIterators, GetValue)
{
	Array<int> arr(1);
	arr.insert(0);
	EXPECT_EQ(arr[0], 0);
	Array<int>::Iterator iter(arr, 0, false);
	EXPECT_EQ(iter.get(), 0);
}