#include "Header.h"

/*************************************************************
* Function: readLine ()										*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function reads one line from an			*
*              FitbitDqta.csv file                          *
* Input parameters: An file pointer and the pointer			*		
*					to the char								*
* Returns: the line string from the file                    *
* Preconditions: The file must already be open.				*
* Postconditions: the line that is read	           			*
*                 from the file is returned.				*
*************************************************************/

char * readLine(FILE *infile, char *line)
{
	fgets(line, 200, infile);

	return line;
}

/*************************************************************
* Function: checkForNull ()									*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will check for any empty data	*
*              int pLine array								*
* Input parameters: A pLine array that contains string		*	
* from the file												*
* Returns: Nothing											*
* Preconditions: pLine has fetched the string fromthe file	*
* Postconditions: modify the string if any empty values 	*
*                 found but will not modify the original file*
*************************************************************/

void checkForNull(char pLine[])
{
	char array[40]; // temporary storage when two commas are found
	int count=0; // to count the commas
	for (int i = 0; pLine[i] != '\n'; i++)
	{
		if (pLine[i] == ','&& pLine[i + 1] == ',')
		{
			strncpy(array, pLine, ++i);
			array[i++] = '0';
			strcpy(array + i, pLine + i - 1);
			strcpy(pLine, array);
		}

	}

	for (int i = 0; count!=6; i++)
	{
		if (pLine[i] == ',')
		{
			count++;
		}
		if (count == 6 && pLine[i+1] == '\n') // if there are 6 commas and the char next to it is \n, it means we are missing an item
		{
			pLine[i+1] = '0';
			pLine[i + 2] = '\n';
		}
	}
	
}

/*************************************************************
* Function: makeToken ()									*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will make token whenever a 	*
*              comma is found in pLine array				*
* Input parameters: A pLine array that contains string		*
*					from the file, and Fitbit struct array	*
* Returns: Nothing											*
* Preconditions: pLine has fetched the string from the file	*
*				and empty values are modified				*
* Postconditions: modify the string with strtok when the 	*
*                 comma is found and store in struct values	*
*************************************************************/

void makeTokens(char pLine[], FitbitData data[])
{
	static int count = 0; //count will not change whenever this function is called
	char *pToken = NULL; // pToken will point to each token when a comma is found
	
	// minute
	pToken = strtok(pLine, ",");
	strcpy(data[count].minute, pToken);

	//calories
	pToken = strtok(NULL, ",");
	data[count].calories = (atof(pToken));

	//distance
	pToken = strtok(NULL, ",");
	data[count].distance = atof(pToken);

	//floors
	pToken = strtok(NULL, ",");
	data[count].floors = atoi(pToken);

	//heart rate
	pToken = strtok(NULL, ",");
	data[count].heartRate = atoi(pToken);

	//steps
	pToken = strtok(NULL, ",");
	data[count].steps = atoi(pToken);

	//sleeplevel
	pToken = strtok(NULL, ",");
	data[count].sleepLevel = atoi(pToken);
	++count;
}

/*************************************************************
* Function: maxSteps ()										*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will check at what time the 	*
*              maximum steps were taken						*
* Input parameters: A FitbitData struct array and time array*
* Returns: value of maximum steps 							*
* Preconditions: data has been stored in FitbitData array	*
* Postconditions: max steps are found and the time will be  *
*				stored in time array						*
*************************************************************/

int maxSteps(FitbitData data[], char time[40])
{
	int max = data[0].steps;
	int i, j;
	for (i = 0; i < 1440; i++)
	{
		if (data[i].steps >= max)
		{
			max = data[i].steps;
			j = i; // j will keep track when the final maximum is found
		}
	}
	strcpy(time, data[j].minute);
	return max;
}

/*************************************************************
* Function: poorestSleep ()									*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will check the longest range 	*
*              of poor sleep								*
* Input parameters: A FitbitData struct array				*
*				start array and end array to store the time	*
* Returns: total of the longest sleep 						*
* Preconditions: data has been stored in FitbitData array	*
* Postconditions: longest sleep range is found				*		
*			and the start time will be stored in start array*
*		    and the end time will be stored in end array	*	
*************************************************************/

int poorestSleep(FitbitData data[], char start[40], char end[40])
{
	int total = 0; int count=0;
	int poorS[50]; //to store the total of every range
	int max = data[0].sleepLevel;
	int j=0; //j for the index for poorS[50] and will be incremented after every range is stored
	for (int i = 0; i < 1440; i++)
	{
		if (data[i].sleepLevel> 1 && data[i].sleepLevel<4)
		{
			total += data[i].sleepLevel;
			strcpy(start, data[i].minute);
				
			if ((data[i + 1].sleepLevel <= 1 || data[i + 1].sleepLevel > 4))
				{
					strcpy(end, data[i].minute);
					poorS[j] = total;
					j++;
					total = 0;
				}	
		}

	}
	// seraching for maximum range of poorest sleep in poorS[50]
	for (int i = 0; i < 50; i++)
	{
		if (poorS[i] > max)
		{
			max = poorS[i];
		}
	}
	
return max;
}
/*************************************************************
* Function: totalDistance ()								*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will sum up the total distance *
*              in 24 hours									*
* Input parameters: A FitbitData struct array				*
* Returns: value of total distnce 							*
* Preconditions: data has been stored in FitbitData array	*
* Postconditions: total distance is summed up				*
*************************************************************/

double totalDistance(FitbitData data[])
{
	double total = 0.0;
	for (int i = 0; i < 1440; i++)
	{
		total =(double) total+ data[i].distance;
	}
	return total;
}

/*************************************************************
* Function: totalCalories ()								*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will sum up the total calories *
*              burned in 24 hours							*
* Input parameters: A FitbitData struct array				*
* Returns: value of total calories burned					*
* Preconditions: data has been stored in FitbitData array	*
* Postconditions: total calories is summed up				*
*************************************************************/


double totalCalories(FitbitData data[])
{
	double total = 0.0;
	for (int i = 0; i < 1440; i++)
	{
		total = (double)total + data[i].calories;
	}
	return total;
}

/*************************************************************
* Function: totalSteps ()									*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will sum up the total steps	*
*              taken in 24 hours							*
* Input parameters: A FitbitData struct array				*
* Returns: value of total steps 							*
* Preconditions: data has been stored in FitbitData array	*
* Postconditions: total steps is summed up					*
*************************************************************/


int totalSteps(FitbitData data[])
{
	double total = 0;
	for (int i = 0; i < 1440; i++)
	{
		total += data[i].steps;
	}
	return total;
}

/*************************************************************
* Function: totalFloors ()									*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will sum up the total floors	*
*               in 24 hours									*
* Input parameters: A FitbitData struct array				*
* Returns: value of total floors 							*
* Preconditions: data has been stored in FitbitData array	*
* Postconditions: total floors is summed up					*
*************************************************************/
int totalFloors(FitbitData data[])
{
	int total = 0;
	for (int i = 0; i < 1440; i++)
	{
		total += data[i].floors;
	}
	return total;
}

/*************************************************************
* Function: averageHeartRate ()								*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will calculate the average 	*
*              of heart rate excluding null values			*
* Input parameters: A FitbitData struct array				*
* Returns: value of average heart rate						*
* Preconditions: data has been stored in FitbitData array	*
* Postconditions: Average heart frate is calculated			*
*************************************************************/
int averageHeartRate(FitbitData data[])
{
	int total = 0;
	int count = 0;
	for (int i = 0; i < 1440; i++)
	{
		if (data[i].heartRate != 0) // will not count the null values 
		{
			total += data[i].heartRate;
			count++;
		}
	}
	return total/count;
}

/*************************************************************
* Function: writeFile ()			`						*
* Date Created:												*
* Date Last Modified:                                       *
* Description: This function will write the calculated		*	
*			values in the file Results.csv 					*
* Input parameters: A FitbitData struct array and the outfile
*					to write the results in					*
* Returns: Nothing											*
* Preconditions: data has been stored in FitbitData array	*	
*				and all functions for calculations are		*	
*				ready to be called							*		
* Postconditions: Results are written in the file			*
*************************************************************/
void writefile(FILE *Outfile, FitbitData data[])
{
	char start[40], end[40], time[40];
	
	//call all the functions and store the values
	double TotalCaloriesBurned = totalCalories(data);
	double TotalDistanceWalked = totalDistance(data);
	int TotalFloorsWalked = totalFloors(data);
	int TotalStepsTaken = totalSteps(data); //may be problems
	double AverageHeartrate = averageHeartRate(data);
	int MaxStepsTaken = maxSteps(data, time);
	int LongestPoorSleep = poorestSleep(data, start, end);


	fprintf(Outfile, "Total Calories = %f\nTotal Distance = %f\nTotal Floors = %d \n", TotalCaloriesBurned, TotalDistanceWalked, TotalFloorsWalked);
	fprintf(Outfile, "Total Steps = %d\nAvg Hearrate = %f\n", TotalStepsTaken, AverageHeartrate);
	fprintf(Outfile, "Max Steps = %d at %s\nLongest poor sleep = %d from %s to %s \n",MaxStepsTaken, time, LongestPoorSleep, start, end);


	printf("Press enter to continue...\n");
	getchar();
}
