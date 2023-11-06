#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> 
#define MAX_VERTEX_NUM 20	//最大结点个数 
typedef char VertexType;
typedef int VRType;
typedef int InfoType;	//图中边上的权值信息 
typedef int QElemType;	//队列中结点数据类型 

/* 图的深度优先遍历和广度优先遍历 */
//邻接表存储图
typedef struct ArcNode {
	int adjvex;					//该弧所指向的结点的位置 
	struct ArcNode* nextarc;	//指向下一条弧的指针 
	InfoType* info;				//该弧相关的信息的指针，如权值 
}ArcNode;

typedef struct VNode {
	VertexType data;	//结点信息 
	ArcNode* firstarc;	//指向第一条依附于该结点的弧指针 
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;	//结点数和弧树 
}ALGraph;

//创建用于广度优先遍历的队列
typedef struct QNode {
	QElemType data;
	struct QNode* qnext;
}QNode, * PQNode;

typedef struct Queue {
	PQNode front;
	PQNode rear;
}Queue, * PQueue;

bool visited[MAX_VERTEX_NUM];  //标记结点是否被遍历过，否为flase,是为true;

PQueue initQueue();	//初始化一个空队列 
void enQueue(PQueue pqueue, QElemType data);	//队尾入队
bool isEmpty(PQueue pqueue);	//判断队列是否为空
QElemType deQueue(PQueue pqueue);	//队头出队 
int locateVex(ALGraph alg, char v);	//确定图中结点位置编号
void createALGraph(ALGraph* alg);	//创建无向图 
void DFS(ALGraph alg, int v);	//深度优先遍历无向图
void BFSTraverse(ALGraph alg);	//广度优先遍历
void DFSTraverse(ALGraph alg);	//对邻接表存储的无向图进行深度优先遍历

/*
测试用例
8 10
1
2
3
4
5
6
7
8
1 2
1 3
2 4
2 5
3 6
3 7
4 8
5 8
6 8
7 8
测试结果
1 2 4 8 5 6 3 7
1 2 3 4 5 6 7 8
*/

int main() {
	ALGraph alg;
	createALGraph(&alg);   //创建无向图 
	DFSTraverse(alg);
	printf("\n");
	BFSTraverse(alg);
	printf("\n");
	return 0;
}

PQueue initQueue() {
	PQueue pqueue = (PQueue)malloc(sizeof(Queue));
	PQNode pqnode = (PQNode)malloc(sizeof(QNode));
	if (pqnode == NULL) {
		printf("队列头空间申请失败！\n");
		exit(-1);
	}
	pqueue->front = pqueue->rear = pqnode;
	pqnode->qnext = NULL;
	return pqueue;
}

void enQueue(PQueue pqueue, QElemType data) {
	PQNode pqnode = (PQNode)malloc(sizeof(QNode));
	if (pqnode == NULL) {
		printf("队列结点申请失败！\n");
		exit(-1);
	}
	pqnode->data = data;
	pqnode->qnext = NULL;
	pqueue->rear->qnext = pqnode;
	pqueue->rear = pqnode;
}

bool isEmpty(PQueue pqueue) {
	if (pqueue->front == pqueue->rear) return true;
	return false;
}

QElemType deQueue(PQueue pqueue) {
	if (isEmpty(pqueue)) {
		printf("队列为空\n");
		exit(-1);
	}
	PQNode pqnode = pqueue->front->qnext;
	pqueue->front->qnext = pqnode->qnext;
	if (pqnode == pqueue->rear) pqueue->rear = pqueue->front;
	QElemType data = pqnode->data;
	free(pqnode);
	return data;
}

int locateVex(ALGraph alg, char v) {
	int i;
	for (i = 0; i < alg.vexnum; i++) {
		if (alg.vertices[i].data == v) return i;
	}
	return -1;
}

void createALGraph(ALGraph* alg) {
	int i, j, v, k;
	printf("请输入所创建无向图的结点数和边数(用空格隔开):");
	scanf("%d %d", &(*alg).vexnum, &(*alg).arcnum);
	getchar();
	for (i = 0; i < (*alg).vexnum; i++) {
		printf("输入第%d个结点名称:", i+1);
		scanf("%c", &(*alg).vertices[i].data);
		(*alg).vertices[i].firstarc = NULL;
		getchar();
	}
	char v1, v2;
	ArcNode* s, * p;
	for (k = 0; k < (*alg).arcnum; k++) {
		printf("输入第%d条边的两个结点名称：", k+1);
		scanf("%c %c", &v1, &v2);
		i = locateVex((*alg), v1);
		j = locateVex((*alg), v2);
		//由于是无向图因此一条边需要关联两个结点 
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextarc = NULL;
		if ((*alg).vertices[i].firstarc == NULL) {
			(*alg).vertices[i].firstarc = p;
		}
		else {
			s = (*alg).vertices[i].firstarc;
			while (s->nextarc != NULL)
				s = s->nextarc;
			s->nextarc = p;
		}

		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		p->nextarc = NULL;
		if ((*alg).vertices[j].firstarc == NULL) (*alg).vertices[j].firstarc = p;
		else {
			s = (*alg).vertices[j].firstarc;
			while (s->nextarc != NULL)
				s = s->nextarc;
			s->nextarc = p;
		}
		getchar();
	}
}

void DFS(ALGraph alg, int v) {
	//从第v个结点出发递归的深度优先遍历图alg
	ArcNode* p;
	visited[v] = true;
	printf("%c ", alg.vertices[v].data);
	for (p = alg.vertices[v].firstarc; p != NULL; p = p->nextarc) {
		if (!visited[p->adjvex])
			DFS(alg, p->adjvex);
	}
}

void DFSTraverse(ALGraph alg) {
	printf("深度优先遍历序列：");
	int v;
	for (v = 0; v < alg.vexnum; v++)
		visited[v] = false;
	for (v = 0; v < alg.vexnum; v++) {
		if (!visited[v])
			DFS(alg, v);
	}
}

void BFSTraverse(ALGraph alg) {
	printf("广度优先遍历序列：");
	PQueue pqueue = initQueue();
	ArcNode* p;
	int i;
	QElemType v;
	for (i = 0; i < alg.vexnum; i++)
		visited[i] = false;
	for (i = 0; i < alg.vexnum; i++) {
		if (!visited[i]) {
			visited[i] = true;
			printf("%c ", alg.vertices[i].data);
			enQueue(pqueue, i);
			while (!isEmpty(pqueue)) {
				v = deQueue(pqueue);
				for (p = alg.vertices[v].firstarc; p != NULL; p = p->nextarc) {
					if (!visited[p->adjvex]) {
						printf("%c ", alg.vertices[p->adjvex].data);
						visited[p->adjvex] = true;
						enQueue(pqueue, p->adjvex);
					}
				}
			}
		}
	}
}
