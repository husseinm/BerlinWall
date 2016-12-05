#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "StateManager.h"


int main(int argc, char* argv[]) {
  // Set window settings
  auto mainWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "Berlin Wall", sf::Style::Close);

  // Set the max framerate
  mainWindow->setFramerateLimit(120);

  // Enable Vsync
  mainWindow->setVerticalSyncEnabled(true);

  // Hide the cursor
  mainWindow->setMouseCursorVisible(false);

  // Set the icon
  sf::Image appIcon;
  appIcon.loadFromFile(baseDir + "icon.png");
  mainWindow->setIcon(128, 128, appIcon.getPixelsPtr());

  // Make manager
  StateManager* manager = StateManagerFactory::getManager(mainWindow);
  manager->registerState(StateId::TitleState);
  manager->registerState(StateId::DifficultyState);

  manager->pushState(StateId::TitleState);

  sf::Clock frameTimer;
  sf::Time frameTime;

  while (mainWindow->isOpen()) {
    frameTime = frameTimer.restart();

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

    manager->update(frameTime.asMilliseconds());
    manager->draw();

    //std::cout << "FPS: " << (1000.f / frameTime.asMilliseconds()) << std::endl;

    // Flip the buffer
    mainWindow->display();
  }
}
