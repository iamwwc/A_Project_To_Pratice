#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<math.h>//flag��Ϊ�˽��������ص�ͷָ�밴�ղ�ͬ������ָ���ͬ��ָ��
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
		printf("                               ͣ��������ϵͳ\n");
		printf("                  1:ͣ������                    2:�շѹ���\n");
		printf("                  3:���ղ�ͬ�������в�ѯ����    4:���ղ�ͬ��������ͳ�Ʋ���\n");
		printf("                  5:��������(ʱ�䵽�ﵱ��22:00)\n");
		scanf("%d", &k);
		getchar();
		switch (k){
		case 1:head0 = Parking_Manage(Ahead, Bhead, Chead); break; //heaad0Ϊ��ʹ����ֵ���ص�������֮��;
		case 2:head0 = Fee_Manage(Ahead, Bhead, Chead); break;//�Ȱѵ�ַ��head0��Ȼ�����flag��ֵ�ֱ�ֵ��������ͬ�Ľṹ��ͷָ��
		case 3:Conditional_Query(Ahead, Bhead, Chead); break;
		case 4:Conditional_Statistics(Ahead, Bhead, Chead); break;
		case 5:ex = 5; break;
		}
		if (ex == 5){
			Write_To_Files(Ahead, Bhead, Chead);
			printf("����\n");
			break;
		}
		if (head0 == NULL)
			flag = 0;
		else if (flag == 1)  	{                            //���ݲ�����ͣ��������Ĳ�ͬ����ַ������ͬ��ͷָ��
	
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




AS *Parking_Manage(AS *Ahead, AS *Bhead, AS *Chead)                      //ͣ��������
{
	AS *creat(AS *head);
	AS *head = NULL;                            //�������������й����У�head=NULLֻ����һ��,�ڵ�����Ӧ�ĺ���ʱ��head����ͬ��ͷָ�븳ֵ
	char Car_Model[20];
	printf("�����복��\n");
	gets(Car_Model);
	while (1){
		if (strcmp(Car_Model, "С��") == 0) {      //����A�����creat����
			flag = 1;
			head = Ahead;                        //Ϊ��ʹ��head�н���һ�Σ�Ϊ�˱�֤���ڶ��ν���creat����ʱhead����һ�ε�head��ͬ
			return creat(head);
		}
		else if (strcmp(Car_Model, "����") == 0) {
			head = Bhead;
			flag = 2;
			return creat(head);
		}
		else if (strcmp(Car_Model, "����") == 0) {//����C�����creat����
			head = Chead;
			flag = 3;
			return creat(head);
		}
		else if (strcmp(Car_Model, "С��") != 0
			&& strcmp(Car_Model, "����") != 0
			&& strcmp(Car_Model, "����") != 0) {
			printf("������ĸ�ʽ����ȷ�����Զ�������һ��\n");
			break;
		}
	}
	return head;
}





AS *Fee_Manage(AS *Ahead, AS *Bhead, AS *Chead)                 //�շѹ�����
{
	int tiend1, tiend2, *ti1, *ti2;                                   //tiend�ǳ����뿪ʱ��ʱ�䣬��ʱ����������������������ʱ�����ʱ���Ȼ���ɷ����ټ���
	char outnum[10], ch0;
	AS *del(AS *, char x[], int *, int *), *head;
	printf("���뵱ǰʱ��(���磺5:30)\n");
	scanf("%d%c%d", &tiend1, &ch0, &tiend2);
	getchar();
	ti1 = &tiend1;                                                   //ti1,ti2ָ����Ϊ�˽�����Ľ���ʱ��ĵ�ַ���뵽ɾ����������
	ti2 = &tiend2;
	printf("���복λ��(��ĸ��д)\n");
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
	return head;                                             //�������ص�ͷָ��ʼ����head��ֻ�����ٷ��������������flag��ֵ�жϽ�head��ֵ����һ��ͷָ��
}





AS *Conditional_Query(AS *Ahead, AS *Bhead, AS *Chead)               //������ѯ����
{
	int m;
	AS *Output_Cars_numbers(AS *, AS *, AS *), *Output_Cars_Numbers_Void(AS *, AS *, AS *), *Output_Information(AS *, AS *, AS *), *head = NULL;
	while (1)
	{
		m = 0;
		printf("            1:�ֱ����A����B����C����ǰ��ͣ�ŵ�������Ϣ   2:�ֱ������ǰA����B����C����ǰ���еĳ�λ��\n");
		printf("            3:���복�ƺţ�����ó���ͣ�ŵĳ�λ��      4:������һ��\n");
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




AS * Output_Information(AS *Ahead, AS *Bhead, AS *Chead)             //�����ǰͣ�ŵ���������Ϣ����
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
				printf("A���޳���ͣ��\n");
				continue;
			}
			printf("%c��\n", ch);
		}
		if (i == 2) {
			if (Bhead == NULL)
				continue;
			ch = 'B';
			p1 = Bhead->next;
			if (p1 == NULL) {
				printf("B���޳���ͣ��\n");
				continue;
			}
			printf("%c��\n", ch);
		}
		if (i == 3) {
			if (Chead == NULL)
				continue;
			ch = 'C';
			p1 = Chead->next;
			if (p1 == NULL) {
				printf("C���޳���ͣ��\n");
				continue;
			}
			printf("%c��\n", ch);
		}
		while (p1 != NULL)               //�����ʱ����ݲ�ͬ��ֵ�ж������ʱ���費��Ҫ��0
		{
			if (p1->xuhao <= 9)
				printf("%c0%d\n%s\n%dʱ%d��\n\n", ch, p1->xuhao, p1->number2, p1->time1, p1->time2);
			else
				printf("%c%d\n%s\n%dʱ%d��\n\n", ch, p1->xuhao, p1->number2, p1->time1, p1->time2);
			p1 = p1->next;
		}
		putchar('\n');
	}
	return head;                              //��Ϊ�ú���ֻ�������һ�ֲ��������Բ���Ҫ�����ʲô����ֵ�������ں��������涨����һ��head=NULL�������ص��ú���
}





AS *Output_Cars_Numbers_Void(AS *Ahead, AS *Bhead, AS *Chead)        //������г�λ�ź���
{
	int i, m = 20, j = 1, k = 0;
	char ch = 'A';
	AS *p1, *p2, *head = NULL;
	if (Ahead == NULL) {
		printf("A����û�г������޷����\n");
		j++;
	}
	else
		p2 = p1 = Ahead->next;
	for (; j <= 3; j++) {
		if (j == 2) {
			if (Bhead == NULL) {
				printf("B����û�г������޷����\n");
				continue;
			}
			ch = 'B';
			p2 = p1 = Bhead->next;
			m = 15;
		}
		else if (j == 3) {
			if (Chead == NULL) {
				printf("C����û�г������޷����\n");
				return head;
			}
			ch = 'C';
			p2 = p1 = Chead->next;
			m = 10;
		}
		printf("%c��:���г�λ�ֱ���\n", ch);
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
					printf("%c0%d\n", ch, i);            //�����ʱ����ݲ�ͬ��ֵ�ж������ʱ���費��Ҫ��0
				else
					printf("%c%d\n", ch, i);
			}
			p1 = p2;                               //����p1��ֵ��ʹ��p1ָ���ͷ����next,���¿�ʼ�Ա���һ��i��ֵ
		}
	}
	return head;                                           //����һ����ָ������ˣ���Ϊ�������������Ҫһ������ķ���ֵ
}





AS *Output_Cars_numbers(AS *Ahead, AS *Bhead, AS *Chead)    //���복�ƺ������λ�ź���
{
	int i = 1;
	char Cars_number[50], ch;
	AS *p1, *head = NULL;
	if (Ahead == NULL)                                 //�ж�һ��ͷָ���ǲ��ǿգ�����ǿվ�ֱ������������
		i++;
	else {
		p1 = Ahead->next;
		ch = 'A';
	}
	printf("�����복�ƺţ����磺³A H1234��\n");
	gets(Cars_number);
	for (; i <= 3; i++) {
		if (i == 2)
			if (Bhead == NULL)                           //�ж�һ��ͷָ���ǲ��ǿգ�����ǿվ�ֱ������������
				continue;
			else {
				ch = 'B';
				p1 = Bhead->next;
			}
			if (i == 3)
				if (Chead == NULL)                           //�ж�һ��ͷָ���ǲ��ǿգ�����ǿվ�ֱ������������
					continue;
				else {
					ch = 'C';
					p1 = Chead->next;
				}
				if (Ahead == NULL
					&&Bhead == NULL
					&&Chead == NULL) {
					printf("ͣ������û��һ������\n");
					return head;
				}
				while (p1 != NULL) {
					if (strcmp(Cars_number, p1->number2) == 0) {
						if (p1->xuhao <= 9)
							printf("�ó�ͣ�ŵĳ�λ����:%c0%d\n", ch, p1->xuhao);  //�����ʱ����ݲ�ͬ��ֵ�ж������ʱ���費��Ҫ��0
						else
							printf("�ó�ͣ�ŵĳ�λ����:%c%d\n", ch, p1->xuhao);
						return head;
					}
					p1 = p1->next;
				}
	}
	printf("û�иó��ƺ�\n");
	return head;
}




AS *Conditional_Statistics(AS *Ahead, AS *Bhead, AS *Chead)           //���ǣ�4���ķֱ������ͣ�ŵ�����������
{
	int i, k;
	char ch = 'A';
	AS *head = NULL, *Five_hours_Statistics(AS *Ahead, AS *Bhead, AS *Chead);
	AS *Charge_Statistics(AS *, AS *, AS *);
	while (1)
	{
		printf("1:�ֱ������ǰͣ����A��B��C������������ 2:���ĳһ��ʱ�䣬�������ǰʱ��Ϊֹ��ͣ������5Сʱ�������������������Ϣ\n");
		printf("3:����һ�����ڣ�ͳ�Ƹ���ͣ�������շѽ��                    4:������һ��\n");
		scanf("%d", &k);
		getchar();
		if (k == 1) {
			for (i = 1; i <= 3; i++) {
				if (i == 1) {
					printf("%c����ͣ�ŵ�������������\n", ch);
					printf("%d\n", an);
				}
				else if (i == 2) {
					ch = 'B';
					printf("%c����ͣ�ŵ�������������\n", ch);
					printf("%d\n", bn);
				}
				else if (i == 3) {
					ch = 'C';
					printf("%c����ͣ�ŵ�������������\n", ch);
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
	AS *p = Ahead->next, *head = NULL;                         //��������Ҫ����ֵ��head�������غ���
	char zf, ch = 'A';                                          //��������ð�ţ���ʵ������
	int nowtime1, nowtime2, nowtime0;                     //�����е�ʱ��ȫ������ɷ���
	printf("�����뵱ǰʱ��(���磺5:30)\n");
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
					printf("��λ��:%c0%d\n���ƺ�:%s\n����ͣ������ʱ��:%d��%d��\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
				else
					printf("��λ��:%c%d\n���ƺ�:%s\n����ͣ������ʱ��:%d��%d��\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
			}
			else {                                              //�������300���ӵĳ�
				if (p->xuhao <= 9)
					printf("��λ��:%c0%d\n���ƺ�:%s\n����ͣ������ʱ��:%d��%d��\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
				else
					printf("��λ��:%c%d\n���ƺ�:%s\n����ͣ������ʱ��:%d��%d��\n\n", ch, p->xuhao, p->number2, p->time1, p->time2);
			}
			p = p->next;
		}
	}
	return head;                                    //�ڴ˷���һ��NULL��ָ��
}



AS *Charge_Statistics(AS *Ahead, AS *Bhead, AS *Chead)  //����һ�����ڣ��ꡤ�£���ͳ�Ƹ���ͣ�������շѽ��(û���п�ʼд)
{
	int i, k = 0, j, m, n, q = 0, w = 1, b = 0;
	double wage = 0;
	FILE *fp;
	char dat[200][200], riqi[20];
	printf("����������Ҫ����������(���磺2015��01��)\n");
	gets(riqi);
	if ((fp = fopen("jilu.txt", "r")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	for (i = 0; !feof(fp); i++) {                  //�����������һȦ��ʹ������������һ���Ǹ����������̣�����Ҫ��һ��������k��                                           //��������ҵ�ʱ��Ϳ���֪��һ����������Ч������
		fgets(dat[i], 1000, fp);
		k++;
	}

	k--;
	//k-=2;                           //��Ϊ��д���ļ���Ϣ��ʱ��ÿ��д���궼�����һ���س�������Ϊ�˳�ѭ����������!feof(fp)�������ܵ���˵��ѭ����2��
	for (i = 0; i<k; i++) {              //����ʵ�ʶ�ά���������Ӧ����k-=2;
		w = 1;                         //������ֵÿ�ζ�Ҫ��ʼ����
		q = 0;
		if (strstr(dat[i], riqi) != NULL) {            //ָ������ַ������ָ��
			b++;
			for (j = 0;; j++) {
				if (*(dat[i] + j) == '.') {
					m = j - 1;                             //ָ�����һ��ָ���λ
					n = j + 1;                          //ָ��ǰ��һ��ָ��ʮ��λ
					for (; *(dat[i] + m) != ','; m--)
						wage = wage + (*(dat[i] + m) - 48)*pow(10, q++);
					for (; *(dat[i] + n) >= '0'&&*(dat[i] + n) <= '9'; n++)
						wage = wage + (*(dat[i] + n) - 48)*pow(0.1, w++);
					break;
				}
			}
		}
	}
	if (b != 0)                                   //���û��Ҫ�����ľͲ���Ҫ��������
		printf("%.2lf\n", wage);
	fclose(fp);
	return 0;
}




AS *creat(AS *head)
{	                                                               //ch0��Ϊ������ʱ��֮���ð��
	int store, record = 0, m, i;                                     //storeΪ����ʱ��Ŵӱ�ͷ����е�xuhao��ȡ������ֵ
	AS *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4, *p5 = NULL, *p0;            //headָ��ĵ�һ���ṹ��һ���ǳ���number1��next���ⶼ��û�����ݵ�
	char ch1[20] = { 0 }, ch0;         	//ch1��Ϊ����ʱ���cheweihao��ֵ��Ȼ������strcpy���Ƶ�cheweihao����
	if (head == NULL)                           //ֻ���ڲ�ͬ������ʼ��һ�ν��룬�Ժ��ٽ���
	{
		p1 = (AS *)malloc(AD); //����տ�ʼ����ʱ�ĵ�һ����ͷ���
		if (p1 == NULL)
		{
			printf("�ڴ����ʧ��\n");
			exit(0);
		}
		head = p1;                                //���͵�xuhao���ڵ�Ŀ����Ϊ�˵����нṹ��Ĳ���ʱ�жϲ����
		printf("�����복�ƺ�\n");
		gets(p1->number2);
		printf("���������ͣ������ʱ��(ʹ��Ӣ��ð��)\n");
		scanf("%d%c%d", &p1->time1, &ch0, &p1->time2);
		p1->nn = 0;
		if (flag == 1) {
			an++;                            //ʹ��Ӧ�Ľ������һ��
			Amax++;                           //��ʱAmax==1��
		}
		else if (flag == 2) {
			bn++;
			Bmax++;
		}
		else if (flag == 3) {
			cn++;
			Cmax++;
		}
		p2 = p1;                                 //Ϊ��ʹ�������´�����p1����һ��p2�ṹ����������
		p1->xuhao = 1;                            //1�ǵ�һ���ṹ��,xuhaoҲ���ǳ�λ�ŵ��������֣�
		p1->next = NULL;
		p1 = (AS *)malloc(AD);  //��һ�δ����ṹ��ʱ�����뿪������ʱ��Ҫ����һ����ͷ���
		if (p1 == NULL) {
			printf("error");
			exit(0);
		}

		p1->number1[0] = 'X'; //�ڳ�������ͣ�������һ�δ�г����뿪�Ĺ��̵��У�����ͷ����number1��ֵX��ʾ��δ����С�Ŀ��г�λ
		p1->number1[1] = 0;   //�������Ժ�����ʱ�����ֱ��ͨ���Ƚ����ִ�С��ȷ�������;
							  //ÿ�δ���һ���µĽṹ�壬�ڽṹ���xuhao������Ҫд�������λ�ŵ����ֲ���;
		p1->next = p2;
		head = p1;
		return head;                          //���˵�һ��������֮��������Ѿ��������
											  //free(p1);                              //�����ͷ�p1����Ϊ��ĿҪ����Ҫ��ͷ���
	}                                          //��һ�δ�������������������
	else {
		p5 = head;              //head!=NULL�����else
		p0 = p2 = p3 = p4 = head->next;
		if (head->number1[0] == 'X')//�ж�һ�±�ͷ������Ƿ�����С���г�λ������X��˵��û����С��λ�����ǿռ仹û�п���
		{                      //�����X��ôxuhao�ò���Ҫ�����ֵ�ˣ������뿪��Ҫ�жϳ�λ�Ƿ���ĩ�ˣ�����ڣ���ôֱ��ɾ����λ����ͷ���X����,xuhao����ֵ                              //���벻ͬ������
			if (an == 20 && flag == 1) {                             //��������Ϣ��ʹ�ڵ�����һ��
																	 //���Զ���A��˵���������Ϊ15ʱ���Ѿ���������󳤶ȣ����Բ��ܹ��������
				printf("û�п��еĳ�λ!\n");
				return head;
			}
			else if (bn == 15 && flag == 2) {
				printf("û�п��еĳ�λ!\n");
				return head;
			}
			else if (cn == 10 && flag == 3) {
				printf("û�п��еĳ�λ!\n");
				return head;
			}

			p1 = (AS *)malloc(AD);           //�����߽������˵���п��еĳ�λ���������
			if (p1 == NULL) {
				printf("�����ڴ����ʧ��\n");
				exit(0);
			}
			printf("�����복�ƺ�\n");                     //���ڶ��ν���creat������ʱ�������Ѿ�����һ����ͷ�ṹ�壬���Խ�������д��ýṹ�壻
			gets(p1->number2);                             //����������뿪�ṹ���ʱ����Ҫ�ٴ���һ���µı�ͷ�ṹ�壻
			printf("���������ͣ������ʱ��(����: 5:30)\n");
			scanf("%d%c%d", &p1->time1, &ch0, &p1->time2);
			p1->nn = 0;
			if (flag == 1) {                            //�жϽ�������򣬲���ʹ��Ӧ������Ľڵ�����һ,Ҳ���ǳ�������һ��
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

			while (p3->next != NULL)               //p1���ٵĿռ��е������Ѿ�������ϣ�����Ϳ�ʼ��ѭ���Ҳ����
				p3 = p3->next;                        //Ѱ�������ĩβ
			p3->next = p1;
			p1->next = NULL;
			return head;
		}
		else {                             //��ͷ��㲻��X��Ҳ��������С���г�λ,��ʱ����Ҫ����ͷ����е�xuhaoȡ������p1���ٵĳ�λ
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
				printf("�����ڴ����ʧ��\n");
				exit(0);
			}
			printf("�����복�ƺ�\n");
			gets(p1->number2);
			printf("���������ͣ������ʱ��(����: 5:30)\n");
			scanf("%d%c%d", &p1->time1, &ch0, &p1->time2);
			p1->nn = 0;
			store = head->xuhao;                            //����ͷ����������ʱ�ȷŵ�store
			p1->xuhao = store;
			while (p4->xuhao<store&&p4->next != NULL) {         //ɾ����һ��A01�󣬱�ͷָ��ֱ����A02���������Լ�����ʱ��϶����������1
																//������Ѱ���µĳ����Ĳ����
				p5 = p4;
				p4 = p4->next;
			}
			if (p4->xuhao>store) {
				p5->next = p1;
				p1->next = p4;
			}
			if (p4->next == NULL) {       //p4��ֵ����p5��p5ָ�������һ��

				(p5->next)->next = p1;
				p1->next = NULL;
			}//ɾ����һ��A01�󣬱�ͷָ��ֱ����A02���������Լ�����ʱ��϶����������1
			p2 = head->next;      //�����������һ�����bug,����������01������p2ָ�����02,Ϊ�˴�ͷ��ʼ����������Ҫ����Ҫp2ָ���һ����λ
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
			if (record == 0) {//record���ҵ����ų��ղŲ���ĳ�λ�ŵĿ��еĳ�λ

				head->number1[0] = 'X';
				head->number1[1] = 0;
			}
			else {              //������˵���п��г�λ������Ҫ�ĳ�Z��Z��ʾ�п��г�λ

				head->number1[0] = 'Z';
				head->number1[1] = 0;
				head->xuhao = record;
			}
		}
		return head;
	}
}





AS *del(AS *head, char outnum[], int *ti1, int *ti2)             //ɾ������
{
	int look, tiji1, tiji2, tiji, record = 0, i, m, kk;             //tiji1,tiji2�ֱ�������ʱ��Сʱ���������õ��Ĳ
	AS *p1, *p2 = head, *p3 = NULL, *_p0, *_p2;
	if (head == NULL) {
		printf("������û�г���ͣ��\n");
		return head;
	}
	p1 = head->next;
	look = (outnum[1] - 48) * 10 + (outnum[2] - 48);      //look�洢���ǽ���λ���е����ֲ���ת���ɵ����������ںͽṹ���е�xuhao�Ƚϴ�С
	while (look != p1->xuhao&&p1->next != NULL) {
		p2 = p1;
		p1 = p1->next;
	}
	if (look == p1->xuhao) {                 //�ҵ��˸ó���,����p1����Ҫɾ���ĳ���

		if (p1->next == NULL) {               //���Ҫɾ���Ľ���������ô���λ�ž�Ҫ����һ����λ�����

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
	}                               //�Ƚ�β�����,p1����ǿգ���ôp2->next�ͳ���NULL���������
	if (look<head->xuhao) {         //��������look������С���г�λ

		head->number1[0] = 'Z';//��ͷ��������X�ˣ�Ҫ���ɱ����,Z��ʾ�п��г�λ
		head->number1[1] = '0';
		head->xuhao = look; //������ͷ����xuhao
	}                 //������˵���ó�λҪ��Ϊ���г�λ,��ͷ����cheweihao��xuhao��Ҫ����������look�϶�������p1->xuhao
	_p0 = _p2 = head->next;      //�����������һ�����bug,����������01������p2ָ�����02,Ϊ�˴�ͷ��ʼ����������Ҫ����Ҫp2ָ���һ����λ
	if (flag == 1)
		m = 20;
	else if (flag == 2)
		m = 15;
	else if (flag == 3)
		m = 10;
	for (i = 1; i <= m; i++) {//����С���г�λ��ɾ���ʹ���֮��Ҫ��һ����С���г�λ

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
	if (record == 0) {//record���ҵ����ų��ղŲ���ĳ�λ�ŵĿ��еĳ�λ

		head->number1[0] = 'X';
		head->number1[1] = 0;
	}
	else {
		head->number1[0] = 'Z';
		head->number1[1] = 0;
		head->xuhao = record;
	}
	if (p1->nn>0)                //�����һ��(nn=0)�Ļ��Ͳ���+24
		kk = 1;
	else                              //ti1��ti2�ֱ����뿪ʱ�ļ�ʱ����
		kk = 0;
	tiji1 = *ti1 * 60 + *ti2;                        //�뿪ʱ�ķ�����
	tiji2 = p1->time1 * 60 + p1->time2;           //����ʱ�ķ��������������+24�õ������ͣ���ķ�����(����������������֮�������������������)
	tiji = p1->nn * 24 * 60 + 24 * kk * 60 + tiji1 - tiji2;            //����ͣ����ͣ����ʱ�任��ɷ���
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
				printf("û�иó���\n");
				return head;
			}
		free(p1);
		printf("�����뿪���\n");
		return head;
}



AS *Write_To_Files(AS *Ahead, AS *Bhead, AS *Chead)        //�����������д���ļ�
{
	AS *head = NULL, *Awrite(AS *), *Bwrite(AS *), *Cwrite(AS *);
	FILE *fp;                                     //��ʼ������д���ļ�
	char date[100];                               //���ļ��ﱣ��ʱ���ڿ�ͷ������,Ҳ���ǵ��������
	printf("             �������뵱������ڣ�����:2016��05��01�գ�\n");
	gets(date);                           //date�������,��Ϊ����д���ļ���ʱ��ֱ�����ַ�������ʽд��
	if ((fp = fopen("jilu.txt", "a+")) == NULL)        //���ļ����в���
	{
		printf("can not open file!\n");
		exit(0);
	}
	else {                                     //���ļ��ɹ����ȼ���ʱ�䣬��ʱ��ת���ɷ��ӽ��м���

		fputs(date, fp);
		fputc(',', fp);
		fprintf(fp, "%.2lfԪ\n", money);
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
	if ((Afp = fopen("A����δ�뿪�ĳ���.dat", "wb")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	fprintf(Afp, "%d", an);
	while (p1 != NULL) {
		p1->nn++;                 //������һ�죬��ʱ��+1��������������ķ���
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
	if ((Bfp = fopen("B����δ�뿪�ĳ���.dat", "wb")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	fprintf(Bfp, "%d", bn);
	while (p1 != NULL) {
		p1->nn++;                 //������һ�죬��ʱ��+1��������������ķ���
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
	if ((Cfp = fopen("C����δ�뿪�ĳ���.dat", "wb")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	fprintf(Cfp, "%d", cn);
	while (p1 != NULL) {
		p1->nn++;                 //������һ�죬��ʱ��+1��������������ķ���
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
	if ((Afp = fopen("A����δ�뿪�ĳ���.dat", "ab+")) == NULL)
	{
		printf("can not open the file!\n");
		exit(0);
	}
	rewind(Afp);                  //��Ϊ��һ�δ򿪳���û������ļ������Բ�����rb����Ϊ�˶�ȡ�ļ���ʱ���ܸ���Դ�ļ�
	fscanf(Afp, "%d", &an);         //���Բ�����wb,����ֻ����ab+(ab��д׷��),Ϊ��ָ�븴ԭ��������rewind
	k = an;
	if (k == 0)                           //��һ�δ��ļ�֮��k==0�����Է���һ���յ�head��ֵ��Ahead����ͷ��ʼ��������
		return head;
	k++;                                  //��Ϊ��ͷ���һ�������������k��ֵӦ���ǽڵ���+1��
	p1 = (AS *)malloc(AD);           //�ȿ��ٵ�һ����ͷ���
	if (p1 == NULL)
	{
		printf("error");
		exit(0);
	}
	p2 = head = p1;                           //��ͷ����Ⱥ�head��������
	while (k--)                           //��������ʱ���ͷ���һ��������
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
	if ((Bfp = fopen("B����δ�뿪�ĳ���.dat", "ab+")) == NULL)
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
	p1 = (AS *)malloc(AD);                      //�ȿ��ٵ�һ����ͷ���
	if (p1 == NULL) {
		printf("error");
		exit(0);
	}
	p2 = head = p1;                         //�ȶ�ȡ��ͷ���
	while (k--) {
		fread(p1, AD, 1, Bfp);
		p2 = p1;
		p1 = (AS *)malloc(AD);               //�ٿ��ٵ�һ��ͣ��λ
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
	if ((Cfp = fopen("C����δ�뿪�ĳ���.dat", "ab+")) == NULL) {
		printf("can not open the file!\n");
		exit(0);
	}
	rewind(Cfp);
	fscanf(Cfp, "%d", &cn);
	k = cn;
	if (k == 0)
		return head;
	k++;
	p1 = (AS *)malloc(AD);           //�ȿ��ٵ�һ����ͷ���
	if (p1 == NULL) {
		printf("error");
		exit(0);
	}
	p2 = head = p1;                                              //�ȶ�ȡ��ͷ���
	while (k--) {
		fread(p1, AD, 1, Cfp);
		p2 = p1;
		p1 = (AS *)malloc(AD);               //�ٿ��ٵ�һ��ͣ��λ
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

