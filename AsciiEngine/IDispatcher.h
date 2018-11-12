#pragma once

struct Message;

class IDispatcher
{
public:
    virtual ~IDispatcher() = default;
    virtual void Dispatch(Message *message) = 0;
};