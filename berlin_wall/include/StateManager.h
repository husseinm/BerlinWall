#ifndef BERLIN_WALL_STATE_MANAGER_H
#define BERLIN_WALL_STATE_MANAGER_H

#include <SFML/Graphics.hpp>
#include "berlin_wall/include/Message.h"
#include "berlin_wall/include/State.h"

class StateManager {
  public:
    ~StateManager();
    bool handleEvent(const sf::Event& evt);
    void handleMessage(const Message&);
    bool update(float dt);
    void draw();
    
    void registerState(StateId state);
    void pushState(StateId state);
    void popState();
  private:
    friend class StateManagerFactory;

    StateManager(std::shared_ptr<sf::RenderWindow> context);

    void updateViews(int newWidth, int newHeight);
    
    std::map<StateId, std::unique_ptr<State>> states;
    std::shared_ptr<sf::RenderWindow> context;
    sf::View renderView;
    sf::View fixedView;
    
    sf::Texture cursorTexture;
    sf::Sprite cursor;
};

class StateManagerFactory {
  public:
    static StateManager* getManager(std::shared_ptr<sf::RenderWindow> context = nullptr);
};

#endif
