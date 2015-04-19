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
 *   Max antal steg i en labyrintväg.
 *------------------------------------*/
#define MAX_PATH 1024

/*--------------------------------------
 * Constant: NO_SOLUTION
 *
 * Description:
 *   Indikerar att ingen lösning finns.
 *------------------------------------*/
#define NO_SOLUTION 10000

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: FindPath()
 * Parameters: pt             Den punkt utifrån vilken vi vill finna en väg ut
 *                            ur labyrinten.
 *             path           Den vektor som vägen ska sparas i.
 *             max_path_size  Storleken på path-vektorn.
 * Returns: Antal steg för den lösning som sparades i path.
 *
 * Description:
 *   Returnerar längden (i antal steg) på en väg ut ur labyrinten.
 *------------------------------------*/
static int FindPath(pointT pt, pointT path[], int max_path_size) {
    // Om det inte finns plats att lagra mer data i vektorn så får vi helt
    // enkelt acceptera att vi inte kan lösa labyrinten denna vägen.
    if (max_path_size <= 0)
        return NO_SOLUTION;

    // Om vi är utanför labyrinten har vi hittat en lösning. Vi sparar den
    // punkten som en lösning, så att vi får med steget ut ur labyrinten som
    // en del av lösningen.
    if (OutsideMaze(pt)) {
        path[0] = pt;
        return 1;
    }

    // Vi har korsat vår egen väg, vilket ju inte är en riktig lösning.
    if (IsMarked(pt))
        return NO_SOLUTION;

    // Markera rutan som besökt.
    MarkSquare(pt);

    for (directionT dir = North; dir <= West; dir++) {
        // Om det är en vägg ivägen går vi vidare till nästa riktning.
        if (WallExists(pt, dir))
            continue;

        // Om length==NO_SOLUTION innebär det att ingen lösning finns genom den
        // riktningen som dir pekar åt. Då går vi vidare och provar nästa.
        //     När vi anropar FindPath ökar vi path-pekaren med ett, och minskar
        // max_path_size med ett. Detta gör att de rekursiva anropen får en
        // pekare till ett slags "subvektor" av path, vilket gör att vi slipper
        // hålla reda på index i path, utan istället bara jobbar med path[0].
        int length = FindPath(AdjacentPoint(pt, dir), path+1, max_path_size-1);
        if (length != NO_SOLUTION) {
            path[0] = pt;
            return 1+length;
        }
    }

    // "I den här uppgiften kommer vi inte att avmarkera rutorna utan istället
    // hålla reda på vägen explicit i ett fält så att vi vägen finns sparad då
    // algoritmen terminerar"
    // ...ok, då gör vi väl så... ingen vet varför, men men...
    //UnmarkSquare(pt);

    return NO_SOLUTION;
}

/*--------------------------------------
 * Function: PrintDirections()
 * Parameters: path    En vektor innehållade lösningen.
 *             length  Antal steg i path-vektorn.
 *
 * Description:
 *   Skriver ut labyrintlösningen.
 *------------------------------------*/
static void PrintDirections(pointT path[], int length) {
    // Det här är ju ett uselt sätt att beskriva vägen ut, vi hittar på
    // något bättre istället.

    /*printf("The following path is a solution:\n");
    for (int i = 0; i < length; i++) {
        printf(" (%d, %d)\n", path[i].x, path[i].y);
    }*/

    // Följande tycker vi är bättre och roligare. :-)

    // Variabeln count håller reda på hur många steg i samma riktning vi gått,
    // och last_dir håller reda på vilken riktning vi gick föregående steg.
    // På så vis kan vi välja att skriva ut antal steg i varje riktning.
    int    count    = 0;
    string last_dir = "";

    printf("Follow these directions to solve the maze:\n\n");
    for (int i = 1; i < length; i++) {
        pointT a = path[i-1],
               b = path[i];

        string dir = "";

        // Genom att jämföra positionsskillnaderna mellan föregående och
        // nuvarande punkt kan vi lista ut vilken riktning vi ska gå mot.
             if (b.y == (a.y+1)) dir = "north";
        else if (b.y == (a.y-1)) dir = "south";
        else if (b.x == (a.x+1)) dir = "east";
        else                     dir = "west";

        // Det är ok att använda == för att jämföra strängarna här eftersom de
        // garanterat pekar till samma minnesadresser om de är ekvivalenta. Vi
        // testar dessutom för i==1 eftersom vi alltid vill räkna upp den första
        // riktningen vi går åt, inte skriva ut den.
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
 *   Löser uppgift 4c.
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
