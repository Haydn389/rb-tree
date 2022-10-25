#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void)
{
  // TODO: initialize struct if needed
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  // nil노드 초기화
  p->nil->color = RBTREE_BLACK;
  p->nil->key = 9;
  p->root = p->nil;
  // p->root->parent=p->nil;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  destroy_node(t,t->root);
  free(t->nil);
  free(t);
}

void destroy_node(rbtree *t,node_t* node)//후위순위 탐색으로 노드 할당해제
{
  if(node==t->nil)
    return;
  destroy_node(t,node->left);
  destroy_node(t,node->right);
  free(node);
  printf("free node!!\n");
}


void inorder(rbtree *t, node_t *node)
{
  if (node == t->nil)
    return;
  inorder(t, node->left);
  printf("%d ->", node->key);
  inorder(t, node->right);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{ // TODO: implement insert
  // printf("insert start, %d \n",key);
  // 새노드 z 선언
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->key = key;
  // nil노드 y 선언
  node_t *y = t->nil;
  node_t *x = t->root; //루트도느 x 선언
  while (x != t->nil) //x가 nil을 만날때 까지
  {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y; //새 노드 z의 부모를 y에 연결
  if (y == t->nil)
    t->root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  // insert_fixup(t,z);

  return t->root;
}

void insert_fixup(rbtree *t, node_t *z)
{
  // z는 항상 red이기때문에 z.p가 red면 계속 수행
  while (z->parent->color == RBTREE_RED)
  {
    if (z->parent == z->parent->parent->left)
    {
      node_t *y = z->parent->parent->right; //삼촌노드 선언
      if (y->color == RBTREE_RED)           //삼촌노드가 붉은경우
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent = RBTREE_RED;
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->right)
        {
          z = z->parent; // z를 pivot으로 업데이트 후 회전
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent); //
      }
    }
    else
    {
      node_t *y = z->parent->parent->left; //삼촌노드 선언
      if (y->color == RBTREE_RED)          //삼촌노드가 붉은경우
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent = RBTREE_RED;
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->left)
        {
          z = z->parent; // z를 pivot으로 업데이트 후 회전
          right_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent); //
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void left_rotate(rbtree *t, node_t *x)
{
  node_t *y = x->right; // x의 오른쪽 자식 y 선언
  x->right = y->left;   // y의 왼쪽 자식을 x의 오른쪽 자식으로 변경
  if (y->left != t->nil)
    y->left->parent = x;
  y->parent = x->parent;   // x의 부모를 y로 연결
  if (x->parent == t->nil) // x의 부모 노드가 nil노드면 트리의 루트노드를 y로 변경
    t->root = y;
  else if (x == x->parent->left) // x의 부모 노드의 왼쪽자식이면, x의 부모노드의 왼쪽 자식을 y로 변경
    x->parent->left = y;
  else
    x->parent->right = y; // x의 부모 노드의 오른쪽자식이면, x의 부모노드의 오른쪽 자식을 y로 변경
  y->left = x;            // y의 왼쪽 자식 노드를 x로 변경
  x->parent = y;          // x의 부모 노드를 y로 변경
}

void right_rotate(rbtree *t, node_t *y)
{
  node_t *x = y->left;    // y의 왼쪽 자식 x 선언
  y->left = x->right;     // x의 오른쪽 서브트리를 y의 왼쪽 서브트리로 옮긴다
  if (x->right != t->nil) // x의 오른쪽 자식노드가 nil이 아니면 x의 오른쪽 자식노드의 부모노드를y로변경
    x->right->parent = y;
  x->parent = y->parent; // x의 부모를 y의 부모로 변경

  if (y->parent == t->nil) // y의 부모 노드가 nil노드면 트리의 루트노드를 x로 변경
    t->root = x;
  else if (y == y->parent->left) // y가 부모 노드의 왼쪽자식이면, y의 부모노드의 왼쪽 자식을 x로 변경
    y->parent->left = x;
  else
    y->parent->right = x; // y의 부모 노드의 오른쪽자식이면, y의 부모노드의 오른쪽 자식을 x로 변경
  x->right = y;           // x의 오른 자식 노드를 y로 변경
  y->parent = x;          // y의 부모 노드를 x로 변경
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
