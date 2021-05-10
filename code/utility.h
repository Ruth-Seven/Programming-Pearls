
#ifndef UTILITY_H
#define UTILITY_H
#include <random>
#include <ctime>

#if	RAND_MAX == 2147483647 //The max value of rand is dependent with LIBRAIES.

inline int  bigrand(){
    return rand(); //避免取余
}

#else 
inline long long  bigrand(){
    return (long long) RAND_MAX * rand() + rand(); //避免取余
}

#endif

inline int randint(int low, int height){
    
    return low + bigrand() % (height - low + 1);
}


// set rand pattern in seed of time sticks.
__attribute__((constructor))
void __register_rand_time(){    
    srand(time(0));
}




#endif //UTILITY_H