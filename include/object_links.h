#ifndef CRASH_OBJECT_LINKS_H
#define CRASH_OBJECT_LINKS_H

#include "common.h"
typedef struct Node {
    s32 kind;
    struct Node *word04;
    u8 pad08[0x5C];
    struct Node *parent;
    struct Node *next;
    struct Node *children;
} Node;
typedef s32 (*Visitor)(Node *, void *);
typedef s32 (*Traversal)(Node *, Visitor, void *);

s32 Gool_ObjectHandleTraverseTreePostorder();
void Gool_ForEachObjectHandle(Traversal traversal, Visitor visitor, void *context);
s32 Gool_ObjectTerminate();

#endif
