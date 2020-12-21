#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 100
#define INF 100000
#define TRUE 1
#define FALSE 0



//ť ����ü ����
struct node
{
	int data;
	struct node* prev;
	struct node* next;
};

int size;
struct node* front;
struct node* rear;

//�׷��� ����ü ����
typedef struct
{
	int n, m; //����, ������ ����
	int adj[SIZE][SIZE];

}GraphType;


void make_adj(GraphType* g, int a, int b)
{

	g->adj[a][b] = 1; //����Ǿ�����
	g->adj[b][a] = 1;
}

void enque(int data)
{
	if (size == 0)
	{
		struct node* newnode = (struct node*)malloc(sizeof(struct node));
		newnode->data = data;

		front = newnode;
		rear = newnode;
		newnode->next = NULL;
		newnode->prev = NULL;

		size++;
	}
	else
	{
		struct node* newnode = (struct node*)malloc(sizeof(struct node));
		newnode->data = data;

		rear->next = newnode;
		newnode->prev = rear;

		rear = newnode;
		newnode->next = NULL;

		size++;
	}
}

int deque()
{
	int k;

	if (size == 0)
	{
		printf("error");
		exit(1);
	}
	else if (size == 1)
	{
		k = front->data;
		front = NULL;
		rear = NULL;
		size = 0;

	}
	else
	{
		k = front->data;
		front = front->next;
		front->prev = NULL;
		size--;
	}

	return k;
}

void bfs(GraphType* g, int visited[], int s)
{

	enque(s);
	visited[s] = TRUE;

	while (size != 0) //ť�� ��������
	{
		s = deque();
		printf("%d\n", s + 1);

		for (int i = 0; i < g->n; i++)
		{
			if (g->adj[s][i] == 1 && !visited[i])
			{
				enque(i);
				visited[i] = TRUE;
			}
		}
	}
}
void main()
{
	GraphType g;
	size = 0;
	int visited[SIZE] = { FALSE };

	front = NULL;
	rear = NULL;

	int n, m, s, i, a, b;

	scanf("%d %d %d", &g.n, &g.m, &s);

	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			g.adj[i][j] = 0;
		}
	} //������� �ʱ�ȭ

	for (i = 0; i < g.m; i++)
	{
		scanf("%d %d", &a, &b);
		make_adj(&g, a - 1, b - 1);
	}
	/*
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			printf("%d ", g.adj[i][j]);
		}
		printf("\n");
	}
	*/

	bfs(&g, visited, s - 1);
}