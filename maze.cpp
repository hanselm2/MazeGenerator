#include "maze.h"
#include "rgbapixel.h"


SquareMaze::SquareMaze()
{
    cells.addelements(4);
}


/*IDEA: get a dset of every cell, then starting from the first square, pick a direction, */
void SquareMaze::makeMaze(int width, int height)
{
    xmax = width;
    ymax = height;

    //clear the old info 
    cells.clear();    //not sure if this will work should inherit from the vector class
    vertWalls.clear();
    horWalls.clear();

    //constructs the blank grid
    int cellNumber = width * height;
    cells.addelements(cellNumber);
    for(int i=0; i<cellNumber; i++)
    {   vertWalls.push_back(true);
        horWalls.push_back(true);    
    }
    
    srand (time(NULL));

    int partitions = cellNumber;
    
    while( partitions > 1 )          //? how do i partition this/how do i know when all cells share a common root. 
    {
        int randHeight = rand() % (height) ; //draw it out of you have a hard time remembering the geometry of why this works
        int randWidth = (rand() % width) +1 ;
        int direction =  rand() % 2;
        int randCell = randHeight*width + randWidth;

        /*cout<<partitions<<"\t";
        cout<<"direction: " <<direction<<"\t";
        cout<<"randCell: "<<randCell<<"\t";
        cout<<"findrandCell: "<<cells.find(randCell)<<"\t";
        cout<<"findrandCell+1; "<<cells.find(randCell+1)<<"\t";
        
        cout<<"findrandCell+width"<<cells.find(randCell+width)<<endl;
        */
        if( (direction == 0) && ((randCell%width)!=0) ) //draw it, if mod with width is =0 its an edge cell
        {
            if( cells.find(randCell) != cells.find(randCell+1) )    //check to see if they are connected
            {   vertWalls[randCell-1] = false;    //destroy the wall
                cells.setunion(randCell, randCell+1);    //union the randCell with the cell to its right
                partitions --;
            }
        }

        else if(direction == 1 && ( (randHeight+1)<height ) ) 
        {
            if( cells.find(randCell) != cells.find(randCell+width) )    //convention will be cross rows then colums
            {   horWalls[randCell-1] = false;     //destroy the wall
                cells.setunion(randCell, randCell+width);   //union the randCell with the cell below it
                partitions --;
            }
        }
    }     
}

//convention will be as follows:0= right, 1=down, 2=left, 3=up
bool SquareMaze::canTravel(int x, int y, int dir) const
{
    int cellLoc = y*xmax + x;

    //! being used because we said true is a wall exists
    if(dir == 0)
        return !vertWalls[cellLoc];
    
    else if(dir == 1)
        return !horWalls[cellLoc];
    
    else if(dir == 2)
    {   
        if( x != 0 )
            return !vertWalls[cellLoc-1];
        else return false;
    }

    else if(dir == 3)
    {
        if( y != 0 )
            return !horWalls[cellLoc-xmax];
        else return false;
    }
    //if everything fails just say it cant travel
    return false;
}


//overrides the random maze and lets you make specific walls exist or not
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    int cellLoc = y*xmax + x;

    if(dir == 0)
        vertWalls[cellLoc] = exists;
   
    else if(dir == 1)
        horWalls[cellLoc] = exists;
}

vector<int> SquareMaze::solveMaze()
{
    vector<int> bestpath, startPath;
    int x, y, bestx;
    x=0;
    y=0;
    bestx = xmax;
    startPath.push_back(0);// starts the first path to be the origin

    solveHelp(startPath, bestpath, x, y, bestx);

    bestpath.erase( bestpath.begin() );  // because we already start inside of the first cell
    
    return bestpath;
}

//bool used to communicate when it is at an edge or not
void SquareMaze::solveHelp( vector<int> & currentPath, vector<int> & best, int x, int y, int & bestx )
{
    //if were on a bottom edge, compare the length of the two vectors, the longest one is now the best, return
    if(y == (ymax-1))
    {   if( currentPath.size() > best.size() )
        {   best = currentPath;
            bestx = x;
        }
        
        else if( currentPath.size() == best.size() ) //tie break on farthest left location
        {   if( x < bestx)
            {   best = currentPath;
                bestx = x;
            }
        }
    }

    int parent = (currentPath.back() + 2)%4;    // makes right left, and up down
    //fuck simplicity trying to use a for loop
    for(int i=0; i<4; i++)
    {
        if( i!=parent && canTravel(x,y,i) )     // if we are not going where we came from, and there is no wall, then go there
        {   
            currentPath.push_back(i);
            if( i==0 )
                solveHelp(currentPath, best, x+1, y, bestx);
            if( i==1 )
                solveHelp(currentPath, best, x, y+1, bestx);
            if( i==2 )
                solveHelp(currentPath, best, x-1, y, bestx);
            if( i==3 )
                solveHelp(currentPath, best, x, y-1, bestx);
        }
    }
    
    currentPath.pop_back();
}

PNG* SquareMaze::drawMaze() const
{
    PNG * picture = new PNG(xmax*10 +1, ymax*10 +1);
    
    //blacken the first two rows
    RGBAPixel black = RGBAPixel(0,0,0);
    for(size_t i=10; i<(xmax*10); i++)
        *((*picture)(i, 0)) = black;
    for(int j=0; j<(ymax*10); j++)
        *((*picture)(0,j)) = black;

    //make the walls
    int x, y;
    int cellNumber = xmax*ymax;
    for(int i=0; i<cellNumber; i++)
    {
        x = i % xmax;
        y = (i / xmax);
        //check the verticle valls
        if( vertWalls[i] )
        {
            for(int j=0; j<=10; j++)
                *((*picture)( ((x+1)*10), (y*10 + j) )) = black;
        }

        if( horWalls[i] )
        {
            for(int j=0; j<=10; j++)
                *((*picture)( (x*10 + j), ((y+1)*10) )) = black;
        }
    }
    return picture;
}

PNG* SquareMaze::drawMazeWithSolution()
{
    PNG * picture = drawMaze();
    vector<int> solution = solveMaze();

    RGBAPixel red = RGBAPixel(255, 0, 0);
    int x, y;
    x = 5;
    y=5;

    for(std::vector<int>::iterator it = solution.begin(); it != solution.end(); it++)
    {
        if(*it == 0)
        {   for(int i=0; i<=10; i++)
                *((*picture)( x+i, y )) = red;
            x = x+10;
        }
        if(*it == 1)
        {   for(int i=0; i<=10; i++)
                *((*picture)( x, y+i )) = red;
            y = y+10;
        }
        if(*it == 2)
        {   for(int i=0; i<=10; i++)
                *((*picture)( x-i, y )) = red;
            x= x-10;
        }
        if(*it == 3)
        {   for(int i=0; i<=10; i++)
                *((*picture)( x, y-i )) = red;
            y = y-10;
        }
    }   

    // delete the bottom wall
    x = x-5;
    y = y+5;
    
    RGBAPixel white = RGBAPixel(255, 255, 255);
    for(int i=1; i<10; i++)
        *((*picture)(x+i, y) ) = white;

    return picture;
}

