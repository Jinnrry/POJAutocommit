#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1001
typedef struct edge{
	int adjvex;//�ߵ��յ�
	struct edge *next;//ָ����һ���߽��
}*ELink;
ELink G[MAX]={NULL};
int n,m,k;
int cow[100];
bool picnic[MAX],flag[MAX];
void OR(int p)
{
	int i;
	for (i=1;i<=n;i++)
	{
		if (flag[i]==false)
			picnic[i]=false;
	}
}
void DFS(int point)
{
	int q;
	ELink p=G[point];
	flag[point]=true;
	while (p!=NULL)
	{
		q=p->adjvex;
		if (flag[q]==false)
			DFS(q);
		p=p->next;
	}
}
int main()
{
	int a,b,i,sum;
	ELink p;
	scanf("%d%d%d",&k,&n,&m);
	for (i=0;i<k;i++)
		scanf("%d",&cow[i]);
	for (i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		p=(ELink)malloc(sizeof(edge));
		p->adjvex=b;
		p->next=G[a];
		G[a]=p;
	}
	memset(picnic,true,sizeof(picnic));
	for (i=0;i<k;i++)
	{
		memset(flag,false,sizeof(flag));
		DFS(cow[i]);
		OR(cow[i]);
	}
	for (i=1,sum=0;i<=n;i++)
	{
		if (picnic[i]==true)
			sum++;
	}
	printf("%d\n",sum);
}

//С�᣺ϡ��ͼ���ڽӱ�洢Ҫ���ڽӾ���Ҫ��Ķ࣬��800MS������45MS