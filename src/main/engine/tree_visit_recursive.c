#include "object_links.h"

/* GCC_VERSION: 2.6.3 */

extern s32 func_8001CDD0(Node *, s32);

#define NODE_CHILDREN(n) ((n)->kind == 2 ? (n)->word04 : (n)->children)
#define NODE_CHILDREN_PTR(n) ((n)->kind == 2 ? &(n)->word04 : &(n)->children)

s32 func_8001B56C(Node *node, Node *new_parent)
{
    Node *parent = node->parent;
    Node *prev;

    if (parent != NULL) {
        prev = NODE_CHILDREN(parent);
        if (prev == node) {
            *NODE_CHILDREN_PTR(parent) = node->next;
        } else if (prev != NULL) {
            while (prev->next != node) {
                if (prev == NULL) {
                    return -0x18;
                }
                prev = prev->next;
                if (prev == NULL) {
                    return -0x18;
                }
            }
            prev->next = node->next;
        } else {
            return -0x18;
        }
    }
    node->parent = new_parent;
    node->next = NODE_CHILDREN(new_parent);
    *NODE_CHILDREN_PTR(new_parent) = node;
}

s32 GOOL_TraverseObjectTreePostorder(Node *root, Visitor visitor, void *context)
{
    Node *child, *next;
    s32 result = visitor(root, context);
    if(result == -25) {
        func_8001CDD0(root, 0);
        return -25;
    }
    child = root->children;
    while(child != NULL && child->kind != 0) {
        next = child->next;
        GOOL_TraverseObjectTreePostorder(child, visitor, context);
        child = next;
    }
    return result;
}
