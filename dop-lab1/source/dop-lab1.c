//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/genlib.h"
#include "lib/simpio.h"

#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// EXTERNS
//---------------------------------------------------------

extern Uppgift1();
extern Uppgift2();
extern Uppgift3();
extern Uppgift4();

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: main()
 * Parameters:
 *
 * Description:
 *   Programmets huvudfunktion.
 *------------------------------------*/
main() {
    // Vi har valt at INTE dela upp VS-l�sningen i flera olika projekt, utan
    // ist�llet implementerat ett menysystem d�r anv�ndaren f�r v�lja den
    // uppgift vars l�sning ska granskas.

    printf("S133686 (Philip Arvidsson) & S141564 (Martin Bergqvist)\n\n");
    printf("Select assignment (1 through 4, exit with 0)\n");

    while (TRUE) {
        switch (GetInteger()) {

        case 1: Uppgift1(); return;
        case 2: Uppgift2(); return;
        case 3: Uppgift3(); return;
        case 4: Uppgift4(); return;

        default: printf("Invalid choice. Try again.\n"); break;

        case 0: return;
        }
    }

    // -
}
