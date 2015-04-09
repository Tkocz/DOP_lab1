//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/genlib.h"
#include "lib/graphics.h"
#include "lib/simpio.h"
#include "lib/strlib.h"

#include <math.h>
#include <stdio.h>

//---------------------------------------------------------
// TYPES
//---------------------------------------------------------

/*--------------------------------------
 * Type: vertexT
 *
 * Description:
 *   Representerar en punkt i bidimensionell rymd.
 *------------------------------------*/
typedef struct {
    float x, y;
} vertexT;

//---------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------

/*--------------------------------------
 * Constant: MAX_SUBDIVS
 *
 * Description:
 *   Max antal subdivideringar av triangeln.
 *------------------------------------*/
#define MAX_SUBDIVS 10

/*--------------------------------------
 * Constant: TRI_SIZE
 *
 * Description:
 *   Storleken på triangeln.
 *------------------------------------*/
#define TRI_SIZE 1.6f

//---------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------

/*--------------------------------------
 * Function: DrawTri()
 * Parameters: v0  Punkt ett.
 *             v1  Punkt två.
 *             v2  Punkt tre.
 *
 * Description:
 *   Ritar den givna triangeln.
 *------------------------------------*/
static void DrawTri(vertexT v0, vertexT v1, vertexT v2) {
    // Vi börjar på punkt v0...
    MovePen(v0.x, v0.y);

    // ...och ritar sedan triangles tre sidor.

    // v0 -> v1
    DrawLine(v1.x - v0.x, v1.y - v0.y);

    // v1 -> v2
    DrawLine(v2.x - v1.x, v2.y - v1.y);

    // v2 -> v0
    DrawLine(v0.x - v2.x, v0.y - v2.y);
}

/*--------------------------------------
 * Function: SubdivTri()
 * Parameters: v0           Punkt ett.
 *             v1           Punkt två.
 *             v2           Punkt tre.
 *             num_subdivs  Antal subdivideringar som ska utföras.
 *             disp         TRUE för att använda "displacement."
 *
 * Description:
 *   Ritar den givna triangeln och delar upp den i fler, mindre trianglar.
 *------------------------------------*/
static void SubdivTri(vertexT v0, vertexT v1, vertexT v2, int num_subdivs,
                      bool disp)
{
    if (num_subdivs < 1) {
        // Vi ritar bara triangeln i sista steget...
        DrawTri(v0, v1, v2, FALSE);
        return; // Klara!
    }

    vertexT sv0, sv1, sv2;

    /*
     * Vi skapar de tre nya punkterna sv0, sv1 och sv2 i triangeln enligt
     * följande:
     *
     *          v0
     *          /\
     *         /  \
     *        /    \
     *       /      \
     *  sv2 /        \ sv0
     *     /          \
     *    /            \
     *   /              \
     *  /________________\
     * v2       sv1       v1
     *
     * Med dessa kan vi skapa fyra nya trianglar:
     *  1. v0  -> sv0 -> sv2 -> v0
     *  2. sv2 -> sv0 -> sv1 -> sv2
     *  3. sv2 -> sv1 -> v2  -> sv2
     *  4. sv0 -> v1  -> sv1 -> sv0
     *
     * Dessa är de fyra "subdividerade" trianglarna, vilka vi skapar genom
     * rekursion.
     */

    sv0.x = (v1.x + v0.x) / 2.0f;
    sv0.y = (v1.y + v0.y) / 2.0f;
    sv1.x = (v2.x + v1.x) / 2.0f;
    sv1.y = (v2.y + v1.y) / 2.0f;
    sv2.x = (v0.x + v2.x) / 2.0f;
    sv2.y = (v0.y + v2.y) / 2.0f;

    if (disp) {
        // Vi flyttar dem lite upp och ner för 3d-effekten...

        float d = 9.0f * pow(0.5, MAX_SUBDIVS - num_subdivs);
        sv0.y += sin(10.0*sv0.x + 5.0*sv0.y) * d;
        sv1.y += sin(10.0*sv1.x + 5.0*sv1.y) * d;
        sv2.y += sin(10.0*sv2.x + 5.0*sv2.y) * d;
    }

    // Här har vi klarat av en subdividering, så vi minskar num_subdivs med ett.
    num_subdivs--;

    SubdivTri(v0 , sv0, sv2, num_subdivs, disp);
    SubdivTri(sv2, sv0, sv1, num_subdivs, disp);
    SubdivTri(sv2, sv1, v2 , num_subdivs, disp);
    SubdivTri(sv0, v1 , sv1, num_subdivs, disp);
}

/*--------------------------------------
 * Function: Uppgift3()
 * Parameters:
 *
 * Description:
 *   Huvudfunktionen för uppgift 3.
 *------------------------------------*/
void Uppgift3() {
    // Nej, jag tänker inte göra egna funktioner för att läsa in antal
    // subdivideringar och displacement... /Philip

    printf("Enter subdivision level (max %d): ", MAX_SUBDIVS);
    int num_subdivs = GetInteger();

    printf("Apply displacement (Y/n) ? ");
    string s = GetLine();

    bool disp = FALSE;
    if (s[0]=='\0' || s[0]=='Y' || s[0]=='y')
        disp = TRUE;

    FreeBlock(s);

    if (num_subdivs < 0          ) num_subdivs = 0;
    if (num_subdivs > MAX_SUBDIVS) num_subdivs = MAX_SUBDIVS;

    InitGraphics();

    float half_width  = GetWindowWidth()  / 2.0f;
    float half_height = GetWindowHeight() / 2.0f;

    // Lite mer centrerad... Orkar inte räkna på saken, duger såhär. /Philip
    half_height *= 1.13f;

    vertexT a, b, c;

    // Här skapar vi den yttersta triangeln...
    a.x = half_width;
    a.y = half_height + TRI_SIZE * 0.707f; // 0.5sqrt(2) för likbenthet...
    b.x = half_width  + TRI_SIZE;
    b.y = half_height - TRI_SIZE;
    c.x = half_width  - TRI_SIZE;
    c.y = half_height - TRI_SIZE;

    // Wiiieeee!
    SubdivTri(a, b, c, num_subdivs, disp);

    printf("Well, I never..! That is one excitng mesh of triangles if I ever");
    printf(" saw one!\n");
}
