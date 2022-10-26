#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>

typedef enum
{
  RBTREE_RED,
  RBTREE_BLACK
} color_t;

typedef int key_t;

typedef struct node_t
{
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;

typedef struct
{
  node_t *root;
  node_t *nil; // for sentinel
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
int rbtree_erase(rbtree *, node_t *);

int rbtree_to_array(const rbtree *, key_t *, const size_t);

//�߰추가함수
void inorder(rbtree *t, node_t *node);
void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *y);
void insert_fixup(rbtree *t, node_t *z);
void destroy_node(rbtree *t, node_t *node);
int inorder_save(const rbtree *t, node_t *node, int n, int i, int *arr);
node_t *find_succsesor(const rbtree *t, node_t *node_to_remove);
void rb_transplant(rbtree *t,node_t*u,node_t*v);
void delete_fixup(rbtree *t, node_t *x);
#endif // _RBTREE_H_
