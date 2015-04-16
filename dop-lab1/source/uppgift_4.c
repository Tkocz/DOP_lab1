/*
 * File: maze.c
 * ------------
 * This program solves a maze by recursive backtracking.
 */

#include <stdio.h>
#include "lib/genlib.h"
#include "lib/simpio.h"
#include "lib/strlib.h"
#include "lib/graphics.h"
#include "lib/mazelib.h"

/*
 * Constants
 * ---------
 * MazeFile -- Name of the file containing the maze
 */

#define MazeFile "example.maz"

/* Private function prototypes */

static bool SolveMaze(pointT pt);
static pointT AdjacentPoint(pointT pt, directionT dir);

// HÄR NEDANFÖR KOMMER VÅR ELAJT-KOD SOM LÖSER ALLA PROBLEM I HELA VÄRLDEN
// -----------------------------------------------------------------------

#define NoSolution 10000

int ShortestPathLength(pointT pt) {
    directionT dir;

    if (OutsideMaze(pt)) return 0;
    if (IsMarked(pt)) return NoSolution;

    MarkSquare(pt);

    int n, e, s, w;
    n = s = e = w = NoSolution;

    if (!WallExists(pt, North)) n = 1+ShortestPathLength(AdjacentPoint(pt, North));
    if (!WallExists(pt, East))  e = 1+ShortestPathLength(AdjacentPoint(pt, East));
    if (!WallExists(pt, South)) s = 1+ShortestPathLength(AdjacentPoint(pt, South));
    if (!WallExists(pt, West))  w = 1+ShortestPathLength(AdjacentPoint(pt, West));

    int min = NoSolution;

    if (n < min) min = n;
    if (e < min) min = e;
    if (s < min) min = s;
    if (w < min) min = w;

    UnmarkSquare(pt);

    return min;
}


// ELAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJT

/* Main program */

void Uppgift4()
{
	string UsrMazeFile;
	UsrMazeFile = GetLine();
    InitGraphics();
    ReadMazeMap(UsrMazeFile);
    /*if (SolveMaze(GetStartPosition())) {
        printf("The marked squares show a solution path.\n");
    } else {
        printf("No solution exists.\n");
    }*/

    ////////// ELAJT STUDENTKOD
    printf("%d\n", ShortestPathLength(GetStartPosition()));
    //////////////////////

}

/*
 * Function: SolveMaze
 * Usage: if (SolveMaze(pt)) . . .
 * -------------------------------
 * This function attempts to generate a solution to the current
 * maze from point pt.  SolveMaze returns TRUE if the maze has
 * a solution and FALSE otherwise.  The implementation uses
 * recursion to solve the submazes that result from marking the
 * current square and moving one step along each open passage.
 */

static bool SolveMaze(pointT pt)
{
    directionT dir;

    if (OutsideMaze(pt)) return (TRUE);
    if (IsMarked(pt)) return (FALSE);
    MarkSquare(pt);
    for (dir = North; dir <= West; dir++) {
        if (!WallExists(pt, dir)) {
            if (SolveMaze(AdjacentPoint(pt, dir))) {
                return (TRUE);
            }
        }
    }
    UnmarkSquare(pt);
    return (FALSE);
}

/*
 * Function: AdjacentPoint
 * Usage: newpt = AdjacentPoint(pt, dir);
 * --------------------------------------
 * This function returns the pointT that results from moving
 * one square from pt in the direction specified by dir.  For
 * example, if pt is the point (1,1), AdjacentPoint(pt, East)
 * would return the point (2,1).
 */

static pointT AdjacentPoint(pointT pt, directionT dir)
{
    pointT newpt;

    newpt = pt;
    switch (dir) {
      case North: newpt.y++; break;
      case East:  newpt.x++; break;
      case South: newpt.y--; break;
      case West:  newpt.x--; break;;
    }
    return (newpt);
}

