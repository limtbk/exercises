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
        //        result[i] = (arc4random() & 0x0F) + '0';
        result[i] = (rand() & 0x0F) + '0';
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
    //    int a = strcmp("1236", "1235");
    
    PRBTree tree = newRBTree();
    
    setValueForKey(tree, "A", "0010");
    setValueForKey(tree, "A", "0005");
    setValueForKey(tree, "A", "0015");
    setValueForKey(tree, "A", "0003");
    setValueForKey(tree, "A", "0008");
    setValueForKey(tree, "A", "0013");
    setValueForKey(tree, "A", "0018");
    /*
     printf("\n"); printTree(tree); printf("\n");
     
     rotateLeft(tree, tree->root->left->left);
     
     printf("\n"); printTree(tree); printf("\n");
     
     rotateLeft(tree, tree->root->left);
     
     printf("\n"); printTree(tree); printf("\n");
     
     rotateLeft(tree, tree->root->left);
     
     printf("\n"); printTree(tree); printf("\n");
     
     rotateRight(tree, tree->root);
     
     printf("\n"); printTree(tree); printf("\n");
     
     rotateRight(tree, tree->root);
     
     printf("\n"); printTree(tree); printf("\n");
     
     rotateRight(tree, tree->root);
     
     printf("\n"); printTree(tree); printf("\n");
     
     rotateRight(tree, tree->root);
     
     printf("\n"); printTree(tree); printf("\n");
     
     rotateRight(tree, tree->root);
     
     printf("\n"); printTree(tree); printf("\n");
     */
    for (int i = 0; i < 10; i++) {
        setValueForKey(tree, randString(16), randString(4));
        
        printf("\n"); printTree(tree); printf("\n");
    }
    
    setValueForKey(tree, "value1", "AAA1");
    setValueForKey(tree, "value2", "AAA2");
    setValueForKey(tree, "value3", "AAA3");
    setValueForKey(tree, "value4", "AAA4");
    setValueForKey(tree, "value5", "AAA5");
    setValueForKey(tree, "value6", "AAA6");
    setValueForKey(tree, "value7", "AAA7");
    setValueForKey(tree, "value8", "AAA8");
    setValueForKey(tree, "value9", "AAA9");
    setValueForKey(tree, "valueA", "AAAA");
    setValueForKey(tree, "valueB", "AAAB");
    //    balanceTree(&tree);
    //    balanceTree(&tree->left);
    //    balanceTree(&tree->right);
    
    //    PTreeProc printTreePtr = &printKeyValue;
    //    dfs(&tree, printTreePtr);
    //    bfs(&tree, printTreePtr);
    
    
    printf("%s\n", getValueForKey(tree, "AAA1"));
    printf("%s\n", getValueForKey(tree, "AAA2"));
    printf("%s\n", getValueForKey(tree, "AAA3"));
    printf("%s\n", getValueForKey(tree, "AAA4"));
    printf("%s\n", getValueForKey(tree, "AAA5"));
    
    //    printTree(&treeNode);
    printf("\n");
    
    removeValueForKey(tree, "AAA3");
    //    removeValueForKey(&tree, "key4");
    
    //    printTree(&tree);
    printf("\n");
    
    printf("%s\n", getValueForKey(tree, "AAA1"));
    printf("%s\n", getValueForKey(tree, "AAA2"));
    printf("%s\n", getValueForKey(tree, "AAA3"));
    printf("%s\n", getValueForKey(tree, "AAA4"));
    printf("%s\n", getValueForKey(tree, "AAA5"));
    
}