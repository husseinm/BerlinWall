#include "config.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <random>
using namespace std;

int main(int argc, char* argv[]) {

  /* Code adapted from the SFML 2 "Window" example */

  cout << "Version " << BERLIN_WALL_VERSION_MAJOR << "." << BERLIN_WALL_VERSION_MINOR << endl;

  sf::Window App(sf::VideoMode(800, 600), "Berlin Wall");

  while (App.isOpen()) {
    sf::Event Event;
    while (App.pollEvent(Event)) {
      if (Event.type == sf::Event::Closed)
    App.close();
    }
    App.display();
  }
}



class Maze {
    public: 
        Maze();
        ~Maze();
        void setLineWidth (int width);
        void setMazeSize (int mazeSize);
        int generate();
    protected:
        int size, lineWidth;
        bool maze[size*size];
    private:
        int posX, posY;
        enum eDirection;
        int Heading_X[9], Heading_Y[9], Mask[9];
        int currentIndex();
        int randInt();
        int randInt4();
        bool IsDirValid( eDirection Dir );
        eDirection GetDirection();
};

Maze::Maze() {
    maze = new bool[size * size];
    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<> dis( 0, size-1 );
    uniform_int_distribution<> dis4( 0, 3 );
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
	std::fill( g_Maze, g_Maze + NumCells * NumCells, 0 );

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
    std::cout << std::endl;
    
    return 0;
}


    
