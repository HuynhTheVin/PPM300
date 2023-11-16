/* Encoding UTF-8 �G���R�[�h */

#define EXTERN extern
#include "PPM.H"
#include "advalue.h"

/************************************
  入力レンジチェック (初期値セット)
 ************************************/
                      /* ﾟCmax, ﾟCmin  tdiv minbit */
const int maxrange1[] = {  /* 庫内温度 */
    1000,     -500,  100,   2,    /* 0 Pt           -50.0~100.0 ﾟC */
    };
const int maxrange2[] = {  /* 湿度入力 */
    100,        0,    1,   10,    /* 0 DC01V            0~100   % */
    };
const int maxrange3[] = {  /* マルチ入力 */
    2000,     -500,  200,   2,    /* 0 K           -50.0~200.0 ﾟC */
    2000,     -500,  200,   2,    /* 1 J           -50.0~200.0 ﾟC */
    2000,     -500,  100,   2,    /* 2 Pt          -50.0~200.0 ﾟC */
    };
void range_chk(void)
{
    int *p;
    BYTE ch;
    
    for (ch=0;ch<MAXCH;ch++){
        if(ch == CH_KONAI){
            p = (int *)&maxrange1[0];/* 庫内入力 */
        }else if(ch == CH_SHITUDO){
            p = (int *)&maxrange2[0];/* 湿度入力 */
        }else{
            p = (int *)&maxrange3[0];/* マルチ入力 */
            p += INPUT_ADC.wksens[ch - CH_MARUCHI1]*3;
        }
        INPUT_ADC.r_span[ch] = *p++;
        INPUT_ADC.r_min[ch]  = *p++;
        INPUT_ADC.r_scal[ch] = INPUT_ADC.r_span[ch]-INPUT_ADC.r_min[ch];
        INPUT_ADC.tdiv[ch]   = *p++;
        INPUT_ADC.minbit[ch] = *p;
    }
}

//long max(long a, long b){
//    if(a>b){return a;}else{return b;}
//}
//long min(long a, long b){
//    if(a>b){return b;}else{return a;}
//}
int cscalsub2(int t)
{
    return(t *INPUT_ADC.minbit[CH1]);
}
/************************
 * リニアライザテーブル *
 ************************/
const int linetbl0[] = {         /* K -210.0～410.0   20℃   */
   15,  42,                      /* min,max 1ﾟC     */
/* REM JIS C1602(1995)*/
  305,  376,  441,  502,  559,
  609,  656,  698,  733,  764,
  789,  806,  820,  828,  831,
  827,  819,  810,  803,  798,
  800,  804,  810,  818,  824,
  829,  833,  836,  840,  842,
  845 };
const int linetbl1[] = {         /* J   -200～400  20℃*/
   24,  55,                      /* min,max 1ﾟC     */
/* REM JIS C1602(1995)*/
  487,  582,  662,  733,  793,
  847,  893,  932,  966,  995,
 1019, 1040, 1057, 1071, 1082,
 1091, 1099, 1103, 1107, 1110,
 1110, 1111, 1110, 1109, 1108,
 1107, 1104, 1104, 1103, 1103,
 1104 };
const int linetbl2[] = {          /* Pt100   -200～500  10℃*/
//  54,   39,/* min,max 1ﾟC  */     /* 2.47V 20K */
//  531,  526,  522,  517,  515,
//  511,  507,  505,  501,  500,
//  495,  495,  490,  491,  488,
//  485,  483,  482,  481,  478,
//  477,  476,  474,  472,  471,
//  469,  468,  466,  464,  463,
//  461,  460,  457,  456,  456,
//  453,  452,  450,  448,  448,
//  446,  444,  442,  440,  440,
//  437,  436,  434,  434,  431,
//  431,  428,  426,  426,  424,
//  421,  421,  420,  417,  416,
//  415,  413,  411,  410,  409,
//  406,  406,  403,  403,  401
//   36,   26,/* min,max 1ﾟC  */     /* 2.46V 2K */  
//   354,  351,  349,  345,  343,
//   342,  338,  337,  335,  334,
//   331,  330,  328,  328,  326,
//   324,  323,  323,  321,  320,
//   319,  318,  317,  316,  316,
//   313,  314,  312,  311,  310,
//   308,  308,  307,  305,  306,
//   303,  303,  302,  301,  300,
//   299,  297,  297,  295,  295,
//   294,  292,  292,  291,  289,
//   289,  288,  286,  286,  285,
//   283,  283,  282,  280,  280,
//   278,  278,  277,  275,  275,
//   274,  272,  272,  271,  269,

    530, 407,/*min,max 1ﾟC  */  /* 2.465V 2K */  
    5301, 5252, 5215, 5166, 5141,
    5117, 5067, 5055, 5018, 5006,
    4969, 4957, 4920, 4920, 4896,
    4871, 4859, 4847, 4834, 4810,
    4797, 4785, 4773, 4761, 4748,
    4724, 4724, 4699 ,4687, 4675,
    4650,4650,4626,4613,4613,
    4576,4576,4564,4540,4540,
    4515,4503,4490,4466,4466,
    4441,4429,4417,4404,4392,
    4380,4355,4343,4343,4318,
    4294,4294,4282,4257,4245,
    4233,4220,4208,4183,4183,
    4159,4147,4134,4122,4110,
  };

const int span_tbl[] = {/* レンジ毎のテーブル最大値 */
   4100, 4000,  5000, 100};
const int min_tbl[] = {/* レンジ毎のテーブル最小値                  */
   -2100, -2000, -2000,  0};      
const int offset_tbl[] = {/* レンジ毎の 0ﾟC 入力に対する定格オフセット */
// 6035, 7890,  -2285,    0};/* 2.47V 20K */
//  6035, 7890,  -1524,    0};/* 2.47V 30K */
    6035, 7890,  -22616,    0};/* 2.465V 2K */
const long adref_tbl[] = { /* レンジ毎のリニアライズテーブル有効幅  */
// 22855,29738,31935,1000000 };/* 2.47V 20K */
// 22855,29738,21395,1000000 };/* 2.47V 30K */
   22855,29738,281032,1000000 };/* 2.465V 2K */
const int rt_tbl[] = { /* 端子  0~50ﾟC の起電力                     */
   2023,2585,0,0 };         
int* const linetbla [] = { (int *)&linetbl0[0],(int *)&linetbl1[0], (int *)&linetbl2[0]};

const int rtlinetbl[] = {         /* 端子温度リニアテーブル -20～70 5℃毎 */
//   717, 811, 897, 977,1052,1098,1122,1129,1116,/* 2.465V 10K 100ohm */
//  1086,1039, 982, 917, 847, 776, 705, 627,562 
     481, 544, 601, 655, 704, 735, 751, 756, 747,/* 2.465V 15K 100ohm */
     726, 695, 656, 613, 566, 518, 471, 419, 375
};
int rtlini(long l)
{
    WORD t,i;
    long av,adr;
    long temp;
    int  *linetbl;
    long tempmin;
    
///* 2.465V 10K 100ohm */
//    l -=3403;                 /* -20℃相当の電圧加算し反転することにより正の範囲に変換 */
//    adr = 16460;               /* -20℃～70℃変化時の電圧幅*/

/* 2.465V 15K 100ohm */
    l -=2280 ;                 /* -20℃相当の電圧加算し反転することにより正の範囲に変換 */
    adr = 11013;               /* -20℃～70℃変化時の電圧幅*/

    linetbl = (int *)&rtlinetbl[0];
    av = -l;                   /* 正の範囲に変換し‐20℃を基準ゼロにシフトした結果 */
    temp = 0;

    if (av < 0){               /* 定格範囲外マイナス */
        t = (-av / linetbl[0]);
        temp -= (long)t*500;  
        av = av % linetbl[0];
        t = linetbl[0];
        av *= 500;
        temp -= av/t;
    }else if (av > adr){       /* 定格範囲外プラス   */
        t = av/adr;
        temp = (long)t * 9000;
        av = av % adr;
        t = av / linetbl[17];
        temp += (t*500);      
        av = av % linetbl[17];
        t = linetbl[17];
        av *= 500;
        temp += av/t;
    } else {                   /* 定格範囲内         */
        i = 0;
        while (av > linetbl[i]) {
            av -= linetbl[i++];
            temp += 500;
        }
        t = linetbl[i];
        av *= 500;
        temp += av/t;
    }

    temp = temp - 2000;
    return temp;               /* 端子温度変換結果 ℃ */
}
/***************
  リニアライズ  
 ***************/
long linsub1(long d)
{
    float t;
    t =((long)d-INPUT_ADC.ref_z1);
    t *=  IN_AJUST.tcajs[0];
    t /= (INPUT_ADC.ref_s1-INPUT_ADC.ref_z1); 
    return t;
}
long linsub2(long d)
{
    float t;
    t =((long)d-INPUT_ADC.ref_z2);
    t *=  IN_AJUST.tcajs[0];
    t /= (INPUT_ADC.ref_s2-INPUT_ADC.ref_z2); 
    return t;
}

long rlin(int avt,BYTE wks)
{
    long j;
    int rt;

    rt = rt_tbl[wks];               /* 0～50℃の起電力          */

    j = 0;
    if (avt < 0){
        while ( avt < 5000){
            avt += 5000;
            j -= rt;
        }
        j -= ((long)~avt * rt/5000 );
    } else {
        while ( avt > 5000){
            avt -= 5000;
            j += rt;
        }
        j += ((long)avt * rt/5000 );
    }
    return j;
}
void mktermt1(void)
{
    long t;
    
    t = linsub1(INPUT_ADC.termt1);
    t += IN_AJUST.tcajz[0];
    t -= IN_AJUST.ajtz[0];
    INPUT_ADC.ttemp1 = rtlini(t);
}
void mktermt2(void)
{
    long t;
    
    t = linsub1(INPUT_ADC.termt2);
    t += IN_AJUST.tcajz[0];
    t -= IN_AJUST.ajtz[0];
    INPUT_ADC.ttemp2 = rtlini(t);
}

/* レンジ合わせてテーブル変更必要かもしれ */
const WORD ptinb_tbl[] = {       /* PT100 Inb の入力係数  100.0℃毎       */
                                 /* 0ﾟC ｦ 1 とする係数 *1000倍値 */
    9972,   9990,  10000,  10018 ,  10033,  10033,  10033,  10033,  10033,  10033,  10033 };

void advaluesub(void)
{
    long    av,adr,av2;
    float   avs;
    WORD    t,i;
    long    temp;
//* long    tempmin;
    int     t1;
    int     *linetbl;
    BYTE    twks,linem;
    
    if(INPUT_ADC.linech == CH_SHITUDO){/* 湿度入力 0～1V固定 */
        twks = DC01V;
        av = (INPUT_ADC.sensin[INPUT_ADC.linech]-IN_AJUST.dcvof2s-INPUT_ADC.ref_z1);
        av = (long)((float)av * IN_AJUST.dcvaj2s/(INPUT_ADC.ref_s1-INPUT_ADC.ref_z1));
        av += IN_AJUST.dcvaj2z;
    }else if(INPUT_ADC.linech == CH_KONAI){/* 庫内入力 Pt100 3線方式固定 */
        twks = PT100;
        avs = (float)(IN_AJUST.offset1-IN_AJUST.ajref1) * IN_AJUST.ptaj1s;
        av2 = (long)(avs / (INPUT_ADC.ref_s2-INPUT_ADC.ref_z2));
        t1 = min(8,max(-2,INPUT_ADC.rtempc[INPUT_ADC.linech]/(1000*INPUT_ADC.minbit[INPUT_ADC.linech])));
        av = (long)(av2 * 10000)/ptinb_tbl[t1+2];
        adr = INPUT_ADC.sensinb[INPUT_ADC.linech]-INPUT_ADC.ref_z2;
        avs = (float)adr * IN_AJUST.ptaj1s;
        adr = (long)(avs/(INPUT_ADC.ref_s2-INPUT_ADC.ref_z2));

        adr *= 10000;
        adr /= ptinb_tbl[t1+2];
        adr -= av;
        av =(INPUT_ADC.sensin[INPUT_ADC.linech] - INPUT_ADC.ref_z2) ;
        avs = (float)av * IN_AJUST.ptaj1s;
        av = (long)(avs/(INPUT_ADC.ref_s2-INPUT_ADC.ref_z2)); 
        av -= adr;
        av += IN_AJUST.ptaj1z;
    }else{/* マルチ入力 */
        if(INPUT_ADC.linech==CH_MARUCHI1){/* マルチ入力1 */
            twks = INPUT_ADC.wksens[CH_M1];
            linem = CH_M1;
        }else if(INPUT_ADC.linech==CH_MARUCHI2){  /* マルチ入力2 */                
            twks = INPUT_ADC.wksens[CH_M2];
            linem = CH_M2;
        }
        else {/* マルチ入力3 */
            twks = INPUT_ADC.wksens[CH_M3];
            linem = CH_M3;
        }
        if(twks == PT100){/* Pt100 */
            avs = (float)(IN_AJUST.offset[linem]-IN_AJUST.ajref[linem]) * IN_AJUST.ptajs[linem];
            av2 = (long)(avs / (INPUT_ADC.ref_s2-INPUT_ADC.ref_z2));
            t1 = min(8,max(-2,INPUT_ADC.rtempc[INPUT_ADC.linech]/(1000*INPUT_ADC.minbit[INPUT_ADC.linech])));
            av = (long)(av2 * 10000)/ptinb_tbl[t1+2];
            adr = INPUT_ADC.sensinb[INPUT_ADC.linech]-INPUT_ADC.ref_z2;
            avs = (float)adr * IN_AJUST.ptajs[linem];
            adr = (long)(avs/(INPUT_ADC.ref_s2-INPUT_ADC.ref_z2));
            
            adr *= 10000;
            adr /= ptinb_tbl[t1+2];
            adr -= av;
            av =(INPUT_ADC.sensin[INPUT_ADC.linech] - INPUT_ADC.ref_z2) ;
            avs = (float)av * IN_AJUST.ptajs[linem];
            av = (long)(avs/(INPUT_ADC.ref_s2-INPUT_ADC.ref_z2)); 
            av -= adr;
            av += IN_AJUST.ptajz[linem];
        }else if(twks==K200||twks==J200){/* 熱電対 */
            av = (INPUT_ADC.sensin[INPUT_ADC.linech]-INPUT_ADC.ref_z1);
            av = (long)((float)av * IN_AJUST.tcajs[linem]/(INPUT_ADC.ref_s1-INPUT_ADC.ref_z1));
            av += IN_AJUST.tcajz[linem];
            // if(INPUT_ADC.linech==CH_MARUCHI1){    /* 端子温度補償 */
            //     mktermt1();
            //     t1 = INPUT_ADC.ttemp1;
            // }else{
            //     mktermt2();
            //     t1 = INPUT_ADC.ttemp2;
            // }
            mktermt1();/* 端子温度補償 */
            mktermt2();
            t1=INPUT_ADC.ttemp1;
            if(KEY_MODE.flg_mode != AJUSTMD){
                av += rlin(t1,twks);
            }
        }
    }
    
    if(twks <DC01V){/* 熱電対,Pt */
        av = av + offset_tbl[twks]; /* 電圧オフセット */
        linetbl = linetbla[twks];   /* テーブル参照   */
        adr = (adref_tbl[twks]);    /* 電圧巾         */
        temp = 0;
        if (av < 0){            /* 定格範囲外マイナス */
            t1 = linetbl[0];
            if(chk_dpoint()){
                t1 /=10;
            }
            t = (-av / t1);
            temp = (long)t*INPUT_ADC.minbit[INPUT_ADC.linech];  
            av = av % t1;
            av *= INPUT_ADC.minbit[INPUT_ADC.linech];
            temp -= av/t1;
            temp = -temp;        
        } else {
            if (av > adr){      /* 定格範囲外プラス */
                t = av/adr;
                t1 = ((span_tbl[twks] - min_tbl[twks])*INPUT_ADC.minbit[INPUT_ADC.linech]);
                temp = (long)t * t1;
                av = av % adr;
                t1 = linetbl[1];
                if(chk_dpoint()){
                    t1 /=10;
                }
                t = av / t1;
                temp += (long)t*INPUT_ADC.minbit[INPUT_ADC.linech];  
                av = av % t1;
                av *= INPUT_ADC.minbit[INPUT_ADC.linech];
                temp += av/t1;
            } else {            /* 定格範囲内 */
                t1 = (int)INPUT_ADC.tdiv[INPUT_ADC.linech]*INPUT_ADC.minbit[INPUT_ADC.linech];
                i = 2;
                while (av > linetbl[i]) {
                    av -= linetbl[i++];
                    temp += t1;
                }

                t = (int)linetbl[i];
                av *= t1;
                temp += av/t;
            }
        }
        temp += min_tbl[twks]*INPUT_ADC.minbit[INPUT_ADC.linech];
        if(INPUT_ADC.linech == CH1){
            INPUT_ADC.rtemp[INPUT_ADC.linech] = temp + cscalsub2(SET_PARA.setpara[PH_DATA64]); /* センサ補正加算 */
            INPUT_ADC.rtempc[INPUT_ADC.linech] = INPUT_ADC.rtemp[INPUT_ADC.linech] ;
        }else{
            INPUT_ADC.rtemp[INPUT_ADC.linech] = temp;
            INPUT_ADC.rtempc[INPUT_ADC.linech] = INPUT_ADC.rtemp[INPUT_ADC.linech] ;
        }
    }else{/* DC入力、スケーリングなし、直接に定格に変換、内部分可能が上がりたい場合はminbitを変更すること */
        // if(INPUT_ADC.linech == CH2){
	   	//     av += nsetpara[PHASE9] * 100; /* センサ補正加算 */
        // }
        INPUT_ADC.rtempc[INPUT_ADC.linech] = av;/* 入力uV */
        av2 = 10000/INPUT_ADC.minbit[INPUT_ADC.linech];     /* 100uV単位 */
        avs = (float)av * INPUT_ADC.r_scal[INPUT_ADC.linech];
        if(avs>=0){
            avs += av2/2;
        }else{
            avs -= av2/2;
        }
        temp = avs/av2; 
        INPUT_ADC.rtemp[INPUT_ADC.linech] = temp;
    }
    
    /* PVフィルタ演算 なし*/

    /* 表示値換算 */
    if (INPUT_ADC.rtemp[INPUT_ADC.linech] <0){/* 四捨五入 */
        temp = (-INPUT_ADC.rtemp[INPUT_ADC.linech] )+(INPUT_ADC.minbit[INPUT_ADC.linech]/2); 
        temp = -temp;
    }else{
        temp = (INPUT_ADC.rtemp[INPUT_ADC.linech] )+(INPUT_ADC.minbit[INPUT_ADC.linech]/2); 
    }
    INPUT_ADC.rtempdp[INPUT_ADC.linech] = temp/INPUT_ADC.minbit[INPUT_ADC.linech];
}

/* 分解能: 12000      */
/* 0%(0V)～80%(1V)    */
/* 1.5ms    */
#define ZEROTA1  -500
#define SPANTA1  1000
/* スパン調整：スパン(80%)(9600) */
/* ゼロ調整  ：スパンの10% (960) */
/* 最小出力は8.8mVの為、5%で調整を行う */
void transf(void){/* 伝送出力  */
    BYTE i;
    int max,min;
    long t;
    
    if((INPUT_ADC.linech==CH_KONAI) || (INPUT_ADC.linech == CH_SHITUDO)){
        i = INPUT_ADC.linech;
        t = INPUT_ADC.rtemp[i];
        if(i == CH_KONAI){/* -50.0℃～100.0℃ */
            min =  ZEROTA1*INPUT_ADC.minbit[i];
            max =  SPANTA1*INPUT_ADC.minbit[i];
        }else{
            min = INPUT_ADC.r_min[i]*INPUT_ADC.minbit[i];
            max = INPUT_ADC.r_span[i]*INPUT_ADC.minbit[i];
        }
        if(t>max){t = max;}
        if(t<min){t = min;}
        min += (max - min)/20;/* ゼロ調整点：5% (割り切り注意) */
        if(KEY_MODE.flg_mode == AJUSTMD){        /* ゼロ調整、スパン調整判定。 */
            t = (t<(INPUT_ADC.r_scal[i]*INPUT_ADC.minbit[i])/2 + INPUT_ADC.r_min[i]) ? (min) :(max);/* 入力レンジの半前後 */
        }
        t -= min;
        t *=(9120 + IN_AJUST.antajs[i]);/* 80% = 9600 = 9120 + 480 */
        t /= (max-min);
        t += IN_AJUST.antajz[i]+480;      /* 9600の5% = 480 */

        if(t<0){t=0;}
        if(t>0xFFFF){t=0xFFFF;}
        INPUT_ADC.pwmo[i] = t;
    }
    if(TIMDT.iw==0){
        MTU.TGRB = pwmo[CH_KONAI];
        MTU.TGRC = pwmo[CH_SHITUDO];
    }
}
/*******************************************************
    変換Ch選択  
 *******************************************************/
void advalue(void)
{
    if(INPUT_ADC.cfadc1.bitms.konai_in_cal_request == 1){/* 庫内温度入力 */
        INPUT_ADC.linech = CH_KONAI;
        INPUT_ADC.cfadc1.bitms.konai_in_cal_request = 0;
        advaluesub();
        transf();/* 伝送出力 */
    }
    if(INPUT_ADC.cfadc1.bitms.shitsudo_in_cal_request == 1){/* 湿度入力 */
        INPUT_ADC.linech = CH_SHITUDO;
        INPUT_ADC.cfadc1.bitms.shitsudo_in_cal_request = 0;
        advaluesub();
        transf();/* 伝送出力 */
    }
    if(INPUT_ADC.cfadc1.bitms.manuchi1_in_cal_request == 1){/* マルチ入力1 */
        INPUT_ADC.linech = CH_MARUCHI1;
        INPUT_ADC.cfadc1.bitms.manuchi1_in_cal_request = 0;
        advaluesub();
    }
    if(INPUT_ADC.cfadc1.bitms.manuchi2_in_cal_request == 1){/* マルチ入力2 */
        INPUT_ADC.linech = CH_MARUCHI2;
        INPUT_ADC.cfadc1.bitms.manuchi2_in_cal_request = 0;
        advaluesub();
    }
    if(INPUT_ADC.cfadc1.bitms.manuchi3_in_cal_request == 1){/* マルチ入力3 */
        INPUT_ADC.linech = CH_MARUCHI3;
        INPUT_ADC.cfadc1.bitms.manuchi3_in_cal_request = 0;
        advaluesub();
    }
}
