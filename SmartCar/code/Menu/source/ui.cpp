
#include "ui.h"
uint8 func_index=0;
uint8 last_index=0;

bool ui_state=true;
bool had_press_key=false;
void (*current_operation_index)(); //定义一个函数指针

typedef struct
{
	uint8 current;
	uint8 up;//向上翻索引号
	uint8 down;//向下翻索引号
	uint8 enter;//确认索引号
	void (*current_operation)();
} key_table;
/*第0页*/
void ui_page_0()
{
    ips200_show_string( 20 , 16*1, "ips200_init success");
    ips200_show_string( 20 , 16*2, "Press the key 3");
    ips200_show_string( 20 , 16*3, "page 0");
    ips200_draw_line(0,16*6,239,16*6,RGB565_RED);
    ips200_show_string( 20 , 16*7, "key0:Back to page1");
    ips200_show_string( 20 , 16*8, "key1:UP");
    ips200_show_string( 20 , 16*9, "key2:Down");
    ips200_show_string( 20 , 16*10,"key3:Select");
}
/*第一页*/
void ui_page_1_1()
{
    ips200_show_string( 20 , 16*1, "GO GO GO");
    ips200_show_string( 20 , 16*2, "Motor");
    ips200_show_string( 20 , 16*3, "Cha bi he");
    ips200_show_string( 20 , 16*4, "return last page");
    ips200_show_string( 10 , 16*1, ">");

}
void ui_page_1_2()
{
    ips200_show_string( 20 , 16*1, "GO GO GO");
    ips200_show_string( 20 , 16*2, "Motor");
    ips200_show_string( 20 , 16*3, "Cha bi he");
    ips200_show_string( 20 , 16*4, "return last page");
    ips200_show_string( 10 , 16*2, ">");
}
void ui_page_1_3()
{
    ips200_show_string( 20 , 16*1, "GO GO GO");
    ips200_show_string( 20 , 16*2, "Motor");
    ips200_show_string( 20 , 16*3, "Cha bi he");
    ips200_show_string( 20 , 16*4, "return last page");
    ips200_show_string( 10 , 16*3, ">");
}
void ui_page_1_4()
{
    ips200_show_string( 20 , 16*1, "GO GO GO");
    ips200_show_string( 20 , 16*2, "Motor");
    ips200_show_string( 20 , 16*3, "Cha bi he");
    ips200_show_string( 20 , 16*4, "return last page");
    ips200_show_string( 10 , 16*4, ">");
}
/*出发*/
void fun_a21()
{
    // ips200_show_string( 20 , 16*1, "fun_d1");
    beep_on();
    system_delay_ms(1000);
    beep_off();
    ui_state=0;
    // break;
}
/*-------------------------------------------------------------*/
/*第二页*/
/*电机设置*/
void motor_page_1()
{
    ips200_show_string( 20 , 16*1, "Motor PID");
    ips200_show_string( 20 , 16*2, "Motor Speed");
    ips200_show_string( 20 , 16*3, "Cha su");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*1, ">");
}
void motor_page_2()
{
    ips200_show_string( 20 , 16*1, "Motor PID");
    ips200_show_string( 20 , 16*2, "Motor Speed");
    ips200_show_string( 20 , 16*3, "Cha su");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*2, ">");
}
void motor_page_3()
{
    ips200_show_string( 20 , 16*1, "Motor PID");
    ips200_show_string( 20 , 16*2, "Motor Speed");
    ips200_show_string( 20 , 16*3, "Cha su");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*3, ">");
}
void motor_page_4()
{
    ips200_show_string( 20 , 16*1, "Motor PID");
    ips200_show_string( 20 , 16*2, "Motor Speed");
    ips200_show_string( 20 , 16*3, "Cha su");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*4, ">");
}

/*差比和阈值设置*/
void cha_bi_he_page_1()
{
    ips200_show_string( 20 , 16*1, "set cha bi he");
    ips200_show_string( 20 , 16*2, "retrun last page");
    ips200_show_string( 10 , 16*1, ">");
}
void cha_bi_he_page_2()
{
    ips200_show_string( 20 , 16*1, "set cha bi he");
    ips200_show_string( 20 , 16*2, "retrun last page");
    ips200_show_string( 10 , 16*2, ">");
}
/*----------------------------------------------------------------*/
/*第三页*/
/*电机PID设置*/
void Motor_PID_page_1()
{
    ips200_show_string( 20 , 16*1, "set Motor Kp");
    ips200_show_string( 20 , 16*2, "set Motor Ki");
    ips200_show_string( 20 , 16*3, "set Motor Kd");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*1, ">");
}
void Motor_PID_page_2()
{
    ips200_show_string( 20 , 16*1, "set Motor Kp");
    ips200_show_string( 20 , 16*2, "set Motor Ki");
    ips200_show_string( 20 , 16*3, "set Motor Kd");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*2, ">");
}
void Motor_PID_page_3()
{
    ips200_show_string( 20 , 16*1, "set Motor Kp");
    ips200_show_string( 20 , 16*2, "set Motor Ki");
    ips200_show_string( 20 , 16*3, "set Motor Kd");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*3, ">");
}
void Motor_PID_page_4()
{
    ips200_show_string( 20 , 16*1, "set Motor Kp");
    ips200_show_string( 20 , 16*2, "set Motor Ki");
    ips200_show_string( 20 , 16*3, "set Motor Kd");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*4, ">");
}
/*电机速度设置*/
void Motor_Speed_page_1()
{
    ips200_show_string( 20 , 16*1, "set Motor straight line speed");
    ips200_show_string( 20 , 16*2, "set Motor curve line speed");
    ips200_show_string( 20 , 16*3, "set Motor circle speed");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*1, ">");
}
void Motor_Speed_page_2()
{
    ips200_show_string( 20 , 16*1, "set Motor straight line speed");
    ips200_show_string( 20 , 16*2, "set Motor curve line speed");
    ips200_show_string( 20 , 16*3, "set Motor circle speed");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*2, ">");
}
void Motor_Speed_page_3()
{
    ips200_show_string( 20 , 16*1, "set Motor straight line speed");
    ips200_show_string( 20 , 16*2, "set Motor curve line speed");
    ips200_show_string( 20 , 16*3, "set Motor circle speed");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*3, ">");
}
void Motor_Speed_page_4()
{
    ips200_show_string( 20 , 16*1, "set Motor straight line speed");
    ips200_show_string( 20 , 16*2, "set Motor curve line speed");
    ips200_show_string( 20 , 16*3, "set Motor circle speed");
    ips200_show_string( 20 , 16*4, "retrun last page");
    ips200_show_string( 10 , 16*4, ">");
}
/*差速设置*/
void Cha_su_page_1()
{
    ips200_show_string( 20 , 16*1, "set cha su");
    ips200_show_string( 20 , 16*2, "retrun last page");
    ips200_show_string( 10 , 16*1, ">");
}
void Cha_su_page_2()
{
    ips200_show_string( 20 , 16*1, "set cha su");
    ips200_show_string( 20 , 16*2, "retrun last page");
    ips200_show_string( 10 , 16*2, ">");
}
/*-------------------------------------------------------------*/
/*第四页*/
/*设置差比和阈值*/ 
void set_cha_he_bi_threshold()
{
    ips200_show_string( 20 , 16*7, "set_cha_he_bi_threshold");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "threshold:");
    
    while (!key3_Press_down())
    {
        ips200_show_uint( 20 , 16*2,G_cha_he_bi_threshold, 2);
        if (key1_Press_down())
        {
            G_cha_he_bi_threshold++;
        }
        if (key2_Press_down())
        {
            G_cha_he_bi_threshold--;
        }
    }
}
/*设置电机PID*/
void set_Motor_KP()
{
    ips200_show_string( 20 , 16*7, "set_Motor_P");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "P:");
    while (!key3_Press_down())
    {
        ips200_show_float( 20 , 16*1, G_motor_Kp,2,2);
        if (key1_Press_down())
        {
            G_motor_Kp+=0.1;
        }
        if (key2_Press_down())
        {
            G_motor_Kp-=0.1;
        }
    }
}
void set_Motor_KI()
{
    ips200_show_string( 20 , 16*7, "set_Motor_I");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "I:");
    while (!key3_Press_down())
    {
        ips200_show_float( 20 , 16*1, G_motor_Ki,2,2);
        if (key1_Press_down())
        {

            G_motor_Ki+=0.1;
        }
            if (key2_Press_down())
        {
            G_motor_Ki-=0.1;
        }
    }
}
void set_Motor_KD()
{
    ips200_show_string( 20 , 16*7, "set_Motor_D");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "D:");
    while (!key3_Press_down())
    {
         ips200_show_float( 20 , 16*1, G_motor_Kd,2,2);
        if (key1_Press_down())
        {
            G_motor_Kd+=0.1;
        }
            if (key2_Press_down())
        {
            G_motor_Kd-=0.1;
        }
    }
}
void set_Motor_straight_line_speed()
{
    ips200_show_string( 20 , 16*7, "set_straight_line_speed");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "straight speed:");
    while (!key3_Press_down())
    {
        ips200_show_uint( 20 , 16*2,G_straight_line_speed, 4);
        if (key1_Press_down())
        {
            G_straight_line_speed+=10;
        }
            if (key2_Press_down())
        {
            G_straight_line_speed-=10;
        }
    }
}
void set_Motor_curve_line_speed()
{
    ips200_show_string( 20 , 16*7, "set_Motor_curve_line_speed");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "curve_line_speed:");
    while (!key3_Press_down())
    {
        ips200_show_uint( 20 , 16*2,G_curve_line_speed, 4);
        if (key1_Press_down())
        {
            G_curve_line_speed+=10;
        }
            if (key2_Press_down())
        {
            G_curve_line_speed-=10;
        }
    }
}
void set_Motor_circle_speed()
{
    ips200_show_string( 20 , 16*7, "set_Motor_circle_speed");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "curve_line_speed:");
    while (!key3_Press_down())
    {
        ips200_show_uint( 20 , 16*2,G_circle_speed, 4);
        if (key1_Press_down())
        {
            G_circle_speed+=10;
        }
            if (key2_Press_down())
        {
            G_circle_speed-=10;
        }
    }
}
void set_Motor_cha_su()
{
    ips200_show_string( 20 , 16*7, "set_Motor_cha_su");
    ips200_show_string( 20 , 16*8, "Press the key 3 to save");
    ips200_show_string( 0 , 16*1, "cha_su K:");
    while (!key3_Press_down())
    {
        ips200_show_float( 20 , 16*2,G_cha_su_K, 2,2);
        if (key1_Press_down())
        {
            G_cha_su_K+=0.1;
        }
            if (key2_Press_down())
        {
            G_cha_su_K-=0.1;
        }
    }
}
/*-------------------------------------------------------------*/

key_table table[40]=
{
/*------------------------------------------------*/	
	//第0层
/*0*/	{0,0,0,1,(*ui_page_0)},

/*------------------------------------------------*/	
    //第1层
/*1*/	{1,4,2, 5,(*ui_page_1_1)},//GO GO GO
/*2*/	{2,1,3, 9,(*ui_page_1_2)},//Motor
/*3*/	{3,2,4,13,(*ui_page_1_3)},//Cha bi he		
/*4*/	{4,3,1, 0,(*ui_page_1_4)},

/*------------------------------------------------*/	
    //第2层
/*5*/	{5,5,5,5,(*fun_a21)},	//出发	懒得改，保留，目的是保持数组顺序，后面看看有什么可以加的
/*6*/    {5,5,5,5,(*fun_a21)},	//出发	
/*7*/    {5,5,5,5,(*fun_a21)},	//出发	
/*8*/    {5,5,5,5,(*fun_a21)},	//出发				
	
/*9*/	{ 9,12,10,15,(*motor_page_1)},	//Motor PID		
/*10*/	{10, 9,11,19,(*motor_page_2)},  //Motor Speed
/*11*/	{11,10,12,23,(*motor_page_3)},	//Cha su				                	
/*12*/	{12,11, 9, 2,(*motor_page_4)},
	
/*13*/  {13,14,14,25,(*cha_bi_he_page_1)},//set cha bi he				
/*14*/	{14,13,13,3,(*cha_bi_he_page_2)},	
/*------------------------------------------------*/	

    //第3层
/*设置电机PID*/
/*15*/	{15,18,16, 26,(*Motor_PID_page_1)},	//set Motor Kp		                	
/*16*/	{16,15,17,27,(*Motor_PID_page_2)},	//set Motor Ki
/*17*/	{17,16,18, 28,(*Motor_PID_page_3)},	//set Motor Kd	                	
/*18*/	{18,17,15,9,(*Motor_PID_page_4)},		                	

/*设置电机速度*/
/*19*/  {19,22,20, 29,(*Motor_Speed_page_1)},	//set Motor straight line speed	                	
/*20*/	{20,19,21,30,(*Motor_Speed_page_2)},    //set Motor curve line speed
/*21*/  {21,20,22, 31,(*Motor_Speed_page_3)},	//set Motor circle speed			                	
/*22*/	{22,21,19,10,(*Motor_Speed_page_4)},

/*设置电机差速*/
/*23*/  {23,24,24, 32,(*Cha_su_page_1)},	    //set cha su			                	
/*24*/	{24,23,23,11,(*Cha_su_page_2)},


/*------------------------------------------------*/	

    //第4层
/*设置差比和阈值*/    
/*25*/ {25,25,25,13,(*set_cha_he_bi_threshold)},

/*选择设置电机P or I or D*/
/*26*/ {26,26,26,15,(*set_Motor_KP)},
/*27*/ {27,27,27,16,(*set_Motor_KI)},
/*28*/ {28,28,28,17,(*set_Motor_KD)},

/*29*/ {29,29,29,19,(*set_Motor_straight_line_speed)},
/*30*/ {30,30,30,20,(*set_Motor_curve_line_speed)},
/*31*/ {31,31,31,21,(*set_Motor_circle_speed)},

/*32*/ {32,32,32,23,(*set_Motor_cha_su)},
};

void ui() 
{
    ips200_init("/dev/fb0");
    ui_page_0();
    while(ui_state)
    {
        if(key1_Press_down())
        {
            had_press_key=true;
            func_index = table[func_index].up;    //向上翻
            while(key1_Press_down());//松手检测
        }
        if(key2_Press_down())
        {
            had_press_key=true;
            func_index = table[func_index].down;    //向下翻
            while(key2_Press_down());
        }
        if(key3_Press_down())
        {
            had_press_key=true;
            func_index = table[func_index].enter;    //确认
            while(key3_Press_down());
        }
        if(key0_Press_down())
        {
            had_press_key=true;
            func_index = 1;    //返回起始界面
            while(key0_Press_down());
        }
        if (had_press_key)
        {
            had_press_key=false;
            // std::cout<<"func_index:"<<(int)func_index<<std::endl;
            current_operation_index = table[func_index].current_operation;

            // u8g2_ClearBuffer(&u8g2); 
            ips200_clear();
            (*current_operation_index)();//执行当前操作函数
            // u8g2_SendBuffer(&u8g2);

            last_index = func_index;
        }
    }
}
