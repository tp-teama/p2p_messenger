#pragma once

class IRecievable {
public:
    IRecievable() {}
    virtual void Recieve() = 0;
    virtual ~IRecievable();
};