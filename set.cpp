#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define MAX 101



typedef struct Node{
    string data;
    struct Node* next;
}Node;

typedef struct hash_elem{
    bool empty;
    Node *elist;
}elem;

typedef struct set_type{
    int size;
    elem hash[MAX];
}myset;





int listSize(Node* lptr)
{
    Node* ptr=lptr;
    int count=1;
    while(ptr!=NULL)
    {
        count++;
        ptr=ptr->next;
    }
    return count;
}

Node* makeNode(string data)
{
    Node* nptr=(Node*)malloc(sizeof(Node));
    nptr->data=data;
    nptr->next=NULL;
    return nptr;
}

void push_back(Node** lptr,string data)
{
    Node* nptr=makeNode(data);
    Node* temp=*lptr;
    if(*lptr==NULL)
    {
        temp=nptr;
        *lptr=nptr;
        return;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=nptr;

}

void removeList(Node* lptr,Node* ptr)
{
    if(lptr==ptr)
    {
        Node* nptr=lptr;
        free(nptr);
        lptr=NULL;
        return;    
    }
    Node* temp=lptr;
    while(temp->next!=ptr)
    {
        temp=temp->next;
    }
    temp->next=ptr->next;
    free(ptr);
}

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
    Node *lptr=set->hash[hashindex].elist;
    if(set->hash[hashindex].empty==false)
    {
        
        Node* temp=lptr;
        while(temp!=NULL)
        {
            if(data.compare(temp->data)==0)
            {
                flag=1;
            }
            temp=temp->next;
        }
        if(flag==0)
        {
            push_back(&lptr,data);
            set->size++;
        }
    }
    else
    {
        set->hash[hashindex].empty=false;
        push_back(&set->hash[hashindex].elist,data);
        set->size++;
    }
      
}

Node* Search(Node* lptr,string data)
{
    Node* temp=lptr;
    while(temp!=NULL)
    {
        if(data.compare(temp->data)==0)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
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
    Node* lptr = set->hash[hashindex].elist;
    if(set->hash[hashindex].empty==false)
    {
        if(isElementof(data,set))
        {
            removeList(lptr,Search(lptr,data));
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

Node* enumerate(myset* set)
{
    Node* ret=NULL;
    for(int i=0;i<MAX;i++)
    {

        Node* lptr=set->hash[i].elist;
        if(listSize(set->hash[i].elist)>0)
        {
            Node* temp=lptr;
            while(temp!=NULL)
            {
                push_back(&ret,temp->data);
                temp=temp->next;
            }
        }
    }
    return ret;
}

bool isElementof(string data,myset* set)
{
    int hashval=hashFunction(data);
    bool retval=false;
    Node* lptr=set->hash[hashval].elist;
    if(listSize(set->hash[hashval].elist)>0)
    {
        Node* temp=lptr;
        while(temp!=NULL)
        {
            if(data.compare(temp->data)==0)
            {
                retval=true;
            }
            temp=temp->next;
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
        ret.hash[i].elist=NULL;
    }
    return ret;
}


myset Union(myset* set1,myset* set2)
{
    myset result=CreateSet();
    for(int i=0;i<MAX;i++)
    {
        Node* lptr1=set1->hash[i].elist;
        Node* temp1=lptr1;
        while(temp1!=NULL)
        {
            AddinSet(temp1->data,&result);
            temp1=temp1->next;
        }
        Node* lptr2=set2->hash[i].elist;
        Node* temp2=lptr2;
        while(temp2!=NULL)
        {
            AddinSet(temp2->data,&result);
            temp2=temp2->next;
        }
        
    }
    return result;

}


myset Intersection(myset* set1,myset* set2)
{
    myset result=CreateSet();
    for(int i=0;i<MAX;i++)
    {

        Node* lptr=set1->hash[i].elist;
        Node* temp=lptr;
        while(temp!=NULL)
        {
            if(isElementof(temp->data,set2))
            {
                AddinSet(temp->data,&result);
            }
            temp=temp->next;
        }
    }
    return result;
}

myset Difference(myset* set1,myset* set2)//set1-set2
{
    myset result=CreateSet();
    
    for(int i=0;i<MAX;i++)
    {
        Node* lptr=set1->hash[i].elist;
        Node* temp=lptr;
        while(temp!=NULL)
        {
            if(!isElementof(temp->data,set2))
            {
                AddinSet(temp->data,&result);
            }
            temp=temp->next;
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
        Node* lptr=set1->hash[i].elist;
        Node* temp=lptr;
        while(temp!=NULL)
        {
            if(!isElementof(temp->data,set2))
            {
                flag=1;
            }
            temp=temp->next;
        }
    }
    if(flag==0)
    {
        retval=true;
    }
    return retval;
    
}


void PrintSet(myset* set)
{
    Node* ptr=enumerate(set);
    Node* temp=ptr;
    cout<<"[";
    while(temp!=NULL)
    {
        cout<<temp->data<<",";
        temp=temp->next;
    }
    cout<<"]\n";

}

int main()
{
    myset set=CreateSet();
    myset set1=CreateSet();
    AddinSet("kartik",&set);
    AddinSet("pranav",&set1);
    AddinSet("kartik",&set1);
    AddinSet("pep",&set);
    PrintSet(&set1);
    PrintSet(&set);
    myset result=Union(&set,&set1);
    bool res=isSubset(&set1,&set);
    PrintSet(&result);
    myset newset = CreateSet();
    cout<<"";

}
