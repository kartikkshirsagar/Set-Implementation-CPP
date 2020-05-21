#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define MAX 101


typedef struct hash_elem{
    bool empty;
    list<string> elist;
}elem;

typedef struct set_type{
    int size;
    elem hash[MAX];
}myset;



int hashFunction(string data){
    int len=data.length();
    int hashvalue=0;
    for (int i = 0; i < len; i++)
    {
        int asc=data[i]-'0';
        hashvalue+=asc*asc;
    }
    hashvalue=hashvalue%101;
    return hashvalue;
    
}

void AddinSet(string data,myset* set){
    int hashindex=hashFunction(data);
    int flag=0;
    if(set->hash[hashindex].empty==false)
    {
        for(auto it=set->hash[hashindex].elist.begin();it!=set->hash[hashindex].elist.end();it++)
        {
            if(data.compare(*it)==0)
            {
                flag=1;
            }
        }
        if(flag==0)
        {
            set->hash[hashindex].elist.push_back(data);
            set->size++;
        }
    }
    else
    {
        set->hash[hashindex].empty=false;
        set->hash[hashindex].elist.push_back(data);
        set->size++;
    }
      
}
bool isElementof(string data,myset* set);

void RemoveSet(string data,myset* set)
{
    if(set->size==0)
    {
        cout<<"Set already empty!\n";
        return;
    }
    int hashindex=hashFunction(data);
    if(set->hash[hashindex].empty==false)
    {
        if(isElementof(data,set))
        {
            set->hash[hashindex].elist.remove(data);
            set->size--;
        }
    }

}

int Size(myset* set)
{
    return set->size;
}

bool isEmpty(myset* set)
{
    bool retval=false;
    if(Size(set)==0)
    {
        retval=true;
    }
    return retval;
}

list<string> enumerate(myset* set)
{
    list<string> ret;
    for(int i=0;i<MAX;i++)
    {
        if(set->hash[i].elist.size()>0)
        {
            for(auto it=set->hash[i].elist.begin();it!=set->hash[i].elist.end();it++)
            {
                ret.push_back(*it);
            }
        }
    }
    return ret;
}

bool isElementof(string data,myset* set)
{
    int hashval=hashFunction(data);
    bool retval=false;
    if(set->hash[hashval].elist.size()>0)
    {
        for(auto it=set->hash[hashval].elist.begin();it!=set->hash[hashval].elist.end();it++)
        {
            if(data.compare(*it)==0)
            {
                retval=true;
            }
        }
    }
    return retval;
}

myset CreateSet()
{
    myset ret;
    ret.size=0;
    for(int i=0;i<MAX;i++)
    {
        ret.hash[i].empty=true;
    }
    return ret;
}


myset Union(myset* set1,myset* set2)
{
    myset result=CreateSet();
    for(int i=0;i<MAX;i++)
    {
        for(auto it=set1->hash[i].elist.begin();it!=set1->hash[i].elist.end();it++)
        {
            AddinSet(*it,&result);
        }
        for(auto it=set2->hash[i].elist.begin();it!=set2->hash[i].elist.end();it++)
        {
            AddinSet(*it,&result);
        }
    }
    return result;

}


myset Intersection(myset* set1,myset* set2)
{
    myset result=CreateSet();
    for(int i=0;i<MAX;i++)
    {
        for(auto it=set1->hash[i].elist.begin();it!=set1->hash[i].elist.end();it++)
        {
            if(isElementof(*it,set2))
            {
                AddinSet(*it,&result);
            }
        }
    }
    return result;
}

myset Difference(myset* set1,myset* set2)//set1-set2
{
    myset result=CreateSet();
    for(int i=0;i<MAX;i++)
    {
        for(auto it=set1->hash[i].elist.begin();it!=set1->hash[i].elist.end();it++)
        {
            if(!isElementof(*it,set2))
            {
                AddinSet(*it,&result);
            }
        }
    }
    return result;
}


myset buildSet(vector<string> elems)
{
    myset result=CreateSet();
    for(int i=0;i<elems.size();i++)
    {
        AddinSet(elems[i],&result);
    }
    return result;
}

bool isSubset(myset* set1,myset* set2) //if set1 is subset of set2
{
    bool retval=false;
    int flag=0;
    for(int i=0;i<MAX;i++)
    {
        for(auto it=set1->hash[i].elist.begin();it!=set1->hash[i].elist.end();it++)
        {
            if(!isElementof(*it,set2))
            {
                flag=1;
            }
        }
    }
    if(flag==0)
    {
        retval=true;
    }
    return retval;
    
}

int main()
{
    myset set=CreateSet();
    myset set1=CreateSet();
    AddinSet("kartik",&set);
    //AddinSet("pranav",&set1);
    AddinSet("kartik",&set1);
    AddinSet("pep",&set);
    myset result=Difference(&set,&set1);
    bool res=isSubset(&set1,&set);
    myset newset = CreateSet();
    cout<<"";

}