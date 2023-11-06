#include <iostream>
#include <string>
#include <vector>
#define MaxVertexNum  100   //结点数目最大值
#define maxSize 20			//队列最大值
typedef char VertexType;	//结点的数据类型
typedef int EdgeType;		//带权图中边上权值的数据类型

//队列
struct Queue
{
	int data[maxSize];
	int front, rear;
};

struct MGraph
{
	VertexType Vex[MaxVertexNum];   //结点表
	EdgeType Edge[MaxVertexNum][MaxVertexNum];  //邻接矩阵，边表
	int vexnum, edgenum;    //图的结点数和弧数
};

int visitDFS[maxSize];//判断结点是否被访问
int visitBFS[maxSize];
void create_Graph(MGraph* G);	//创建无向图
void InitQueue(Queue* Q);	//初始化队列
int IsEmpty(Queue* Q);	//判断队空
void EnQueue(Queue* Q, int e);	//入队
void DeQueue(Queue* Q, int* e);	//出队
void DFS(MGraph G, int i);	//深度优先遍历
void DFSTraverse(MGraph G);	//深度优先遍历
void BFS(MGraph G);	//广度优先遍历

using namespace std;

int main(){
	MGraph G;
	create_Graph(&G);
	DFSTraverse(G);
	BFS(G);
	cout<<endl;
}

void create_Graph(MGraph* G) {
	int i, j;
	int start, end;  //边的起点序号、终点序号
	int numV, numE;
	int w;   //边上的权值
	cout<<"请输入所创建无向图的结点数和边数(用空格隔开):";
    cin>>numV>>numE;
	G->vexnum = numV;
	G->edgenum = numE;
	//图的初始化
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			if (i == j) G->Edge[i][j] = 0;
			else G->Edge[i][j] = 32767;
		}
	}

	//结点信息存入结点表
	for (i = 0; i < G->vexnum; i++) {
		cout<<"输入第"<<i+1<<"个结点名称:";
		cin>>G->Vex[i];
	}
	cout<<endl;
	//输入无向图边的信息
	for (i = 0; i < G->edgenum; i++) {
		cout<<"请输入边的起点序号，终点序号，权值(用空格隔开)：";
		cin>>start, end, w;
		G->Edge[start - 1][end - 1] = w;
		G->Edge[end - 1][start - 1] = w;   //无向图具有对称性
	}
}

void InitQueue(Queue* Q) {
	Q->front = Q->rear = 0;
}

int IsEmpty(Queue* Q) {
	if (Q->front == Q->rear) return 1;
	else return 0;
}

void EnQueue(Queue* Q, int e) {
	if ((Q->rear + 1) % maxSize == Q->front) return;
	else {
		Q->data[Q->rear] = e;
		Q->rear = (Q->rear + 1) % maxSize;
	}
}

void DeQueue(Queue* Q, int* e) {
	if (Q->rear == Q->front) return;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % maxSize;
}

void DFS(MGraph G, int i) {
	int j;
	visitDFS[i] = 1;
	cout<<G.Vex[i];
	for (j = 0; j < G.vexnum; j++) {
		if (G.Edge[i][j] != 32767 && !visitDFS[j]) DFS(G, j);
	}
}

void DFSTraverse(MGraph G) {
	int i;
	cout<<"\n深度优先遍历序列：";
	for (i = 0; i < G.vexnum; i++) visitDFS[i] = 0;
	for (i = 0; i < G.vexnum; i++) {
		if (!visitDFS[i]) DFS(G, i);
	}
}

void BFS(MGraph G) {
	int i, j;
	Queue Q;
	cout<<"\n广度优先遍历序列：";
	for (i = 0; i < G.vexnum; i++) visitBFS[maxSize] = 0;
	InitQueue(&Q);
	for (i = 0; i < G.vexnum; i++) {
		if (!visitBFS[i]) {
			visitBFS[i] = 1;
			cout<<G.Vex[i];
			EnQueue(&Q, i);

			while (!IsEmpty(&Q)) {
				DeQueue(&Q, &i);
				for (j = 0; j < G.vexnum; j++) {
					if (!visitBFS[j] && G.Edge[i][j] != 32767) {
						visitBFS[j] = 1;
						cout<<G.Vex[j];
						EnQueue(&Q, j);
					}
				}
			}
		}
	}
}
