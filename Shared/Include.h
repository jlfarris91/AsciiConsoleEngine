#pragma once
#include <exception>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef uchar byte;

#include "Time.h"
#include "Args.h"
#include "Property.h"
#include "SmartPtr.h"
#include "Bool.h"
#include "LazyString.h"

typedef String string;
typedef const string &StringParam;

#define SafeDelete(a) {if (a!=NULL) delete a; a = NULL;}
#define SafeArrayDelete(a) {if (a!=NULL) delete [] a; a = NULL;}

#define ToCoord(vec) (COORD{(SHORT)vec.x, (SHORT)vec.y})
#define Split2(vec) vec.x, vec.y
#define Split3(vec) vec.x, vec.y, vec.z
#define Split4(vec) vec.x, vec.y, vec.z, vec.w
#define SPLIT2(vec) vec.X, vec.Y
#define SPLIT3(vec) vec.X, vec.Y, vec.Z

#define SetBit(flag, bit) (uint)flag |= bit
#define ClearBit(flag, bit) (uint)flag &= ~bit
#define IsSet(flag, bit) (((uint)flag & (uint)bit) != 0)

#define IfContainerContainsKey(iter, container, key) \
    auto &&iter = container.find(key); \
    if (iter != container.end()) \

template <typename T, int N>
size_t LengthOf(const T(&)[N])
{
    return N;
}

void HandleLastError();

template <typename T>
void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}