#include <stdio.h>
#include "BiThrNode.h"

void visitTree(char);

int main(int argc,char *argv[]){
	BiThrTree curtree,treeHeader;
	char filename[] = "tree.txt";

	//构建树
	CreatBitTree(&curtree, filename);
	//线索化
	InOrderThreading(&treeHeader, curtree);
	//访问树
	InOrderVisit(treeheader, visitTree);
	printf("\n");

	return 0;
}

void visitTree(char ch){
	printf("%-5c", ch);
}
