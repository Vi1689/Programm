#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum rbcolor { BLACK = 0, RED = 1 } t_rbcolor;

typedef unsigned int t_key;
typedef unsigned int t_value;

typedef struct s_rbnode {
    t_key key;
    t_value value;
    t_rbcolor color;
    struct s_rbnode* left;
    struct s_rbnode* right;

} t_rbnode;

t_rbnode* erase_tree(t_rbnode* node);
t_rbnode* remove_key(t_rbnode* node, t_key key);
unsigned int get_size(t_rbnode* node, t_key key);
t_value get_key(t_rbnode* node, t_key key);
void insert(t_key key, t_value value);

t_rbnode* root_rbtree = (t_rbnode*)0;

static inline int is_red(t_rbnode* node)
{
    return ((node) ? (node->color == RED) : (0));
}

static inline int my_compare(unsigned int key1, unsigned int key2)
{
    return ((key1 == key2) ? (0) : ((key1 < key2) ? (-1) : (1)));
}

static void flip_color(t_rbnode* node)
{
    node->color = !(node->color);
    node->left->color = !(node->left->color);
    node->right->color = !(node->right->color);
}

static t_rbnode* rotate_left(t_rbnode* left)
{
    t_rbnode* right;

    if (!left)
        return ((t_rbnode*)0);
    right = left->right;
    left->right = right->left;
    right->left = left;
    right->color = left->color;
    left->color = RED;
    return (right);
}

static t_rbnode* rotate_right(t_rbnode* right)
{
    t_rbnode* left;

    if (!right)
        return ((t_rbnode*)0);
    left = right->left;
    right->left = left->right;
    left->right = right;
    left->color = right->color;
    right->color = RED;
    return (left);
}

t_rbnode* create_node(t_key key, t_value value)
{
    t_rbnode* new;

    if ((new = (t_rbnode*)malloc(sizeof(*new))) == (t_rbnode*)0)
        return ((t_rbnode*)0);
    new->key = key;
    new->value = value;
    new->color = RED;
    new->left = (t_rbnode*)0;
    new->right = (t_rbnode*)0;
    return (new);
}

static t_rbnode* insert_this(t_rbnode* node, t_key key, t_value value)
{
    int res;

    if (!node)
        return (create_node(key, value));
    res = my_compare(key, node->key);
    if (res == 0)
        node->value = value;
    else if (res < 0)
        node->left = insert_this(node->left, key, value);
    else
        node->right = insert_this(node->right, key, value);
    if (is_red(node->right) && !is_red(node->left))
        node = rotate_left(node);
    if (is_red(node->left) && is_red(node->left->left))
        node = rotate_right(node);
    if (is_red(node->left) && is_red(node->right))
        flip_color(node);
    return (node);
}

void insert(t_key key, t_value value)
{
    root_rbtree = insert_this(root_rbtree, key, value);
    if (root_rbtree)
        root_rbtree->color = BLACK;
}

t_value get_key(t_rbnode* node, t_key key)
{
    int cmp;

    while (node) {
        if (!(cmp = my_compare(key, node->key)))
            return (node->value);
        node = ((cmp < 0) ? (node->left) : (node->right));
    }
    return (0);
}

static t_rbnode* min(t_rbnode* node)
{
    if (!node)
        return ((t_rbnode*)0);
    while (node->left)
        node = node->left;
    return (node);
}

inline t_rbnode* balance_me_that(t_rbnode* node)
{
    if (is_red(node->right))
        node = rotate_left(node);
    if (is_red(node->left) && is_red(node->left->left))
        node = rotate_right(node);
    if (is_red(node->left) && is_red(node->right))
        flip_color(node);
    return (node);
}

static t_rbnode* move_red_to_left(t_rbnode* node)
{
    flip_color(node);
    if (node && node->right && is_red(node->right->left)) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
        flip_color(node);
    }
    return (node);
}

static t_rbnode* move_red_to_right(t_rbnode* node)
{
    flip_color(node);
    if (node && node->left && is_red(node->left->left)) {
        node = rotate_right(node);
        flip_color(node);
    }
    return (node);
}

static t_rbnode* remove_min(t_rbnode* node)
{
    if (!node)
        return ((t_rbnode*)0);
    if (!node->left) {
        free(node);
        return ((t_rbnode*)0);
    }
    if (!is_red(node->left) && !is_red(node->left->left))
        node = move_red_to_left(node);
    node->left = remove_min(node->left);
    return (balance_me_that(node));
}

static t_rbnode* remove_it(t_rbnode* node, t_key key)
{
    t_rbnode* tmp;

    if (!node)
        return ((t_rbnode*)0);
    if (my_compare(key, node->key) == -1) {
        if (node->left) {
            if (!is_red(node->left) && !is_red(node->left->left))
                node = move_red_to_left(node);
            node->left = remove_key(node->left, key);
        }
    } else {
        if (is_red(node->left))
            node = rotate_right(node);
        if (!my_compare(key, node->key) && !node->right) {
            free(node);
            return ((t_rbnode*)0);
        }
        if (node->right) {
            if (!is_red(node->right) && !is_red(node->right->left))
                node = move_red_to_right(node);
            if (!my_compare(key, node->key)) {
                tmp = min(node->right);
                node->key = tmp->key;
                node->value = tmp->value;
                node->right = remove_min(node->right);
            } else
                node->right = remove_key(node->right, key);
        }
    }
    return (balance_me_that(node));
}

t_rbnode* remove_key(t_rbnode* node, t_key key)
{
    node = remove_it(node, key);
    if (node)
        node->color = BLACK;
    return (node);
}

t_rbnode* erase_tree(t_rbnode* node)
{
    if (node) {
        if (node->left)
            erase_tree(node->left);
        if (node->right)
            erase_tree(node->right);
        node->left = (t_rbnode*)0;
        node->right = (t_rbnode*)0;
        free(node);
    }
    return ((t_rbnode*)0);
}

extern t_rbnode* root_rbtree;

int main()
{
    /* root_rbtree = NULL; */
    /* insert(16, 16); */
    /* insert(24, 24); */
    /* insert(32, 32); */
    /* insert(40, 40); */
    /* insert(48, 48); */
    /* insert(80, 80); */
    /* insert(31426, 31426); */
    /* insert(31424, 31424); */
    /* root_rbtree = remove_k(root_rbtree, 31426); */
    /* root_rbtree = remove_k(root_rbtree, 31424); */
    /* root_rbtree = remove_k(root_rbtree, 24); */
    /* root_rbtree = remove_k(root_rbtree, 40); */
    /* root_rbtree = remove_k(root_rbtree, 48); */
    /* print_ascii_tree(root_rbtree); */

    unsigned int i;
    int a;
    srandom(time(NULL));
    for (i = 0; i < 30; ++i) {
        /* printf("\nboucle numero %d\n", i); */
        a = random() % 100;
        insert(a, a);
        //    insert(i + 'A', i + 'A');
        /* if (i % 50 == 0 && i > 0) */
        /*   remove_key(root_rbtree, random() % i); */
        /* print_ascii_tree(root_rbtree); */
    }

    /* remove_key(root_rbtree, 70); */
    /* remove_key(root_rbtree, 70); */
    /* remove_key(root_rbtree, 70); */
    /* insert(70, 70); */
    /* insert(70, 70); */
    /* insert(70, 70); */
    /* insert(70, 70); */
    /* insert(70, 70); */
    /* remove_key(root_rbtree, 72); */
    /* remove_key(root_rbtree, 68); */
    /* remove_key(root_rbtree, 69); */
    /* remove_key(root_rbtree, 65); */
    /* remove_key(root_rbtree, 66); */

    /* insert(66, 66); */
    /* insert(75, 75); */
    /* insert(76, 76); */
    /* insert(77, 77); */

    /* for (unsigned int i = 65; i < 75; ++i) */
    /*   root_rbtree = remove_key(root_rbtree, i); */

    //  root_rbtree = erase_tree(root_rbtree);
    //  print_ascii_tree(root_rbtree);
    //  printf("root_rbtree: %c\n", root_rbtree->key);
    erase_tree(root_rbtree);
    return (0);
}