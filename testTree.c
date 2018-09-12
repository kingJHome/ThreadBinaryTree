#include <stdio.h>
#include "BiThrNode.h"

void visitTree(char);

int main(int argc,char *argv[]){
	BiThrTree curtree,treeHeader;
	char filename[] = "tree.txt";

	//构建树
	CreateBitTree(&curtree, filename);
	//中序遍历树
	//InOriginVisit(curtree, visitTree);
	//线索化
	InOrderThreading(&treeHeader, curtree);
	//访问树
	InOrderVisit(treeHeader, visitTree);
	printf("\n");

	return 0;
}

void visitTree(char ch){
	printf("%-3c", ch);
}
