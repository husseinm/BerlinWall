#include "config.h"
#include <iostream>
#include "berlin_wall/include/TitleState.h"

TitleState::TitleState() {
}

TitleState::~TitleState() {
}

bool TitleState::handleEvent(const sf::Event& evt) {
  return true;
}

void TitleState::handleMessage(const Message&) {
}

bool TitleState::update(float dt) {
}

void TitleState::draw(sf::RenderWindow* context) {
  // Render
  sf::Font font;

  if (!font.loadFromFile(baseDir + "../assets/KBPlanetEarth.ttf"))
    std::cout << "Could Not Load Font";

  sf::Text text("Hello SFML", font, 50);
  text.setStyle(sf::Text::Bold);

  // inside the main loop, between window.clear() and window.display()
  context->draw(text);
}
