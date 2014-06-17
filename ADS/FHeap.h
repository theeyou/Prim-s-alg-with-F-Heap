//
//  FHeap.h
//  ADS
//
//  Created by yuqing on 14-3-19.
//  Copyright (c) 2014年 yuqing. All rights reserved.
//
#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;
#ifndef ADS_FHeap_h
#define ADS_FHeap_h


template<class T> struct FHeapNode
{
    FHeapNode<T> * pre;
    FHeapNode<T> *next;
    FHeapNode<T> *parent;
    FHeapNode<T> *child;
    T value;
    int source;
    int destiny;
    int degree;
    bool childcut;
    FHeapNode(T val,int sou,int des)
    {
        value=val;
        pre=this;
        next=this;
        parent=NULL;
        child=NULL;
        source=sou;
        destiny=des;
        degree=0;
        childcut=false;
    }
};

template<class T> class FHeap
{
    FHeapNode<T> *min;
public:
    FHeap()
    {
        min=NULL;
    }
    FHeapNode<T>* merge(FHeapNode<T> *s1,FHeapNode<T> *s2);
    void insert(T value,int source,int destiny);
    FHeapNode<T>* findminroot(FHeapNode<T> *s,int &d);
    int addchild(FHeapNode <T> *p, FHeapNode<T> *c);
    FHeapNode<T>* removemin();
    void cut(FHeapNode<T> *p, FHeapNode<T>* c);
    FHeapNode<T> *findbyD(int val)
    {
        return findbyD(min,val);
    }
    
    FHeapNode<T> *findbyD(FHeapNode<T> *heap,int val);
    void DecreaseKey(FHeapNode<T> *point, T nValue,int sou,int des);
    ~FHeap()
    {
        _deleteAll(min);
    }
    void _deleteAll(FHeapNode<T>* n) {
        if(n!=NULL) {
            FHeapNode <T>* c=n;
            do {
                FHeapNode<T>* d=c;
                c=c->next;
                _deleteAll(d->child);
                delete []d;
            } while(c!=n);
        }
    }
};
template <class T>
FHeapNode<T>* FHeap<T>::merge(FHeapNode<T> *ss1,FHeapNode<T> *ss2)//merge S1 and S2 while s1 must be min
{
    FHeapNode<T>* s1=ss1;
    FHeapNode<T>* s2=ss2;
    if(s1==NULL) return s2;
    else if(s2==NULL) return s1;
    else{
        if(s2->value<s1->value){
            FHeapNode<T> *t=s2;
            s2=s1;
            s1=t;
        }
        FHeapNode<T> *temp1=s1->next;
        FHeapNode<T> *temp2=s2->pre;
        s1->next=s2;
        s2->pre=s1;
        temp1->pre=temp2;
            temp2->next=temp1;
    }
    return s1;
}

template <class T>
void FHeap<T>::insert(T value,int source,int destiny)
{
    FHeapNode<T> *newnode=new FHeapNode<T> (value,source,destiny);
    min=merge(min, newnode);
};

template <class T>
FHeapNode<T>* FHeap<T>::findminroot(FHeapNode<T>* s,int &d)
{
    if(s==NULL)
    {
        d= -1;
        return NULL;
    }
    FHeapNode<T> *temp=s;
    FHeapNode<T> *mins=s;
    int maxdgree=0;
    
    do{
        if(mins->value>temp->value)
            mins=temp;
            if(maxdgree<temp->degree)
                maxdgree=temp->degree;
                //cout<<"temp:"<<temp->value<<" ";
                temp=temp->next;
                }while(temp!=s);
    
    d=maxdgree;
    //cout<<"Now the minimun is"<<mins->value<<endl;
    return mins;
};

template <class T>
int FHeap<T>::addchild(FHeapNode<T> *p, FHeapNode<T> *c)
{
    p->degree++;
    c->next->pre=c->pre;
    c->pre->next=c->next;
    c->parent=p;
    if(!p->child)
    {
        p->child=c;
        c->next=c;
        c->pre=c;
    }
    
    else{
        FHeapNode<T> *t1=p->child->next;
        p->child->next=c;
        c->next=t1;
        t1->pre=c;
        c->pre=p->child;
    }
    //cout<<c->value<<" is the child of "<<c->parent->value<<endl;
    return 1;
};

template <class T>
FHeapNode<T>* FHeap<T>::removemin()
{
    FHeapNode <T> *old=min;
    if(min==NULL)
        return NULL;
    else if(min->child==NULL&&min->next==min)
        { min=NULL; return old;}
    
    int MaxDegree;
    
    if(min->child==NULL)
    {
        min->pre->next=min->next;
        min->next->pre=min->pre;
        min=min->next;
    }
    else
    {
        FHeapNode<T> *c=min->child;
        FHeapNode<T> *pos=min->child;
        do
        {
            pos->parent=NULL;
            pos->childcut=false;
            pos=pos->next;
        }while(pos!=c);
        
        if(min->next==min) min=c;
        else{
            min->pre->next=min->next;
            min->next->pre=min->pre;
            min=min->next;
            min=merge(min,c);
            
        }
    }
    
    //cout<<"paircomb(min);combine top level heaps...."<<endl;
    
    FHeapNode<T> *pos=min;
    FHeapNode <T> * degreecount[5000];
    for(int i=0;i<5000;i++)
        degreecount[i]=NULL;
    
    FHeapNode<T> *x;
    FHeapNode<T> *lastPos=pos;
    while(1)
    {
        if(degreecount[pos->degree]==NULL||degreecount[pos->degree]==pos)
        {   degreecount[pos->degree]=pos;
            pos=pos->next;
            if(lastPos==pos)
                break;
        }
        else
        {
            x=degreecount[pos->degree];
            degreecount[pos->degree]=NULL;
            if(x->value>pos->value)
            {
                addchild(pos,x);
                lastPos=pos;
            }
            
            else{
                addchild(x,pos);
                pos=x;
                lastPos=pos;
                }
            continue;
            
        }
    }
    
    min=findminroot(pos,MaxDegree);
    return old;
};

template <class T>
void FHeap<T>::cut(FHeapNode<T> *p, FHeapNode<T> *c)
{
    if(p->child==c)
    {   if(c->next==c) p->child=NULL;
        else p->child=c->next;
    }
    c->pre->next=c->next;
    c->next->pre=c->pre;
    c->parent=NULL;
    p->degree--;
    c->childcut=false;
    c->next=c;
    c->pre=c;
    //cout<<c->value<<" is cut from "<<p->value<<endl;
    //add the node to top level chain
    min=merge(min,c);
};

template <class T>
void FHeap<T>::DecreaseKey(FHeapNode<T> *point, T nValue,int sou,int des)
{
    if(point==NULL) return;
    FHeapNode<T>* pp=point->parent;
    FHeapNode<T>* p=point;
    if(point->value>nValue)
    {
        point->value=nValue;
        point->source=sou;
        point->destiny=des;
        if(pp&&pp->value>nValue){
            cut(pp,p);
            p=pp;
            pp=pp->parent;
            while(pp&&p->childcut)
                {
                    cut(pp,p);
                    p=pp;
                    pp=pp->parent;
                }
                if(!p->childcut)
                    p->childcut=true;
                
            }
        
    }
    if(min->value>nValue)
        min=point;
};



template <class T>
FHeapNode<T> * FHeap<T>::findbyD(FHeapNode<T> *heap,int val)
{
    FHeapNode<T>* n=heap;
    if(n==NULL)return NULL;
    do {
        if(n->destiny==val)return n;
            FHeapNode<T>* result=findbyD(n->child,val);
            if(result)return result;
            //cout<<"jkjij"<<n->value<<endl;
            n=n->next;
            
            }while(n!=heap);
            return NULL;
};

#endif
