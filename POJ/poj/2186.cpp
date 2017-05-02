#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxn 10001
typedef struct edge{
	int adjvex;//�ߵ��յ�
	struct edge *next;//ָ����һ���߽��
}*ELink;
ELink G[maxn]={NULL},GT[maxn]={NULL};
bool c[maxn];
bool find[maxn],cow=false;
int n,m,e,q,num=0;	//nΪ������Ŀ,e�Ǳ���,mΪ���ʱ�併����ָ��,q��p�Ķ���ָ��
int a1[maxn],a2[maxn],p[maxn];//c�Ƕ�����ɫ��,a1�����ʱ�併���,a2�Ǹ�����,p��������ǿ��ͨ�����ڶ���
void ADJLIST()
{
	int k,vi,vj;
	ELink P,Q;
	for (k=0;k<e;k++)
	{
		scanf("%d%d",&vi,&vj);//���붥��ż��,ʼ����ǰ���յ��ں�
		P=(ELink)malloc(sizeof(edge));
		P->adjvex=vj;
		P->next=G[vi];
		G[vi]=P;
		Q=(ELink)malloc(sizeof(edge));
		Q->adjvex=vi;
		Q->next=GT[vj];
		GT[vj]=Q;
	}
}
void dfs_visit_first(int u)
{
	ELink P=G[u];
	c[u]=true;
	while (P!=NULL)
	{
		if (c[P->adjvex]==false)
			dfs_visit_first(P->adjvex);
		P=P->next;
	}
	a1[m--]=u;
}
void dfs_visit_second(int u)
{
	ELink P=GT[u];
	c[u]=true;
	while (P!=NULL)
	{
		if (c[P->adjvex]==false)
			dfs_visit_second(P->adjvex);
		P=P->next;
	}
	p[q++]=u;
	find[u]=true;
}
void dfs_first()
{
	int u;
	memset(c,false,sizeof(c));
	m=n;	//m�ĳ�ʼ��
	for (u=1;u<=n;u++)
	{
		if (c[a2[u]]==false)
			dfs_visit_first(a2[u]);
	}
}
void dfs_second()
{
	int u,i;
	ELink P;
	memset(c,false,sizeof(c));
	for (u=1;u<=n;u++)
	{
		if (c[a2[u]]==false)
		{
			q=0;
			memset(find,false,sizeof(find));
			dfs_visit_second(a2[u]);
			for (i=0;i<q;i++)
			{
				P=G[p[i]];
				while (P!=NULL)
				{
					if (find[P->adjvex]==false)
						break;
					P=P->next;
				}
				if (P!=NULL)
					break;
			}
			if (i==q)
			{
				if (cow==false)
				{
					cow=true;
					num+=q;
				}
				else num=0;
			}
		}
	}
}
int main()
{
	int i;
	scanf("%d%d",&n,&e);
	ADJLIST();
	for (i=1;i<=n;i++)
		a2[i]=i;
	dfs_first();
	for (i=1;i<=n;i++)	//֮����Ҫ����һ����������a2,����Ϊ��dfs������a1�е�ֵ��ı�
		a2[i]=a1[i];
	dfs_second();
	printf("%d\n",num);
	return 0;
}
