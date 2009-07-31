#ifndef COLLISION_H
#define COLLISION_H

// Collision masks

struct LineMask
{
	double x1, y1, x2, y2, thickness;
};

struct SplineMask
{
	int length;
	double thickness;
	double *x, *y;
};

struct BitMask
{
	double x, y, rot, xscale, yscale, x_origin, y_origin;
	int w, h;
	bool *bitmask;
};

struct CircleMask
{
	double x, y, radius;
};

struct PointMask
{
	double x, y;
};

struct RectMask
{
	double x1, y1, x2, y2;
};

struct PolyMask
{
	int length;
	double *x, *y;
};

struct SpriteMask
{
	BitMask *pixels;
	PolyMask *polygon;
};


// Collision checking functions

bool CollisonCheck(PointMask *source, PointMask *dest);
bool CollisonCheck(PointMask *source, RectMask *dest);

#endif
