//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "marphilib.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

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
