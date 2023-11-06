#include <iostream>
#include <queue>
using namespace std;

struct node
{
	int data;
	node * lchild;
	node * rchild;
};

node* newNode(int v) { 
	node*Node = new node; //����һ��node���ͱ����ĵ�ַ�ռ�
	Node->data = v; //���ȨֵΪv
	Node->lchild = Node->rchild = NULL; //��ʼ״̬�������Һ���
	return Node; //�����½ڵ�ĵ�ַ
}

void search(node*root,int x, int newdata){
	if (root == NULL) return; //����Ϊ�սڵ�Ŀ�����
	if (root->data == x) {
		root->data = newdata; //�ҵ�������Ϊx�Ľ�㣬�����޸�Ϊnewdata
	}
	search(root->lchild, x, newdata);//������������
	search(root->rchild, x, newdata);//������������
}

void insert(node*& root, int x) {
	if (root == NULL) { //������������ʧ�ܣ������㣨�ݹ�߽磩
		root = newNode(x);
		return;
	}
	if (root->data > x) { //������������
		insert(root->lchild, x);
	}
	else insert(root->rchild, x); //������������
}

node*create(int data[], int n) {
	node* root = NULL;     //�½��ո����
	for (int i = 0; i < n; i++) {
		insert(root, data[i]); //��data[0]��data[n-1]���������
	}
	return root; //���ظ��ڵ�
}

void preorder(node*root) { //�������
	if (root == NULL) return; //������������ݹ�߽�
	cout << root->data << endl;; //���ʸ��ڵ�������
	preorder(root->lchild); //����������
	preorder(root->rchild); //����������
}

void inorder(node*root) { //�������
	if (root == NULL) return; //������������ݹ�߽�
	inorder(root->lchild); //����������
	cout << root->data << endl;; //���ʸ��ڵ�������
	inorder(root->rchild); //����������
}
void postorder(node* root) { //�������
	if (root == NULL) return; //������������ݹ�߽�
	preorder(root->lchild); //����������
	preorder(root->rchild); //����������
	cout << root->data << endl;; //���ʸ��ڵ�������
}

void LayerOrder(node* root) { //�������
	queue<node*> q; //�����������ǵ�ַ �ǵõ���ͷ�ļ�<quene>
	q.push(root);  //�����ڵ����
	while (!q.empty())  //�˳�����Ϊ����Ϊ��
	{
		node* now = q.front(); //ȡ������Ԫ��
		cout << now->data << endl;
		q.pop();        //��������Ԫ��
		if (now->lchild != NULL) q.push(now->lchild);//�������ǿ���ѹ�����
		if (now->rchild != NULL) q.push(now->rchild);//�������ǿ���ѹ�����
	}
}
int main() {
	int n = 10;
	int nums[10] = { 5,3,8,2,4,1,6,7,9,0 };
	node* root = create(nums, 10);
	//search(root, 7, 11); //�����滻
	preorder(root);//ǰ�����
	//inorder(root);    //�������
	//postorder(root);  //�������
	//LayerOrder(root);  //�������
	return 0;
}


