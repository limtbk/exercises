//
//  testTrees.c
//  TestDataStructures
//
//  Created by lim on 3/20/14.
//  Copyright (c) 2014 lim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

char *randString(int len) {
    char *result = malloc(len+1);
    result[len] = 0;
    for (size_t i = 0; i < len; i++) {
        result[i] = (arc4random() & 0x0F) + '0';
//        result[i] = (rand() & 0x0F) + '0';
        if (result[i]>'9') {
            result[i] += 'A' - '0' - 10;
        }
    }
    return result;
}

void printKeyValue(PRBTreeNode *tree) {
    PRBTreeNode aTree = *tree;
    printf("%s : %s\n", aTree->key, aTree->value);
}

void rbTreeTest() {
    PRBTree tree = newRBTree();
    
    setValueForKey(tree, "A", "0003");
    setValueForKey(tree, "A", "0005");
    setValueForKey(tree, "A", "0008");
    setValueForKey(tree, "A", "0010");
    setValueForKey(tree, "A", "0013");
    setValueForKey(tree, "A", "0015");
    setValueForKey(tree, "A", "0018");
    setValueForKey(tree, "A", "0019");
    setValueForKey(tree, "A", "0020");
    setValueForKey(tree, "A", "0021");
    setValueForKey(tree, "A", "0022");
    setValueForKey(tree, "A", "0023");
    setValueForKey(tree, "A", "0024");
    setValueForKey(tree, "A", "0025");

    printf("\n"); printTree(tree); printf("\n");
     
    for (int i = 0; i < 1024; i++) {
        setValueForKey(tree, randString(16), randString(4));
    }
    printf("\n"); printTree(tree); printf("\n");

    removeValueForKey(tree, "0025");
    printf("\n"); printTree(tree); printf("\n");
}