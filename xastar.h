/**
 * This file belongs to the 'xlib' (now 'xlab') game engine.
 * Copyright 2009 xfacter
 * Copyright 2016 wickles
 * This work is licensed under the LGPLv3
 * subject to all terms as reproduced in the included LICENSE file.
 */

#ifndef __X_ASTAR_H__
#define __X_ASTAR_H__

extern int *pathLength;
extern int *pathLocation;
extern int *pathStatus;
extern int *xPath;
extern int *yPath;
extern bool **walkable;

bool InitAstar(int width, int height, int entities);

void EndAstar();

int FindPath (int ID,int startX, int startY, int targetX, int targetY);

void UpdatePath(int ID);

#endif
