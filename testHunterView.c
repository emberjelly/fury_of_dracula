#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "cities.h"
#include "game.h"
#include "HunterView.h"


int main(int argc, char * argv[]) { 
    playerMessage messages[] = {};
    int trail[TRAIL_SIZE];
    
    int i;
    int j;
    int numLocations[1];
    numLocations[0] = -1;
    
    printf("Test 1\n");
    printf("Test basic empty initialisation\n");
    HunterView hv = newHunterView("", messages);
    assert(getCurrentPlayer(hv) == PLAYER_LORD_GODALMING);
    assert(getRound(hv) == 0);
    assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(getScore(hv) == GAME_START_SCORE);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == UNKNOWN_LOCATION);
        
    disposeHunterView(hv);
    printf("passed\n");
    
    printf("Test 2\n");
    printf("Testing a hunter view 3 turns into a game\n");
    hv = newHunterView("GAL.... SAL.... HAL....", messages);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == ALICANTE);
    assert(getLocation(hv,PLAYER_DR_SEWARD) == ALICANTE);
    assert(getLocation(hv,PLAYER_VAN_HELSING) == ALICANTE);
    assert(getCurrentPlayer(hv) == PLAYER_MINA_HARKER);
    assert(getRound(hv) == 0);
    assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(getScore(hv) == GAME_START_SCORE);
    
    disposeHunterView(hv);
    printf("Passed\n");
    
    printf("Test 3\n");
    printf("Testing a hunter view at the end of round 1\n");
    
    hv = newHunterView("GAL.... SED.... HBE.... MLI.... DC?V...", messages);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == ALICANTE);
    assert(getLocation(hv,PLAYER_DR_SEWARD) == EDINBURGH);
    assert(getLocation(hv,PLAYER_VAN_HELSING) == BELGRADE);
    assert(getLocation(hv,PLAYER_MINA_HARKER) == LEIPZIG);
    assert(getLocation(hv,PLAYER_DRACULA) == CITY_UNKNOWN);
    assert(getCurrentPlayer(hv) == PLAYER_LORD_GODALMING);
    assert(getRound(hv) == 1);
    assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(getScore(hv) == 365);
    printf("Testing getHistory\n");
    

    for (j = 0; j < 5; j ++) {
    
        getHistory(hv, j, trail);
        for (i = 0; i < TRAIL_SIZE; i ++) {
            printf("%d ", trail[i]);
        }
        printf("\n\n");
    }
    disposeHunterView(hv);
    printf("Passed\n");
    
    printf("Test 4\n");
    printf("Testing a hunter view at the end of round 2\n");
    
    hv = newHunterView("GAL.... SED.... HBE.... MLI.... DC?V... GVE.... SBE.... HED.... MAL.... DS?V...", messages);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == VENICE);
    assert(getLocation(hv,PLAYER_DR_SEWARD) == BELGRADE);
    assert(getLocation(hv,PLAYER_VAN_HELSING) == EDINBURGH);
    assert(getLocation(hv,PLAYER_MINA_HARKER) == ALICANTE);
    assert(getLocation(hv,PLAYER_DRACULA) == SEA_UNKNOWN);
    assert(getCurrentPlayer(hv) == 0);
    assert(getRound(hv) == 2);
    assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 2);
    assert(getScore(hv) == 364);
    
    printf("Testing connected Locations\n");
    LocationID* locs;
    locs = connectedLocations(hv, numLocations, EDINBURGH, 0, getRound(hv), 1, 1, 1);
    printf("The number locations connected to EDINBURGH is %d\n", numLocations[0]);
    
    for (i = 0; i < numLocations[0]; i ++) {
        printf("%d\n", locs[i]);
    }

    
    printf("\nTesting getHistory\n");
    
    for (j = 0; j < 5; j ++) {
    
        getHistory(hv, j, trail);
        for (i = 0; i < TRAIL_SIZE; i ++) {
            printf("%d ", trail[i]);
        }
        printf("\n\n");
    }
    
    free (locs);
    disposeHunterView(hv);
    printf("Passed\n");

    printf("Test 5\n");
    printf("Testing a game 14 rounds in\n");
    printf("During this round there were:\n");
    printf("four traps encountered\n");
    printf("One matured vampire\n");
    printf("One encounter with dracula by PLAYER_LORD_GODALMING\n");
    
    hv = newHunterView(
    "GAL.... SED.... HBE.... MLI.... DC?.V.. GVE.... SBE.... HED.... MAL.... DS?T... GAL.... SED.... HBE.... MLI.... DC?V... GVE.... SBE.... HED.... MAL.... DS?T... GAL.... SED.... HBE.... MLI.... DC?T... GVE.... SBE.... HED.... MAL.... DS?T... GAL.... SED.... HBE.... MLI.... DC?T... GVE.... SBE.... HED.... MAL.... DS?T... GAL.... SED.... HBE.... MLI.... DC?T... GVE.... SBE.... HED.... MAL.... DS?T... GAL.... SED.... HBE.... MLI.... DC?V... GVE.... SBE.... HED.... MAL.... DS?V... GAL.... SED.... HBE.... MLI.... DC?T... GVED... SBE.... HED.... MALV... DS?T.V.", messages);


    assert(getLocation(hv,PLAYER_LORD_GODALMING) == VENICE);
    assert(getLocation(hv,PLAYER_DR_SEWARD) == BELGRADE);
    assert(getLocation(hv,PLAYER_VAN_HELSING) == EDINBURGH);
    assert(getLocation(hv,PLAYER_MINA_HARKER) == ALICANTE);
    assert(getLocation(hv,PLAYER_DRACULA) == SEA_UNKNOWN);
    assert(getCurrentPlayer(hv) == 0);
    assert(getRound(hv) == 14);
    printf("%d\n", getHealth(hv, PLAYER_LORD_GODALMING));
    assert(getHealth(hv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS - 4);
    assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 14 - 10);
    assert(getScore(hv) == 366 - 14 - 13);
    printf("Passed\n");
    printf("Testing getHistory\n\n");
    for (j = 0; j < 5; j ++) {
    
        getHistory(hv, j, trail);
        for (i = 0; i < TRAIL_SIZE; i ++) {
            printf("%d ", trail[i]);
        }
        printf("\n\n");
    }
    //free (locs);
    disposeHunterView(hv);
    return 0;



/*    
#define PLAYER_LORD_GODALMING   0
#define PLAYER_DR_SEWARD        1
#define PLAYER_VAN_HELSING      2
#define PLAYER_MINA_HARKER      3
#define PLAYER_DRACULA          4
*/

}

