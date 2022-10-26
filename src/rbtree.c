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

void destroy_node(rbtree *t, node_t *node) //�������� Ž������ ��� �Ҵ�����
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
  // ����� z ����
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->key = key;
  node_t *y = t->nil;   // nil��� y ���� : �� ��� z�� �� ��带 ã�Ƽ� ������
  node_t *x = t->root;  // Ž�� ������ ���� ��Ʈ���� x ����
  while (x != t->nil)   // x�� nil�� ������ ����
  {
    y = x;
    if (key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y; //�� ��� z�� �θ� y�� ����(���� ù ���� z�� p�� nil�̵�)
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
  // z�� �׻� red�� z.p�� red�� �ȵǱ� ������ #4����
  node_t *y; //���̳��
  while (z->parent->color == RBTREE_RED)
  {
    if (z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right; //���̳�� ����
      if (y->color == RBTREE_RED)   //���̳�尡 �������
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
          z = z->parent; // z�� pivot���� ������Ʈ �� ȸ��
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent); //
      }
    }
    else
    {
      y = z->parent->parent->left; //���̳�� ����
      if (y->color == RBTREE_RED)  //���̳�尡 �������
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
          z = z->parent; // z�� pivot���� ������Ʈ �� ȸ��
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
  node_t *y = x->right; // x�� ������ �ڽ� y ����
  x->right = y->left;   // y�� ���� �ڽ��� x�� ������ �ڽ����� ����
  if (y->left != t->nil)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;   // x�� �θ� y�� ����
  if (x->parent == t->nil) // x�� �θ� ��尡 nil���� Ʈ���� ��Ʈ��带 y�� ����
  {
    t->root = y;
  }
  else if (x == x->parent->left) // x�� �θ� ����� �����ڽ��̸�, x�� �θ����� ���� �ڽ��� y�� ����
    x->parent->left = y;
  else
    x->parent->right = y; // x�� �θ� ����� �������ڽ��̸�, x�� �θ����� ������ �ڽ��� y�� ����
  y->left = x;            // y�� ���� �ڽ� ��带 x�� ����
  x->parent = y;          // x�� �θ� ��带 y�� ����
  return;
}

void right_rotate(rbtree *t, node_t *y)
{
  node_t *x = y->left;    // y�� ���� �ڽ� x ����
  y->left = x->right;     // x�� ������ ����Ʈ���� y�� ���� ����Ʈ���� �ű��
  if (x->right != t->nil) // x�� ������ �ڽĳ�尡 nil�� �ƴϸ� x�� ������ �ڽĳ���� �θ��带y�κ���
    x->right->parent = y;
  x->parent = y->parent;  // x�� �θ� y�� �θ�� ����

  if (y->parent == t->nil) // y�� �θ� ��尡 nil���� Ʈ���� ��Ʈ��带 x�� ����
    t->root = x;
  else if (y == y->parent->left) // y�� �θ� ����� �����ڽ��̸�, y�� �θ����� ���� �ڽ��� x�� ����
    y->parent->left = x;
  else
    y->parent->right = x; // y�� �θ� ����� �������ڽ��̸�, y�� �θ����� ������ �ڽ��� x�� ����
  x->right = y;           // x�� ���� �ڽ� ��带 y�� ����
  y->parent = x;          // y�� �θ� ��带 x�� ����
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
  node_t *x=t->root;  //��Ʈ���� Ž������
  if (x==t->nil)
    return x;
  while (x->left!=t->nil)
  {
    x=x->left;
  }
  return x;
}

//���� ��尡 tree�� root�� �ƴѰ�쿡 �İ��ڸ� ã������
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
  node_t *x=t->root;  //��Ʈ���� Ž������
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
  //y�� ���� = �����Ǵ� ���� ��ġ�� �ִ� ��� (������ ��� or successor)
  //y (z���ڽ��� 2�̸�) : Ʈ������ ������ ���
  //y_color (z���ڽ��� 2�̸�) : Ʈ������ ������ ����� ��
  //y (z���ڽ��� 2�̻�) : successor
  //y_color (z���ڽ��� 2�̻�) : successor �� ��
  node_t *y=z;
  color_t y_origin_col=y->color; //�����Ǵ� �� 
  node_t *x=NULL;   //x�� ������ ���� ��ġ�� ��ü�ϴ� ���(���� ���⿡ extra black�ٿ���)
  if(z->left==t->nil) //�����ڽ�(X) ������ �ڽ�(X or O)
  {
    x=z->right; 
    rb_transplant(t,z,z->right);
  }
  else if (z->right==t->nil) //�����ڽ�(O) ������ �ڽ� (X)
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
  node_t *w;  //x�� �������
  while (x!=t->root && x->color==RBTREE_BLACK)
  {
    if(x==x->parent->left)//x�� �θ��� �����ڽ��ΰ��
    {
      w=x->parent->right; // x�� �������
      if(w->color==RBTREE_RED) // Case 1
      {
        w->color=RBTREE_BLACK; //������ �θ� �� ��ȯ
        x->parent->color=RBTREE_RED;
        left_rotate(t,x->parent); //�θ���� ��ȸ��
        w=x->parent->right;    //w�� �ٽ� x�� �θ��� �����ڽ����� ������Ʈ
      }
      if(w->left->color==RBTREE_BLACK && w->right->color==RBTREE_BLACK)
      { // Case2 x�� w�� black�� ��Ƽ� �θ𿡰� ����
        w->color=RBTREE_RED;  //w�� red�� ��
        x=x->parent;  //�θ𿡰� ����
      }
      else
      {
        if(w->right->color==RBTREE_BLACK)
        { // Case 3
          w->left->color=RBTREE_BLACK;  //������ ������ ������ ������ �����ڳ� �� ��ȯ
          w->color=RBTREE_RED;
          right_rotate(t,w);  //������ ���� �������� ȸ��
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
    else//x�� �θ��� ������ �ڽ��ΰ��
    {
      w=x->parent->left; // x�� �������
      if(w->color==RBTREE_RED) // Case 1
      {
        w->color=RBTREE_BLACK; //������ �θ� �� ��ȯ
        x->parent->color=RBTREE_RED;
        right_rotate(t,x->parent); //�θ���� ��ȸ��
        w=x->parent->left;    //w�� �ٽ� x�� �θ��� �����ڽ����� ������Ʈ
      }
      if(w->right->color==RBTREE_BLACK && w->left->color==RBTREE_BLACK)
      { // Case2 x�� w�� black�� ��Ƽ� �θ𿡰� ����
        w->color=RBTREE_RED;  //w�� red�� ��
        x=x->parent;  //�θ𿡰� ����
      }
      else
      {
        if(w->left->color==RBTREE_BLACK)
        { // Case 3
          w->right->color=RBTREE_BLACK;  //������ ������ ������ ������ �����ڳ� �� ��ȯ
          w->color=RBTREE_RED;
          left_rotate(t,w);  //������ ���� �������� ȸ��
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