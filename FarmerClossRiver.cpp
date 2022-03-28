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
// 图的顶点
{
	int farmer; // 农夫
	int wolf; // 狼
	int sheep; //羊
	int veget; // 白菜
} Vertex;
Vertex arr[MAXV];
typedef struct ANode {         	//弧的结点结构类型
	int adjvex;              	//该弧的终点位置
	struct ANode *nextarc; 		//指向下一条弧的指针
	bool isConnect;
} ArcNode;

typedef struct Vnode {    		//邻接表头结点的类型
	Vertex data;            	//顶点信息
	int count;             		//存放顶点入度,只在拓扑排序中用
	ArcNode *firstarc;     		//指向第一条弧
} VNode;

typedef struct {
	VNode  adjlist[MAXV];    //邻接表
	int n,e;		     //图中顶点数n和边数e
} ALGraph;			//邻接表类型
//======================================================================================

//每个表头表示每种状态 A为是否可以连接两种状态 A=0不能 A=1可以连接.....最后遍历能从初始状态到末尾状态的所有方法就可以了
void CreateAdj(ALGraph *&G,bool A[MAXV][MAXV],int n,int e) { //创建图的邻接表
	int i,j;
	ArcNode *p1;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	for (i=0; i<n; i++)								//给邻接表中所有头结点的指针域置初值
		G->adjlist[i].firstarc=NULL;
	for (i=0; i<n; i++)								//检查邻接矩阵中每个元素
		for (j=n-1; j>=0; j--)
			if (A[i][j]) {		//存在一条边
				p1 = (ArcNode *)malloc(sizeof(ArcNode));
				p1->adjvex = j;							//按照下标生成编号
				p1->isConnect = A[i][j];
//				p1=(ArcNode *)malloc(sizeof(ArcNode));	//创建一个结点p
				p1->nextarc = NULL;						//尾插法存储连接
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
//当农夫与羊不在一起时，狼与羊或羊与白菜在一起是不安全的
{
	if (farmer != sheep && (wolf == sheep || sheep == veget)) {
		return false;
	} else {
		return true; // 安全返回true
	}
}

void mAll() {
	int i = 0;
	printf("生成所有安全的图的顶点\n");
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
						printf("第%d组数据组合:（%d，       %d，     %d，     %d ）\n",i+1,arr[i].farmer , arr[i].wolf , arr[i].sheep ,arr[i].veget);
						fflush(stdout);
						i++;
					}
				}
			}
		}
	}
	index = i;
	printf("共[%d]种情况\n",index);
}
//======================================================================================
// 判断状态i与状态j之间是否可转换
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
	// 以上三个条件不同时满足两个且农夫状态改变时，返回真,也即农夫每次只能带一件东西过河或者不带东西过河
	if (arr[i].farmer != arr[j].farmer && k <= 1) {
		printf("%d->%d \n",i+1,j+1);
		return true;
	} else {
		return false;
	}
}

void mConn(bool A[][MAXV]) {
	printf("\n所有可以的连接情况：\n");
	for(int i = 0; i < index; i++) {
		for(int j = 0; j < index; j++) {
			// 状态i与状态j之间可转化，初始化为1，否则为0
			if (isConnect(i, j)) { //农夫状态必须改变，其他三个只能改变一个，只能带一个过河
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
int paths[MAXV][MAXV]; //存放路径
int path[MAXV]; //路径
int pathnum=0; //当前是第几条路径
void FindAllPath(ALGraph *&G, int u,int v,int k) { //u->v   当前是第k个位置
	int i;
	ArcNode *p;
	visit[u]=1; //走到了u
	path[k]=u; //添加到路径->下标位置为k的结点是u（第k+1个是u）
	if (u==v) { //找到了
		printf("\n");
		for (i=0; i<=k; i++) {//复制到paths
			paths[pathnum][i] = path[i];
			printf("%d  ",paths[pathnum][i]+1);
		}
		printf("\n");
		pathnum++; //找下一条路径
	} else {
		//u的邻边开始找
		for (p=G->adjlist[u].firstarc; p; p=p->nextarc) {
			if (visit[p->adjvex]==0)
				FindAllPath(G, p->adjvex, v, k+1); //去这个邻接点找
		}
	}
	// 回溯到上一个结点
	// 注意：回溯应该写在外面-->也就是不管有没有找到都要回溯
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
			printf("（%d，       %d，     %d，     %d ）\n",arr[paths[i][j]].farmer , arr[paths[i][j]].wolf , arr[paths[i][j]].sheep ,arr[paths[i][j]].veget);
		}
		printf("（%d，       %d，     %d，     %d ）\n\n\n",arr[paths[i][j]].farmer , arr[paths[i][j]].wolf , arr[paths[i][j]].sheep ,arr[paths[i][j]].veget);
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
	printf("共%d条路径\n\n",pathnum);
	pAll(end);
	return 0;
}
