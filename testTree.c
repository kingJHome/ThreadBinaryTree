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
	if( argc >= 2 ){
		//线索化
		if( strcmp(argc[1],"-i")==0 ){
			InOrderThreading(&treeHeader, curtree);
		}else if( strcmp(argc[1],"-n")==0 ){
			midThreadTree(&treeHeader, curtree);
		}
	}
	//访问树
	InOrderVisit(treeHeader, visitTree);
	printf("\n");

	return 0;
}

void visitTree(char ch){
	printf("%-3c", ch);
}
