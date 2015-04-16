//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/genlib.h"
#include "lib/mazelib.h"
#include "lib/simpio.h"

//---------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------

/*--------------------------------------
 * Constant: NO_SOLUTION
 *
 * Description:
 *   Indikerar att ingen l�sning finns.
 *------------------------------------*/
#define NO_SOLUTION 10000

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: ShortestPathLength()
 * Parameters: pt  Den punkt utifr�n vilken vi vill finna l�ngden p� kortaste
 *                 l�sningen.
 *
 * Description:
 *   Returnerar l�ngden (i antal steg) p� den kortaste l�sningen f�r en
 *   labyrint.
 *------------------------------------*/
static int ShortestPathLength(pointT pt) {
    // Om vi �r utanf�r labyrinten har vi hittat en utg�ng och returnerar d�rmed
    // noll, vilket indikerar att vi �r klara.
    if (OutsideMaze(pt))
        return 0;

    // Vi vill inte bes�ka samma ruta flera g�nger. Vi l�ser detta genom att
    // returnera NO_SOLUTION, vilket ju �r ett h�gt v�rde, varf�r den v�gen
    // aldrig kan vara den kortaste.
    if (IsMarked(pt))
        return NO_SOLUTION;

    // Markera rutan f�r att f�rs�kra att vi inte g�r �ver den flera g�nger per
    // "s�kv�g."
    MarkSquare(pt);

    // Fr�n varje ruta kan vi g� �t fyra (egentligen tre eftersom vi kommer fr�n
    // ett h�ll) h�ll. Detta g�r vi dessutom rekursivt f�r att garanterat s�ka
    // igenom alla m�jliga v�gar som g�r att f�lja.
    int path0, path1, path2, path3;
    
    // Vi s�tter alla v�gar till NO_SOLUTION f�rst s� att vi vet att vi inte
    // funnit n�gon l�sning �n.
    path0 = path1 = path2 = path3 = NO_SOLUTION;

    // Vi provar de olika fyra riktningarna fr�n nuvarande ruta, men vi ser till
    // att vi bara g�r �t de h�ll som inte har en v�gg iv�gen (duh).

    // Vi provar att g� upp�t/norrut och g�r om alltihop d�rifr�n rekursivt...
    if (!WallExists(pt, North))
        path0 = ShortestPathLength(AdjacentPoint(pt, North));

    // Vi provar att g� h�ger/�sterut och g�r om alltihop d�rifr�n rekursivt...
    if (!WallExists(pt, East))
        path1 = ShortestPathLength(AdjacentPoint(pt, East));

    // Vi provar att g� ned�t/s�derut och g�r om alltihop d�rifr�n rekursivt...
    if (!WallExists(pt, South))
        path2 = ShortestPathLength(AdjacentPoint(pt, South));

    // Vi provar att g� v�nster/v�sterut och g�r om alltihop d�rifr�n
    // rekursivt...
    if (!WallExists(pt, West))
        path3 = ShortestPathLength(AdjacentPoint(pt, West));

    // Variabeln min_path anv�nder vi f�r att lagra den kortaste v�gen av de
    // fyra olika (rekursiva) riktningarna. Initialt NO_SOLUTION eftersom vi
    // inte har n�gon l�sning �nnu.
    int min_path = NO_SOLUTION;

    // H�r v�ljer vi ut v�rdet p� den kortaste v�gen (fr�n nuvarande ruta till
    // utg�ng) och returnerar det. Genom att g�ra det rekursivt f�r vi till slut
    // l�ngden p� den kortaste v�gen fr�n en given punkt till labyrintens
    // utg�ng. Vi plussar dessutom p� ett f�r att indikera att vi just tagit ett
    // steg.
    if (path0 < min_path) min_path = 1+path0;
    if (path1 < min_path) min_path = 1+path1;
    if (path2 < min_path) min_path = 1+path2;
    if (path3 < min_path) min_path = 1+path3;

    // Avmarkera rutan s� att vi kan korsa den igen.
    UnmarkSquare(pt);

    // Returnera v�rdet p� kortaste v�gen. Det kan ocks� vara s� att ingen
    // l�sning finns, varp� min_path h�r kommer att vara detsamma som
    // NO_SOLUTION.
    return min_path;
}

/*--------------------------------------
 * Function: Uppgift4a()
 * Parameters:
 *
 * Description:
 *   L�ser uppgift 4a.
 *------------------------------------*/
void Uppgift4a() {
    printf("Uppgift 4a)\n\n");
    printf("Would you like to speed up the process (for complex mazes)? ");
    string s = GetLine();

    if (s[0]=='Y' || s[0]=='y')
        SetPauseTime(0.0);

    FreeBlock(s);

    printf("Finding shortest path to exit...\n");

    int num_steps = ShortestPathLength(GetStartPosition());

    printf("Shortest path is %d steps.\n", num_steps);
    printf("-------------------\n\n");
}
