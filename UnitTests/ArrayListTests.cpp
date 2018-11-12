#include "ArrayListTests.h"

struct Foo
{
    static bool calledCopyCtor;
    static bool calledDtor;

    int data = 0;

    Foo(int data = 0) : data(data) {}

    Foo(const Foo &other)
    {
        calledCopyCtor = true;
    }

    ~Foo()
    {
        calledDtor = true;
    }

    bool operator==(const Foo &rhs) const
    {
        return this->data == rhs.data;
    }
};

bool Foo::calledCopyCtor = false;
bool Foo::calledDtor = false;

DefineTest(ArrayListTests::Push_Back, ShouldAppendItem)
{
    // Arrange
    ArrayList<int> list;

    // Act
    list.push_back(10);

    // Assert
    Assert(list.count == 1);
    Assert(list[0] == 10);
}

DefineTest(ArrayListTests::Push_Back, ShouldCallCopyCtor)
{
    Foo::calledCopyCtor = false;
    Foo foo;

    // Arrange
    ArrayList<Foo> list;

    // Act
    list.push_back(foo);

    // Assert
    Assert(list.count == 1);
    Assert(Foo::calledCopyCtor);
}

DefineTest(ArrayListTests::Push_Range, ShouldAppendItems)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);

    // Act
    int asd[] { 3, 4, 5, 6, 7 };
    list.push_range(asd);

    // Assert
    Assert(list.count == 8);
    for (unsigned i = 0; i < list.count; ++i)
    {
        Assert(list[i] == i);
    }
}

DefineTest(ArrayListTests::Push_Range, ShouldAppendOtherListsItems)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);

    ArrayList<int> list2;
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);

    // Act
    list.push_range(list2);

    // Assert
    Assert(list.count == 6);
    for (unsigned i = 0; i < list.count; ++i)
    {
        Assert(list[i] == i);
    }
}

DefineTest(ArrayListTests::Insert, ShouldInsertItem)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(3);

    // Act
    list.insert(2);

    // Assert
    Assert(list.count == 4);
    for (int i = 0; i < 4; ++i)
    {
        Assert(list[i] == i);
    }
}

DefineTest(ArrayListTests::Insert, ShouldInsertToFront)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Act
    list.insert(0);

    // Assert
    Assert(list.count == 4);
    for (int i = 0; i < 4; ++i)
    {
        Assert(list[i] == i);
    }
}

DefineTest(ArrayListTests::Insert, ShouldInsertToBack)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);

    // Act
    list.insert(3);

    // Assert
    Assert(list.count == 4);
    for (int i = 0; i < 4; ++i)
    {
        Assert(list[i] == i);
    }
}

DefineTest(ArrayListTests::Insert, ShouldInsertIntoEmptyList)
{
    // Arrange
    ArrayList<int> list;

    // Act
    list.insert(123);

    // Assert
    Assert(list.count == 1);
    Assert(list[0] == 123);
}

DefineTest(ArrayListTests::Remove, ShouldRemoveItem)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);

    // Act
    list.remove(1);

    // Assert
    Assert(list.count == 2);
    Assert(list[0] == 0);
    Assert(list[1] == 2);
}

DefineTest(ArrayListTests::Remove, ShouldRemoveFirstItem)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);

    // Act
    list.remove(0);

    // Assert
    Assert(list.count == 2);
    Assert(list[0] == 1);
    Assert(list[1] == 2);
}

DefineTest(ArrayListTests::Remove, ShouldRemoveLastItem)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);

    // Act
    list.remove(2);

    // Assert
    Assert(list.count == 2);
    Assert(list[0] == 0);
    Assert(list[1] == 1);
}

DefineTest(ArrayListTests::Remove, ShouldCallItemsDestructor)
{
    Foo::calledDtor = false;
    Foo foo;

    // Arrange
    ArrayList<Foo> list;
    list.push_back(foo);

    // Act
    list.remove(foo);

    // Assert
    Assert(list.count == 0);
    Assert(Foo::calledDtor);
}

DefineTest(ArrayListTests::Reserve, ShouldIncreaseSizeIfArrayCapacityIsLess)
{
    // Arrange
    ArrayList<int> list;
    list.push_back(123);

    // Act
    list.reserve(10);

    // Assert
    Assert(list.capacity >= 10);
    Assert(list.count == 1);
}

DefineTest(ArrayListTests::Reserve, ShouldDoNothingIfArrayCapacityIsGreater)
{
    // Arrange
    ArrayList<int> list;
    for (int i = 0; i < 10; ++i)
    {
        list.push_back(i);
    }
    unsigned capacity = list.capacity;

    // Act
    list.reserve(5);

    // Assert
    Assert(list.capacity == capacity);
    Assert(list.count == 10);
}

DefineTest(ArrayListTests::Reserve, ShouldDoNothingIfArrayCapacityIsEqual)
{
    // Arrange
    ArrayList<int> list;
    for (int i = 0; i < 10; ++i)
    {
        list.push_back(i);
    }
    unsigned capacity = list.capacity;

    // Act
    list.reserve(capacity);

    // Assert
    Assert(list.capacity == capacity);
    Assert(list.count == 10);
}

DefineTest(ArrayListTests::Range, ShouldIterateThroughAllElements)
{
    // Arrange
    ArrayList<int> list;
    for (int i = 0; i < 10; ++i)
    {
        list.push_back(i);
    }

    // Act + Assert
    int count = 0;
    for (auto &&item : list)
    {
        Assert(item == count++);
    }
}