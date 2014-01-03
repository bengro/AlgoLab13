#include <iostream>
#include <vector>
#include <queue>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel	 	K;
typedef CGAL::Delaunay_triangulation_2<K> 					    Delaunay;
typedef Delaunay::All_faces_iterator                            AFI;
typedef map<Delaunay::Face_handle, int>                         StateMap;

int testcase(int N) {
    vector<K::Point_2> points;
    for(int n = 0; n < N; ++n) {
        double x, y; cin >> x >> y;
        points.push_back(K::Point_2(x, y));
    }
    
    int M; cin >> M;
    vector<pair<K::Point_2, double> > people;
    for(int m = 0; m < M; ++m) {
        double x, y, d; cin >> x >> y >> d;
        people.push_back(make_pair(K::Point_2(x, y), d));
    }

    StateMap state;
    Delaunay t;
	t.insert(points.begin(), points.end());
    
    for(int p = 0; p < M; ++p) {
        K::Point_2 coord = people[p].first;
        K::FT d = people[p].second;
        
        if(CGAL::squared_distance(coord, t.nearest_vertex(coord)->point()) < d) {
            cout << "n";
            continue;
        }

        Delaunay::Face_handle start_face = t.locate(coord);
        if(t.is_infinite(start_face)) {
            cout << "y";
            continue;
        }

        bool stop = false;
        queue<Delaunay::Face_handle> fifo;
        fifo.push(start_face);
        int bfs_id = p+1;
        state[start_face] = bfs_id;
        while(!fifo.empty()) {
            Delaunay::Face_handle f = fifo.front(); fifo.pop();
            for(int e = 0; e < 3; ++e) {
                K::Segment_2 seg = t.segment(f, e);
                Delaunay::Face_handle neighbour = f->neighbor(e);
                
                if((seg.squared_length() >= 4*d) && state[neighbour] != bfs_id){
                    if(t.is_infinite(neighbour)) {
                        cout << "y";
                        stop = true;
                        break;
                    }
                    fifo.push(neighbour);
                    state[neighbour] = bfs_id;
                }
            }
            if(stop) break;
            
        }
        if(!stop) cout << "n";
    }
    cout << "\n";
}

int main() {
    while(true) {
        int N; cin >> N;
        if(N == 0) return 0;
        testcase(N);
    }
}
