#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> 
#define MAX_VERTEX_NUM 20	//�������� 
typedef char VertexType;
typedef int VRType;
typedef int InfoType;	//ͼ�б��ϵ�Ȩֵ��Ϣ 
typedef int QElemType;	//�����н���������� 

/* ͼ��������ȱ����͹�����ȱ��� */
//�ڽӱ�洢ͼ
typedef struct ArcNode {
	int adjvex;					//�û���ָ��Ľ���λ�� 
	struct ArcNode* nextarc;	//ָ����һ������ָ�� 
	InfoType* info;				//�û���ص���Ϣ��ָ�룬��Ȩֵ 
}ArcNode;

typedef struct VNode {
	VertexType data;	//�����Ϣ 
	ArcNode* firstarc;	//ָ���һ�������ڸý��Ļ�ָ�� 
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;	//������ͻ��� 
}ALGraph;

//�������ڹ�����ȱ����Ķ���
typedef struct QNode {
	QElemType data;
	struct QNode* qnext;
}QNode, * PQNode;

typedef struct Queue {
	PQNode front;
	PQNode rear;
}Queue, * PQueue;

bool visited[MAX_VERTEX_NUM];  //��ǽ���Ƿ񱻱���������Ϊflase,��Ϊtrue;

PQueue initQueue();	//��ʼ��һ���ն��� 
void enQueue(PQueue pqueue, QElemType data);	//��β���
bool isEmpty(PQueue pqueue);	//�ж϶����Ƿ�Ϊ��
QElemType deQueue(PQueue pqueue);	//��ͷ���� 
int locateVex(ALGraph alg, char v);	//ȷ��ͼ�н��λ�ñ��
void createALGraph(ALGraph* alg);	//��������ͼ 
void DFS(ALGraph alg, int v);	//������ȱ�������ͼ
void BFSTraverse(ALGraph alg);	//������ȱ���
void DFSTraverse(ALGraph alg);	//���ڽӱ�洢������ͼ����������ȱ���

/*
��������
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
���Խ��
1 2 4 8 5 6 3 7
1 2 3 4 5 6 7 8
*/

int main() {
	ALGraph alg;
	createALGraph(&alg);   //��������ͼ 
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
		printf("����ͷ�ռ�����ʧ�ܣ�\n");
		exit(-1);
	}
	pqueue->front = pqueue->rear = pqnode;
	pqnode->qnext = NULL;
	return pqueue;
}

void enQueue(PQueue pqueue, QElemType data) {
	PQNode pqnode = (PQNode)malloc(sizeof(QNode));
	if (pqnode == NULL) {
		printf("���н������ʧ�ܣ�\n");
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
		printf("����Ϊ��\n");
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
	printf("����������������ͼ�Ľ�����ͱ���(�ÿո����):");
	scanf("%d %d", &(*alg).vexnum, &(*alg).arcnum);
	getchar();
	for (i = 0; i < (*alg).vexnum; i++) {
		printf("�����%d���������:", i+1);
		scanf("%c", &(*alg).vertices[i].data);
		(*alg).vertices[i].firstarc = NULL;
		getchar();
	}
	char v1, v2;
	ArcNode* s, * p;
	for (k = 0; k < (*alg).arcnum; k++) {
		printf("�����%d���ߵ�����������ƣ�", k+1);
		scanf("%c %c", &v1, &v2);
		i = locateVex((*alg), v1);
		j = locateVex((*alg), v2);
		//����������ͼ���һ������Ҫ����������� 
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
	//�ӵ�v���������ݹ��������ȱ���ͼalg
	ArcNode* p;
	visited[v] = true;
	printf("%c ", alg.vertices[v].data);
	for (p = alg.vertices[v].firstarc; p != NULL; p = p->nextarc) {
		if (!visited[p->adjvex])
			DFS(alg, p->adjvex);
	}
}

void DFSTraverse(ALGraph alg) {
	printf("������ȱ������У�");
	int v;
	for (v = 0; v < alg.vexnum; v++)
		visited[v] = false;
	for (v = 0; v < alg.vexnum; v++) {
		if (!visited[v])
			DFS(alg, v);
	}
}

void BFSTraverse(ALGraph alg) {
	printf("������ȱ������У�");
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
