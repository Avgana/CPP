#ifndef olympicStats_header
#define olympicStats_header

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#define null NULL

using namespace std;

typedef struct athlete{
	char name[17];
	float *rate;
	float avg;
	struct athlete *next;
}Athl, *Pathl;

typedef struct athlete_List{
	struct athlete *head;
	struct athlete *tail;
	int size;
	int judgeRank;
	int MAX_ATHLETES;
}Athl_list, *Pathl_list;


void free(Pathl_list al);
void getInfo(Pathl_list al, Pathl a);
void printMenu();
int input();
void init(Pathl_list al);
void addToList(Pathl_list al, Athl a);
Pathl searchInList(Pathl_list al, char *name);
void displayRatingForAthlete(Pathl_list al);
void displayAverageForAthlete(Pathl_list al);
void printAvgOfRatesForAllAthletes(Pathl_list al);
float calAvg(float * a, int len);
void printExpectedValueVector(Pathl_list al);
void printSharedCovarianceMatrix(Pathl_list al);

#endif // olympicStats_header
