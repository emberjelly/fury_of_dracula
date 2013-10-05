#include <stdlib.h>
#include <assert.h>
#include "game.h"
#include "HunterView.h"
#include <stdio.h>
#include <string.h>

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
static Graph newGraph();
static void destroyGraph(Graph g); 
static void updateTrail (HunterView h);
static void canReachInN(Graph g, Location start, Transport type, int n, int locs[]);
static void update(HunterView hunterView, char *play);
typedef struct vNode *VList;

static void makeMap(Graph g);
static void addLink(Graph g, Location start, Location end, Transport type);
static VList addtoList (Graph g, VList v, Location loca, Transport type);

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

     
struct hunterView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    int curPlayer; //Player whose turn it is
    int round; //Round number
    int score;
    int hp[5]; //The hunters health and dracula's blood points
    char *pastPlays; //All plays ever made
    int playerLocations[5]; //Location of all 5 players
    LocationID playerLocation; //Location of current player
    int hello; //Whatever that is
    Graph map; //The graph of the map
    char trails[5][TRAIL_SIZE];
};
     

HunterView newHunterView( char *pastPlays, playerMessage messages[] ) {
    HunterView hunterView = malloc( sizeof( struct hunterView ) );
   
    //Put the initial values into the hunterView adt
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
    int i, j;
    for (i = 0; i < 5; i ++) {
        for (j = 0; j < TRAIL_SIZE; j ++) {
            hunterView->trails[i][j] = UNKNOWN_LOCATION;
        }
    }
    //Store each characters information in a play
    char play[8];
    int i1 = 0;
    int i2 = 0;
    play[7] = '\0';
    int pos = 0;
    int turnCount = 0;
    //A wrapper for updating the hunterView
    while (pastPlays[pos] != '\0')  {
        //Build the string with the player info for this turn
        play[i2] = pastPlays[pos];
        if (i2 == 6) {
            printf("update ");
            update(hunterView, play);
            if (pastPlays[pos + 1] != '\0') pos ++;
            turnCount ++;
            if (turnCount % 5 == 0) {
                //When all 5 players have had a turn
                hunterView->round ++; //Increment the round number
                //Adjust the game score
                hunterView->score --;
            }

        }
        pos ++;
        i1 ++;
        i2 = i1%7;
    }
    
    hunterView->map = newGraph();

    return hunterView;
}

static void update(HunterView hunterView, char *play) {
    
    //The character whose turn it is
    int character;
    
    if (play[0] == 'B') character = 0;
    if (play[0] == 'S') character = 1;
    if (play[0] == 'H') character = 2;
    if (play[0] == 'M') character = 3;
    if (play[0] == 'D') character = 4;
    printf("%s\n", play);
    //A string to store the city code
    char city[3];
    city[0] = play[1];
    city[1] = play[2];
    city[2] = '\0';

    //Move the player to the new location

    if (strcmp(city,"AL") == 0) hunterView->playerLocations[character] = 0;
    if (strcmp(city,"AM") == 0) hunterView->playerLocations[character] = 1;
    if (strcmp(city,"AT") == 0) hunterView->playerLocations[character] = 2;
    if (strcmp(city,"BA") == 0) hunterView->playerLocations[character] = 3;
    if (strcmp(city,"BI") == 0) hunterView->playerLocations[character] = 4;
    if (strcmp(city,"BE") == 0) hunterView->playerLocations[character] = 5;
    if (strcmp(city,"BR") == 0) hunterView->playerLocations[character] = 6;
    if (strcmp(city,"BO") == 0) hunterView->playerLocations[character] = 7;
    if (strcmp(city,"BU") == 0) hunterView->playerLocations[character] = 8;
    if (strcmp(city,"BC") == 0) hunterView->playerLocations[character] = 9;
    if (strcmp(city,"BD") == 0) hunterView->playerLocations[character] = 10;
    if (strcmp(city,"CA") == 0) hunterView->playerLocations[character] = 11;
    if (strcmp(city,"CG") == 0) hunterView->playerLocations[character] = 12;
    if (strcmp(city,"CD") == 0) hunterView->playerLocations[character] = 13;
    if (strcmp(city,"CF") == 0) hunterView->playerLocations[character] = 14;
    if (strcmp(city,"CO") == 0) hunterView->playerLocations[character] = 15;
    if (strcmp(city,"CN") == 0) hunterView->playerLocations[character] = 16;
    if (strcmp(city,"DU") == 0) hunterView->playerLocations[character] = 17;
    if (strcmp(city,"ED") == 0) hunterView->playerLocations[character] = 18;
    if (strcmp(city,"FL") == 0) hunterView->playerLocations[character] = 19;
    if (strcmp(city,"FR") == 0) hunterView->playerLocations[character] = 20;
    if (strcmp(city,"GA") == 0) hunterView->playerLocations[character] = 21;
    if (strcmp(city,"GW") == 0) hunterView->playerLocations[character] = 22;
    if (strcmp(city,"GE") == 0) hunterView->playerLocations[character] = 23;
    if (strcmp(city,"GO") == 0) hunterView->playerLocations[character] = 24;
    if (strcmp(city,"GR") == 0) hunterView->playerLocations[character] = 25;
    if (strcmp(city,"HA") == 0) hunterView->playerLocations[character] = 26;
    if (strcmp(city,"JM") == 0) hunterView->playerLocations[character] = 27;
    if (strcmp(city,"KL") == 0) hunterView->playerLocations[character] = 28;
    if (strcmp(city,"LE") == 0) hunterView->playerLocations[character] = 29;
    if (strcmp(city,"LI") == 0) hunterView->playerLocations[character] = 30;
    if (strcmp(city,"LS") == 0) hunterView->playerLocations[character] = 31;
    if (strcmp(city,"LV") == 0) hunterView->playerLocations[character] = 32;
    if (strcmp(city,"LO") == 0) hunterView->playerLocations[character] = 33;
    if (strcmp(city,"MA") == 0) hunterView->playerLocations[character] = 34;
    if (strcmp(city,"MN") == 0) hunterView->playerLocations[character] = 35;
    if (strcmp(city,"MR") == 0) hunterView->playerLocations[character] = 36;
    if (strcmp(city,"MI") == 0) hunterView->playerLocations[character] = 37;
    if (strcmp(city,"MU") == 0) hunterView->playerLocations[character] = 38;
    if (strcmp(city,"NA") == 0) hunterView->playerLocations[character] = 39;
    if (strcmp(city,"NP") == 0) hunterView->playerLocations[character] = 40;
    if (strcmp(city,"NU") == 0) hunterView->playerLocations[character] = 41;
    if (strcmp(city,"PA") == 0) hunterView->playerLocations[character] = 42;
    if (strcmp(city,"PL") == 0) hunterView->playerLocations[character] = 43;
    if (strcmp(city,"PR") == 0) hunterView->playerLocations[character] = 44;
    if (strcmp(city,"RO") == 0) hunterView->playerLocations[character] = 45;
    if (strcmp(city,"SA") == 0) hunterView->playerLocations[character] = 46;
    if (strcmp(city,"SN") == 0) hunterView->playerLocations[character] = 47;
    if (strcmp(city,"SR") == 0) hunterView->playerLocations[character] = 48;
    if (strcmp(city,"SJ") == 0) hunterView->playerLocations[character] = 49;
    if (strcmp(city,"SO") == 0) hunterView->playerLocations[character] = 50;
    if (strcmp(city,"ST") == 0) hunterView->playerLocations[character] = 51;
    if (strcmp(city,"SW") == 0) hunterView->playerLocations[character] = 52;
    if (strcmp(city,"SZ") == 0) hunterView->playerLocations[character] = 53;
    if (strcmp(city,"TO") == 0) hunterView->playerLocations[character] = 54;
    if (strcmp(city,"VA") == 0) hunterView->playerLocations[character] = 55;
    if (strcmp(city,"VR") == 0) hunterView->playerLocations[character] = 56;
    if (strcmp(city,"VE") == 0) hunterView->playerLocations[character] = 57;
    if (strcmp(city,"VI") == 0) hunterView->playerLocations[character] = 58;
    if (strcmp(city,"ZA") == 0) hunterView->playerLocations[character] = 59;
    if (strcmp(city,"ZU") == 0) hunterView->playerLocations[character] = 60;


    if (strcmp(city,"C?") == 0) hunterView->playerLocations[character] = 71;
    if (strcmp(city,"S?") == 0) hunterView->playerLocations[character] = 72;
    if (strcmp(city,"HI") == 0) hunterView->playerLocations[character] = 73;
    if (city[0] == 'D') hunterView->playerLocations[character] = 73 + (int)city[1] - '0';
    if (strcmp(city,"TP") == 0) hunterView->playerLocations[character] = 79;
    
    if (strcmp(city,"NS") == 0) hunterView->playerLocations[character] =  61;
    if (strcmp(city,"EC") == 0) hunterView->playerLocations[character] =  62;
    if (strcmp(city,"IS") == 0) hunterView->playerLocations[character] =  63;
    if (strcmp(city,"AO") == 0) hunterView->playerLocations[character] =  64;
    if (strcmp(city,"BB") == 0) hunterView->playerLocations[character] =  65;
    if (strcmp(city,"MS") == 0) hunterView->playerLocations[character] =  66;
    if (strcmp(city,"TS") == 0) hunterView->playerLocations[character] =  67;
    if (strcmp(city,"IO") == 0) hunterView->playerLocations[character] =  68;
    if (strcmp(city,"AS") == 0) hunterView->playerLocations[character] =  69;
    if (strcmp(city,"BS") == 0) hunterView->playerLocations[character] =  70;

    
    //Look at the remaining 4 spaces

    int i;
    char event;
    for (i = 0; i < 4; i ++) {
    
        event = play[i + 3]; //The +3 skips out the character and city code
        
        if (character == 4) {
            //Dracula
            if (event == 'T') {
                //Placed a trap
            }
            if (event == 'V') {
                if (i == 2) {
                    //Because 2 + 3 = 5
                    //Vampire has matured
                    hunterView->score -= 13;
                } else {
                    //Placed an immature vampire
                }
            }
            if (event == 'M') {
                //trap left trail
            }
        } else {
            //Hunter
            if (event == 'T') {
                //Trap was encountered
                hunterView->hp[character] -= 2;
            } else if (event == 'V') {
                //immature vampire is vanquished
            } else if (event == 'D') {
                //Dracula was encountered
                hunterView->hp[4] -= 10; //Dracula loses 10 points
                hunterView->hp[character] -= 4; //Hunter loses 4 points
            }
        }
    }
    
    //Update the player whose next turn it is
    updateTrail (hunterView);
    hunterView->curPlayer ++;
    if (hunterView->curPlayer > 4) hunterView->curPlayer = 0;
}

static void updateTrail (HunterView h) {
    char newTrail[6];
    newTrail[0] = getLocation(h, h->curPlayer);
    int i;
    for (i = 0; i < 5; i ++) {
        newTrail[i + 1] = h->trails[h->curPlayer][i];

    }

    for (i = 0; i < 6; i ++) {
        h->trails[h->curPlayer][i] = newTrail[i];
    }
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
    int i;
    for (i = 0; i < TRAIL_SIZE; i ++) {
        trail[i] = currentView->trails[player][i];
    }
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
    
    //Get the list corresponding to the given start location
    VList v = currentView->map->connections[from];

    //Allocate memory for the results
    LocationID * locs = malloc(*numLocations);
    locs[0] = from;
    int array[NUM_LOCATIONS] = {0};
    int i;
    int index = 1;
    
    for (i = 1; i < *numLocations; i ++) {
        locs[i] = -1;
    }

    if (rail) {
        //Dracula cannot travel by rail
        if (player != PLAYER_DRACULA) {
            //The number of cities transversable in one turn depends on the round
            canReachInN(currentView->map, from, RAIL, currentView->round%4, array);
            
            //Already added this one
            array[from] = 0;
            for (i = 0; i < NUM_LOCATIONS; i ++) {
                if (array[i]) {
                    locs[index] = i;
                    index ++;
                }
            }
        }
    }

    while (v != NULL) {
        //Cycle through the list and get the edges
        
        //handle road
        if (road) {
            if (v->type == ROAD) {
                if (!(v->v == ST_JOSEPH_AND_ST_MARYS && player == PLAYER_DRACULA)) {
                    if (!array[v->v]) {
                        locs[index] = v->v;
                        index ++;
                    }
                }
            }
        }

        
        if (sea) {
            if (v->type == SEA) {
                if (!array[v->v] && locs[index-1] != v->v) {
                    locs[index] = v->v;
                    index ++;
                }
            }
        }
        v = v->next;
    }
    
    return locs;
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

static void canReachInN(Graph g, Location start, Transport type, int n, int locs[]) {

    locs[start] = 1;
    if (n == 0) return;
    
    VList l = g->connections[start];
    while (l!= NULL) {
        if (type == l->type || type == ANY) {
            canReachInN(g,l->v, type, n-1, locs);
        }
        l = l->next;
    }
}

//Generate the map
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
    
    addLink(g, BRUSSELS, LE_HAVRE, ROAD);
    addLink(g, BRUSSELS, PARIS, ROAD);
    addLink(g, BRUSSELS, PARIS, RAIL);
    addLink(g, BRUSSELS, STRASBOURG, ROAD);

    addLink(g, FRANKFURT, STRASBOURG, ROAD);
    addLink(g, FRANKFURT, STRASBOURG, RAIL);
    addLink(g, FRANKFURT, NUREMBURG, ROAD);
    addLink(g, FRANKFURT, LEIPZIG, ROAD);
    addLink(g, FRANKFURT, LEIPZIG, RAIL);
    
    addLink(g, LEIPZIG, NUREMBURG, ROAD);
    addLink(g, LEIPZIG, NUREMBURG, RAIL);
   
    addLink(g, LE_HAVRE, NANTES, ROAD);
    addLink(g, LE_HAVRE, PARIS, ROAD);
    addLink(g, LE_HAVRE, PARIS, RAIL);
    
    addLink(g, PARIS, NANTES, ROAD);
    addLink(g, PARIS, BORDEAUX, RAIL);
    addLink(g, PARIS, CLERMONT_FERRAND, ROAD);
    addLink(g, PARIS, MARSEILLES, RAIL);
    addLink(g, PARIS, GENEVA, ROAD);
    addLink(g, PARIS, STRASBOURG, ROAD);
    
    addLink(g, STRASBOURG, GENEVA, ROAD);
    addLink(g, STRASBOURG, ZURICH, ROAD);
    addLink(g, STRASBOURG, ZURICH, RAIL);
    addLink(g, STRASBOURG, NUREMBURG, ROAD);
    addLink(g, STRASBOURG, MUNICH, ROAD);

    addLink(g, NUREMBURG, MUNICH, RAIL);
    addLink(g, NUREMBURG, MUNICH, ROAD);
    addLink(g, NUREMBURG, PRAGUE, ROAD);
    
    addLink(g, PRAGUE, VIENNA, ROAD);
    addLink(g, PRAGUE, VIENNA, RAIL);
   
    addLink(g, NANTES, BORDEAUX, SEA);
    addLink(g, NANTES, SANTANDER, SEA);
    addLink(g, NANTES, BORDEAUX, ROAD);
    addLink(g, NANTES, CLERMONT_FERRAND, ROAD);
    
    addLink(g,CLERMONT_FERRAND, BORDEAUX, ROAD);
    addLink(g,CLERMONT_FERRAND, MARSEILLES, ROAD);
    addLink(g,CLERMONT_FERRAND, GENEVA, ROAD);
    addLink(g,CLERMONT_FERRAND, TOULOUSE, ROAD);
    
    addLink(g, GENEVA, MARSEILLES, ROAD);
    addLink(g, GENEVA, MILAN, RAIL);
    addLink(g, GENEVA, ZURICH, ROAD);
    
    addLink(g, ZURICH, MUNICH, ROAD);
    addLink(g, ZURICH, MILAN, ROAD);
    addLink(g, ZURICH, MILAN, RAIL);
    addLink(g, ZURICH, MARSEILLES, ROAD);
    
    addLink(g, MUNICH, MILAN, ROAD);
    addLink(g, MUNICH, VENICE, ROAD);
    addLink(g, MUNICH, ZAGREB, ROAD);
    addLink(g, MUNICH, VIENNA, ROAD);
    
    addLink(g, BORDEAUX, SANTANDER, SEA);
    addLink(g, BORDEAUX, SARAGOSSA, ROAD);
    addLink(g, BORDEAUX, SARAGOSSA, RAIL);
    addLink(g, BORDEAUX, TOULOUSE, ROAD);
    
    addLink(g, TOULOUSE, SARAGOSSA, ROAD);
    addLink(g, TOULOUSE, BARCELONA, ROAD);
    addLink(g, TOULOUSE, MARSEILLES, ROAD);
    
    addLink(g, MARSEILLES, MILAN, ROAD);
    addLink(g, MARSEILLES, GENOA, ROAD);
    addLink(g, MARSEILLES, BARCELONA, SEA);
    addLink(g, MARSEILLES, ALICANTE, SEA);
    addLink(g, MARSEILLES, CAGLIARI, SEA);

    addLink(g, MILAN, GENOA, ROAD);
    addLink(g, MILAN, VENICE, ROAD);
    addLink(g, MILAN, FLORENCE, RAIL);
    
    addLink(g, VENICE, FLORENCE, ROAD);
    addLink(g, VENICE, VIENNA, RAIL);
    addLink(g, VENICE, BARI, SEA);
    addLink(g, VENICE, GENOA, ROAD);
    
    addLink(g, GENOA, FLORENCE, ROAD);
    addLink(g, GENOA, ROME, SEA);
    addLink(g, GENOA, NAPLES, SEA);
    addLink(g, GENOA, CAGLIARI, SEA);
    
    addLink(g, FLORENCE, ROME, ROAD);
    addLink(g, FLORENCE, ROME, RAIL);
    
    addLink(g, SANTANDER, LISBON, ROAD);
    addLink(g, SANTANDER, MADRID, ROAD);
    addLink(g, SANTANDER, MADRID, RAIL);
    addLink(g, SANTANDER, SARAGOSSA, ROAD);
    
    addLink(g, LISBON, CADIZ, SEA);
    addLink(g, LISBON, CADIZ, ROAD);
    addLink(g, LISBON, MADRID, ROAD);
    addLink(g, LISBON, MADRID, RAIL);
    
    addLink(g, MADRID, SARAGOSSA, RAIL);
    addLink(g, MADRID, SARAGOSSA, ROAD);
    addLink(g, MADRID, ALICANTE, RAIL);
    addLink(g, MADRID, ALICANTE, ROAD);
    addLink(g, MADRID, GRANADA, ROAD);
    addLink(g, MADRID, CADIZ, ROAD);
    
    addLink(g, CADIZ, GRANADA, ROAD);

    addLink(g, GRANADA, ALICANTE, ROAD);

    addLink(g, ALICANTE, SARAGOSSA, ROAD);
    addLink(g, ALICANTE, BARCELONA, RAIL);
    addLink(g, ALICANTE, BARCELONA, SEA);
    addLink(g, ALICANTE, GENOA, SEA);
    addLink(g, ALICANTE, CAGLIARI, SEA);
    
    addLink(g, CAGLIARI, ROME, SEA);
    addLink(g, CAGLIARI, NAPLES, SEA);
    
    addLink(g, SARAGOSSA, BARCELONA, ROAD);
    addLink(g, SARAGOSSA, BARCELONA, RAIL);

    addLink(g, ROME, NAPLES, SEA);
    addLink(g, ROME, NAPLES, ROAD);
    addLink(g, ROME, NAPLES, RAIL);
    addLink(g, ROME, BARI, ROAD);
    
    addLink(g, NAPLES, BARI, ROAD);
    addLink(g, NAPLES, BARI, RAIL);
    
    addLink(g, VIENNA, BUDAPEST, RAIL);
    addLink(g, VIENNA, BUDAPEST, ROAD);
    addLink(g, VIENNA, ZAGREB, ROAD);
    
    addLink(g, BUDAPEST, ZAGREB, ROAD);
    addLink(g, BUDAPEST, SZEGED, ROAD);
    addLink(g, BUDAPEST, SZEGED, RAIL);
    addLink(g, BUDAPEST, KLAUSENBURG, ROAD);
    
    addLink(g, KLAUSENBURG, CASTLE_DRACULA, ROAD);
    addLink(g, KLAUSENBURG, SZEGED, ROAD);
    addLink(g, KLAUSENBURG,BELGRADE, ROAD);
    addLink(g, KLAUSENBURG, GALATZ, ROAD);
    addLink(g, KLAUSENBURG, BUCHAREST, ROAD);
    
    addLink(g, GALATZ, CASTLE_DRACULA, ROAD);
    addLink(g, GALATZ, BUCHAREST, ROAD);
    addLink(g, GALATZ, BUCHAREST, RAIL);
    addLink(g, GALATZ, CONSTANTA, ROAD);
    
    addLink(g, CONSTANTA, BUCHAREST, ROAD);
    addLink(g, CONSTANTA, BUCHAREST, RAIL);
    addLink(g, CONSTANTA, VARNA, ROAD);
    addLink(g, CONSTANTA, VARNA, SEA);
    
    addLink(g, ZAGREB, SZEGED, ROAD);
    addLink(g, ZAGREB, SARAJEVO, ROAD);
    addLink(g, ZAGREB, ST_JOSEPH_AND_ST_MARYS, ROAD);

    addLink(g, ST_JOSEPH_AND_ST_MARYS, SZEGED, ROAD);
    addLink(g, ST_JOSEPH_AND_ST_MARYS, SARAJEVO, ROAD);
    addLink(g, ST_JOSEPH_AND_ST_MARYS, BELGRADE, ROAD);
    
    addLink(g, SZEGED, BELGRADE, ROAD);
    addLink(g, SZEGED, BELGRADE, RAIL);
    addLink(g, SZEGED, BUCHAREST, RAIL);
    
    addLink(g, BUCHAREST, BELGRADE, ROAD);
    addLink(g, BUCHAREST, SOFIA, ROAD);
    
    addLink(g, SARAJEVO, BELGRADE, ROAD);
    addLink(g, SARAJEVO, SOFIA, ROAD);
    addLink(g, SARAJEVO, VALONA, ROAD);
    
    addLink(g, BELGRADE, SOFIA, ROAD);
    addLink(g, BELGRADE, SOFIA, RAIL);
    
    addLink(g, SOFIA, VALONA, ROAD);
    addLink(g, SOFIA, VARNA, ROAD);
    addLink(g, SOFIA, VARNA, RAIL);
    addLink(g, SOFIA, SALONICA, RAIL);
    addLink(g, SOFIA, SALONICA, ROAD);
    
    addLink(g, VALONA, SALONICA, ROAD);
    addLink(g, VALONA, SALONICA, SEA);
    addLink(g, VALONA, ATHENS, SEA);
    addLink(g, VALONA, ATHENS,ROAD);
    
    addLink(g, ATHENS, SALONICA, SEA);
}

