//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/genlib.h"
#include "lib/simpio.h"

#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------

/*--------------------------------------
 * Constants: MAX_WEIGHTS
 *
 * Description:
 *   Max antal tyngder.
 *------------------------------------*/
#define MAX_WEIGHTS 10

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: IsMeasurable()
 * Parameters: target       Målvikten som ska "motvägas."
 *             weights      En vektor innehållandes alla tyngder.
 *             num_weights  Antalet tyngder i weights-vektorn.
 *
 * Description:
 *   Låter användaren skriva in ett heltal.
 *------------------------------------*/
bool IsMeasurable(int target, int weights[], int num_weights) {
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

    // Vi kan nu göra tre val:
    //   1. Använd inte tyngden alls.
    //   2. Använd tyngden som motvikt.
    //   3. Använd tyngden som medvikt.
    //
    // Vi vill testa alla möjliga kombinationer, så vi utför alla tre val
    // rekursivt nedan.

    return IsMeasurable(target    , weights, i)  // Utan tyngden.
        || IsMeasurable(target - w, weights, i)  // Motvikt.
        || IsMeasurable(target + w, weights, i); // Medvikt.
}

/*--------------------------------------
 * Function: Uppgift2()
 * Parameters:
 *
 * Description:
 *   Programmets huvudfunktion (avseende uppgift 2).
 *------------------------------------*/
void Uppgift2() {
    int weights[MAX_WEIGHTS] = { 0 };
    int num_weights = MAX_WEIGHTS;

    printf("Enter desired weightstones (Max is %d), end with 0\n", MAX_WEIGHTS);

    for (int i = 0; i < 10; i++){
        weights[i] = GetInteger();
        if (weights[i] <= 0) {
            num_weights = i;
            break;
        }
    }

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
