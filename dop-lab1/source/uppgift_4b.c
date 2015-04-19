//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/extgraph.h"
#include "lib/genlib.h"
#include "lib/mazelib.h"

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: SolveMaze()
 * Parameters: pt         Den punkt utifrån vilken vi vill lösa labyrinten.
 *             num_calls  Räknare för antal anrop.
 *             unmark     Indikerar huruvida UnmarkSquare()-funktionen ska
 *                        anropas.
 *
 * Description:
 *   Löser labyrinten (om möjligt) och räknar antalet anrop.
 *------------------------------------*/
static bool SolveMaze(pointT pt, int* num_calls, bool unmark) {
    ++(*num_calls);

    if (OutsideMaze(pt))
        return TRUE;

    if (IsMarked(pt))
        return FALSE;

    MarkSquare(pt);

    for (directionT dir = North; dir <= West; dir++) {
        // Om det är en vägg ivägen går vi vidare till nästa riktning.
        if (WallExists(pt, dir))
            continue;

        if (SolveMaze(AdjacentPoint(pt, dir), num_calls, unmark)) {
            // Vi måste avmarkera även här så att inte lösningen ligger kvar
            // som markerad i labyrinten.
            if (unmark)
                UnmarkSquare(pt);

            return TRUE;
        }
    }

    if (unmark)
        UnmarkSquare(pt);

    return FALSE;
}

/*--------------------------------------
 * Function: Uppgift4b()
 * Parameters:
 *
 * Description:
 *   Löser uppgift 4b.
 *------------------------------------*/
void Uppgift4b() {
    int num_calls           = 0;
    int num_calls_no_unmark = 0;

    pointT start_pos = GetStartPosition();

    SetPauseTime(0.0);

    SolveMaze(start_pos, &num_calls          , TRUE);
    SolveMaze(start_pos, &num_calls_no_unmark, FALSE);

    printf("Uppgift 4b)\n\n");

    // Det första anropet är inte rekursivt (se labbspec), varför vi subtraherar
    // ett från variablerna.
    printf("Number of calls with unmark: %d\n"   , num_calls-1);
    printf("Number of calls WITHOUT unmark: %d\n", num_calls_no_unmark-1);
    printf("-------------------\n\n");

    system("pause");
    ExitGraphics();
}
