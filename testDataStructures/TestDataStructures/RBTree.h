//
//  RBTree.h
//  TestDataStructures
//
//  Created by lim on 3/20/14.
//  Copyright (c) 2014 lim. All rights reserved.
//

#ifndef TestDataStructures_RBTree_h
#define TestDataStructures_RBTree_h

typedef struct RBTreeStruct RBTree;
typedef RBTree *PRBTree;

typedef struct RBTreeNodeStruct RBTreeNode;
typedef RBTreeNode *PRBTreeNode;

typedef enum RBTreeColorEnum RBTreeColor;
enum RBTreeColorEnum {RBTreeColorBlack, RBTreeColorRed};

typedef void *KeyValueProc(char *key, char *value);
typedef void TreeProc(PRBTreeNode *tree);
typedef TreeProc *PTreeProc;

typedef int (*PCompareKeyFunc)(void *left, void *right);
typedef void (*PPrintKeyFunc)(void *key);
typedef void (*PPrintValueFunc)(void *value);
typedef void (*PFreeKeyFunc)(void *key);
typedef void (*PFreeValueFunc)(void *value);
typedef void (*PNodeProcessFunc)(PRBTreeNode treeNode);

struct RBTreeNodeStruct {
    void *key;
    void *value;
    RBTreeColor color;
    PRBTreeNode left;
    PRBTreeNode right;
    PRBTreeNode parent;
};

struct RBTreeStruct {
    PRBTreeNode root;
    //    PRBTreeNode nilNode;
    PCompareKeyFunc compareKey;
    PPrintKeyFunc printKey;
    PPrintValueFunc printValue;
    PFreeKeyFunc freeKey;
    PFreeValueFunc freeValue;
};

PRBTree newRBTree();
PRBTreeNode newRBTreeNode(void *key, void *value);

void setValueForKey(PRBTree tree, void *value, void *key);
void *getValueForKey(PRBTree tree, void *key);
void removeValueForKey(PRBTree tree, void *key);

/*
 // will became private
 
 void rotateLeft(PRBTreeNode *tree);
 void rotateRight(PRBTreeNode *tree);
 
 void bfs(PRBTreeNode *tree, PTreeProc proc);
 void dfs(PRBTreeNode *tree, PTreeProc proc);
 
 int nodelevel(PRBTreeNode *tree, PRBTreeNode node);
 int childCount(PRBTreeNode *tree);
 int leftChildCount(PRBTreeNode *tree);
 int rightChildCount(PRBTreeNode *tree);
 //void balanceTree(PRBTreeNode *tree);
 
 
 */
void printTree(PRBTree tree);
void defaultPrintKey(void *key);
void defaultPrintValue(void *value);

void defaultFreeKey(void *key);
void defaultFreeValue(void *value);

int defaultCompareKey(void *keyLeft, void *keyRight);

void rotateLeft(PRBTree tree, PRBTreeNode node);
void rotateRight(PRBTree tree, PRBTreeNode node);


#endif
