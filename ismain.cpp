/*
  ��576�д���
  ʹ���ڽӱ�
  ˼·��
  		1������������������г�Ա���ܵ�״̬
		2���������ɵ�״̬�ж�ÿ����״̬֮���ܷ�����
		3�������ڽӱ�
		4��ͨ��DFS��������start->end��·��
		5��������з������䲽�� 
*/

#include "FarmerClossRiver.cpp"
#include "ChuanjiaoshiAndYeren.cpp"
#include <stdlib.h>
void menu() {
	printf("======================================\n");
	printf("======================================\n");
	printf("======                          ======\n");
	printf("======                          ======\n");
	printf("======    1��ũ�����           ======\n");
	printf("======    2������ʿ��Ұ�˹���   ======\n");
	printf("======    3���˳�               ======\n");
	printf("======                          ======\n");
	printf("======                          ======\n");
	printf("======================================\n");
	printf("======================================\n");

}

int main() {
	int k=1;
	while(k) {
		system("cls");
		menu();
		int n;
		scanf("%d",&n);
		system("cls");
		switch(n) {
			case 1:
				FCR();
				system("pause");
				break;
			case 2:
				CAY();
				system("pause");
				break;
			case 3:
				k = 0;
				break;
			default :
				printf("������1~3����\n");
				system("pause");
		}
	}
	printf("�ɹ��˳�~");
	return 0;
}
