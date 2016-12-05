/*#include "config.h"
#include "berlin_wall/include/Spy.h"

Spy::Spy() {
}

Spy::~Spy() {
}

bool Spy::handleEvent(const sf::Event& evt) {
  return true;
}

void Spy::handleMessage(const Message&) {
  if (Message == up){
    spySprite.setTexture(backSpy);
    move(0,1);
  }
  if (Message == down){
    spySprite.setTexture(frontSpy);
    move(0,-1);
  }
  if (Message == left){
    spySprite.setTexture(leftSpy);
    move(-1,0);
  }
  if (Message == right){
    spySprite.setTexture(rightSpy);
    move(1,0);
  }
  if (Message == collide){
    move(0,0);
  }
}

bool Spy::update(float dt) {
}

void Spy::draw(sf::RenderWindow* context) {
  // Render
  sf::Texture frontSpy;
  frontSpy.loadFromFile("spy_front.png");

  sf::Texture backSpy;
  backSpy.loadFromFile("spy_back.png");

  sf::Texture leftSpy;
  leftSpy.loadFromFile("spy_left.png");

  sf::Texture rightSpy;
  rightSpy.loadFromFile("spy_right.png");

  sf::Sprite spySprite;

  spySprite.setTexture(spyTexture);
  spySprite.setPosition(200, 0);

  // inside the main loop, between window.clear() and window.display()
  context->draw(spySprite);
}*/
