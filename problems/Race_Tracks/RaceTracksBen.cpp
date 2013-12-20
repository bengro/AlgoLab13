#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

vector<string> answers;

int main(int argc, char const *argv[])
{

	int testsets;
	cin >> testsets;

	for (int testset = 0; testset < testsets; testset++) {

		int m, n;
		cin >> m >> n;

		int s1, s2;
		cin >> s1 >> s2;

		int f1, f2;
		cin >> f1 >> f2;

		int numberObstacles;
		cin >> numberObstacles;

		vector< vector<bool> > obstacles (m, vector<bool>(n));
		for (int o = 0; o < numberObstacles; o++)
		{
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;

			for (int x = x1; x <= x2; x++)
			{
				for (int y = y1; y <= y2; y++) {
					obstacles[x][y] = true;		
				}
			}
		}

		if (obstacles[f1][f2] == true)
		{
			answers.push_back("No solution.");
			continue;
		}

		// visited states
		vector< vector< set<pair<int,int> > > > visited(m, vector<set<pair<int,int> > >(n) );

		// fifo queue for BFS
		queue<pair< pair< pair<int, int>, int>, pair<int, int> > > fifo;
		
		// adding starting point to fifo queue
		pair<pair< pair<int, int>,int>, pair<int, int> > start_point = make_pair( make_pair( make_pair(s1,s2) , 0), make_pair(0,0));
		fifo.push(start_point);
		visited[s1][s2].insert(make_pair(0,0));

		bool success = false;

		while (!fifo.empty()) {
			pair<
				pair< 
					pair<int, int>, int>, 
					pair<int,int> 
				> current_element = fifo.front();

			// remove current element
			fifo.pop();

			// add to visited
			int current_x = current_element.first.first.first;
			int current_y = current_element.first.first.second;
			int current_hops = current_element.first.second;
			int current_xv = current_element.second.first;
			int current_yv = current_element.second.second;
			
			if ( (current_x == f1) && (current_y == f2) )
			{
				stringstream ss;
				ss << "Optimal solution takes " << current_hops << " hops.";
				answers.push_back(ss.str());
				success = true;
				break;
			}

			// get children, add to queue
			for (int xv = -1; xv <= 1; xv++)
			{
				for (int yv = -1; yv <= 1; yv++) {

					// updated velocity
					int new_vx = current_xv + xv;
					int new_vy = current_yv + yv;

					// potential x and y coordinates
					int new_x = current_x + new_vx; 
					int new_y = current_y + new_vy;

					// check for velocity range (-3,3), grid range (m,n) and obstacles
					if ((new_vx <= 3) && (new_vy <= 3)
						&& (new_vx >= -3) && (new_vy >= -3)
						&& (new_x < m) && (new_y < n)
						&& (new_y >= 0) && (new_x >= 0)
						&& obstacles[new_x][new_y] != true)
					{
						pair<int, int> child_velocity = make_pair(new_vx, new_vy);
						if (visited[new_x][new_y].find(child_velocity) == visited[new_x][new_y].end())
						{

							if ( (new_x == f1) && (new_y == f2) )
							{
								stringstream ss;
								ss << "Optimal solution takes " << current_hops + 1 << " hops.";
								answers.push_back(ss.str());
								success = true;
								goto loopend;
							}

							pair< pair<int, int>, int> child_position = make_pair(make_pair(new_x, new_y), current_hops + 1);
							pair< pair< pair<int, int>, int>, pair<int,int> > fifo_element = make_pair(child_position, child_velocity);
							fifo.push(fifo_element);

							// add to visited nodes
							visited[new_x][new_y].insert(child_velocity);
						}
					}
				}
			}

			if(success == true) {
				loopend:
					break;
			}

		}		

		if (success == false) answers.push_back("No solution.");
	}
	

	for (vector<string>::iterator iter = answers.begin(); iter != answers.end(); iter++) 
	{
		cout << *iter << "\n";
	}

	return 0;
}