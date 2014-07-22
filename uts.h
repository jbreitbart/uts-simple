/*
 *         ---- The Unbalanced Tree Search (UTS) Benchmark ----
 *  
 *  Copyright (c) 2010 See AUTHORS file for copyright holders
 *
 *  This file is part of the unbalanced tree search benchmark.  This
 *  project is licensed under the MIT Open Source license.  See the LICENSE
 *  file for copyright and licensing information.
 *
 *  UTS is a collaborative project between researchers at the University of
 *  Maryland, the University of North Carolina at Chapel Hill, and the Ohio
 *  State University.  See AUTHORS file for more information.
 *
 */

#ifndef _UTS_H
#define _UTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rng/rng.h"

/***********************************************************
 *  Tree node                                              *
 ***********************************************************/
struct Node {
	int type;
	int height;
	int numChildren;
	struct state_t state;
};



void uts_initRoot(Node * root);
int uts_numChildren(Node *parent);
int uts_numChildren_bin(Node * parent);
int uts_numChildren_geo(Node * parent);
int uts_childType(Node *parent);
void initNode(Node * child);
int getComputeGran();
void uts_parseParams(int argc, char **argv);
void uts_printParams();

void uts_showStats(int nThreads, double walltime, unsigned long nNodes, unsigned long nLeaves, unsigned long maxDepth);

#ifdef __cplusplus
}
#endif

#endif /* _UTS_H */
