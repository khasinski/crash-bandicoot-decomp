#include "object_links.h"

/* GCC_VERSION: 2.6.3 */

extern s32 func_8001B6F0(Node *, Visitor, void *);
extern s32 func_8001CDD0(Node *, s32);
s32 func_8001B6F0(Node *root, Visitor visitor, void *context)
{
    Node *child = root->children;
    Node *next;
    if(child != NULL) {
        do {
            next = child->next;
            if(func_8001B6F0(child, visitor, context) == -25)
                func_8001CDD0(root, 0);
            child = next;
        } while(child != NULL);
    }
    return visitor(root, context);
}
