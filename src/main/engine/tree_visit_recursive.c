#include "object_links.h"

/* GCC_VERSION: 2.6.3 */

extern s32 func_8001CDD0(Node *, s32);
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
