// 12.9 水库抽样问题，K=1;

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


vector<int> arr(2000);

// 水库抽样算法
static int times = 0;

void onlineRandomKcasesClear(){
    times = 0;
}

void onlineRandomKcases(int sample, int k, vector<int> &ans){
    ++times;
    int t =  bigrand() %  times;
    if(times <= k) ans[times - 1] = sample;
    else if(t < k) ans[t] = sample;
 
}

void test_n(int randomSample, int K){
    vector<int> times;
    times.resize(randomSample);
    const int runtimes = 100000;
    
    int tbegin2, tend2, tadd = 0;
    int tbegin = clock();    
    for(int  i = 0; i < runtimes; ++i){
        vector<int> randarr(K);
        onlineRandomKcasesClear();
        for(int j = 0; j < randomSample; ++j){
            onlineRandomKcases(j, K, randarr);            
        } 
        tbegin2 = clock();
        for(auto t : randarr) ++times[t];        
        tend2 = clock();
        tadd += tend2 - tbegin2;
    }    
    int tend = clock();
    cout <<"Array size:" <<  (double)randomSample <<"\tRandom size:" << std::setw(10)<< (double) K << "\tTime: " << std::setw(15) <<  (double)(tend - tbegin - tadd) / CLOCKS_PER_SEC * 1000  << "(ms)" \
        << "\t Time in Per Generation: " << (double)(tend - tbegin - tadd) / CLOCKS_PER_SEC * 1000 / runtimes << "(ms)" \
        " \t Add Operation Time: " << (double)((tadd)) / CLOCKS_PER_SEC * 1000  << "(ms)\n";
    #ifdef  PRINTARR
    for(int i = 0; i < times.size(); ++i) 
        cout << i << ":" <<times[i] << '\t'; 
    cout << endl << endl;
    #endif // PRINTARR

}

void  test(int n){
    for(int i = 10; i < n; i *= 10)
        test_n(i, i / 10);        
}
int main(){
    // test for effiency.
    #ifndef PRINTARR
    test(1e9);
    #else
    // test for correctness.
    test(1e4);
    #endif // PRINTARR

    return 0;
}

// // Test outpus:
 
// ❯ g++ ./12.10.cpp&& ./a.out
// Array size:10   Random size:         1  Time:         120.414(ms)        Time in Per Generation: 0.00120414(ms)          Add Operation Time: 82.865(ms)
// Array size:100  Random size:        10  Time:          345.74(ms)        Time in Per Generation: 0.0034574(ms)   Add Operation Time: 107.556(ms)
// Array size:1000 Random size:       100  Time:         2712.03(ms)        Time in Per Generation: 0.0271203(ms)   Add Operation Time: 273.603(ms)


// ❯ g++ ./12.10.cpp -DPRINTARR && ./a.out
// Array size:10   Random size:         1  Time:          119.04(ms)        Time in Per Generation: 0.0011904(ms)   Add Operation Time: 79.856(ms)
// 0:9979  1:9905  2:10020 3:10047 4:9915  5:10079 6:10100 7:9971  8:9994  9:9990

// Array size:100  Random size:        10  Time:         347.006(ms)        Time in Per Generation: 0.00347006(ms)          Add Operation Time: 107.514(ms)
// 0:9988  1:9961  2:10029 3:9981  4:10005 5:9903  6:10058 7:9744  8:9929  9:10019 10:9826 11:9816 12:9927 13:10021        14:9924 15:10004        16:10033        17:10036        18:9943 19:9944     20:10128        21:10137        22:10005        23:9969 24:10056        25:9993 26:9915 27:10157        28:10032        29:10054        30:10118        31:9863 32:10198        33:10035    34:9808 35:10054        36:10046        37:9889 38:9827 39:9999 40:10061        41:9855 42:10039        43:10221        44:10115        45:9859 46:10142        47:9986 48:10132   49:10029 50:10258        51:9976 52:10056        53:10103        54:10022        55:9815 56:9943 57:10098        58:9877 59:10074        60:10019        61:9919 62:9926 63:10148        64:9919     65:10070        66:10071        67:9970 68:10167        69:10067        70:10113        71:10009        72:9746 73:9867 74:10002        75:10182        76:10082        77:10039   78:10083 79:9859 80:10092        81:10122        82:9947 83:10049        84:10071        85:10017        86:9913 87:10039        88:9856 89:9947 90:9918 91:9859 92:9930 93:10048        94:10084    95:9989 96:9892 97:9964 98:10019        99:9951

// Array size:1000 Random size:       100  Time:         2505.42(ms)        Time in Per Generation: 0.0250542(ms)   Add Operation Time: 263.797(ms)
// 0:9947  1:9936  2:9947  3:10088 4:10191 5:10033 6:9943  7:10117 8:10078 9:10179 10:9965 11:10088        12:9952 13:10006        14:9978 15:10004        16:10092        17:10190        18:9967     19:10088        20:9983 21:9858 22:10185        23:10057        24:9905 25:9841 26:9943 27:10055        28:9866 29:9941 30:10063        31:10015        32:9950 33:9922 34:9898 35:10030    36:10105        37:10047        38:10013        39:10004        40:10023        41:9905 42:9929 43:10020        44:9983 45:10023        46:9884 47:10011        48:10078        49:9837     50:9949 51:10120        52:9894 53:9780 54:9892 55:9923 56:9950 57:10173        58:9990 59:9914 60:10091        61:10044        62:10103        63:10058        64:9806 65:9908 66:9997     67:9940 68:9927 69:10053        70:10012        71:9896 72:9950 73:10014        74:10076        75:9992 76:9950 77:9899 78:9860 79:9923 80:9968 81:9912 82:9972 83:9972 84:9977 85:9883     86:10005        87:9919 88:10026        89:10039        90:10018        91:9975 92:9911 93:10128        94:10093        95:9872 96:10108        97:10027        98:10167        99:9976     100:10050       101:10038       102:10067       103:9925        104:9908        105:10041       106:9797        107:9879        108:10141       109:9999        110:10003       111:9997    112:9982        113:10104       114:10089       115:10146       116:9983        117:9960        118:9973        119:9948        120:9910        121:10131       122:9993        123:9930    124:10019       125:10061       126:10115       127:9925        128:9924        129:10016       130:9891        131:10071       132:9895        133:9917        134:10113       135:10055   136:9988        137:10050       138:10048       139:9836        140:10074       141:10096       142:10017       143:9967        144:9905        145:10068       146:9963        147:10153   148:10217       149:9948        150:9982        151:9814        152:9897        153:9840        154:9912        155:9982        156:10075       157:9840        158:10101       159:9925    160:10003       161:10045       162:9869        163:9961        164:10115       165:10090       166:9982        167:9865        168:10110       169:9960        170:10013       171:10096   172:9926        173:10092       174:9688        175:10092       176:10147       177:10211       178:9934        179:10059       180:9924        181:9962        182:9809        183:10152   184:9990        185:10112       186:9925        187:10189       188:10063       189:10082       190:10246       191:9965        192:9984        193:10013       194:9910        195:9866    196:9780        197:9985        198:10026       199:10033       200:9946        201:10024       202:9869        203:9807        204:10028       205:10106       206:9989        207:10044   208:9854        209:10005       210:9989        211:10082       212:9946        213:10114       214:9918        215:10200       216:10047       217:10157       218:10072       219:9864    220:10115       221:10067       222:9949        223:10157       224:9882        225:10164       226:9925        227:9836        228:10000       229:10012       230:9918        231:9886    232:10096       233:10042       234:10144       235:9836        236:10082       237:10041       238:10090       239:10051       240:10016       241:9910        242:10135       243:9997    244:10056       245:9890        246:9935        247:10178       248:9920        249:10055       250:9946        251:10021       252:10005       253:10129       254:10052       255:10089   256:9982        257:10175       258:9883        259:10061       260:9822        261:9879        262:10089       263:10061       264:9990        265:10133       266:10037       267:10034   268:9805        269:9992        270:10021       271:9999        272:10039       273:9853        274:10006       275:9991        276:10020       277:10005       278:9900        279:10054   280:10038       281:9975        282:9874        283:10057       284:10047       285:9979        286:10158       287:10052       288:10088       289:9933        290:9867        291:10071   292:10119       293:9957        294:10063       295:10006       296:10127       297:10033       298:9896        299:10155       300:9879        301:9947        302:10044       303:9867    304:10023       305:9927        306:9922        307:9837        308:9968        309:9995        310:10138       311:9937        312:10043       313:9989        314:10132       315:9928    316:10063       317:9981        318:10054       319:10101       320:10032       321:9961        322:10076       323:9958        324:9879        325:10035       326:9951        327:9922    328:9953        329:10126       330:10026       331:10111       332:9847        333:10179       334:10064       335:9987        336:9975        337:9931        338:10120       339:9920    340:10070       341:9883        342:9885        343:9897        344:10112       345:9962        346:9974        347:10007       348:10021       349:10106       350:9822        351:9948    352:10148       353:10088       354:10032       355:9995        356:10010       357:9946        358:10024       359:10020       360:9990        361:9965        362:10073       363:10002   364:9944        365:10025       366:9893        367:10132       368:10060       369:9853        370:10136       371:9931        372:9898        373:10164       374:9917        375:9963    376:9894        377:10133       378:9813        379:10001       380:9990        381:9969        382:9862        383:10052       384:9975        385:10021       386:9888        387:9968    388:10022       389:10042       390:9889        391:9872        392:10092       393:9983        394:9888        395:10067       396:10088       397:9943        398:9936        399:10201   400:9945        401:10017       402:9870        403:9979        404:9895        405:9999        406:10064       407:10035       408:10031       409:10030       410:10021       411:9834    412:10049       413:9943        414:10006       415:9974        416:10120       417:9951        418:9889        419:10038       420:10152       421:10085       422:9973        423:9931    424:10048       425:10158       426:10162       427:10198       428:9998        429:9985        430:10074       431:10117       432:9982        433:9918        434:9947        435:9932    436:10131       437:9926        438:10010       439:10110       440:10060       441:10004       442:10020       443:10173       444:9958        445:9869        446:10127       447:10000   448:10166       449:10021       450:10130       451:9943        452:9860        453:10021       454:9994        455:9947        456:10223       457:9910        458:9919        459:10001   460:10019       461:9953        462:9898        463:10183       464:10093       465:9856        466:10128       467:10075       468:10021       469:9874        470:10212       471:10110   472:9996        473:10051       474:9872        475:9966        476:9882        477:10041       478:10089       479:10038       480:9970        481:9864        482:9986        483:9988    484:9974        485:10121       486:9897        487:9915        488:10037       489:10103       490:10062       491:10020       492:10038       493:9982        494:10026       495:9916    496:9873        497:10055       498:10059       499:10003       500:9848        501:9868        502:10090       503:9936        504:9930        505:10083       506:9929        507:10048   508:10069       509:9896        510:9942        511:10164       512:10049       513:10123       514:10098       515:10159       516:10134       517:9919        518:9885        519:9994    520:10089       521:9931        522:9909        523:9993        524:10094       525:9992        526:9790        527:9960        528:10141       529:9871        530:9926        531:9961    532:9863        533:9936        534:9975        535:9965        536:9942        537:10102       538:10026       539:9900        540:10061       541:9851        542:9942        543:9851    544:10003       545:9776        546:10042       547:10142       548:9972        549:9990        550:9950        551:10054       552:9962        553:9965        554:10031       555:10098   556:9921        557:9803        558:10027       559:9849        560:9898        561:9893        562:10071       563:10046       564:9927        565:10042       566:9928        567:9935    568:9854        569:9885        570:9906        571:10129       572:10006       573:10079       574:9944        575:9928        576:9920        577:9991        578:10023       579:10018   580:10124       581:10039       582:9939        583:10233       584:10138       585:10040       586:10039       587:9969        588:9866        589:9869        590:10045       591:10100   592:9958        593:10021       594:9974        595:9857        596:10118       597:10085       598:10052       599:9948        600:9916        601:9974        602:10017       603:10084   604:9980        605:9901        606:10115       607:10094       608:10139       609:10196       610:9937        611:9886        612:9970        613:9974        614:9980        615:9925    616:9972        617:9889        618:9946        619:9991        620:10160       621:10086       622:10100       623:10214       624:10048       625:9748        626:10049       627:10029   628:9969        629:10014       630:9956        631:10007       632:9998        633:10206       634:9912        635:10149       636:10159       637:10074       638:9980        639:10247   640:10123       641:10008       642:9862        643:10119       644:10000       645:9860        646:10073       647:10052       648:9973        649:9803        650:9892        651:9960    652:10057       653:10047       654:10252       655:9864        656:9985        657:10008       658:10005       659:9998        660:10202       661:10134       662:9896        663:10085   664:9873        665:10057       666:10173       667:9957        668:9986        669:10057       670:10049       671:9934        672:10151       673:10005       674:10138       675:10080   676:10062       677:9998        678:10012       679:10094       680:9974        681:10045       682:10072       683:10104       684:10005       685:9987        686:10047       687:9911    688:9982        689:9769        690:9885        691:9915        692:10113       693:9815        694:9936        695:10153       696:9897        697:9986        698:10000       699:9967    700:10124       701:10021       702:9915        703:10023       704:9983        705:10055       706:10039       707:9834        708:9853        709:10115       710:9954        711:10008   712:9831        713:10038       714:9851        715:10097       716:10006       717:10054       718:9954        719:10180       720:9903        721:10002       722:9943        723:9936    724:9877        725:9996        726:10083       727:10116       728:10046       729:9945        730:10165       731:9974        732:9923        733:10051       734:10020       735:10023   736:9912        737:9947        738:10023       739:10056       740:9995        741:9848        742:9889        743:9963        744:10075       745:9972        746:10084       747:9970    748:10013       749:9938        750:9947        751:10110       752:9741        753:10097       754:9945        755:9926        756:9939        757:9918        758:10118       759:10027   760:10077       761:10168       762:9968        763:10083       764:9875        765:9951        766:9896        767:10184       768:10047       769:10017       770:9885        771:10037   772:10133       773:9966        774:10036       775:10118       776:9977        777:9878        778:10110       779:10051       780:9979        781:10050       782:9873        783:10000   784:10159       785:9906        786:9910        787:10004       788:9915        789:10118       790:10051       791:9924        792:10092       793:10066       794:9937        795:9893    796:10025       797:9958        798:9976        799:9995        800:10137       801:9861        802:9922        803:9959        804:10092       805:10147       806:9928        807:10099   808:10033       809:9892        810:10099       811:9976        812:10076       813:9995        814:9992        815:9950        816:10055       817:10179       818:9999        819:10002   820:10096       821:10090       822:9879        823:10089       824:10009       825:10021       826:9836        827:10079       828:10063       829:9943        830:10038       831:10045   832:10019       833:10288       834:9938        835:10079       836:9771        837:10152       838:10000       839:9882        840:10042       841:10064       842:10010       843:10162   844:10059       845:10058       846:10131       847:10160       848:10022       849:9997        850:10103       851:9965        852:9873        853:10041       854:9995        855:10027   856:10012       857:9988        858:9957        859:10015       860:9991        861:10053       862:10000       863:10125       864:10089       865:10048       866:9917        867:10129   868:10081       869:10067       870:9913        871:10081       872:9796        873:9854        874:10093       875:10082       876:10047       877:9952        878:10133       879:9974    880:9760        881:10059       882:9981        883:9853        884:9943        885:10062       886:10012       887:10035       888:9939        889:9961        890:9830        891:9975    892:9869        893:9979        894:9873        895:10052       896:10043       897:9992        898:9934        899:9862        900:9858        901:9979        902:9893        903:9904    904:9926        905:10102       906:9974        907:9983        908:9915        909:10100       910:10132       911:10112       912:10041       913:9915        914:9878        915:9901    916:10033       917:10021       918:10090       919:10044       920:9977        921:10001       922:9805        923:9992        924:9974        925:10076       926:10066       927:9967    928:9782        929:9887        930:9904        931:10032       932:9874        933:10222       934:9956        935:9962        936:10042       937:9866        938:9996        939:10047   940:10098       941:10047       942:9903        943:9993        944:9977        945:10102       946:9972        947:9927        948:10059       949:10100       950:9897        951:9945    952:10106       953:9790        954:10135       955:10008       956:9765        957:9946        958:9932        959:9938        960:9960        961:9959        962:9968        963:10031   964:9813        965:10047       966:9901        967:9965        968:9857        969:9973        970:9911        971:10045       972:10083       973:10093       974:9962        975:10004   976:9806        977:10010       978:10013       979:9858        980:10020       981:10152       982:9957        983:10040       984:10115       985:10003       986:9951        987:10071   988:9839        989:9984        990:10158       991:10219       992:9992        993:9879        994:10112       995:9876        996:10053       997:10036       998:10070       999:10132