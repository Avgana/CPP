#include "olympicStats_header.h"
int MAX_ATHLETES;

int main(int argc, char* argv[]){
    cout << argc << ", " << argv[0] << ", " << argv[1] << ", " << argv[2] << endl;
	if((argc != 3) || !(argv[1] > 0 && argv[2] > 0)){
		cerr << "ERROR: USAGE <executable> NUM_REFEREES MAX_ATHLETES" << endl;
		exit(0);
	}
	Pathl_list al = new Athl_list;
	(*al).judgeRank = atoi(argv[1]);
	(*al).MAX_ATHLETES = atoi(argv[2]);

	init(al);
	while(1){
		printMenu();
		switch(input()){
			case 0:
				free(al);
				exit(0);
				break;
			case 1:
				Athl a;
				a.rate = new float[(*al).judgeRank];
				getInfo(al, &a);
				addToList(al, a);
				break;
			case 2:
				displayRatingForAthlete(al);
				break;
			case 3:
				displayAverageForAthlete(al);
				break;
			case 4:
				printAvgOfRatesForAllAthletes(al);
				break;
			case 5:
				printExpectedValueVector(al);
				break;
			case 6:
				printSharedCovarianceMatrix(al);
				break;
			default:
				cerr << "ERROR: invalid command" << endl;
				break;
		}
	}
}
