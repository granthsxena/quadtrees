#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "data.h"
#include "location.h"
#include "read.h"
#include "record_struct.h"

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

int main(int argc, char *argv[]) {
    // Opens the required files for the program.
    FILE *inputFile = fopen(argv[2], "r");
    assert(inputFile);

    // Reads the data from the file in.
    int n;
    struct csvRecord **dataset = readCSV(inputFile, &n);
    fclose(inputFile);

    // Creates the root node for the Quadtree.
    quadtreeNode_t *tree = createQuadtreeNode(createRectangle(
        createPoint(atof(argv[4]), atof(argv[5])),
        createPoint(atof(argv[6]), atof(argv[7]))));

    // Adds all the record's read in from the file to the quadtree.
    for (int i = 0; i < n; i++) {
        addRecord(tree, dataset[i]);
    }
    freeCSV(dataset, n);

    // read in inputs and prints to file.
    double xCord;
    double yCord;
    char nums[STR_LEN];
    while (1 == scanf("%[^\n]%*c", nums)) {
        sscanf(nums, "%lf %lf", &xCord, &yCord);
        searchTreeForPoint(tree, createPoint(xCord, yCord), argv[3], nums);
    }
    
	return 0;
}
