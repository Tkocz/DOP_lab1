//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include <stdio.h>

//---------------------------------------------------------
// TYPES
//---------------------------------------------------------

typedef enum { FALSE, TRUE } Bool;//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------
main() {
    int weights[] = { 1, 15, 20 };
    int num_weights = sizeof(weights) / sizeof(int);
    int total_weight = 0;

    for (int i = 0; i < num_weights; i++)
        total_weight += weights[i];

    for (int i = 0; i <= total_weight; i++) {
        Bool im = IsMeasurable(i, weights, num_weights);

        if (im)
            printf("%d is measurable\n", i);
        else
            printf("%d is NOT measurable\n", i);
    }

    printf("No weights above %d are measurable.\n", total_weight);

    system("pause");

}

Bool IsMeasurable(int target, int weights[], int num_weights) {
    // Vi har lyckats n� m�lvikten med en kombination av tyngder, vilket inneb�r
    // att den g�r att balansera ut mot de tyngder vi har.
    if (target == 0)
        return TRUE;

    // Vi har provat alla tyngder utan att n� m�lvikten, allts� kan vi inte v�ga
    // upp mot den.
    if (num_weights == 0)
        return FALSE;

    // Vi anv�nder den sista tyngden som vi har och "plockar bort" den.
    int i = num_weights - 1;

    // Vikten p� den tyngd vi ska prova med nu.
    int w = weights[i];

    return IsMeasurable(target, weights, i)      // Utan tyngden.
        || IsMeasurable(target - w, weights, i)  // Motvikt.
        || IsMeasurable(target + w, weights, i); // Medvikt.
}
