#include "olympicStats_header.h"



void free(Pathl_list al){
	while(al->head != null){
		Pathl t = al->head;
		al->head = al->head->next;
		delete t;
	}
	delete al;
}

void getInfo(Pathl_list al, Pathl a){
	cout << "Enter the athlete name: ";
	cin >> a->name;
	float n;
	char c;
	cout << "Enter the rates: " << endl;
	int len = al->judgeRank;
	for(int i=0;i<len;i++){
		cin >> n >> c;
		a->rate[i] = n;
	}
	a->avg = calAvg(a->rate, al->judgeRank);
}

void printMenu(){
	cout << "0. Exit\n"
	"1. Entering judges rating for an athlete\n"
	"2. Display judges rating for an athlete\n"
	"3. Display rating average for an athlete\n"
	"4. Prints a summary of the average rating of the gymnasts in the system\n"
	"5. Print the expected value vector of all ratings\n"
	"6. Print the shared covariance matrix of all ratings" << endl;
}

int input(){
	int n;
	cout << "Enter your choice: ";
	cin >> n;
	return ( ( ( n >= 0 ) && ( n <= 6 ) ) ? n : -1 );
}

void init(Pathl_list al){
	al->size = 0;
	al->head = null;
	al->tail = null;
}

void addToList(Pathl_list al, Athl a){
	Pathl temp = searchInList(al, a.name);
	if(al->size == al->MAX_ATHLETES)	cerr << "ERROR: MAX_ATHLETES exceeded" << endl;
	else if( temp != null){
		strcpy(temp->name,a.name);
		for(int i=0;i<al->judgeRank;i++)	temp->rate[i] = a.rate[i];
		temp->avg = a.avg;
	}
	else{
		temp = new Athl;
		if(al->size == 0)	al->head = temp;
		strcpy(temp->name,a.name);
		for(int i=0;i<al->judgeRank;i++)	temp->rate[i] = a.rate[i];
		temp->avg = a.avg;
		temp->next = null;
		al->tail->next = temp;
		al->tail = al->tail->next;
		al->size += 1;
	}
}

Pathl searchInList(Pathl_list al, char *name){
	if(al->size == 0)	return null;
	if(al->size == 1)
		if(!strcmp(al->head->name, name))
			return al->head;
	Pathl t = al->head;
	while(t->next != null){
		if(!strcmp(t->name, name))
			return t;
		t = t->next;
	}
	return null;
}

void displayRatingForAthlete(Pathl_list al){
	char name[17];
	cout << "Enter an athlete name: ";
	cin >> name;
	Pathl t = searchInList(al, name);
	if(t == null)	cerr << "ERROR: " << name << " does not exist" << endl;
	else{
		cout << t->name << " = [";
		for(int i=0;i<al->judgeRank;i++)	cout << t->rate[i] << " ";
		cout << "]" << endl;
	}
}

void displayAverageForAthlete(Pathl_list al){
	char name[17];
	cout << "Enter an athlete name: ";
	cin >> name;
	Pathl t = searchInList(al, name);
	if(t == null)	cerr << "ERROR: " << name << " does not exist" << endl;
	else
		cout << name << ", " << t->avg << endl;
}

void printAvgOfRatesForAllAthletes(Pathl_list al){
	if(al->size == 0)	cerr << "ERROR: no records in the system" << endl;
	else{
		Pathl t = al->head;
		while(t->next != null){
			cout << t->name << ", " << t->avg << endl;
			t = t->next;
		}
	}
}

float calAvg(float * a, int len){
	float sum = 0;
	for(int i=0;i<len;i++)	sum += a[i];
	return sum / len;
}

void printExpectedValueVector(Pathl_list al){
	if(al->size == 0)	cerr << "ERROR: no records in the system" << endl;
	else{
		cout << "mean = [ ";
		for(int i=0;i<al->judgeRank;i++){
			Pathl t = al->head;
			float sum = 0;
			while(t->next != null){
				sum += t->rate[i];
				t = t->next;
			}
			cout << sum/al->judgeRank << " ";
		}
		cout << "]" << endl;
	}
}

void printSharedCovarianceMatrix(Pathl_list al){
	if(al->size == 0)	cerr << "ERROR: no records in the system" << endl;
	else{
		float rates[al->judgeRank][al->size+1];
		for(int i=0;i<al->judgeRank;i++){
			Pathl t = al->head;
			int j=0;
			float sum = 0;
			while(t->next != null){
				rates[i][j] = t->rate[i];
				sum += t->rate[i];
				t = t->next;
				j++;
			}
			rates[i][j] = sum/al->judgeRank;
		}
		float cov[al->judgeRank][al->judgeRank];
		int m = (al->judgeRank == 1) ? 1 : al->judgeRank - 1;
		for(int i=0;i<al->judgeRank;i++){
			for(int j=i;j<al->judgeRank;j++){
				float sum = 0;
				for(int k=0;k<al->size;k++)
					sum += (rates[i][k] - rates[i][al->size])*(rates[j][k] - rates[j][al->size]);
				cov[i][j] = cov[j][i] = sum/m;
			}
		}
		cout << "cov = [ ";
		for(int i=0;i<al->judgeRank;i++){
			for(int j=0;j<al->judgeRank;j++)
				cout << cov[i][j] << " ";
			cout << endl;
		}
		cout << "]" << endl;
	}
}
