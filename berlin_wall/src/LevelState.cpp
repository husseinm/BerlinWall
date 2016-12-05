#include <iostream>
#include "config.h"
#include "LevelState.h"
#include "StateManager.h"

LevelState::LevelState() : kbPlanetEarth(), background(sf::Vector2f(screenWidth, screenHeight)) {
    kbPlanetEarth.loadFromFile(baseDir + "KBPlanetEarth.ttf");

    // Background
    backgroundImage.loadFromFile(baseDir + "bg.jpg");
    backgroundImage.setRepeated(true);
    background.setTexture(&backgroundImage);
    background.setTextureRect({ 0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight)});
}

LevelState::~LevelState() {
}

bool LevelState::handleEvent(const sf::Event& evt) {
  return true;
}

void LevelState::handleMessage(const Message& msg) {
  if (msg.getId() == Message::EasyDifficulty) {
    numberOfSoldiers = 3;
  } else if (msg.getId() == Message::MediumDifficulty) {
    numberOfSoldiers = 4;
  } else if (msg.getId() == Message::HardDifficulty) {
    numberOfSoldiers = 5;
  }
}

bool LevelState::update(float dt) {
    return true;
}

void LevelState::draw(sf::RenderWindow* context) {
    context->draw(background);
}
