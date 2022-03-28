/*
  共576行代码
  使用邻接表
  思路：
  		1、按照情况来生成所有成员可能的状态
		2、依照生成的状态判断每两个状态之间能否连接
		3、创建邻接表
		4、通过DFS查找所有start->end的路径
		5、输出所有方法及其步骤 
*/

#include "FarmerClossRiver.cpp"
#include "ChuanjiaoshiAndYeren.cpp"
#include <stdlib.h>
void menu() {
	printf("======================================\n");
	printf("======================================\n");
	printf("======                          ======\n");
	printf("======                          ======\n");
	printf("======    1、农夫过河           ======\n");
	printf("======    2、传教士与野人过河   ======\n");
	printf("======    3、退出               ======\n");
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
				printf("请输入1~3整数\n");
				system("pause");
		}
	}
	printf("成功退出~");
	return 0;
}
