//
//  main.c
//  MatrixRect
//
//  Created by Ivan Klymchuk on 2018-08-01.
//

#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? a : b)

int gc, sc;

typedef struct IntMatrixStruct {
    int *a;
    int m, n;
} IntMatrix;

int get(IntMatrix matr, int i, int j) {
    gc++;
    if ((i >= 0) && (j >= 0) && (i < matr.m) && (j < matr.n)) {
        return matr.a[i * matr.n + j];
    }
    return -1;
}

void set(IntMatrix matr, int i, int j, int v) {
    sc++;
    if ((i >= 0) && (j >= 0) && (i < matr.m) && (j < matr.n)) {
        matr.a[i * matr.n + j] = v;
    }
}

IntMatrix new(int m, int n) {
    int *a = calloc(m * n, sizeof(int));
    return (IntMatrix){.a = a, .m = m, .n = n};
}

void print(IntMatrix mt) {
    for (int i = 0; i < mt.m; i++) {
        for (int j = 0; j < mt.n; j++) {
            int v = get(mt, i, j);
            printf("%2i ", v);
        }
        printf("\n");
    }
}

void testMatrix(void);

int findRect(IntMatrix mt);

int calcNonZeros(IntMatrix mt);

int main(int argc, const char * argv[]) {
    testMatrix();
    return 0;
}

void testMatrix() {
    int arr[] = {0, 1, 1, 1, 1,
                 1, 1, 0, 0, 0,
                 0, 0, 1, 0, 1,
                 1, 0, 0, 1, 0,
                 1, 0, 1, 0, 0};
    
    IntMatrix mt = {.a = arr, .m = 5, .n = 5};
    
    gc = 0;
    sc = 0;
    int result = findRect(mt);
    printf("\n");
    print(mt);
    printf("\n%s\nreads=%i writes=%i\n", result?"YES":"NO", gc, sc);
}

int calcNonZeros(IntMatrix mt) {
    int result = 0;
    for (int i = 0; i < mt.m; i++) {
        for (int j = 0; j < mt.n; j++) {
            result += (get(mt, i, j) != 0) ? 1 : 0;
        }
    }
    return result;
}

void chkLines(IntMatrix mt, ii, jj) {
    for (int i = 0; i < mt.m; i++) {
        if ((i != ii) && (get(mt, i, jj) == 1)) {
            for (int j = 0; j < mt.n; j++) {
                if (j != jj) {
                    if (get(mt, ii, j) == 1) {
                        set(mt, i, j, -1);
                    }
                    if (get(mt, i, j) == 1) {
                        set(mt, ii, j, -1);
                    }
                }
            }
        }
    }
}

int findRect(IntMatrix mt) {
    int k = calcNonZeros(mt);
    if (k < 4) {
        return 0;
    }
    if (k > (mt.m + mt.n + MIN(mt.m, mt.n) - 3)) {
        return 1;
    }
    
    IntMatrix mp = new(mt.m, mt.n);
//    print(mp);

    for (int i = 0; i < mt.m; i++) {
        for (int j = 0; j < mt.n; j++) {
            if (get(mt, i, j) == 1) {
                if (get(mp, i, j) != 0) {
                    return 1;
                } else {
                    set(mp, i, j, 1);
                    chkLines(mp, i, j);
//                    printf("\n");
//                    print(mp);
                }
            }
        }
    }
    
    return 0;
}

