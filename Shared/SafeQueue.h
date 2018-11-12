#pragma once

class SafeQueue
{

public:

	SafeQueue(unsigned int size = 0, unsigned int count = 0);
	virtual ~SafeQueue();

	bool Write(const void *pData);
	bool Read(void *pData);
	bool Empty(void) const { return (mReadIndex == mWriteIndex); }

protected:

	unsigned char *mpData;
	size_t mSize;
	size_t mCount;
	unsigned int mWriteIndex;
	unsigned int mReadIndex;

};