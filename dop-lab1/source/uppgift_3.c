//---------------------------------------------------------
// INCLUDES
//---------------------------------------------------------

#include "lib/genlib.h"
#include "lib/graphics.h"
#include "lib/extgraph.h"
#include "lib/simpio.h"

// Dessa använder vi för att förhindra flimmer.
#include <Windows.h>
#include <tchar.h>

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
 *   Max antal subdivideringar av den yttersta triangeln.
 *------------------------------------*/
#define MAX_SUBDIVS 10

/*--------------------------------------
 * Constant: TRI_SIZE
 *
 * Description:
 *   Storleken på den yttersta triangeln.
 *------------------------------------*/
#define TRI_SIZE 1.6f

//---------------------------------------------------------
// GLOBALS
//---------------------------------------------------------

/*--------------------------------------
 * Variable: g_anim
 *
 * Description:
 *   Används för animation. JAG VET, JAG VET, inga globala variabler. Kom igen
 *   nu, det här är ju jättehäftigt och används bara för att det ska se ballt
 *   ut, inte för att lösa uppgiften.
 *------------------------------------*/
static float g_anim = 0.0f;

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

    // v0----v1
    DrawLine(v1.x - v0.x, v1.y - v0.y);

    // v1----v2
    DrawLine(v2.x - v1.x, v2.y - v1.y);

    // v2----v0
    DrawLine(v0.x - v2.x, v0.y - v2.y);
}

/*--------------------------------------
 * Function: SubdivTri()
 * Parameters: v0           Punkt ett.
 *             v1           Punkt två.
 *             v2           Punkt tre.
 *             num_subdivs  Antal subdivideringar som ska utföras.
 *             disp         TRUE för att använda "displacement."
 * Returns:    Antalet uppritade trianglar.
 *
 * Description:
 *   Ritar den givna triangeln och delar upp den i fler, mindre trianglar.
 *------------------------------------*/
static int SubdivTri(vertexT v0, vertexT v1, vertexT v2, int num_subdivs,
                     bool disp)
{

    // Om num_subdivs == 0 så har vi nått maximal subdividering, och det är dags
    // att rita triangeln. Detta är de minsta trianglarna vi skapar, och det är
    // bara dem vi ritar upp i fönstret.
    if (num_subdivs == 0) {
        DrawTri(v0, v1, v2);
        return 1; // Returnera 1 så att vi kan räkna trianglarna...
    }

    // Vi har inte nått maxdjup än, så vi skapar fyra ännu mindre trianglar...

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
     *   1. v0  -> sv0 -> sv2 -> v0
     *   2. sv2 -> sv0 -> sv1 -> sv2
     *   3. sv2 -> sv1 -> v2  -> sv2
     *   4. sv0 -> v1  -> sv1 -> sv0
     *
     *          v0
     *          /\
     *         /  \
     *        / 1  \
     *       /______\
     *  sv2 /\      /\ sv0
     *     /  \ 2  /  \
     *    /    \  /    \
     *   /  3   \/  4   \
     *  /________________\
     * v2       sv1       v1
     *
     *
     * Dessa är de fyra "subdividerade" trianglarna, vilka vi skapar genom
     * rekursion. Vi räknar ut de nya punkterna genom att ta snitten mellan två
     * andra punkter i den triangel vi har, vilket ger en s.k. midpoint som
     * ligger på mitten av segmentet.
     */

    // sv0 = mittimellan v0 och v1
    sv0.x = (v1.x + v0.x) / 2.0f;
    sv0.y = (v1.y + v0.y) / 2.0f;

    // sv1 = mittimellan v1 och v2
    sv1.x = (v2.x + v1.x) / 2.0f;
    sv1.y = (v2.y + v1.y) / 2.0f;

    // sv2 = mittimellan v0 och v2
    sv2.x = (v0.x + v2.x) / 2.0f;
    sv2.y = (v0.y + v2.y) / 2.0f;

    if (disp) {
        // Vi flyttar dem lite upp och ner för att få 3d-effekt om disp == TRUE...

        float d = 12.0f * (float)pow(0.5f, MAX_SUBDIVS - num_subdivs);

        sv0.y += (float)sin(10.0f*sv0.x + 5.0f*sv0.y + g_anim) * d;
        sv1.y += (float)sin(10.0f*sv1.x + 5.0f*sv1.y + g_anim) * d;
        sv2.y += (float)sin(10.0f*sv2.x + 5.0f*sv2.y + g_anim) * d;
    }

    // Här har vi klarat av en nivå subdividering, så vi minskar num_subdivs med
    // ett och kör nästa nivå fyra gånger om (en för varje mindre triangel).
    num_subdivs--;

    return SubdivTri(v0 , sv0, sv2, num_subdivs, disp)  // Triangel 1.
         + SubdivTri(sv2, sv0, sv1, num_subdivs, disp)  // - || -   2.
         + SubdivTri(sv2, sv1, v2 , num_subdivs, disp)  // - || -   3.
         + SubdivTri(sv0, v1 , sv1, num_subdivs, disp); // - || -   4.
}

/*--------------------------------------
 * Function: DisableRedraw()
 * Parameters: hwnd Fönster-"pekare."
 *
 * Description:
 *   Hindrar fönstret från att rita upp sitt innehåll.
 *------------------------------------*/
static void DisableRedraw(HWND hwnd) {
    SendMessage(hwnd, WM_SETREDRAW, FALSE, 0);
}

/*--------------------------------------
 * Function: EnableRedraw()
 * Parameters: hwnd Fönster-"pekare."
 *
 * Description:
 *   Tillåter fönstret att rita upp sitt innehåll.
 *------------------------------------*/
static void EnableRedraw(HWND hwnd) {
    SendMessage(hwnd, WM_SETREDRAW, TRUE, 0);
    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
}

/*--------------------------------------
 * Function: Uppgift3()
 * Parameters:
 *
 * Description:
 *   Huvudfunktionen för uppgift 3.
 *------------------------------------*/
void Uppgift3() {
    //**************************************
    // 1. Låt användaren ange inputs.
    //**************************************

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

    //**************************************
    // 2. Verifiera korrekta inputs.
    //**************************************

    if (num_subdivs < 0          ) num_subdivs = 0;
    if (num_subdivs > MAX_SUBDIVS) num_subdivs = MAX_SUBDIVS;

    //**************************************
    // 3. Starta grafikbiblioteket.
    //**************************************

    InitGraphics();
    SetWindowTitle("TriWin1337");

    //**************************************
    // 4. Skapa den yttersta triangeln.
    //**************************************

    // Vi utgår ifrån mitten av fönstret för att få en centrerad triangel.
    float half_width  = (float)GetWindowWidth()  / 2.0f;
    float half_height = (float)GetWindowHeight() / 2.0f;

    // Lite mer centrerad... Orkar inte räkna på saken, duger såhär. /Philip
    half_height *= 1.13f;

    vertexT a, b, c;

    /*
     * Här skapar vi den yttersta triangeln:
     *
     *      a
     *      /\
     *     /  \
     *    /    \
     *   /      \
     *  /________\
     * c          b
     *
     * Presto!
     */
    a.x = half_width;
    a.y = half_height + TRI_SIZE * 0.707f; // 0.5sqrt(2) för likbenthet...
    b.x = half_width  + TRI_SIZE;
    b.y = half_height - TRI_SIZE;
    c.x = half_width  - TRI_SIZE;
    c.y = half_height - TRI_SIZE;

    //**************************************
    // 5. Nu blir det rekursion!
    //**************************************

    // Vi animerar bara om vi använder displacement, annars syns det ju inte
    // ändå...
    if (disp) {
        float win_width  = (float)GetWindowWidth();
        float win_height = (float)GetWindowHeight();

        // H4x!
        HWND hwnd = FindWindow(NULL, _T("TriWin1337"));

        while (TRUE) {
            // Förbjud fönstret från att uppdateras under uppritning, så att det
            // inte "flimrar."
            DisableRedraw(hwnd);
                
            // Rensa ritytan.
            SetEraseMode(TRUE);
            StartFilledRegion(1.0);
                MovePen (0.0       , 0.0);
                DrawLine(win_width , 0.0);
                DrawLine(0.0       , win_height);
                DrawLine(-win_width, 0.0);
            EndFilledRegion();
            SetEraseMode(FALSE);

            // Rita trianglarna!
            SubdivTri(a, b, c, num_subdivs, disp);

            // Nu tillåter vi att allt ritas upp i fönstret igen.
            EnableRedraw(hwnd);

            // 60fps blir säkert bra.
            Pause(1.0 / 60.0);

            // Wiiieee, den fladdrar i vinden!
            g_anim += 0.21f;
        }
    }
    else {
        // Rita trianglarna!
        int num_tris = SubdivTri(a, b, c, num_subdivs, disp);
        printf("Well, I never..! That is one exciting mesh of triangles if I "
               "ever saw one!\n");
        printf("\n%d triangles drawn.\n", num_tris);
    }

    system("pause");
    ExitGraphics();
}
