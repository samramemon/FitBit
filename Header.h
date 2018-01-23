#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;
typedef struct fitbit
{
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

char * readLine(FILE *infile, char *line);
void checkForNull(char pLine[]);
void makeTokens(char pLine[], FitbitData data[]);
double totalDistance(FitbitData data[]);
int totalFloors(FitbitData data[]);
int totalSteps(FitbitData data[]);
double totalCalories(FitbitData data[]);
void writefile(FILE *Outfile, FitbitData data[]);