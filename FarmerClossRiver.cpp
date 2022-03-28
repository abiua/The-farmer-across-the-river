#include <stdio.h>
#include <malloc.h>
#include<iostream>
#include <stdlib.h>
#define VertexNum 16
#define MAXV 100
int index = 0;
int isok = 0;
//======================================================================================
typedef struct
// ͼ�Ķ���
{
	int farmer; // ũ��
	int wolf; // ��
	int sheep; //��
	int veget; // �ײ�
} Vertex;
Vertex arr[MAXV];
typedef struct ANode {         	//���Ľ��ṹ����
	int adjvex;              	//�û����յ�λ��
	struct ANode *nextarc; 		//ָ����һ������ָ��
	bool isConnect;
} ArcNode;

typedef struct Vnode {    		//�ڽӱ�ͷ��������
	Vertex data;            	//������Ϣ
	int count;             		//��Ŷ������,ֻ��������������
	ArcNode *firstarc;     		//ָ���һ����
} VNode;

typedef struct {
	VNode  adjlist[MAXV];    //�ڽӱ�
	int n,e;		     //ͼ�ж�����n�ͱ���e
} ALGraph;			//�ڽӱ�����
//======================================================================================

//ÿ����ͷ��ʾÿ��״̬ AΪ�Ƿ������������״̬ A=0���� A=1��������.....�������ܴӳ�ʼ״̬��ĩβ״̬�����з����Ϳ�����
void CreateAdj(ALGraph *&G,bool A[MAXV][MAXV],int n,int e) { //����ͼ���ڽӱ�
	int i,j;
	ArcNode *p1;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	for (i=0; i<n; i++)								//���ڽӱ�������ͷ����ָ�����ó�ֵ
		G->adjlist[i].firstarc=NULL;
	for (i=0; i<n; i++)								//����ڽӾ�����ÿ��Ԫ��
		for (j=n-1; j>=0; j--)
			if (A[i][j]) {		//����һ����
				p1 = (ArcNode *)malloc(sizeof(ArcNode));
				p1->adjvex = j;							//�����±����ɱ��
				p1->isConnect = A[i][j];
//				p1=(ArcNode *)malloc(sizeof(ArcNode));	//����һ�����p
				p1->nextarc = NULL;						//β�巨�洢����
				ArcNode *p;
				p = G->adjlist[i].firstarc;
				if (p == NULL) {
					G->adjlist[i].firstarc = p1;
				} else {
					while (p->nextarc) {
						p = p->nextarc;
					}
					p->nextarc = p1;
				}
			}
	G->n=n;
	G->e=n;
}
//======================================================================================
bool isSafe(int farmer, int wolf, int sheep, int veget)
//��ũ��������һ��ʱ�������������ײ���һ���ǲ���ȫ��
{
	if (farmer != sheep && (wolf == sheep || sheep == veget)) {
		return false;
	} else {
		return true; // ��ȫ����true
	}
}

void mAll() {
	int i = 0;
	printf("�������а�ȫ��ͼ�Ķ���\n");
	printf("              farmer  , wolf,  sheep   , veget\n");
	for (int farmer = 0; farmer <= 1; farmer++) {
		for (int wolf = 0; wolf <= 1; wolf++) {
			for (int sheep = 0; sheep <= 1; sheep++) {
				for (int veget = 0; veget <= 1; veget++) {
					if (isSafe(farmer, wolf, sheep, veget)) {
						arr[i].farmer = farmer;
						arr[i].wolf = wolf;
						arr[i].sheep = sheep;
						arr[i].veget = veget;
						printf("��%d���������:��%d��       %d��     %d��     %d ��\n",i+1,arr[i].farmer , arr[i].wolf , arr[i].sheep ,arr[i].veget);
						fflush(stdout);
						i++;
					}
				}
			}
		}
	}
	index = i;
	printf("��[%d]�����\n",index);
}
//======================================================================================
// �ж�״̬i��״̬j֮���Ƿ��ת��
bool isConnect(int i, int j) {
	int k = 0;
	if (arr[i].wolf != arr[j].wolf) {
		k++;
	}
	if (arr[i].sheep != arr[j].sheep) {
		k++;
	}
	if (arr[i].veget != arr[j].veget) {
		k++;
	}
	// ��������������ͬʱ����������ũ��״̬�ı�ʱ��������,Ҳ��ũ��ÿ��ֻ�ܴ�һ���������ӻ��߲�����������
	if (arr[i].farmer != arr[j].farmer && k <= 1) {
		printf("%d->%d \n",i+1,j+1);
		return true;
	} else {
		return false;
	}
}

void mConn(bool A[][MAXV]) {
	printf("\n���п��Ե����������\n");
	for(int i = 0; i < index; i++) {
		for(int j = 0; j < index; j++) {
			// ״̬i��״̬j֮���ת������ʼ��Ϊ1������Ϊ0
			if (isConnect(i, j)) { //ũ��״̬����ı䣬��������ֻ�ܸı�һ����ֻ�ܴ�һ������
				A[i][j] = A[j][i] = true;
				isok++;
			} else {
				A[i][j] = A[j][i] = false;
			}
		}
	}
}
//======================================================================================
int visit[MAXV] = {0};
int paths[MAXV][MAXV]; //���·��
int path[MAXV]; //·��
int pathnum=0; //��ǰ�ǵڼ���·��
void FindAllPath(ALGraph *&G, int u,int v,int k) { //u->v   ��ǰ�ǵ�k��λ��
	int i;
	ArcNode *p;
	visit[u]=1; //�ߵ���u
	path[k]=u; //��ӵ�·��->�±�λ��Ϊk�Ľ����u����k+1����u��
	if (u==v) { //�ҵ���
		printf("\n");
		for (i=0; i<=k; i++) {//���Ƶ�paths
			paths[pathnum][i] = path[i];
			printf("%d  ",paths[pathnum][i]+1);
		}
		printf("\n");
		pathnum++; //����һ��·��
	} else {
		//u���ڱ߿�ʼ��
		for (p=G->adjlist[u].firstarc; p; p=p->nextarc) {
			if (visit[p->adjvex]==0)
				FindAllPath(G, p->adjvex, v, k+1); //ȥ����ڽӵ���
		}
	}
	// ���ݵ���һ�����
	// ע�⣺����Ӧ��д������-->Ҳ���ǲ�����û���ҵ���Ҫ����
	visit[u]=0;
	path[k]=0;
}
//======================================================================================
int local(int f,int w,int s,int v) {
	for(int i = 0; i < index; i++) {
		if( (f==arr[i].farmer) && (w==arr[i].wolf) && (s==arr[i].sheep) && (v==arr[i].veget) ) {
			return i;
		}
	}
}

void pAll(int end) {
	for(int i = 0; i < pathnum; i++) {
		int j;
		printf("  farmer  , wolf,  sheep   , veget\n");
		for(j = 0; paths[i][j] != end; j++) {
			printf("��%d��       %d��     %d��     %d ��\n",arr[paths[i][j]].farmer , arr[paths[i][j]].wolf , arr[paths[i][j]].sheep ,arr[paths[i][j]].veget);
		}
		printf("��%d��       %d��     %d��     %d ��\n\n\n",arr[paths[i][j]].farmer , arr[paths[i][j]].wolf , arr[paths[i][j]].sheep ,arr[paths[i][j]].veget);
	}
}
//======================================================================================
int FCR() {
	pathnum = index = 0;
	ALGraph *G;
	arr[index].farmer = arr[index].sheep = arr[index].veget = arr[index].wolf = 0;
	mAll();
	bool A[index][MAXV];
	mConn(A);
	CreateAdj(G,A,index,isok);
	int start = local(0,0,0,0);
	int end = local(1,1,1,1);
	FindAllPath(G,start,end,0);
	printf("��%d��·��\n\n",pathnum);
	pAll(end);
	return 0;
}
