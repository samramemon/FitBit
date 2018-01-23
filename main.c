/*******************************************************************************
* Programmer: Samra Memon													  *
* Class: CptS 122				                                              *
* Programming Assignment: Assignment 1                                        *
* Date:        6/13/2017                                                      *
*                                                                             *
* Description: This program the  calculates the Total Calories,				  *			
*			Total Distance, Total Floors, Total Steps, Avg Hearrate,		  *		
*			Max Steps, Sleep range from the FitbitData.csv file				  *
*                                                                             *
* Relevant Formulas: Refer to each function definition.                       *
*                                                                             *
* Format of record in input file (FitbitData.csv): 
*					23:42:00	0.968900025	0	0	77	0	1				  *
*																			  *
* Format of output file (Results.csv)										  *
*				Total Calories = 2294.936577								  *
*				Total Distance = 6.624171									  *
*				Total Floors = 31											  *
*				Total Steps = 15415											  *
*				Avg Hearrate = 70.000000									  *
*				Max Steps = 120 at 10:40:00									  *
*				Longest poor sleep = 18 from 23:50:00 to 23:56:00			  *
******************************************************************************/
#include "Header.h"
int main(void)
{
	FILE *infile = NULL, *outfile = NULL;
	FitbitData data[1440] = { { "" } };
	char pLine[200] = "";
	/* Open the input and output files before accessing them */
	
	infile = fopen("FitbitData.csv", "r");
	outfile = fopen("Results.csv", "w");


	/* Could not open input file. May be because do not have read permissions
	or the file does not exist, etc. */
	if (infile == NULL)
	{
		printf("WARNING: Could not open %s\n", "FitbitData.csv");
	}


	/* Could not open input file. May be because do not have write permissions
	or the file does not exist, etc. */
	if (outfile == NULL)
	{
		printf("WARNING: Could not open %s\n", "Results.csv");
	}
	else 
	{
		readLine(infile, pLine);
		while (!feof(infile))
		{
			readLine(infile, pLine);
			checkForNull(pLine);
			makeTokens(pLine, data);
		}
		writefile(outfile, data);
	}
	/* Close the input and output files */
	fclose(infile);
	fclose(outfile);
	return 0;
}