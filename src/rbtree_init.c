#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void)
{
  // TODO: initialize struct if needed
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  // nil��� �ʱ�ȭ
  p->nil->color = RBTREE_BLACK;
  // p->nil->left = NULL;
  // p->nil->right = NULL;
  p->nil->key = 999;
  p->root=p->nil; 

  p->root=(node_t *)calloc(1, sizeof(node_t));
  p->root->parent=p->nil;
  p->nil->left=p->root;
  p->nil->right=p->root;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

void inorder(rbtree *t, node_t *node)
{
  if (node == t->nil)
    return;
  inorder(t,node->left);
  printf("%d \n", node->key);
  inorder(t, node->right);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{ // TODO: implement insert
  // printf("insert start, %d \n",key);

  // ����� z ����
  node_t *z=(node_t *)calloc(1, sizeof(node_t));
  z->key=key;

  // nil��� y ����
  node_t *y=t->nil;
  node_t *x=t->root;
  while(x!=t->nil)
  {
    y=x;
    if (z->key < x->key)
      x=x->left;
    else
      x=x->right;
  }
  z->parent=y;
  if (y==t->nil)
    t->root=z;
  else if (z->key<y->key)
    y->left=z;
  else y->right=z;

  z->left=t->nil;
  z->right=t->nil;
  z->color=RBTREE_RED;

  return t->root;
}



void left_rotate(rbtree *t, node_t *x){
  node_t *y= x->right;  //x�� ������ �ڽ� y ����
  x->right=y->left;     //y�� ���� �ڽ��� x�� ������ �ڽ����� ����
  if (y->left!=t->nil)
    y->left->parent=x;  
  y->parent=x->parent;    //x�� �θ� y�� ����
  if (x->parent==t->nil)  //x�� �θ� ��尡 nil���� Ʈ���� ��Ʈ��带 y�� ����
    t->root=y;            
  else if (x==x->parent->left)//x�� �θ� ����� �����ڽ��̸�, x�� �θ����� ���� �ڽ��� y�� ����
    x->parent->left=y;
  else
    x->parent->right=y;//x�� �θ� ����� �������ڽ��̸�, x�� �θ����� ������ �ڽ��� y�� ����
  y->left=x;  // y�� ���� �ڽ� ��带 x�� ����
  x->parent=y;// x�� �θ� ��带 y�� ����
}

void right_rotate(rbtree *t, node_t *y){
  node_t *x= y->left;  //y�� ���� �ڽ� x ����
  y->left=x->right;     //x�� ������ ����Ʈ���� y�� ���� ����Ʈ���� �ű��
  if (x->right!=t->nil) //x�� ������ �ڽĳ�尡 nil�� �ƴϸ� x�� ������ �ڽĳ���� �θ��带y�κ���
    x->right->parent=y;  
  x->parent=y->parent;    //x�� �θ� y�� �θ�� ����

  if (y->parent==t->nil)  //y�� �θ� ��尡 nil���� Ʈ���� ��Ʈ��带 x�� ����
    t->root=x;            
  else if (y==y->parent->left)//y�� �θ� ����� �����ڽ��̸�, y�� �θ����� ���� �ڽ��� x�� ����
    y->parent->left=x;
  else
    y->parent->right=x;//y�� �θ� ����� �������ڽ��̸�, y�� �θ����� ������ �ڽ��� x�� ����
  x->right=y;  // x�� ���� �ڽ� ��带 y�� ����
  y->parent=x;// y�� �θ� ��带 x�� ����
}




node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}

