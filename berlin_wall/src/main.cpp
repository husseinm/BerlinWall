#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

<<<<<<< HEAD
#include "berlin_wall/include/StateManager.h"


int main(int argc, char* argv[]) {
  sf::VideoMode resolution = sf::VideoMode(800, 600);

  // TODO: Get from Config file...
  // 4:3 resolution = sf::VideoMode(1366, 768);

  sf::RenderWindow mainWindow(resolution, "Berlin Wall");
  mainWindow.setFramerateLimit(120);
  mainWindow.setVerticalSyncEnabled(true);

   //mainWindow.setIcon(unsigned int width, unsigned int height, const Uint8 *pixels)

  StateManager* manager = StateManagerFactory::getManager(std::unique_ptr<sf::RenderWindow>(&mainWindow));
=======
#include "config.h"
#include "StateManager.h"


int main(int argc, char* argv[]) {
    sf::VideoMode resolution = sf::VideoMode::getDesktopMode();

    // TODO: Get from Config
  auto mainWindow = std::make_shared<sf::RenderWindow>(resolution, "Berlin Wall");
  mainWindow->setFramerateLimit(120);
  mainWindow->setVerticalSyncEnabled(true);
  mainWindow->setMouseCursorVisible(false);
    sf::Image appIcon;
    appIcon.loadFromFile(baseDir + "icon.png");
  mainWindow->setIcon(128, 128, appIcon.getPixelsPtr());

  StateManager* manager = StateManagerFactory::getManager(mainWindow);
>>>>>>> origin/master
  manager->registerState(StateId::TitleState);
  manager->pushState(StateId::TitleState);

  float delta = 0.0;

<<<<<<< HEAD
  while (mainWindow.isOpen()) {

=======
  while (mainWindow->isOpen()) {
>>>>>>> origin/master
    // Clear the screen
    mainWindow->clear();

    // Handle Input - TODO: Move to thread
    sf::Event event;

    while (mainWindow->pollEvent(event)) {
      manager->handleEvent(event);
    }
    /*
    while (MessageStack.pollMessage()) {
      manager->handleMessage(<#const Message &#>)
    }
    */
    manager->update(delta);
    manager->draw();

    // Flip the buffer
    mainWindow->display();

    //delta = Timer.reset();
  }
}
