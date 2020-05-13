#pragma once

class ISendable {
public:
    ISendable() {}
    virtual void Send() = 0;
    virtual ~ISendable();
};