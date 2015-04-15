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

main() {
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
}
