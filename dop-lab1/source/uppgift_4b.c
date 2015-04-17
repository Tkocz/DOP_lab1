#include "lib/extgraph.h"
#include "lib/genlib.h"
#include "lib/mazelib.h"

static bool SolveMaze(pointT pt, int* num_calls, bool unmark)
{
    directionT dir;

    ++(*num_calls);

    if (OutsideMaze(pt))
        return (TRUE);

    if (IsMarked(pt))
        return (FALSE);

    MarkSquare(pt);

    for (dir = North; dir <= West; dir++) {
        // Om det är en vägg ivägen går vi vidare till nästa riktning.
        if (WallExists(pt, dir))
            continue;

        if (SolveMaze(AdjacentPoint(pt, dir), num_calls, unmark)) {
            // Vi måste avmarkera även här så att inte lösningen ligger kvar
            // som markerad i labyrinten.
            if (unmark)
                UnmarkSquare(pt);

            return (TRUE);
        }
    }

    if (unmark)
        UnmarkSquare(pt);

    return (FALSE);
}


void Uppgift4b() {
    int num_calls           = 0;
    int num_calls_no_unmark = 0;

    pointT start_pos = GetStartPosition();

    SetPauseTime(0.0);

    SolveMaze(start_pos, &num_calls          , TRUE);
    SolveMaze(start_pos, &num_calls_no_unmark, FALSE);

    printf("Uppgift 4a)\n\n");

    // Det första anropet är inte rekursivt (se labbspec), varför vi subtraherar
    // ett från variablerna.
    printf("Number of calls with unmark: %d\n"   , num_calls-1);
    printf("Number of calls WITHOUT unmark: %d\n", num_calls_no_unmark-1);
    printf("-------------------\n\n");

    system("pause");
    ExitGraphics();
}
