#include "chatroom.h"


void ChatRoom::join(ChatParticipantPtr participant)
{
    participants_.insert(participant);
    for (auto msg: recent_msgs_) {
        participant->deliver(msg);
    }
}

void ChatRoom::leave(ChatParticipantPtr participant)
{
    participants_.erase(participant);
}

void ChatRoom::deliver(const ChatMessage &msg)
{
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs) {
        recent_msgs_.pop_front();
    }

    for (auto p: participants_) {
        p->deliver(msg);
    }
}
