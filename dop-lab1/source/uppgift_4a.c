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
 *   Indikerar att ingen lösning finns.
 *------------------------------------*/
#define NO_SOLUTION 10000

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: ShortestPathLength()
 * Parameters: pt  Den punkt utifrån vilken vi vill finna längden på kortaste
 *                 lösningen.
 *
 * Description:
 *   Returnerar längden (i antal steg) på den kortaste lösningen för en
 *   labyrint.
 *------------------------------------*/
static int ShortestPathLength(pointT pt) {
    // Om vi är utanför labyrinten har vi hittat en utgång och returnerar därmed
    // noll, vilket indikerar att vi är klara.
    if (OutsideMaze(pt))
        return 0;

    // Vi vill inte besöka samma ruta flera gånger. Vi löser detta genom att
    // returnera NO_SOLUTION, vilket ju är ett högt värde, varför den vägen
    // aldrig kan vara den kortaste.
    if (IsMarked(pt))
        return NO_SOLUTION;

    // Markera rutan för att försäkra att vi inte går över den flera gånger per
    // "sökväg."
    MarkSquare(pt);

    // Från varje ruta kan vi gå åt fyra (egentligen tre eftersom vi kommer från
    // ett håll) håll. Detta gör vi dessutom rekursivt för att garanterat söka
    // igenom alla möjliga vägar som går att följa.
    int path0, path1, path2, path3;
    
    // Vi sätter alla vägar till NO_SOLUTION först så att vi vet att vi inte
    // funnit någon lösning än.
    path0 = path1 = path2 = path3 = NO_SOLUTION;

    // Vi provar de olika fyra riktningarna från nuvarande ruta, men vi ser till
    // att vi bara går åt de håll som inte har en vägg ivägen (duh).

    // Vi provar att gå uppåt/norrut och gör om alltihop därifrån rekursivt...
    if (!WallExists(pt, North))
        path0 = ShortestPathLength(AdjacentPoint(pt, North));

    // Vi provar att gå höger/österut och gör om alltihop därifrån rekursivt...
    if (!WallExists(pt, East))
        path1 = ShortestPathLength(AdjacentPoint(pt, East));

    // Vi provar att gå nedåt/söderut och gör om alltihop därifrån rekursivt...
    if (!WallExists(pt, South))
        path2 = ShortestPathLength(AdjacentPoint(pt, South));

    // Vi provar att gå vänster/västerut och gör om alltihop därifrån
    // rekursivt...
    if (!WallExists(pt, West))
        path3 = ShortestPathLength(AdjacentPoint(pt, West));

    // Variabeln min_path använder vi för att lagra den kortaste vägen av de
    // fyra olika (rekursiva) riktningarna. Initialt NO_SOLUTION eftersom vi
    // inte har någon lösning ännu.
    int min_path = NO_SOLUTION;

    // Här väljer vi ut värdet på den kortaste vägen (från nuvarande ruta till
    // utgång) och returnerar det. Genom att göra det rekursivt får vi till slut
    // längden på den kortaste vägen från en given punkt till labyrintens
    // utgång. Vi plussar dessutom på ett för att indikera att vi just tagit ett
    // steg.
    if (path0 < min_path) min_path = 1+path0;
    if (path1 < min_path) min_path = 1+path1;
    if (path2 < min_path) min_path = 1+path2;
    if (path3 < min_path) min_path = 1+path3;

    // Avmarkera rutan så att vi kan korsa den igen.
    UnmarkSquare(pt);

    // Returnera värdet på kortaste vägen. Det kan också vara så att ingen
    // lösning finns, varpå min_path här kommer att vara detsamma som
    // NO_SOLUTION.
    return min_path;
}

/*--------------------------------------
 * Function: Uppgift4a()
 * Parameters:
 *
 * Description:
 *   Löser uppgift 4a.
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
