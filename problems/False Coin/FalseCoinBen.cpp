#include <iostream>
#include <vector>
using namespace std;

int solve(int numberOfCoins, vector< pair<char, vector<int> > > equations);

vector<int> answers;

int main(int argc, char const *argv[])
{
	int datasets;
	cin >> datasets;

	for (int dataset = 0; dataset < datasets; dataset++) {
		//cout << "data set: " << dataset << "\n";

		int numberOfCoins, numberOfWeighings;
		cin >> numberOfCoins >> numberOfWeighings;

		vector< pair<char, vector<int> > > equations;
		equations.clear();
		for (int i = 0; i < numberOfWeighings; i++) {
			//cout << "reading weighing: " << i << " \n";
			int coinsInPan;
			cin >> coinsInPan;
			
			vector<int> coins;
			coins.clear();
			for (int j = 0; j < (coinsInPan*2); j++)
			{
				int coin;
				cin >> coin;
				coins.push_back(coin);
				//cout << "reading coin: " << j << "\n";
			}

			char operatorSymbol;
			cin >> operatorSymbol;

			equations.push_back(make_pair(operatorSymbol, coins));
		}


		int result = solve(numberOfCoins, equations);
		if (result != 0)
		{
			answers.push_back(result);
		} else {
			answers.push_back(result);
		}

	}

	for (vector<int>::iterator answer = answers.begin(); answer != answers.end(); answer++) {
		cout << *answer << "\n";
	}

	return 0;
}

int solve(int numberOfCoins, vector< pair<char, vector<int> > > equations) {

	vector<int> falseCoins;

	for(int n = 1; n <= numberOfCoins; n++) {
		int coin_id = n;

		bool holding = true;
		//cout << "coin_id: " << coin_id << "\n";

		vector<int> lightWeightedCoins (numberOfCoins+1, 1);
		lightWeightedCoins.at(coin_id) = 0;
		vector<int> heavyWeightedCoins (numberOfCoins+1, 0);
		heavyWeightedCoins.at(coin_id) = 1;

		//cout << "initialized weighted vectors \n";

		for (vector< pair<char, vector<int> > >::iterator eq_it = equations.begin(); eq_it != equations.end(); eq_it++)
		{
			//cout << "evaluationg equation... coin_id: " << coin_id << "\n";
			vector<int> coins = eq_it->second;
			int pan = coins.size() / 2;

			vector<int> leftSum (2, 0);
			vector<int> rightSum (2, 0);

			int i = 1; 
			for (vector<int>::iterator coin_it = coins.begin(); coin_it != coins.end(); coin_it++)
			{
				//cout << "iterating over coin: " << *coin_it << " adding: " << lightWeightedCoins[*coin_it] << "\n";
				
				if (i <= pan) {
					leftSum[0] = leftSum[0] + lightWeightedCoins[*coin_it];
					leftSum[1] = leftSum[1] + heavyWeightedCoins[*coin_it];
				} else {
					rightSum[0] = rightSum[0] + lightWeightedCoins[*coin_it];
					rightSum[1] = rightSum[1] + heavyWeightedCoins[*coin_it];
				}

				i++;
			}
			//cout << "coin_id: " << coin_id << " leftSum light: " << leftSum[0] << " rightSum light: " << rightSum[0] << "\n";
			//cout << "coin_id: " << coin_id << " leftSum heavy: " << leftSum[1] << " rightSum heavy: " << rightSum[1] << "\n";

			char symbol = eq_it->first;
			if (symbol == '<')
			{
				bool verdict_light = leftSum[0] < rightSum[0];	// assuming false coin is lighter than others
				bool verdict_heavy = leftSum[1] < rightSum[1];	// assuming false coin is heavier than others

				if (verdict_light || verdict_heavy)
				{	
					// possible
				} else {
					holding = false;
					break;
				}
			}
			if (symbol == '>')
			{
				bool verdict_light = leftSum[0] > rightSum[0];	// assuming false coin is lighter than others
				bool verdict_heavy = leftSum[1] > rightSum[1];	// assuming false coin is heavier than others

				if (verdict_light || verdict_heavy)
				{
					// possible
				} else {
					holding = false;
					break;
				}
			}
			if (symbol == '=')
			{
				bool verdict_light = leftSum[0] == rightSum[0];	// assuming false coin is lighter than others
				bool verdict_heavy = leftSum[1] == rightSum[1];	// assuming false coin is heavier than others

				if (verdict_light || verdict_heavy)
				{
					// possible
					//cout << "checking equation: " << leftSum[0] << "=" << rightSum[0] << " OR " << leftSum[1] << "=" << rightSum[1];
				} else {
					//cout << "does not hold...";
					holding = false;
					break;
				}
			}

		}

		if (holding == true)
		{	
			falseCoins.push_back(coin_id);
		}

	}

	if(falseCoins.size() == 1) {
		return falseCoins[0];
	} else {
		return 0;
	}

}