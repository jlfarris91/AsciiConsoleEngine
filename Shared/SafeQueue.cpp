#include "SafeQueue.h"
#include <stdio.h>
#include <string>

SafeQueue::SafeQueue(unsigned int size, unsigned int count)
{
	if (size && count)
	{
		mpData = new unsigned char[size*count];
		mSize = size;
		mCount = count;
		mReadIndex = 0;
		mWriteIndex = 0;
	}
}

SafeQueue::~SafeQueue()
{
	delete mpData;
}

bool SafeQueue::Write(const void *pData)
{
	if (pData)
	{
		if (mReadIndex == mWriteIndex)
		{
			mWriteIndex = 0;
			_ReadWriteBarrier();
			mReadIndex = 0;
		}
		if (mWriteIndex < mCount)
		{
			memcpy(mpData + (mWriteIndex*mSize), pData, mSize);
			_ReadWriteBarrier();
			++mWriteIndex;
			return true;
		}
	}
	return false;
}

bool SafeQueue::Read(void *pData)
{
	if (pData)
	{
		if (mReadIndex < mWriteIndex)
		{
			memcpy(pData, mpData + (mReadIndex*mSize), mSize);
			_ReadWriteBarrier();
			++mReadIndex;
			return true;
		}
	}
	return false;
}