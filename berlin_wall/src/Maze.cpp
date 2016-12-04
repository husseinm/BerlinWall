#include "config.h"
#include "berlin_wall/include/Soldier.h"

Maze::Maze(int size, int lineWidth) {
    maze = new bool[size * size];
}

Maze::~Maze() {
    delete maze;
}

void Maze::setMazeSize(int mazeSize) {
	size = mazeSize;
}

void Maze::setLineWidth(int width) {
	lineWidth = width;
}
int Maze::currentIndex() {
    return posX + size * posY;
}
int Maze::randInt(){
        return static_cast<int>( dis( gen ) );
    }

int Maze::randInt4(){
        return static_cast<int>( dis4( gen ) );
    }
//                   0  1  2  3  4  5  6  7  8
//                      U  R     D           L

bool Maze::IsDirValid( eDirection Dir ){
    int NewX = posX + Heading_X[ Dir ];
    int NewY = posY + Heading_Y[ Dir ];

    if ( !Dir || NewX < 0 || NewY < 0 || NewX >= size || NewY >= size ) return false;

    return !maze[ NewX + size * NewY ];
}

Maze::eDirection Maze::GetDirection() {
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

int Maze::generate() {

    int Heading_X[9] = { 0, 0,+1, 0, 0, 0, 0, 0,-1 };
    int Heading_Y[9] = { 0,-1, 0, 0,+1, 0, 0, 0, 0 };
    int Mask[9]      = {
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

    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<> dis( 0, size-1 );
    uniform_int_distribution<> dis4( 0, 3 );

    // prepare PRNG
	gen.seed(5489u);

	// clear maze
	fill( maze, maze + size * size, 0 );

	// setup initial point
	posX = randInt();
	posY = randInt();


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
