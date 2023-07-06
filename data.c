#include <stdio.h>

#include "location.h"
#include "read.h"
#include "record_struct.h"

// Struct that stores all the data in a node
typedef struct dataPoint dataPoint_t;

// cite this from assignment 1 solution
// function requires a pointer to a record to be read and processed in to a dataPoint.
dataPoint_t *readRecord(struct csvRecord *record);

// Sets the relevant field.
// function needs a pointer to where data shall be stored,
// the number of fields in the data and their values.
void setField(dataPoint_t *record, int fieldIndex, char *fieldVal);

// Reads in an int from a string.
// This function uses a pointer to a string which contains data to be read to an int.
int readIntField(char *fieldString);

// reads in a string from a string.
// This function uses a pointer to a string which contains data to be read to a string.
char *readStringField(char *fieldString);

// reads in a double from a string.
// This function uses a pointer to a string which contains data to be read to a double.
double readDoubleField(char *fieldString);

// prints information from data to the specified file.
// This function requires a pointer to the data to be printed, the file they are to be printed to,
// and the point at which this data was found in the tree.
void printNode(dataPoint_t *d, FILE *file, char *nums);

// Frees data in a datapoint.
// Takes in a pointer to the dataPoint to be freed
void freeData(dataPoint_t *d);

















#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "data.h"
#include "location.h"
#include "read.h"
#include "record_struct.h"

#define NUM_FIELDS 19
#define NUMERIC_BASE 10

// Struct that stores the x and y coordinates of a point
struct point2D {
	double x;
    double y;
};

// Struct that stores all the data in a node
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

// struct that stores a a record from the input file
struct csvRecord {
    int fieldCount;
    char **fields;
};

/*  The code below is sourced from the following cite:
	The University of Melbourne (Sam Hoffmann)
	9th September 2022
	COMP20003 Assignment 1 Submission
	Computer Program for printing data to a file
	Found at: https://edstem.org/au/courses/9173/lessons/25539/slides/182812
*/
///////////////// START CITED CODE /////////////////
// prints information from data to the specified file.
void printNode(dataPoint_t *d, FILE *file, char *nums) {
    fprintf(file, "%s\n", nums);
	fprintf(file, "--> footpath_id: %d || address: %s || clue_sa: %s || "
	"asset_type: %s || deltaz: %0.2lf || distance: %0.2lf || grade1in: %0.1lf "
	"|| mcc_id: %d || mccid_int: %d || rlmax: %0.2lf || rlmin: %0.2lf || "
	"segside: %s || statusid: %d || streetid: %d || street_group: %d || "
	"start_lat: %0.6lf || start_lon: %0.6lf || end_lat: %0.6lf || end_lon: "
	"%0.6lf || \n",
	d->footpath_id, d->address, d->clue_sa, d->asset_type, d->deltaz,
	d->distance, d->grade1in, d->mcc_id, d->mccid_int, d->rlmax, d->rlmin,
	d->segside, d->statusid, d->streetid, d->street_group, d->start_lat,
	d->start_lon, d->end_lat, d->end_lon);
}
///////////////// END CITED CODE /////////////////

/*  The code below is sourced from the following cite:
	The University of Melbourne
	9th September 2022
	COMP20003 Assignment 1 Solution
	Computer Program for reading in CSV file
	Found at: https://edstem.org/au/courses/9173/lessons/25539/slides/182812/solution
*/
///////////////// START CITED CODE /////////////////
/* Read a record into a typed data structure. */
dataPoint_t *readRecord(struct csvRecord *record) {
    struct dataPoint *ret = (struct dataPoint *) malloc(sizeof(struct dataPoint));
    assert(ret);
    //ret->address = malloc(sizeof(sizeof(char) * 512));
    assert(record->fieldCount == NUM_FIELDS);
    for(int i = 0; i < NUM_FIELDS; i++){
        setField(ret, i, record->fields[i]);
    }
    return ret;
};

// Sets the relevant field.
void setField(dataPoint_t *record, int fieldIndex, char *fieldVal){
    switch(fieldIndex){
        case 0:
            record->footpath_id = readIntField(fieldVal);
            break;
        case 1:
            record->address = readStringField(fieldVal);
            break;
        case 2:
            record->clue_sa = readStringField(fieldVal);
            break;
        case 3:
            record->asset_type = readStringField(fieldVal);
            break;
        case 4:
            record->deltaz = readDoubleField(fieldVal);
            break;
        case 5:
            record->distance = readDoubleField(fieldVal);
            break;
        case 6:
            record->grade1in = readDoubleField(fieldVal);
            break;
        case 7:
            record->mcc_id = readIntField(fieldVal);
            break;
        case 8:
            record->mccid_int = readIntField(fieldVal);
            break;
        case 9:
            record->rlmax = readDoubleField(fieldVal);
            break;
        case 10:
            record->rlmin = readDoubleField(fieldVal);
            break;
        case 11:
            record->segside = readStringField(fieldVal);
            break;
        case 12:
            record->statusid = readIntField(fieldVal);
            break;
        case 13:
            record->streetid = readIntField(fieldVal);
            break;
        case 14:
            record->street_group = readIntField(fieldVal);
            break;
        case 15:
            record->start_lat = readDoubleField(fieldVal);
            break;
        case 16:
            record->start_lon = readDoubleField(fieldVal);
            break;
        case 17:
            record->end_lat = readDoubleField(fieldVal);
            break;
        case 18:
            record->end_lon = readDoubleField(fieldVal);
            break;
        default:
            fprintf(stderr, "%d: Unhandled field number %d\n", __LINE__, 
                fieldIndex);
            assert(fieldIndex >= 0 && fieldIndex < NUM_FIELDS);
    }
}

// Reads in an int from a string.
int readIntField(char *fieldString){
    return strtol(fieldString, NULL, NUMERIC_BASE);
}

// reads in a string from a string.
char *readStringField(char *fieldString) {
    char *str = strdup(fieldString);
    assert(str);
    return str;
}

// reads in a double from a string.
double readDoubleField(char *fieldString) {
    return strtod(fieldString, NULL);
}

// Frees data in a datapoint.
void freeData(dataPoint_t *d) {
    if(! d){
        return;
    }
    if(d->address){
        free(d->address);
    };
    if(d->clue_sa){
        free(d->clue_sa);
    };
    if(d->asset_type){
        free(d->asset_type);
    };
    if(d->segside){
        free(d->segside);
    };
    free(d);
}
///////////////// END CITED CODE /////////////////
