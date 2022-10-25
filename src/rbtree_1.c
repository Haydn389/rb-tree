#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void)
{
  // TODO: initialize struct if needed
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  // p->nil->parent=NULL;
  // p->nil->left=NULL;
  // p->nil->right=NULL;
  
  p->nil->color = RBTREE_BLACK;
  p->nil=p->root; // nil이 root를 가리킴

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

void inorder(rbtree *t, node_t *node)
{
  if (node != t->nil)
    return;
  inorder(t,node->left);
  printf("%d \n", node->key);
  inorder(t, node->right);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  printf("insert start, %d \n",key);
  node_t *z=(node_t *)calloc(1, sizeof(node_t));
  z->key=key;
  node_t *y=t->nil;
  node_t *x=t->root;
  while(x!=t->nil)
  {
    y=x;
    if (key < x->key)
      x=x->left;
    else
      x=x->right;
  }
  

  node_t *p=t->root;
  node_t *parent = t->nil;

  //
  while (p != t->nil)
  {
    parent=p;
    if(p->key <= key){
      p=p->right;
    }
    else
      p=p->left;
  }
  //
  node_t *child = (node_t *)malloc(sizeof(node_t));
  child->key = key;
  child->left = t->nil;
  child->right = t->nil;

  // //
  if(parent!=NULL){
    if(parent->key < child->key)
      parent->right=child;
    else
      parent->left=child;
  }
  // printf("insert end, %d\n",t->root->key);
  return t->root;
}

void left_rotate(rbtree *t, node_t *x){
  node_t *y= x->right;  //x의 오른쪽 자식 y 선언
  x->right=y->left;     //y의 왼쪽 자식을 x의 오른쪽 자식으로 변경
  if (y->left!=t->nil)
    y->left->parent=x;  
  y->parent=x->parent;    //x의 부모를 y로 연결
  if (x->parent==t->nil)  //x의 부모 노드가 nil노드면 트리의 루트노드를 y로 변경
    t->root=y;            
  else if (x==x->parent->left)//x의 부모 노드의 왼쪽자식이면, x의 부모노드의 왼쪽 자식을 y로 변경
    x->parent->left=y;
  else
    x->parent->right=y;//x의 부모 노드의 오른쪽자식이면, x의 부모노드의 오른쪽 자식을 y로 변경
  y->left=x;  // y의 왼쪽 자식 노드를 x로 변경
  x->parent=y;// x의 부모 노드를 y로 변경
}

void right_rotate(rbtree *t, node_t *y){
  node_t *x= y->left;  //y의 왼쪽 자식 x 선언
  y->left=x->right;     //x의 오른쪽 서브트리를 y의 왼쪽 서브트리로 옮긴다
  if (x->right!=t->nil) //x의 오른쪽 자식노드가 nil이 아니면 x의 오른쪽 자식노드의 부모노드를y로변경
    x->right->parent=y;  
  x->parent=y->parent;    //x의 부모를 y의 부모로 변경

  if (y->parent==t->nil)  //y의 부모 노드가 nil노드면 트리의 루트노드를 x로 변경
    t->root=x;            
  else if (y==y->parent->left)//y가 부모 노드의 왼쪽자식이면, y의 부모노드의 왼쪽 자식을 x로 변경
    y->parent->left=x;
  else
    y->parent->right=x;//y의 부모 노드의 오른쪽자식이면, y의 부모노드의 오른쪽 자식을 x로 변경
  x->right=y;  // x의 오른 자식 노드를 y로 변경
  y->parent=x;// y의 부모 노드를 x로 변경
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

