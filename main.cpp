#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "png.h"
using namespace std;
int main()
{ 
   SquareMaze m;
   m.makeMaze(150,150);
   std::cout << "MakeMaze complete" << std::endl;

   PNG* unsolved = m.drawMaze();
   unsolved->writeToFile("unsolved.png");
   delete unsolved;
   std::cout << "drawMaze complete" << std::endl;
   
   
   vector<int> sol = m.solveMaze();
   std::cout << "solveMaze complete" << std::endl;
   //for(int i=0; i<sol.size(); i++)
       //cout<<sol[i]<<" ";

   PNG* solved = m.drawMazeWithSolution();
   solved->writeToFile("solved.png");
   delete solved;
   std::cout << "drawMazeWithSolution complete" << std::endl;
   
   return 0;
}

