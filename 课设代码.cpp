#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
#define INF 10000;
typedef struct node//结点
{
	char num;//结点编号
	char name[20];//结点名称
}node;
typedef struct graph//图
{
	node no[20];//图中包含的结点
	int a[20][20];//直接路径长度
	int jdnum,bnum;//结点数，边数
}graph;
int getplace(graph *t,char x)//得到编号为x在数组中下标
{
	for(int i=0;i<t->jdnum;i++)
	{
		if(t->no[i].num==x)
		{return i;}
	}
	cout<<"error";
	return -1;
}
void tu1(graph *t)//显示文件内信息
{
	cout<<t->jdnum;
	cout<<endl;
	for(int i=0;i<t->jdnum;i++)
	{
		cout<<t->no[i].num<<" ";
		cout<<t->no[i].name<<" ";
	}
	cout<<endl;
	cout<<t->bnum;
	for(int i=0;i<t->jdnum;i++)
	{
		for(int j=0;j<t->jdnum;j++)
		{
			cout<<t->a[i][j]<<"   ";
		}
		cout<<endl;
	}
}
void tu2(graph *t,int d[20][20])//显示所有路径及其距离
{
	int n=0;
	for(int i=0;i<t->jdnum;i++)
	{
		for(int j=i;j<t->jdnum;j++)
		{
			cout<<t->no[i].name<<"->"<<t->no[j].name<<"  距离为："<<d[i][j]<<"         ";
			n++;
			if(n%3==0)
			{cout<<endl;}
		}
	}
}
void creat(graph *t)//构造一个图，并将其以文件存储
{
	FILE *fp;
	fp=fopen("tu","w");
	cout<<"构造校园平面图"<<endl;
	cout<<"请输入总结点数：";
	cin>>t->jdnum;
	cout<<"请输入结点编号及名称："<<endl;
	for(int i=0;i<t->jdnum;i++)
	{
		cin>>t->no[i].num;
		cin>>t->no[i].name;
	}
	cout<<"请输入边数：";
	cin>>t->bnum;
	for(int i=0;i<t->jdnum;i++)
	{
		for(int j=0;j<t->jdnum;j++)
		{
			if(i==j)
			{
				t->a[i][j]=0;
			}
			else
			{t->a[i][j]=INF;}
		}
	}
	cout<<"请输入各个边数信息："<<endl;
	for(int i=0;i<t->bnum;i++)
	{
		char m,n;
		int len;
		int x=0,y=0;
		cin>>m;cin>>n;cin>>len;
		x=getplace(t,m);
		y=getplace(t,n);
		t->a[x][y]=t->a[y][x]=len;
	}
	fprintf(fp,"%d\n",t->jdnum);
	for(int i=0;i<t->jdnum;i++)
	{
		fprintf(fp,"%c\t",t->no[i].num);
		fprintf(fp,"%s\t",t->no[i].name);
	}
	fprintf(fp,"\n");
	fprintf(fp,"%d\n",t->bnum);
	for(int i=0;i<t->jdnum;i++)
	{
		for(int j=0;j<t->jdnum;j++)
		{
			fprintf(fp,"%d\t",t->a[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	cout<<endl<<"已完成校园平面图的构造，请关闭调试界面，继续操作";
}
void fetchtu(graph *t)//读取文件中图信息，并将其赋给图t
{
	FILE *fp;
	fp=fopen("tu","r");
	char m;
	if(fp==NULL)
	{
		cout<<"未找到校园平面图，无法进行导航，请先输入校园平面图";
		creat(t);
		cout<<"已完成图的构造，请继续进行操作"<<endl;
		fetchtu(t);
	}
	fscanf(fp,"%d",&t->jdnum);
	fscanf(fp,"%c",&m);
	for(int i=0;i<t->jdnum;i++)
	{
		fscanf(fp,"%c",&t->no[i].num);
		fscanf(fp,"%c",&m);
		fscanf(fp,"%s",t->no[i].name);
		fscanf(fp,"%c",&m);
	}
	fscanf(fp,"%d",&t->bnum);
	fscanf(fp,"%c",&m);
	for(int i=0;i<t->jdnum;i++)
	{
		for(int j=0;j<t->jdnum;j++)
		{
			fscanf(fp,"%d",&t->a[i][j]);
			fscanf(fp,"%c",&m);
		}
		fscanf(fp,"%c",&m);
	}
}
void FLY(graph *t,int p[20][20],int d[20][20])//弗洛伊德算法
{
	int i,j,k;
	for(i=0;i<t->jdnum;i++)
	{
		for(j=0;j<t->jdnum;j++)
		{
			d[i][j]=t->a[i][j];
			p[i][j]=j;
		}
	}
	for(k=0;k<t->jdnum;k++)
	{
		for(i=0;i<t->jdnum;i++)
		{
			for(j=0;j<t->jdnum;j++)
			{
				if(d[i][j]>(d[i][k]+d[k][j]))
				{
					d[i][j]=d[i][k]+d[k][j];
					p[i][j]=k;
				}
			}
		}
	}
}
void print(graph *t,int x,int y)//输出函数
{
	int z;
	int p[20][20],d[20][20];
	FLY(t,p,d);
	cout<<t->no[x].name<<"到"<<t->no[y].name<<"的最短距离为："<<d[x][y]<<"米"<<endl;
	cout<<"最短路径为："<<t->no[x].name;
	z=p[x][y];
	while(z!=y)
	{
		cout<<"->"<<t->no[z].name;
		z=p[z][y];
	}
	cout<<"->"<<t->no[y].name<<endl;
	//tu1(t);//显示文件内信息
	//tu2(t,d);//显示所有路径及其距离
}
void shortway(graph *t)//输出最短路径
{
	fetchtu(t);
	char start,end;
	int x,y;
	int p[20][20],d[20][20];
	cout<<endl<<"校园地点所对应的编号为："<<endl;
	for(int i=0;i<t->jdnum/2;i++)
	{
		cout<<t->no[i].num<<":"<<t->no[i].name<<" ";
	}
	cout<<endl;
	for(int i=t->jdnum/2;i<t->jdnum;i++)
	{
		cout<<t->no[i].num<<":"<<t->no[i].name<<" ";
	}
	cout<<endl;
	cout<<"请输入两地点所对应的编号，中间用空格隔开："<<endl;
	cin>>start>>end;
	int n=0;
	int m=0;
	for(int i=0;i<t->jdnum;i++)
	{
		if(start==t->no[i].num)
		{n=1;}
		if(end==t->no[i].num)
		{m=1;}
	}
	if(n==0||m==0)
	{
		cout<<"输入错误，请重新输入"<<endl;
		cin>>start>>end;
	}
	x=getplace(t,start);
	y=getplace(t,end);
	print(t,x,y);
}
void operate(graph *t)//操作界面
{
	cout<<"校园导航系统"<<endl;
	cout<<"1:输入校园平面图"<<endl;
	cout<<"2:查询两地最短路径"<<endl;
	cout<<"3:退出程序"<<endl;
	cout<<"请输入要操作的编号:";
	int n;
	cin>>n;
	while(n>3||n<=0)
	{
		cout<<"输入编号错误，请重新输入：";
		cin>>n;
	}
	switch(n)
	{
	case 1:creat(t);break;
	case 2:shortway(t);break;
	case 3:exit(0);break;
	}
}
int main()
{
	graph *t;
	t=new graph;
	operate(t);
	return 0;
}
/*
18
A 艺术馆 B 体育馆 C 游泳馆 D 北足 E 北寝室 F 北食堂 G 机械馆 H 图书馆 I 蓝天剧场
J 工训楼 K 逸夫馆 L 经管楼 M 行政楼 N 教学楼 O 南足 P 南食堂 Q 校医院 R 南寝室
26
A B 150
A G 80
A H 100
B C 100
B H 150
C D 100
C I 300
D I 150
D E 130
E F 50
E I 200
G H 150
G J 100
H I 300
H N 270
I P 400
I Q 450
J K 75
K L 100
L M 200
M N 150
N O 300
O P 200
O R 150
P R 80
P Q 100
*/