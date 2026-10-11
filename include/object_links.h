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

#endif
