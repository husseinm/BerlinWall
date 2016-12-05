#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Message.h"

class Entity {
public:
  virtual bool handleEvent(const sf::Event& evt) = 0;
  virtual void handleMessage(const Message&) = 0;
  virtual bool update(float dt) = 0;
  virtual void draw(sf::RenderWindow* context) = 0;
};

#endif
