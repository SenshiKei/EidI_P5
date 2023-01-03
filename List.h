//
// Created by belah on 29.12.2022.
//

#ifndef EIDI_P5_LIST_H
#define EIDI_P5_LIST_H

struct Node2D
{
    struct Node2D* before;
    struct Node2D* after;
    int value;
};

struct List2D
{
    struct Node2D* first;
    struct Node2D* last;
    int length;
};

void List2D_Append(struct List2D*, struct Node2D*);

void List2D_Prepend(struct List2D*, struct Node2D*);

void List2D_Pop(struct List2D*, struct Node2D*);

void List2D_InsertBefore(struct List2D*, struct Node2D*, int);

void List2D_InsertAfter(struct List2D*, struct Node2D*, int);

int List2D_Length(struct List2D*);

void List2D_Clear(struct List2D*);

struct List2D* List2D_New();

struct Node2D* List2D_Search(struct List2D*, int);

struct Node2D *Node2D_New(int value);

#endif //EIDI_P5_LIST_H
