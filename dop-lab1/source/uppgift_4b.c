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
 * Parameters: pt         Den punkt utifr�n vilken vi vill l�sa labyrinten.
 *             num_calls  R�knare f�r antal anrop.
 *             unmark     Indikerar huruvida UnmarkSquare()-funktionen ska
 *                        anropas.
 *
 * Description:
 *   L�ser labyrinten (om m�jligt) och r�knar antalet anrop.
 *------------------------------------*/
static bool SolveMaze(pointT pt, int* num_calls, bool unmark) {
    ++(*num_calls);

    if (OutsideMaze(pt))
        return TRUE;

    if (IsMarked(pt))
        return FALSE;

    MarkSquare(pt);

    for (directionT dir = North; dir <= West; dir++) {
        // Om det �r en v�gg iv�gen g�r vi vidare till n�sta riktning.
        if (WallExists(pt, dir))
            continue;

        if (SolveMaze(AdjacentPoint(pt, dir), num_calls, unmark)) {
            // Vi m�ste avmarkera �ven h�r s� att inte l�sningen ligger kvar
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
 *   L�ser uppgift 4b.
 *------------------------------------*/
void Uppgift4b() {
    int num_calls           = 0;
    int num_calls_no_unmark = 0;

    pointT start_pos = GetStartPosition();

    SetPauseTime(0.0);

    SolveMaze(start_pos, &num_calls          , TRUE);
    SolveMaze(start_pos, &num_calls_no_unmark, FALSE);

    printf("Uppgift 4b)\n\n");

    // Det f�rsta anropet �r inte rekursivt (se labbspec), varf�r vi subtraherar
    // ett fr�n variablerna.
    printf("Number of calls with unmark: %d\n"   , num_calls-1);
    printf("Number of calls WITHOUT unmark: %d\n", num_calls_no_unmark-1);
    printf("-------------------\n\n");

    system("pause");
    ExitGraphics();
}
