#include <stdint.h>

#include "AVL.h"

int32_t main ( int32_t argc, const char * Argv [] )
{
	
	AVLNode_t * Root = NewAVLNode ( 10 );
	
	AVLNode_t * Node3 = NewAVLNode ( 3 );
	AVLNode_t * Node7 = NewAVLNode ( 3 );
	AVLNode_t * Node17 = NewAVLNode ( 17 );
	AVLNode_t * Node16 = NewAVLNode ( 16 );
	
	AVLInsert ( & Root, NewAVLNode ( 5 ) );
	AVLInsert ( & Root, NewAVLNode ( 4 ) );
	AVLInsert ( & Root, Node3 );
	AVLInsert ( & Root, NewAVLNode ( 15 ) );
	AVLInsert ( & Root, Node7 );
	AVLInsert ( & Root, Node16 );
	AVLInsert ( & Root, NewAVLNode ( 20 ) );
	AVLInsert ( & Root, NewAVLNode ( 1 ) );
	AVLInsert ( & Root, Node17 );
	AVLInsert ( & Root, NewAVLNode ( 12 ) );
	AVLInsert ( & Root, NewAVLNode ( 24 ) );
	AVLInsert ( & Root, NewAVLNode ( 19 ) );
	AVLInsert ( & Root, NewAVLNode ( 21 ) );
	
	// AVLPrints nodes in order from least to greatest as [$N ($P)] where N = Value and P = Parent's Value.
	// If the node is a root, it is printed in the form [N (root)].
	AVLPrint ( Root );
	
	AVLRemove ( & Root, Node3 );
	AVLRemove ( & Root, Node7 );
	AVLRemove ( & Root, Node17 );
	AVLRemove ( & Root, Node16 );
	
	AVLPrint ( Root );
	
	AVLRemove ( & Root, Root );
	AVLInsert ( & Root, NewAVLNode ( 18 ) );
	
	AVLPrint ( Root );
	
	DeleteAVLNode ( Node3 );
	DeleteAVLNode ( Node7 );
	DeleteAVLNode ( Node17 );
	DeleteAVLNode ( Node16 );
	DeleteAVLTree ( Root );
	
	return 0;
	
};

