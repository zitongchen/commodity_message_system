




/*                                    2014-2015ѧ��ڶ�ѧ�ڡ�C���Գ������ʵѵ��
                                      �������������ѧ�뼼��רҵ  ҽѧӦ�÷���14��1����
									  ������         ѧ�ţ�
									       ����ͨ         1405553127
									  	   ����ӯ  	      1405553105

  ��Ҫ���㣺
	1.����MCI�ṩ��������ʾ���ܣ��ֱ��ڽ���ϵͳ���˳�ϵͳ�Լ�����������ʱ�򷢳�������ʾ��
	2.���ø�д���Զ���Myatof()�����ṩ��ǿ��ĺ������жϣ���ֹ�ڻ����������͵��������������Ļ�Ӣ���ַ���
	3.�ڳ�����д���˴����ĺ������жϵĴ��룬ʹ����İ�ȫ�Դ����ߣ�
	4.��ϵͳ�еĻ�����������������˿�������ͳ�ƣ�
	5.�ڴ���ģ���в����������޸Ĺ��ܣ���������ɾ�����ܣ�
	6.��ͳ�ƹ��ܺͲ�ѯ�����жԼ۸�����Ϳ��������ǽ�������������������
	

  ���ڲ��㣺
  1.�޷����������������ʱ�����������������������⣻


  ���·ֹ�������ͨͬѧ��Ҫ����󲿷ֺ������磺¼�룬��ʾ��ɾ������ѯ���޸ģ�ͳ�ƣ����湲7���������޸�bug
			����ӯͬѧ��Ҫ��������Ͳ�����������������Ѱ��bug����ƿ�

*/



//Ԥ�������
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>
//#include<ctype.h>
#include <windows.h>             //
#include <mmsystem.h>           //����������Ƶ��Ҫ��ͷ�ļ�
#pragma comment(lib,"winmm.lib")//




#define HEADER1 "---------------------------------------------------��Ʒ��Ϣ����ϵͳ----------------------------------------------\n"
#define HEADER2 "| ��Ʒ���  | ��Ʒ���   | ��Ʒ����  |        ���� |  ��Ʒ����|  �۳�����|     ���|  ��Ʒ�ܽ��|��������        |\n"
#define HEADER2_1 "| ��Ʒ���  |  ��Ʒ���   |  ��Ʒ���� |      ����   | ��Ʒ���� | �۳�����  |   ���  | ��Ʒ�ܽ�� |     ��������    |\n"

#define HEADER3 "|-----------|------------|-----------|-------------|----------|----------|---------|------------|----------------|\n"
#define HEADER4 "|----------------------------------------------------------------------------------------------------------------\n"
#define FORMAT  "| %-10s| %-10s | %-10s|   %10.2lf|     %5d|     %5d|    %5d|  %10.2lf| %-14s |\n"

#define DATA  p->num, p->type ,p->name, p->price, p->amount, p->sold, p->stock, p->total, p->producer
#define END    "\n|-------------------------------------------------------------------------------------------------------------------|\n"
#define N 100

int saveflag=0;  //ȫ�ֱ�������ʶ�Ƿ���Ҫ���̵ı�־����

//��Ʒ��Ϣ����ϵͳ�ĺ������ݽṹ
typedef struct commodity
{	char num[10];          //��Ʒ���
	char type[10];         //��Ʒ���
	char name[10];         //��Ʒ����
	char producer[20];     //��������
	double price;         //��Ʒ����
	int amount;           //��Ʒ����
	int sold;             //��Ʒ�۳�����
	double total;         //��Ʒ�ܽ��
	int stock;           //��Ʒ�Ŀ�棻

}SPXX;

//��ʾϵͳ���˵�
void menu()
{
	system("cls");
	printf("                   ��Ʒ��Ϣ����ϵͳ                 \n");
	printf("*************************���˵�**************************\n");
	printf("*             1 ¼����Ϣ        2 ��ʾ��Ϣ              *\n");
	printf("*             3 ɾ����Ϣ        4 ��ѯ��Ϣ              *\n");
	printf("*             5 �޸���Ϣ        6 ������Ϣ              *\n");
	printf("*             7 ������Ϣ        8 ������Ϣ              *\n");
	printf("*             9 ͳ����Ϣ        0 �˳�ϵͳ              *\n");
	printf("*********************************************************\n");
	printf("                  ���������ѡ��<0-9>:\n");
}


//������ʾ��Ƶ����
void sound()
{
	mciSendString("open \d:\\��Ʒ��Ϣ����ϵͳ\\������ʾ��.mp3\ type MPEGVideo alias file", NULL, 0, NULL);
	mciSendString("seek yeah to start", 0, 0, 0);//��λ����ʼ��
    mciSendString("play file", NULL, 0, NULL);//��Ƶ�Ŀ�ʼ
	getchar();
	mciSendString("close file",NULL,0,NULL);//��Ƶ�Ĺر�
	
    
}
//��ӭ��Ƶ����
void sound_1()
{
	mciSendString("open \d:\\��Ʒ��Ϣ����ϵͳ\\��ӭ��.mp3\ type MPEGVideo alias file", NULL, 0, NULL);
	mciSendString("seek yeah to start", 0, 0, 0);//��λ����ʼ��
    mciSendString("play file", NULL, 0, NULL);
	getchar();
	mciSendString("close file",NULL,0,NULL);
	
	
    
}
//��������Ƶ
void sound_2()
{
	mciSendString("open \d:\\��Ʒ��Ϣ����ϵͳ\\������.mp3\ type MPEGVideo alias file", NULL, 0, NULL);
	mciSendString("seek yeah to start", 0, 0, 0);//��λ����ʼ��
    mciSendString("play file", NULL, 0, NULL);
	getchar();
	mciSendString("close file",NULL,0,NULL);

    
}


//��ʽ�������ͷ//printf(HEADER3);
void printheader()
{
	printf(HEADER1);
	printf("\n");
	printf(HEADER2);
	
}

//��ʽ�������������
void printdata(SPXX *p)
{	
	
	printf(FORMAT,DATA);
}
//�Ա�����ʽ���,��printdata()��С��Ĳ��
void printdata_1(SPXX pp)
{
	SPXX *p;
	p=&pp;
	printf(HEADER3);
	printf(FORMAT,DATA);

}

//�������������Ϣ
void Wrong(){
	printf("\n\n\n\n\n\n***********Error����������Enter������***********\n");
	sound();

}

//���û���ҵ��˼�¼����Ϣ
void Nofind()
{ 
	printf("\n\n\n********û�ҵ���Ҫ����Ϣ��*********\n");
	
}


//Disp���������ڰ����е���Ϣ��ʾ����Ļ��,���ڴ�������Ƕ�ĺ�����
void Disp(SPXX *SP,int n)
{
	int i;
	if(n==0)
	{
		printf("\n-------��Ʒ��Ϣ����ϵͳ��δ��¼��\n");
	}
	else
	{
		printf("\n\n");
		printheader();
		i=0;
		while(i<n)
		{
			printdata_1(*SP++);
			i++;
		
		}
	}

}


//��������Ϣ�������Ļ�ϣ�����0���أ���Disp()��������
void Disps(SPXX *SP,int n)
{	int i;
	char k[5];
	SPXX *sp=SP;
	double Myatof(char str[]);//Myatof()����������
	
	if(n==0)
	{
		printf("\n-------��Ʒ��Ϣ����ϵͳ��δ��¼��\n");
	}
	else
	{
		printf("\n\n");
		printheader();
		i=0;
		while(i<n)
		{
			printdata_1(*sp++);
			i++;
		}
	}

	printf("��'0'�������˵���");
	scanf("%s",k);
	getchar();
	while(1)
	{
		sp=SP;
		i=0;
		if((int)Myatof(k)==0&&strlen(k)==1)
		{
			return;
		}
		else
		{
			
			Wrong();
			system("cls");
			while(i<n)
			{
				printdata_1(*sp++);
				i++;
			}
			printf("��'0'�������˵���");
			scanf("%s",k);
			getchar();
		}	
	}
}

//����stringinput�����ã������ַ����������г��ȵ��ж�
void stringinput(char *t,int lens,char *notice)
{
	int i=0;
	char str[20];

	do
	{
		printf(notice);
		scanf("%s",str);
		i=strlen(str);
		getchar();
		if(i>lens)
			printf("\n\n�����˹涨�ĳ��ȣ�\n\n");
	}while (i>lens);
	strcpy(t,str);
}

//�Զ����atof()������
double Myatof(char str[])
{
	int i=0,t=0,k=0;
	double j=0;//atof()���ص���double���ͣ�
	char c[2]="\0";
	i=strlen(str);
	for(t=0;t<i;t++)
	{
		if('A'<=str[t])
		{
			return -1;
		}
		else if(str[t]&0x80)//���ð�λ���ж�������Ƿ�������
		{ 
			c[k] =str[t];
			k++;
			if (k==2) 
				 return -1;
		}
		else 
			k=0;
	}
	if(i==1&&str[0]=='0')
		return 0;
	else
	{
		j=atof(str);
		return j;
	}
}


//���ڻ����������͵����룺��int,double��������������⣩
double datainput(char *notice)
{ 
	double t;
	char p[20];

	while(1)
	{	t=0;
		printf(notice);
		scanf("%s",p);
		t=Myatof(p);//���ַ���strת����һ��˫������ֵ�����ؽ���� ����str ��������Ч���ֿ�ͷ

		if(t==-1)//����ĺ������ĺͺ�Ӣ���ַ���ִ������룻
		{
			printf("���벻�ܺ������Ļ�Ӣ���ַ�,���������!");
			continue;
		}
		else if(t<0)
		{
			printf("�������ֵ����Ϊ������");
			continue;
		}
		else	
			return t;
	}
}


//Locate�����ã����ڶ�λ����Ҫ��ļ�¼��

void Locate(SPXX *SP,int n,char findmess[],char nameorphonenum[],int p1[])//�漰����ͬ���ƵĽṹ�壬                                                            
{                                                                         //�����������ͬ���ƵĽṹ���±�װ������ 
	int i=0,j;               
	p1[0]=-2;            //��p1[0]��ֵΪ-2������Ϊ�жϣ���p1[0]=-2֤��û���ҵ�Ҫ�ҵ���Ϣ���±ꣻ                  
	if(strcmp(nameorphonenum,"num")==0)
	{
		j=0;           //���±��0��ʼ��
		while(i<n)
		{
			if(strcmp((SP+i)->num,findmess)==0)
			{
				p1[j]=i;
				j++;	
			}
			i++;	
		}
		if(p1[0]==-2)          //���if������֤��û���ҵ�Ҫ�ҵı�Ż����ƣ�
			p1[0]=-1;	
	}
	else if(strcmp(nameorphonenum,"name")==0)
	{
		j=0;
		while(i<n)
		{
			if(strcmp((SP+i)->name,findmess)==0)
			{
				p1[j]=i;
				j++;
			}
			i++;
		}
		p1[j+1]=-3;//�����ڷ��ص�ʱ���ж��������Ļ�ϵ���Ϣ�Ƿ������
		if(p1[0]==-2)
			p1[0]=-1;
	}
	else if(strcmp(nameorphonenum,"type")==0)
	{
		j=0;
		while(i<n)
		{
			if(strcmp((SP+i)->type,findmess)==0)
			{
				p1[j]=i;
				j++;
			}
			i++;
		}
		p1[j+1]=-3;//�����ڷ��ص�ʱ���ж��������Ļ�ϵ���Ϣ�Ƿ������
		if(p1[0]==-2)
			p1[0]=-1;
	}
		else if(strcmp(nameorphonenum,"producer")==0)
	{
		j=0;
		while(i<n)
		{
			if(strcmp((SP+i)->producer,findmess)==0)
			{
				p1[j]=i;
				j++;
			}
			i++;
		}
		p1[j+1]=-3;//�����ڷ��ص�ʱ���ж��������Ļ�ϵ���Ϣ�Ƿ������
		if(p1[0]==-2)
			p1[0]=-1;
	}
}





//ģ����ѯ���������Ĺ���˼·��Locate()������
void strstrserve(SPXX *SP,int n,char findmess[],char nameorphonenum[],int p2[])
{
	int i=0,j=0;
	p2[0]=-2;
	if(strcmp(nameorphonenum,"num")==0)
	{
		j=0;
		while(i<n)
		{
			if((strstr((SP+i)->num,findmess))!=NULL)
			{
				p2[j]=i;
				j++;
			}
			i++;
		}
		p2[j+1]=-3;
		if(p2[0]==-2)
			p2[0]=-1;
	}
	else if(strcmp(nameorphonenum,"name")==0)
	{
		j=0;
		while(i<n)
		{
			
			if((strstr((SP+i)->name ,findmess))!=NULL)
			{//���ܣ���������һ��ָ�룬��ָ���ַ���str2 �״γ������ַ���str1�е�λ�ã����û���ҵ�������NULL��
				p2[j]=i;
				j++;
			}
			i++;
		}
	    p2[j+1]=-3;
		if(p2[0]==-2)
			p2[0]=-1;
	}
}
  

//��ѯ���ܵ�ģ����ѯģ�飻
//û�зֱ�ŵ�ģ����ѯ������ģ����ѯ�����ǰѱ�ţ����ȵ�ģ����ѯͨ��forѭ��ȫ����ѯ��
//���ٶȶ�ģ����ѯ�е����ƣ�
void strstrserve_2(SPXX *SP,int n,char findmess[],int p2[])
{
	int i=0,j=0;
	p2[0]=-2;
	for(i=0;i<n;i++)
	{
		if(strstr((SP+i)->num,findmess))
		{
			p2[j]=i;
			j++;
			continue;
		}
		else if(strstr((SP+i)->type,findmess))
		{
			p2[j]=i;
			j++;
			continue;
		}
		else if(strstr((SP+i)->name,findmess))
		{
			p2[j]=i;
			j++;
			continue;
		}
	}
	p2[j+1]=-3;
	if(p2[0]==-2)
		p2[0]=-1;		
}



//����Add�����ã������Ʒ��Ϣ��
int Add(SPXX *SP,int n)
{
	char ch,num[10],c[2];
	int i,flag=0,j=0;
	while(1)
	{
		while(1)
		{
			system("cls");
			Disp(SP,n);
			stringinput(num,10,"�����ţ���'0'�������˵�����");
			flag=0;
			if(strcmp(num,"0")==0) return n;
			i=0;
			while(i<n)
			{
				if(strcmp((SP+i)->num,num)==0)
				{
					flag=1;break;//��flag=1��ô˵������ı���Ѿ�������
				}
				i++;
			}
			for(i=0;i<strlen(num);i++)
			{
				if(num[i]&0x80)//���ð�λ���ж�������Ƿ������ģ�
				{
					c[j]=num[i];
					j++;
					if(j==2)
					{
						j=0;
						printf("����в��ܴ��������ַ�!\n�Ƿ���������ţ�");
						scanf("%c",&ch);
						getchar();
						if(ch=='y'||ch=='Y') 
						{	flag=2;break;}
						else
							return n;
					}
				}
				else 
					j=0;
			}
			if(flag==2)//���������ַ����ж��Ƿ�������룻
				continue;
			if(flag==1)
			{
				printf("--------���%s�Ѿ����ڣ�����һ�Σ�(y/n):",num);
				scanf("%c",&ch);
				getchar();
				if(ch=='y'||ch=='Y') 
					continue;
				else
					return n;
			}
			else 
				break;
		}
		//�ַ���������Ϣ������
		strcpy((SP+n)->num,num);
		stringinput((SP+n)->type,10,"���:");
		stringinput((SP+n)->name,10,"����:");
		stringinput((SP+n)->producer,20,"��������:");
		
		//���������������ݵ����룻
		(SP+n)->price=datainput("����:");
		(SP+n)->amount=(int)datainput("����:");
		(SP+n)->sold=(int)datainput("�۳���Ʒ������");

		//�������۳������ĺ������жϣ�
		while((SP+n)->amount<(SP+n)->sold)
		{
			printf("��������۳���Ʒ����Ӧ��Ҫ����%d��\n",(SP+n)->amount);
			(SP+n)->sold=(int)datainput("�������µ��۳���Ʒ������");
		}
	
		//ͨ����ѧ�����Զ�������Ʒ������Ʒ�ܽ�
		(SP+n)->total=((SP+n)->price*(SP+n)->amount);
		(SP+n)->stock=((SP+n)->amount-(SP+n)->sold);  
		n++;
		saveflag=1;
	}
	return n;
}




//����Del_2����ģ�����Ҳ�ɾ������������Ϣ�����ҵ������Ϣ���±겢���������У�Ȼ����������ɾ������Ԫ�أ�
int Del_2(SPXX *SP,int n)
{
	int sel,p2[30],j,p,i;
	char findmess[10],flag,sel_1[5];
	while(1)
	{
		j=0;i=0;
		system("cls");
		Disp(SP,n);
		printf("\n        ģ��ɾ���Ӳ˵�         \n");
		printf("*********************************\n");
		printf("*      1 ���ݱ�� 2 ��������    *\n");
		printf("*      0 ������һ���˵�         *\n");
		printf("*********************************\n");
		printf("           ��ѡ��<0-2>:         \n");
		scanf("%s",sel_1);
		getchar();
		sel=(int)Myatof(sel_1);    //��׳���жϣ������д�����ʾ��
		if(sel==0)
			return n;
		else if(sel==1)
		{
			stringinput(findmess,10,"����ֶΣ�");
			strstrserve(SP,n,findmess,"num",p2);	//ģ�������±꣬���洢��p2������
			if(p2[0]!=-1)
			{	
				system("cls");
				j=0;
				printf("    "HEADER2);
				while(1)
				{
						printf("(%2d):",j+1);
						printdata((SP+p2[i]));
						i++;
						j++;
						if(p2[i+1]==-3)
							break;
				}
				printf("����������ɾ������<��'0'������һ���˵�>��\n");
				scanf("%d",&i);
				getchar();
				while(i>j)                //��׳���жϣ�
				{	
					printf("��ѡ�������ڣ�\n���������<��'0'������һ���˵�>��");
					scanf("%d",&i);
					getchar();
					if(i==0)
						break;
				}
				if(i==0)
					continue;
				p=p2[i-1];//����Ӧ��Ϣ����Ʒ�±��p;
			
				printf("�����Ҫɾ����<y/n>:");
				scanf("%c",&flag);
				if(flag=='N'||flag=='n')
					continue;
			}
			if(p2[0]!=-1)
			{
				for(i=p+1;i<n;i++)
				{
					SP[i-1]=SP[i];//ȷ����ɾ����Ӧ����Ϣ��
				}
				printf("\nɾ���ɹ���\n");
				n--;
				getchar();
				saveflag=1;
			}
			else 
				Nofind();
		}	
		else if(sel==2)
		{
			stringinput(findmess,15,"�������е����ƣ�");
			strstrserve(SP,n,findmess,"name",p2);
			if(p2[0]!=-1)
			{	
				system("cls");
				j=0;
				printf("    "HEADER2);
				while(1)
				{
						printf("(%d):",j+1);
						printdata((SP+p2[i]));
						i++;
						j++;
						if(p2[i+1]==-3)
							break;
				}
				printf("����������ɾ������<��'0'������һ���˵�>��\n");
				scanf("%d",&i);	
				getchar();
				while(i>j)                //��׳���жϣ�
				{	
					printf("��ѡ�������ڣ�\n���������<��'0'������һ���˵�>��");
					scanf("%d",&i);
					getchar();
					if(i==0)
						break;
					
				}
				if(i==0)
					continue;
				p=p2[i-1];
				printf("�����Ҫɾ����<y/n>:");
				scanf("%c",&flag);
				getchar();
				if(flag=='N'||flag=='n')
					continue;
			}
			if(p2[0]!=-1)
			{
				for(i=p+1;i<n;i++)
				{
					SP[i-1]=SP[i];
					
				}
				printf("\nɾ���ɹ���\n");
				n--;
			    getchar();
				saveflag=1;
			}
			else 
				Nofind();
		}
		else
			Wrong();
	}
	return n;
}




//����Del����ɾ��������Ϣ�����ҵ������Ԫ�ص��±꣬Ȼ����������ɾ������Ԫ�أ�
int Del(SPXX *SP,int n)
{
	int sel,p1[30],j=0, p,i=0;
	char findmess[20],flag,sel_2[5];
	if(n<0)
	{
		system("cls");
		printf("\n-------��Ʒ��Ϣϵͳ��ʱû����Ϣ��\n");
		getchar();
		return n;
	}

	while(1){
		system("cls");
		Disp(SP,n);
		printf("\n          ɾ���Ӳ˵�         \n");
		printf("*********************************\n");
		printf("*      1 ���ݱ�� 2 ��������    *\n");
		printf("*      3 ������� 4 ģ��ɾ��    *\n");
		printf("*      5 ����ɾ�� 0 �������˵�  *\n");
		printf("*********************************\n");
		printf("           ��ѡ��<0-5>:");
		scanf("%s",&sel_2);
		getchar();                 //����ĺ���ҪŶ���࿴��
		sel=(int)Myatof(sel_2);    //��׳���жϣ�
		if(sel==0)
			return n;
		else if(sel==1)
		{
			stringinput(findmess,10,"�������еı�ţ�");
			Locate(SP,n,findmess,"num",p1);		
			p=p1[0];                     //�����Ψһ�ԣ�����ֻҪ�ж�p1[0]��ֵ�Ϳ����ˣ�
			if(p!=-1)//�����������Ϣ�Ͳ���ִ�����if��䣻
			{
				printf(HEADER2);
				printdata(SP+p);
				printf("�����Ҫɾ����<y/n>:");
				scanf("%c",&flag);
				getchar();
				if(flag=='N'||flag=='n')
				{
					continue;
				}	
			}
			if(p!=-1)
			{
				for(i=p+1;i<n;i++)
				{
					SP[i-1]=SP[i];
				}
				printf("ɾ���ɹ���\n");
				n--;
				getchar();
				saveflag=1;				
			}
			else 
			{Nofind();getchar();}			
		}
		
		else if(sel==2||sel==3)
		{
			if(sel==2)
			{
				stringinput(findmess,15,"�������е����ƣ�");
				Locate(SP,n,findmess,"name",p1);
			
			}
			else
			{
				stringinput(findmess,15,"�������е����");
				Locate(SP,n,findmess,"type",p1);
			
			}
			if(p1[0]!=-1)///����û�����ݾͲ���ִ�����if��䣻
			{	
				system("cls");
				j=0;i=0;
				printf("    "HEADER2);
				while(1)
				{
						printf("(%d):",j+1);
						printdata((SP+p1[i]));
						i++;
						j++;
						if(p1[i+1]==-3)
							break;
				}
				printf("����������ɾ������<��'0'������һ���˵�>��\n");
				scanf("%d",&i);
				getchar();
				p=p1[i-1];
				while(i>j)                //��׳���жϣ�
				{	
					printf("��ѡ�������ڣ�\n���������<��'0'������һ���˵�>��");
					scanf("%d",&i);
					getchar();
					if(i==0)
						break;
				}
				if(i==0)
					continue;
				printf("�����Ҫɾ����<y/n>:");
				scanf("%c",&flag);
				getchar();
				if(flag=='N'||flag=='n')
					continue;
			}
			if(p1[0]!=-1)
			{
				for(i=p+1;i<n;i++)
				{
					SP[i-1]=SP[i];
				}
				printf("\nɾ���ɹ���\n");
				n--;
				getchar();
				saveflag=1;
			}
			else 
			{	Nofind();getchar();
			}
		}
		else if(sel==4)
		{
			Del_2(SP,n);//���������ģ��ɾ���Ӻ���
		}
		else if(sel==5)
		{
			while(1){
				j=0;i=0;
			system("cls");
			sel=0;
			printf("          ����ɾ���Ӳ˵�\n");
			printf("***************************************\n");
			printf("*   1 ��Ʒ���      2 ��Ʒ����        * \n");
			printf("*   3 ��Ʒ��������  0 ������һ�����˵�*\n");
			printf("***************************************\n");
			printf("         ��ѡ��<0-3>��");
			scanf("%s",&sel_2);
			getchar();
			sel=(int)Myatof(sel_2);//��׳���ж�
			if(sel==0)
				break ;
			else if(sel==1)
			{
				stringinput(findmess,10,"��������ɾ�������");
				Locate(SP,n,findmess,"type",p1);
				if(p1[0]!=-1)
				{
					system("cls");
					j=0;
					printf("    "HEADER2);
					while(1)
					{
						printf("(%d):",j+1);
						printdata((SP+p1[i]));
						i++;
						j++;
						if(p1[i+1]==-3)
							break;
					}
					printf("�����Ҫ����ɾ����<y/n>:");
					scanf("%c",&flag);
					getchar();
					if(flag=='n'||flag=='N')
						continue;
				}
				if(p1[0]!=1)
				{
					for(i=0;i<j;i++)
					{
					
						for(p=p1[i]-i;p<n;p++)//��i����Ϊ��ԭ�������±�ǰ����iΪ�˵õ�ԭ���������Լ�i��
						{
							SP[p]=SP[p+1];
						}
						n--;
					}
					printf("\n����ɾ���ɹ���");
					getchar();
					saveflag=1;
				}
				else
					Nofind();
			}
			else if(sel==2)
			{
				stringinput(findmess,n,"��������ɾ�������ƣ�");
				Locate(SP,n,findmess,"name",p1);
				getchar();
				if(p1[0]!=-1)
				{
					system("cls");
					j=0;
					printf("    "HEADER2);
					while(1)
					{
						printf("(%d)",j+1);
						printdata((SP+p1[i]));
						i++;
						j++;
						if(p1[i+1]==-3)
							break;
					}
				
					printf("�����Ҫ����ɾ����<y/n>:");
					scanf("%c",&flag);
					getchar();
					if(flag=='n'||flag=='N')
						return n;
				}
				if(p1[0]!=1)
				{
					for(i=0;i<j;i++)
					{
					
						for(p=p1[i]-i;p<n;p++)
						{
							SP[p]=SP[p+1];
						}
						n--;
					}
					printf("\n����ɾ���ɹ���");
					getchar();
					saveflag=1;
				}
				else
					Nofind();	
			}
			else if(sel==3)
			{
				stringinput(findmess,n,"��������ɾ�����������̣�");
				Locate(SP,n,findmess,"producer",p1);
				if(p1[0]!=-1)
				{
					system("cls");
					j=0;
					printf("    "HEADER2);
					while(1)
					{
						printf("(%d)",j+1);
						printdata((SP+p1[i]));
						i++;
						j++;
						if(p1[i+1]==-3)
							break;
					}
					printf("�����Ҫ����ɾ����<y/n>:");
					scanf("%c",&flag);
					getchar();
					if(flag=='n'||flag=='N')
						return n;
				}
				if(p1[0]!=1)
				{
					for(i=0;i<j;i++)
					{
					
						for(p=p1[i]-i;p<n;p++)
						{
							SP[p]=SP[p+1];
						}
						n--;
					}
					printf("\n����ɾ���ɹ���");
					getchar();
					saveflag=1;
				}
				else
					Nofind();	
			}
			else
			{
				Wrong();
			}
			}
		}
		else 
		{	Wrong();
		}
	}
	return n;
}



//��ѯ����
void Qur(SPXX *SP,int n)
{
	int sel,j,i,p=0,p1[30],k;
	double max,min;
	char findmess[20],sel_1[5];
	SPXX transport;
	if(n<0)
	{
		system("cls");
		printf("\n-------��Ʒϵͳû�м�¼��\n");
		getchar();
	}
	
	while(1)
	{	j=0,i=0;
		system("cls");
		printf("        	    ��ѯ�Ӳ˵�\n");
		printf("**********************************************\n");
		printf("*       1 ��ȷ��ѯ       2 ģ����ѯ          *\n");
		printf("*       3 ���������ѯ   0 �������˵�        *\n");
		printf("**********************************************\n");
		printf("                ��ѡ��<0-3>:   ");
		scanf("%s",sel_1);
		getchar();
		sel=(int)Myatof(sel_1);
		if(sel==0)
			return ;
		else if(sel==1)
		{
			while(1){
			system("cls");
			printf("\n         ��ȷ��ѯ�Ӳ˵�         \n");
			printf("**********************************\n");
			printf("*      1 ���ݱ�� 2 ��������     *\n");
			printf("*      3 ������� 0 �������˵�   *\n");
			printf("*********************************\n");
			printf("           ��ѡ��<0-3>         ");
			scanf("%s",&sel_1);
			getchar();                
			sel=(int)Myatof(sel_1);    //��׳���жϣ�
			if(sel==0)
				break;
			else if(sel==1)
			{
				stringinput(findmess,10,"�������еı�ţ�");
				Locate(SP,n,findmess,"num",p1);		
				p=p1[0];   //�����Ψһ�ԣ�����ֻҪ�ж�p1[0]��ֵ�Ϳ����ˣ�
				system("cls");
				if(p!=-1)
				{
					printf(HEADER2);
					printdata((SP+p));
					printf(HEADER3);
					getchar();
				}
				else 
				{Nofind();getchar();}			
			}
			else if(sel==2||sel==3)
			{
				if(sel==2)
				{
					stringinput(findmess,15,"�������е����ƣ�");
					Locate(SP,n,findmess,"name",p1);
				}
				else
				{
					stringinput(findmess,15,"�������е����");
					Locate(SP,n,findmess,"type",p1);
				}
				if(p1[0]!=-1)///����û�����ݾͲ���ִ�����if��䣻
				{	
					system("cls");
					j=0;i=0;
					printf(HEADER2);
					while(1)
					{
							printdata((SP+p1[i]));
							printf(HEADER3);
							i++;
							j++;
							if(p1[i+1]==-3)
								break;
					}
					printf("\n  ��Enter��������һ���˵���");
					getchar();
				}
				else 
				{	Nofind();getchar();
				}
			}
			else
				Wrong();
			}
		}
		else if(sel==2)
		{
			system("cls");
			printf("\n������Ҫ��ѯ�����ݣ�");
			scanf("%s",findmess);
			getchar();
			strstrserve_2(SP,n,findmess,p1);	
			if(p1[0]==-1)
			{
				Nofind();
				getchar();
				continue;
			}
			printf(HEADER2);
			while(1)
			{
				printf("(%d):",j+1);
				printdata((SP+p1[i]));
				i++;
				j++;
				if(p1[i+1]==-3)
					break;
			}
			printf("\n  ��Enter��������һ���˵���");
			getchar();
		}
		else if(sel==3)
		{
			system("cls");
			j=0;
			p1[0]=-1;
			printf("������Ҫ��ѯ���۸�����(�磺xx-xx)��");
			scanf("%lf-%lf",&min,&max);
			getchar();
			for(i=0;i<n;i++)
			{
				if((SP+i)->price>=min&&(SP+i)->price<=max)
				{
					p1[j]=i;
					j++;
				}
			}
			if(p1[0]==-1)
			{
				printf("\n\n�����ڼ۸���%lf��%lf����Ʒ��",min,max);
				getchar();
				continue;
			}
			p1[j]=-2;
			if(p1[0]!=-1)
			{
				for(i=0;i<j;i++)
				{
					for(k=i+1;k<j;k++)
					{
						if((SP+p1[i])->price>(SP+p1[k])->price)
						{
							transport=*(SP+p1[k]);
							*(SP+p1[k])=*(SP+p1[i]);
							*(SP+p1[i])=transport;
						}
					}	
				}
			}
			i=0;
			j=0;
			if(p1[0]!=-1)
			{
				printf("\n\n");
				printf(HEADER2);

			}
			while(p1[0]!=-1)
			{
				printdata((SP+p1[j]));
				j++;
				if(p1[j]==-2)
					break;
			}
			printf("\n  ��Enter��������һ���˵���");
			getchar();
		}
		else
		{	Wrong();
		}
	}

}


//������
void SelectSort(SPXX goods[],int n)
{	int i,j,indexmin,select;
	char sel[5];
	SPXX newinfo;
	if(n<=0)
	{	system("cls");
		printf("n====>���޼�¼��\n");
		getchar();
	}
	system("cls");
	Disp(goods,n);//��ʾ����ǰ�����м�¼
	printf("\n\n");
	printf("                �����Ӳ˵�\n");
	printf("******************************************\n");
	printf("*    1 �������������  2 ��������������  *\n");
	printf("*    3 ��������������  4 ��������������  *\n");
	printf("*    5 �������������  0 ��'0'�������˵� *\n");
	printf("******************************************\n");
	printf("	   ������ѡ����<0-5>:   ");
	scanf("%s",&sel);
	select=(int)Myatof(sel);    //��׳���жϣ�
	if(select==0)
		return;
	else if(select==1)
	{	for(i=0;i<n-1;i++)
		{	indexmin=i;
			for(j=i+1;j<n;j++)
				if(strcmp(goods[j].num,goods[indexmin].num)==-1)  indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);//��ʾ��������м�¼
		getchar();
		saveflag=1;
		printf("\n   ------�������\n");
		printf("\n��Enter��������һ���˵���");
		getchar();
	}
	else if(select==2)
	{
		for(i=0;i<n;i++)
		{
			indexmin=i;
			for(j=i+1;j<n;j++)
				if(strcmp(goods[j].type,goods[indexmin].type)<0) indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);
		getchar();
		saveflag=1;
		printf("\n�������\n");
		getchar();  

	}
	else if (select==3)//����¼��������
	{	for(i=0;i<n-1;i++)
		{	indexmin=i;
			for(j=i+1;j<n;j++)
				if(strcmp(goods[j].name,goods[indexmin].name)<0)   indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);//��ʾ��������м�¼
		getchar();
		saveflag=1;
		printf("\n�������!\n");
		getchar();
	}
	else if (select==4)//����¼������������
	{	for(i=0;i<n-1;i++)
		{	indexmin=i;
			for(j=i+1;j<n;j++)
				if(goods[j].price<goods[indexmin].price)   indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);//��ʾ��������м�¼
		getchar();
		saveflag=1;
		printf("\n�������!\n");
		getchar();
	}
	else if (select==5)//����¼�����������
	{	for(i=0;i<n-1;i++)
		{	indexmin=i;
			for(j=i+1;j<n;j++)
				if(goods[j].stock<goods[indexmin].stock)   indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);//��ʾ��������м�¼
		getchar();
		saveflag=1;
		printf("\n �������!\n");
		getchar();
	}
	else
	{	Wrong();
		
	}
}


//����Insert���ڲ����¼�����Ȱ���Ų�ѯ��Ҫ���������Ԫ��λ�ã�Ȼ���ڸü�¼���֮�����һ��������Ԫ��
int Insert(SPXX goods[],int n)
{	char ch,num[10],s[10];     //s[]��������λ��֮ǰ�ļ�¼��ţ�num[]����������¼�¼�ı��
	SPXX newinfo;		       //���ڽ�������ʱ����
	int flag,i,k=0;
	system("cls");
	Disp(goods,n);
	while(1)
	{
	while(1)
	{	stringinput (s,10,"������һ����¼��ţ�������ļ�¼��λ�ڸñ�ż�¼�ĺ���<��'0'�������˵�>��");
		if((int)Myatof(s)==0&&strlen(s)==1)  //�����ж��Ƿ񷵻����˵���
			return n; 
		flag=0;i=0;
		while(i<n)            //��ѯ�ñ���Ƿ���ڣ�flag=1��ʾ�ñ�Ŵ���
		{	if(strcmp(goods[i].num,s)==0)
			{	k=i;
				flag=1;
				break;
			}
			i++;
		}
		if(flag==1) break;    //����Ŵ��ڣ�����в���֮ǰ���¼�¼�������
		else
		{	while(1)
			{
			printf("\n=====>���%s �����ڣ�����һ�Σ�(y/n):",s);
			scanf("%c",&ch);
			getchar();
			if(ch=='y'||ch=='Y') 
				break;
			else if(ch=='n'||ch=='N')  //�����ж��Ƿ񷵻����˵�����û����һ�䰴��������ܷ������˵�������y��
				return n;
			else
			{
				printf("�������������������룡");
				getchar();
			}
			}
		}
	}
	while(1)
	{
		stringinput(num,10,"�������µı�ţ�");
		i=0;flag=0;
		while(i<n)
		{
			if(strcmp(goods[i].num,num)==0)
			{
				flag=1;break;
			}
			i++;
		}
		if(flag==1)
		{
			
			while(1){	
			printf("���%s�Ѿ����ڣ�����һ�Σ�(y/n):",num);
			scanf("%c",&ch);
			getchar();
			if(ch=='y'||ch=='Y')
				break;
			else if(ch=='n'||ch=='N')
				return n;
			else
			{
				printf("�������������������룡\n");
				getchar();
			}			
			}
		}
		else break;
	}
	strcpy(newinfo.num,num);                  //�������������Ϣ��
	stringinput(newinfo.type,10,"���:");
	stringinput(newinfo.name,10,"����:");
	newinfo.price=datainput("���ۣ�");
	newinfo.amount=(int)datainput("��Ʒ������");
	newinfo.sold=(int)datainput("��Ʒ�۳�������");
	newinfo.total=(newinfo.price*newinfo.amount);
	newinfo.stock=(newinfo.amount-newinfo.sold);
	stringinput(newinfo.producer,16,"��������:");
	saveflag=1;
	for(i=n-1;i>k;i--)                       //�±�ŵ���Ϣ����ƣ�
	{
		goods[i+1]=goods[i];
	}
	goods[k+1]=newinfo;
	n++;
	Disp(goods,n);
	printf("\n\n");
	getchar();
	}
}

//Modify()���������޸���Ʒ����Ϣ�������У���ȷ�޸ĺ������޸�
void Modify(SPXX *SP,int n)
{
	char findmess[20],transport[20],ch,sel[5];
	int p=0,sel_1,p1[25],sel_2=0,flag=0,j=0,i=0;

	if(n<=0)
	{
		system("cls");
		printf("\n----��Ʒ��Ϣϵͳû�м�¼��");
		getchar();
	}
	while(1)
	{system("cls");
	Disp(SP,n);
	printf("           �޸��Ӳ˵�\n");
	printf("************************************\n");
	printf("*    1 ��ȷ�޸�  2 �����޸�        *\n");
	printf("*    0 �������˵�                  *\n");
	printf("*************************************\n");
	printf("        �������ѡ��<0-2>:");
	scanf("%s",&sel);
	getchar();
	sel_1=(int)Myatof(sel);
	if(sel_1==0)
		return ;
	else if(sel_1==1)
	{
		system("cls");
		stringinput(findmess,10,"������һ���Ѿ����ڵı�ţ�");
		Locate(SP,n,findmess,"num",p1);         //Ѱ�������ŵ��±ꣻ
		p=p1[0];
		if(p!=-1)
		{	printf(HEADER2);
			printdata((SP+p));

		}
		if(p!=-1)
		{
			printf("        ��ȷ�޸��Ӳ˵�\n");
			printf("**********************************\n");
			printf("*    1 ��Ʒ���  2 ��Ʒ���      * \n");
			printf("*    3 ��Ʒ����  4 ��Ʒ����      *  \n");
			printf("*    5 ��Ʒ����  6 ��Ʒ�۳�����  *  \n");
			printf("*    7 ��Ʒ��������              *  \n");
			printf("*    0 ������һ���˵�            *     \n");
			printf("**********************************\n");
			printf("        �������ѡ��<0-7>:  ");
			scanf("%s",&sel);
			getchar();
			sel_2=(int)Myatof(sel);
			if(sel_2==0)
				continue ;
			else if(sel_2==1)
			{
				while(1)
				{
					flag=0;
					printf("�����µ���Ʒ��ţ�");
					scanf("%s",transport);
					getchar();
					while(i<n)
					{
						if(strcmp((SP+i)->num,transport)==0)
						{
							flag=1;
							break;
						}
						i++;
					}
					if(flag==1)
					{
						printf("���������Ʒ����Ѿ����ڣ�\n");
						printf("�Ƿ�������һ���µı��<y/n>:");
						scanf("%c",&ch);
						getchar();
						if(ch=='y'||ch=='Y')
							continue;
						else
							break;
					}
					else
					{
						strcpy((SP+p)->num,transport);
						break;
					}
				}
			}
			else if(sel_2==2)
			{
				printf("�����µ���Ʒ���ͣ�");
				scanf("%s",transport);
				strcpy((SP+p)->type,transport);
				getchar();
			}
			else if(sel_2==3)
			{
				printf("�����µ���Ʒ���ƣ�");
				scanf("%s",transport);
				strcpy((SP+p)->name,transport);
				getchar();
			}
			else if(sel_2==4)
			{
				(SP+p)->price=datainput("�����µ���Ʒ���ۣ�");
				getchar();
			}
			else if(sel_2==5)
			{
				(SP+p)->amount=(int)datainput("�����µ���Ʒ������");
				getchar();
				while((SP+p)->amount<(SP+p)->sold)
				{
					printf("��Ʒ������Ӧ������%d��",(SP+p)->sold);
					(SP+p)->amount=(int)datainput("�����µ���Ʒ������");
				}
			}
			else if(sel_2==6)
			{
				(SP+p)->sold=(int)datainput("�����µ���Ʒ�۳�������");
				getchar();
				while((SP+p)->amount<(SP+p)->sold)
				{
					printf("��Ʒ������Ӧ�ö���%d��",(SP+p)->amount);
					(SP+p)->sold=(int)datainput("�����µ���Ʒ�۳�������");
				}
			}
			else if(sel_2==7)
			{
				printf("�����µ���Ʒ�������ң�");
				scanf("%s",transport);
				strcpy((SP+p)->producer,transport);
				getchar();
			}
			(SP+p)->total=(SP+p)->amount*(SP+p)->price;//�Զ����ɵ���ֵ��
			(SP+p)->stock=(SP+p)->amount-(SP+p)->sold;
		}
			
		else
		{
			Nofind();
			getchar();
		}
	}
	else if(sel_1==2)
	{
		system("cls");
		sel_2=0;
		printf("          �����޸��Ӳ˵�\n");
		printf("*****************************************\n");
		printf("*    1 ��Ʒ���       2 ��Ʒ����        *\n");
		printf("*    3 ��Ʒ��������   0 ������һ�����˵�*\n");
		printf("*****************************************\n");
		printf("         ��ѡ��<0-3>��       ");
		scanf("%s",&sel);
		getchar();
		sel_2=(int)Myatof(sel);
		if(sel_2==0)
			continue ;
		else if(sel_2==1)
		{
			stringinput(findmess,10,"���������޸ĵ����");
			Locate(SP,n,findmess,"type",p1);
			if(p1[0]!=-1)
			{
				system("cls");
				j=0;
				printf("    "HEADER2);
				while(1)
				{
					printf("(%2d):",j+1);
					printdata((SP+p1[i]));
					i++;
					j++;
					if(p1[i+1]==-3)
						break;
				}
				stringinput(transport,10,"�������µ����");
				printf("�����Ҫ�����޸���<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='n'||ch=='N')
					return;
			}
			if(p1[0]!=1)
			{
				for(i=0;i<j;i++)
				{
					strcpy((SP+p1[i])->type,transport);
				}
				printf("\n�޸ĳɹ���");
				getchar();
				saveflag=1;
			}
			else
				Nofind();
		}
		else if(sel_2==2)
		{
			stringinput(findmess,n,"���������޸ĵ����ƣ�");
			Locate(SP,n,findmess,"name",p1);
			getchar();
			if(p1[0]!=-1)
			{
				system("cls");
				j=0;
				printf("    "HEADER2);
				while(1)
				{
					printf("(%2d)",j+1);
					printdata((SP+p1[i]));
					i++;
					j++;
					if(p1[i+1]==-3)
						break;
				}
				stringinput(transport,10,"�������µ����ƣ�");
				printf("�����Ҫ�����޸���<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='n'||ch=='N')
					continue;
			}
			if(p1[0]!=1)
			{
				for(i=0;i<j;i++)
				{
					strcpy((SP+p1[i])->name,transport);
				}
				printf("\n�޸ĳɹ���");
				getchar();
				saveflag=1;
			}
			else
				Nofind();	
		}
		else if(sel_2==3)
		{
			stringinput(findmess,n,"���������޸ĵ��������̣�");
			Locate(SP,n,findmess,"producer",p1);
		
			if(p1[0]!=-1)
			{
				system("cls");
				j=0;
				printf("    "HEADER2);
				while(1)
				{
					printf("(%2d)",j+1);
					printdata((SP+p1[i]));
					i++;
					j++;
					if(p1[i+1]==-3)
						continue;
				}
				stringinput(transport,10,"�������µ��������̣�");
				printf("�����Ҫ�����޸���<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='n'||ch=='N')
					return;
			}
			if(p1[0]!=1)
			{
				for(i=0;i<j;i++)
				{
					strcpy((SP+p1[i])->producer,transport);
				}
				printf("\n�޸ĳɹ���");
				getchar();
				saveflag=1;
			}
			else
				Nofind();	
		}
		else
		{
			Wrong();
		}
	}
	else
	{
		Wrong();
	}
	}
	
}





//������Ʒ��Ϣ
void Save(SPXX goods[],int n)
{
	FILE *fp;
	int i=0;
	fp=fopen("d:\\��Ʒ��Ϣ����ϵͳ\\commoditymess.txt","w");//��ֻд�ķ�ʽ���ļ���
	if(fp==NULL)
	{
		printf("\n--------�ļ���ʧ�ܣ�\a\a");
		getchar();
	}
	for(i=0;i<n;i++)
	{
		if(fwrite(&goods[i],sizeof(SPXX),1,fp)==1)
			continue;
		else
			break;
	}
	if(i>0)
	{
		getchar();
		printf("\n\n--------����ļ����棬ȫ���ı����¼��%d����\n",n);
		getchar();
		saveflag=0;
	}
	else
	{
		system("cls");
		printf("\n\n--------û������Ϣ�����棡\n");
		getchar();
	}
	fclose(fp);//�رմ��ļ���	
}







//ͳ����Ʒ��Ϣ�ĺ���
void count_1(SPXX *SP,int n)
{
	int sel,j=0,i=0,k,p1[30];
	char findmess[20],ch,th,sel_1[5];
	double min,max;
	FILE *fp;
	SPXX *sp=SP,transport;
	while(1){
		system("cls");
	printf("             ͳ���Ӳ˵�\n");
	printf("*****************************************\n");
	printf("*   1 ���ͳ��        2 ����ͳ��        *\n");
	printf("*   3 ����������ͳ��  4 ��Ʒ���ͳ��    *\n");
	printf("*   5 �ֶ�ͳ��        0 �������˵�      *\n");
	printf("*****************************************\n");
	printf("          ���������ѡ��<0~5>:");
	scanf("%s",&sel_1);
	getchar();
	sel=(int)Myatof(sel_1);
	if(sel==0)
		return;
	else if(sel==1)
	{
		while(1)
		{
			j=0;
			i=0;
			system("cls");
			stringinput(findmess,10,"��������ͳ�Ƶ����(��'0'������һ���˵�)��");//Ҫ���н�׳�Ե��жϣ�
			if(findmess[0]=='0'&&strlen(findmess)==1)
				break;
			Locate(sp,n,findmess,"type",p1);
			if(p1[0]==-1)
			{
				Nofind();
				printf("�Ƿ�Ҫ�����µ����<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='y'||ch=='Y')
					continue;
				else
					break;
			}
			while(p1[0]!=-1)
			{
				if(j==0)
					printf(HEADER2);
				printf(HEADER3);
				printdata((sp+p1[i]));
				i++;
				j++;
				if(p1[j+1]==-3)
					break;
			}
			if(p1[0]!=-1)
			{
				printf("\n\n---->���Ϊ%s��%d��\n",findmess,j);
			}
			printf("\n  ��Enter��������һ���˵���");
			getchar();
			break;
		}
	}
	else if(sel==2)
	{
		while(1)
		{
			j=0;
			i=0;
			system("cls");
			stringinput(findmess,10,"��������ͳ�Ƶ�����(��'0'������һ���˵�)��");
			if(findmess[0]=='0'&&strlen(findmess)==1)
				break;
			Locate(sp,n,findmess,"name",p1);
			if(p1[0]==-1)
			{
				Nofind();
				printf("�Ƿ������µ�����?<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='Y'||ch=='y')
					continue;
				else 
					break;
			}
			while(p1[0]!=-1)
			{
				if(j==0)
					printf(HEADER2);
				printf(HEADER3);
				printdata((sp+p1[i]));
				i++;
				j++;
				if(p1[j+1]==-3)
					break;
			}
			if(p1[0]!=-1)
			{
				printf("\n\n---->����Ϊ%s����%d��\n",findmess,j);
			}
			getchar();
			break;
		}	
	}
	else if(sel==3)
	{
		while(1)
		{
			j=0;
			i=0;
			k=0;
			system("cls");
			printf("��������ͳ�Ƶ��۵�����(��xx-xx):");
			scanf("%lf-%lf",&min,&max);
			getchar();
			j=0;
			for(i=0;i<n;i++)
			{
				if((sp+i)->price>=min&&(sp+i)->price<=max)
				{
					p1[j]=i;
					j++;
				}	
			}
			if(j==0)
			{
				printf("�����ڼ۸���%0.2lf��%0.2lf����Ʒ��",min,max);
				printf("�Ƿ������µļ۸����䣿<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='y'||ch=='Y')
					continue;
				else
					break;
			}
			else
			{
				printf(HEADER2);
				for(i=0;i<j;i++)
				{
					for(k=i+1;k<j;k++)
					{
						if((sp+p1[i])->price>(sp+p1[k])->price)
						{
							transport=*(sp+p1[k]);
							*(sp+p1[k])=*(sp+p1[i]);
							*(sp+p1[i])=transport;
						}
					}	
				}
				for(i=0;i<j;i++)
				{
					printf(HEADER3);
					printdata((sp+p1[i]));
				}
				printf("\n\n---->�۸���%0.2lf��%0.2lf����Ʒ��%d����\n",min,max,j);
			}
			fp=fopen("d:\\��Ʒ��Ϣ����ϵͳ\\�۸������嵥.txt","w+");
			if(fp==NULL)
			{
				printf("�ļ������ڣ�");
				exit(0);
			}
			printf("�Ƿ����Ʒ��Ϣ����д��һ���ļ��У�<y/n>:");
			scanf("%c",&th);
			getchar();
			if(th=='y'||th=='Y')
			{
				fprintf(fp,"                                              �۸������嵥\n",NULL);
				fprintf(fp,HEADER4,NULL);
				fprintf(fp, HEADER2_1,NULL);
				for(i=0;i<j;i++)
				{	fprintf(fp,HEADER4,NULL);
					fprintf(fp,FORMAT,(sp+p1[i])->num,(sp+p1[i])->type,(sp+p1[i])->name,(sp+p1[i])->price,(sp+p1[i])->amount,(sp+p1[i])->sold,
							(sp+p1[i])->stock,(sp+p1[i])->total,(sp+p1[i])->producer);
				}
				fclose(fp);
				printf("�ļ��������ɹ���\n");
				getchar();
				break;
			}
			else
			{
				break;
			}
		}	
	}
	else if(sel==4)
	{
		while(1)
		{	
			system("cls");
			j=0;
			i=0;
			printf("\n��������ͳ�ƵĿ��ֵ��");
			scanf("%d",&k);
			getchar();
			for(i=0;i<n;i++)
			{
				if(k>=(sp+i)->stock)
				{
					p1[j]=i;
					j++;
				}
			}
			if(j==0)
			{
				printf("���û�е���%d����Ʒ��",k);
				printf("�Ƿ�����һ���µĿ��ֵ��<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='y'||ch=='Y')
					continue;
				else
					break;
			}
			else
			{
				printf(HEADER2);
				for(i=0;i<j;i++)
				{
					for(k=i+1;k<j;k++)
					{
						if((sp+p1[i])->stock>(sp+p1[k])->stock)
						{
							transport=*(sp+p1[k]);
							*(sp+p1[k])=*(sp+p1[i]);
							*(sp+p1[i])=transport;
						}
					}	
				}
				for(i=0;i<j;i++)
				{
					
					printf(HEADER3);
					printdata((sp+p1[i]));
				}
				printf("\n\n---->������%d����Ʒ��%d����\n",k,j);
			}
			
			fp=fopen("d:\\��Ʒ��Ϣ����ϵͳ\\�����嵥.txt","w+");
			if(fp==NULL)
			{
				printf("�ļ������ڣ�");
				exit(0);
			}
			printf("�Ƿ����Ʒ��Ϣ����д��һ���ļ��У�<y/n>:");
			scanf("%c",&th);
			getchar();
			if(th=='y'||th=='Y')
			{fprintf(fp,"                                               �����嵥\n\n\n",NULL);
				fprintf(fp,HEADER4,NULL);
				fprintf(fp, HEADER2_1,NULL);
				for(i=0;i<j;i++)
				{	fprintf(fp,HEADER4,NULL);
					fprintf(fp,FORMAT,(sp+p1[i])->num,(sp+p1[i])->type,(sp+p1[i])->name,(sp+p1[i])->price,(sp+p1[i])->amount,(sp+p1[i])->sold,
							(sp+p1[i])->stock,(sp+p1[i])->total,(sp+p1[i])->producer);
				}				
				fclose(fp);
				printf("�ļ��������ɹ���");
				getchar();
				break;
			}
			else
				break;
		}	
	}
	else if(sel==5)
	{
		while(1)
		{
			system("cls");
			j=0;
			i=0;
			stringinput(findmess,10,"��������ͳ�Ƶ��ֶ�(��'0'������һ���˵�):");
			if(findmess[0]=='0'&&strlen(findmess)==1)
				break;
			strstrserve_2(sp,n,findmess,p1);
			if(p1[0]==-1)
			{
				printf("û���ҵ���������ֶ�\n�Ƿ������µ��ֶ�<y/n>:");
				scanf("%c",&ch);
				getchar();
				if(ch=='Y'||ch=='y')
					continue;
				else 
					break;
				
			}
			if(p1[0]==-1)
			{
				Nofind();
				getchar();
			}
			while(1)
			{
				if(j==0)
					printf(HEADER2);
				printf(HEADER3);
				printdata((sp+p1[i]));
				i++;
				j++;
				if(p1[j+1]==-3)
					break;
			}
			printf("\n\n---->�ֶ�Ϊ%s����Ʒ��%d��\n",findmess,j);
			printf("��Enter��������һ���˵���");
			getchar();
			break;
		}
	}
	else 
	{	
		Wrong();
		
	}
	}
}



//������������ʾ��¼��
main()
{
	SPXX goods[N],*SP;//=(struct abc *)malloc(sizeof(struct abc));;
	FILE *fp;
	int select;
	char selects[20];//�������˵������룻
	char ch;
	int count=0; 
	system("cls"); //������Ʒ��Ϣ��������
	fp=fopen("d:\\��Ʒ��Ϣ����ϵͳ\\commoditymess.txt","a+");
	if(fp==NULL)
	{
		printf("\n\a\a\a\a*****can't open file!\n");
		exit(0);
	}
	while(!feof(fp))
	{
		if(fread(&goods[count],sizeof(SPXX),1,fp)==1)
			count++;
	}
	fclose(fp);
	printf("**********************************************************************\n");
	printf("*                                                                    *\n");
	printf("*         ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��         *\n");   
	printf("*                                                                    *\n");
	printf("*           ��ӭʹ��                                                 *\n");
	printf("*                                                                    *\n");
	printf("*                          ӯͨ                                      *\n");
	printf("*                                                                    *\n");
	printf("*                                  ��Ʒ��Ϣ����ϵͳ                  *\n");
	printf("*                                                                    *\n");
	printf("*         ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��         *\n");
	printf("*                                                                    *\n");
	printf("**********************************************************************\n");
	printf("\n     �ɹ����ļ����ܹ���%d����¼\n",count);
	sound_1();
	SP=goods;

	//��ʾ���˵�����������ִ����Ӧ�Ĳ�����
	menu();
	while(1)
	{
		system("cls");
		menu();
		scanf("%s",&selects);
		getchar();
		select=(int)Myatof(selects);
		if(select==0)
		{
			if(saveflag==1)
			{
				getchar();
				printf("\n    �Ƿ�Ҫ�����Ѿ��޸ĵ���Ϣ���ļ���(y/n):");
				scanf("%c",&ch);
				if(ch=='y'||ch=='Y')
					Save(goods,count); 
					  
			}
			printf("\n                   ��л��ʹ�ñ�ϵͳ��\n\n\n");
			sound_2();
			break;
		}
		switch(select)
		{
			case 1:count=Add(SP,count);break;
			case 2:system("cls");Disps(SP,count);break;
			case 3:count=Del(SP,count);break;
			case 4:Qur(SP,count);getchar();break;//���� 0 ��ͻ���⣨ע�⣩
			case 5:Modify(SP,count);break;
			case 6:count=Insert(SP,count);break;
			case 7:SelectSort(SP,count);break;
			case 8:Save(SP,count);break;
			case 9:count_1(SP,count);break;
			default:Wrong();break;
		}
	}
}
