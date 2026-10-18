#include "object_links.h"

/* GCC_VERSION: 2.6.3 */

/* Partial linked-object layout; word04 is used when kind is two. */

s32 GOOL_TraverseObjectTreePostorder(Node *, Visitor, void *);
s32 func_8001CDD0(Node *, s32);
s32 func_8001B92C(Node *root, Visitor visitor, void *context)
{
    Node *node, *next, *child, *next_child;
    if(root->kind == 2) node = root->word04;
    else node = root->children;
    if(node != NULL) {
        do {
            child = node->children;
            next = node->next;
            if(child != NULL) {
                do {
                    next_child = child->next;
                    if(GOOL_TraverseObjectTreePostorder(child, visitor, context) == -25)
                        func_8001CDD0(node, 0);
                    child = next_child;
                } while(child != NULL);
            }
            if(visitor(node, context) == -25)
                func_8001CDD0(root, 0);
            node = next;
        } while(node != NULL);
    }
    return -255;
}
