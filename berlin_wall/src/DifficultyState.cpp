#include <iostream>
#include "config.h"
#include "DifficultyState.h"
#include "StateManager.h"

static sf::Vector2f buttonSize(screenWidth * 0.75, screenHeight * 0.2);

DifficultyState::DifficultyState() : kbPlanetEarth(),
  background(sf::Vector2f(screenWidth, screenHeight)),
  easyButton("Easy", 75, buttonSize, sf::Vector2f(screenWidth * 0.5, screenHeight * 0.36), Message::EasyDifficulty),
  mediumButton("Medium", 75, buttonSize, sf::Vector2f(screenWidth * 0.5, screenHeight * 0.61), Message::MediumDifficulty),
  hardButton("Hard", 75, buttonSize, sf::Vector2f(screenWidth * 0.5, screenHeight * 0.86), Message::HardDifficulty) {
    kbPlanetEarth.loadFromFile(baseDir + "KBPlanetEarth.ttf");

    // Background
    backgroundImage.loadFromFile(baseDir + "bg.jpg");
    backgroundImage.setRepeated(true);
    background.setTexture(&backgroundImage);
    background.setTextureRect({ 0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight)});

    // Main Title
    mainHeader = sf::Text("Choose a Difficulty", kbPlanetEarth, 100);
    mainHeader.setStyle(sf::Text::Bold);
    mainHeader.setFillColor(sf::Color::Black);
    sf::FloatRect headerRect = mainHeader.getLocalBounds();
    mainHeader.setOrigin(headerRect.left + headerRect.width / 2.0f,
        headerRect.top + headerRect.height / 2.0f);
    mainHeader.setPosition(screenWidth * 0.5, screenHeight * 0.12);
  }

DifficultyState::~DifficultyState() {
}

bool DifficultyState::handleEvent(const sf::Event& evt) {
  easyButton.handleEvent(evt);
  mediumButton.handleEvent(evt);
  hardButton.handleEvent(evt);

  return true;
}

void DifficultyState::handleMessage(const Message& msg) {
  if (msg.getId() == Message::EasyDifficulty || 
      msg.getId() == Message::MediumDifficulty ||
      msg.getId() == Message::HardDifficulty) {
    StateManagerFactory::getManager()->pushState(LevelState);
    messageStack.push(msg);
  }
}

bool DifficultyState::update(float dt) {
  return true;
}

void DifficultyState::draw(sf::RenderWindow* context) {
  context->draw(background);
  context->draw(mainHeader);
  easyButton.draw(context);
  mediumButton.draw(context);
  hardButton.draw(context);
}
