#define	MAXV 100				//��󶥵����
#define MAX 100
#include <stdio.h>
#include <malloc.h>
int visited[MAX] = {0};
int start_c,start_y,boat_member_max;
int cnt1;
int isok1 = 0;
int indexC = 0;
//���¶����ڽӱ�����
struct Rec {
	int left_c;		//�󰶴���ʿ
	int right_c;	//�Ұ�����ʿ
	int left_y;		//��Ұ��
	int right_y;	//�Ұ�Ұ��
	int boat_location;	//�������
};

struct Rec arr1[MAX];//·���洢

struct rec_Cal {
	int first, second;//��¼ǰ��״̬���ж��Ƿ��������   ǰi   ��j
};
rec_Cal cal[MAX];
typedef struct ANode1 {         	//���Ľ��ṹ����
	int adjvex;              	//�û����յ�λ��
	struct ANode1 *nextarc; 		//ָ����һ������ָ��
//	bool isConnect;				//�Ƿ���
} ArcNode1;

typedef Rec Vertex1;

typedef struct Vnode1 {    		//�ڽӱ�ͷ��������
	Vertex1 data;            	//������Ϣ
	int count;             		//��Ŷ������,ֻ��������������
	ArcNode1 *firstarc;     		//ָ���һ����
} Vnode1;

typedef struct {
	Vnode1  adjlist[MAXV];    //�ڽӱ�
	int n,e;		     //ͼ�ж�����n�ͱ���e
} ALGraph1;			//�ڽӱ�����
//======================================================================================

void pRec(Rec t) {
	printf("%4d             %4d             %4d             %4d             %4d\n",t.left_c,t.left_y,t.right_c,t.right_y,t.boat_location);
}
//======================================================================================
//���㵱������Ϊboat_member_max�����г˴����
void Cal() {
	int st = 0;
	for(int i = 0; i <= boat_member_max; ++i) {	//�޶��ϴ���Ա��
		if(i != 0)
			st = 0;
		else
			st = 1;
		for(int j = st; j <= boat_member_max-i; ++j) {
			cnt1++;
			cal[cnt1].first = i, cal[cnt1].second = j;
		}
	}
	printf("����ֻ������%d���˵�ʱ�򣬺Ϸ��Ķɺӷ���\n", boat_member_max);
	printf("	----����ʿ����----Ұ������----\n");
	for(int i = 0; i < cnt1; ++i)
		printf("[%d] ----%5d	----    %5d		----\n", i,
		       cal[i].first, cal[i].second);
	printf("cnt = %d\n", cnt1);
}
//======================================================================================
void CreateAdj(ALGraph1 *&G,bool A[MAXV][MAXV],int n,int e) { //����ͼ���ڽӱ�
	int i,j;
	ArcNode1 *p1;
	G=(ALGraph1 *)malloc(sizeof(ALGraph1));
	for (i=0; i<n; i++)								//���ڽӱ�������ͷ����ָ�����ó�ֵ
		G->adjlist[i].firstarc=NULL;
	for (i=0; i<n; i++)								//����ڽӾ�����ÿ��Ԫ��
		for (j=n-1; j>=0; j--)
			if (A[i][j]) {		//������������
				p1 = (ArcNode1 *)malloc(sizeof(ArcNode1));
				p1->adjvex = j;							//�����±����ɱ��
//				p1->isConnect = A[i][j];
//				p1=(ArcNode *)malloc(sizeof(ArcNode));	//����һ�����p
				p1->nextarc = NULL;						//β�巨�洢����
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
int paths1[MAX][MAX]; //���·��
int path1[MAX]; //·��
int pathnum1=0; //��ǰ�ǵڼ���·��
void FindAllPath(ALGraph1 *&G, int u,int v,int k) { //u->v   ��ǰ�ǵ�k��λ��
	int i;
	ArcNode1 *p;
	visit1[u]=1; //�ߵ���u
	path1[k]=u; //��ӵ�·��->�±�λ��Ϊk�Ľ����u����k+1����u��
	if (u==v) { //�ҵ���
		for (i=0; i<=k; i++) {//���Ƶ�paths
			paths1[pathnum1][i] = path1[i];
			printf("%d  ",paths1[pathnum1][i]);
		}
		printf("\n");
		pathnum1++; //����һ��·��
	} else {
		//u���ڱ߿�ʼ��
		for (p=G->adjlist[u].firstarc; p; p=p->nextarc) {
			if (visit1[p->adjvex]==0)
				FindAllPath(G, p->adjvex, v, k+1); //ȥ����ڽӵ���
		}
	}
	// ���ݵ���һ�����
	// ע�⣺����Ӧ��д������-->Ҳ���ǲ�����û���ҵ���Ҫ����
	visit1[u]=0;
	path1[k]=0;
}

void DispAdj(ALGraph1 *G) {	//����ڽӱ�G
	int i;
	ArcNode1 *p;
	for (i=0; i<G->n; i++) {
		p=G->adjlist[i].firstarc;
		printf("%d ->",i);
		while (p!=NULL) {
			printf("%d��",p->adjvex);
			p=p->nextarc;
		}
		printf("��\n");
	}
}
//======================================================================================
bool check(Rec t) {
	//�Ƿ��ظ�����
	for(int i = 0; i < indexC; i++) {
		if((t.left_c == arr1[i].left_c && t.left_y == arr1[i].left_y)
		        && (t.boat_location == arr1[i].boat_location)) {
			return false;
		}
	}
	//����С��0 ����
	if(t.left_c < 0 || t.left_y < 0 || t.right_c < 0 || t.right_y < 0  ) {
		return false;
	}

	/*
	����ʿ�Ƿ񱻳�
	1���󰶣��ڴ���ʿ���� ������0 ������£�����ʿ���� < Ұ������
	2���Ұ����ڴ���ʿ���� ������0 ������£�����ʿ���� < Ұ������
	*/
	if((t.left_c != 0 && t.left_c < t.left_y) ||
	        (t.right_c < t.right_y && t.right_c != 0) ) {
		return false;
	}
	/*����Ϊ1���Ұ�Ϊ-1��
	1����û�˵�����£�boatֵ����Ϊ-1
	2���Ұ�û�˵�����£�boatֵ����Ϊ1
	*/
	//0 0 3 0 -1
	if((t.left_c == 0 && t.left_y == 0 && t.boat_location == 1)||(t.right_c == 0 && t.right_y == 0 && t.boat_location == -1)) {
		return false;
	}
	return true;
}

bool isConn(int i,int j) {                             //����������������������������������������������������
	/*
	��j�Ĵ�Ϊ-1ʱ��˵������ĩ״̬���Ұ�
	һ�����ж� i ״̬���Ƿ�����
	�����ж� i -> j״̬ʱ�ǲ��� i �ļ������� j ��������,�� �󰶵� ������ ���Ұ��� �����
	�����仯�Ĵ�С�Ƿ񳬹����������
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
	��֮��Ȼ
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
	printf("��[%d]�����\n",indexC);
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
	printf("������bool�Ͷ�ά�����¼ÿ��������Ƿ��������\n");
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
		printf("\n��%d��·��\n",i+1);
		printf("�󰶴���ʿ��\t��Ұ����\t�Ұ�����ʿ��\t�Ұ�Ұ����\t����λ��\n");
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
	printf("�����봫��ʿ������");
	scanf("%d",&start_c);
	printf("������Ұ��������");
	scanf("%d",&start_y);
	printf("�����봬�������������");
	scanf("%d", &boat_member_max);
	if(boat_member_max == 0){
		printf("�޹��ӷ���\n");
		return;
	}
	Cal();							//�ҵ����жɴ����

	arr1[0].left_c = start_c;
	arr1[0].left_y = start_y;
	arr1[0].right_c = 0;
	arr1[0].right_y = 0;
	arr1[0].boat_location = 1;
	mAll(arr1);						//�ҵ��������
	bool A[indexC][MAX];
	mConn1(A);						//����bool�Ͷ�ά���飬���жϺ������ж��������Ƿ��������
	CreateAdj(G,A,indexC,2*isok1);
	DispAdj(G);
	printf("\n");
	int start = local(start_c,start_y,0,0,1);
	int end = local(0,0,start_c,start_y,-1);
	FindAllPath(G,start,end,0 );
	if(pathnum1 == 0){
		printf("�޹��ӷ���\n");
		return;
	}
	else{
		printf("��%d�ֹ��ӷ���\n",pathnum1);
		DispMeth(end);
	}
	return;
}
