#include <stdio.h>
#include <stdlib.h>
#define RED 1 //Defining Red by 1 and Black by 0.
#define BLACK 0
int total = 0; // Total no. of nodes in the tree
// structure for red black tree
struct tree
{
    int color;          //stores color of node
    int key;            //stores key value of node
    int freq;           //stores frequency of value entered in case of repetitions
    struct tree *left;  //points to left child of node
    struct tree *right; //points to right child
    struct tree *p;     //points to the parent of the node
};
//sentinel node NIL to avoid extra space
struct tree *NIL = NULL;
// create a new node
struct tree *newNode(int val)
{
    struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
    temp->key = val;
    temp->left = NIL;
    temp->right = NIL;
    temp->p = NIL;
    temp->color = RED;
    temp->freq = 0;
    return temp;
}
//Left rotation
struct tree *left_rotate(struct tree *root, struct tree *x)
{
    if (x != NIL)
    {
        struct tree *y;
        y = x->right;
        x->right = y->left;
        if (y->left != NIL)
        {
            y->left->p = x;
        }
        y->p = x->p;
        if (x->p == NIL)
        {
            root = y;
        }
        else if (x == x->p->left)
        {
            x->p->left = y;
        }
        else
        {
            x->p->right = y;
        }
        y->left = x;
        x->p = y;
    }
    return root;
}
//Right rotation
struct tree *right_rotate(struct tree *root, struct tree *x)
{
    if (x != NIL)
    {
        struct tree *y;
        y = x->left;
        x->left = y->right;
        if (y->right != NIL)
        {
            y->right->p = x;
        }
        y->p = x->p;
        if (x->p == NIL)
        {
            root = y;
        }
        else if (x == x->p->left)
        {
            x->p->left = y;
        }
        else
        {
            x->p->right = y;
        }
        y->right = x;
        x->p = y;
    }
    return root;
}
//function for balancing tree after insertion by required recoloring and rotations
struct tree *insert_fixup(struct tree *root, struct tree *z)
{
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            struct tree *y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if (z == z->p->right)
            {
                z = z->p;
                root = left_rotate(root, z);
            }
            if (z->p != NIL && z->p->p != NIL)
            {
                z->p->color = BLACK;
                z->p->p->color = RED;
                root = right_rotate(root, z->p->p);
            }
        }
        else
        {
            struct tree *y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if (z == z->p->left)
            {
                z = z->p;
                root = right_rotate(root, z);
            }
            if (z->p != NIL && z->p->p != NIL)
            {
                z->p->color = BLACK;
                z->p->p->color = RED;
                root = left_rotate(root, z->p->p);
            }
        }
    }
    root->color = BLACK;
    return root;
}
//insert element in the tree following BST properties
struct tree *insert(struct tree *root, int key)
{
    if (root == NULL)
    {
        return newNode(key);
    }
    else
    {
        struct tree *y = NIL;
        struct tree *x = root;
        struct tree *z = newNode(key);
        while (x != NIL)
        {
            y = x;
            if (key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->p = y;
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        root = insert_fixup(root, z);
        return root;
    }
}
//function for finding minimum valued element in the given subtree
struct tree *minimum(struct tree *start)
{
    struct tree *temp = start;
    while (temp->left != NIL)
    {
        temp = temp->left;
    }
    return temp;
}
//function for joining tree after deleting an element
struct tree *Transplant(struct tree *root, struct tree *u, struct tree *v)
{
    if (u->p == NIL)
    {
        root = v;
    }
    else if (u == u->p->left)
    {
        u->p->left = v;
    }
    else
    {
        u->p->right = v;
    }
    v->p = u->p;
    return root;
}
// balancing tree by recoloring and rotations after deleting an elememt
struct tree *delete_fixup(struct tree *root, struct tree *x)
{
    struct tree *w;
    while (x != root && x->color == BLACK)
    {
        if (x == x->p->left)
        {
            w = x->p->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                root = left_rotate(root, x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
                if (x == root && x->left == NIL)
                {
                    root = x;
                    return root;
                }
            }
            else if (w->right->color == BLACK)
            {
                w->left->color = BLACK;
                w->color = RED;
                root = right_rotate(root, w);
                w = x->p->right;
            }
            w->color = x->p->color;
            x->p->color = BLACK;
            w->right->color = BLACK;
            root = left_rotate(root, x->p);
            x = root;
        }
        else
        {
            w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                root = right_rotate(root, x->p);
                w = x->p->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->p;
                if (x == root && x->right == NIL)
                {
                    root = x;
                    return root;
                }
            }
            else if (w->left->color == BLACK)
            {
                w->right->color = BLACK;
                w->color = RED;
                root = left_rotate(root, w);
                w = x->p->left;
            }
            w->color = x->p->color;
            x->p->color = BLACK;
            w->left->color = BLACK;
            root = right_rotate(root, x->p);
            x = root;
        }
    }
    x->color = BLACK;
    return root;
}
//deleting an element
struct tree *delete (struct tree *root, struct tree *z)
{
    if (total == 1 && root == z)
    {
        free(z);
        return NULL;
    }
    struct tree *y = z;
    struct tree *x;
    int original = y->color;
    if (z->left == NIL)
    {
        x = z->right;
        root = Transplant(root, z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        root = Transplant(root, z, z->left);
    }
    else
    {
        y = minimum(z->right);
        original = y->color;
        x = y->right;
        if (y->p == z)
        {
            x->p = y;
        }
        else
        {
            root = Transplant(root, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        root = Transplant(root, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (original == BLACK)
    {
        root = delete_fixup(root, x);
    }
    free(z);
    return root;
}
//displaying elements and their colors
void display(struct tree *root)
{
    if (root == NULL)
    {
        printf("Tree Empty\n");
    }
    else
    {
        struct tree *temp = root;
        if (temp != NIL)
        {
            display(temp->left);
            printf("%d\t", temp->key);
            printf("%d\t", temp->freq);
            if (temp->p == NIL)
            {
                printf("NIL\t");
            }
            else
            {
                printf("%d\t", temp->p->key);
            }
            if (temp->color == BLACK)
            {
                printf("Black\n");
            }
            else
            {
                printf("Red\n");
            }
            display(temp->right);
        }
    }
}
//search function
struct tree *search(struct tree *root, int val)
{
    if (root == NULL || root->key == val)
        return root;

    if (root->key < val)
        return search(root->right, val);

    return search(root->left, val);
}
//function to find black height of node wanted by the user.
int black_height(struct tree *root, int val)
{
    struct tree *z = search(root, val);
    if (z)
    {
        struct tree *temp = root;
        int bh = 0;
        while (temp != z)
        {
            if (val < temp->key)
            {
                if (temp->color == BLACK)
                    bh++;
                temp = temp->left;
            }
            else
            {
                if (temp->color == BLACK)
                    bh++;
                temp = temp->right;
            }
        }
        return bh;
    }
    return -1;
}
int main()
{
    NIL = (struct tree *)malloc(sizeof(struct tree));
    NIL->color = BLACK;
    NIL->p = NULL;
    NIL->right = NULL;
    NIL->left = NULL;
    struct tree *root = NULL;
    char c;
    printf("Enter I for insert, D for delete, S for search, V for view, M to find minimum, B to know black height, E for exit: ");
    scanf(" %c", &c);
    while (c != 'E')
    {
        switch (c)
        {
        case 'I':
            printf("Enter number of terms: ");
            int n, val;
            scanf("%d", &n);
            printf("Enter value to insert\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &val);
                if (total == 0 || search(root, val) == root)
                {
                    if (!search(root, val))
                    {
                        root = insert(root, val);
                        root->color = BLACK;
                        total++;
                        root->freq++;
                    }
                    else
                    {
                        root->freq++;
                    }
                }
                else
                {
                    if (search(root, val))
                    {
                        struct tree *t = search(root, val);
                        t->freq++;
                    }
                    else
                    {
                        root = insert(root, val);
                        total++;
                        search(root, val)->freq++;
                    }
                }
            }
            break;
        case 'D':
            printf("Enter element to be deleted: ");
            int del;
            scanf("%d", &del);
            if (search(root, del))
            {
                root = delete (root, search(root, del));
            }
            else
            {
                printf("Element not found.\n");
                break;
            }
            NIL->color = BLACK;
            NIL->p = NULL;
            NIL->right = NULL;
            NIL->left = NULL;
            total--;
            printf("Element deleted\n");
            break;
        case 'V':
            if (root == NULL)
            {
                printf("Tree Empty\n");
                printf("Total elements : %d\n", total);
            }
            else
            {
                printf("Root : %d\n", root->key);
                printf("Total elements : %d\n", total);
                printf("Value Frequency Parent Color\n");
                display(root);
            }
            break;
        case 'S':
            printf("Enter element to be searched: ");
            int s;
            scanf("%d", &s);
            struct tree *t = search(root, s);
            if (t)
            {
                printf("Found\n");
                printf("Value Frequency Parent Color\n");
                printf("%d\t", t->key);
                printf("%d\t", t->freq);
                if (t->p == NIL)
                {
                    printf("NIL\t");
                }
                else
                {
                    printf("%d\t", t->p->key);
                }
                if (t->color == BLACK)
                {
                    printf("Black\n");
                }
                else
                {
                    printf("Red\n");
                }
            }
            else
            {
                printf("Not Found\n");
            }
            break;
        case 'M':
            if (root == NULL)
            {
                printf("Tree Empty\n");
            }
            else
            {
                printf("Minimum Value found is: %d\n", minimum(root)->key);
            }
            break;
        case 'B':
            printf("Enter value of key whose black height is to be determined: ");
            int a;
            scanf("%d", &a);
            int bh = black_height(root, a);
            if (bh != -1)
            {
                printf("Black height of %d is : %d\n", a, bh);
            }
            else
            {
                printf("Element not found\n");
            }
            break;
        case 'E':
            return -1;
            break;
        default:
            printf("Invalid Input.\n");
        }
        printf("Enter I for insert, D for delete, S for search, V for view, M to find minimum, B to know black height, E for exit: ");
        scanf(" %c", &c);
    }
    return 0;
}