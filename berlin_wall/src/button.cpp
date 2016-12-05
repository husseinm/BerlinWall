#include "Button.h"
#include "config.h"

#include <iostream>

Button::Button(std::string title, int fontSize, sf::Vector2f size, sf::Vector2f position, Message::MessageId emitter) : background(size), messageToEmit(emitter) {
  sf::FloatRect buttonRect = background.getLocalBounds();
  background.setOrigin(buttonRect.left + buttonRect.width / 2.0f,
      buttonRect.top + buttonRect.height / 2.0f);
  background.setPosition(position);
  background.setFillColor(sf::Color::Black);
  kbPlanetEarth.loadFromFile(baseDir + "KBPlanetEarth.ttf");
  this->title = sf::Text(title, kbPlanetEarth, fontSize);
  this->title.setFillColor(sf::Color::White);
  this->title.setPosition(position);
  sf::FloatRect titleRect = this->title.getLocalBounds();
  this->title.setOrigin(titleRect.left + titleRect.width / 2.0f,
      titleRect.top + titleRect.height / 2.0f);
}

Button::~Button() {
}

bool Button::handleEvent(const sf::Event& evt) {
    if (evt.type == sf::Event::MouseButtonPressed) {
        if (evt.mouseButton.button == sf::Mouse::Button::Left) {
            if (background.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y)) {
                messageStack.push(this->messageToEmit);
            }
        }
    }
}

void Button::handleMessage(const Message&) {
}

bool Button::update(float dt) {
}

void Button::draw(sf::RenderWindow* context) {
  context->draw(background);
  context->draw(title);
}
