#include <stdlib.h>
#include <assert.h>
#include "game.h"
#include "HunterView.h"
#include <stdio.h>
#include <string.h>
#include "Graph.h"

//Add the next item to a hunter or dracula's trail
static void updateTrail (HunterView h);
//implement turn using the information from play
static void update(HunterView hunterView, char *play);


struct hunterView {
    int curPlayer; //Player whose turn it is
    int round; //Round number
    int score; //Game score
    int hp[5]; //The hunters health and dracula's blood points
    char trails[5][TRAIL_SIZE];
    int playerLocations[5]; //Location of all 5 players
    LocationID playerLocation; //Location of current player
    Graph map; //The graph of the map
};


HunterView newHunterView( char *pastPlays, playerMessage messages[] ) {
    HunterView hunterView = malloc( sizeof( struct hunterView ) );
   
    int i1 = 0;
    int i2 = 0;
    int pos = 0;
    int turnCount = 0;
    int i, j;
    char play[8];
    play[7] = '\0';
    
    //Put the initial values into the hunterView adt
    hunterView->curPlayer = 0;
    hunterView->round = 0;
    hunterView->score = GAME_START_SCORE;
    
    hunterView->hp[0] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[1] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[2] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[3] = GAME_START_HUNTER_LIFE_POINTS;
    hunterView->hp[4] = GAME_START_BLOOD_POINTS;
    
    hunterView->playerLocations[0] = UNKNOWN_LOCATION;
    hunterView->playerLocations[1] = UNKNOWN_LOCATION;
    hunterView->playerLocations[2] = UNKNOWN_LOCATION;
    hunterView->playerLocations[3] = UNKNOWN_LOCATION;
    hunterView->playerLocations[4] = UNKNOWN_LOCATION;
    
    for (i = 0; i < 5; i ++) {
        for (j = 0; j < TRAIL_SIZE; j ++) {
            hunterView->trails[i][j] = UNKNOWN_LOCATION;
        }
    }
    
    //Store each characters information in a play
    //A wrapper for updating the hunterView
    while (pastPlays[pos] != '\0')  {
        //Build the string with the player info for this turn
        play[i2] = pastPlays[pos];
        if (i2 == 6) {
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
    
    if (play[0] == 'G') character = 0;
    if (play[0] == 'S') character = 1;
    if (play[0] == 'H') character = 2;
    if (play[0] == 'M') character = 3;
    if (play[0] == 'D') character = 4;

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
    
    //A special case if the player is Dracula
    if (strcmp(city,"CD") == 0) {
    
        hunterView->playerLocations[character] = 13;
        if (hunterView->curPlayer == PLAYER_DRACULA) {
            hunterView->hp[PLAYER_DRACULA] += 10;
        }
    }
    
    //Set the players new location
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

    
    //Dracula locations
    if (strcmp(city,"C?") == 0) hunterView->playerLocations[character] = 71;
    //Another special case if Dracula goes to sea
    if (strcmp(city,"S?") == 0) {
        hunterView->playerLocations[character] = 72;
        hunterView->hp[PLAYER_DRACULA] -= 2;
    }
    
    if (strcmp(city,"HI") == 0) hunterView->playerLocations[character] = 73;
    if (city[0] == 'D') hunterView->playerLocations[character] = 73 + (int)city[1] - '0';
    
    if (strcmp(city,"TP") == 0) {
        hunterView->playerLocations[character] = 79;
        hunterView->hp[4] += 10;
    }
    
    //Sea locations
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

    
    //Look at the remaining 4 indexes in the play array

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
                printf("trap\n");
                hunterView->hp[character] -= 2;
            } else if (event == 'V') {
                //immature vampire is vanquished
                
                //Add this location to Dracula's trail
                hunterView->trails[PLAYER_DRACULA][hunterView->round%13] = hunterView->playerLocations[character];
                
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
    *numLocations = 0;
    //Get the list corresponding to the given start location
    VList v = currentView->map->connections[from];

    //A buffer for the result
    int buffer[64] = {-1};
    buffer[0] = from;
    int array[NUM_LOCATIONS] = {0};
    int i;
    int index = 1;
    int numLocs = 1;
    int count;
    int seen = 0;
    
    if (rail) {
        //Dracula cannot travel by rail
        if (player != PLAYER_DRACULA) {
            //The number of cities transversable in one turn depends on the round
            canReachInN(currentView->map, from, RAIL, currentView->round%4, array);
            
            //Already added this one
            array[from] = 0;
            for (i = 0; i < NUM_LOCATIONS; i ++) {
                if (array[i]) {
                    numLocs ++;
                    buffer[index] = i;
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
                    //We need to make sure that the location has not already been added
                    if (!array[v->v]) {
                        buffer[index] = v->v;
                        index ++;
                        numLocs ++;
                    }
                }
            }
        }

        
        if (sea) {
            if (v->type == SEA) {
                //Make sure the location has not been added due to rail
                if (!array[v->v]) {
                    //We need to make sure that the location has not already been added
                    for (count = 0; count < 64; count ++) {
                        //If we find it in the buffer don't add it to the array
                        if (buffer[count] == v->v) seen = 1;
                    }
                    if (!seen) {
                        buffer[index] = v->v;
                        index ++;
                        numLocs ++;
                    } else {
                        //reset seen for next pass
                        seen = 0;
                    }
                }
            }
        }
        v = v->next;
    }
    
    //Allocate memory for the results
    LocationID * locs = malloc(numLocs*sizeof(LocationID));
    
    //Store the number of results in numlocs
    *numLocations = numLocs;
    
    //Tansfer from the buffer to locs
    for (i = 0; i < numLocs; i ++) {
        locs[i] = buffer[i];
    }
    return locs;
}

