#ifndef BERLIN_WALL_MESSAGE_H
#define BERLIN_WALL_MESSAGE_H

#include <stack>

class Message {
  public:
    enum MessageId {
      SpyMovedLeft = 0,
      SpyMovedRight,
      SpyMovedUp,
      SpyMovedDown,
      SpyCollided,
      SoldierKilled,
      CloseGame,
      ChooseDifficulty,
      EasyDifficulty,
      MediumDifficulty,
      HardDifficulty
    };

    Message(MessageId msgId) : msgId(msgId) {};
    ~Message() {};

    MessageId getId() const { return msgId; };
  private:
    MessageId msgId;
};

extern std::stack<Message> messageStack;

#endif
