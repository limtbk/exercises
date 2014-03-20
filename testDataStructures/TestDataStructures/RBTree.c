//
//  RBTree.c
//  TestDataStructures
//
//  Created by lim on 3/20/14.
//  Copyright (c) 2014 lim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBTree.h"

PRBTree newRBTree() {
    PRBTree tree = calloc(1, sizeof(RBTree));
    tree->compareKey = &defaultCompareKey;
    tree->freeKey = &defaultFreeKey;
    tree->printKey = &defaultPrintKey;
    tree->freeValue = &defaultFreeValue;
    tree->printValue = &defaultPrintValue;
    return tree;
}

PRBTreeNode newRBTreeNode(void *key, void *value) {
    PRBTreeNode treeNode = calloc(1, sizeof(RBTreeNode));
    treeNode->key = key;
    treeNode->value = value;
    return treeNode;
}

int isLastNode(PRBTree tree, PRBTreeNode node) { //return if node has nilNode in left and right
    return (NULL == node->left) && (NULL == node->right);
}

PRBTreeNode findNodeWithKey(PRBTree tree, PRBTreeNode node, void *key) {
    if (node != NULL) {
        PRBTreeNode currentNode = node;
        int compareResult = tree->compareKey(currentNode->key, key);
        while (compareResult) {
            if (compareResult>0) {
                if (currentNode->left) {
                    currentNode = currentNode->left;
                } else {
                    break;
                }
            } else if (compareResult<0) {
                if (currentNode->right) {
                    currentNode = currentNode->right;
                } else {
                    break;
                }
            }
            compareResult = tree->compareKey(currentNode->key, key);
        }
        return currentNode;
    } else {
        return NULL;
    }
}

PRBTreeNode findNodeInTreeWithKey(PRBTree tree, void *key) { //stops if node found or no way down
    return findNodeWithKey(tree, tree->root, key);
}


PRBTreeNode nodeGrandParent(PRBTreeNode node) {
    PRBTreeNode grandParent = NULL;
    PRBTreeNode parent = node->parent;
    if (parent) {
        grandParent = parent->parent;
    }
    return grandParent;
}

PRBTreeNode nodeUncle(PRBTreeNode node) {
    PRBTreeNode uncle = NULL;
    PRBTreeNode parent = node->parent;
    PRBTreeNode grandParent = nodeGrandParent(node);
    if (grandParent) {
        if (grandParent->left == parent) {
            uncle = grandParent->right;
        } else {
            uncle = grandParent->left;
        }
    }
    return uncle;
}

void rotateLeft(PRBTree tree, PRBTreeNode node) {
    PRBTreeNode parent = node->parent;
    int isLeft;
    if (parent) {
        isLeft = (parent->left == node);
    }
    PRBTreeNode right = node->right;
    if (right) {
        node->right = right->left;
        if (node->right) {
            node->right->parent = node;
        }
        right->left = node;
        right->left->parent = right;
        if (parent) {
            if (isLeft) {
                parent->left = right;
            } else {
                parent->right = right;
            }
        } else {
            tree->root = right;
            right->parent = NULL;
        }
    }
}

void rotateRight(PRBTree tree, PRBTreeNode node) {
    PRBTreeNode parent = node->parent;
    int isLeft;
    if (parent) {
        isLeft = (parent->left == node);
    }
    PRBTreeNode left = node->left;
    if (left) {
        node->left = left->right;
        if (node->left) {
            node->left->parent = node;
        }
        left->right = node;
        left->right->parent = left;
        if (parent) {
            if (isLeft) {
                parent->left = left;
            } else {
                parent->right = left;
            }
        } else {
            tree->root = left;
            left->parent = NULL;
        }
    }
}

void insertCase1(PRBTree tree, PRBTreeNode newNode);
void insertCase2(PRBTree tree, PRBTreeNode newNode);
void insertCase3(PRBTree tree, PRBTreeNode newNode);
void insertCase4(PRBTree tree, PRBTreeNode newNode);
void insertCase5(PRBTree tree, PRBTreeNode newNode);

void insertCase1(PRBTree tree, PRBTreeNode newNode) {
    printf("@1");
    if (NULL == newNode->parent) {
        newNode->color = RBTreeColorBlack;
    } else {
        insertCase2(tree, newNode);
    }
}

void insertCase2(PRBTree tree, PRBTreeNode newNode) {
    printf("@2");
    if (newNode->parent->color == RBTreeColorBlack) {
        newNode->color = RBTreeColorRed;
    } else {
        insertCase3(tree, newNode);
    }
}

void insertCase3(PRBTree tree, PRBTreeNode newNode) {
    printf("@3");
    PRBTreeNode uncle = nodeUncle(newNode);
    if ((uncle!=NULL) && (uncle->color == RBTreeColorRed)) {
        newNode->parent->color = RBTreeColorBlack;
        uncle->color = RBTreeColorBlack;
        newNode->parent->parent->color = RBTreeColorRed;
        insertCase1(tree, newNode->parent->parent);
    } else {
        insertCase4(tree, newNode);
    }
}

void insertCase4(PRBTree tree, PRBTreeNode newNode) {
    printf("@4");
    PRBTreeNode node = newNode;
    if ((newNode == newNode->parent->right) && (newNode->parent == newNode->parent->parent->left)) {
        node = newNode->parent;
        rotateLeft(tree, newNode->parent);
    } else if ((newNode == newNode->parent->left) && (newNode->parent == newNode->parent->parent->right)) {
        node = newNode->parent;
        rotateRight(tree, newNode->parent);
    }
    insertCase5(tree, node);
}

void insertCase5(PRBTree tree, PRBTreeNode newNode) {
    printf("@5");
    newNode->parent->color = RBTreeColorBlack;
    newNode->parent->parent->color = RBTreeColorRed;
    if (newNode == newNode->parent->left) {
        rotateRight(tree, newNode->parent->parent);
    } else {
        rotateLeft(tree, newNode->parent->parent);
    }
}

void setValueForKey(PRBTree tree, void *value, void *key) {
    PRBTreeNode node = findNodeInTreeWithKey(tree, key);
    int compareResult = 0;
    
    if (node) { //case 0: replace value with key instead of insert new value
        compareResult = tree->compareKey(node->key, key);
        int compareResult = tree->compareKey(node->key, key);
        if (0 == compareResult) {
            tree->freeValue(node->value);
            node->value = value;
            return;
        }
    }
    
    PRBTreeNode newNode = newRBTreeNode(key, value);
    if (!node) {
        tree->root = newNode;
        insertCase1(tree, newNode);
    } else if (compareResult>0) {
        node->left = newNode;
        newNode->parent = node;
        insertCase2(tree, newNode);
    } else if (compareResult<0) {
        node->right = newNode;
        newNode->parent = node;
        insertCase2(tree, newNode);
    }
}

void *getValueForKey(PRBTree tree, void *key) {
    PRBTreeNode node = findNodeInTreeWithKey(tree, key);
    if (node) {
        int compareResult = tree->compareKey(node->key, key);
        if (0 == compareResult) {
            return node->value;
        }
    }
    return NULL;
}

void freeNode(PRBTreeNode node) {
    defaultFreeKey(node->key);
    defaultFreeValue(node->value);
    free(node);
}

void removeValueForKey(PRBTree tree, void *key) {
    
    /*
     PRBTreeNode aTree = *tree;
     if (aTree) {
     int cmpresult = defaultCompareKey(key, aTree->key);
     if (cmpresult==0) {
     if (aTree->left) {
     if (aTree->right) { // left, right
     PRBTreeNode leftXCHG = aTree->left;
     PRBTreeNode leftXCHGParent = NULL;
     while (leftXCHG->right) {
     leftXCHGParent = leftXCHG;
     leftXCHG = leftXCHG->right;
     }
     leftXCHG->right = aTree->right;
     leftXCHG->right->parent = leftXCHG;
     if (leftXCHGParent) {
     leftXCHGParent->right = leftXCHG->left;
     leftXCHGParent->right->parent = leftXCHGParent;
     leftXCHG->left = aTree->left;
     leftXCHG->left->parent = leftXCHG;
     }
     *tree = leftXCHG;
     freeNode(aTree);
     
     } else { //left
     *tree = aTree->left;
     freeNode(aTree);
     }
     } else {
     if (aTree->right) { //right
     *tree = aTree->right;
     freeNode(aTree);
     } else { // none
     *tree = NULL;
     freeNode(aTree);
     }
     }
     } else if (cmpresult<0) {
     removeValueForKey(&(aTree->left), key);
     } else {
     removeValueForKey(&(aTree->right), key);
     }
     }
     */
}

/*
 typedef struct NodeListStruct NodeList;
 typedef NodeList *PNodeList;
 struct NodeListStruct {
 PRBTreeNode treeNode;
 PNodeList next;
 };
 
 PNodeList addToList(PNodeList *list, PRBTreeNode node) {
 PNodeList aList = calloc(1, sizeof(NodeList));
 aList->treeNode = node;
 if (*list) {
 (*list)->next = aList;
 } else {
 *list = aList;
 }
 return  aList;
 }
 
 void bfs(PRBTreeNode *tree, PTreeProc proc) {
 PNodeList listStart = NULL;
 PNodeList listEnd = addToList(&listStart, *tree);
 while (listStart) {
 if (listStart->treeNode->left) {
 listEnd = addToList(&listEnd, listStart->treeNode->left);
 }
 if (listStart->treeNode->right) {
 listEnd = addToList(&listEnd, listStart->treeNode->right);
 }
 (*proc)(&(listStart->treeNode));
 PNodeList next = listStart->next;
 free(listStart);
 listStart = next;
 }
 }
 
 void dfs(PRBTreeNode *tree, PTreeProc proc) {
 PRBTreeNode aTree = *tree;
 if (aTree) {
 dfs(&aTree->left, proc);
 (*proc)(&aTree);
 dfs(&aTree->right, proc);
 }
 }
 
 void rotateLeft(PRBTreeNode *tree) {
 PRBTreeNode aTree = *tree;
 if (aTree) {
 PRBTreeNode right = aTree->right;
 if (right) {
 aTree->right = right->left;
 aTree->right->parent = aTree;
 right->left = aTree;
 right->left->parent = right;
 *tree = right;
 }
 }
 }
 
 void rotateRight(PRBTreeNode *tree) {
 PRBTreeNode aTree = *tree;
 if (aTree) {
 PRBTreeNode left = aTree->left;
 if (left) {
 aTree->left = left->right;
 aTree->left->parent = aTree;
 left->right = aTree;
 left->right->parent = left;
 *tree = left;
 }
 }
 }
 
 int nodelevel(PRBTreeNode *tree, PRBTreeNode node) {
 PRBTreeNode aTree = *tree;
 if (aTree) {
 if (node) {
 int level = 0;
 PRBTreeNode currNode = aTree;
 
 int cmpresult = strcmp(node->key, currNode->key);
 
 while (cmpresult && currNode) {
 if (cmpresult<0) {
 currNode = currNode->left;
 } else {
 currNode = currNode->right;
 }
 level++;
 if (currNode) {
 cmpresult = strcmp(node->key, currNode->key);
 }
 }
 if (currNode) {
 return level;
 }
 }
 }
 return -1;
 }
 
 int childCount(PRBTreeNode *tree) {
 PRBTreeNode aTree = *tree;
 int count = 0;
 if (aTree) {
 if (aTree->left) {
 count = count + 1 + childCount(&aTree->left);
 }
 if (aTree->right) {
 count = count + 1 + childCount(&aTree->right);
 }
 }
 return count;
 }
 
 int leftChildCount(PRBTreeNode *tree) {
 PRBTreeNode aTree = *tree;
 int count = 0;
 if (aTree) {
 if (aTree->left) {
 count = count + 1 + childCount(&aTree->left);
 }
 }
 return count;
 }
 
 int rightChildCount(PRBTreeNode *tree) {
 PRBTreeNode aTree = *tree;
 int count = 0;
 if (aTree) {
 if (aTree->right) {
 count = count + 1 + childCount(&aTree->right);
 }
 }
 return count;
 }
 
 //void balanceTree(PRBTreeNode *tree) {
 //    PRBTreeNode aTree = *tree;
 //    if (aTree) {
 //        int left = leftChildCount(&aTree);
 //        int right = rightChildCount(&aTree);
 //
 //        while (((left-right)>1) || ((right-left)>1)) {
 //            if (left>right) {
 //                rotateRight(&aTree);
 //            } else if (right>left) {
 //                rotateLeft(&aTree);
 //            }
 //            int oldLeft = left;
 //            //            int oldRight = right;
 //            left = leftChildCount(&aTree);
 //            right = rightChildCount(&aTree);
 //
 //            if (((oldLeft - left)>1) || ((left - oldLeft)>1)) {
 //                if (aTree->left) {
 //                    balanceTree(&aTree->left);
 //                }
 //                if (aTree->right) {
 //                    balanceTree(&aTree->right);
 //                }
 //            }
 //        }
 //    }
 //    *tree = aTree;
 //}
 */
void printTreeLvl(PRBTreeNode tree, int level) {
    if (tree) {
        printTreeLvl(tree->left, level+1);
        if (tree->color == RBTreeColorRed) {
            printf("%*s", level*2+1, "+");
        } else {
            printf("%*s", level*2+1, "-");
        }
        defaultPrintKey(tree->key);
        printf("\n");
        printTreeLvl(tree->right, level+1);
    } else {
    }
}

void printTree(PRBTree tree) {
    printTreeLvl(tree->root, 0);
}


void defaultPrintKey(void *key) {
    char *s = (char *)key;
    printf("%s", s);
}

void defaultPrintValue(void *value) {
    char *s = (char *)value;
    printf("%s", s);
}

void defaultFreeKey(void *key) {
    //    free(key);
}

void defaultFreeValue(void *value) {
    //    free(value);
}

int defaultCompareKey(void *keyLeft, void *keyRight) { //result > 0 -> left > right; result < 0 -> left < right
    int cmpresult = strcmp(keyLeft, keyRight);
    return cmpresult;
}

