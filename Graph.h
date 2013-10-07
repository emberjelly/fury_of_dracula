#ifndef GRAPH_H
#define GRAPH_H

#include "cities.h"

#define ROAD 0
#define RAIL 1
#define SEA 2
#define ANY 4
#define NUM_TRANSPORT 3

// vertices denoted by integers 0..N-1 
typedef int Location;
typedef int Transport; 

typedef struct edge{
    Location start;
    Location end;
    Transport type;
} Edge;

// graph representation is hidden 
typedef struct GraphRep *Graph; 


// operations on graphs 
Graph newGraph();
void destroyGraph(Graph g); 
void canReachInN(Graph g, Location start, Transport type, int n, int locs[]);
void makeMap(Graph g);
void addLink(Graph g, Location start, Location end, Transport type);


typedef struct vNode *VList;

struct vNode { 
    Location v;     //ALICANTE etc
    Transport type; //ROAD, RAIL, SEA, ANY
    VList next; 
};  

struct GraphRep { 
    int nV; // #vertices
    int nE[NUM_TRANSPORT]; //counter for number of edges of each type    
    VList connections[NUM_MAP_LOCATIONS]; // array of lists 
}; 
#endif
