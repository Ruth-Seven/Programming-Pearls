#include <ctime>
#include <cstdio>
#include <iostream>
#include <vector>
#include "utility.h"

using namespace std;

#define MAX(a, b) ((a) > (b)) ? a : b

int arr[2000];

int getmaxelement(int arr[], int len){
    if(len <= 1) return arr[0];
    else return MAX(getmaxelement(arr, len - 1), arr[len - 1]);
}

void test_n(int n){

    for(int i = 0; i < n; ++i) arr[i] = rand() %  n;
    int tbegin = clock();
    int maxv = getmaxelement(arr, n);
    int tend = clock();
    cout <<"Array size:" <<  n << " \t Time: " << (double)(tend - tbegin) / CLOCKS_PER_SEC * 1000  << "(ms)"<< "\t Max elements:" << maxv << endl;

}

void  test(){
    for(int i = 0; i < 1000; i += 5)
        test_n(i);
}
int main(){
    test();
    return 0;
}

// Test outpus:
// Array size:0     Time: 0.001(ms)         Max elements:0
// Array size:5     Time: 0.002(ms)         Max elements:3
// Array size:10    Time: 0.002(ms)         Max elements:9
// Array size:15    Time: 0.008(ms)         Max elements:13
// Array size:20    Time: 1.331(ms)         Max elements:19
// Array size:25    Time: 26.415(ms)        Max elements:24
// Array size:30    Time: 1993.75(ms)       Max elements:29
// Array size:35    Time: 5824.36(ms)       Max elements:34
// Array size:40    Time: 887292(ms)        Max elements:36
// Afer many many minutes, there were no more outputs before i closed.
