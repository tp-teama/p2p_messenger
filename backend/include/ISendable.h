#pragma once
#include "Message.h"
#include "Chat.h"

class ISendable {
public:
    ISendable() {}
    virtual bool SendToPort(const std::string&, int) = 0;
    virtual ~ISendable() {}
};