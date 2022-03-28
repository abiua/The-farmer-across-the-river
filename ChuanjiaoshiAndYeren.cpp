#define	MAXV 100				//最大顶点个数
#define MAX 100
#include <stdio.h>
#include <malloc.h>
int visited[MAX] = {0};
int start_c,start_y,boat_member_max;
int cnt1;
int isok1 = 0;
int indexC = 0;
//以下定义邻接表类型
struct Rec {
	int left_c;		//左岸传教士
	int right_c;	//右岸传教士
	int left_y;		//左岸野人
	int right_y;	//右岸野人
	int boat_location;	//靠岸情况
};

struct Rec arr1[MAX];//路径存储

struct rec_Cal {
	int first, second;//记录前后状态，判断是否可以连接   前i   后j
};
rec_Cal cal[MAX];
typedef struct ANode1 {         	//弧的结点结构类型
	int adjvex;              	//该弧的终点位置
	struct ANode1 *nextarc; 		//指向下一条弧的指针
//	bool isConnect;				//是否能
} ArcNode1;

typedef Rec Vertex1;

typedef struct Vnode1 {    		//邻接表头结点的类型
	Vertex1 data;            	//顶点信息
	int count;             		//存放顶点入度,只在拓扑排序中用
	ArcNode1 *firstarc;     		//指向第一条弧
} Vnode1;

typedef struct {
	Vnode1  adjlist[MAXV];    //邻接表
	int n,e;		     //图中顶点数n和边数e
} ALGraph1;			//邻接表类型
//======================================================================================

void pRec(Rec t) {
	printf("%4d             %4d             %4d             %4d             %4d\n",t.left_c,t.left_y,t.right_c,t.right_y,t.boat_location);
}
//======================================================================================
//计算当最大最船量为boat_member_max的所有乘船情况
void Cal() {
	int st = 0;
	for(int i = 0; i <= boat_member_max; ++i) {	//限定上船成员量
		if(i != 0)
			st = 0;
		else
			st = 1;
		for(int j = st; j <= boat_member_max-i; ++j) {
			cnt1++;
			cal[cnt1].first = i, cal[cnt1].second = j;
		}
	}
	printf("当船只最多承载%d个人的时候，合法的渡河方案\n", boat_member_max);
	printf("	----传教士人数----野人人数----\n");
	for(int i = 0; i < cnt1; ++i)
		printf("[%d] ----%5d	----    %5d		----\n", i,
		       cal[i].first, cal[i].second);
	printf("cnt = %d\n", cnt1);
}
//======================================================================================
void CreateAdj(ALGraph1 *&G,bool A[MAXV][MAXV],int n,int e) { //创建图的邻接表
	int i,j;
	ArcNode1 *p1;
	G=(ALGraph1 *)malloc(sizeof(ALGraph1));
	for (i=0; i<n; i++)								//给邻接表中所有头结点的指针域置初值
		G->adjlist[i].firstarc=NULL;
	for (i=0; i<n; i++)								//检查邻接矩阵中每个元素
		for (j=n-1; j>=0; j--)
			if (A[i][j]) {		//可以连接再连
				p1 = (ArcNode1 *)malloc(sizeof(ArcNode1));
				p1->adjvex = j;							//按照下标生成编号
//				p1->isConnect = A[i][j];
//				p1=(ArcNode *)malloc(sizeof(ArcNode));	//创建一个结点p
				p1->nextarc = NULL;						//尾插法存储连接
				ArcNode1 *p;
				p = (ArcNode1 *)malloc(sizeof(ArcNode1));
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
int visit1[MAX] = {0};
int paths1[MAX][MAX]; //存放路径
int path1[MAX]; //路径
int pathnum1=0; //当前是第几条路径
void FindAllPath(ALGraph1 *&G, int u,int v,int k) { //u->v   当前是第k个位置
	int i;
	ArcNode1 *p;
	visit1[u]=1; //走到了u
	path1[k]=u; //添加到路径->下标位置为k的结点是u（第k+1个是u）
	if (u==v) { //找到了
		for (i=0; i<=k; i++) {//复制到paths
			paths1[pathnum1][i] = path1[i];
			printf("%d  ",paths1[pathnum1][i]);
		}
		printf("\n");
		pathnum1++; //找下一条路径
	} else {
		//u的邻边开始找
		for (p=G->adjlist[u].firstarc; p; p=p->nextarc) {
			if (visit1[p->adjvex]==0)
				FindAllPath(G, p->adjvex, v, k+1); //去这个邻接点找
		}
	}
	// 回溯到上一个结点
	// 注意：回溯应该写在外面-->也就是不管有没有找到都要回溯
	visit1[u]=0;
	path1[k]=0;
}

void DispAdj(ALGraph1 *G) {	//输出邻接表G
	int i;
	ArcNode1 *p;
	for (i=0; i<G->n; i++) {
		p=G->adjlist[i].firstarc;
		printf("%d ->",i);
		while (p!=NULL) {
			printf("%d→",p->adjvex);
			p=p->nextarc;
		}
		printf("∧\n");
	}
}
//======================================================================================
bool check(Rec t) {
	//是否重复操作
	for(int i = 0; i < indexC; i++) {
		if((t.left_c == arr1[i].left_c && t.left_y == arr1[i].left_y)
		        && (t.boat_location == arr1[i].boat_location)) {
			return false;
		}
	}
	//人数小于0 出错
	if(t.left_c < 0 || t.left_y < 0 || t.right_c < 0 || t.right_y < 0  ) {
		return false;
	}

	/*
	传教士是否被吃
	1、左岸：在传教士人数 不等于0 的情况下，传教士人数 < 野人人数
	2、右岸：在传教士人数 不等于0 的情况下，传教士人数 < 野人人数
	*/
	if((t.left_c != 0 && t.left_c < t.left_y) ||
	        (t.right_c < t.right_y && t.right_c != 0) ) {
		return false;
	}
	/*（左岸为1，右岸为-1）
	1、左岸没人的情况下，boat值不能为-1
	2、右岸没人的情况下，boat值不能为1
	*/
	//0 0 3 0 -1
	if((t.left_c == 0 && t.left_y == 0 && t.boat_location == 1)||(t.right_c == 0 && t.right_y == 0 && t.boat_location == -1)) {
		return false;
	}
	return true;
}

bool isConn(int i,int j) {                             //出问题啦！！！！！！！！！！！！！！！！！！！！！！
	/*
	当j的船为-1时，说明船的末状态在右岸
	一、先判断 i 状态船是否在左岸
	二、判断 i -> j状态时是不是 i 的减少了且 j 的增多了,即 左岸的 减少了 ，右岸的 变多了
	三、变化的大小是否超过最大载人数
	*/
	if(arr1[j].boat_location == -1) {
		if(arr1[i].boat_location == -1) {
			return false;
		}
		if( (arr1[j].right_c - arr1[i].right_c < 0)||(arr1[j].right_y - arr1[i].right_y < 0) ) {
			return false;
		}
		if( (arr1[j].right_c-arr1[i].right_c)==0 && (arr1[j].right_y - arr1[i].right_y)==0 ) {
			return false;
		}
		if( ((arr1[j].right_c-arr1[i].right_c)+(arr1[j].right_y-arr1[i].right_y)) >boat_member_max ) {
			return false;
		}
	}
	/*
	反之亦然
	*/
	if(arr1[j].boat_location == 1) {
		if(arr1[i].boat_location == 1) {
			return false;
		}
		if( (arr1[j].left_c - arr1[i].left_c < 0)||(arr1[j].left_y - arr1[i].left_y < 0) ) {
			return false;
		}
		if( (arr1[j].left_c-arr1[i].left_c)==0 && (arr1[j].left_y - arr1[i].left_y)==0 ) {
			return false;
		}
		if( ((arr1[j].left_c-arr1[i].left_c)+(arr1[j].left_y-arr1[i].left_y)) >boat_member_max ) {
			return false;
		}
	}

	return true;
}

void mAll(Rec node[]) {
	for(int i = 0; i < indexC+1; i++) {
		for(int j = 0; j < cnt1; j++) {
			Rec t;
			t.left_c = node[i].left_c - cal[j].first * node[i].boat_location;
			t.left_y = node[i].left_y - cal[j].second * node[i].boat_location;
			t.right_c = node[i].right_c + cal[j].first * node[i].boat_location;
			t.right_y = node[i].right_y + cal[j].second * node[i].boat_location;
			t.boat_location = (-1 * node[indexC].boat_location);
			if(check(t)) {
				node[++indexC] = t;
			}
		}
	}
	indexC++;
	for(int i = 0; i < indexC ; i++) {
		pRec(node[i]);
	}
	printf("共[%d]种情况\n",indexC);
}

void mConn1(bool A[][MAX]) {
	for(int i = 0; i < indexC; i++)
		for(int j = 0; j < indexC; j++) {
			if(i == j) {
				A[j][i] = A[i][j] = false;
				continue;
			}
			if(isConn(i,j)) {
				A[j][i] = A[i][j] = true;
				isok1++;
			} else {
				A[j][i] = A[i][j] = false;
			}
		}
	printf("以下是bool型二维数组记录每两种情况是否可以相连\n");
	for(int i = 0; i < indexC; i++) {
		for(int j = 0; j < indexC; j++) {
			if(A[i][j]) {
				printf("1 ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
//======================================================================================
int local(int lc,int ly,int rc,int ry,int boat) {
	for(int i = 0; i < indexC; i++) {
		if( (lc == arr1[i].left_c) && (ly == arr1[i].left_y) && (rc == arr1[i].right_c) && (ry == arr1[i].right_y) && (boat == arr1[i].boat_location) ) {
			return i;
		}
	}
}
//======================================================================================
void DispMeth(int end) {
	for(int i = 0; i < pathnum1; i++) {
		printf("\n第%d条路径\n",i+1);
		printf("左岸传教士数\t左岸野人数\t右岸传教士数\t右岸野人数\t船的位置\n");
		int j = 0;
		for(j = 0; paths1[i][j] != end; j++) {
			pRec(arr1[paths1[i][j]]);
		}
		pRec(arr1[paths1[i][j]]);
		printf("\n");
	}

}
//======================================================================================
void CAY() {
	cnt1 = indexC = pathnum1 = 0;
	ALGraph1 *G;
	printf("请输入传教士人数：");
	scanf("%d",&start_c);
	printf("请输入野人人数：");
	scanf("%d",&start_y);
	printf("请输入船最大载人数量：");
	scanf("%d", &boat_member_max);
	if(boat_member_max == 0){
		printf("无过河方法\n");
		return;
	}
	Cal();							//找到所有渡船情况

	arr1[0].left_c = start_c;
	arr1[0].left_y = start_y;
	arr1[0].right_c = 0;
	arr1[0].right_y = 0;
	arr1[0].boat_location = 1;
	mAll(arr1);						//找到所有情况
	bool A[indexC][MAX];
	mConn1(A);						//制作bool型二维数组，用判断函数来判断两个点是否可以连接
	CreateAdj(G,A,indexC,2*isok1);
	DispAdj(G);
	printf("\n");
	int start = local(start_c,start_y,0,0,1);
	int end = local(0,0,start_c,start_y,-1);
	FindAllPath(G,start,end,0 );
	if(pathnum1 == 0){
		printf("无过河方法\n");
		return;
	}
	else{
		printf("共%d种过河方法\n",pathnum1);
		DispMeth(end);
	}
	return;
}
