#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>
#include <SFML/Graphics.hpp>

#ifdef __APPLE__
#include "ResourcePath.hpp"
std::string baseDir = resourcePath();
#else
std::string baseDir = "";
#endif

class Message {
    
};

class StateManager;

class State {
public:
    virtual bool handleEvent(const sf::Event& evt) = 0;
    virtual void handleMessage(const Message&) = 0;
    virtual bool update(float dt) = 0;
    virtual void draw() = 0;
protected:
    friend class StateManager;

    State() = default;
    virtual ~State() = 0;
    
    enum Id {
        TitleState = 0,
        SettingsState,
        LevelState,
        PauseState,
        DifficultyState,
        ScoreState
    };
    
    Id stateId;
};

class StateManager {
public:
    StateManager() {
        
    }
    ~StateManager() {
        
    }
private:
    std::map<State::Id, std::unique_ptr<State>> states;
    
};

class TitleState : State {
public:
    bool handleEvent(const sf::Event& evt) { return true; };
    void handleMessage(const Message&) {};
    bool update(float dt) {};
    void draw() {};
private:
    friend class TitleStateFactory;
    
    TitleState() {
        
    }
    
    ~TitleState() {
        
    }
};

class TitleStateFactory {
public:
    static TitleState getState() {
        if (!titleState) {
            titleState = std::unique_ptr<TitleState>(new TitleState());
        }
        
        return *titleState.get();
    };
private:
    static std::unique_ptr<TitleState> titleState;
};


void drawTitleScreen(sf::RenderWindow& context) {
    // Render
    sf::Font font;
    
    if (!font.loadFromFile(baseDir + "/assets/KBPlanetEarth.ttf"))
        return EXIT_FAILURE;
    
    sf::Text text("Hello SFML", font, 50);
    text.setStyle(sf::Text::Bold);
    
    // inside the main loop, between window.clear() and window.display()
    context.draw(text);
}

int main(int argc, char* argv[]) {
    sf::VideoMode resolution = sf::VideoMode(800, 600);
    
    // TODO: Get from Config file...
    resolution = sf::VideoMode(1366, 768);
    
    sf::RenderWindow mainWindow(resolution, "Berlin Wall");
    mainWindow.setFramerateLimit(120);
    mainWindow.setVerticalSyncEnabled(true);
    // TODO: Set the icon
    //mainWindow.setIcon(unsigned int width, unsigned int height, const Uint8 *pixels)
    
    while (mainWindow.isOpen()) {
        // Clear the screen
        mainWindow.clear();
        
        // Handle Input - TODO: Move to thread
        sf::Event Event;
        
        while (mainWindow.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                mainWindow.close();
            }
        }
        
        // Render
        drawTitleScreen(mainWindow);
        
        // Flip the buffer
        mainWindow.display();
    }
}
