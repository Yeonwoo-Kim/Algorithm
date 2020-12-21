#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 100
#define INF 100000
#define TRUE 1
#define FALSE 0

//adj�� ����ü AdjType
typedef struct
{
	int start, end, weight; //���� ����,�� ����,����ġ

}AdjType;

typedef struct
{
	int n, m; //��� ����,������ ����
	AdjType adj[SIZE]; //������ �����ϱ� ���� �迭

}GraphType;


int k = 0;

//�׷��� ����
void make_adj(GraphType* g, int start, int end, int weight)
{

	g->adj[k].start = start;
	g->adj[k].end = end;
	g->adj[k].weight = weight;
	k++;
}

int parent[SIZE];


void init_parent(int m) //parent �迭 �ʱ�ȭ (�ڱ��ڽ� ����)
{
	for (int i = 0; i < m; i++)
	{
		parent[i] = i;
	}
}

int getParent(int x)
{
	if (parent[x] == x) //�θ�� �ڽ��̶� ������ return(��������)
	{
		return x;
	}
	else //�ڽ��� ���� ����Ű�� �ִ� �θ����� ���� �ڽŰ� �ٸ��ٸ� ���� �θ� ã��
	{
		return parent[x] = getParent(parent[x]);
	}
}

void unionParent(int a, int b) //���� ã�� �θ�� �־��� (���߿� �����ָ� �θ��)
{
	a = getParent(a);
	b = getParent(b);

	if (a < b)
	{
		parent[b] = a;
	}
	else
	{
		parent[a] = b;
	}
}

int compare(const void* a, const void* b)
{
	AdjType* x = (AdjType*)a;
	AdjType* y = (AdjType*)b;
	return (x->weight - y->weight);
}

void kruskal(GraphType* g)
{
	AdjType str;

	int edge_accepted = 0;
	int a, b;
	int sum = 0;

	//����
	qsort(g->adj, g->m, sizeof(AdjType), compare);

	//union-parent�� parent �迭 �ʱ�ȭ
	init_parent(g->m); 
	
	int i = 0;

	while (edge_accepted < g->n-1) //���õ� ������ ���� �׷����� ���-1 ���� ���� ����
	{
		str = g->adj[i];

		a = getParent(str.start);
		b = getParent(str.end);

		if (a != b) //�ٸ� �θ� ������.. => ����Ŭ�� ���� �ȵǸ�
		{

			printf(" %d", str.weight);
			sum += str.weight;
			edge_accepted++;
			unionParent(a, b); //���ο� �θ�� ����
		}
		i++;
	}

	printf("\n");
	printf("%d", sum);
}

void main()
{
	GraphType g;

	int i, j, a, b, w;

	scanf("%d %d", &g.n, &g.m);


	//adj �ʱ�ȭ
	for (i = 0; i < g.m; i++)
	{
		g.adj[i].start = 0;
		g.adj[i].end = 0;
		g.adj[i].weight = INF;
	}

	for (i = 0; i < g.m; i++)
	{
		scanf("%d %d %d", &a, &b, &w);

		make_adj(&g, a, b, w);
	}

	kruskal(&g);

}