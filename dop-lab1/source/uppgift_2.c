//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// TYPES
//---------------------------------------------------------

typedef enum { FALSE, TRUE } Bool;//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------
main() {
    // Tyngderna vi ska prova med.
    int weights[]   = { 1, 15, 20 };

    // Antalet tyngder.
    int num_weights = sizeof(weights) / sizeof(int);

    // Totalvikten så vet vi maxvikten vi kan väga upp mot.
    int total_weight = 0;

    // Räkna ut totalvikt.
    for (int i = 0; i < num_weights; i++)
        total_weight += weights[i];

    // Prova alla vikter upp till och med totalvikten.
    for (int i = 0; i <= total_weight; i++) {
        if (IsMeasurable(i, weights, num_weights))
            printf("%d is measurable.\n", i);
        else
            printf("%d is NOT measurable.\n", i);
    }

    // Klart! :-)

    printf("No weights above %d are measurable.\n", total_weight);
    system("pause");
}

/*------------------------------------------------
* FUNCTIONS
*----------------------------------------------*/

/*--------------------------------------
* Function: GetIntFromUser()
* Parameters:
*
* Description:
*   Låter användaren skriva in ett heltal.
*------------------------------------*/
int GetIntFromUser() {
    char buf[16];
    Bool is_valid_int = FALSE;

    while (!is_valid_int) {
        fgets(buf, sizeof(buf), stdin);

        int len = strlen(buf);

        is_valid_int = TRUE;
        for (int i = 0; i < len; i++) {
            char c = buf[i];

            if (c == '\r' || c == '\n') {
                buf[i] = '\0';
                break;
            }

            if (!isdigit(c)) {
                is_valid_int = FALSE;
                break;
            }
        }

        if (strlen(buf) == 0)
            is_valid_int = FALSE;

        if (!is_valid_int)
            printf("Invalid integer. Try again: ");
    }

    return atoi(buf);
}

Bool IsMeasurable(int target, int weights[], int num_weights) {
    // Vi har lyckats nå målvikten med en kombination av tyngder, vilket innebär
    // att den går att balansera ut mot de tyngder vi har.
    if (target == 0)
        return TRUE;

    // Vi har provat alla tyngder utan att nå målvikten, alltså kan vi inte väga
    // upp mot den.
    if (num_weights == 0)
        return FALSE;

    // Vi använder den sista tyngden som vi har och "plockar bort" den.
    int i = num_weights - 1;

    // Vikten på den tyngd vi ska prova med nu.
    int w = weights[i];

    return IsMeasurable(target    , weights, i)  // Utan tyngden.
        || IsMeasurable(target - w, weights, i)  // Motvikt.
        || IsMeasurable(target + w, weights, i); // Medvikt.
}
