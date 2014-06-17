//
//  Graph.h
//  ADS
//
//  Created by yuqing on 14-3-19.
//  Copyright (c) 2014年 yuqing. All rights reserved.
//
#include "FHeap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
#ifndef ADS_Graph_h
#define ADS_Graph_h
//
//  FHeap.h
//  ADS
//
//  Created by yuqing on 14-3-19.
//  Copyright (c) 2014年 yuqing. All rights reserved.
//



class Node//store an edge
{
public:
    int destiny;
    int cost;
    Node(int des=0, int cos=0)
    {
        destiny=des;
        cost=cos;
    }
    void print()
    {
        cout<<destiny<<" "<<cost<<" ";
    }
};

class Graph
{
    int numOfVer;
    int numOfedge;
    vector< vector <Node *> >aList;//the graph structure
public:
    Graph(int numv=0, int numedge=0)
    {
        numOfedge=numedge;
        numOfVer=numv;
    }
    
    int fromFile(char* fname);
    void insert(int s,int d, int v)
    {
        Node *nod=new Node (d,v);
        aList.at(s).push_back(nod);
        nod=new Node (s,v);
        aList.at(d).push_back(nod);
    }
    
    void simpleMST();
    void FHeapMST();
    
};
int Graph::fromFile(char* fname)
{
    int source,destiny,cost;
    ifstream in(fname);
    Node *nod;
    
    if(in)
    {
        in>>numOfVer>>numOfedge;
        for(int i=0;i<numOfVer;i++)
        {
            vector <Node *> temp;
            aList.push_back(temp);
        }
        while(!in.eof())
        {
            in>>source>>destiny>>cost;
            if(!in.eof())
            {
                cout<<source<<"-"<<destiny<<" :"<<cost<<endl;
                nod=new Node (destiny,cost);
                aList.at(source).push_back(nod);
                nod =new Node (source, cost);
                aList.at(destiny).push_back(nod);
            }
                
        }
        return 1;
    }
    else return 0;
                
}

void Graph::simpleMST()
{
    int minCost=0;
    vector<Node *> tempVec;
    int lowest[numOfVer];
    int closest[numOfVer];
    bool visited[numOfVer];
    int minpos;
    for(int i=0;i<numOfVer;i++)
    {
        lowest[i]=10000;
        closest[i]=0;
        visited[i]=false;
    }
    lowest[0]=0;
    
    for(int j=0;j<numOfVer;j++){
        int min=10001;
        minpos=-1;
        for(int i=0;i<numOfVer;i++)
        {
            
            if((lowest[i]<min)&&(!visited[i]))
            {
                min=lowest[i];
                minpos=i;
            }
            
        }
        cout<<"min:"<<minpos<<endl;
        visited[minpos]=true;
        minCost+=lowest[minpos];
        tempVec=aList.at(minpos);
        
        
        for(vector<Node *>::iterator it = tempVec.begin() ; it != tempVec.end(); ++it)
        {
            //r=(*it)->destiny;
            if((!visited[(*it)->destiny])&&(*it)->cost<lowest[(*it)->destiny])
            {
                lowest[(*it)->destiny]=(*it)->cost;
                closest[(*it)->destiny]=minpos;
            }
        }
    }
    cout<<minCost<<endl;
    for(int i=1;i<numOfVer;i++)
    {
        cout<<closest[i]<<" "<<i<<"cost: "<<lowest[i]<<endl;
    }
    
}
void Graph::FHeapMST()
{
    FHeap<int> FH;
    int MSTCost=0;
    bool visited[numOfVer];
    for(int j=0;j<numOfVer;j++)
        visited[j]=false;
    
    int closest[numOfVer];
    vector<Node *> tempVec;
    FH.insert(0, 0, 0);
    int minD;
    int c;
    int d;
    FHeapNode<int> *mini,*t;
    for(int i=0;i<numOfVer;i++)
    {
        mini=FH.removemin();
        if(!mini) break;
        minD=mini->destiny;
        MSTCost+=mini->value;
        //cout<<mini->source<<"->"<<minD<<"cost:"<<mini->value<<endl;
        visited[minD]=true;
        closest[minD]=mini->source;
        tempVec=aList.at(minD);
        for(vector<Node *>::iterator it = tempVec.begin() ; it != tempVec.end(); ++it)
        {
            d=(*it)->destiny;
            c=(*it)->cost;
            t=FH.findbyD(d);
            if(!visited[d] && !t)
                FH.insert(c,minD,d);
            else if(!visited[d])
                FH.DecreaseKey(t, c, minD, d);
            
        }
        delete []mini;
    }
    cout<<MSTCost<<endl;
}
#endif
