#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Boat {
	int ring;
	int length;
	bool taken;
	
};
inline bool operator<( const Boat& lhs, const Boat& rhs ) {
    return lhs.ring < rhs.ring;
}
inline bool operator<( int lhs, const Boat& rhs ) {
    return lhs <= rhs.ring;
}
inline bool operator<(const Boat& lhs, const int &val) {
	return (lhs.ring < val);
}

void testcase() {
	int boats; cin >> boats;
	vector<Boat> boat_list;

	for (int i = 0; i < boats; ++i)
	{
		int length, ring; cin >> length >> ring;
		Boat boat;
		boat.length = length;
		boat.ring = ring;
		boat.taken = false;
		boat_list.push_back(boat);
	}

	std::sort(boat_list.begin(), boat_list.end());

	int counter = 1;
	int rightmost = boat_list[0].ring;
	boat_list[0].taken = true;

	// Problem 1: rightmost < boat_list.back().ring ... meaning, we stopped too early, neglecting the last boat.
	// Problem 2: Endless loop in the scenario of just one boat... as righmost = boat_list.back().ring.
	while((rightmost <= boat_list.back().ring) && (boat_list.size() != 1)) {

		vector<Boat>::iterator up = lower_bound(boat_list.begin(), boat_list.end(), rightmost);
		int index = (up - boat_list.begin());
		int next = index;
		//cerr << "next: " << next << "\n";

		// check if already taken, if yes, move pointer to the right.
		if(boat_list[next].taken == true) next++;

		int local_rightmost;
		int min_rightmost = -1;
		int boat_index;
		do {
			int ring = boat_list[next].ring;
			int left = ring - rightmost;
			int right = boat_list[next].length - left;

			if(right < 0) local_rightmost = ring;
			else local_rightmost = ring + right;
			
			//cerr << "local_rightmost: " << local_rightmost << " min_rightmost: " << min_rightmost << "\n"; 
			if((local_rightmost < min_rightmost) || (min_rightmost == -1)) { 
				min_rightmost = local_rightmost; 
				boat_index = next;
				//cerr << "local minimum set: " << local_rightmost << " boat_index: " << boat_index << "\n";
			}
			next++;
		}
		// Problem 4: while condition was wrong - running through example revealed mistake.
		while( (boat_list[next].ring < min_rightmost) && (next < boat_list.size()) );

		boat_list[boat_index].taken = true;
		rightmost = min_rightmost;
		counter++;

		// Problem 2: break out as soon as the last boat has been assigned. 
		// Needed because rightmost <= boat_list.back().ring. boat_index not available in while header.
		if(boat_index == (boat_list.size() - 1)) break;
	}
	
	cout << counter << "\n";
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}