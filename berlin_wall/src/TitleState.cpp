#include <iostream>
#include "config.h"
#include "TitleState.h"
#include "StateManager.h"

TitleState::TitleState() : kbPlanetEarth(), background(sf::Vector2f(screenWidth, screenHeight)), quitButton("Quit Game", 75, sf::Vector2f(screenWidth * 0.75, screenHeight * 0.2),                                                                                                                    sf::Vector2f(screenWidth * 0.5, screenHeight * 0.8), Message::CloseGame), playGameButton("Play Now", 75, sf::Vector2f(screenWidth * 0.75, screenHeight * 0.2),                                                                                                                    sf::Vector2f(screenWidth * 0.5, screenHeight * 0.55), Message::ChooseDifficulty) {
  kbPlanetEarth.loadFromFile(baseDir + "KBPlanetEarth.ttf");
  mainHeader = sf::Text("Berlin Wall", kbPlanetEarth, 180);
  mainHeader.setStyle(sf::Text::Bold);
  mainHeader.setFillColor(sf::Color::Black);

  // Title
  sf::FloatRect headerRect = mainHeader.getLocalBounds();
  mainHeader.setOrigin(headerRect.left + headerRect.width / 2.0f,
      headerRect.top + headerRect.height / 2.0f);

  mainHeader.setPosition(screenWidth * 0.5, screenHeight * 0.2);

  // Background
  backgroundImage.loadFromFile(baseDir + "bg.jpg");
  backgroundImage.setRepeated(true);
  background.setTexture(&backgroundImage);
  background.setTextureRect({ 0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight)});

  // Quit Button
}

TitleState::~TitleState() {
}

bool TitleState::handleEvent(const sf::Event& evt) {
    quitButton.handleEvent(evt);
    playGameButton.handleEvent(evt);
  return true;
}

void TitleState::handleMessage(const Message&) {
    
}

bool TitleState::update(float dt) {
}

void TitleState::draw(sf::RenderWindow* context) {
  context->draw(background);
  context->draw(mainHeader);
  quitButton.draw(context);
  playGameButton.draw(context);
}
