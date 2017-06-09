int an = 0, bn = 0, cn = 0, \
flag = 0, Amax = 0, Bmax = 0, Cmax = 0; //Xmax(x==A或B或C)是结点中车位号最大的那一个数,方便新建结构体时xuhao的确定//xn是结点的个数
double money = 0;//一天的总费用            

typedef struct car {
	char number1[10];                             //车位号,只在表头结点有实际作用，车辆中序号直接有xuhao存放，在输出车位号的时候加上开头大写字母就行了
	char number2[20];                             //车牌号
	int  time1, time2;                             //停车时间
	int  xuhao;                                   //车位号的整数部分，用来比较大小和确定插入点
	int nn;										//nn是为了计算跨天的汽车的费用的，VC中结构体成员不能初始化，所以只能在创建链表的时候赋值为0；以后每过一个完整的一天就+1
	struct car *next;                             //当进入第二天nn++，在第三天离开时用nn*24*60算出来完整天的分钟数,然后用(24+t1-t2)*60计算剩余时间的分钟数
}AS;
#define AD sizeof(AS)

