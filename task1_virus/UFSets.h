//
// Created by Gong chen on 2022/4/12.
//

#ifndef TASK1_VIRUS_UFSETS_H
#define TASK1_VIRUS_UFSETS_H
#include "Assistance.h"

template <class ElemType>
struct ElemNode
{

    ElemType data;
    int parent;
};



template <class ElemType>
class UFSets
{
protected:

    ElemNode<ElemType> *sets;
    int size;

public:

    UFSets(ElemType es[], int n);
    virtual ~UFSets();
    ElemType GetElem(int p)const;
    int GetOrder(ElemType e)const;
    void Union(ElemType a, ElemType b);
    void WeightedUnion(ElemType a, ElemType b);
    bool Differ(ElemType a, ElemType b);
    UFSets(const UFSets &copy);
    UFSets &operator =(const UFSets &copy);
    int Find(ElemType e) const;
    int CollapsingFind(ElemType e) const;
    int nodesnum();
};



template <class ElemType>
UFSets<ElemType>::UFSets(ElemType es[], int n)

{
    size = n;
    sets = new ElemNode<ElemType>[size];
    for (int i = 0; i < size; i++) {
        sets[i].data = es[i];
        sets[i].parent = -1;
    }
}

template <class ElemType>
int UFSets<ElemType>::Find(ElemType e) const
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        return -1;
    while (sets[p].parent > -1)
        p = sets[p].parent;
    return p;
}

template <class ElemType>
int UFSets<ElemType>::CollapsingFind(ElemType e) const
{
    int i, k, p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        return -1;
    for(i = p ; sets[i].parent >= 0; i= sets[i].parent) ;
    while ( i!= sets[p].parent ) {
        k = sets[p].parent ;
        sets[p].parent = i;
        p = k;
    }
    return i;
}


template <class ElemType>
UFSets<ElemType>::~UFSets()
{
    delete []sets;
}

template <class ElemType>
ElemType UFSets<ElemType>::GetElem(int p) const
{
    if (p < 0 || p >= size)
        throw Error("元素不存在!");
    return sets[p].data;
}

template <class ElemType>
int UFSets<ElemType>::GetOrder(ElemType e) const
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        return -1;
    return p;
}

template <class ElemType>
void UFSets<ElemType>::Union(ElemType a, ElemType b)
{
    int r1 = Find(a);
    int r2 = Find(b);
    if (r1 != r2 && r1 != -1) {
        sets[r1].parent += sets[r2].parent;
        sets[r2].parent = r1;
    }
}

template <class ElemType>
void UFSets<ElemType>::WeightedUnion(ElemType a, ElemType b)
{
    int r1 = Find(a);
    int r2 = Find(b);
    if (r1 != r2 && r1 != -1) {
        int  temp = sets[r1].parent + sets[r2].parent;
        if (sets[r1].parent <= sets[r2].parent ) {
            sets[r2].parent = r1;
            sets[r1].parent = temp;
        }
        else {
            sets[r1].parent = r2;
            sets[r2].parent = temp;
        }
    }
}

template <class ElemType>
bool UFSets<ElemType>::Differ(ElemType a, ElemType b)
{
    int r1 = Find(a);
    int r2 = Find(b);
    return r1 != r2;
}

template <class ElemType>
UFSets<ElemType>::UFSets(const UFSets &copy)
{
    size = copy.size;
    sets = new ElemNode<ElemType>[size];
    for (int i = 0; i < size; i++)
        sets[i] = copy.sets[i];
}

template <class ElemType>
UFSets<ElemType> &UFSets<ElemType>::operator=(const UFSets<ElemType> &copy)
{
    if (&copy != this)	{
        size = copy.size;
        delete []sets;
        sets = new ElemNode<ElemType>[size];
        for (int i = 0; i < size; i++)
            sets[i] = copy.sets[i];
    }
    return *this;
}

template<class ElemType>
int UFSets<ElemType>::nodesnum() {
    int num=0;
    for(int i=0;i<size;i++){
        if(sets[i].parent<0)
            num++;
    }
    return num;
}

#endif //TASK1_VIRUS_UFSETS_H
