#ifndef BERLIN_WALL_DIFFICULTY_STATE_H
#define BERLIN_WALL_DIFFICULTY_STATE_H

#include "State.h"
#include "Button.h"

class DifficultyState : State {
  public:
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
  private:
    friend class StateManager;

    sf::Font kbPlanetEarth;
    sf::RectangleShape background;
    sf::Texture backgroundImage;
    sf::Text mainHeader;

    Button easyButton;
    Button mediumButton;
    Button hardButton;

    DifficultyState();
    ~DifficultyState();
};

#endif
