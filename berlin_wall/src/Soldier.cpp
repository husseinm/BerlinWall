#include "config.h"
#include "berlin_wall/include/Soldier.h"

Soldier::Soldier() {
}

Soldier::~Soldier() {
}

bool Soldier::handleEvent(const sf::Event& evt) {
  return true;
}

void Soldier::handleMessage(const Message&) {
  if(Message == die) {
      // Remove the soldier on death
    soldier.delete();
  }
}

bool Soldier::update(float dt) {
}

void Soldier::draw(sf::RenderWindow* context) {
  // Render
  sf::Texture soldierTexture;
  soldierTexture.loadFromFile("../assets/soldier.png");

  sf::Sprite soldierSprite;

  soldierSprite.setTexture(soldierTexture);

  // inside the main loop, between window.clear() and window.display()
  context->draw(spySprite);
}

int getNumSoldiers(string difficulty) {
    
    // Set the number of soldiers depending on difficulty
    
    int numSoldiers;
    if (difficulty == easy)
    {
        numSoldiers = 3;
    }
    else if (difficulty == medium)
    {
        numSoldiers = 4;
    }
    else if (difficulty == hard)
    {
        numSoldiers = 5;
    }
}

void randomSoldierPositions(int numSoldiers) {
    
    // Get random positions the soldiers
    
    float soldierPositionX[numSoldiers];
    float soldierPositionY[numSoldiers];

    for(int i = 0; i < numSoldiers; i++)
    {
        soldierPositionX[i] = 200 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(800-200))) ;
        soldierPositionY[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/600));
        soldierSprite.setPosition(soldierPositionX[i], soldierPositionY[i]);
    }
}
