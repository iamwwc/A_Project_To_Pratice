#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<math.h>//flag是为了将函数返回的头指针按照不同的区域分给不同的指针
#include "Golbal.h"

int main(void)
{
	int k, ex = 0;
	AS *Ahead = NULL, *Bhead = NULL, *Chead = NULL;
	AS *Parking_Manage(AS *Ahead, AS *Bhead, AS *Chead), *Fee_Manage(AS *Ahead, AS *Bhead, AS *Chead);
	AS *Conditional_Query(AS *Ahead, AS *Bhead, AS *Chead), *head0, *Conditional_Statistics(AS *, AS *, AS *);
	AS *Write_To_Files(AS *, AS *, AS *), *Awrite(AS *Ahead), *Bwrite(AS *Bhead), *Cwrite(AS *Chead), *Aread(), *Bread(), *Cread();
	Ahead = Aread();
	Bhead = Bread();
	Chead = Cread();
	while (1)
	{
		printf("                               停车场管理系统\n");
		printf("                  1:停车管理                    2:收费管理\n");
		printf("                  3:按照不同条件进行查询操作    4:按照不同条件进行统计操作\n");
		printf("                  5:结束当天(时间到达当天22:00)\n");
		scanf("%d", &k);
		getchar();
		switch (k){
		case 1:head0 = Parking_Manage(Ahead, Bhead, Chead); break; //heaad0为了使函数值返回到主函数之后;
		case 2:head0 = Fee_Manage(Ahead, Bhead, Chead); break;//先把地址给head0，然后根据flag的值分别赋值给三个不同的结构体头指针
		case 3:Conditional_Query(Ahead, Bhead, Chead); break;
		case 4:Conditional_Statistics(Ahead, Bhead, Chead); break;
		case 5:ex = 5; break;
		}
		if (ex == 5){
			Write_To_Files(Ahead, Bhead, Chead);
			printf("晚安！\n");
			break;
		}
		if (head0 == NULL)
			flag = 0;
		else if (flag == 1)  	{                            //根据操作的停车场区域的不同将地址赋给不同的头指针
	
			Ahead = head0;
			Awrite(Ahead);
		}	else if (flag == 2)	{
			Bhead = head0;
			Bwrite(Bhead);
		}	else if (flag == 3)	{
			Chead = head0;
			Cwrite(Chead);
		}
	}
	return 0;
}




AS *Parking_Manage(AS *Ahead, AS *Bhead, AS *Chead)                      //停车管理函数
{
	AS *creat(AS *head);
	AS *head = NULL;                            //在整个程序运行过程中，head=NULL只进行一次,在调用相应的函数时，head被不同的头指针赋值
	char Car_Model[20];
	printf("请输入车型\n");
	gets(Car_Model);
	while (1){
		if (strcmp(Car_Model, "小型") == 0) {      //进入A区域的creat函数
			flag = 1;
			head = Ahead;                        //为了使得head承接上一次，为了保证当第二次进入creat函数时head与上一次的head相同
			return creat(head);
		}
		else if (strcmp(Car_Model, "中型") == 0) {
			head = Bhead;
			flag = 2;
			return creat(head);
		}
		else if (strcmp(Car_Model, "大型") == 0) {//进入C区域的creat函数
			head = Chead;
			flag = 3;
			return creat(head);
		}
		else if (strcmp(Car_Model, "小型") != 0
			&& strcmp(Car_Model, "中型") != 0
			&& strcmp(Car_Model, "大型") != 0) {
			printf("您输入的格式不正确，已自动返回上一层\n");
			break;
		}
	}
	return head;
}





AS *Fee_Manage(AS *Ahead, AS *Bhead, AS *Chead)                 //收费管理函数
{
	int tiend1, tiend2, *ti1, *ti2;                                   //tiend是车辆离开时的时间，将时间拆成两个整数，在最后进行时间计算时，先换算成分钟再计算
	char outnum[10], ch0;
	AS *del(AS *, char x[], int *, int *), *head;
	printf("输入当前时间(例如：5:30)\n");
	scanf("%d%c%d", &tiend1, &ch0, &tiend2);
	getchar();
	ti1 = &tiend1;                                                   //ti1,ti2指针是为了将输入的结束时间的地址传入到删除函数里面
	ti2 = &tiend2;
	printf("输入车位号(字母大写)\n");
	gets(outnum);
	if (outnum[0] == 'A') {
		flag = 1;
		head = Ahead;
	}
	else if (outnum[0] == 'B') {
		flag = 2;
		head = Bhead;
	}
	else if (outnum[0] == 'C') {
		flag = 3;
		head = Chead;
	}
	head = del(head, outnum, ti1, ti2);
	return head;                                             //函数返回的头指针始终是head，只不过再返回主函数后根据flag的值判断将head赋值给哪一个头指针
}





AS *Conditional_Query(AS *Ahead, AS *Bhead, AS *Chead)               //条件查询函数
{
	int m;
	AS *Output_Cars_numbers(AS *, AS *, AS *), *Output_Cars_Numbers_Void(AS *, AS *, AS *), *Output_Information(AS *, AS *, AS *), *head = NULL;
	while (1)
	{
		m = 0;
		printf("            1:分别输出A区，B区，C区当前所停放的汽车信息   2:分别输出当前A区，B区，C区当前空闲的车位号\n");
		printf("            3:输入车牌号，输出该车所停放的车位号      4:返回上一层\n");
		scanf("%d", &m);
		getchar();
		switch (m)
		{
		case 1:Output_Information(Ahead, Bhead, Chead); break;
		case 2:Output_Cars_Numbers_Void(Ahead, Bhead, Chead); break;
		case 3:Output_Cars_numbers(Ahead, Bhead, Chead); break;
		case 4:break;
		}
		if (m == 4)
			break;
	}
	return head;
}




AS * Output_Information(AS *Ahead, AS *Bhead, AS *Chead)             //输出当前停放的汽车的信息函数
{
	int i;
	char ch;
	AS *head = NULL, *p1;
	for (i = 1; i <= 3; i++)
	{
		if (i == 1)
		{
			if (Ahead == NULL)
				continue;
			ch = 'A';
			p1 = Ahead->next;
			if (p1 == NULL) {
				printf("A区无车辆停靠\n");
				continue;
			}
			printf("%c区\n", ch);
		}
		if (i == 2) {
			if (Bhead == NULL)
				continue;
			ch = 'B';
			p1 = Bhead->next;
			if (p1 == NULL) {
				printf("B区无车辆停靠\n");
				continue;
			}
			printf("%c区\n", ch);
		}
		if (i == 3) {
			if (Chead == NULL)
				continue;
			ch = 'C';
			p1 = Chead->next;
			if (p1 == NULL) {
				printf("C区无车辆停靠\n");
				continue;
			}
			printf("%c区\n", ch);
		}
		while (p1 != NULL)               //输出的时候根据不同的值判断输出的时候需不需要加0
		{
			if (p1->xuhao <= 9)
				printf("%c0%d\n%s\n%d时%d分\n\n", ch, p1->xuhao, p1->number2, p1->time1, p1->time2);
			else
				printf("%c%d\n%s\n%d时%d分\n\n", ch, p1->xuhao, p1->number2, p1->time1, p1->time2);
			p1 = p1->next;
		}
		putchar('\n');
	}
	return head;                              //因为该函数只是完成了一种操作，所以不需要具体的什么返回值，所以在函数体里面定义了一个head=NULL用来返回调用函数
}





AS *Output_Cars_Numbers_Void(AS *Ahead, AS *Bhead, AS *Chead)        //输出空闲车位号函数
{
	int i, m = 20, j = 1, k = 0;
	char ch = 'A';
	AS *p1, *p2, *head = NULL;
	if (Ahead == NULL) {
		printf("A区域没有车辆，无法输出\n");
		j++;
	}
	else
		p2 = p1 = Ahead->next;
	for (; j <= 3; j++) {
		if (j == 2) {
			if (Bhead == NULL) {
				printf("B区域没有车辆，无法输出\n");
				continue;
			}
			ch = 'B';
			p2 = p1 = Bhead->next;
			m = 15;
		}
		else if (j == 3) {
			if (Chead == NULL) {
				printf("C区域没有车辆，无法输出\n");
				return head;
			}
			ch = 'C';
			p2 = p1 = Chead->next;
			m = 10;
		}
		printf("%c区:空闲车位分别是\n", ch);
		for (i = 1; i <= m; i++) {
			k = 0;
			while (p1 != NULL) {
				if (p1->xuhao == i) {
					k++;
					break;
				}
				p1 = p1->next;
			}
			if (k == 0) {
				if (i <= 9)
					printf("%c0%d\n", ch, i);            //输出的时候根据不同的值判断输出的时候需不需要加0
				else
					printf("%c%d\n", ch, i);
			}
			p1 = p2;                               //重置p1的值，使得p1指向表头结点的next,重新开始对比下一个i的值
		}
	}
	return head;                                           //返回一个空指针就行了，因为这个函数并不需要一个具体的返回值
}





AS *Output_Cars_numbers(AS *Ahead, AS *Bhead, AS *Chead)    //输入车牌号输出车位号函数
{
	int i = 1;
	char Cars_number[50], ch;
	AS *p1, *head = NULL;
	if (Ahead == NULL)                                 //判断一下头指针是不是空，如果是空就直接跳过就行了
		i++;
	else {
		p1 = Ahead->next;
		ch = 'A';
	}
	printf("请输入车牌号（例如：鲁A H1234）\n");
	gets(Cars_number);
	for (; i <= 3; i++) {
		if (i == 2)
			if (Bhead == NULL)                           //判断一下头指针是不是空，如果是空就直接跳过就行了
				continue;
			else {
				ch = 'B';
				p1 = Bhead->next;
			}
			if (i == 3)
				if (Chead == NULL)                           //判断一下头指针是不是空，如果是空就直接跳过就行了
					continue;
				else {
					ch = 'C';
					p1 = Chead->next;
				}
				if (Ahead == NULL
					&&Bhead == NULL
					&&Chead == NULL) {
					printf("停车场内没有一辆车辆\n");
					return head;
				}
				while (p1 != NULL) {
					if (strcmp(Cars_number, p1->number2) == 0) {
						if (p1->xuhao <= 9)
							printf("该车停放的车位号是:%c0%d\n", ch, p1->xuhao);  //输出的时候根据不同的值判断输出的时候需不需要加0
						else
							printf("该车停放的车位号是:%c%d\n", ch, p1->xuhao);
						return head;
					}
					p1 = p1->next;
				}
	}
	printf("没有该车牌号\n");
	return head;
}




AS *Conditional_Statistics(AS *Ahead, AS *Bhead, AS *Chead)           //这是（4）的分别输出所停放的汽车的数量
{
	int i, k;
	char ch = 'A';
	AS *head = NULL, *Five_hours_Statistics(AS *Ahead, AS *Bhead, AS *Chead);
	AS *Charge_Statistics(AS *, AS *, AS *);
	while (1)
	{
		printf("1:分别输出当前停放在A，B，C的汽车的数量 2:输出某一个时间，输出到当前时间为止，停车超过5小时的汽车数量，并输出信息\n");
		printf("3:输入一个日期，统计该月停车场的收费金额                    4:返回上一层\n");
		scanf("%d", &k);
		getchar();
		if (k == 1) {
			for (i = 1; i <= 3; i++) {
				if (i == 1) {
					printf("%c区所停放的汽车的数量是\n", ch);
					printf("%d\n", an);
				}
				else if (i == 2) {
					ch = 'B';
					printf("%c区所停放的汽车的数量是\n", ch);
					printf("%d\n", bn);
				}
				else if (i == 3) {
					ch = 'C';
					printf("%c区所停放的汽车的数量是\n", ch);
					printf("%d\n", cn);
				}
			}
		}
		else if (k == 2)
			Five_hours_Statistics(Ahead, Bhead, Chead);
		else if (k == 3)
			Charge_Statistics(Ahead, Bhead, Chead);
		else if (k == 4)
			break;
	}
	return head;
}



AS *Five_hours_Statistics(AS *Ahead, AS *Bhead, AS *Chead)
{
	int i;
	AS *p = Ahead->next, *head = NULL;                         //函数不需要返回值，head用来返回函数
	char zf, ch = 'A';                                          //用来吸收冒号，无实际作用
	int nowtime1, nowtime2, nowtime0;                     //把所有的时间全部换算成分钟
	printf("请输入当前时间(例如：5:30)\n");
	scanf("%d%c%d", &nowtime1, &zf, &nowtime2);
	nowtime0 = nowtime1 * 60 + nowtime2;
	for (i = 1; i <= 3; i++) {
		if (i == 2) {
			p = Bhead->next;
			ch = 'B';
		}
		else if (i == 3) {
			p = Chead->next;
			ch = 'C';
		}
		while (p != NULL) {
			if (p->nn > 0) {
				if (p->xuhao <= 9)
					printf("车位号:%c0%d\n车牌号:%s\n进入停车场的时间:%d点%d分\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
				else
					printf("车位号:%c%d\n车牌号:%s\n进入停车场的时间:%d点%d分\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
			}
			else {                                              //输出大于300分钟的车
				if (p->xuhao <= 9)
					printf("车位号:%c0%d\n车牌号:%s\n进入停车场的时间:%d点%d分\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
				else
					printf("车位号:%c%d\n车牌号:%s\n进入停车场的时间:%d点%d分\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
			}
			p = p->next;
		}
	}
	return head;                                    //在此返回一个NULL的指针
}



AS *Charge_Statistics(AS *Ahead, AS *Bhead, AS *Chead)  //输入一个日期（年·月），统计该月停车场的收费金额(没还有开始写)
{
	int i, k = 0, j, m, n, q = 0, w = 1, b = 0;
	double wage = 0;
	FILE *fp;
	char dat[200][200], riqi[20];
	printf("请输入你想要搜索的日期(例如：2015年01月)\n");
	gets(riqi);
	if ((fp = fopen("jilu.txt", "r")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	for (i = 0; !feof(fp); i++) {                  //在里面多走了一圈，使得数组最下面一行是个乱码烫烫烫，所以要有一个计数的k，                                           //在下面查找的时候就可以知道一共多少行有效数据了
		fgets(dat[i], 1000, fp);
		k++;
	}

	k--;
	//k-=2;                           //因为在写入文件信息的时候，每次写入完都会加上一个回车，又因为退出循环的条件是!feof(fp)，所以总的来说多循环了2次
	for (i = 0; i<k; i++) {              //所以实际二维数组的行数应该是k-=2;
		w = 1;                         //变量的值每次都要初始化掉
		q = 0;
		if (strstr(dat[i], riqi) != NULL) {            //指向二级字符数组的指针
			b++;
			for (j = 0;; j++) {
				if (*(dat[i] + j) == '.') {
					m = j - 1;                             //指针后退一个指向个位
					n = j + 1;                          //指针前进一个指向十分位
					for (; *(dat[i] + m) != ','; m--)
						wage = wage + (*(dat[i] + m) - 48)*pow(10, q++);
					for (; *(dat[i] + n) >= '0'&&*(dat[i] + n) <= '9'; n++)
						wage = wage + (*(dat[i] + n) - 48)*pow(0.1, w++);
					break;
				}
			}
		}
	}
	if (b != 0)                                   //如果没有要搜索的就不需要有输出语句
		printf("%.2lf\n", wage);
	fclose(fp);
	return 0;
}




AS *creat(AS *head)
{	                                                               //ch0是为了吸收时间之间的冒号
	int store, record = 0, m, i;                                     //store为了暂时存放从表头结点中的xuhao中取出的数值
	AS *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4, *p5 = NULL, *p0;            //head指向的第一个结构体一定是除了number1和next以外都是没有数据的
	char ch1[20] = { 0 }, ch0;         	//ch1是为了临时存放cheweihao的值，然后利用strcpy复制到cheweihao里面
	if (head == NULL)                           //只有在不同的区域开始第一次进入，以后不再进入
	{
		p1 = (AS *)malloc(AD); //程序刚开始运行时的第一个表头结点
		if (p1 == NULL)
		{
			printf("内存分配失败\n");
			exit(0);
		}
		head = p1;                                //整型的xuhao存在的目的是为了当进行结构体的插入时判断插入点
		printf("请输入车牌号\n");
		gets(p1->number2);
		printf("请输入进入停车场的时间(使用英文冒号)\n");
		scanf("%d%c%d", &p1->time1, &ch0, &p1->time2);
		p1->nn = 0;
		if (flag == 1) {
			an++;                            //使对应的结点数加一；
			Amax++;                           //此时Amax==1；
		}
		else if (flag == 2) {
			bn++;
			Bmax++;
		}
		else if (flag == 3) {
			cn++;
			Cmax++;
		}
		p2 = p1;                                 //为了使得下面新创建的p1与上一个p2结构体连接起来
		p1->xuhao = 1;                            //1是第一个结构体,xuhao也就是车位号的整数部分；
		p1->next = NULL;
		p1 = (AS *)malloc(AD);  //第一次创建结构体时，当离开函数的时候要创建一个表头结点
		if (p1 == NULL) {
			printf("error");
			exit(0);
		}

		p1->number1[0] = 'X'; //在车辆进入停车场并且还未有车辆离开的过程当中，将表头结点的number1赋值X表示还未有最小的空闲车位
		p1->number1[1] = 0;   //方便在以后插入的时候可以直接通过比较数字大小来确定插入点;
							  //每次创建一个新的结构体，在结构体的xuhao变量中要写入这个车位号的数字部分;
		p1->next = p2;
		head = p1;
		return head;                          //到此第一辆车进入之后的链表已经创建完毕
											  //free(p1);                              //不能释放p1，因为题目要求需要表头结点
	}                                          //第一次创建结束，函数结束；
	else {
		p5 = head;              //head!=NULL则进入else
		p0 = p2 = p3 = p4 = head->next;
		if (head->number1[0] == 'X')//判断一下表头结点中是否含有最小空闲车位，等于X就说明没有最小车位，但是空间还没有开辟
		{                      //如果是X那么xuhao久不需要添加数值了，车辆离开后要判断车位是否在末端，如果在，那么直接删除车位，表头结点X不变,xuhao不赋值                              //进入不同的区域
			if (an == 20 && flag == 1) {                             //先输入信息再使节点数加一；
																	 //所以对于A来说，当结点数为15时，已经到达了最大长度，所以不能够继续添加
				printf("没有空闲的车位!\n");
				return head;
			}
			else if (bn == 15 && flag == 2) {
				printf("没有空闲的车位!\n");
				return head;
			}
			else if (cn == 10 && flag == 3) {
				printf("没有空闲的车位!\n");
				return head;
			}

			p1 = (AS *)malloc(AD);           //程序走进这里就说明有空闲的车位，允许进入
			if (p1 == NULL) {
				printf("区域内存分配失败\n");
				exit(0);
			}
			printf("请输入车牌号\n");                     //当第二次进入creat函数的时候，由于已经有了一个表头结构体，所以将数据先写入该结构体；
			gets(p1->number2);                             //并且最后再离开结构体的时候需要再创建一个新的表头结构体；
			printf("请输入进入停车场的时间(例如: 5:30)\n");
			scanf("%d%c%d", &p1->time1, &ch0, &p1->time2);
			p1->nn = 0;
			if (flag == 1) {                            //判断进入的区域，并且使对应的区域的节点数加一,也就是车辆多了一个
				m = 20;
				an++;
				head->xuhao = p1->xuhao = ++Amax;
			}
			else if (flag == 2) {
				m = 15;
				bn++;
				head->xuhao = p1->xuhao = ++Bmax;
			}
			else if (flag == 3) {
				m = 10;
				cn++;
				head->xuhao = p1->xuhao = ++Cmax;
			}

			while (p3->next != NULL)               //p1开辟的空间中的数据已经输入完毕，下面就开始用循环找插入点
				p3 = p3->next;                        //寻找链表的末尾
			p3->next = p1;
			p1->next = NULL;
			return head;
		}
		else {                             //表头结点不是X，也就是有最小空闲车位,这时候需要将表头结点中的xuhao取出来给p1开辟的车位
			if (flag == 1) {
				an++;
				m = 20;
			}
			else if (flag == 2) {
				bn++;
				m = 15;
			}
			else if (flag == 3) {
				cn++;
				m = 10;
			}
			p1 = (AS *)malloc(AD);
			if (p1 == NULL) {
				printf("区域内存分配失败\n");
				exit(0);
			}
			printf("请输入车牌号\n");
			gets(p1->number2);
			printf("请输入进入停车场的时间(例如: 5:30)\n");
			scanf("%d%c%d", &p1->time1, &ch0, &p1->time2);
			p1->nn = 0;
			store = head->xuhao;                            //将表头结点的数字暂时先放到store
			p1->xuhao = store;
			while (p4->xuhao<store&&p4->next != NULL) {         //删除第一个A01后，表头指针直接与A02相连，所以检索的时候肯定不会检索到1
																//这里是寻找新的车辆的插入点
				p5 = p4;
				p4 = p4->next;
			}
			if (p4->xuhao>store) {
				p5->next = p1;
				p1->next = p4;
			}
			if (p4->next == NULL) {       //p4把值给了p5，p5指向了最后一个

				(p5->next)->next = p1;
				p1->next = NULL;
			}//删除第一个A01后，表头指针直接与A02相连，所以检索的时候肯定不会检索到1
			p2 = head->next;      //如果不加上这一句会有bug,如果插入的是01，由于p2指向的是02,为了从头开始搜索，所以要重新要p2指向第一个车位
			for (i = 1; i <= m; i++) {
				while (p2 != NULL) {
					if (p2->xuhao == i)
						break;
					p2 = p2->next;
				}
				if (p2 == NULL) {
					record = i;
					break;
				}
				p2 = p0;
			}
			if (record == 0) {//record是找到的排除刚才插入的车位号的空闲的车位

				head->number1[0] = 'X';
				head->number1[1] = 0;
			}
			else {              //成立就说明有空闲车位，所以要改成Z，Z表示有空闲车位

				head->number1[0] = 'Z';
				head->number1[1] = 0;
				head->xuhao = record;
			}
		}
		return head;
	}
}





AS *del(AS *head, char outnum[], int *ti1, int *ti2)             //删除函数
{
	int look, tiji1, tiji2, tiji, record = 0, i, m, kk;             //tiji1,tiji2分别是两个时间小时与分钟相减得到的差；
	AS *p1, *p2 = head, *p3 = NULL, *_p0, *_p2;
	if (head == NULL) {
		printf("该区域没有车辆停放\n");
		return head;
	}
	p1 = head->next;
	look = (outnum[1] - 48) * 10 + (outnum[2] - 48);      //look存储的是将车位号中的数字部分转换成的整数，便于和结构体中的xuhao比较大小
	while (look != p1->xuhao&&p1->next != NULL) {
		p2 = p1;
		p1 = p1->next;
	}
	if (look == p1->xuhao) {                 //找到了该车辆,并且p1就是要删除的车辆

		if (p1->next == NULL) {               //如果要删除的结点在最后，那么最大车位号就要是上一个车位的序号

			if (flag == 1)
				Amax = p2->xuhao;
			else if (flag == 2)
				Bmax = p2->xuhao;
			else if (flag == 3)
				Cmax = p2->xuhao;
		}
		if (flag == 1)
			an--;
		else if (flag == 2)
			bn--;
		else if (flag == 3)
			cn--;
		p2->next = p1->next;
	}                               //先将尾首相接,p1如果是空，那么p2->next就成了NULL，道理都差不多
	if (look<head->xuhao) {         //成立就是look就是最小空闲车位

		head->number1[0] = 'Z';//开头不是再是X了，要换成别的了,Z表示有空闲车位
		head->number1[1] = '0';
		head->xuhao = look; //更换表头结点的xuhao
	}                 //成立则说明该车位要成为空闲车位,表头结点的cheweihao和xuhao需要更换，并且look肯定不等于p1->xuhao
	_p0 = _p2 = head->next;      //如果不加上这一句会有bug,如果插入的是01，由于p2指向的是02,为了从头开始搜索，所以要重新要p2指向第一个车位
	if (flag == 1)
		m = 20;
	else if (flag == 2)
		m = 15;
	else if (flag == 3)
		m = 10;
	for (i = 1; i <= m; i++) {//找最小空闲车位，删除和创建之后都要找一次最小空闲车位

		while (_p2 != NULL) {
			if (_p2->xuhao == i)
				break;
			_p2 = _p2->next;
		}
		if (_p2 == NULL) {
			record = i;
			break;
		}
		_p2 = _p0;
	}
	if (record == 0) {//record是找到的排除刚才插入的车位号的空闲的车位

		head->number1[0] = 'X';
		head->number1[1] = 0;
	}
	else {
		head->number1[0] = 'Z';
		head->number1[1] = 0;
		head->xuhao = record;
	}
	if (p1->nn>0)                //如果第一天(nn=0)的话就不能+24
		kk = 1;
	else                              //ti1和ti2分别是离开时的几时几分
		kk = 0;
	tiji1 = *ti1 * 60 + *ti2;                        //离开时的分钟数
	tiji2 = p1->time1 * 60 + p1->time2;           //进入时的分钟数，两个相减+24得到两天的停留的分钟数(将完整的天数移走之后假设这两天是连续的)
	tiji = p1->nn * 24 * 60 + 24 * kk * 60 + tiji1 - tiji2;            //将在停车场停留的时间换算成分钟
	if (tiji <= 30) {
		if (flag == 1)
			money = 1.5 + money;
		else if (flag == 2)
			money = 2 + money;
		else if (flag == 3)
			money = 2.5 + money;
	}
	else
		if (tiji>30 && tiji <= 60) {
			if (flag == 1)
				money = 3 + money;
			else if (flag = 2)
				money = 4 + money;
			else if (flag == 3)
				money = 5 + money;
		}
		else {
			if (flag == 1)
				money = tiji / 60 * 3 + money;
			else if (flag == 2)
				money = tiji / 60 * 4 + money;
			else if (flag == 3)
				money = tiji / 60 * 5 + money;
		}
		if (p1->next == NULL)
			if (p1->xuhao != look) {
				printf("没有该车辆\n");
				return head;
			}
		free(p1);
		printf("车辆离开完成\n");
		return head;
}



AS *Write_To_Files(AS *Ahead, AS *Bhead, AS *Chead)        //将当天的收入写入文件
{
	AS *head = NULL, *Awrite(AS *), *Bwrite(AS *), *Cwrite(AS *);
	FILE *fp;                                     //开始将费用写入文件
	char date[100];                               //往文件里保存时放在开头的日期,也就是当天的日期
	printf("             请先输入当天的日期（例如:2016年05月01日）\n");
	gets(date);                           //date存放日期,是为了在写入文件的时候直接以字符串的形式写入
	if ((fp = fopen("jilu.txt", "a+")) == NULL)        //对文件进行操作
	{
		printf("can not open file!\n");
		exit(0);
	}
	else {                                     //打开文件成功，先计算时间，将时间转换成分钟进行计算

		fputs(date, fp);
		fputc(',', fp);
		fprintf(fp, "%.2lf元\n", money);
	}
	fclose(fp);
	//Awrite(Ahead);
	// Bwrite(Bhead);
	//Cwrite(Chead);
	return head;
}



AS *Awrite(AS *Ahead)
{
	FILE *Afp;
	AS *p1 = Ahead;
	if ((Afp = fopen("A区域未离开的车辆.dat", "wb")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	fprintf(Afp, "%d", an);
	while (p1 != NULL) {
		p1->nn++;                 //进入下一天，计时器+1方便下面计算隔天的费用
		fwrite(p1, AD, 1, Afp);
		p1 = p1->next;
	}
	fclose(Afp);
	return Ahead;
}


AS *Bwrite(AS *Bhead)
{
	FILE *Bfp;
	AS *p1 = Bhead;
	if ((Bfp = fopen("B区域未离开的车辆.dat", "wb")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	fprintf(Bfp, "%d", bn);
	while (p1 != NULL) {
		p1->nn++;                 //进入下一天，计时器+1方便下面计算隔天的费用
		fwrite(p1, AD, 1, Bfp);
		p1 = p1->next;
	}
	fclose(Bfp);
	return Bhead;
}




AS *Cwrite(AS *Chead)
{
	FILE *Cfp;
	AS *p1 = Chead;
	if ((Cfp = fopen("C区域未离开的车辆.dat", "wb")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	fprintf(Cfp, "%d", cn);
	while (p1 != NULL) {
		p1->nn++;                 //进入下一天，计时器+1方便下面计算隔天的费用
		fwrite(p1, AD, 1, Cfp);
		p1 = p1->next;
	}
	fclose(Cfp);
	return Chead;
}



AS *Aread()
{
	int k;
	AS *p1, *p2, *head = NULL;
	FILE *Afp;
	if ((Afp = fopen("A区域未离开的车辆.dat", "ab+")) == NULL)
	{
		printf("can not open the file!\n");
		exit(0);
	}
	rewind(Afp);                  //因为第一次打开程序并没有这个文件，所以不能用rb，又为了读取文件的时候不能覆盖源文件
	fscanf(Afp, "%d", &an);         //所以不能用wb,所以只能用ab+(ab是写追加),为了指针复原，所以用rewind
	k = an;
	if (k == 0)                           //第一次打开文件之后，k==0，所以返回一个空的head赋值给Ahead，从头开始创建链表
		return head;
	k++;                                  //因为表头结点一起读出来，所以k的值应该是节点数+1；
	p1 = (AS *)malloc(AD);           //先开辟第一个表头结点
	if (p1 == NULL)
	{
		printf("error");
		exit(0);
	}
	p2 = head = p1;                           //表头结点先和head连接起来
	while (k--)                           //读出来的时候表头结点一并读出来
	{
		fread(p1, AD, 1, Afp);
		p2 = p1;
		p1 = (AS *)malloc(AD);
		if (p1 == NULL)
		{
			printf("error");
			exit(0);
		}
		p2->next = p1;
	}
	p2->next = NULL;
	free(p1);
	fclose(Afp);
	return head;
}





AS *Bread()
{
	int k;
	AS *p1, *p2, *head = NULL;
	FILE *Bfp;
	if ((Bfp = fopen("B区域未离开的车辆.dat", "ab+")) == NULL)
	{
		printf("can not open the file!\n");
		exit(0);
	}
	rewind(Bfp);
	fscanf(Bfp, "%d", &bn);
	k = bn;
	if (k == 0)
		return head;
	k++;
	p1 = (AS *)malloc(AD);                      //先开辟第一个表头结点
	if (p1 == NULL) {
		printf("error");
		exit(0);
	}
	p2 = head = p1;                         //先读取表头结点
	while (k--) {
		fread(p1, AD, 1, Bfp);
		p2 = p1;
		p1 = (AS *)malloc(AD);               //再开辟第一个停车位
		if (p1 == NULL) {
			printf("error");
			exit(0);
		}
		p2->next = p1;
	}
	p2->next = NULL;
	free(p1);
	fclose(Bfp);
	return head;
}





AS *Cread()
{
	int k;
	AS *p1, *p2, *head = NULL;
	FILE *Cfp;
	if ((Cfp = fopen("C区域未离开的车辆.dat", "ab+")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	rewind(Cfp);
	fscanf(Cfp, "%d", &cn);
	k = cn;
	if (k == 0)
		return head;
	k++;
	p1 = (AS *)malloc(AD);           //先开辟第一个表头结点
	if (p1 == NULL) {
		printf("error");
		exit(0);
	}
	p2 = head = p1;                                              //先读取表头结点
	while (k--) {
		fread(p1, AD, 1, Cfp);
		p2 = p1;
		p1 = (AS *)malloc(AD);               //再开辟第一个停车位
		if (p1 == NULL) {
			printf("error");
			exit(0);
		}
		p2->next = p1;
	}
	p2->next = NULL;
	free(p1);
	fclose(Cfp);
	return head;
}

