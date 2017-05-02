#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000
typedef struct edge{
	int adjvex;//�ߵ��յ�
	struct edge *next;//ָ����һ���߽��
}*ELink;
ELink G[MAX];
int n,m;
bool flag[MAX];
__int64 cd,min;
__int64 num[MAX];
void ADJLIST(int e);//��n����e���ߵ�ͼ�����ڽӱ�洢�ṹ
__int64 dfs(int node);
__int64 abs(__int64 a,__int64 b);
int main()
{
	int t=1,i;
	scanf("%d%d",&n,&m);
	while (n!=0 || m!=0)
	{
		memset(G,NULL,sizeof(G));
		memset(flag,false,sizeof(flag));
		for (i=0;i<n;i++)
			scanf("%I64d",&num[i]);
		ADJLIST(m);
		dfs(0);
		min=99999999999999I64;
		for (i=1;i<n;i++)
			if ((cd=abs(num[i],num[0]-num[i]))<min)
				min=cd;
		printf("Case %d: %I64d\n",t++,min);
		scanf("%d%d",&n,&m);
	}
	return 0;
}
void ADJLIST(int e)
{
	int k,vi,vj;
	ELink p;
	for (k=0;k<e;k++)
	{
		scanf("%d%d",&vi,&vj);//���붥��ż��,ʼ����ǰ���յ��ں�
		vi--;
		vj--;
		p=(ELink)malloc(sizeof(edge));
		p->adjvex=vj;
		p->next=G[vi];
		G[vi]=p;
		p=(ELink)malloc(sizeof(edge));
		p->adjvex=vi;
		p->next=G[vj];
		G[vj]=p;
	}
}
__int64 dfs(int node)
{
	ELink p=G[node];
	flag[node]=true;
	while (p!=NULL)
	{
		if (flag[p->adjvex]==false)
			num[node]+=dfs(p->adjvex);
		p=p->next;
	}
	return num[node];
}
__int64 abs(__int64 a,__int64 b)
{
	if (a>b)
		return a-b;
	else return b-a;
}
