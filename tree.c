#include "data.h"
#include "location.h"
#include "read.h"
#include "record_struct.h"

// number representing max length of a string.
#define STR_LEN 512

// Structure that holds the required information for the quadTree.
typedef struct quadtreeNode quadtreeNode_t;

// creates a root node for a PR Quadtree.
// function takes in the bottom left and upper right points that make up the quadtree's area.
quadtreeNode_t *createQuadtreeNode(rectangle2D_t *rectangle);

// adds a record to the quad tree.
// function takes in a point pointing to the root of the tree and
// a pointer pointing towards the record to be added.
void addRecord(quadtreeNode_t *root, struct csvRecord *record);

// Adds a new node into the quadtree.
// Takes in the root of the tree that the node is being inserted into,
// the data to be inserted and the location where it is inserted.
void addQuadtreeNode(quadtreeNode_t *root, dataPoint_t *data, point2D_t *point);

// Searches the tree for a specific point and returns the quadrants it is in as a string.
// takes in a pointer to the root of the tree, a pointer to a point to be searched,
// and a string that stores the quadrants that the point is located in.
dataPoint_t *searchTree(quadtreeNode_t *root, point2D_t *point, char search[STR_LEN]);

// Calls a function to search a tree for a point and prints required information to a file and stdout.
// The function requires the root of the tree to search, a point to search, a file to print to
// and a string to print the information about where the point was found.
void searchTreeForPoint(quadtreeNode_t *root, point2D_t *point, char *filename, char *nums);


















#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "tree.h"
#include "data.h"
#include "location.h"
#include "read.h"
#include "record_struct.h"

#define NUM_POINTS 2
#define SW_QUAD 0
#define NW_QUAD 1
#define NE_QUAD 2
#define SE_QUAD 3
#define STR_LEN 512

// struct that hold the information for a PR Quadtree node.
struct quadtreeNode {
    rectangle2D_t *bounds;
    point2D_t *location;
    dataPoint_t *data;
    quadtreeNode_t *NW;
    quadtreeNode_t *NE;
    quadtreeNode_t *SW;
    quadtreeNode_t *SE;
};

// Struct that stores the x and y coordinates of a point
struct point2D {
	double x;
    double y;
};

// Struct that stores the information in a line of the file.
struct dataPoint {
	int footpath_id;
	char *address;
	char *clue_sa;
	char *asset_type;
	double deltaz;
	double distance;
	double grade1in;
	int mcc_id;
	int mccid_int;
	double rlmax;
	double rlmin;
	char *segside;
	int statusid;
	int streetid;
	int street_group;
	double start_lat;
	double start_lon;
	double end_lat;
	double end_lon;
};

// Calls a function to search a tree for a point and prints required information to a file and stdout.
void searchTreeForPoint(quadtreeNode_t *root, point2D_t *point, char *filename, char *nums) {
	FILE *outputFile = fopen(filename, "a");
    assert(outputFile);
    char search[STR_LEN] = "";

    dataPoint_t *matchedData = searchTree(root, point, search);
	if (matchedData != NULL) {
		printNode(matchedData, outputFile, nums);
    	printf("%s -->%s\n", nums, search);
	}
    
    fclose(outputFile);
}

// Searches the tree for a specific point and returns the quadrants it is in as a string.
dataPoint_t *searchTree(quadtreeNode_t *root, point2D_t *point, char search[STR_LEN]) {
	// checks if node is internal or a leaf
	// if it's a leaf it checks if the data point stored matches and returns 1 if yes.
	if (root->NW == NULL) {
		if (comparePoint(root->location, point)) {
			return root->data;
		} else {
			return NULL;
		}
	} // otherwise it directs the search to the correct child node.
	else {
		int quad = determineQuadrant(point, root->bounds);
		if (quad == SW_QUAD) {
			strcat(search, " SW");
			return searchTree(root->SW, point, search);
		} else if (quad == NW_QUAD) {
			strcat(search, " NW");
			return searchTree(root->NW, point, search);
		} else if (quad == NE_QUAD) {
			strcat(search, " NE");
			return searchTree(root->NE, point, search);
		} else if (quad == SE_QUAD) {
			strcat(search, " SE");
			return searchTree(root->SE, point, search);
		} else {
			return 0;
		}
	}
}

// creates a root node for a PR Quadtree
quadtreeNode_t *createQuadtreeNode(rectangle2D_t *rectangle) {
    quadtreeNode_t *node = malloc(sizeof(*node));
    assert(node);

    node->bounds = rectangle;
    node->location = NULL;
    node->data = NULL;
	node->NW = NULL;
	node->NE = NULL;
	node->SW = NULL;
	node->SE = NULL;

    return node;
}

// Adds a record's start and end points into the Quadtree.
void addRecord(quadtreeNode_t *root, struct csvRecord *record) {
	dataPoint_t *data = readRecord(record);

	addQuadtreeNode(root, data, createPoint(data->start_lon, data->start_lat));

	addQuadtreeNode(root, data, createPoint(data->end_lon, data->end_lat));
}

// Adds a new node into the quadtree.
void addQuadtreeNode(quadtreeNode_t *root, dataPoint_t *data, point2D_t *point) {
	// If the node is an empty leaf.
	if (root->data == NULL && root->NW == NULL) {
		root->data = data;
		root->location = point;
	}

	// if the node is a filled leaf or an internal node.
	else {
		// If the node doesn't have any child nodes already, they are created.
		if (root->NW == NULL) {
			root->NW = createQuadtreeNode(createNW(root->bounds));
			root->NE = createQuadtreeNode(createNE(root->bounds));
			root->SW = createQuadtreeNode(createSW(root->bounds));
			root->SE = createQuadtreeNode(createSE(root->bounds));
		}

		// finds which child nodes that the data needs to be inserted into.
		int quad = determineQuadrant(point, root->bounds);

		if (quad == SW_QUAD) {
			// if node is an internal node
			if (root->data == NULL) {
				addQuadtreeNode(root->SW, data, point);
			}
			// if node is a filled leaf node
			else {
				addQuadtreeNode(root->SW, data, point);
				
				dataPoint_t *tempData = root->data;
				point2D_t *tempLocation = root->location;
				root->data = NULL;
				root->location = NULL;

				addQuadtreeNode(root, tempData, tempLocation);
			}
		} else if (quad == NW_QUAD) {
			// if node is an internal node
			if (root->data == NULL) {
				addQuadtreeNode(root->NW, data, point);
			}
			// if node is a filled leaf node
			else {
				addQuadtreeNode(root->NW, data, point);

				dataPoint_t *tempData = root->data;
				point2D_t *tempLocation = root->location;
				root->data = NULL;
				root->location = NULL;

				addQuadtreeNode(root, tempData, tempLocation);
			}
		} else if (quad == NE_QUAD) {
			// if node is an internal node
			if (root->data == NULL) {
				addQuadtreeNode(root->NE, data, point);
			}
			// if node is a filled leaf node
			else {
				addQuadtreeNode(root->NE, data, point);

				dataPoint_t *tempData = root->data;
				point2D_t *tempLocation = root->location;
				root->data = NULL;
				root->location = NULL;

				addQuadtreeNode(root, tempData, tempLocation);
			}
		} else if (quad == SE_QUAD) {
			// if node is an internal node
			if (root->data == NULL) {
				addQuadtreeNode(root->SE, data, point);
			}
			// if node is a filled leaf node
			else {
				addQuadtreeNode(root->SE, data, point);

				dataPoint_t *tempData = root->data;
				point2D_t *tempLocation = root->location;
				root->data = NULL;
				root->location = NULL;

				addQuadtreeNode(root, tempData, tempLocation);
			}
		}
		// node not within bounds
		else {
			return;
		}
	}
}
