#ifndef _DSETS_H
#define _DSETS_H

#include <vector>

using std::vector;

//shouldnt be templatized if you need to templatize change to 2 vectors, 1 the int and the other the data type, just update both of them at the same time, run time effeciencies will not suffer
class DisjointSets
{

    public:

        //default constructor to which sets has no elements
        //DisjointSets();

        //constructor which will creat a sets with then specified number of elements
        //DisjointSets(int numcreate);

        //destructor should not be required, no dynamic memory storage is being used

        // copy constructor and = operator may need to be implemented, unsure of that

        //the int coresponding to the location of the vector will 
        void addelements(int num);
        
        //find correlated to the index 
        int find(int elem);

        //creates a union based on two indices
        void setunion(int a, int b);
       
        void clear();

    private:

        //vector that we will be using to store the disjoint set, will not need to be dynamic
        vector<int> sets;


};
#endif


