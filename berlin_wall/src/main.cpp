#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "StateManager.h"


int main(int argc, char* argv[]) {
  auto mainWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "Berlin Wall", sf::Style::Close);
  mainWindow->setFramerateLimit(120);
  mainWindow->setVerticalSyncEnabled(true);
  mainWindow->setMouseCursorVisible(false);

  sf::Image appIcon;
  appIcon.loadFromFile(baseDir + "icon.png");
  mainWindow->setIcon(128, 128, appIcon.getPixelsPtr());

  StateManager* manager = StateManagerFactory::getManager(mainWindow);
  manager->registerState(StateId::TitleState);
  manager->pushState(StateId::TitleState);

  float delta = 0.0;

  while (mainWindow->isOpen()) {
    // Clear the screen
    mainWindow->clear();

    // Handle Input - TODO: Move to thread
    sf::Event event;

    while (mainWindow->pollEvent(event)) {
      manager->handleEvent(event);
    }

    while (!messageStack.empty()) {
      manager->handleMessage(messageStack.top());
      messageStack.pop();
    }

    manager->update(delta);
    manager->draw();

    // Flip the buffer
    mainWindow->display();

    //delta = Timer.reset();
  }
}
