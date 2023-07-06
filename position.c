typedef struct point2D point2D_t;
typedef struct rectangle2D rectangle2D_t;

// creates and returns a rectangle struct.
// It takes in the bottom left and top points of this rectangle.
rectangle2D_t *createRectangle(point2D_t *botL, point2D_t *upR);

// creates and returns a 2D location point.
// It takes in the x and y coordinates of the point.
point2D_t *createPoint(double x, double y);

// Determines if a point lies within a rectangle.
// Requires a pointer to a point and a rectangle.
int inRectangle(point2D_t *point, rectangle2D_t *rectangle);

// Determines which quadrant (NW, NE, SW, SE) of a rectangle a point is in.
// Function takes in a pointer to a point and a rectangle.
int determineQuadrant(point2D_t *point, rectangle2D_t *parentBounds);

// Following four functions create the four quadrants of a rectangle.
// They all require a pointer to a rectangle.
rectangle2D_t *createNW(rectangle2D_t *parentBounds);
rectangle2D_t *createNE(rectangle2D_t *parentBounds);
rectangle2D_t *createSW(rectangle2D_t *parentBounds);
rectangle2D_t *createSE(rectangle2D_t *parentBounds);

// Function compares two points to see if they lie at the same spot.
// Takes in two pointers to two points.
int comparePoint(point2D_t *point1, point2D_t *point2);











#include <stdlib.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "location.h"

#define SW_QUAD 0
#define NW_QUAD 1
#define NE_QUAD 2
#define SE_QUAD 3
#define NO_QUAD 4

// Struct that stores the x and y coordinates of a point
struct point2D {
	double x;
    double y;
};

// Struct that stores the bottom left and upper right points of a rectangle
struct rectangle2D {
    point2D_t *bottomLeft;
    point2D_t *upperRight;
};

// Determines if a point lies within a rectangle.
int inRectangle(point2D_t *point, rectangle2D_t *rectangle) {
    // saves the x and y coordinates of the point to the checked
    double pointX = point->x;
    double pointY = point->y;

    // saves the x and y coordinates of the boundaries that need to be checked.
    double bot = rectangle->bottomLeft->y;
    double left = rectangle->bottomLeft->x;
    double top = rectangle->upperRight->y;
    double right = rectangle->upperRight->x;

    // checks if the point is within the rectangle and returns 1 if it is, and 0 if not.
    if (bot <= pointY && right >= pointX && top > pointY && left < pointX) {
        return 1;
    }
    return 0;
}

// Determines which quadrant (NW, NE, SW, SE) of a rectangle a point is in.
int determineQuadrant(point2D_t *point, rectangle2D_t *parentBounds) {
    if (inRectangle(point, createSW(parentBounds))) {
        return SW_QUAD;
    } else if (inRectangle(point, createNW(parentBounds))) {
        return NW_QUAD;
    } else if (inRectangle(point, createNE(parentBounds))) {
        return NE_QUAD;
    } else if (inRectangle(point, createSE(parentBounds))) {
        return SE_QUAD;
    }
    return NO_QUAD;
}

// Creates a new rectangle in the bottom left quarter of the supplied rectangle.
rectangle2D_t *createSW(rectangle2D_t *parentBounds) {
    double left = parentBounds->bottomLeft->x;
    double bot = parentBounds->bottomLeft->y;
    double right = (left + parentBounds->upperRight->x)/2;
    double top = (bot + parentBounds->upperRight->y)/2;

    rectangle2D_t *newRectangle = createRectangle(createPoint(left, bot), createPoint(right, top));
    return newRectangle;
}

// Creates a new rectangle in the bottom right quarter of the supplied rectangle.
rectangle2D_t *createSE(rectangle2D_t *parentBounds) {
    double bot = parentBounds->bottomLeft->y;
    double right = parentBounds->upperRight->x;
    double left = (right + parentBounds->bottomLeft->x)/2;
    double top = (bot + parentBounds->upperRight->y)/2;

    rectangle2D_t *newRectangle = createRectangle(createPoint(left, bot), createPoint(right, top));
    return newRectangle;
}

// Creates a new rectangle in the top right quarter of the supplied rectangle.
rectangle2D_t *createNE(rectangle2D_t *parentBounds) {
    double right = parentBounds->upperRight->x;
    double top = parentBounds->upperRight->y;
    double left = (right + parentBounds->bottomLeft->x)/2;
    double bot = (top + parentBounds->bottomLeft->y)/2;

    rectangle2D_t *newRectangle = createRectangle(createPoint(left, bot), createPoint(right, top));
    return newRectangle;
}

// Creates a new rectangle in the top left quarter of the supplied rectangle.
rectangle2D_t *createNW(rectangle2D_t *parentBounds) {
    double left = parentBounds->bottomLeft->x;
    double top = parentBounds->upperRight->y;
    double right = (left + parentBounds->upperRight->x)/2;
    double bot = (top + parentBounds->bottomLeft->y)/2;

    rectangle2D_t *newRectangle = createRectangle(createPoint(left, bot), createPoint(right, top));
    return newRectangle;
}

// creates and returns a rectangle struct.
rectangle2D_t *createRectangle(point2D_t *botL, point2D_t *upR) {
    rectangle2D_t *rectangle = malloc(sizeof(*rectangle));
    assert(rectangle);

    rectangle->bottomLeft = botL;
    rectangle->upperRight = upR;

    return rectangle;
}

// creates and returns a 2D location point.
point2D_t *createPoint(double x, double y) {
    point2D_t *point = malloc(sizeof(*point));
    assert(point);

    point->x = x;
    point->y = y;

    return point;
}

// compares two points to see if they are the same.
int comparePoint(point2D_t *point1, point2D_t *point2) {
    double x1 = point1->x;
    double x2 = point2->x;
    double y1 = point1->y;
    double y2 = point2->y;

    if (abs(x1) - abs(x2) == 0) {
        if (abs(y1) - abs(y2) == 0) {
            return 1;
        }
    }
    return 0;
}
