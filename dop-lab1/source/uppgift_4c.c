#include "lib/extgraph.h"
#include "lib/mazelib.h"

#include <string.h>


#define MAX_PATH 1024
#define NO_SOLUTION 10000

int FindPath(pointT pt, pointT path[], int max_path_size) {
    directionT dir;

    if (OutsideMaze(pt)) {
        path[0] = pt;
        return 1;
    }

    if (IsMarked(pt))
        return NO_SOLUTION;

    MarkSquare(pt);

    for (dir = North; dir <= West; dir++) {
        // Om det �r en v�gg iv�gen g�r vi vidare till n�sta riktning.
        if (WallExists(pt, dir))
            continue;

        int length = FindPath(AdjacentPoint(pt, dir), path+1, max_path_size-1);
        if (length != NO_SOLUTION) {
            path[0] = pt;
            return 1+length;
        }
    }

    // I den h�r uppgiften kommer vi inte att avmarkera rutorna utan ist�llet
    // h�lla reda p� v�gen explicit i ett f�lt s� att vi v�gen finns sparad d�
    // algoritmen terminerar
    // ...ok, d� g�r vi v�l s�...
    //UnmarkSquare(pt);

    return NO_SOLUTION;
}

void Uppgift4c() {
    pointT path[MAX_PATH];

    int length = FindPath(GetStartPosition(), path, MAX_PATH);
    if (length == 0) {
        printf("No solution exists.\n");
    }
    else {
        // Det h�r �r ju ett uselt s�tt att beskriva v�gen ut, vi hittar p�
        // n�got b�ttre ist�llet.
        /*printf("The following path is a solution:\n");
        for (int i = 0; i < length; i++) {
            printf(" (%d, %d)\n", path[i].x, path[i].y);
        }*/

        int count = 0;
        string last_dir = "";

        printf("Follow these directions to solve the maze:\n");
        for (int i = 1; i < length; i++) {
            pointT a = path[i-1],
                   b = path[i];

            string dir = "";

                 if (b.y == (a.y+1)) dir = "north";
            else if (b.y == (a.y-1)) dir = "south";
            else if (b.x == (a.x+1)) dir = "east";
            else                     dir = "west";

            if (i == 1)
                last_dir = dir;

            if (dir == last_dir) {
                count++;
            }
            else {
                if (count <= 1)
                    printf("Go %s\n", last_dir);
                else
                    printf("Go %s %d steps\n", last_dir, count);

                count = 1;
            }

            last_dir = dir;
        }

        if (count <= 1)
            printf("Go %s\n", last_dir);
        else
            printf("Go %s %d steps\n", last_dir, count);
    }

    system("pause");
    ExitGraphics();
}
