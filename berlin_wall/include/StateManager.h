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

    StateManager(std::unique_ptr<sf::RenderWindow> context);

    std::map<StateId, std::unique_ptr<State>> states;
    std::unique_ptr<sf::RenderWindow> context;
};

class StateManagerFactory {
  public:
    static StateManager* getManager(std::unique_ptr<sf::RenderWindow> context = nullptr);
};

#endif
