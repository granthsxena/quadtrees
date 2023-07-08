# quadtrees

PR Quadtree Implementation

This repository contains an implementation of the PR Quadtree data structure, which is used to efficiently store and search for 2-dimensional points. The PR Quadtree is a recursive data structure that divides a given area into quadrants, allowing for efficient point storage and retrieval.

Introduction to PR Quadtrees

A PR Quadtree is a point-region quadtree specifically designed for storing 2-dimensional points. The quadtree is built recursively by subdividing a rectangle into four equally-sized sub-rectangles. Each node in the quadtree represents a rectangle that covers a part of the indexed area. The leaf nodes of the quadtree can be black, indicating the presence of a single data point, or white, indicating an empty node. Internal nodes are colored gray and contain four children representing the four quadrants.

Building a PR Quadtree

To build a PR Quadtree, an initial rectangle is defined to encompass all the points to be stored. The points are then inserted one by one, recursively subdividing the rectangles into four quadrants when necessary. The insertion process ensures that each leaf node contains either a single data point or is empty. The construction of the PR Quadtree is independent of the order of point insertion.

Search and Range Query

The PR Quadtree enables efficient search operations. To search for a specific data point, the quadtree is traversed recursively by comparing the point's coordinates with the rectangle regions at each level. The search process stops when a leaf node is reached. If the leaf node contains the desired data point, it is returned; otherwise, it is reported that the data point is not stored in the PR Quadtree.

A range query, also known as a window query, retrieves all data points within a given query rectangle. This query is performed by recursively traversing the quadtree and selecting the internal children whose rectangles overlap with the query rectangle. The process continues until the leaf level is reached, and the data points from the black leaf nodes within the query rectangle are returned.

Implementation Details

The implementation of the PR Quadtree includes several data structures and functions to support point insertion, search, and range queries. Some of the essential data structures include point2D for storing 2-dimensional point coordinates, rectangle2D for specifying rectangles, dataPoint for storing data associated with a point, and quadtreeNode for representing nodes in the quadtree.

The implementation provides functions such as inRectangle to check if a point lies within a rectangle, rectangleOverlap to test if two rectangles overlap, determineQuadrant to determine the quadrant of a point within a rectangle, addPoint for inserting a data point into the quadtree, searchPoint for searching a data point, and rangeQuery for performing range queries.

Usage

To use the PR Quadtree implementation, follow the steps below:

Clone this repository to your local machine.
Compile the source code using the provided Makefile to generate an executable program called dict3.
Execute the program with the required command-line arguments.
The first argument should always be 3, indicating the stage of execution.
The second argument is the name of the data file to be processed.
The third argument is the name of the output file where matching records will be stored.
The fourth and fifth arguments specify the x and y coordinate pair of the bottom-left corner of the root node area.
The sixth and seventh arguments specify the x and y coordinate pair of the top-right corner of the root node area.
The program will read the data from the specified file and construct the PR Quadtree.
Input coorindate pairs from stdin to search the quadtree for the corresponding point region. The program will print all matching records to the output file.
The list of quadrant directions followed from the root until the correct point region is found will be output to stdout.
For more details and additional functions, refer to the code implementation and the provided references.
