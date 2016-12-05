#ifndef SPY_H_INCLUDED
#define SPY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Spy : Entity
{
  public:
    Spy();
    ~Spy();

    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw(sf::RenderWindow* context);
  private:
    friend class LevelState;

    void move(int x, int y);

    bool canMoveLeft;
    bool canMoveRight;
    bool canMoveUp;
    bool canMoveDown;

    sf::Texture frontSpy;
    sf::Texture backSpy;
    sf::Texture leftSpy;
    sf::Texture rightSpy;

    sf::Sprite spySprite;

    int stepRate;
};

#endif
