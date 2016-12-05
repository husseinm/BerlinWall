#include "config.h"
#include "Spy.h"

Spy::Spy() {
  frontSpy.loadFromFile(baseDir + "spy_front.png");
  backSpy.loadFromFile(baseDir + "spy_back.png");
  leftSpy.loadFromFile(baseDir + "spy_left.png");
  rightSpy.loadFromFile(baseDir + "spy_right.png");

  spySprite.setPosition(100, 100);
  spySprite.setTexture(frontSpy);
  spySprite.scale(0.3, 0.3);
}

Spy::~Spy() {
}

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

void Spy::handleMessage(const Message& msg) {
  if (msg.getId() == Message::MessageId::SpyMovedUp) {
    spySprite.setTexture(backSpy);
    move(0, -15);
  } else if (msg.getId() == Message::MessageId::SpyMovedDown) {
    spySprite.setTexture(frontSpy);
    move(0, 15);
  } else if (msg.getId() == Message::MessageId::SpyMovedLeft) {
    spySprite.setTexture(leftSpy);
    move(-15 ,0);
  } else if (msg.getId() == Message::MessageId::SpyMovedRight) { 
    spySprite.setTexture(rightSpy);
    move(15, 0);
  } else if (msg.getId() == Message::MessageId::SpyCollided) {
    move(0, 0);
  }
}

void Spy::move(int x, int y) {
    spySprite.setPosition(spySprite.getPosition().x + x, spySprite.getPosition().y + y);
}

bool Spy::update(float dt) {
}

void Spy::draw(sf::RenderWindow* context) {
  // inside the main loop, between window.clear() and window.display()
  context->draw(spySprite);
}

