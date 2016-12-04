#ifndef BERLIN_WALL_TITLE_STATE_H
#define BERLIN_WALL_TITLE_STATE_H

#include "State.h"

class TitleState : State {
  public:
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
  private:
    friend class StateManager;

    TitleState();
    ~TitleState();
};

#endif
