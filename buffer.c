/*************************************************************************
 *                                                                       *
 * Copyright (c) 1992, 1993 Ronald Joe Record                           *
 *                                                                       *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/
 /*
 *  The X Consortium, and any party obtaining a copy of these files from
 *  the X Consortium, directly or indirectly, is granted, free of charge,
 *  a full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 *  nonexclusive right and license to deal in this software and
 *  documentation files (the "Software"), including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons who receive
 *  copies from any such party to do so.  This license includes without
 *  limitation a license to do the foregoing actions under any patents of
 *  the party supplying this software to the X Consortium.
 */

#include "libXrr.h"

void
BufferInPixmap(display, pixmap, contexts, points, col, x, y)
Display *display;
Pixmap pixmap;
GC *contexts;
points_t *points;
int col, x, y;
{
    if (points->npoints[col] == MAXPOINTS)
    {
        XDrawPoints(display, pixmap, contexts[col],
            points->data[col], points->npoints[col], CoordModeOrigin);
        points->npoints[col] = 0;
    }
    points->data[col][points->npoints[col]].x = x;
    points->data[col][points->npoints[col]].y = y;
    ++points->npoints[col];
}

void
BufferPoint(display, window, pixmap, contexts, points, col, x, y)
Display *display;
Window window;
Pixmap pixmap;
GC *contexts;
points_t *points;
int col, x, y;
{
    if (points->npoints[col] == MAXPOINTS)
    {
        XDrawPoints(display, window, contexts[col],
            points->data[col], points->npoints[col], CoordModeOrigin);
        XDrawPoints(display, pixmap, contexts[col],
            points->data[col], points->npoints[col], CoordModeOrigin);
        points->npoints[col] = 0;
    }
    points->data[col][points->npoints[col]].x = x;
    points->data[col][points->npoints[col]].y = y;
    ++points->npoints[col];
}

void
InitBuffer(points, maxcolor)
points_t *points;
int maxcolor;
{
    static int i;

    for (i = 0 ; i < maxcolor; i++)
        points->npoints[i] = 0;
}

void
FlushPixmap(display, pixmap, contexts, points, mincolor, maxcolor)
Display *display;
Pixmap pixmap;
GC *contexts;
points_t *points;
int mincolor, maxcolor;
{
    static int color;

    for (color = mincolor; color < maxcolor; ++color)
        if (points->npoints[color]) {
            XDrawPoints(display, pixmap, contexts[color], points->data[color], 
                    points->npoints[color], CoordModeOrigin);
            points->npoints[color] = 0;
        }
}

void
FlushBuffer(display, window, pixmap, contexts, points, mincolor, maxcolor)
Display *display;
Window window;
Pixmap pixmap;
GC *contexts;
points_t *points;
int mincolor, maxcolor;
{
    static int color;

    for (color = mincolor; color < maxcolor; ++color)
        if (points->npoints[color]) {
            XDrawPoints(display, window, contexts[color], points->data[color], 
                    points->npoints[color], CoordModeOrigin);
            XDrawPoints(display, pixmap, contexts[color], points->data[color], 
                    points->npoints[color], CoordModeOrigin);
            points->npoints[color] = 0;
        }
}
