#include "Button.h"
#include "config.h"

#include <iostream>

Button::Button(std::string title, int fontSize, sf::Vector2f size, sf::Vector2f position, Message::MessageId emitter) : background(size), messageToEmit(emitter) {

  // Make rectangle
  sf::FloatRect buttonRect = background.getLocalBounds();

  // Move origin to center of rectangle
  background.setOrigin(buttonRect.left + buttonRect.width / 2.0f,
      buttonRect.top + buttonRect.height / 2.0f);

  // Set the position
  background.setPosition(position);

  // Set the fill color
  background.setFillColor(sf::Color::Black);

  // Load font and logistics
  kbPlanetEarth.loadFromFile(baseDir + "KBPlanetEarth.ttf");
  this->title = sf::Text(title, kbPlanetEarth, fontSize);
  this->title.setFillColor(sf::Color::White);
  this->title.setPosition(position);

  // Set origin of title to center
  sf::FloatRect titleRect = this->title.getLocalBounds();
  this->title.setOrigin(titleRect.left + titleRect.width / 2.0f,
      titleRect.top + titleRect.height / 2.0f);
}

Button::~Button() {
}

//Event handling
bool Button::handleEvent(const sf::Event& evt) {

  // Check if clicked
  if (evt.type == sf::Event::MouseButtonPressed) {
    if (evt.mouseButton.button == sf::Mouse::Button::Left) {
      if (background.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y)) {

        //Send message
        messageStack.push(this->messageToEmit);
      }
    }
  }
}

void Button::handleMessage(const Message&) {
}

bool Button::update(float dt) {
}

// Draw the button
void Button::draw(sf::RenderWindow* context) {
  context->draw(background);
  context->draw(title);
}
