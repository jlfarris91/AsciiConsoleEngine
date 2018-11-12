#include "ObjectPoolTests.h"
#include "ObjectPool.h"

class PoolableInt : public PoolableObject<int>
{
public:
    PoolableInt(int i = 0)
        : integer(i)
    {
    }
    int integer;
};

DefineTest(ObjectPoolTests::New, ShouldReturnValidHandle)
{
    // Arrange
    ObjectPool<PoolableInt> pool;
    pool.Reserve(1);

    // Act
    auto &&intHandle = pool.New(123);

    // Assert
    Assert(pool.Count == 1);
    Assert(intHandle.IsAlive);
    Assert(intHandle->integer == 123);
}

DefineTest(ObjectPoolTests::New, ShouldReserveAdditionalObjectsWhenAtCapacity)
{
    // Arrange
    ObjectPool<PoolableInt> pool;

    // Act
    // use up all existing objects
    for (uint i = 0; i < 3; ++i)
    {
        (void)pool.New();
    }
    
    // then try to get one more
    auto &&intHandle = pool.New(456);

    // Assert
    Assert(pool.Count == 4);
    Assert(intHandle.IsAlive);
    Assert(intHandle->integer == 456);
}