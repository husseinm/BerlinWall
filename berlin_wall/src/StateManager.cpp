#include <memory>
#include <iostream>

#include "config.h"
#include "StateManager.h"
#include "TitleState.h"
#include "LevelState.h"
#include "DifficultyState.h"

/* 

   1. Create the other States
   2. Get them to run
   3. Ensure Difficulty
   4. Spy/Solider
   5. Maze
   6. Game

*/

std::stack<Message> messageStack = std::stack<Message>();

StateManager::StateManager(std::shared_ptr<sf::RenderWindow> context) : context(context), renderView(), cursorTexture(), cursor() {
  // We are using a cursor sprite over the OS due to time constraints
  // Prepare the cursor sprite to be drawn over the mouse throughout the game
  cursorTexture.loadFromFile(baseDir + "cursor.png");
  cursor.setTexture(cursorTexture);
  cursor.setRotation(-20);

  // Set the Fixed View & Render View to the initial window size since no resizing has yet happened
  // Fixed View is necessary for linear cursor rendering
  fixedView = context->getView();
  renderView = fixedView;

  //updateViews(context->getSize().x, context->getSize().y);
}

StateManager::~StateManager() {
}

void StateManager::registerState(StateId stateToCreate) {
  switch (stateToCreate) {
    case (TitleState):
      states[TitleState] = std::unique_ptr<State>(new class TitleState());
    case (LevelState):
      states[LevelState] = std::unique_ptr<State>(new class LevelState());
    case (DifficultyState):
      states[DifficultyState] = std::unique_ptr<State>(new class DifficultyState());
  };
}

void StateManager::pushState(StateId stateToPush) {
  currentState = states[stateToPush].get();
}

bool StateManager::handleEvent(const sf::Event& evt) {
  switch(evt.type) {
    case sf::Event::Closed:
      context->close();
    case sf::Event::Resized:
      // Update the Letterbox
      updateViews(evt.size.width, evt.size.height);
  }

  currentState->handleEvent(evt);
};

void StateManager::handleMessage(const Message& message) {
  switch (message.getId()) {
    case Message::MessageId::CloseGame:
      context->close();
      return;
    case Message::MessageId::ChooseDifficulty:
      pushState(DifficultyState);
      return;
  }

  currentState->handleMessage(message);
};

bool StateManager::update(float dt) {
  return currentState->update(dt);
};

void StateManager::draw() {
  // Render the Game in the Viewport
  context->setView(renderView);
  currentState->draw(context.get());

  // Render the cursor relative to the entire window
  context->setView(fixedView);
  sf::Vector2f cursorPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*context.get()));
  cursorPos.x -= 15; // Offset the Image size
  cursor.setPosition(cursorPos);
  context->draw(cursor);
};

StateManager* StateManagerFactory::getManager(std::shared_ptr<sf::RenderWindow> context) {
  static StateManager* manager = new StateManager(context);

  return manager;
};

void StateManager::updateViews(int newWidth, int newHeight) {
  /*
  // Compares the aspect ratio of the window to the aspect ratio of the view,
  // and sets the view's viewport accordingly in order to archieve a letterbox effect.
  // A new view (with a new viewport set) is returned.
  float windowRatio = newWidth / static_cast<float>(newHeight);
  float viewRatio = (4/3);
  float sizeX = 1;
  float sizeY = 1;
  float posX = 0;
  float posY = 0;
  bool horizontalSpacing = !(windowRatio < viewRatio);

  // If horizontalSpacing is true, the black bars will appear on the left and right side.
  // Otherwise, the black bars will appear on the top and bottom.
  if (horizontalSpacing) {
  sizeX = viewRatio / windowRatio;
  posX = (1 - sizeX) / 2.f;
  } else {
  sizeY = windowRatio / viewRatio;
  posY = (1 - sizeY) / 2.f;
  }

  renderView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
  fixedView.setSize(newWidth, newHeight);
  fixedView.setCenter(newWidth / 2, newHeight / 2);
  screenWidth = newWidth;
  screenHeight = newHeight;
  */
}
