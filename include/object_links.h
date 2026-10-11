#ifndef CRASH_OBJECT_LINKS_H
#define CRASH_OBJECT_LINKS_H

#include "common.h"
typedef struct Node {
    s32 kind;
    struct Node *word04;
    u8 pad08[0x60];
    struct Node *next;
    struct Node *children;
} Node;
typedef s32 (*Visitor)(Node *, void *);
typedef s32 (*Traversal)(Node *, Visitor, void *);

s32 func_8001B92C(Node *root, Visitor visitor, void *context);
void func_8001BA18(Traversal traversal, Visitor visitor, void *context);
s32 func_8001D1E0(Node *object, void *context);

#endif
