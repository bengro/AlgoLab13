#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef Delaunay::Finite_edges_iterator FEI;
typedef Delaunay::Finite_vertices_iterator FVI;

void testcase(int N) {
	vector<K::Segment_2> rect;
	int x1, y1, x2, y2; 
	cin >> x1 >> y1 >> x2 >> y2;
	rect.push_back(K::Segment_2(K::Point_2(x1, y1), K::Point_2(x1, y2)));
	rect.push_back(K::Segment_2(K::Point_2(x1, y2), K::Point_2(x2, y2)));
	rect.push_back(K::Segment_2(K::Point_2(x2, y2), K::Point_2(x2, y1)));
	rect.push_back(K::Segment_2(K::Point_2(x2, y1), K::Point_2(x1, y1)));
	
	vector<K::Point_2> points;
	for(int n = 0; n < N; ++n) {
		int x, y; cin >> x >> y;
		points.push_back(K::Point_2(x, y));
	}
	
	vector<pair<K::FT, pair<Delaunay::Vertex_handle, Delaunay::Vertex_handle> > > lines;
	Delaunay t;
	t.insert(points.begin(), points.end());
	for(FEI edge = t.finite_edges_begin(); edge != t.finite_edges_end(); ++edge) {
		Delaunay::Vertex_handle v1 = edge->first->vertex((edge->second + 1) % 3);
		Delaunay::Vertex_handle v2 = edge->first->vertex((edge->second + 2) % 3);
		K::Segment_2 seg = t.segment(edge);
		K::FT length = CGAL::sqrt(seg.squared_length());
		lines.push_back(make_pair(length, make_pair(v1, v2)));
	}
	
	for(FVI v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
		Delaunay::Vertex_handle vertex = v;
		K::FT min_dist; bool min_set = false;
		for(int i = 0; i < 4; ++i) {
			K::FT dist = CGAL::squared_distance(rect[i], v->point());
			if(dist < min_dist || !min_set) { min_dist = dist; min_set = true; }
		}
		lines.push_back(make_pair(CGAL::sqrt(min_dist)*2, make_pair(vertex, vertex)));
	}
	sort(lines.begin(), lines.end());
	
	int dead = 0;
	int time = 0;
	int pointer = 0;
	bool not_printed = true;
	set<Delaunay::Vertex_handle> bact;
	while(dead < N) {
		K::FT length_t = 2 * (pow(time, 2.0) + 0.5);
		while(lines[pointer].first <= length_t) {
			if(dead == 0) cout << time << " ";
			
			pair<Delaunay::Vertex_handle, Delaunay::Vertex_handle> p = lines[pointer].second;
			if(p.first == p.second) bact.insert(p.first);
			else { bact.insert(p.first); bact.insert(p.second); }
			dead = bact.size();
			
			if(dead / (double) N > 0.5 && not_printed) { cout << time << " "; not_printed = false; }
			if(dead == N) { cout << time << "\n"; break; }	
			
			if(pointer+1 == lines.size()) break;
			else ++pointer;
		}
		++time;
	}
}

int main() {
	while(true){
		int N; cin >> N;
		if(N == 0) return 0;
		testcase(N);
	}
}
