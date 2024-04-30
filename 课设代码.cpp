#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
#define INF 10000;
typedef struct node//���
{
	char num;//�����
	char name[20];//�������
}node;
typedef struct graph//ͼ
{
	node no[20];//ͼ�а����Ľ��
	int a[20][20];//ֱ��·������
	int jdnum,bnum;//�����������
}graph;
int getplace(graph *t,char x)//�õ����Ϊx���������±�
{
	for(int i=0;i<t->jdnum;i++)
	{
		if(t->no[i].num==x)
		{return i;}
	}
	cout<<"error";
	return -1;
}
void tu1(graph *t)//��ʾ�ļ�����Ϣ
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
void tu2(graph *t,int d[20][20])//��ʾ����·���������
{
	int n=0;
	for(int i=0;i<t->jdnum;i++)
	{
		for(int j=i;j<t->jdnum;j++)
		{
			cout<<t->no[i].name<<"->"<<t->no[j].name<<"  ����Ϊ��"<<d[i][j]<<"         ";
			n++;
			if(n%3==0)
			{cout<<endl;}
		}
	}
}
void creat(graph *t)//����һ��ͼ�����������ļ��洢
{
	FILE *fp;
	fp=fopen("tu","w");
	cout<<"����У԰ƽ��ͼ"<<endl;
	cout<<"�������ܽ������";
	cin>>t->jdnum;
	cout<<"���������ż����ƣ�"<<endl;
	for(int i=0;i<t->jdnum;i++)
	{
		cin>>t->no[i].num;
		cin>>t->no[i].name;
	}
	cout<<"�����������";
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
	cout<<"���������������Ϣ��"<<endl;
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
	cout<<endl<<"�����У԰ƽ��ͼ�Ĺ��죬��رյ��Խ��棬��������";
}
void fetchtu(graph *t)//��ȡ�ļ���ͼ��Ϣ�������丳��ͼt
{
	FILE *fp;
	fp=fopen("tu","r");
	char m;
	if(fp==NULL)
	{
		cout<<"δ�ҵ�У԰ƽ��ͼ���޷����е�������������У԰ƽ��ͼ";
		creat(t);
		cout<<"�����ͼ�Ĺ��죬��������в���"<<endl;
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
void FLY(graph *t,int p[20][20],int d[20][20])//���������㷨
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
void print(graph *t,int x,int y)//�������
{
	int z;
	int p[20][20],d[20][20];
	FLY(t,p,d);
	cout<<t->no[x].name<<"��"<<t->no[y].name<<"����̾���Ϊ��"<<d[x][y]<<"��"<<endl;
	cout<<"���·��Ϊ��"<<t->no[x].name;
	z=p[x][y];
	while(z!=y)
	{
		cout<<"->"<<t->no[z].name;
		z=p[z][y];
	}
	cout<<"->"<<t->no[y].name<<endl;
	//tu1(t);//��ʾ�ļ�����Ϣ
	//tu2(t,d);//��ʾ����·���������
}
void shortway(graph *t)//������·��
{
	fetchtu(t);
	char start,end;
	int x,y;
	int p[20][20],d[20][20];
	cout<<endl<<"У԰�ص�����Ӧ�ı��Ϊ��"<<endl;
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
	cout<<"���������ص�����Ӧ�ı�ţ��м��ÿո������"<<endl;
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
		cout<<"�����������������"<<endl;
		cin>>start>>end;
	}
	x=getplace(t,start);
	y=getplace(t,end);
	print(t,x,y);
}
void operate(graph *t)//��������
{
	cout<<"У԰����ϵͳ"<<endl;
	cout<<"1:����У԰ƽ��ͼ"<<endl;
	cout<<"2:��ѯ�������·��"<<endl;
	cout<<"3:�˳�����"<<endl;
	cout<<"������Ҫ�����ı��:";
	int n;
	cin>>n;
	while(n>3||n<=0)
	{
		cout<<"�����Ŵ������������룺";
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
A ������ B ������ C ��Ӿ�� D ���� E ������ F ��ʳ�� G ��е�� H ͼ��� I ����糡
J ��ѵ¥ K �ݷ�� L ����¥ M ����¥ N ��ѧ¥ O ���� P ��ʳ�� Q УҽԺ R ������
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