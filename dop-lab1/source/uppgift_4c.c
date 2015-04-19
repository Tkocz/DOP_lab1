//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/extgraph.h"
#include "lib/mazelib.h"

//---------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------

/*--------------------------------------
 * Constant: MAX_PATH
 *
 * Description:
 *   Max antal steg i en labyrintv�g.
 *------------------------------------*/
#define MAX_PATH 1024

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
 * Function: FindPath()
 * Parameters: pt             Den punkt utifr�n vilken vi vill finna en v�g ut
 *                            ur labyrinten.
 *             path           Den vektor som v�gen ska sparas i.
 *             max_path_size  Storleken p� path-vektorn.
 * Returns: Antal steg f�r den l�sning som sparades i path.
 *
 * Description:
 *   Returnerar l�ngden (i antal steg) p� en v�g ut ur labyrinten.
 *------------------------------------*/
static int FindPath(pointT pt, pointT path[], int max_path_size) {
    // Om det inte finns plats att lagra mer data i vektorn s� f�r vi helt
    // enkelt acceptera att vi inte kan l�sa labyrinten denna v�gen.
    if (max_path_size <= 0)
        return NO_SOLUTION;

    // Om vi �r utanf�r labyrinten har vi hittat en l�sning. Vi sparar den
    // punkten som en l�sning, s� att vi f�r med steget ut ur labyrinten som
    // en del av l�sningen.
    if (OutsideMaze(pt)) {
        path[0] = pt;
        return 1;
    }

    // Vi har korsat v�r egen v�g, vilket ju inte �r en riktig l�sning.
    if (IsMarked(pt))
        return NO_SOLUTION;

    // Markera rutan som bes�kt.
    MarkSquare(pt);

    for (directionT dir = North; dir <= West; dir++) {
        // Om det �r en v�gg iv�gen g�r vi vidare till n�sta riktning.
        if (WallExists(pt, dir))
            continue;

        // Om length==NO_SOLUTION inneb�r det att ingen l�sning finns genom den
        // riktningen som dir pekar �t. D� g�r vi vidare och provar n�sta.
        //     N�r vi anropar FindPath �kar vi path-pekaren med ett, och minskar
        // max_path_size med ett. Detta g�r att de rekursiva anropen f�r en
        // pekare till ett slags "subvektor" av path, vilket g�r att vi slipper
        // h�lla reda p� index i path, utan ist�llet bara jobbar med path[0].
        int length = FindPath(AdjacentPoint(pt, dir), path+1, max_path_size-1);
        if (length != NO_SOLUTION) {
            path[0] = pt;
            return 1+length;
        }
    }

    // "I den h�r uppgiften kommer vi inte att avmarkera rutorna utan ist�llet
    // h�lla reda p� v�gen explicit i ett f�lt s� att vi v�gen finns sparad d�
    // algoritmen terminerar"
    // ...ok, d� g�r vi v�l s�... ingen vet varf�r, men men...
    //UnmarkSquare(pt);

    return NO_SOLUTION;
}

/*--------------------------------------
 * Function: PrintDirections()
 * Parameters: path    En vektor inneh�llade l�sningen.
 *             length  Antal steg i path-vektorn.
 *
 * Description:
 *   Skriver ut labyrintl�sningen.
 *------------------------------------*/
static void PrintDirections(pointT path[], int length) {
    // Det h�r �r ju ett uselt s�tt att beskriva v�gen ut, vi hittar p�
    // n�got b�ttre ist�llet.

    /*printf("The following path is a solution:\n");
    for (int i = 0; i < length; i++) {
        printf(" (%d, %d)\n", path[i].x, path[i].y);
    }*/

    // F�ljande tycker vi �r b�ttre och roligare. :-)

    // Variabeln count h�ller reda p� hur m�nga steg i samma riktning vi g�tt,
    // och last_dir h�ller reda p� vilken riktning vi gick f�reg�ende steg.
    // P� s� vis kan vi v�lja att skriva ut antal steg i varje riktning.
    int    count    = 0;
    string last_dir = "";

    printf("Follow these directions to solve the maze:\n\n");
    for (int i = 1; i < length; i++) {
        pointT a = path[i-1],
               b = path[i];

        string dir = "";

        // Genom att j�mf�ra positionsskillnaderna mellan f�reg�ende och
        // nuvarande punkt kan vi lista ut vilken riktning vi ska g� mot.
             if (b.y == (a.y+1)) dir = "north";
        else if (b.y == (a.y-1)) dir = "south";
        else if (b.x == (a.x+1)) dir = "east";
        else                     dir = "west";

        // Det �r ok att anv�nda == f�r att j�mf�ra str�ngarna h�r eftersom de
        // garanterat pekar till samma minnesadresser om de �r ekvivalenta. Vi
        // testar dessutom f�r i==1 eftersom vi alltid vill r�kna upp den f�rsta
        // riktningen vi g�r �t, inte skriva ut den.
        if (i == 1 || dir == last_dir) {
            count++;
        }
        else {
            if (count <= 1) printf("  %s\n", last_dir);
            else            printf("  %d steps %s\n", count, last_dir);

            count = 1;
        }

        last_dir = dir;
    }

    if (count <= 1) printf("  %s\n", last_dir);
    else            printf("  %d steps %s\n", count, last_dir);

    printf("\n");
}

/*--------------------------------------
 * Function: Uppgift4c()
 * Parameters:
 *
 * Description:
 *   L�ser uppgift 4c.
 *------------------------------------*/
void Uppgift4c() {
    pointT path[MAX_PATH];

    printf("Uppgift 4c)\n\n");

    int length = FindPath(GetStartPosition(), path, MAX_PATH);
    if (length == 0)
        printf("No solution exists.\n");
    else
        PrintDirections(path, length);

    printf("-------------------\n\n");

    system("pause");
    ExitGraphics();
}
