#pragma once

template <typename T>
class List
{
public:
    virtual T *cloneArray() = 0;

    virtual int getSize() = 0;

    virtual void clear() = 0;
};