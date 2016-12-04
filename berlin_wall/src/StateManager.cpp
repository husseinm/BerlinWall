#include <memory>
#include <iostream>

#include "config.h"
#include "StateManager.h"
#include "TitleState.h"

/* Mahdi's Todo for today:
    3. Custom Cursor/Icon
    4. Settings File Class
    5. StateManager
    6. Comment the shit out of everything
 
 States
 
 THEN -> Audio/Scores
 
 */


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
    updateViews(context->getSize().x, context->getSize().y);
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
      // Update the Letterbox
      updateViews(evt.size.width, evt.size.height);
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
  // Render the Game in the Viewport
  context->setView(renderView);
  states[StateId::TitleState]->draw(context.get());
    
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
}
