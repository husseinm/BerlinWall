#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Message.h"

class Button : Entity {
  public:
    Button(std::string title, int fontSize, sf::Vector2f size, sf::Vector2f position, Message::MessageId emitter);
    ~Button();
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
  private:
    sf::RectangleShape background;
    sf::Text title;
    sf::Font kbPlanetEarth;
    Message messageToEmit;
};

#endif
