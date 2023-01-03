//
// Created by belah on 29.12.2022.
//
#include <stdlib.h>
#include <stdio.h>

#include "List.h"
#include "config_util.h"

void List2D_Append(struct List2D* list, struct Node2D* newNode)
{
    if ( list == NULL || newNode == NULL) exit_with_output("NPR - app");

    if (list->last == NULL || list->length == 0)
    {
        list->first = newNode;
        list->last = newNode;
        list->length = 1;
    }
    else
    {
        list->last->after = newNode;
        newNode->before = list->last;
        list->last = newNode;
    }

    list->length += 1;
}

void List2D_Prepend(struct List2D* list, struct Node2D* newNode)
{
    if ( list == NULL || newNode == NULL) exit_with_output("NPR - pre");

    struct Node2D *first = list->first;
    list->first = newNode;
    newNode->after = first;

    if (first == NULL)
    {
        list->last = newNode;
    }
    else
    {
        first->before = newNode;
    }

    list->length += 1;
}

void List2D_Pop(struct List2D* list, struct Node2D* node)
{
    if ( list == NULL || node == NULL) exit_with_output("NPR - pop");

    if (list->first == node)
        list->first = node->after;
    else
    {
        if (node->before != NULL) node->before->after = node->after;

        if (node->after != NULL) node->after->before = node->before;
    }

    list->length -= 1;
}

void List2D_InsertBefore(struct List2D* list, struct Node2D* node, int value)
{
    if ( list == NULL || node == NULL) exit_with_output("NPR - insBef");

    if (node ==  NULL)
        List2D_Append(list, Node2D_New(value));
    else
    {
        struct Node2D *newNode = Node2D_New(1);

        newNode->before = node->before;
        newNode->after = node;
        node->before = &newNode;

        if (newNode->before != NULL) newNode->before->after = newNode;
    }
    list->length += 1;
}

void List2D_InsertAfter(struct List2D* list, struct Node2D* node, int value)
{
    if ( list == NULL) exit_with_output("NPR - insAft");

    if (node == NULL) List2D_Append(list, Node2D_New(value));

    struct Node2D *newNode = Node2D_New(value);

    newNode->after = node->after;
    node->after = newNode;

    list->length += 1;
}

int List2D_Length(struct List2D* list)
{
    return list->length;
}

void List2D_Clear(struct List2D* list)
{
    if(list->first == NULL || list->last == NULL) return;
    struct Node2D *currentNode = list->first;
    struct Node2D *nextNode = list->first->after;
    for (int i = 0; i < list->length; ++i)
    {
        free(currentNode);
        currentNode = nextNode;
        nextNode = currentNode->after;
    }
    free(list);
}

void List2D_Remove(struct List2D* list, int i)
{
    struct Node2D* node = List2D_Search(list, i);
    List2D_Pop(list, node);
}

struct List2D* List2D_New()
{
    struct List2D *newList = malloc(sizeof(struct List2D));

    if (newList == NULL) exit_with_output("Malloc");

    newList->first = NULL;
    newList->last = NULL;
    newList->length = 0;

    return newList;
}

struct Node2D* List2D_Search(struct List2D* list, int value)
{
    if ( list == NULL) return NULL;

    struct Node2D *currentNode = list->first;
    while (currentNode != NULL)
    {
        if (currentNode->value == value) return currentNode;
        currentNode = currentNode->after;
    }
    return NULL;
}

struct Node2D *Node2D_New(int value)
{
    struct Node2D *newNode = malloc(sizeof(struct Node2D));

    if (newNode == NULL) exit_with_output("Malloc");

    newNode->after = NULL;
    newNode->before = NULL;
    newNode->value = value;

    return newNode;
}
