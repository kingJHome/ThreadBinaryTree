#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BiThrNode.h"

/******************辅助函数*******************/
//线索化递归方法
BiThrTree InThreadTree(BiThrTree t,BiThrTree pre){
	BiThrTree result = NULL;

	if(t){
		BiThrTree temp = InThreadTree(t->lchild,NULL);
		/*if(!t->lchild){
			t->LTag = Thread;
			t->lchild = pre;
		}
		if(temp && !temp->rchild){
			temp->RTag = Thread;
			temp->rchild = t;
		}*/
		temp = InThreadTree(t->rchild,NULL);
		/*if( temp != NULL ){
			result = temp;
		}else{
			result = t;
		}*/
	}

	return result;
}

//获取文件树形字符串
char* getFileString(char *filename){
	char *result = NULL;
	int initSize = 10;
	FILE *fp = fopen(filename,"r");

	if( fp ){
		result = (char*)malloc(initSize);
		if(result){
			char *read = NULL;
			size_t setSize = 0,getSize;
			
			memset(result,'\0',initSize);
			getSize = getline(&read,&setSize,fp);
			if(getSize != -1){
				setSize = 0;
				strcpy(result, read);
				while((getSize = getline(&read,&setSize,fp)) != -1){
					setSize = 0;
					strcat(result,read);
				}
			}
		}
	}

	return result;
}

//获取制定的结束位置
char *endPos(char *str,const char find){
	size_t slen = strlen(str),
		   fpos = 0;
	
	for( ; fpos<slen && str[fpos]!=find; ++fpos);

	return (str+fpos);
}

//由文本构建树
void createTreeByStr(BiThrTree t,char *start,const char *end){
	if( t && start != end ){
		char *flagPos = strstr(start,"<"),
			 *value = strstr(flagPos,"\""),
			 *flagEnd = endPos(start,'>');

		if(flagPos[1] != '/'){
			BiThrTree pnode = (BiThrTree)malloc(sizeof(BiThrNode));
			if( pnode ){
				pnode->LTag = pnode->RTag = Link;
				pnode->data = value[1];
				pnode->parent = t;
				if(flagPos[1] == 'l'){
					t->lchild = pnode;
				}else if(flagPos[1] == 'r'){
					t->rchild = pnode;
				}

				if(*(flagEnd-1) != '/'){//非闭合标签，有子节点
					createTreeByStr(pnode, flagEnd+1, end);
				}else{
					createTreeByStr(t, flagEnd+1, end);
				}
			}
		}else{//闭合标签
			createTreeByStr(t->parent,flagEnd+1,end);
		}
	}
}
/*********************end*********************/

//构建树
void CreateBitTree(BiThrTree *t,char *filename){
	char *treeStr = getFileString(filename);
	
	//先根据字符串构建根结点
	char *rootStart = strstr(treeStr,"<root"),
		 *rootEnd = strstr(treeStr,"</root>");

	if(rootStart && rootEnd){
		*t = (BiThrTree)malloc(sizeof(BiThrNode));

		if( *t ){
			char *startend = endPos(rootStart,'>'),
				 *value = strstr(treeStr,"\"");

			(*t)->RTag = (*t)->LTag = Link;
			(*t)->data = *(value + 1);
			//构建根结点的左右子树
			createTreeByStr(*t,startend+1,rootEnd);
		}
	}
}

//中序遍历树
void InOriginVisit(BiThrTree t,void (*tarcter)(char)){
	if( t ){
		InOriginVisit(t->lchild, tarcter);
		tarcter(t->data);
		InOriginVisit(t->rchild, tarcter);
	}
}

//中序线索化树
void InOrderThreading(BiThrTree *thr,BiThrTree t){
	*thr = (BiThrTree)malloc(sizeof(BiThrNode));

	if( *thr ){
		(*thr)->LTag = Link;
		(*thr)->RTag = Thread;
		(*thr)->rchild = *thr;

		if( t == NULL ){
			(*thr)->lchild = *thr;
		}else{
			(*thr)->lchild = t;
			BiThrTree finalt = InThreadTree(t,*thr);
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
