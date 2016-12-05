#ifndef SOLDIER_H_INCLUDED
#define SOLDIER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Soldier : Entity
{
  public:
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
};

#endif
