#include <memory>
#include "StateManager.h"
#include "TitleState.h"

/*
void maintainAspectRatio(float newWidth, float) {
  //first we check our new aspect width to see if it changed
  float newAspectWidth = window.getSize().x;
  float newAspectHeight = window.getSize().y;

  if(newAspectWidth != currentAspectWidth) {
    // width changed, maintain the aspect ratio and adjust the height
    currentAspectWidth = newAspectWidth;
    currentAspectHeight = currentAspectWidth / aspectRatio;
  } else if(newAspectHeight != currentAspectHeight) {
    // height changed, maintain aspect ratio and change the width
    currentAspectHeight = newAspectHeight;
    currentAspectWidth = currentAspectHeight * aspectRatio;
  }

  std::cout << "width: " << currentAspectWidth << " height: " << currentAspectHeight;
  window.setSize(sf::Vector2u(currentAspectWidth, currentAspectHeight));
}
*/
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
  switch(evt.type) {
    case sf::Event::Closed:
      context->close();
    case sf::Event::Resized:
      break;
      //maintainAspectRatio(evt.size.width, evt.size.height);
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
