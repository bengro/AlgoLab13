/*
* Benjamin Gröhbiel
* Domino
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main (int argc, const char *argv[]) 
{

  ios_base::sync_with_stdio(false);
  
  int testcases;
  cin >> testcases;
  
  map< int, vector<int> > index;

  for (int testcase = 0; testcase < testcases; testcase++) {
    
    long int dominoes;
    cin >> dominoes;

    for (int dominoPos = 1; dominoPos <= dominoes; dominoPos++) {
      int height;
      cin >> height;
      index[testcase].push_back(height);
    }

  }

  for (map<int, vector<int> >::iterator it = index.begin(); it != index.end(); it++) {
      //cout << "Testcase: " << it->first << " Tiles: " << it->second.size() << "\n";

      vector<int> tiles = it->second;

      if (tiles.size() == 0) {
        cout << 0;
      } 
      else 
      {  
        int intervalRight = 0;
        int iteration = 0;
        int counter = 0;

        for (vector<int>::iterator tile_it = tiles.begin(); tile_it != tiles.end(); tile_it++) {
          
          if (iteration > intervalRight) {
              //cout << "Break; iteration > intervalRight \n";
              break;
          }
          
          int h = *tile_it;
          int newIntervalRight = h + iteration - 1;

          if(newIntervalRight > intervalRight) {
            intervalRight = newIntervalRight;
          }

          iteration++;
          //cout << "intervalRight: " << intervalRight << " iteration: " << iteration << "\n";
          counter++;
        }

        cout << counter << "\n";

      }
  }
  
  return 0;

}
