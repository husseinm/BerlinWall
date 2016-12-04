#include <memory>
#include "StateManager.h"
#include "TitleState.h"

StateManager::StateManager(std::unique_ptr<sf::RenderWindow> context) : context(std::move(context)) {
}

StateManager::~StateManager() {
}

void StateManager::registerState(StateId stateToCreate) {
  states[stateToCreate] = std::unique_ptr<State>(new class TitleState());
}

void StateManager::pushState(StateId stateToPush) {

}

void StateManager::popState() {

}

bool StateManager::handleEvent(const sf::Event& evt) {
  if (evt.type == sf::Event::Closed) {
    context->close();
  }

  states[StateId::TitleState]->handleEvent(evt);
};

void StateManager::handleMessage(const Message& message) {
  states[StateId::TitleState]->handleMessage(message);
};

bool StateManager::update(float dt) {
  return states[StateId::TitleState]->update(dt);
};

void StateManager::draw() {
  states[StateId::TitleState]->draw(context.get());
};

StateManager* StateManagerFactory::getManager(std::unique_ptr<sf::RenderWindow> context) {
  static StateManager* manager = new StateManager(std::move(context));

  return manager;
};
