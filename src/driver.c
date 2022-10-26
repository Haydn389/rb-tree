#include "rbtree.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
  rbtree *tree=new_rbtree();

  // printf(">>>%p\n",tree->nil); /* nil과 root의관계*/
  // printf(">>>%p\n",tree->root); /* nil과 root의관계*/
  // printf(">>>%p\n",tree->root->key); /* nil과 root의관계*/

  rbtree_insert(tree,10);
  rbtree_insert(tree,9);
  rbtree_insert(tree,8);
  rbtree_insert(tree,7);
  rbtree_insert(tree,6);
  rbtree_insert(tree,5);
  rbtree_insert(tree,4);
  rbtree_insert(tree,3);
  rbtree_insert(tree,2);

  inorder(tree,tree->root);
  printf("\n");
  printf("root key : %d\n",tree->root->key);
  // int n=9;
  // int arr[n];
  // rbtree_to_array(tree, arr, n);
  // for (int i=0;i<n;i++){
  //   printf("%d >>> ",arr[i]);
  // }
  /*erase test*/
  node_t *target=rbtree_find(tree,7);
  rbtree_erase(tree,target);
  printf("\n");
  inorder(tree,tree->root);
  printf("\n");
  printf("root key : %d\n",tree->root->key);

  /*find test*/
  // node_t*find=rbtree_find(tree,0);
  // if (find==NULL)
  // {
  //   printf(">>찾는값이 없습니다.\n");
  // }
  // else
  //   printf(">>find node : %d\n",find->key);

  printf("삭제 \n");
  // delete_rbtree(tree);
  // inorder(tree,tree->root);
  printf("hello\n");
  // printf("%d\n",RBTREE_RED);

  return 0;
}