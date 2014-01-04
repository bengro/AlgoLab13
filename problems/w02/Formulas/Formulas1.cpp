#include <iostream>
#include <vector>
using namespace std;

void init_mergesort(vector<int> &racers, vector<int> &aux, int left, int right);
void sort(vector<int> &racers, vector<int> &aux, int left, int right);
void merge(vector<int> &racers, vector<int> &aux, int left, int pivot, int right);

vector<unsigned long> answers;

unsigned long overpasses;

int main(int argc, char const *argv[])
{
	
	int testcases;
	cin >> testcases;

	for (int testcase = 0; testcase < testcases; testcase++)
	{
		int size;
		cin >> size;

		vector<int> racers;
		vector<int> aux;

		for (int racer = 0; racer < size; racer++)
		{
		 	int pos;
		 	cin >> pos;
		 	racers.push_back(pos);
		}

		aux = racers;

		overpasses = 0;
		init_mergesort(racers, aux, 0, size-1);
		answers.push_back(overpasses % 10000);
	}

	for(vector<unsigned long>::iterator iter = answers.begin(); iter != answers.end(); iter++) {
		cout << *iter << "\n";
	}

	return 0;
}

void init_mergesort(vector<int> &racers, vector<int> &aux, int left, int right) {
	int pivot = (left + right) / 2;

	sort(racers, aux, left, pivot);
	sort(racers, aux, pivot + 1, right);
	merge(racers, aux, left, pivot, right);
}

void sort(vector<int> &racers, vector<int> &aux, int left, int right) {
	if (left < right)
	{	
		int pivot = (left + right) / 2;
		sort(racers, aux, left, pivot);
		sort(racers, aux, pivot+1, right);
		merge(racers, aux, left, pivot, right);
	}
}

void merge(vector<int> &racers, vector<int> &aux, int left, int pivot, int right) {
	
	unsigned long local_overpasses = 0;
	int a = left;
	int i = left;
	int j = pivot + 1; 

	// TODO: if left - right smaller than threshold, then use insertion sort!
	while( (i <= pivot) && (j <= right) )
	{
		if (racers[i] == racers[j]) {
			aux[a++] = racers[i++]; 
		}
		if (racers[i] < racers[j]) { 
			aux[a++] = racers[i++]; 
		}
		if (racers[i] > racers[j]) { 
			aux[a++] = racers[j++];
			local_overpasses += (pivot + 1 - left) - (i - left); 	
		}

	}

	if (i <= pivot) for (int k = i; k <= pivot; k++) { aux[a++] = racers[k]; i++; } 
	if (j <= right) for (int k = j; k <= right; k++) { aux[a++] = racers[k]; j++; }

	//TODO: make it faster!
	for (int k = left; k <= right; k++) { 
		racers[k] = aux[k];
	}

	overpasses += local_overpasses;
}