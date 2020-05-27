#pragma once
#include "Message.h"
#include "Chat.h"

class ISendable {
public:
    ISendable() {}
    virtual void SendToPort(const std::string&, int) = 0;
    virtual ~ISendable() {}
};