#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100001 //�����Ŀ
#define MIN -2100000000
typedef struct edge{
	int adjvex;//�ߵ��յ�
	struct edge *next;//ָ����һ���߽��
}*ELink;
ELink G[MAX];
int dp[MAX],weight[MAX],queue[MAX];
bool source[MAX];
int n,m,front;
void ADJLIST(int e);//��n����e���ߵ�ͼ�����ڽӱ�洢�ṹ
void DFS(int point);
void DP();
int main()
{
	int i,max;
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		memset(source,false,sizeof(source));
		memset(G,NULL,sizeof(G));
		for (i=1;i<=n;i++)
		{
			scanf("%d",&weight[i]);
			dp[i]=MIN;
		}
		ADJLIST(m);
		front=n;
		for (i=1;i<=n;i++)
			if (source[i]==false)
				DFS(i);
		DP();
		for (i=1,max=MIN;i<=n;i++)
		{
			if (G[i]==NULL && dp[i]>max)
				max=dp[i];
		}
		printf("%d\n",max);
	}
}
void ADJLIST(int e)
{
	int k,vi,vj;
	ELink p;
	for (k=0;k<e;k++)
	{
		scanf("%d%d",&vi,&vj);//���붥��ż��,ʼ����ǰ,�յ��ں�
		p=(ELink)malloc(sizeof(edge));
		p->adjvex=vj;
		p->next=G[vi];
		G[vi]=p;
	}
}
void DFS(int point)
{
	ELink p=G[point];
	while (p!=NULL)
	{
		if (source[p->adjvex]==false)
			DFS(p->adjvex);
		p=p->next;
	}
	queue[front--]=point;
	source[point]=true;
}
void DP()
{
	int i,q,r;
	ELink p;
	for (i=1;i<=n;i++)
	{
		r=queue[i];
		p=G[r];
		if (dp[r]==MIN)
			dp[r]=weight[r];
		while (p!=NULL)
		{
			q=p->adjvex;
			if (dp[r]+weight[q]>dp[q])
				dp[q]=dp[r]+weight[q];
			p=p->next;
		}
	}
}
