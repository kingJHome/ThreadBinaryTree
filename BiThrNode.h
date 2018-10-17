#ifndef _SELFNODE_TREE
#define _SELFNODE_TREE

#define MAXSIZE 20

typedef enum{Link, Thread}PointerTag;				//Link:指针;Thread:线索
typedef struct BiThrNode{
	char data;
	struct BiThrNode *parent,*lchild,*rchild;		//父节点、左右孩子指针
	PointerTag LTag,RTag;					//左右标志
}BiThrNode, *BiThrTree;

/****************************栈*******************************/
typedef struct treeStack{
	BiThrTree arr[MAXSIZE];
	int curPos;
}TreeStack;
/*************************************************************/

//构建树
void CreateBitTree(BiThrTree *t,char *filename);

//中序遍历树
void InOriginVisit(BiThrTree t,void (*tarcter)(char));

//中序线索化树
void InOrderThreading(BiThrTree *thr,BiThrTree t);

//非递归中序线索化树
void midThreadTree(BiThrTree *thr,BiThrTree t);

//遍历线索化树
void InOrderVisit(BiThrTree t,void (*tracter)(char));
#endif
