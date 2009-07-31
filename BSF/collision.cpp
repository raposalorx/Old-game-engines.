#include "collision.h"

bool CollisonCheck(PointMask *source, PointMask *dest)
{
	return ((int)source->x == (int)dest->y) and ((int)source->y == (int)dest->y);
}

bool CollisonCheck(PointMask *source, RectMask *dest)
{
	return (source->x >= dest->x1) and (source->x <= dest->x2) and (source->y >= dest->y1) and (source->y <= dest->y2);
}
