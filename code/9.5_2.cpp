
/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* genbins.c -- generate random numbers with bins */

/* If NODESIZE is 8, this program uses the special-case malloc.
   Change NODESIZE to 0 to use the system malloc.
 */

// Modified by ove in 2021-05-10 10:54:09
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utility.h"
using  namespace std;

// #define PROFILING
#define NODESIZE 8
#define NODEGROUP 100000
int nodesleft = 0;
char *freenode;

void *pmalloc(int size)
{	void *p;
	if (size != NODESIZE)
		return malloc(size);
	if (nodesleft == 0) {
		freenode = (char *)malloc(NODEGROUP*NODESIZE);
		nodesleft = NODEGROUP;
	}
	nodesleft--;
	p = (void *) freenode;
	freenode += NODESIZE;
	return p;
}

struct node {
	int val;
	struct node *next;
};

struct node **bin, *sentinel;
int bins, bincnt, maxval;

void initbins(int maxelms, int pmaxval)
{	int i;
	bins = maxelms;
	maxval = pmaxval;
	bin = (struct node **)pmalloc(bins*sizeof(struct node *));
	sentinel = (struct node *)pmalloc(sizeof(struct node));
	sentinel->val = maxval;
	for (i = 0; i < bins; i++)
		bin[i] = sentinel; // 插入排序比较的哨兵
	bincnt = 0;
}

// 升序插入
struct node *rinsert(struct node *p, int t)
{	if (p->val < t) {
		p->next = rinsert(p->next, t);
	} else if (p->val > t) {
        #ifdef TEST_PMALLOC
        // cout << '@';
		struct node *q = (struct node *)pmalloc(sizeof(struct node));
        #else 
        // cout << '#';
        struct node *q = (struct node *)malloc(sizeof(struct node));
        #endif //TEST_MALLOC
		q->val = t;
		q->next = p;
		p = q;
		bincnt++;
	}
	return p;
}

void insert(int t)
{	int i = rand() % bins;
	// i = t / (1 + maxval/bins);
	bin[i] = rinsert(bin[i], t);
}

void report()
{	int i, j = 0;
	struct node *p;
	for (i = 0; i < bins; i++){
		for (p = bin[i]; p != sentinel; p = p->next)
    #ifdef  PROFILING
        {
            printf("%d ", p->val);
			/* Uncomment for testing, comment for profiling */
        }
        printf("\n");
    #else
    ;
    #endif
    }
}

inline int bigrand()
{	return RAND_MAX*rand() + rand();
}

// set rand pattern in seed of time sticks.
__attribute__((constructor))
void __register_rand_time(){    
    srand(time(0));
}


// test timing

void test_M(int m, int n){
    // test 
    int tbegin = clock();
    initbins(m, n);
	while (bincnt < m) {
		insert(bigrand() % n);
	}
	report();    
    int tend = clock();
    cout <<"Bin size:" <<  (double)m << "\tMaxValue:" << n << " \t Time: " << (double)(tend - tbegin) / CLOCKS_PER_SEC * 1000  << "(ms)" << endl;

}

void  test(){
    int m  = 8000;
    int n = 200;
    for(int i = 100; i < 1e8 + 1; i *= 10)
        test_M(i, 200);
}


int main(int argc, char *argv[])
{	
    test();
    return 0;
}


// Test Step:
// ```shell
//  # test_malloc
//  g++  9.5._2.cpp -o 9.5._2  && 9.5._2
//  # test_pmalloc
//  g++  9.5._2.cpp -o 9.5._2 -DTEST_PMALLOC && 9.5._2
//  ```

// if #define NODEGROUP 1000
// Test test_malloc
// Bin size:100    MaxValue:200     Time: 0.045(ms)
// Bin size:1000   MaxValue:200     Time: 3.229(ms)
// Bin size:10000  MaxValue:200     Time: 1.804(ms)
// Bin size:100000 MaxValue:200     Time: 26.283(ms)
// Bin size:1e+06  MaxValue:200     Time: 288.53(ms)
// Bin size:1e+07  MaxValue:200     Time: 3539.9(ms)
// Bin size:1e+08  MaxValue:200     Time: 53074(ms)

// Test test_pmalloc
// Bin size:100    MaxValue:200     Time: 0.013(ms)
// Bin size:1000   MaxValue:200     Time: 0.219(ms)
// Bin size:10000  MaxValue:200     Time: 1.598(ms)
// Bin size:100000 MaxValue:200     Time: 28.929(ms)
// Bin size:1e+06  MaxValue:200     Time: 279.765(ms)
// Bin size:1e+07  MaxValue:200     Time: 3552.48(ms)
// Bin size:1e+08  MaxValue:200     Time: 54538.1(ms)


// if #define NODEGROUP 100000
// Test test_malloc
// Bin size:100    MaxValue:200     Time: 0.013(ms)
// Bin size:1000   MaxValue:200     Time: 0.132(ms)
// Bin size:10000  MaxValue:200     Time: 2.127(ms)
// Bin size:100000 MaxValue:200     Time: 24.761(ms)
// Bin size:1e+06  MaxValue:200     Time: 318.766(ms)
// Bin size:1e+07  MaxValue:200     Time: 4071.11(ms)
// Bin size:1e+08  MaxValue:200     Time: 53068.4(ms)

// Test test_pmalloc
// Bin size:100    MaxValue:200     Time: 0.012(ms)
// Bin size:1000   MaxValue:200     Time: 0.132(ms)
// Bin size:10000  MaxValue:200     Time: 1.528(ms)
// Bin size:100000 MaxValue:200     Time: 36.736(ms)
// Bin size:1e+06  MaxValue:200     Time: 293.315(ms)
// Bin size:1e+07  MaxValue:200     Time: 3656(ms)
// Bin size:1e+08  MaxValue:200     Time: 53105.3(ms)

// 对于大数据只有，勉强10% 性能提升，而且不稳定
// 可惜只是简单的设计一个malloc优化，还不够，内存分配优化策略还有内存释放的部分。已经有的方案是SGI STL的二级缓存方案