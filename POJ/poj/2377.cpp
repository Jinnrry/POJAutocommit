#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define	VCount	1000//������Ŀ
#define	ECount	20000//�ߵ���Ŀ	
int rank[ECount];//��ֵ����ĸ�������,��¼�����ߵ��±�
int parent[VCount];
struct Edge{
	int a;
	int b;
	int weigh;
}edge[ECount];
int cmp(const void *a, const void *b)
{
	int x,y;
	x=*(int *)a;
	y=*(int *)b;
	if (edge[x].weigh<edge[y].weigh)
		return 1;
	else if (edge[x].weigh>edge[y].weigh)
		return -1;
	else return 0;
}
int root(int i){
	int r,p;
	for (r=i;parent[r]>=0;r=parent[r]);
	while (i!=r){
		p=i;
		i=parent[i];
		parent[p]=r;
	}	
	return r;
}
bool merge(int i,int j)//����֮ǰ�Ƿ�����ͬһ����
{
	i=root(i);
	j=root(j);
	if (i==j) return true;
	if (parent[i]<parent[j]){
		parent[i]+=parent[j];
		parent[j]=i;
		return false;
	}
	else {
		parent[j]+=parent[i];
		parent[i]=j;
		return false;
	}
}
int kruskal(int v,int e)
{
	int result=0;
	int count,i;
	memset(parent,-1,sizeof(parent));//���鼯Ԥ����,���Ƚ�ÿ��Ԫ�ؿ���һ�������ļ���
	qsort(rank,e,sizeof(rank[0]),cmp);//����ֵ����,����Ϊ��С������,����Ϊ���������
	for (i=0,count=1;count<v && i<e;i++)
	{
		if (merge(edge[rank[i]].a,edge[rank[i]].b)==false)
		{
			//˵��֮ǰ���㲻��ͬһ����ͨ������,����Ҫ��
			//���ñ�ͳ������,���ϲ���������������ͨ����Ϊһ����ͨ����
			result+=edge[rank[i]].weigh;
			count++;
		}
	}
	if (count!=v)
		return -1;//�Ҳ�����С������,ע������Լ��-1��ʾ����ʧ��
	return result;
}
int main()
{
	int a,b,i,n,m;
	scanf("%d%d",&n,&m);
	for (i=0;i<m;i++)
	{
		scanf("%d%d%d",&a,&b,&edge[i].weigh);
		rank[i]=i;
		edge[i].a=a-1;
		edge[i].b=b-1;
	}
	printf("%d\n",kruskal(n,m));
	return 0;
}