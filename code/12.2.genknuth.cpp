// 随机数问题：N球抽M奖问题
// 包含了3个原文算法和2个课后习题12.9和12.2（未调试）两个题目的解答
#include <ctime>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include "utility.h"

using namespace std;

// #define PRINTARR
vector<int> arr; // 0~n-1的有序数组，由于抽取样本的样本池



// Kruth 提出的算法 o(n)
vector<int> genKnuth(int m, vector<int> &arr){
    int remainding = arr.size();
    int select = m;
    vector<int> randarr;
    for(auto t : arr){
        if((bigrand() % remainding) < select){ // selct /  remainding 的概率抽中
            randarr.push_back(t);
            --select;
        }
        --remainding;    
        if(select == 0) break;    
    }
    return randarr;
}

// 插入集合算法 o(mlogm)
vector<int> genInSet(int m, vector<int> &arr){
    set<int> pool;
    vector<int> randarr;
    while(pool.size() < m){
        pool.insert(arr[bigrand()%arr.size()]);
    }
    for(auto t : pool) randarr.push_back(t);
    return randarr;
}

// 洗牌算法 o(n)
vector<int> genShuffle(int m, vector<int> &arr){
    vector<int> randarr;
    int n = arr.size();
    for(int i = 0; i < n - 1; ++i){
        int t = randint(i, n - 1);        
        swap(arr[i], arr[t]);
    }
    for(int i = 0; i < m; ++i) randarr.push_back(arr[i]);
    return randarr;

}

// 12.2exce 抽头算法:子集不等概率 o(m)
vector<int> genBigSet(int m, vector<int> &arr){
    vector<int> randarr;
    int n = arr.size();
    int start = bigrand() % n;
    for(int i = 0; i < m; ++i) randarr.push_back(arr[(i + start) % n]);
    return randarr;
}

//12.9exce
vector<int> genfloyd(int m, vector<int> &arr){
    set<int> S;
    set<int>::iterator i;
    int n = arr.size();
    for (int j = n-m; j < n; j++) {
        int t = bigrand() % (j+1);
        if (S.find(t) == S.end())
            S.insert(t); // t not in S
        else
            S.insert(j); // t in S
    }
    for (i = S.begin(); i != S.end(); ++i)
        cout << *i << "\n";
}
void test_n(int randomSample, int m, int chioce){
    arr.resize(randomSample);
    
    for(int i = 0; i < randomSample; ++i) arr[i] = i;
    vector<int> (*prandfunc)(int, vector<int>&) = nullptr; // 指向测试函数
    switch(chioce){
        case 1:
            prandfunc = genKnuth;
            break;
        case 2:
            prandfunc = genInSet;
            break;
        case 3:
            prandfunc = genShuffle;
            break;
        case 4:
            prandfunc = genBigSet;
            break;
        default:
            cout << "\nError! Empty Point\n" << endl;
            return;
    }
    vector<int> times(randomSample);
    vector<int> randomarr;
    int tbegin = clock();
    int tbegin2, tend2, tadd = 0;
    #ifndef PRINTARR
    const int runtimes = 10;
    #else
    const int runtimes = 10000;
    #endif //PRINTARR
    for(int  i = 0;i < runtimes; ++i){
        randomarr = prandfunc(m, arr);
        tbegin2 = clock();
        for(auto t : randomarr) ++times[t];
        tend2 = clock();
        tadd += tend2 - tbegin2;
    }    
    int tend = clock();
    cout <<"Array size:" <<  (double)randomSample <<"\tRandom size:" << std::setw(15)<< (double) m  << "\tTime: " << std::setw(15) <<  (double)(tend - tbegin - tadd) / CLOCKS_PER_SEC * 1000  << "(ms)" \
        << "\t Time in Per Generation: " << (double)(tend - tbegin - tadd) / CLOCKS_PER_SEC * 1000 / runtimes << "(ms)" \
        " \t Add Operation Time: " << (double)((tadd)) / CLOCKS_PER_SEC * 1000  << "(ms)\n";
    #ifdef  PRINTARR
    for(int i = 0; i < times.size(); ++i) 
        cout << i << ":" <<times[i] << '\t'; 
    cout << endl << endl;
    #endif // PRINTARR

}

void test_multy(int arrsize, int chioce){
    for(int i = 10; i < arrsize; i *= 10)
        test_n(arrsize, i, chioce);
}
void  test(int arrsize){
    cout << " KNUTH \n" << endl;
    test_multy(arrsize, 1);
    cout << " IN SET \n" << endl;
    test_multy(arrsize, 2);
    cout << " SHUFFLE\n" << endl;
    test_multy(arrsize, 3);
    cout << " BigSet\n" << endl;
    test_multy(arrsize, 4);
}


int main(){    
    // test for effiency.
    #ifndef PRINTARR
    test(1e8);
    #else
    // test for correctness.
    test(100);
    #endif // PRINTARR

    
    return 0;
}

// // Test outpus:
// g++ ./12.2.genknuth.cpp && ./a.out
//  KNUTH

// Array size:1e+08        Random size:             10     Time:           0.036(ms)        Time in Per Generation: 0.0036(ms)      Add Operation Time: 0.01(ms)
// Array size:1e+08        Random size:            100     Time:           0.225(ms)        Time in Per Generation: 0.0225(ms)      Add Operation Time: 0.036(ms)
// Array size:1e+08        Random size:           1000     Time:           1.177(ms)        Time in Per Generation: 0.1177(ms)      Add Operation Time: 0.147(ms)
// Array size:1e+08        Random size:          10000     Time:          11.363(ms)        Time in Per Generation: 1.1363(ms)      Add Operation Time: 1.467(ms)
// Array size:1e+08        Random size:         100000     Time:         115.858(ms)        Time in Per Generation: 11.5858(ms)     Add Operation Time: 17.353(ms)
// Array size:1e+08        Random size:          1e+06     Time:         1200.42(ms)        Time in Per Generation: 120.042(ms)     Add Operation Time: 174.618(ms)
// Array size:1e+08        Random size:          1e+07     Time:         11745.2(ms)        Time in Per Generation: 1174.52(ms)     Add Operation Time: 1747.88(ms)
//  IN SET

// Array size:1e+08        Random size:             10     Time:           0.095(ms)        Time in Per Generation: 0.0095(ms)      Add Operation Time: 0.02(ms)
// Array size:1e+08        Random size:            100     Time:           0.745(ms)        Time in Per Generation: 0.0745(ms)      Add Operation Time: 0.116(ms)
// Array size:1e+08        Random size:           1000     Time:           9.066(ms)        Time in Per Generation: 0.9066(ms)      Add Operation Time: 0.931(ms)
// Array size:1e+08        Random size:          10000     Time:         103.592(ms)        Time in Per Generation: 10.3592(ms)     Add Operation Time: 7.141(ms)
// Array size:1e+08        Random size:         100000     Time:         1798.91(ms)        Time in Per Generation: 179.891(ms)     Add Operation Time: 73.112(ms)
// Array size:1e+08        Random size:          1e+06     Time:         26935.9(ms)        Time in Per Generation: 2693.59(ms)     Add Operation Time: 528.978(ms)
// Array size:1e+08        Random size:          1e+07     Time:          520162(ms)        Time in Per Generation: 52016.2(ms)     Add Operation Time: 1966.72(ms)
//  SHUFFLE


// Test2 PRINTARR
// g++ ./12.2.genknuth.cpp -DPRINTARR &&./a.out

//   KNUTH 

// Array size:100	Random size:             10	Time:          49.997(ms)	 Time in Per Generation: 0.0049997(ms) 	 Add Operation Time: 10.297(ms)
// 0:1025	1:1024	2:999	3:1011	4:971	5:1027	6:1012	7:1007	8:971	9:999	10:985	11:963	12:1009	13:950	14:1036	15:1038	16:967	17:957	18:996	19:1079	20:997	21:1053	22:990	23:1037	24:1038	25:984	26:1005	27:975	28:1068	29:1005	30:1021	31:977	32:1001	33:1018	34:1010	35:998	36:999	37:1051	38:1009	39:1028	40:1000	41:994	42:954	43:1058	44:1052	45:989	46:969	47:968	48:1001	49:1002	50:998	51:997	52:1036	53:981	54:1032	55:996	56:989	57:1020	58:928	59:985	60:1016	61:988	62:971	63:1007	64:944	65:961	66:992	67:984	68:1022	69:1034	70:1081	71:1003	72:982	73:1007	74:1084	75:969	76:1014	77:989	78:977	79:1005	80:946	81:1024	82:955	83:977	84:1022	85:979	86:946	87:1050	88:1007	89:1026	90:955	91:954	92:941	93:923	94:997	95:1023	96:999	97:994	98:1010	99:1003	

//  IN SET 

// Array size:100	Random size:             10	Time:           77.58(ms)	 Time in Per Generation: 0.007758(ms) 	 Add Operation Time: 10.74(ms)
// 0:1021	1:1013	2:1022	3:1005	4:1022	5:1031	6:1036	7:1012	8:1031	9:983	10:988	11:970	12:999	13:1003	14:1004	15:988	16:1033	17:1022	18:975	19:988	20:1007	21:1029	22:1048	23:987	24:998	25:994	26:1002	27:986	28:984	29:1013	30:981	31:905	32:1060	33:985	34:1010	35:1008	36:1017	37:1004	38:993	39:1053	40:1036	41:986	42:995	43:1006	44:989	45:1018	46:980	47:1009	48:1070	49:1004	50:1001	51:1020	52:1047	53:998	54:1023	55:983	56:997	57:996	58:1023	59:978	60:992	61:1028	62:991	63:944	64:953	65:1028	66:1004	67:1026	68:1015	69:1010	70:963	71:952	72:976	73:971	74:965	75:1003	76:1034	77:958	78:980	79:1012	80:1011	81:944	82:945	83:1055	84:1008	85:961	86:983	87:986	88:979	89:1032	90:991	91:1013	92:918	93:1034	94:954	95:1025	96:1028	97:969	98:981	99:1009	

//  SHUFFLE

// Array size:100	Random size:             10	Time:          62.274(ms)	 Time in Per Generation: 0.0062274(ms) 	 Add Operation Time: 10.066(ms)
// 0:994	1:939	2:985	3:1020	4:991	5:999	6:980	7:1037	8:1105	9:1037	10:973	11:1009	12:981	13:1029	14:1046	15:961	16:987	17:975	18:985	19:1064	20:1061	21:1056	22:982	23:1021	24:993	25:939	26:998	27:987	28:1029	29:994	30:1016	31:989	32:953	33:1046	34:1046	35:1007	36:1007	37:1000	38:989	39:956	40:994	41:987	42:1000	43:996	44:936	45:1016	46:963	47:976	48:979	49:994	50:961	51:1033	52:1010	53:980	54:966	55:1007	56:1048	57:1025	58:958	59:1013	60:1007	61:1023	62:1023	63:955	64:971	65:964	66:997	67:964	68:992	69:985	70:975	71:982	72:987	73:1025	74:1037	75:1014	76:984	77:972	78:1032	79:1000	80:1046	81:960	82:977	83:989	84:997	85:1050	86:1032	87:931	88:1019	89:1040	90:1023	91:979	92:1001	93:1064	94:1022	95:1015	96:1008	97:954	98:995	99:1001	

//  BigSet

// Array size:100	Random size:             10	Time:          25.533(ms)	 Time in Per Generation: 0.0025533(ms) 	 Add Operation Time: 10.036(ms)
// 0:1042	1:1018	2:1019	3:1009	4:1019	5:1024	6:1012	7:994	8:993	9:992	10:974	11:1000	12:1008	13:1027	14:1010	15:994	16:1017	17:1025	18:1016	19:1011	20:1018	21:1013	22:997	23:989	24:1015	25:1021	26:1013	27:1012	28:1003	29:994	30:991	31:986	32:1008	33:993	34:982	35:987	36:985	37:965	38:985	39:988	40:971	41:1000	42:988	43:1011	44:1007	45:1033	46:1030	47:1062	48:1054	49:1050	50:1067	51:1036	52:1035	53:1045	54:1041	55:1021	56:1013	57:972	58:982	59:994	60:987	61:986	62:981	63:948	64:931	65:933	66:937	67:978	68:977	69:968	70:975	71:978	72:987	73:997	74:1025	75:1007	76:996	77:971	78:950	79:946	80:936	81:938	82:955	83:976	84:952	85:951	86:971	87:973	88:1000	89:1018	90:1039	91:1045	92:1022	93:1005	94:1018	95:1029	96:1026	97:1048	98:1040	99:1039	

