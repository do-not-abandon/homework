#include <iostream>
#include <string>
#include <vector>
#define MaxVertexNum  100   //�����Ŀ���ֵ
#define maxSize 20			//�������ֵ
typedef char VertexType;	//������������
typedef int EdgeType;		//��Ȩͼ�б���Ȩֵ����������

//����
struct Queue
{
	int data[maxSize];
	int front, rear;
};

struct MGraph
{
	VertexType Vex[MaxVertexNum];   //����
	EdgeType Edge[MaxVertexNum][MaxVertexNum];  //�ڽӾ��󣬱߱�
	int vexnum, edgenum;    //ͼ�Ľ�����ͻ���
};

int visitDFS[maxSize];//�жϽ���Ƿ񱻷���
int visitBFS[maxSize];
void create_Graph(MGraph* G);	//��������ͼ
void InitQueue(Queue* Q);	//��ʼ������
int IsEmpty(Queue* Q);	//�ж϶ӿ�
void EnQueue(Queue* Q, int e);	//���
void DeQueue(Queue* Q, int* e);	//����
void DFS(MGraph G, int i);	//������ȱ���
void DFSTraverse(MGraph G);	//������ȱ���
void BFS(MGraph G);	//������ȱ���

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
	int start, end;  //�ߵ������š��յ����
	int numV, numE;
	int w;   //���ϵ�Ȩֵ
	cout<<"����������������ͼ�Ľ�����ͱ���(�ÿո����):";
    cin>>numV>>numE;
	G->vexnum = numV;
	G->edgenum = numE;
	//ͼ�ĳ�ʼ��
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			if (i == j) G->Edge[i][j] = 0;
			else G->Edge[i][j] = 32767;
		}
	}

	//�����Ϣ�������
	for (i = 0; i < G->vexnum; i++) {
		cout<<"�����"<<i+1<<"���������:";
		cin>>G->Vex[i];
	}
	cout<<endl;
	//��������ͼ�ߵ���Ϣ
	for (i = 0; i < G->edgenum; i++) {
		cout<<"������ߵ������ţ��յ���ţ�Ȩֵ(�ÿո����)��";
		cin>>start, end, w;
		G->Edge[start - 1][end - 1] = w;
		G->Edge[end - 1][start - 1] = w;   //����ͼ���жԳ���
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
	cout<<"\n������ȱ������У�";
	for (i = 0; i < G.vexnum; i++) visitDFS[i] = 0;
	for (i = 0; i < G.vexnum; i++) {
		if (!visitDFS[i]) DFS(G, i);
	}
}

void BFS(MGraph G) {
	int i, j;
	Queue Q;
	cout<<"\n������ȱ������У�";
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
