#include "AVL.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

inline int32_t Max ( int32_t A, int32_t B )
{
	
	return ( A > B ) ? A : B;
	
};

AVLNode_t * NewAVLNode ( uint32_t Value )
{
	
	AVLNode_t * Node = (AVLNode_t *) malloc ( sizeof ( AVLNode_t ) );
	
	if ( Node == NULL )
		return NULL;
	
	Node -> Value = Value;
	
	Node -> Parent = NULL;
	Node -> Left = NULL;
	Node -> Right = NULL;
	Node -> Height = 0;
	
	return Node;
	
};

void DeleteAVLNode ( AVLNode_t * Node )
{
	
	if ( Node == NULL )
		return;
	
	free ( Node );
	
};

void DeleteAVLTree ( AVLNode_t * Root )
{
	
	if ( Root == NULL )
		return;
	
	DeleteAVLTree ( Root -> Left );
	DeleteAVLTree ( Root -> Right );
	
	DeleteAVLNode ( Root );
	
};

inline int32_t __AdjustHeight ( AVLNode_t * Node )
{
	
	Node -> Height = 1 + Max ( ( Node -> Right != NULL ) ? Node -> Right -> Height : - 1, ( Node -> Left != NULL ) ? Node -> Left -> Height : - 1 );
	return Node -> Height;
	
};

inline AVLNode_t * __RotateRight ( AVLNode_t * Root )
{
	
	AVLNode_t * NewRoot = Root -> Left;
	
	if ( Root -> Parent != NULL )
	{
		
		if ( Root -> Parent -> Left == Root ) 
			Root -> Parent -> Left = NewRoot; 
		else
			Root -> Parent -> Right = NewRoot;
		
	}
	
	NewRoot -> Parent = Root -> Parent;
	Root -> Parent = NewRoot;
	Root -> Left = NewRoot -> Right;
	
	if ( Root -> Left != NULL )
		Root -> Left -> Parent = Root;
	
	NewRoot -> Right = Root;
	
	__AdjustHeight ( Root );
	__AdjustHeight ( NewRoot );
	
	return NewRoot;
	
};

inline AVLNode_t * __LeftMostNode ( AVLNode_t * Node )
{
	
	while ( Node -> Left != NULL )
		Node = Node -> Left;
	
	return Node;
	
};

inline AVLNode_t * __RotateLeft ( AVLNode_t * Root )
{
	
	AVLNode_t * NewRoot = Root -> Right;
	
	if ( Root -> Parent != NULL )
	{
		
		if ( Root -> Parent -> Right == Root ) 
			Root -> Parent -> Right = NewRoot; 
		else
			Root -> Parent -> Left = NewRoot;
		
	}
	
	NewRoot -> Parent = Root -> Parent;
	Root -> Parent = NewRoot;
	Root -> Right = NewRoot -> Left;
	
	if ( Root -> Right != NULL )
		Root -> Right -> Parent = Root;
	
	NewRoot -> Left = Root;
	
	__AdjustHeight ( Root );
	__AdjustHeight ( NewRoot );
	
	return NewRoot;
	
};


inline AVLNode_t * __Balance ( AVLNode_t * Root )
{
	
	int32_t Balance = 0;
	int32_t SubBalance = 0;
	
	Balance += ( Root -> Left != NULL ) ? Root -> Left -> Height : - 1;
	Balance -= ( Root -> Right != NULL ) ? Root -> Right -> Height : - 1;
	
	if ( Balance > 1 )
	{
		
		SubBalance += ( Root -> Left -> Left != NULL ) ? Root -> Left -> Left -> Height : - 1;
		SubBalance -= ( Root -> Left -> Right != NULL ) ? Root -> Left -> Right -> Height : - 1;
		
		if ( SubBalance > 0 )
		{
			
			Root = __RotateRight ( Root );
			
		}
		else
		{
			
			__RotateLeft ( Root -> Left );
			Root = __RotateRight ( Root );
			
		}
		
	}
	else if ( Balance < - 1 )
	{
		
		SubBalance -= ( Root -> Right -> Left != NULL ) ? Root -> Right -> Left -> Height : - 1;
		SubBalance += ( Root -> Right -> Right != NULL ) ? Root -> Right -> Right -> Height : - 1;
		
		if ( SubBalance > 0 )
		{
			
			Root = __RotateLeft ( Root );
			
		}
		else
		{
			
			__RotateRight ( Root -> Right );
			Root = __RotateLeft ( Root );
			
		}
		
	}
	
	return Root;
	
};

void AVLInsert ( AVLNode_t ** Root, AVLNode_t * Node )
{
	
	Node -> Height = 0;
	
	if ( * Root == NULL )
	{
		
		* Root = Node;
		
		return;
		
	}
	
	AVLNode_t * Current = * Root;
	
	while ( true )
	{
		
		if ( Node -> Value > Current -> Value )
		{
			
			if ( Current -> Right == NULL )
			{
				
				Node -> Parent = Current;
				Current -> Right = Node;
				
				break;
				
			}
			
			Current = Current -> Right;
			
		}
		else
		{
			
			if ( Current -> Left == NULL )
			{
				
				Node -> Parent = Current;
				Current -> Left = Node;
				
				break;
				
			}
			
			Current = Current -> Left;
			
			
		}
		
	}
	
	Current = Node;
	
	do
	{
		
		Current = Current -> Parent;
		__AdjustHeight ( Current );
		
		if ( Current == * Root )
		{
			
			* Root = __Balance ( Current );
			
			return;
			
		}
		
		Current = __Balance ( Current );
		
	} 
	while ( Current -> Parent != NULL );
	
};

void AVLRemove ( AVLNode_t ** Root, AVLNode_t * Node )
{
	
	AVLNode_t * UnbalancedNode;
	AVLNode_t * SuccessorNode;
	
	if ( Node == * Root )
	{
		
		if ( Node -> Left != NULL )
		{
			
			if ( Node -> Right != NULL )
			{
				
				SuccessorNode = __LeftMostNode ( Node -> Right );
				UnbalancedNode = SuccessorNode -> Parent;
				
				if ( SuccessorNode -> Right != NULL )
				{
					
					if ( UnbalancedNode -> Right == SuccessorNode )
						UnbalancedNode -> Right = SuccessorNode -> Right;
					else
						UnbalancedNode -> Left = SuccessorNode -> Right;
						
					SuccessorNode -> Right -> Parent = UnbalancedNode;
					
				}
				else
				{
					
					if ( UnbalancedNode -> Right == SuccessorNode )
						UnbalancedNode -> Right = NULL;
					else
						UnbalancedNode -> Left = NULL;
					
				}
				
				if ( UnbalancedNode == * Root )
				{
					
					UnbalancedNode = SuccessorNode;
					( * Root ) -> Right = NULL;
					
				}
				
				* Root = SuccessorNode;
				SuccessorNode -> Parent = NULL;
				
				SuccessorNode -> Left = Node -> Left;
				Node -> Left -> Parent = SuccessorNode;
				
				SuccessorNode -> Right = Node -> Right;
				if ( Node -> Right != NULL )
					Node -> Right -> Parent = SuccessorNode;
				
			}
			else
			{
				
				* Root = Node -> Left;
				* Root -> Parent = NULL;
				Node -> Left = NULL;
				
				return;
				
			}
			
		}
		else
		{
			
			if ( Node -> Right != NULL )
			{
				
				* Root = Node -> Right;
				* Root -> Parent = NULL;
				Node -> Right = NULL;
				
				return;
				
			}
			else
			{
				
				* Root = NULL;
				
				return;
				
			}
			
		}
		
	}
	else
	{
		
		if ( Node -> Left != NULL )
		{
			
			if ( Node -> Right != NULL )
			{
				
				SuccessorNode = __LeftMostNode ( Node -> Right );
				UnbalancedNode = SuccessorNode -> Parent;
				
				if ( SuccessorNode -> Right != NULL )
				{
					
					if ( UnbalancedNode -> Left == SuccessorNode )
						UnbalancedNode -> Left = SuccessorNode -> Right;
					else
						UnbalancedNode -> Right = SuccessorNode -> Right;
					
					SuccessorNode -> Right -> Parent = SuccessorNode -> Parent;
					
				}
				else
				{
					
					if ( UnbalancedNode -> Right == SuccessorNode )
						UnbalancedNode -> Right = NULL;
					else
						UnbalancedNode -> Left = NULL;
					
				}
				
				if ( UnbalancedNode == Node )
				{
					
					UnbalancedNode = SuccessorNode;
					Node -> Right = NULL;
					
				}
				
				if ( Node -> Parent -> Left == Node )
					Node -> Parent -> Left = SuccessorNode;
				else
					Node -> Parent -> Right = SuccessorNode;
				
				SuccessorNode -> Parent = Node -> Parent;
				
				SuccessorNode -> Right = Node -> Right;
				if ( SuccessorNode -> Right != NULL )
					SuccessorNode -> Right -> Parent = SuccessorNode;
				
				SuccessorNode -> Left = Node -> Left;
				SuccessorNode -> Left -> Parent = SuccessorNode;
				
				Node -> Parent = NULL;
				Node -> Left = NULL;
				Node -> Right = NULL;
				
			}
			else
			{
				
				if ( Node -> Parent -> Right == Node )
					Node -> Parent -> Right = Node -> Left;
				else
					Node -> Parent -> Left = Node -> Left;
				
				UnbalancedNode = Node -> Left -> Parent = Node -> Parent;
				Node -> Parent = NULL;
				Node -> Left = NULL;
			}
			
		}
		else
		{
			
			if ( Node -> Right != NULL )
			{
				
				if ( Node -> Parent -> Right == Node )
					Node -> Parent -> Right = Node -> Right;
				else
					Node -> Parent -> Left = Node -> Right;
				
				UnbalancedNode = Node -> Right -> Parent = Node -> Parent;
				Node -> Parent = NULL;
				Node -> Right = NULL;
				
			}
			else
			{
				
				if ( Node -> Parent -> Right == Node )
					Node -> Parent -> Right = NULL;
				else
					Node -> Parent -> Left = NULL;
				
				UnbalancedNode = Node -> Parent;
				Node -> Parent = NULL;
				
			}
			
		}
		
	}
	
	while ( true )
	{
		
		__AdjustHeight ( UnbalancedNode );
		
		if ( UnbalancedNode == * Root )
		{
			
			* Root = __Balance ( UnbalancedNode );
			
			return;
			
		}
		
		UnbalancedNode = __Balance ( UnbalancedNode );
		UnbalancedNode = UnbalancedNode -> Parent;
		
	}
	
};

AVLNode_t * Search ( AVLNode_t * Root, uint32_t Value )
{
	
	while ( true )
	{
		
		if ( Root == NULL )
			return NULL;
		
		if ( Root -> Value > Value )
			Root = Root -> Left;
		else if ( Root -> Value < Value )
			Root = Root -> Right;
		else
			return Root;
		
	}
	
};

inline void __PrintTree ( AVLNode_t * Node )
{
	
	if ( Node == NULL )
		return;
	
	__PrintTree ( Node -> Left );
	
	if ( Node -> Parent != NULL )
		printf ( "[%i (%i)]  ", Node -> Value, Node -> Parent -> Value );
	else
		printf("[%i (root)]  ", Node -> Value );
	
	__PrintTree ( Node -> Right );
	
}

void AVLPrint ( AVLNode_t * Root )
{
	
	__PrintTree ( Root );
	printf ( "\n" );
	
};
