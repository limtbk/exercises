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
    treeNode->color = RBTreeColorRed;
    return treeNode;
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

int nodeParentPosition(PRBTree tree, PRBTreeNode node) { //-1 - left, 1 - right, 0 - no parent
    int result = 0;
    PRBTreeNode parent = node->parent;
    if (parent) {
        result = (parent->left == node)?-1:((parent->right == node)?1:0);
    }
    return  result;
}

void rotateLeft(PRBTree tree, PRBTreeNode node) {
    int parentSide = nodeParentPosition(tree, node);
    PRBTreeNode parent = NULL;
    PRBTreeNode right = NULL;
    PRBTreeNode rightLeft = NULL;
    parent = node->parent;
    right = node->right;
    if (right) { //need to rotate!
        rightLeft = right->left;
        node->parent = right;
        node->right = rightLeft;
        if (rightLeft) {
            rightLeft->parent = node;
        }
        right->left = node;
        right->parent = parent;
        if (parentSide<0) {
            parent->left = right;
        } else if (parentSide>0) {
            parent->right = right;
        } else {
            tree->root = right;
        }
    }
}

void rotateRight(PRBTree tree, PRBTreeNode node) {
    int parentSide = nodeParentPosition(tree, node);
    PRBTreeNode parent = NULL;
    PRBTreeNode left = NULL;
    PRBTreeNode leftRight = NULL;
    parent = node->parent;
    left = node->left;
    if (left) { //need to rotate!
        leftRight = left->right;
        node->parent = left;
        node->left = leftRight;
        if (leftRight) {
            leftRight->parent = node;
        }
        left->right = node;
        left->parent = parent;
        if (parentSide<0) {
            parent->left = left;
        } else if (parentSide>0) {
            parent->right = left;
        } else {
            tree->root = left;
        }
    }
}


void insertCase1(PRBTree tree, PRBTreeNode node);
void insertCase2(PRBTree tree, PRBTreeNode node);
void insertCase3(PRBTree tree, PRBTreeNode node);
void insertCase4l(PRBTree tree, PRBTreeNode node);
void insertCase4r(PRBTree tree, PRBTreeNode node);
void insertCase5l(PRBTree tree, PRBTreeNode node);
void insertCase5r(PRBTree tree, PRBTreeNode node);

void insertCase1(PRBTree tree, PRBTreeNode node) {
    if (!node->parent) {
        node->color = RBTreeColorBlack;
    } else {
        insertCase2(tree, node);
    }
}

void insertCase2(PRBTree tree, PRBTreeNode node) {
    //assume that node not parent
    if (node->parent->color != RBTreeColorBlack) {
        insertCase3(tree, node);
    }
}

void insertCase3(PRBTree tree, PRBTreeNode node) {
    //assume that parent not black, and grandparent present
    PRBTreeNode uncle = nodeUncle(node);
    RBTreeColor uncleColor = uncle?uncle->color:RBTreeColorBlack;
    if (uncleColor == RBTreeColorRed) { //assume, that if uncle color red - uncle exists
        node->parent->color = RBTreeColorBlack;
        uncle->color = RBTreeColorBlack;
        node->parent->parent->color = RBTreeColorRed;
        insertCase1(tree, node->parent->parent);
    } else {
        int nodePos = nodeParentPosition(tree, node->parent);
        if (nodePos<0) { //left branch
            insertCase4l(tree, node);
        } else  if (nodePos>0) { //right branch
            insertCase4r(tree, node);
        } //else error - it cannot be
    }
}

void insertCase4l(PRBTree tree, PRBTreeNode node) {
    int nodePos = nodeParentPosition(tree, node);
    PRBTreeNode parent = node->parent;
    if (nodePos>0) { //right
        rotateLeft(tree, parent);
        insertCase5l(tree, parent);
    } else {
        insertCase5l(tree, node);
    }
}

void insertCase4r(PRBTree tree, PRBTreeNode node) {
    int nodePos = nodeParentPosition(tree, node);
    PRBTreeNode parent = node->parent;
    if (nodePos<0) { //left
        rotateRight(tree, parent);
        insertCase5r(tree, parent);
    } else {
        insertCase5r(tree, node);
    }
}

void insertCase5l(PRBTree tree, PRBTreeNode node) {
    PRBTreeNode parent = node->parent;
    PRBTreeNode grandParent = parent->parent;
    rotateRight(tree, grandParent);
    parent->color = RBTreeColorBlack;
    grandParent->color = RBTreeColorRed;
}

void insertCase5r(PRBTree tree, PRBTreeNode node) {
    PRBTreeNode parent = node->parent;
    PRBTreeNode grandParent = parent->parent;
    rotateLeft(tree, grandParent);
    parent->color = RBTreeColorBlack;
    grandParent->color = RBTreeColorRed;
}

void setValueForKey(PRBTree tree, void *value, void *key) {
    PRBTreeNode node = findNodeInTreeWithKey(tree, key);
    int compareResult = 0;
    if (node) { //case 0: replace value with key instead of insert new value
        compareResult = tree->compareKey(node->key, key);
        if (0 == compareResult) {
            tree->freeValue(node->value);
            node->value = value;
            return;
        }
    }
    PRBTreeNode newNode = newRBTreeNode(key, value);
    if (!node) {
        tree->root = newNode;
    } else if (compareResult>0) {
        node->left = newNode;
        newNode->parent = node;
    } else if (compareResult<0) {
        node->right = newNode;
        newNode->parent = node;
    }
    insertCase1(tree, newNode);
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
//    PRBTreeNode aTree = *tree;
//    if (aTree) {
//        int cmpresult = defaultCompareKey(key, aTree->key);
//        if (cmpresult==0) {
//            if (aTree->left) {
//                if (aTree->right) { // left, right
//                    PRBTreeNode leftXCHG = aTree->left;
//                    PRBTreeNode leftXCHGParent = NULL;
//                    while (leftXCHG->right) {
//                        leftXCHGParent = leftXCHG;
//                        leftXCHG = leftXCHG->right;
//                    }
//                    leftXCHG->right = aTree->right;
//                    leftXCHG->right->parent = leftXCHG;
//                    if (leftXCHGParent) {
//                        leftXCHGParent->right = leftXCHG->left;
//                        leftXCHGParent->right->parent = leftXCHGParent;
//                        leftXCHG->left = aTree->left;
//                        leftXCHG->left->parent = leftXCHG;
//                    }
//                    *tree = leftXCHG;
//                    freeNode(aTree);
//                    
//                } else { //left
//                    *tree = aTree->left;
//                    freeNode(aTree);
//                }
//            } else {
//                if (aTree->right) { //right
//                    *tree = aTree->right;
//                    freeNode(aTree);
//                } else { // none
//                    *tree = NULL;
//                    freeNode(aTree);
//                }
//            }
//        } else if (cmpresult<0) {
//            removeValueForKey(&(aTree->left), key);
//        } else {
//            removeValueForKey(&(aTree->right), key);
//        }
//    }
}

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

