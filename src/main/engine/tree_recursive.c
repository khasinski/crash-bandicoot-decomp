#include "object_links.h"

/* GCC_VERSION: 2.6.3 */

s32 GOOL_TraverseObjectTreePostorder(Node *, Visitor, void *);
s32 func_8001B788(Node *, Visitor, void *);
s32 func_8001CDD0(Node *, s32);
s32 GOOL_TraverseObjectTreePostorder(Node *root, Visitor visitor, void *context)
{
    Node *child = root->children;
    Node *next;
    if(child != NULL) {
        do {
            next = child->next;
            if(GOOL_TraverseObjectTreePostorder(child, visitor, context) == -25)
                func_8001CDD0(root, 0);
            child = next;
        } while(child != NULL);
    }
    return visitor(root, context);
}

s32 func_8001B788(Node *root, Visitor visitor, void *context)
{
    Node *child;
    Node *next;
    s32 result = 0;

    if (root == NULL) {
        return 0;
    }
    if (root->kind != 2) {
        result = visitor(root, context);
        if (result != 0) {
            return result;
        }
    }
    if (root->kind == 2) {
        child = root->word04;
    } else {
        child = root->children;
    }
    while (child != NULL && result == 0) {
        next = child->next;
        result = func_8001B788(child, visitor, context);
        child = next;
    }
    return result;
}
