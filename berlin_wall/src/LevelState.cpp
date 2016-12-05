#include <iostream>
#include <algorithm>
#include "config.h"
#include "LevelState.h"
#include "StateManager.h"

LevelState::LevelState() : kbPlanetEarth(), background(sf::Vector2f(screenWidth, screenHeight)), spy(), soldier(), gameNotPaused(true), score(0) {
  kbPlanetEarth.loadFromFile(baseDir + "KBPlanetEarth.ttf");

  // Background
  backgroundImage.loadFromFile(baseDir + "bg.jpg");
  backgroundImage.setRepeated(true);
  background.setTexture(&backgroundImage);
  background.setTextureRect({ 0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight)});

  // TODO: Run Maze Stuff

}

LevelState::~LevelState() {
}

bool LevelState::handleEvent(const sf::Event& evt) {
  if (gameNotPaused) {
    spy.handleEvent(evt);
    soldier.handleEvent(evt);
  }
  return true;
}

int stepRate = 15;

void LevelState::handleMessage(const Message& msg) {
  if (gameNotPaused) {
    if (msg.getId() == Message::MessageId::EasyDifficulty ||
        msg.getId() == Message::MessageId::MediumDifficulty ||
        msg.getId() == Message::MessageId::HardDifficulty) {
      gameTime.restart();
    }
    spy.handleMessage(msg);
    soldier.handleMessage(msg);
  }
}

bool LevelState::update(float dt) {
  if (gameNotPaused) {
    soldier.update(dt);
    spy.update(dt);

    if (spy.spySprite.getGlobalBounds().intersects(soldier.soldierSprite.getGlobalBounds())) {
      messageStack.push(Message(Message::MessageId::SoldierKilled));
      score += 1;
    }

    remainingTime = 60.f - gameTime.getElapsedTime().asSeconds();
    gameNotPaused = (remainingTime > 0);
  }
  return true;
}

void LevelState::draw(sf::RenderWindow* context) {
  context->draw(background);
  soldier.draw(context);
  spy.draw(context);

  sf::Text timeText(std::to_string((remainingTime > 0) ? remainingTime : 0), kbPlanetEarth, 50);
  timeText.setPosition(screenWidth * 0.75, screenHeight * 0.05);
  timeText.setFillColor(sf::Color::Black);
  context->draw(timeText);
    
  sf::Text scoreText(std::to_string(score), kbPlanetEarth, 50);
  scoreText.setPosition(screenWidth * 0.75, screenHeight * 0.15);
  scoreText.setFillColor(sf::Color::Black);
  context->draw(scoreText);
}
