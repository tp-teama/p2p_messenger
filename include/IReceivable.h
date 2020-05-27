#pragma once

class IReceivable {
public:
    IReceivable() {}
    virtual void Receive() = 0;
    virtual ~IReceivable() {}
};