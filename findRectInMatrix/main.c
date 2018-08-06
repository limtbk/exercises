//
//  main.c
//  MatrixRect
//
//  Created by Ivan Klymchuk on 2018-08-01.
//

#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? a : b)
#define MAX(a,b) ((a) > (b) ? a : b)

int gc, sc;

typedef struct IntListStruct {
    int *a;
    int s, p;
} IntList;

typedef struct IntMatrixStruct {
    int *a;
    int m, n, c;
} IntMatrix;

int get(IntMatrix matr, int i, int j) {
    gc++;
    if ((i >= 0) && (j >= 0) && (i < matr.m) && (j < matr.n)) {
        return matr.a[i * matr.n + j];
    }
    return -1;
}

void set(IntMatrix *matr, int i, int j, int v) {
    sc++;
    if ((i >= 0) && (j >= 0) && (i < matr->m) && (j < matr->n)) {
        if (!matr->a[i * matr->n + j] && v) {
            matr->c++;
        }
        matr->a[i * matr->n + j] = v;
    }
}

IntMatrix new(int m, int n) {
    int *a = calloc(m * n, sizeof(int));
    return (IntMatrix){.a = a, .m = m, .n = n, .c = 0};
}

void del(IntMatrix mt) {
    free(mt.a);
    mt.a = 0;
    mt.m = 0;
    mt.n = 0;
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
void testChkLines(void);

int findRect(IntMatrix mt);

int calcNonZeros(IntMatrix mt);

int main(int argc, const char * argv[]) {
    testChkLines();
//    testMatrix();
    return 0;
}




void testMatrix() {
//    int arr[] = {0, 1, 1, 1, 1,
//                 1, 1, 0, 0, 0,
//                 1, 0, 1, 0, 0,
//                 1, 0, 0, 1, 0,
//                 1, 0, 0, 0, 1,
//    };
//    IntMatrix mt = {.a = arr, .m = 5, .n = 5};

//    int arr[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//                 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
//                 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
//                 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
//                 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
//                 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
//                 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
//                 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
//                 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
//                 1, 0, 0, 0, 0, 0, 0, 0, 0, 1
//    };
//    IntMatrix mt = {.a = arr, .m = 10, .n = 10};
    
    int arr[] = {
        0, 0, 1, 1, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
        1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 1, 0, 1, 0, 1, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
        1, 1, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 1, 1, 0
    };
    IntMatrix mt = {.a = arr, .m = 10, .n = 10};



    gc = 0;
    sc = 0;
    int result = findRect(mt);
    printf("\n%s\nreads=%i writes=%i\n", result?"YES":"NO", gc, sc);
    print(mt);
    printf("\n");
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

void chkLines(IntMatrix *mt, ii, jj) {
    for (int i = 0; i < mt->m; i++) {
        if ((i != ii) && (get(*mt, i, jj) == 1)) {
            for (int j = 0; j < mt->n; j++) {
                if (j != jj) {
                    if (get(*mt, ii, j) == 1) {
                        set(mt, i, j, -1);
                    }
                    if (get(*mt, i, j) == 1) {
                        set(mt, ii, j, -1);
                    }
                }
            }
        }
    }
    for (int j = 0; j < mt->n; j++) {
        if ((j != jj) && (get(*mt, ii, j) == 1)) {
            for (int i = 0; i < mt->m; i++) {
                if (i != ii) {
                    if (get(*mt, i, jj) == 1) {
                        set(mt, i, j, -1);
                    }
                    if (get(*mt, i, j) == 1) {
                        set(mt, i, jj, -1);
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
//    if (k > (mt.m + mt.n + MIN(mt.m, mt.n) - 3)) {
//        return 1;
//    }
    
    IntMatrix mp = new(mt.m, mt.n);
//    print(mp);

    for (int i = 0; i < mt.m; i++) {
        for (int j = 0; j < mt.n; j++) {
            if (get(mt, i, j) == 1) {
                if (get(mp, i, j) != 0) {
                    return 1;
                } else {
                    set(&mp, i, j, 1);
                    chkLines(&mp, i, j);
//                    printf("\n");
//                    print(mp);
                }
            }
        }
    }
    
    return 0;
}

void testChkLines() {
    
    IntMatrix res = new(30, 30);
    
    for (int ni = 2; ni < 31; ni++) {
        for (int mi = ni; mi < 31; mi++) {
            
            int maxn = 0;
            
            for (int l = 0; l < 10000; l++) {
                IntMatrix mt = new(mi, ni);
                
                int n = 0;
                
                while (mt.c < ni * mi) {
                    int i = arc4random() % mt.m;
                    int j = arc4random() % mt.n;
                    if (get(mt, i, j) == 0) {
                        set(&mt, i, j, 1);
                        chkLines(&mt, i, j);
                        n++;
//                        printf("\n");
//                        print(mt);
                    }
                }
                if (maxn < n) {
                    maxn = n;
                    printf("\n");
                    print(mt);
                    printf("\n%ix%i %i\n", mt.m, mt.n, n);
                }
                del(mt);
            }
         
            set(&res, mi-2, ni-2, maxn);
            set(&res, ni-2, mi-2, maxn);

        }
    }
    printf("\n");
    print(res);


}
