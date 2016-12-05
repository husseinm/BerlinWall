#include "config.h"
#include "Soldier.h"

Soldier::Soldier() {
  soldierTexture.loadFromFile(baseDir + "soldier.png");
  soldierSprite.setTexture(soldierTexture);

  sf::FloatRect soldierRect = soldierSprite.getLocalBounds();
  soldierSprite.setOrigin(soldierRect.left + soldierRect.width / 2.0f,
      soldierRect.top + soldierRect.height / 2.0f);

  regenerate();
}

Soldier::~Soldier() {
}

bool Soldier::handleEvent(const sf::Event& evt) {
  return true;
}

void Soldier::handleMessage(const Message& msg) {
  if (msg.getId() == Message::SoldierKilled) {
    regenerate();
  }
}

bool Soldier::update(float dt) {
}

void Soldier::draw(sf::RenderWindow* context) {
  context->draw(soldierSprite);
}

void Soldier::regenerate() {
  // Get random positions the soldiers
  int x = 256 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 768)) ;
  int y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 768));
  soldierSprite.setPosition(x, y);
}

