#ifndef SOLDIER_H_INCLUDED
#define SOLDIER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Soldier : Entity
{
  public:
    Soldier();
    ~Soldier();
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
  private:
    friend class LevelState;

    void regenerate();

    sf::Sprite soldierSprite;
    sf::Texture soldierTexture;
};

#endif
