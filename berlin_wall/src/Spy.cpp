#include "config.h"
#include "berlin_wall/include/Spy.h"

Spy::Spy() {
}

Spy::~Spy() {
}

bool Spy::handleEvent(const sf::Event& evt) {
  return true;
}

// Basic logic for the spy movement
void Spy::handleMessage(const Message&) {
  if (Message == up){
    spySprite.setTexture(backSpy);
      // Offset 1 up from the position
    move(0,1);
  }
  if (Message == down){
    spySprite.setTexture(frontSpy);
      // Offset 1 down from the position
    move(0,-1); 
  }
  if (Message == left){
    spySprite.setTexture(leftSpy);
      // Offset 1 left from the position
    move(-1,0);
  }
  if (Message == right){
    spySprite.setTexture(rightSpy);
      // Offset 1 right from the position
    move(1,0);
  }
  if (Message == collide){
      //Don't move
    move(0,0);
  }
}

bool Spy::update(float dt) {
}

// 
void Spy::draw(sf::RenderWindow* context) {
  // Render the appropriate image for the orientation of the spy
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
}
