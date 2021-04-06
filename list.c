#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

// intialization of list
void init(list *l){
    l->front=NULL;
    l->end=NULL;
    return;
}

// to create newnode
node *newNode(char *fileName){
    node *temp=(node *)malloc(sizeof(node));
    if(!temp){
        return NULL;
    }
    temp->fileName=(char *)malloc(sizeof(fileName));
    strcpy(temp->fileName,fileName);
    temp->next=NULL;
    return temp;
}
// insert  function to add filename in the list 
void insert(list *l,char *fileName){
    if(l->front==NULL){
        l->front=newNode(fileName);
        l->end=l->front;
        return;
    }
    node *last=l->end;
    last->next=newNode(fileName);
    l->end=last->next;
    return;
}

// pop function to get filename from list
char *pop(list *l){
    char *file=(char *)malloc(sizeof(char)*100);
    node *temp=l->front;
    l->front=temp->next;
    strcpy(file,temp->fileName);
    free(temp->fileName);
    free(temp);
    return file;
}

// isempty function to check whether list is empty or not
int isempty(list *l){
    if(l->front==NULL){
        return 1;
    }
    return 0;
}