#include "uts.h"

#include <stack>
#include <iostream>


/* 
 * Generate all children of the parent
 */
template <typename datastructure>
static void genChildren(Node * parent, Node * child, datastructure &stack) {
	int parentHeight = parent->height;

	// can be called by multiple threads in parallel for different(!) nodes
	int numChildren = uts_numChildren(parent);
	// can be called by multiple threads in parallel for different(!) nodes
	int childType   = uts_childType(parent);

	// record number of children in parent
	parent->numChildren = numChildren;

	// construct children and push in our data structure
	if (numChildren > 0) {

		child->type = childType;
		child->height = parentHeight + 1;


		for (int i = 0; i < numChildren; i++) {
			for (int j = 0; j < getComputeGran(); j++) {
				// can be called by multiple threads in parallel for different(!) nodes
				rng_spawn(parent->state.state, child->state.state, i);
			}

			// store a copy auf *child in your data structure
			stack.push(*child);
			std::cout << "Added new child!" << std::endl;
		}
	}
}

/* 
 * parallel search of UTS trees using work stealing 
 */
template <typename datastructure>
static void parTreeSearch(datastructure &stack) {
	Node *parent;
	Node child;

	// init a child, we will reuse this again and again
	initNode(&child);

	/* local work */
	while (!stack.empty()) {

		// get an pointer to an element from our data structure
		parent = &stack.top();

		if (parent->numChildren < 0){
			// first time visited, construct children and place on stack
			genChildren(parent, &child, stack);
		} else {		
			// remove the element from our data structure
			stack.pop();
		}
	}
}





int main(int argc, char *argv[]) {

	// parse parameter
	uts_parseParams(argc, argv);
	
	// show parameter
	uts_printParams();

	// init the root node of our work-tree
	Node root;
	uts_initRoot(&root);
	
	// create our data structure
	std::stack<Node> stack;
	
	// add the root node to our data structure
	stack.push(root);

	// start our benchmark
	parTreeSearch(stack);

	// gather the following information during runtime and call this function
	// nThreads = number of threads
	// walltime = runtime of parTreeSearch
	// nNodes = number of nodes of the tree
	// nLeaves = number of leaves of the tree, that is number of children == 0
	// maxDepth = maximal depth of the tree
	// uts_showStats(int nThreads, double walltime, unsigned long nNodes, unsigned long nLeaves, unsigned long maxDepth)
	
	return 0;
}
