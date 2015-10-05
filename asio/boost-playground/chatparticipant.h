#ifndef CHATPARTICIPANT_H
#define CHATPARTICIPANT_H
#include "chatmessage.h"
#include <memory>
class ChatParticipant
{
public:
    virtual ~ChatParticipant();
    virtual void deliver(const ChatMessage& msg) = 0;
};

typedef std::shared_ptr<ChatParticipant> ChatParticipantPtr;
#endif // CHATPARTICIPANT_H
