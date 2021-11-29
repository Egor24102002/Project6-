using namespace std;
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define HEADER ("Лабораторная работа №6\nВыполнил:Пантюшов Е.\n\n")
#include <queue>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
using namespace std;
struct node
{
	int vertex;
	struct node* next;
};

struct Graph
{
	int numVertices;
	struct node** adjList;
};

struct node* createNode(int v)
{
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices)
{
	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;
	graph->adjList = (node**)malloc(vertices * sizeof(struct node*));
	for (int i = 0; i < vertices; i++)
		graph->adjList[i] = NULL;
	return graph;
}

void addEdge(struct Graph* graph, int i, int j)
{
	struct node* newNode = createNode(j);
	if (graph->adjList[i] == NULL)
	{
		graph->adjList[i] = newNode;
		newNode = NULL;
	}
	struct node* temp = graph->adjList[i];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;

	newNode = createNode(i);
	if (graph->adjList[j] == NULL)
	{
		graph->adjList[j] = newNode;
		newNode = NULL;
	}
	temp = graph->adjList[j];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

void printGraph(struct Graph* graph)
{
	for (int i = 0; i < graph->numVertices; i++)
	{
		struct node* temp = graph->adjList[i];
		printf("%d-я вершина: ", i);
		while (temp)
		{
			printf("%d ", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}
void bfs(int** G, int* DIST, int v, int n)
{
	queue <int> q;
	q.push(v);
	DIST[v] = 0;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		printf(" %d ", v);
		for (int i = 0; i < n; i++)
		{
			if ((G[v][i] == 1) && (DIST[i] == -1))
			{
				q.push(i);
				DIST[i] = 1+DIST[v];
			}
		}
	}
}
void dfs(int** G, int* DIST, int v, int a, int n)
{
	int rez = a + 1;
	DIST[v] = a;
	for (int i = 0; i < n; i++)
	{
		if (G[v][i] == 1 && DIST[i] == -1)
			dfs(G, DIST,i,rez,n);
		if (G[v][i] == 1 && a < DIST[i])
			dfs(G, DIST, i, rez, n);
	}
}
void dfs_list(struct Graph* graph, int* DIST, int v, int a, int n)
{
	int rez = a + 1;
	DIST[v] = a;
	struct node* list = graph->adjList[v];
	while(list)
	{
		if (DIST[list->vertex] == -1)
			dfs_list(graph, DIST, list->vertex, rez, n);
		if (a < DIST[list->vertex])
			dfs_list(graph, DIST, list->vertex, rez, n);
		list = list->next;
	}
}
void bfs_list(struct Graph *graph, int* DIST, int v, int n)
{
	queue <int> q;
	q.push(v);
	DIST[v] = 0;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		printf(" %d ", v);
		struct node* list = graph->adjList[v];
		while(list)
		{
			if  (DIST[list->vertex] == -1)
			{
				q.push(list->vertex);
				DIST[list->vertex] = 1 + DIST[v];
			}
			list = list->next;
		}
	}
}

void task_1_1(int** G, int n)
{
	printf("\nЗадание 1.\n\nПункт 1.\nМатрица смежности:\n");
	for (int i = 0; i < n; i++)
	{
		G[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
		{
			G[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				G[i][j] = 0;
			}
			else
			{
				G[i][j] = G[j][i];
			}
			printf(" %d ", G[i][j]);
		}
		printf("\n");
	}
}
void task_1_2(int** G, int n)
{
	int* DIST = (int*)malloc(n * sizeof(int));
	int v;
	for (int i = 0; i < n; i++)
	{
		DIST[i] = -1;
	}
	printf("\nПункт 1.2.\nВведите точку входа: ");
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в ширину(матрица): ");
	bfs(G, DIST, v, n);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		if (DIST[i] == -1)
		{
			DIST[i] = 0;
		}
		printf("Расстояние от %dой вершины до %dой вершины=%d\n", v, i, DIST[i]);
	}
	free(DIST);
}
void task_1_3(int **G,int n,struct Graph *graph)
{
	int v;
	int* DIST = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((G[i][j] == 1) && (i < j))
			{
				addEdge(graph, i, j);
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		DIST[i] = -1;
	}

	printf("\n\nПункт 3.\nСписок смежности: \n");
	printGraph(graph);
	printf("Введите точку входа: ");
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в ширину(список): ");
	bfs_list(graph, DIST, v, n);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		if (DIST[i] == -1)
		{
			DIST[i] = 0;
		}
		printf("Расстояние от %dой вершины до %dой вершины(список)=%d\n", v, i, DIST[i]);
	}
	free(DIST);
}
void task_2_1(int** G, int n)
{
	int* DIST = (int*)malloc(n * sizeof(int));
	int v = 0;
	int a = 0;
	for (int i = 0; i < n; i++)
	{
		DIST[i] = -1;
	}
	printf("\nПункт 2.1.\nВведите точку входа: ");
	scanf("%d", &v);
	dfs(G, DIST, v, a, n);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		if (DIST[i] == -1)
		{
			DIST[i] = 0;
		}
		printf("Расстояние от %dой вершины до %dой вершины=%d\n", v, i, DIST[i]);
	}
	free(DIST);
}
void task_2_2(int** G, int n, struct Graph* graph)
{
	int* DIST = (int*)malloc(n * sizeof(int));
	int v = 0;
	int a = 0;
	for (int i = 0; i < n; i++)
	{
		DIST[i] = -1;
	}
	printf("\nПункт 2.2.\nВведите точку входа: ");
	scanf("%d", &v);
	dfs_list(graph, DIST, v,a, n);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		if (DIST[i] == -1)
		{
			DIST[i] = 0;
		}
		printf("Расстояние от %dой вершины до %dой вершины(список)=%d\n", v, i, DIST[i]);
	}
	free(DIST);
}
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf(HEADER);
	printf("Введите размерность матрицы: ");
	int n;
	scanf("%d", &n);
	int** G = (int**)malloc(n * sizeof(int*));
	struct Graph* graph = createGraph(n);
	task_1_1(G, n);
	clock_t t1 = clock();
	task_1_2(G, n);
	clock_t t2 = clock();
	float res1 = t2 - t1;
	printf("Время: %f", res1 / 1000);
	task_1_3( G, n,graph);
	clock_t t3 = clock();
	task_2_1(G, n);
	clock_t t4 = clock();
	float res2 = t4 - t3;
	printf("Время: %f", res2 / 1000);
	task_2_2(G, n, graph);
	system("PAUSE");
	return 0;
}
