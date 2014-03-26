#ifndef _MAZE_H
#define _MAZE_H

#include "png.h"
#include "dsets.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "rgbapixel.h"

using std::vector;
using namespace std;

class SquareMaze
{
    public:
        //set will be 1, and will be a blank PNG
        SquareMaze();

        //make maze by randomly destroying walls after drawing a grid and insure that there is just 1 final set 
        void makeMaze(int width, int height);

        //returns if its possible to move forwards given a square and a direction, true if no wall
        //edge cases are the entrance and exit
        bool canTravel(int x, int y, int dir) const;

        //sets a wall depending if the wall already exists
        void setWall(int x, int y, int dir, bool exists);

        //traverses the maze, sensitive to runtime
        vector<int> solveMaze();

        //draws the maze without the solution
        PNG* drawMaze() const;

        //calls drawmaze, then solve maze, modifies the png from draw maze to show the solution vector and the exit
        PNG* drawMazeWithSolution();

    private:
 

        void solveHelp( vector<int> & currentPath, vector<int> & best, int x, int y, int & bestx);

        DisjointSets cells;
        vector<bool> vertWalls; //true will be wall exists, false will be not exists
        vector<bool> horWalls;

        int xmax;   //storing these because im having 1 array for a 2d picture
        int ymax;

};
#endif

