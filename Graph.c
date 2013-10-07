#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "cities.h"


static VList addtoList (Graph g, VList v, Location loca, Transport type);


Graph newGraph() { 
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

void destroyGraph(Graph g){
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




void addLink(Graph g, Location start, Location end, Transport type){
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

void canReachInN(Graph g, Location start, Transport type, int n, int locs[]) {

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
void makeMap(Graph g){
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
