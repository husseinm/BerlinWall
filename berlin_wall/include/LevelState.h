#ifndef BERLIN_WALL_LEVEL_STATE_H
#define BERLIN_WALL_LEVEL_STATE_H

#include "Soldier.h"
#include "Spy.h"
#include "State.h"
#include "Button.h"

class LevelState : State {
  public:
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
  private:
    friend class StateManager;

    Spy spy;
    Soldier soldier;

    bool gameNotPaused;
    int score;
    float remainingTime;
    sf::Clock gameTime;
    
    sf::Font kbPlanetEarth;
    sf::RectangleShape background;
    sf::Texture backgroundImage;
    
    LevelState();
    ~LevelState();
};

#endif
