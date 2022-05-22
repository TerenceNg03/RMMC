>>>>>> test1.c symbol table >>>>>>

int64_tRMMC__0;
doubleRMMC__1;
int64_tRMMC__2;
doubleRMMC__3;
int64_tRMMC__4;
int64_tRMMC__5;
int64_tRMMC__6;
int64_tRMMC__7;
int64_tRMMC__8;
doubleRMMC__9;
doubleRMMC__10;
int64_tRMMC__11;
int64_tRMMC__12;
int64_tRMMC__13;
int64_tRMMC__15;
int64_tRMMC__16;
int64_tRMMC__17;
int64_tRMMC__18;
uint8_t RMMC_14 [4] = {
RMMC__15,
RMMC__16,
RMMC__17,
RMMC__18};
int64_tRMMC__20;
uint8_tRMMC__21;
int64_tRMMC__22;
uint8_tRMMC__23;
int64_tRMMC__25;
int64_tRMMC__26;
int64_tRMMC__27;
uint8_t RMMC_24 [3] = {
RMMC__25,
RMMC__26,
RMMC__27};
doubleRMMC__29;
uint8_tRMMC__30;
uint8_tRMMC__31;
uint8_tRMMC__33;
uint8_tRMMC__34;
uint8_tRMMC__35;
uint8_tRMMC__36;
uint8_tRMMC__37;
uint8_tRMMC__38;
uint8_t RMMC_32 [6] = {
RMMC__33,
RMMC__34,
RMMC__35,
RMMC__36,
RMMC__37,
RMMC__38};

>>>>>>>>> code >>>>>>>>>>>

RMMC__0 = 9
 int64_t USER_a
 USER_a = RMMC__0
RMMC__1 = 9.800000
RMMC__2 = 8
RMMC__3 = RMMC__1 + RMMC__2
RMMC__4 = 6
RMMC__5 = 9
RMMC__6 = 5
RMMC__7 = RMMC__5 - RMMC__6
RMMC__8 = RMMC__4 - RMMC__7
RMMC__9 = RMMC__3 & RMMC__8
double(* USER_b)
USER_b = malloc(sizeof(double))
 *(USER_b) = RMMC__9
RMMC__10 = (*USER_b) + USER_a
RMMC__11 = 7
RMMC__12 = USER_a = RMMC__11
RMMC__13 = RMMC__10,RMMC__12
int64_t(* USER_c)
 c = &(RMMC__13)
RMMC__15 = 1
RMMC__16 = 2
RMMC__17 = 3
RMMC__18 = 9
 uint8_t USER_m[4]
 USER_m =  RMMC_14 
RMMC__20 = 9
RMMC__21 = USER_m[RMMC__20]
RMMC__22 = 10
RMMC__23 = RMMC__21 + RMMC__22
RMMC__25 = 1
RMMC__26 = 2
RMMC__27 = 3
RMMC__29 = 9.800000
RMMC__30 = 
RMMC__31 = RMMC__23 + RMMC__30
 uint8_t USER___e
 USER___e = RMMC__31
RMMC__33 = 97
RMMC__34 = 115
RMMC__35 = 99
RMMC__36 = 100
RMMC__37 = 92
RMMC__38 = 99
 uint8_t USER_str[6]
 USER_str =  RMMC_32 
RMMC__40:
>>> function paramters >>>
 uint32_t USER_p1
 char USER_p2
 int32_t USER_RMMC__41
>>> function body >>>
int64_tRMMC_RMMC__40_1;
uint32_tRMMC_RMMC__40_2;
RMMC_RMMC__40_1 = 1
int64_t(* USER_uni__1)
USER_uni__1 = malloc(sizeof(int64_t))
 *(USER_uni__1) = RMMC_RMMC__40_1
int64_t(* USER_uni__2)
uint8_t(* USER_uni__3)
USER_uni__3 = USER_uni__1
RMMC_RMMC__40_2 = USER_p1 + USER_p2
free(USER_uni__2)
free(USER_uni__3)
ret RMMC_RMMC__40_2 to RMMC__40
free(USER_uni__2)
free(USER_uni__3)
<<< function ends <<<
 int32_t(* USER_func__1)(uint32_t,char)
 USER_func__1 = RMMC__40
RMMC__42:
>>> function paramters >>>
 int8_t USER_para1
>>> function body >>>
 uint32_t RMMC_RMMC__42_1
RMMC_RMMC__42_1 = USER_para1
RMMC_RMMC__42_2 = USER_func__1( RMMC_RMMC__42_1 )
 int32_t USER_func1__para
 USER_func1__para = RMMC_RMMC__42_2
<<< function ends <<<
 void(* USER_func__2)(int8_t)
 USER_func__2 = RMMC__42
free(USER_b)

>>>>>>> end of test1.c >>>>>>>>

