#include <stdio.h>
#include <stdlib.h>
#include "BiThrNode.h"

/******************辅助函数*******************/
//线索化递归方法
BiThrTree InThreadTree(BiThrTree t,BiThrTree pre){
	BiThrTree result = NULL;

	if(t){
		BiThree temp = InThreadTree(t->lchild,pre);
		if(!t->lchild){
			t->LTag = Thread;
			t->lchild = pre;
		}
		if(!temp->rchild){
			temp->RTag = Thread;
			temp->rchild = t;
		}
		result = t;
		result = InThreadTree(t->rchild,result);
	}

	return result;
}
/*********************end*********************/

//构建树
void CreatBitTree(BiThrTree *t,char *filename){
}

//中序线索化树
void InOrderThreading(BiThrTree *thr,BiThrTree t){
	*thr = (BiThrTree)malloc(sizeof(BiThrNOde));

	if( *thr ){
		(*thr)->LTag = Link;
		(*thr)->RTag = Thread;
		(*thr)->rchild = *thr;

		if( !t ){
			(*thr)->lchild = *thr;
		}else{
			(*thr)->lchild = t;
			BiThrTree finalt = InThreadTree(t);
			finalt->RTag = Thread;
			finalt->rchild = (*thr);
			(*thr)->rchild = finalt;
		}
	}
}

//遍历线索化树
void InOrderVisit(BiThrTree t,void (*tracter)(char)){
	BiThrTree p = t->lchild;

	while(p != t){
		for( ; p->LTag==Link; p = p->lchild);
		tracter(p->data);
		while(p->RTag==Thread && p!=t){
			p = p->rchild;
			tracter(p->data);
		}
		p = p->rchild;
	}
}
