#include "./stdafx.h"

#include <Windows.h>
#include <iostream>

void HandleLastError()
{
    auto errorCode = GetLastError();
    std::cout << "Error: " << errorCode;
}