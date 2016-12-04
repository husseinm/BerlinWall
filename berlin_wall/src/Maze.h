#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <random>
using namespace std;

class Maze {
    public:
        Maze(int size, int lineWidth);
        ~Maze();
        void setLineWidth (int width);
        void setMazeSize (int mazeSize);
        int generate();

    private:
        int posX, posY;
        int size, lineWidth;
        bool* maze;
        int Heading_X[9];
        int Heading_Y[9];
        int Mask[9];

        enum eDirection {
            eDirection_Invalid = 0,
            eDirection_Up      = 1,
            eDirection_Right   = 2,
            eDirection_Down    = 4,
            eDirection_Left    = 8
        };

        random_device rd;
        mt19937 gen;
        uniform_int_distribution<> dis;
        uniform_int_distribution<> dis4;

        int currentIndex();
        int randInt();
        int randInt4();
        bool IsDirValid( eDirection Dir );
        eDirection GetDirection();
};

#endif
