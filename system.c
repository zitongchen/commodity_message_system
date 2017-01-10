




/*                                    2014-2015学年第二学期《C语言程序设计实训》
                                      班名：计算机科学与技术专业  医学应用方向14（1）班
									  姓名：         学号：
									       陈子通         1405553127
									  	   曾蔼盈  	      1405553105

  主要亮点：
	1.利用MCI提供了语音提示功能，分别在进入系统，退出系统以及在输入错误的时候发出语音提示；
	2.利用改写的自定义Myatof()函数提供了强大的合理性判断，防止在基本数据类型的输入中输入中文或英文字符；
	3.在程序中写入了大量的合理性判断的代码，使程序的安全性大大提高；
	4.在系统中的基本数据类型中添加了库存的数量统计；
	5.在代码模块中不但有批量修改功能，还有批量删除功能；
	6.在统计功能和查询功能中对价格区间和库存在输出是进行了升序的排序输出；
	

  存在不足：
  1.无法解决单价区间输入时不按规则输入所产生的问题；


  大致分工：陈子通同学主要负责大部分函数，如：录入，显示，删除，查询，修改，统计，保存共7个函数和修改bug
			曾蔼盈同学主要负责排序和插入两个函数、负责寻找bug和设计框

*/



//预处理命令；
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>
//#include<ctype.h>
#include <windows.h>             //
#include <mmsystem.h>           //这三个是音频所要的头文件
#pragma comment(lib,"winmm.lib")//




#define HEADER1 "---------------------------------------------------商品信息管理系统----------------------------------------------\n"
#define HEADER2 "| 商品编号  | 商品类别   | 商品名称  |        单价 |  商品数量|  售出数量|     库存|  商品总金额|生产厂家        |\n"
#define HEADER2_1 "| 商品编号  |  商品类别   |  商品名称 |      单价   | 商品数量 | 售出数量  |   库存  | 商品总金额 |     生产厂家    |\n"

#define HEADER3 "|-----------|------------|-----------|-------------|----------|----------|---------|------------|----------------|\n"
#define HEADER4 "|----------------------------------------------------------------------------------------------------------------\n"
#define FORMAT  "| %-10s| %-10s | %-10s|   %10.2lf|     %5d|     %5d|    %5d|  %10.2lf| %-14s |\n"

#define DATA  p->num, p->type ,p->name, p->price, p->amount, p->sold, p->stock, p->total, p->producer
#define END    "\n|-------------------------------------------------------------------------------------------------------------------|\n"
#define N 100

int saveflag=0;  //全局变量，标识是否需要存盘的标志变量

//商品信息管理系统的核心数据结构
typedef struct commodity
{	char num[10];          //商品编号
	char type[10];         //商品类别
	char name[10];         //商品名称
	char producer[20];     //生产厂家
	double price;         //商品单价
	int amount;           //商品数量
	int sold;             //商品售出数量
	double total;         //商品总金额
	int stock;           //商品的库存；

}SPXX;

//显示系统主菜单
void menu()
{
	system("cls");
	printf("                   商品信息管理系统                 \n");
	printf("*************************主菜单**************************\n");
	printf("*             1 录入信息        2 显示信息              *\n");
	printf("*             3 删除信息        4 查询信息              *\n");
	printf("*             5 修改信息        6 插入信息              *\n");
	printf("*             7 排序信息        8 保存信息              *\n");
	printf("*             9 统计信息        0 退出系统              *\n");
	printf("*********************************************************\n");
	printf("                  请输入你的选择<0-9>:\n");
}


//错误提示音频函数
void sound()
{
	mciSendString("open \d:\\商品信息管理系统\\错误提示语.mp3\ type MPEGVideo alias file", NULL, 0, NULL);
	mciSendString("seek yeah to start", 0, 0, 0);//定位到起始点
    mciSendString("play file", NULL, 0, NULL);//音频的开始
	getchar();
	mciSendString("close file",NULL,0,NULL);//音频的关闭
	
    
}
//欢迎音频函数
void sound_1()
{
	mciSendString("open \d:\\商品信息管理系统\\欢迎语.mp3\ type MPEGVideo alias file", NULL, 0, NULL);
	mciSendString("seek yeah to start", 0, 0, 0);//定位到起始点
    mciSendString("play file", NULL, 0, NULL);
	getchar();
	mciSendString("close file",NULL,0,NULL);
	
	
    
}
//结束语音频
void sound_2()
{
	mciSendString("open \d:\\商品信息管理系统\\结束语.mp3\ type MPEGVideo alias file", NULL, 0, NULL);
	mciSendString("seek yeah to start", 0, 0, 0);//定位到起始点
    mciSendString("play file", NULL, 0, NULL);
	getchar();
	mciSendString("close file",NULL,0,NULL);

    
}


//格式化输出表头//printf(HEADER3);
void printheader()
{
	printf(HEADER1);
	printf("\n");
	printf(HEADER2);
	
}

//格式化输出表中数据
void printdata(SPXX *p)
{	
	
	printf(FORMAT,DATA);
}
//以表格的形式输出,与printdata()有小许的差别；
void printdata_1(SPXX pp)
{
	SPXX *p;
	p=&pp;
	printf(HEADER3);
	printf(FORMAT,DATA);

}

//输出按键错误信息
void Wrong(){
	printf("\n\n\n\n\n\n***********Error输入有误！敲Enter键继续***********\n");
	sound();

}

//输出没查找到此记录的信息
void Nofind()
{ 
	printf("\n\n\n********没找到你要的信息！*********\n");
	
}


//Disp函数：用于把已有的信息显示到屏幕上,属于大函数中内嵌的函数；
void Disp(SPXX *SP,int n)
{
	int i;
	if(n==0)
	{
		printf("\n-------商品信息管理系统尚未记录！\n");
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


//把数据信息输出到屏幕上，并按0返回；于Disp()有所区别；
void Disps(SPXX *SP,int n)
{	int i;
	char k[5];
	SPXX *sp=SP;
	double Myatof(char str[]);//Myatof()函数的声明
	
	if(n==0)
	{
		printf("\n-------商品信息管理系统尚未记录！\n");
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

	printf("按'0'返回主菜单：");
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
			printf("按'0'返回主菜单：");
			scanf("%s",k);
			getchar();
		}	
	}
}

//函数stringinput的作用：输入字符串，并进行长度的判断
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
			printf("\n\n超过了规定的长度！\n\n");
	}while (i>lens);
	strcpy(t,str);
}

//自定义的atof()函数；
double Myatof(char str[])
{
	int i=0,t=0,k=0;
	double j=0;//atof()返回的是double类型；
	char c[2]="\0";
	i=strlen(str);
	for(t=0;t<i;t++)
	{
		if('A'<=str[t])
		{
			return -1;
		}
		else if(str[t]&0x80)//利用按位与判断输入的是否是中文
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


//用于基本数据类型的输入：如int,double；（这里存在问题）
double datainput(char *notice)
{ 
	double t;
	char p[20];

	while(1)
	{	t=0;
		printf(notice);
		scanf("%s",p);
		t=Myatof(p);//将字符串str转换成一个双精度数值并返回结果。 参数str 必须以有效数字开头

		if(t==-1)//输入的含有中文和和英文字符便执行这代码；
		{
			printf("输入不能含有中文或英文字符,请从新输入!");
			continue;
		}
		else if(t<0)
		{
			printf("输入的数值不能为负数！");
			continue;
		}
		else	
			return t;
	}
}


//Locate的作用，用于定位符合要求的记录；

void Locate(SPXX *SP,int n,char findmess[],char nameorphonenum[],int p1[])//涉及到有同名称的结构体，                                                            
{                                                                         //所以用数组把同名称的结构体下标装起来； 
	int i=0,j;               
	p1[0]=-2;            //把p1[0]赋值为-2用于作为判断，若p1[0]=-2证明没有找到要找的信息的下标；                  
	if(strcmp(nameorphonenum,"num")==0)
	{
		j=0;           //让下标从0开始；
		while(i<n)
		{
			if(strcmp((SP+i)->num,findmess)==0)
			{
				p1[j]=i;
				j++;	
			}
			i++;	
		}
		if(p1[0]==-2)          //这个if语句成立证明没有找到要找的编号或名称；
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
		p1[j+1]=-3;//用于在返回的时候判断输出在屏幕上的信息是否结束；
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
		p1[j+1]=-3;//用于在返回的时候判断输出在屏幕上的信息是否结束；
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
		p1[j+1]=-3;//用于在返回的时候判断输出在屏幕上的信息是否结束；
		if(p1[0]==-2)
			p1[0]=-1;
	}
}





//模糊查询，，函数的构建思路跟Locate()的类似
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
			{//功能：函数返回一个指针，它指向字符串str2 首次出现于字符串str1中的位置，如果没有找到，返回NULL。
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
  

//查询功能的模糊查询模块；
//没有分编号的模糊查询和类别的模糊查询，而是把编号，类别等的模糊查询通过for循环全部查询；
//跟百度都模糊查询有点相似；
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



//函数Add的作用：添加商品信息；
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
			stringinput(num,10,"输入编号（按'0'返回主菜单）：");
			flag=0;
			if(strcmp(num,"0")==0) return n;
			i=0;
			while(i<n)
			{
				if(strcmp((SP+i)->num,num)==0)
				{
					flag=1;break;//若flag=1那么说明输入的编号已经存在了
				}
				i++;
			}
			for(i=0;i<strlen(num);i++)
			{
				if(num[i]&0x80)//利用按位与判断输入的是否是中文；
				{
					c[j]=num[i];
					j++;
					if(j==2)
					{
						j=0;
						printf("编号中不能存在中文字符!\n是否从新输入编号：");
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
			if(flag==2)//存在中文字符后判断是否从新输入；
				continue;
			if(flag==1)
			{
				printf("--------编号%s已经存在，在试一次？(y/n):",num);
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
		//字符串类型信息的输入
		strcpy((SP+n)->num,num);
		stringinput((SP+n)->type,10,"类别:");
		stringinput((SP+n)->name,10,"名称:");
		stringinput((SP+n)->producer,20,"生产厂家:");
		
		//基本数据类型数据的输入；
		(SP+n)->price=datainput("单价:");
		(SP+n)->amount=(int)datainput("数量:");
		(SP+n)->sold=(int)datainput("售出商品数量：");

		//数量与售出数量的合理性判断；
		while((SP+n)->amount<(SP+n)->sold)
		{
			printf("你输入的售出商品数量应该要少于%d。\n",(SP+n)->amount);
			(SP+n)->sold=(int)datainput("请输入新的售出商品数量：");
		}
	
		//通过数学运算自动生成商品库存和商品总金额；
		(SP+n)->total=((SP+n)->price*(SP+n)->amount);
		(SP+n)->stock=((SP+n)->amount-(SP+n)->sold);  
		n++;
		saveflag=1;
	}
	return n;
}




//函数Del_2用于模糊查找并删除单条数据信息，先找到相关信息的下标并放在数组中，然后在数组中删除该组元素；
int Del_2(SPXX *SP,int n)
{
	int sel,p2[30],j,p,i;
	char findmess[10],flag,sel_1[5];
	while(1)
	{
		j=0;i=0;
		system("cls");
		Disp(SP,n);
		printf("\n        模糊删除子菜单         \n");
		printf("*********************************\n");
		printf("*      1 根据编号 2 根据名称    *\n");
		printf("*      0 返回上一级菜单         *\n");
		printf("*********************************\n");
		printf("           请选择<0-2>:         \n");
		scanf("%s",sel_1);
		getchar();
		sel=(int)Myatof(sel_1);    //健壮性判断；输入有错误提示；
		if(sel==0)
			return n;
		else if(sel==1)
		{
			stringinput(findmess,10,"编号字段：");
			strstrserve(SP,n,findmess,"num",p2);	//模糊查找下标，并存储在p2数组中
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
				printf("请输入你想删除的项<按'0'返回上一级菜单>：\n");
				scanf("%d",&i);
				getchar();
				while(i>j)                //健壮性判断，
				{	
					printf("你选择的项不存在！\n请从新输入<按'0'返回上一级菜单>：");
					scanf("%d",&i);
					getchar();
					if(i==0)
						break;
				}
				if(i==0)
					continue;
				p=p2[i-1];//把相应信息的商品下标给p;
			
				printf("你真的要删除吗？<y/n>:");
				scanf("%c",&flag);
				if(flag=='N'||flag=='n')
					continue;
			}
			if(p2[0]!=-1)
			{
				for(i=p+1;i<n;i++)
				{
					SP[i-1]=SP[i];//确定后删除相应的信息；
				}
				printf("\n删除成功！\n");
				n--;
				getchar();
				saveflag=1;
			}
			else 
				Nofind();
		}	
		else if(sel==2)
		{
			stringinput(findmess,15,"输入已有的名称：");
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
				printf("请输入你想删除的项<按'0'返回上一级菜单>：\n");
				scanf("%d",&i);	
				getchar();
				while(i>j)                //健壮性判断，
				{	
					printf("你选择的项不存在！\n请从新输入<按'0'返回上一级菜单>：");
					scanf("%d",&i);
					getchar();
					if(i==0)
						break;
					
				}
				if(i==0)
					continue;
				p=p2[i-1];
				printf("你真的要删除吗？<y/n>:");
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
				printf("\n删除成功！\n");
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




//函数Del用于删除数据信息，先找到保存该元素的下标，然后在数组中删除该组元素；
int Del(SPXX *SP,int n)
{
	int sel,p1[30],j=0, p,i=0;
	char findmess[20],flag,sel_2[5];
	if(n<0)
	{
		system("cls");
		printf("\n-------商品信息系统暂时没有信息！\n");
		getchar();
		return n;
	}

	while(1){
		system("cls");
		Disp(SP,n);
		printf("\n          删除子菜单         \n");
		printf("*********************************\n");
		printf("*      1 根据编号 2 根据名称    *\n");
		printf("*      3 根据类别 4 模糊删除    *\n");
		printf("*      5 批量删除 0 返回主菜单  *\n");
		printf("*********************************\n");
		printf("           请选择<0-5>:");
		scanf("%s",&sel_2);
		getchar();                 //这里的很重要哦！多看看
		sel=(int)Myatof(sel_2);    //健壮性判断；
		if(sel==0)
			return n;
		else if(sel==1)
		{
			stringinput(findmess,10,"输入已有的编号：");
			Locate(SP,n,findmess,"num",p1);		
			p=p1[0];                     //编号有唯一性，所以只要判断p1[0]的值就可以了；
			if(p!=-1)//如果不存在信息就不用执行这个if语句；
			{
				printf(HEADER2);
				printdata(SP+p);
				printf("你真的要删除吗？<y/n>:");
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
				printf("删除成功！\n");
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
				stringinput(findmess,15,"输入已有的名称：");
				Locate(SP,n,findmess,"name",p1);
			
			}
			else
			{
				stringinput(findmess,15,"输入已有的类别：");
				Locate(SP,n,findmess,"type",p1);
			
			}
			if(p1[0]!=-1)///如有没有数据就不用执行这个if语句；
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
				printf("请输入你想删除的项<按'0'返回上一级菜单>：\n");
				scanf("%d",&i);
				getchar();
				p=p1[i-1];
				while(i>j)                //健壮性判断，
				{	
					printf("你选择的项不存在！\n请从新输入<按'0'返回上一级菜单>：");
					scanf("%d",&i);
					getchar();
					if(i==0)
						break;
				}
				if(i==0)
					continue;
				printf("你真的要删除吗？<y/n>:");
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
				printf("\n删除成功！\n");
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
			Del_2(SP,n);//在这里调用模糊删除子函数
		}
		else if(sel==5)
		{
			while(1){
				j=0;i=0;
			system("cls");
			sel=0;
			printf("          批量删除子菜单\n");
			printf("***************************************\n");
			printf("*   1 商品类别      2 商品名称        * \n");
			printf("*   3 商品生产厂商  0 返回上一级主菜单*\n");
			printf("***************************************\n");
			printf("         请选择<0-3>：");
			scanf("%s",&sel_2);
			getchar();
			sel=(int)Myatof(sel_2);//健壮性判断
			if(sel==0)
				break ;
			else if(sel==1)
			{
				stringinput(findmess,10,"输入你想删除的类别：");
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
					printf("你真的要批量删除吗？<y/n>:");
					scanf("%c",&flag);
					getchar();
					if(flag=='n'||flag=='N')
						continue;
				}
				if(p1[0]!=1)
				{
					for(i=0;i<j;i++)
					{
					
						for(p=p1[i]-i;p<n;p++)//减i是因为在原来数的下标前移了i为了得到原来的数所以减i；
						{
							SP[p]=SP[p+1];
						}
						n--;
					}
					printf("\n批量删除成功！");
					getchar();
					saveflag=1;
				}
				else
					Nofind();
			}
			else if(sel==2)
			{
				stringinput(findmess,n,"输入你想删除的名称：");
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
				
					printf("你真的要批量删除吗？<y/n>:");
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
					printf("\n批量删除成功！");
					getchar();
					saveflag=1;
				}
				else
					Nofind();	
			}
			else if(sel==3)
			{
				stringinput(findmess,n,"输入你想删除的生产厂商：");
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
					printf("你真的要批量删除吗？<y/n>:");
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
					printf("\n批量删除成功！");
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



//查询函数
void Qur(SPXX *SP,int n)
{
	int sel,j,i,p=0,p1[30],k;
	double max,min;
	char findmess[20],sel_1[5];
	SPXX transport;
	if(n<0)
	{
		system("cls");
		printf("\n-------商品系统没有记录！\n");
		getchar();
	}
	
	while(1)
	{	j=0,i=0;
		system("cls");
		printf("        	    查询子菜单\n");
		printf("**********************************************\n");
		printf("*       1 精确查询       2 模糊查询          *\n");
		printf("*       3 单价区间查询   0 返回主菜单        *\n");
		printf("**********************************************\n");
		printf("                请选择<0-3>:   ");
		scanf("%s",sel_1);
		getchar();
		sel=(int)Myatof(sel_1);
		if(sel==0)
			return ;
		else if(sel==1)
		{
			while(1){
			system("cls");
			printf("\n         精确查询子菜单         \n");
			printf("**********************************\n");
			printf("*      1 根据编号 2 根据名称     *\n");
			printf("*      3 根据类别 0 返回主菜单   *\n");
			printf("*********************************\n");
			printf("           请选择<0-3>         ");
			scanf("%s",&sel_1);
			getchar();                
			sel=(int)Myatof(sel_1);    //健壮性判断；
			if(sel==0)
				break;
			else if(sel==1)
			{
				stringinput(findmess,10,"输入已有的编号：");
				Locate(SP,n,findmess,"num",p1);		
				p=p1[0];   //编号有唯一性，所以只要判断p1[0]的值就可以了；
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
					stringinput(findmess,15,"输入已有的名称：");
					Locate(SP,n,findmess,"name",p1);
				}
				else
				{
					stringinput(findmess,15,"输入已有的类别：");
					Locate(SP,n,findmess,"type",p1);
				}
				if(p1[0]!=-1)///如有没有数据就不用执行这个if语句；
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
					printf("\n  按Enter键返回上一级菜单！");
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
			printf("\n输入你要查询的内容：");
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
			printf("\n  按Enter键返回上一级菜单！");
			getchar();
		}
		else if(sel==3)
		{
			system("cls");
			j=0;
			p1[0]=-1;
			printf("输入你要查询单价格区间(如：xx-xx)：");
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
				printf("\n\n不存在价格在%lf到%lf的商品！",min,max);
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
			printf("\n  按Enter键返回上一级菜单！");
			getchar();
		}
		else
		{	Wrong();
		}
	}

}


//排序函数
void SelectSort(SPXX goods[],int n)
{	int i,j,indexmin,select;
	char sel[5];
	SPXX newinfo;
	if(n<=0)
	{	system("cls");
		printf("n====>尚无记录！\n");
		getchar();
	}
	system("cls");
	Disp(goods,n);//显示排序前的所有记录
	printf("\n\n");
	printf("                排序子菜单\n");
	printf("******************************************\n");
	printf("*    1 按编号升序排序  2 按类型升序排序  *\n");
	printf("*    3 按名称升序排序  4 按单价升序排序  *\n");
	printf("*    5 按库存升序排序  0 按'0'返回主菜单 *\n");
	printf("******************************************\n");
	printf("	   请输入选项编号<0-5>:   ");
	scanf("%s",&sel);
	select=(int)Myatof(sel);    //健壮性判断；
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
		Disp(goods,n);//显示排序后所有记录
		getchar();
		saveflag=1;
		printf("\n   ------完成排序！\n");
		printf("\n按Enter键返回上一级菜单！");
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
		printf("\n完成排序！\n");
		getchar();  

	}
	else if (select==3)//按记录姓名排序
	{	for(i=0;i<n-1;i++)
		{	indexmin=i;
			for(j=i+1;j<n;j++)
				if(strcmp(goods[j].name,goods[indexmin].name)<0)   indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);//显示排序后所有记录
		getchar();
		saveflag=1;
		printf("\n完成排序!\n");
		getchar();
	}
	else if (select==4)//按记录单价升序排序
	{	for(i=0;i<n-1;i++)
		{	indexmin=i;
			for(j=i+1;j<n;j++)
				if(goods[j].price<goods[indexmin].price)   indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);//显示排序后所有记录
		getchar();
		saveflag=1;
		printf("\n完成排序!\n");
		getchar();
	}
	else if (select==5)//按记录库存升序排序
	{	for(i=0;i<n-1;i++)
		{	indexmin=i;
			for(j=i+1;j<n;j++)
				if(goods[j].stock<goods[indexmin].stock)   indexmin=j;
			newinfo=goods[i];
			goods[i]=goods[indexmin];
			goods[indexmin]=newinfo;
		}
		system("cls");
		Disp(goods,n);//显示排序后所有记录
		getchar();
		saveflag=1;
		printf("\n 完成排序!\n");
		getchar();
	}
	else
	{	Wrong();
		
	}
}


//函数Insert用于插入记录：首先按编号查询到要插入的数组元素位置，然后在该记录编号之后插入一个新数组元素
int Insert(SPXX goods[],int n)
{	char ch,num[10],s[10];     //s[]保存插入点位置之前的记录编号，num[]保存输入的新纪录的编号
	SPXX newinfo;		       //用于交换的临时变量
	int flag,i,k=0;
	system("cls");
	Disp(goods,n);
	while(1)
	{
	while(1)
	{	stringinput (s,10,"请输入一个记录编号，待插入的记录将位于该编号记录的后面<按'0'返回主菜单>：");
		if((int)Myatof(s)==0&&strlen(s)==1)  //用于判断是否返回主菜单；
			return n; 
		flag=0;i=0;
		while(i<n)            //查询该编号是否存在，flag=1表示该编号存在
		{	if(strcmp(goods[i].num,s)==0)
			{	k=i;
				flag=1;
				break;
			}
			i++;
		}
		if(flag==1) break;    //若编号存在，则进行插入之前的新纪录输入操作
		else
		{	while(1)
			{
			printf("\n=====>编号%s 不存在，再试一次？(y/n):",s);
			scanf("%c",&ch);
			getchar();
			if(ch=='y'||ch=='Y') 
				break;
			else if(ch=='n'||ch=='N')  //用于判断是否返回主菜单，若没有这一句按任意键都能返回主菜单（除了y）
				return n;
			else
			{
				printf("你的输入有误请从新输入！");
				getchar();
			}
			}
		}
	}
	while(1)
	{
		stringinput(num,10,"请输入新的编号：");
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
			printf("编号%s已经存在，再试一次？(y/n):",num);
			scanf("%c",&ch);
			getchar();
			if(ch=='y'||ch=='Y')
				break;
			else if(ch=='n'||ch=='N')
				return n;
			else
			{
				printf("你的输入有误请从新输入！\n");
				getchar();
			}			
			}
		}
		else break;
	}
	strcpy(newinfo.num,num);                  //接受新输入的信息；
	stringinput(newinfo.type,10,"类别:");
	stringinput(newinfo.name,10,"名称:");
	newinfo.price=datainput("单价：");
	newinfo.amount=(int)datainput("商品数量：");
	newinfo.sold=(int)datainput("商品售出数量：");
	newinfo.total=(newinfo.price*newinfo.amount);
	newinfo.stock=(newinfo.amount-newinfo.sold);
	stringinput(newinfo.producer,16,"生产厂商:");
	saveflag=1;
	for(i=n-1;i>k;i--)                       //新编号的信息向后移；
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

//Modify()函数用于修改商品的信息，功能有：精确修改和批量修改
void Modify(SPXX *SP,int n)
{
	char findmess[20],transport[20],ch,sel[5];
	int p=0,sel_1,p1[25],sel_2=0,flag=0,j=0,i=0;

	if(n<=0)
	{
		system("cls");
		printf("\n----商品信息系统没有记录！");
		getchar();
	}
	while(1)
	{system("cls");
	Disp(SP,n);
	printf("           修改子菜单\n");
	printf("************************************\n");
	printf("*    1 精确修改  2 批量修改        *\n");
	printf("*    0 返回主菜单                  *\n");
	printf("*************************************\n");
	printf("        输入你的选择<0-2>:");
	scanf("%s",&sel);
	getchar();
	sel_1=(int)Myatof(sel);
	if(sel_1==0)
		return ;
	else if(sel_1==1)
	{
		system("cls");
		stringinput(findmess,10,"请输入一个已经存在的编号：");
		Locate(SP,n,findmess,"num",p1);         //寻找输入编号的下标；
		p=p1[0];
		if(p!=-1)
		{	printf(HEADER2);
			printdata((SP+p));

		}
		if(p!=-1)
		{
			printf("        精确修改子菜单\n");
			printf("**********************************\n");
			printf("*    1 商品编号  2 商品类别      * \n");
			printf("*    3 商品名称  4 商品单价      *  \n");
			printf("*    5 商品数量  6 商品售出数量  *  \n");
			printf("*    7 商品生产厂家              *  \n");
			printf("*    0 返回上一级菜单            *     \n");
			printf("**********************************\n");
			printf("        输入你的选择<0-7>:  ");
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
					printf("输入新的商品编号：");
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
						printf("你输入的商品编号已经存在！\n");
						printf("是否再输入一个新的编号<y/n>:");
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
				printf("输入新的商品类型：");
				scanf("%s",transport);
				strcpy((SP+p)->type,transport);
				getchar();
			}
			else if(sel_2==3)
			{
				printf("输入新的商品名称：");
				scanf("%s",transport);
				strcpy((SP+p)->name,transport);
				getchar();
			}
			else if(sel_2==4)
			{
				(SP+p)->price=datainput("输入新的商品单价：");
				getchar();
			}
			else if(sel_2==5)
			{
				(SP+p)->amount=(int)datainput("输入新的商品数量：");
				getchar();
				while((SP+p)->amount<(SP+p)->sold)
				{
					printf("商品数量不应该少于%d。",(SP+p)->sold);
					(SP+p)->amount=(int)datainput("输入新的商品数量：");
				}
			}
			else if(sel_2==6)
			{
				(SP+p)->sold=(int)datainput("输入新的商品售出数量：");
				getchar();
				while((SP+p)->amount<(SP+p)->sold)
				{
					printf("商品数量不应该多于%d。",(SP+p)->amount);
					(SP+p)->sold=(int)datainput("输入新的商品售出数量：");
				}
			}
			else if(sel_2==7)
			{
				printf("输入新的商品生产厂家：");
				scanf("%s",transport);
				strcpy((SP+p)->producer,transport);
				getchar();
			}
			(SP+p)->total=(SP+p)->amount*(SP+p)->price;//自动生成的数值；
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
		printf("          批量修改子菜单\n");
		printf("*****************************************\n");
		printf("*    1 商品类别       2 商品名称        *\n");
		printf("*    3 商品生产厂商   0 返回上一级主菜单*\n");
		printf("*****************************************\n");
		printf("         请选择<0-3>：       ");
		scanf("%s",&sel);
		getchar();
		sel_2=(int)Myatof(sel);
		if(sel_2==0)
			continue ;
		else if(sel_2==1)
		{
			stringinput(findmess,10,"输入你想修改的类别：");
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
				stringinput(transport,10,"请输入新的类别：");
				printf("你真的要批量修改吗？<y/n>:");
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
				printf("\n修改成功！");
				getchar();
				saveflag=1;
			}
			else
				Nofind();
		}
		else if(sel_2==2)
		{
			stringinput(findmess,n,"输入你想修改的名称：");
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
				stringinput(transport,10,"请输入新的名称：");
				printf("你真的要批量修改吗？<y/n>:");
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
				printf("\n修改成功！");
				getchar();
				saveflag=1;
			}
			else
				Nofind();	
		}
		else if(sel_2==3)
		{
			stringinput(findmess,n,"输入你想修改的生产厂商：");
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
				stringinput(transport,10,"请输入新的生产厂商：");
				printf("你真的要批量修改吗？<y/n>:");
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
				printf("\n修改成功！");
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





//保存商品信息
void Save(SPXX goods[],int n)
{
	FILE *fp;
	int i=0;
	fp=fopen("d:\\商品信息管理系统\\commoditymess.txt","w");//以只写的方式打开文件；
	if(fp==NULL)
	{
		printf("\n--------文件打开失败！\a\a");
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
		printf("\n\n--------完成文件保存，全部的保存记录有%d条！\n",n);
		getchar();
		saveflag=0;
	}
	else
	{
		system("cls");
		printf("\n\n--------没有新信息被保存！\n");
		getchar();
	}
	fclose(fp);//关闭此文件；	
}







//统计商品信息的函数
void count_1(SPXX *SP,int n)
{
	int sel,j=0,i=0,k,p1[30];
	char findmess[20],ch,th,sel_1[5];
	double min,max;
	FILE *fp;
	SPXX *sp=SP,transport;
	while(1){
		system("cls");
	printf("             统计子菜单\n");
	printf("*****************************************\n");
	printf("*   1 类别统计        2 名称统计        *\n");
	printf("*   3 单价上下限统计  4 商品库存统计    *\n");
	printf("*   5 字段统计        0 返回主菜单      *\n");
	printf("*****************************************\n");
	printf("          请输入你的选择<0~5>:");
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
			stringinput(findmess,10,"输入你想统计的类别(按'0'返回上一级菜单)：");//要进行健壮性的判断；
			if(findmess[0]=='0'&&strlen(findmess)==1)
				break;
			Locate(sp,n,findmess,"type",p1);
			if(p1[0]==-1)
			{
				Nofind();
				printf("是否要输入新的类别！<y/n>:");
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
				printf("\n\n---->类别为%s有%d项\n",findmess,j);
			}
			printf("\n  按Enter键返回上一级菜单！");
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
			stringinput(findmess,10,"输入你想统计的名称(按'0'返回上一级菜单)：");
			if(findmess[0]=='0'&&strlen(findmess)==1)
				break;
			Locate(sp,n,findmess,"name",p1);
			if(p1[0]==-1)
			{
				Nofind();
				printf("是否输入新的名称?<y/n>:");
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
				printf("\n\n---->名称为%s的有%d项\n",findmess,j);
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
			printf("输入你想统计单价的区间(如xx-xx):");
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
				printf("不存在价格在%0.2lf到%0.2lf的商品！",min,max);
				printf("是否输入新的价格区间？<y/n>:");
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
				printf("\n\n---->价格在%0.2lf到%0.2lf的商品有%d件。\n",min,max,j);
			}
			fp=fopen("d:\\商品信息管理系统\\价格区间清单.txt","w+");
			if(fp==NULL)
			{
				printf("文件不存在！");
				exit(0);
			}
			printf("是否把商品信息数据写到一个文件中！<y/n>:");
			scanf("%c",&th);
			getchar();
			if(th=='y'||th=='Y')
			{
				fprintf(fp,"                                              价格区间清单\n",NULL);
				fprintf(fp,HEADER4,NULL);
				fprintf(fp, HEADER2_1,NULL);
				for(i=0;i<j;i++)
				{	fprintf(fp,HEADER4,NULL);
					fprintf(fp,FORMAT,(sp+p1[i])->num,(sp+p1[i])->type,(sp+p1[i])->name,(sp+p1[i])->price,(sp+p1[i])->amount,(sp+p1[i])->sold,
							(sp+p1[i])->stock,(sp+p1[i])->total,(sp+p1[i])->producer);
				}
				fclose(fp);
				printf("文件输出保存成功！\n");
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
			printf("\n输入你想统计的库存值：");
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
				printf("库存没有低于%d的商品！",k);
				printf("是否输入一个新的库存值？<y/n>:");
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
				printf("\n\n---->库存低于%d的商品有%d件！\n",k,j);
			}
			
			fp=fopen("d:\\商品信息管理系统\\进货清单.txt","w+");
			if(fp==NULL)
			{
				printf("文件不存在！");
				exit(0);
			}
			printf("是否把商品信息数据写到一个文件中！<y/n>:");
			scanf("%c",&th);
			getchar();
			if(th=='y'||th=='Y')
			{fprintf(fp,"                                               进货清单\n\n\n",NULL);
				fprintf(fp,HEADER4,NULL);
				fprintf(fp, HEADER2_1,NULL);
				for(i=0;i<j;i++)
				{	fprintf(fp,HEADER4,NULL);
					fprintf(fp,FORMAT,(sp+p1[i])->num,(sp+p1[i])->type,(sp+p1[i])->name,(sp+p1[i])->price,(sp+p1[i])->amount,(sp+p1[i])->sold,
							(sp+p1[i])->stock,(sp+p1[i])->total,(sp+p1[i])->producer);
				}				
				fclose(fp);
				printf("文件输出保存成功！");
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
			stringinput(findmess,10,"输入你想统计的字段(按'0'返回上一级菜单):");
			if(findmess[0]=='0'&&strlen(findmess)==1)
				break;
			strstrserve_2(sp,n,findmess,p1);
			if(p1[0]==-1)
			{
				printf("没有找到你输入的字段\n是否输入新的字段<y/n>:");
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
			printf("\n\n---->字段为%s的商品有%d项\n",findmess,j);
			printf("按Enter键返回上一级菜单！");
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



//打开主函数，显示记录；
main()
{
	SPXX goods[N],*SP;//=(struct abc *)malloc(sizeof(struct abc));;
	FILE *fp;
	int select;
	char selects[20];//接受主菜单的输入；
	char ch;
	int count=0; 
	system("cls"); //保存商品信息的条数；
	fp=fopen("d:\\商品信息管理系统\\commoditymess.txt","a+");
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
	printf("*         ★  ★  ★  ★  ★  ★  ★  ★  ★  ★  ★  ★  ★         *\n");   
	printf("*                                                                    *\n");
	printf("*           欢迎使用                                                 *\n");
	printf("*                                                                    *\n");
	printf("*                          盈通                                      *\n");
	printf("*                                                                    *\n");
	printf("*                                  商品信息管理系统                  *\n");
	printf("*                                                                    *\n");
	printf("*         ★  ★  ★  ★  ★  ★  ★  ★  ★  ★  ★  ★  ★         *\n");
	printf("*                                                                    *\n");
	printf("**********************************************************************\n");
	printf("\n     成功打开文件，总共有%d条记录\n",count);
	sound_1();
	SP=goods;

	//显示主菜单，根据输入执行相应的操作；
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
				printf("\n    是否要保存已经修改的信息到文件？(y/n):");
				scanf("%c",&ch);
				if(ch=='y'||ch=='Y')
					Save(goods,count); 
					  
			}
			printf("\n                   感谢你使用本系统！\n\n\n");
			sound_2();
			break;
		}
		switch(select)
		{
			case 1:count=Add(SP,count);break;
			case 2:system("cls");Disps(SP,count);break;
			case 3:count=Del(SP,count);break;
			case 4:Qur(SP,count);getchar();break;//存在 0 冲突问题（注意）
			case 5:Modify(SP,count);break;
			case 6:count=Insert(SP,count);break;
			case 7:SelectSort(SP,count);break;
			case 8:Save(SP,count);break;
			case 9:count_1(SP,count);break;
			default:Wrong();break;
		}
	}
}
