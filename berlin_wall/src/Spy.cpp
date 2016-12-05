#include "config.h"
#include "StateManager.h"
#include "Spy.h"

Spy::Spy() : canMoveUp(true), canMoveDown(true), canMoveLeft(true), canMoveRight(true), stepRate(0) {
  frontSpy.loadFromFile(baseDir + "spy_front.png");
  backSpy.loadFromFile(baseDir + "spy_back.png");
  leftSpy.loadFromFile(baseDir + "spy_left.png");
  rightSpy.loadFromFile(baseDir + "spy_right.png");

  // Initial position and texture
  spySprite.setPosition(100, 100);
  spySprite.setTexture(frontSpy);

  // Set origin to center
  sf::FloatRect spyRect = spySprite.getLocalBounds();
  spySprite.setOrigin(spyRect.left + spyRect.width / 2.0f,
      spyRect.top + spyRect.height / 2.0f);
}

Spy::~Spy() {
}

// Handle key presses
bool Spy::handleEvent(const sf::Event& evt) {
  if (evt.type == sf::Event::KeyPressed) {
    if (evt.key.code == sf::Keyboard::W ||
        evt.key.code == sf::Keyboard::Up) {
      messageStack.push(Message(Message::SpyMovedUp));
    } else if (evt.key.code == sf::Keyboard::A ||
        evt.key.code == sf::Keyboard::Left) {
      messageStack.push(Message(Message::SpyMovedLeft));
    } else if (evt.key.code == sf::Keyboard::S ||
        evt.key.code == sf::Keyboard::Down) {
      messageStack.push(Message(Message::SpyMovedDown));
    } else if (evt.key.code == sf::Keyboard::D ||
        evt.key.code == sf::Keyboard::Right) {
      messageStack.push(Message(Message::SpyMovedRight));
    }
  }

  return true;
}

// Basic logic for the spy movement
void Spy::handleMessage(const Message& msg) {
  if (msg.getId() == Message::MessageId::SpyMovedUp) {
    spySprite.setTexture(backSpy);
    if (canMoveUp) move(0, -stepRate);
  } else if (msg.getId() == Message::MessageId::SpyMovedDown) {
    spySprite.setTexture(frontSpy);
    if (canMoveDown) move(0, stepRate);
  } else if (msg.getId() == Message::MessageId::SpyMovedLeft) {
    spySprite.setTexture(leftSpy);
    if (canMoveLeft) move(-stepRate ,0);
  } else if (msg.getId() == Message::MessageId::SpyMovedRight) { 
    spySprite.setTexture(rightSpy);
    if (canMoveRight) move(stepRate, 0);
  }

  // Set the number of soldiers depending on difficulty
  if (msg.getId() == Message::EasyDifficulty) {
    stepRate = 60;
  } else if (msg.getId() == Message::MediumDifficulty) {
    stepRate = 20;
  } else if (msg.getId() == Message::HardDifficulty) {
    stepRate = 7;
  }
}

// Move spy
void Spy::move(int x, int y) {
  spySprite.setPosition(spySprite.getPosition().x + x, spySprite.getPosition().y + y);
}

// Moving range
bool Spy::update(float dt) {
  canMoveLeft = spySprite.getPosition().x > 0;
  canMoveRight = spySprite.getPosition().x < screenWidth;
  canMoveDown = spySprite.getPosition().y < screenHeight;
  canMoveUp = spySprite.getPosition().y > 0;
}

void Spy::draw(sf::RenderWindow* context) {
  // inside the main loop, between window.clear() and window.display()
  context->draw(spySprite);
}
