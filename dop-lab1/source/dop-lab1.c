#include "lib/genlib.h"
#include "lib/simpio.h"

#include <stdio.h>
#include <stdlib.h>

extern Uppgift1();
extern Uppgift2();
extern Uppgift3();
extern Uppgift4();

main() {
    printf("Select assignment (1 through 4, exit with 0)\n");
    while (TRUE){
        switch (GetInteger()){
        //case 1: Uppgift1();
        case 2: Uppgift2(); break;
        case 3: Uppgift3(); break;
        case 4: Uppgift4(); break;
        default: return;
        case 0: return(FALSE);
        }
    }
}
