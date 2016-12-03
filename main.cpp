#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>
#include <SFML/Graphics.hpp>
<<<<<<< HEAD
=======
#include <string>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <random>
using namespace std;
>>>>>>> 8b533e33e0d6726837df96803c3d0e1cde9fcdb9

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

class Maze {
    public: 
        Maze(int size, int lineWidth);
        ~Maze();
        void setLineWidth (int width);
        void setMazeSize (int mazeSize);
        int generate();

    private:
        int posX, posY;
        enum eDirection;
        int Heading_X[9];
        int Heading_Y[9];
        int Mask[9];
        int size, lineWidth;
        bool* maze;
        
        int currentIndex();
        int randInt();
        int randInt4();
        bool IsDirValid( eDirection Dir );
        eDirection GetDirection();
};

Maze::Maze(int size, int lineWidth) {
    maze = new bool[size * size];
    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<> dis( 0, size-1 );
    uniform_int_distribution<> dis4( 0, 3 );
}

Maze::~Maze() {
    delete maze;
}

Maze::setMazeSize(int mazeSize) {
	size = mazeSize;
} 

Maze::setLineWidth(int width) {
	lineWidth = width;
}
Maze::currentIndex() {
    return posX + size * posY;
}
Maze::int randInt(){
        return static_cast<int>( dis( gen ) );
    }

Maze::int randInt4(){
        return static_cast<int>( dis4( gen ) );
    }
Maze::enum eDirection {
        eDirection_Invalid = 0,
        eDirection_Up      = 1,
        eDirection_Right   = 2,
        eDirection_Down    = 4,
        eDirection_Left    = 8
    };
//                   0  1  2  3  4  5  6  7  8
//                      U  R     D           L
Maze::int Heading_X[9] = { 0, 0,+1, 0, 0, 0, 0, 0,-1 };
Maze::int Heading_Y[9] = { 0,-1, 0, 0,+1, 0, 0, 0, 0 };
Maze::int Mask[9]      = {
                                0,
                                eDirection_Down | eDirection_Down << 4,
                                eDirection_Left | eDirection_Left << 4,
                                0,
                                eDirection_Up | eDirection_Up << 4,
                                0,
                                0,
                                0,
                                eDirection_Right | eDirection_Right << 4
                            };
Maze::bool IsDirValid( eDirection Dir ){
    int NewX = posX + Heading_X[ Dir ];
    int NewY = posY + Heading_Y[ Dir ];

    if ( !Dir || NewX < 0 || NewY < 0 || NewX >= size || NewY >= size ) return false;

    return !maze[ NewX + size * NewY ];
}

Maze::eDirection GetDirection() {
    eDirection Dir = eDirection( 1 << randInt4() );

    while ( true )
    {
        for ( int x = 0; x < 4; x++ )
        {
            if ( IsDirValid( Dir ) ) { return eDirection( Dir ); }

            Dir = eDirection( Dir << 1 );

            if ( Dir > eDirection_Left ) { Dir = eDirection_Up; }
        }

        Dir = eDirection( ( maze[ currentIndex() ] & 0xf0 ) >> 4 );

        // nowhere to go
        if ( !Dir ) return eDirection_Invalid;

        posX += Heading_X[ Dir ];
        posY += Heading_Y[ Dir ];

        Dir = eDirection( 1 << randInt4() );
    }
}

Maze::generate() {
    // prepare PRNG
	gen.seed(5489u);

	// clear maze
	fill( g_Maze, g_Maze + NumCells * NumCells, 0 );

	// setup initial point
	g_PtX = RandomInt();
	g_PtY = RandomInt();
    
    
    // Generate
    int Cells = 0;

    for ( eDirection Dir = GetDirection(); Dir != eDirection_Invalid; Dir = GetDirection() )
    {
        // a progress indicator, kind of
        if ( ++Cells % 1000 == 0 ) std::cout << ".";

        maze[ currentIndex() ] |= Dir;

        posX += Heading_X[ Dir ];
        posY += Heading_Y[ Dir ];

        maze[ currentIndex() ] = Mask[ Dir ];
    }
    cout << endl;
    
    return 0;
}