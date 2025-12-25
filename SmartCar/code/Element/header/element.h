#ifndef __ELEMENT_H_
#define __ELEMENT_H_
//枚举元素！
enum Flag_element {
    NONE, CIRCLE_L, Zebra, CROSS, CIRCLE_R,Zebra2,
};//元素锁标志位！！！


/*圆环*/
enum Flag_e {
    FLAG_0, FLAG_1, FLAG_2, FLAG_3, FLAG_4, FLAG_5, FLAG_6, FLAG_7, FLAG_8, FLAG_9,
};
enum Left_Flag_e {
    LEFT_FLAG_0, LEFT_FLAG_1, LEFT_FLAG_2, LEFT_FLAG_3, LEFT_FLAG_4, LEFT_FLAG_5, LEFT_FLAG_6, LEFT_FLAG_7, LEFT_FLAG_8, LEFT_FLAG_9,
};
/*斑马线*/
// enum Zebra_times {
//     Zebra_0, Zebra_1, Zebra_2, Zebra_3, Zebra_4, //Zebra_4设置停止或者在Zebra_3就停止
// };
enum Zebra_times {
    Zebra_0, Zebra_once, Zebra_twice,
};
/*十字*/
// enum CROSS {
//     FLAGc_0,FLAGc_1, FLAGc_2, FLAGc_3,FLAGx_Left_3,FLAGx_Right_3,
// };
enum Flag_c {
    FLAGc_0, FLAGc_1, FLAGc_2, FLAGc_3, FLAGx_Right_3, FLAGx_Left_3,FLAGr_Right1,FLAGr_Left1,
};
/*圆环状态的枚举，声明放在main中*/
extern enum Flag_e circle_Flag;
// enum Flag_element FLAG_ELEMENT=NONE;
#endif