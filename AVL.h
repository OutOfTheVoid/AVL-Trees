#ifndef AVL_H
#define AVL_H

#include <stdint.h>

typedef struct AVLNode_Struct
{
	
	struct AVLNode_Struct * Parent;
	struct AVLNode_Struct * Left;
	struct AVLNode_Struct * Right;
	
	int32_t Height;
	
	uint32_t Value;
	
} AVLNode_t;

AVLNode_t * NewAVLNode ( uint32_t Value );
void DeleteAVLNode ( AVLNode_t * Node );
void DeleteAVLTree ( AVLNode_t * Root );

void AVLInsert ( AVLNode_t ** Root, AVLNode_t * Node );
void AVLRemove ( AVLNode_t ** Root, AVLNode_t * Node );
AVLNode_t * AVLSearch ( AVLNode_t * Root, uint32_t Value );

void AVLPrint ( AVLNode_t * Root );

#endif
