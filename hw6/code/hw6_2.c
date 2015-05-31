#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "bst.h"
#include "rb.h"

struct word 
{
    char s[130];
    int length;
};

void ReadWord(struct word *element)
{
    fgets(element->s, 129, stdin);
    int found = 0;
    for (int count = 0; count < 129 && !found; count++)
    {
        if (element->s[count] == '\n')
        {
            element->s[count] = '\0';
            element->length = count;
            found = 1;
        }
    }
}

void preorder_avl(const struct avl_node *node)
{
    if (node == NULL)
        return;
    printf("%s ", ((struct word *)node->avl_data)->s);
    if (node->avl_link[0] != NULL || node->avl_link[1] != NULL)
    {
        putchar('(');
        preorder_avl(node->avl_link[0]);
        putchar(',');
        putchar(' ');
        preorder_avl(node->avl_link[1]);
        putchar(')');
    }
}

void preorder_bst(const struct bst_node *node)
{
    if (node == NULL)
        return;
    printf("%s ", ((struct word *)node->bst_data)->s);
    if (node->bst_link[0] != NULL || node->bst_link[1] != NULL)
    {
        putchar('(');
        preorder_bst(node->bst_link[0]);
        putchar(',');
        putchar(' ');
        preorder_bst(node->bst_link[1]);
        putchar(')');
    }
}

void preorder_rb(const struct rb_node *node)
{
    if (node == NULL)
        return;
    printf("%s ", ((struct word *)node->rb_data)->s);
    if (node->rb_link[0] != NULL || node->rb_link[1] != NULL)
    {
        putchar('(');
        preorder_rb(node->rb_link[0]);
        putchar(',');
        putchar(' ');
        preorder_rb(node->rb_link[1]);
        putchar(')');
    }
}

int Compare_by_lexicographical_order(const void *pa, const void *pb, void *param)
{
    const struct word *a = (const struct word *)pa;
    const struct word *b = (const struct word *)pb;

    return strcmp(a->s, b->s);
}

int main() 
{
    struct avl_table *avltree;
    struct bst_table *bsttree;
    struct rb_table *rbtree;

    avltree = avl_create(Compare_by_lexicographical_order, NULL, NULL);
    bsttree = bst_create(Compare_by_lexicographical_order, NULL, NULL);
    rbtree = rb_create(Compare_by_lexicographical_order, NULL, NULL);

    for (int i = 0; i < 32; i++)
    {
        struct word *element = 
            (struct word *)malloc(sizeof(struct word));

        ReadWord(element);

#ifdef DEBUG
        printf("Read in word: %s, length = %d\n", element->s, element->length);
#endif

        avl_probe(avltree, element);
        bst_probe(bsttree, element);
        rb_probe(rbtree, element);
    }

    preorder_avl(avltree->avl_root); puts("");
    preorder_bst(bsttree->bst_root); puts("");
    preorder_rb(rbtree->rb_root); puts("");
    return 0;
}
