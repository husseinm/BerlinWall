#ifndef BERLIN_WALL_STATE_H
#define BERLIN_WALL_STATE_H

#include <SFML/Graphics.hpp>
#include "berlin_wall/include/Message.h"

enum StateId {
  TitleState = 0,
  SettingsState,
  LevelState,
  PauseState,
  DifficultyState,
  ScoreState
};

class State {
  public:
    virtual ~State() = default;
    virtual bool handleEvent(const sf::Event& evt) = 0;
    virtual void handleMessage(const Message&) = 0;
    virtual bool update(float dt) = 0;
    virtual void draw(sf::RenderWindow* context) = 0;
  protected:
    friend class StateManager;

    State() = default;

    StateId stateId;
};

#endif
