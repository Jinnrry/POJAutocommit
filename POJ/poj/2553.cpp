#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxn 5001	//��󶥵���
typedef struct edge{
	int adjvex;//�ߵ��յ�
	struct edge *next;//ָ����һ���߽��
}*ELink;
ELink G[maxn],GT[maxn];	//�ڽӱ�洢,G��ԭͼ,GT��ת��ͼ
bool c[maxn];	//������ѹ������Ƿ��ѷ���
bool bottom[maxn],find[maxn];	//bottomΪ���ļ���,find�洢ĳ��ǿ��ͨ����
int n,m,e,q;	//nΪ������Ŀ,e�Ǳ���,mΪ���ʱ�併����ָ��,q��p�Ķ���ָ��
int a1[maxn],a2[maxn],p[maxn];//c�Ƕ�����ɫ��,a1�����ʱ�併���,a2�Ǹ�����,p��������ǿ��ͨ�����ڶ���
void ADJLIST()	//��ͼ��ͼ��ת��
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
void gt()	//����ת��
{
	int i;
	ELink P,Q;
	for (i=1;i<=n;i++)
	{
		P=G[i];
		while (P!=NULL)
		{
			Q=(ELink)malloc(sizeof(edge));
			Q->adjvex=i;
			Q->next=GT[P->adjvex];
			GT[P->adjvex]=Q;
			P=P->next;
		}
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
	a1[m--]=u;	//���򱣴����ʱ��
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
	p[q++]=u;	//����ǿ��ͨ�����еĵ�
	find[u]=true;
}
void dfs_first()	//ԭͼ��DFS
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
void dfs_second()	//ת��ͼ��DFS
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
				for (i=0;i<q;i++)
					bottom[p[i]]=true;
			}
		}
	}
}
int main()
{
	int i;
	while (scanf("%d",&n),n!=0)
	{
		scanf("%d",&e);
		memset(G,NULL,sizeof(G));
		memset(GT,NULL,sizeof(GT));
		memset(bottom,false,sizeof(bottom));
		ADJLIST();
		for (i=1;i<=n;i++)
			a2[i]=i;
		dfs_first();
		for (i=1;i<=n;i++)	//֮����Ҫ����һ����������a2,����Ϊ��dfs������a1�е�ֵ��ı�
			a2[i]=a1[i];
		dfs_second();
		for (i=1;i<=n;i++)
			if (bottom[i]==true)
				printf("%d ",i);
		putchar('\n');
	}
	return 0;
}
