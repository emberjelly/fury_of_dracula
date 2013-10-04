#include <stdlib.h>
#include <assert.h>
#include "game.h"
#include "HunterView.h"
#include <stdio.h>

#define ROAD 0
#define RAIL 1
#define SEA 2
#define ANY 4
#define NUM_TRANSPORT 3

//Can the Clashbee helps? :( 

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
static Graph newGraph();
static void destroyGraph(Graph g); 
static void showGraph(Graph g); 

//static int numV(Graph g);
//static int numE(Graph g, Transport t);


//returns 1 if there is an edge from start to end with a given transport type
//returns 0 otherwise
static int isAdjacent(Graph g,Location start, Location end, Transport type);

typedef struct vNode *VList;

static void makeMap(Graph g);
static void addLink(Graph g, Location start, Location end, Transport type);
static VList addtoList (Graph g, VList v, Location loca, Transport type);

struct vNode { 
    Location v;     //ALICANTE etc
    Transport type; //LAND, SEA, ANY
    VList next; 
};  

struct GraphRep { 
    int nV; // #vertices
    int nE[NUM_TRANSPORT]; //counter for number of edges of each type    
    VList connections[NUM_MAP_LOCATIONS]; // array of lists 
}; 

     
struct hunterView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    int curPlayer;
    int round;
    int score;
    int hp[5];
    char *pastPlays;
    int playerLocations[5];
    LocationID playerLocation;
    int hello;
    Graph map;
};
     

HunterView newHunterView( char *pastPlays, playerMessage messages[] ) {
    HunterView hunterView = malloc( sizeof( struct hunterView ) );
    
    hunterView->hello = 42;
    hunterView->curPlayer = 0;
    hunterView->round = 0;
    hunterView->score = GAME_START_SCORE;
    
    hunterView->hp[0] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[1] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[2] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[3] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[4] = GAME_START_BLOOD_POINTS;
    
    hunterView->pastPlays = pastPlays;
    
    hunterView->playerLocations[0] = UNKNOWN_LOCATION;
    hunterView->playerLocations[1] = UNKNOWN_LOCATION;
    hunterView->playerLocations[2] = UNKNOWN_LOCATION;
    hunterView->playerLocations[3] = UNKNOWN_LOCATION;
    hunterView->playerLocations[4] = UNKNOWN_LOCATION;
    
    hunterView->map = newGraph();
    
    showGraph(hunterView->map);
    return hunterView;
}
     
     
// this function frees all memory previously allocated for the HunterView
// toBeDeleted. toBeDeleted should not be accessed after the call.
void disposeHunterView( HunterView toBeDeleted ) {
    //COMPLETE THIS IMPLEMENTATION
    destroyGraph(toBeDeleted->map);
    free( toBeDeleted );
}


Round getRound (HunterView currentView) {
    return currentView->round;

}

//Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer (HunterView currentView) {
    return currentView->curPlayer;
}

//Get the current score
int getScore(HunterView currentView) {
    return currentView->score;

}

//Get the current health points for a given player
int getHealth(HunterView currentView, PlayerID id) {
    return currentView->hp[id];


}

//Get the current location id of a given player
//May be NO_LOCATION if the player has not had a turn yet
//(ie at the beginning of the game
//Or for dracula it may be UNKNOWN_CITY or UNKNOWN_SEA
LocationID getLocation(HunterView currentView, PlayerID id) {

    return currentView->playerLocations[id];
}

//Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns for the given player
// For dracula this may include other locations CITY_UNKNOWN or SEA_UNKNOWN
// For any player if the move does not exist yet (i.e, the start of the game),
// the value should be NO_LOCATION (-1)
// For example after 2 turns the array may have the contents
// {29, 182, -1, -1, -1, -1} 
// This would mean in the first move the player started on location 182 
// then moved to the current location of 29
void getHistory (HunterView currentView, PlayerID player,LocationID trail[TRAIL_SIZE]) {


}

//Functions that query the map to find information about connectivity

//This function returns an array of LocationID that represent all locations that are connected 
//to the given LocationID. 
//road, rail and sea are connections should only be considered if the road, rail, sea parameters 
//are TRUE.
//The size of the array should be stored in the variable pointed to by numLocations
//The array can be in any order but must contain unique entries
//Your function must take into account the round and player id for rail travel
//Your function must take into account that dracula can't move to the hospital or travel by rail
//but need not take into account draculas trail
//Any location that the player is currently in, should be included.
LocationID * connectedLocations(HunterView currentView, int * numLocations, LocationID from, 
                              PlayerID player, Round round, int road, int rail, int sea) {
    isAdjacent(currentView->map, 0, 1, 0);
    return NULL;
}


static Graph newGraph() { 
    int i; 
    Graph g = malloc(sizeof(struct GraphRep));
    assert(g != NULL);
    g->nV = NUM_MAP_LOCATIONS;
    for (i = 0; i < g->nV; i++){ 
        g->connections[i] = NULL;  
    }

    g->nE[ROAD] = 0;
    g->nE[SEA] = 0; 
    g->nE[RAIL] = 0;
    
    makeMap(g);
    return g; 
} 

static void destroyGraph(Graph g){
    int i;
    VList curr;
    VList next;
    assert(g != NULL);
    assert(g->connections != NULL);
  
    for (i = 0; i < g->nV; i++){
         curr = g->connections[i];
         while(curr !=NULL){
             next = curr->next;
             free(curr);
             curr=next;
         }
    }
    free(g);
}   

static void addLink(Graph g, Location start, Location end, Transport type){
    g->connections[start] = addtoList (g, g->connections[start], end, type);
    g->connections[end] = addtoList (g, g->connections[end], start, type);
    
    if (type == ANY){
        g->nE[ROAD] ++;
        g->nE[RAIL]++;
        g->nE[SEA] ++;
    } else {
        g->nE[type] ++;
    }
}


static VList addtoList (Graph g, VList v, Location loca, Transport type) {

    //Note: This function does not handle the case of being given
    //An edge which is already contained in the list
    
    VList newNode = malloc(sizeof(struct vNode));
    newNode->next = NULL;
    newNode->v = loca;
    newNode->type = type;

    if (v == NULL) return newNode;
    
    VList nextNode = v;
    while (nextNode->next != NULL) {
        nextNode = nextNode->next;
    }

    nextNode->next = newNode;
    return v;
}

static void makeMap(Graph g){
    addLink(g, EDINBURGH, MANCHESTER, ROAD);
    addLink(g, EDINBURGH, MANCHESTER, RAIL);
    addLink(g, EDINBURGH, HAMBURG, SEA);
    addLink(g, EDINBURGH, AMSTERDAM, SEA);
    
    
    addLink(g, GALWAY, DUBLIN, ROAD);
    addLink(g, GALWAY, LISBON, SEA);
    addLink(g, GALWAY, CADIZ, SEA);
    
    addLink(g, DUBLIN, LIVERPOOL, SEA);
    addLink(g, DUBLIN, SWANSEA, SEA);
    
    addLink (g, LIVERPOOL, MANCHESTER, RAIL);
    addLink (g, LIVERPOOL, MANCHESTER, ROAD);
    addLink (g, LIVERPOOL, SWANSEA, ROAD);
    addLink (g, LIVERPOOL, SWANSEA, SEA);
    addLink (g, LIVERPOOL, DUBLIN, SEA);
    
    addLink (g, MANCHESTER, LONDON, ROAD);
    addLink (g, MANCHESTER, LONDON, RAIL);
    
    addLink (g, SWANSEA, LONDON, ROAD);
    addLink (g, SWANSEA, LONDON, RAIL);
    
    
    addLink(g, LONDON, LE_HAVRE, SEA);
    addLink(g, LONDON, PLYMOUTH, SEA);
    addLink(g, LONDON, PLYMOUTH, ROAD);
    
    addLink(g, AMSTERDAM, BRUSSELS, ROAD);
    addLink(g, AMSTERDAM, COLOGNE, ROAD);
    addLink(g, AMSTERDAM, HAMBURG, SEA);
    
    addLink(g, COLOGNE, HAMBURG, ROAD);
    addLink(g, COLOGNE, BRUSSELS, ROAD);
    addLink(g, COLOGNE, BRUSSELS, RAIL);
    addLink(g, COLOGNE, STRASBOURG, ROAD);
    addLink(g, COLOGNE, LEIPZIG, ROAD);
    addLink(g, COLOGNE, FRANKFURT, ROAD);
    addLink(g, COLOGNE, FRANKFURT, RAIL);
    
    addLink(g, HAMBURG, LEIPZIG, ROAD);
    addLink(g, HAMBURG, BERLIN, ROAD);
    addLink(g, HAMBURG, BERLIN, RAIL);
    
    addLink(g, BERLIN, LEIPZIG, ROAD);
    addLink(g, BERLIN, LEIPZIG, RAIL);

    addLink(g, BERLIN, PRAGUE, ROAD);
    addLink(g, BERLIN, PRAGUE, RAIL);
    
    addLink(g, BRUSSELS, PRAGUE, ROAD);
    addLink(g, BERLIN, PRAGUE, ROAD);


}

//Useful for debugging
static void showGraph(Graph g) { 
    assert(g != NULL); 
    printf("V=%d, E=%d + %d + %d\n", g->nV, g->nE[ROAD],g->nE[RAIL], g->nE[SEA]); 
    int i; 
    for (i = 0; i < g->nV; i++) { 
        VList n = g->connections[i]; 
        while (n != NULL) { 
            printf("%d-%d ",i,n->v); 
            if(n->type == ROAD){
                printf("L ");
            } else if(n->type == SEA){
                printf("S ");
            } else {
                printf("ERROR NO SUCH TYPE");
                exit(0);
            }
            n = n->next; 
        } 
        if (g->connections [i] != NULL) 
            printf("\n"); 
        }
}
/*
static int numV(Graph g){
    assert(g != NULL);
    return g->nV;
}

static int numE(Graph g, Transport type){
    assert(g != NULL);
    assert(type >= 0 && type <= ANY);
    if(type == ANY){
        return g->nE[LAND] + g->nE[SEA];
    } else {
        return g->nE[type];
    }
}
*/
//returns 1 if there is an edge from start to end of the given type
//gives 0 otherwise
static int isAdjacent(Graph g,Location start, Location end, Transport type){
    VList l = g->connections[start];

    while (l != NULL) {
       if (l->v == end && (l->type == type || type == ANY)) {
           return 1;
       }
       l = l->next;
    }


    l = g->connections[end];

    while (l != NULL) {
       if (l->v == start && (l->type == type || type == ANY)) {
           return 1;
       }
       l = l->next;
    }
    
    return 0;
    
    
}

