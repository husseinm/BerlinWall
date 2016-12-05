#ifndef BERLIN_WALL_TITLE_STATE_H
#define BERLIN_WALL_TITLE_STATE_H

#include "Button.h"
#include "State.h"

class TitleState : State {
  public:
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
  private:
    friend class StateManager;

    sf::Font kbPlanetEarth;
    sf::Text mainHeader;
    sf::RectangleShape background;
    sf::Texture backgroundImage;
    Button quitButton;
    Button playGameButton;

    TitleState();
    ~TitleState();
};

#endif
