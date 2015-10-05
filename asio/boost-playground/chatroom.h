#ifndef CHATROOM_H
#define CHATROOM_H

#include <set>
#include <chatparticipant.h>

class ChatRoom
{
public:
    void join(ChatParticipantPtr participant);
    void leave(ChatParticipantPtr participant);
    void deliver(const ChatMessage& msg);

private:
    std::set<ChatParticipantPtr> participants_;
    enum {max_recent_msgs = 100};
    ChatMessageQueue recent_msgs_;
};

#endif // CHATROOM_H
