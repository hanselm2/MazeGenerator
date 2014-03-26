#include "dsets.h"
#include <vector>
#include <iostream>
using namespace std;
using std::vector;

// will be used as our constructor by default the object is null as it is a vector
void DisjointSets::addelements(int num){    
    for(int i=0; i<=num; i++)
        sets.push_back(-1);
}

int DisjointSets::find(int elem){
    
    //cout<<elem<<endl;  
    if(sets[elem] < 0)
        return elem;
    else //reruce back down and unwrap
    {   sets[elem]=find(sets[elem]);
        return sets[elem];
    }
    
}


void DisjointSets::setunion(int a, int b){
    //find the root of bot a and b 
    int roota, rootb;
    roota = find(a);
    rootb = find(b);

    if (roota == rootb)
        return;

    sets[roota] = rootb;
}

void DisjointSets::clear(){
    sets.clear();
}


