//
//  main.cpp
//  ADS
//
//  Created by yuqing on 14-3-19.
//  Copyright (c) 2014年 yuqing. All rights reserved.
//
#include "Graph.h"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{

    // insert code here...
    //std::cout << "Hello, World!\n";
    
    Graph G;
    G.fromFile("/Users/thee/Documents/x.txt");
        /*G.insert(0,1,4);
    G.insert(0, 7, 8);
    G.insert(1, 2, 8);
    G.insert(1, 7, 11);
    G.insert(2, 3, 7);
    G.insert (2, 8, 2);
    G.insert ( 2, 5, 4);
    G.insert ( 3, 4, 9);
    G.insert ( 3, 5, 14);
    G.insert ( 4, 5, 10);
    G.insert ( 5, 6, 2);
    G.insert ( 6, 7, 1);
    G.insert ( 6, 8, 6);
    G.insert ( 7, 8, 7);*/
    cout<<"simep"<<endl;
    G.simpleMST();
    cout<<"FH"<<endl;
    G.FHeapMST();
    
    return 1;
}

