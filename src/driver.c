#include "rbtree.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
  rbtree *tree=new_rbtree();

  // printf(">>>%p\n",tree->nil); /* nil과 root의관계*/
  // printf(">>>%p\n",tree->root); /* nil과 root의관계*/
  // printf(">>>%p\n",tree->root->key); /* nil과 root의관계*/

  tree->root=rbtree_insert(tree,50);
  tree->root=rbtree_insert(tree,10);
  tree->root=rbtree_insert(tree,100);
  inorder(tree,tree->root);
  printf("1회수행 \n");
  tree->root=rbtree_insert(tree,20);
  tree->root=rbtree_insert(tree,70);
  tree->root=rbtree_insert(tree,65);
  inorder(tree,tree->root);
  printf("삭제 \n");
  delete_rbtree(tree);
  inorder(tree,tree->root);
  

  printf("\nhello\n");
  printf("%d\n",RBTREE_RED);

  return 0;
}