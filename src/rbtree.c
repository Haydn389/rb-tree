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
  p->nil->key = 0;
  p->root = p->nil;
  // p->root->parent=p->nil;
  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  destroy_node(t, t->root);
  free(t->nil);
  free(t);
}

void destroy_node(rbtree *t, node_t *node) //후위순위 탐색으로 노드 할당해제
{
  if (node == t->nil)
    return;
  destroy_node(t, node->left);
  destroy_node(t, node->right);
  free(node);
  // printf("free node!!\n");
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
  node_t *y = t->nil;   // nil노드 y 선언 : 새 노드 z가 들어갈 노드를 찾아서 저장함
  node_t *x = t->root;  // 탐색 시작을 위해 루트도느 x 선언
  while (x != t->nil)   // x가 nil을 만날때 까지
  {
    y = x;
    if (key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y; //새 노드 z의 부모를 y에 연결(만약 첫 노드면 z의 p가 nil이됨)
  if (y == t->nil)
    t->root = z;
  else if (key < y->key)
    y->left = z;
  else
    y->right = z;

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  insert_fixup(t, z);
  return t->root;
}

void insert_fixup(rbtree *t, node_t *z)
{
  // z는 항상 red라서 z.p가 red면 안되기 때문에 #4위반
  node_t *y; //삼촌노드
  while (z->parent->color == RBTREE_RED)
  {
    if (z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right; //삼촌노드 선언
      if (y->color == RBTREE_RED)   //삼촌노드가 붉은경우
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
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
      y = z->parent->parent->left; //삼촌노드 선언
      if (y->color == RBTREE_RED)  //삼촌노드가 붉은경우
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
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
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return;
}

void left_rotate(rbtree *t, node_t *x)
{
  node_t *y = x->right; // x의 오른쪽 자식 y 선언
  x->right = y->left;   // y의 왼쪽 자식을 x의 오른쪽 자식으로 변경
  if (y->left != t->nil)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;   // x의 부모를 y로 연결
  if (x->parent == t->nil) // x의 부모 노드가 nil노드면 트리의 루트노드를 y로 변경
  {
    t->root = y;
  }
  else if (x == x->parent->left) // x의 부모 노드의 왼쪽자식이면, x의 부모노드의 왼쪽 자식을 y로 변경
    x->parent->left = y;
  else
    x->parent->right = y; // x의 부모 노드의 오른쪽자식이면, x의 부모노드의 오른쪽 자식을 y로 변경
  y->left = x;            // y의 왼쪽 자식 노드를 x로 변경
  x->parent = y;          // x의 부모 노드를 y로 변경
  return;
}

void right_rotate(rbtree *t, node_t *y)
{
  node_t *x = y->left;    // y의 왼쪽 자식 x 선언
  y->left = x->right;     // x의 오른쪽 서브트리를 y의 왼쪽 서브트리로 옮긴다
  if (x->right != t->nil) // x의 오른쪽 자식노드가 nil이 아니면 x의 오른쪽 자식노드의 부모노드를y로변경
    x->right->parent = y;
  x->parent = y->parent;  // x의 부모를 y의 부모로 변경

  if (y->parent == t->nil) // y의 부모 노드가 nil노드면 트리의 루트노드를 x로 변경
    t->root = x;
  else if (y == y->parent->left) // y가 부모 노드의 왼쪽자식이면, y의 부모노드의 왼쪽 자식을 x로 변경
    y->parent->left = x;
  else
    y->parent->right = x; // y의 부모 노드의 오른쪽자식이면, y의 부모노드의 오른쪽 자식을 x로 변경
  x->right = y;           // x의 오른 자식 노드를 y로 변경
  y->parent = x;          // y의 부모 노드를 x로 변경
  return;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  node_t *z = t->root;
  while (z != t->nil)
  {
    if (z->key == key)
      return z;
    else if (z->key < key)
      z = z->right;
    else
      z = z->left;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  node_t *x=t->root;  //루트부터 탐색시작
  if (x==t->nil)
    return x;
  while (x->left!=t->nil)
  {
    x=x->left;
  }
  return x;
}

//시작 노드가 tree의 root가 아닌경우에 후계자를 찾기위함
node_t*tree_minimum(const rbtree *t, node_t*node_to_remove)
{
  node_t*x=node_to_remove;
  if (x==t->nil)
    return x;
  while (x->left!=t->nil)
  {
    x=x->left;
  }
  return x;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *x=t->root;  //루트부터 탐색시작
  if (x==t->nil)
    return x;
  while (x->right!=t->nil)
  {
    x=x->right;
  }
  return x;
}

void rb_transplant(rbtree *t,node_t*u,node_t*v)
{
  if(u->parent==t->nil)
    t->root=v;
  else if (u==u->parent->left)
    u->parent->left=v;
  else 
    u->parent->right=v;
  v->parent=u->parent;    
}

int rbtree_erase(rbtree *t, node_t *z)
{
  // TODO: implement erase
  //y의 정의 = 삭제되는 색의 위치에 있던 노드 (삭제될 노드 or successor)
  //y (z의자식이 2미만) : 트리에서 삭제될 노드
  //y_color (z의자식이 2미만) : 트리에서 삭제될 노드의 색
  //y (z의자식이 2이상) : successor
  //y_color (z의자식이 2이상) : successor 의 색
  node_t *y=z;
  color_t y_origin_col=y->color; //삭제되는 색 
  node_t *x=NULL;   //x는 삭제된 색의 위치를 대체하는 노드(추후 여기에 extra black붙여줌)
  if(z->left==t->nil) //왼쪽자식(X) 오른쪽 자식(X or O)
  {
    x=z->right; 
    rb_transplant(t,z,z->right);
  }
  else if (z->right==t->nil) //왼쪽자식(O) 오른쪽 자식 (X)
  {
    x=z->left;
    rb_transplant(t,z,z->left);
  }
  else
  {
    y=tree_minimum(t,z->right);
    y_origin_col=y->color;
    x=y->right;
    if(y->parent==z)
    {
      x->parent=y;
    }
    else
    {
      rb_transplant(t,y,y->right);
      y->right=z->right;
      y->right->parent=y;
    }
    rb_transplant(t,z,y);
    y->left=z->left;
    y->left->parent=y;
    y->color=z->color;
  }
  if(y_origin_col==RBTREE_BLACK)
  {
    delete_fixup(t,x);
  }
  free(z);
  return 0;
}

void delete_fixup(rbtree *t, node_t *x){
  node_t *w;  //x의 형제노드
  while (x!=t->root && x->color==RBTREE_BLACK)
  {
    if(x==x->parent->left)//x가 부모의 왼쪽자식인경우
    {
      w=x->parent->right; // x의 형제노드
      if(w->color==RBTREE_RED) // Case 1
      {
        w->color=RBTREE_BLACK; //형제와 부모 색 교환
        x->parent->color=RBTREE_RED;
        left_rotate(t,x->parent); //부모기준 좌회전
        w=x->parent->right;    //w는 다시 x의 부모의 오른자식으로 업데이트
      }
      if(w->left->color==RBTREE_BLACK && w->right->color==RBTREE_BLACK)
      { // Case2 x와 w의 black을 모아서 부모에게 전달
        w->color=RBTREE_RED;  //w는 red가 됨
        x=x->parent;  //부모에게 전가
      }
      else
      {
        if(w->right->color==RBTREE_BLACK)
        { // Case 3
          w->left->color=RBTREE_BLACK;  //오른쪽 형제와 오른쪽 형제의 왼쪽자녀 색 교환
          w->color=RBTREE_RED;
          right_rotate(t,w);  //오른쪽 형제 기준으로 회전
          w=x->parent->right; 
        }
        //Case 4
        w->color=x->parent->color;
        x->parent->color=RBTREE_BLACK;
        w->right->color=RBTREE_BLACK;
        left_rotate(t,x->parent);
        x=t->root;
      }
    } 
    else//x가 부모의 오른쪽 자식인경우
    {
      w=x->parent->left; // x의 형제노드
      if(w->color==RBTREE_RED) // Case 1
      {
        w->color=RBTREE_BLACK; //형제와 부모 색 교환
        x->parent->color=RBTREE_RED;
        right_rotate(t,x->parent); //부모기준 좌회전
        w=x->parent->left;    //w는 다시 x의 부모의 오른자식으로 업데이트
      }
      if(w->right->color==RBTREE_BLACK && w->left->color==RBTREE_BLACK)
      { // Case2 x와 w의 black을 모아서 부모에게 전달
        w->color=RBTREE_RED;  //w는 red가 됨
        x=x->parent;  //부모에게 전가
      }
      else
      {
        if(w->left->color==RBTREE_BLACK)
        { // Case 3
          w->right->color=RBTREE_BLACK;  //오른쪽 형제와 오른쪽 형제의 왼쪽자녀 색 교환
          w->color=RBTREE_RED;
          left_rotate(t,w);  //오른쪽 형제 기준으로 회전
          w=x->parent->left; 
        }
        //Case 4
        w->color=x->parent->color;
        x->parent->color=RBTREE_BLACK;
        w->left->color=RBTREE_BLACK;
        right_rotate(t,x->parent);
        x=t->root;
      }
    }
  }
  x->color=RBTREE_BLACK;
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  inorder_save(t, t->root, n,0,arr);
  return 0;
}

int inorder_save(const rbtree *t, node_t *node, int n,int i,int *arr)
{
  if (node == t->nil || i>=n)
    return i;
  i=inorder_save(t, node->left, n,i,arr);
  // printf("%d ** ", node->key);
  arr[i++]=node->key;
  i=inorder_save(t, node->right, n,i,arr);
  return i;
}