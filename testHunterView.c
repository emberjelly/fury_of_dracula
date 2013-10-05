#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "cities.h"
#include "game.h"
#include "HunterView.h"


int main(int argc, char * argv[]) { 
    playerMessage messages[] = {};
    
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
    hv = newHunterView("BAL.... SAL.... HAL....", messages);
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
    
    hv = newHunterView("BAL.... SED.... HBE.... MLI.... DC?V...", messages);
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
    
    return 0;



/*    
#define PLAYER_LORD_GODALMING   0
#define PLAYER_DR_SEWARD        1
#define PLAYER_VAN_HELSING      2
#define PLAYER_MINA_HARKER      3
#define PLAYER_DRACULA          4
*/

}

