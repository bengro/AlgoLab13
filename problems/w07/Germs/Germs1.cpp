#include <iostream>
#include <vector>
#include <cmath>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel	 	K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>     Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> 					Delaunay;
typedef Delaunay::Finite_edges_iterator                         FEI;
typedef Delaunay::Finite_vertices_iterator                      FVI;

void testcase(int N) {
    double left, bottom, right, top; cin >> left >> bottom >> right >> top;
    vector<K::Segment_2> rectangle;
    rectangle.push_back(K::Segment_2(K::Point_2(left, bottom), K::Point_2(left, top)));
    rectangle.push_back(K::Segment_2(K::Point_2(left, top), K::Point_2(right, top)));
    rectangle.push_back(K::Segment_2(K::Point_2(right, top), K::Point_2(right, bottom)));
    rectangle.push_back(K::Segment_2(K::Point_2(right, bottom), K::Point_2(left, bottom)));
    
    vector<pair<K::Point_2, int> > points;
    for(int b = 0; b < N; ++b) {
        double x, y; cin >> x >> y;
        points.push_back(make_pair(K::Point_2(x, y), b));
    }

    Delaunay t;
	t.insert(points.begin(), points.end());
    
    vector<pair<double, pair<int, int> > > edges;
    for(FEI e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Delaunay::Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
        Delaunay::Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
        K::FT edge_length = CGAL::sqrt(CGAL::squared_distance(v1->point(), v2->point()));
        edges.push_back(make_pair(edge_length, make_pair(v1->info(), v2->info())));
    }
    
    for(FVI p = t.finite_vertices_begin(); p != t.finite_vertices_end(); ++p) {
        Delaunay::Vertex_handle vertex = p;
        K::FT min; bool min_set = false;
        for(int seg = 0; seg < 4; ++seg) {
            K::FT seg_min = CGAL::squared_distance(rectangle[seg], vertex->point());
            if(min_set == false || min > seg_min) { min_set = true; min = seg_min; }    
        }
        edges.push_back(make_pair(2*CGAL::sqrt(min), make_pair(p->info(), p->info())));
    }
    
    sort(edges.begin(), edges.end());

    int dead = 0;
    int pointer = 0;
    int h = 0;
    bool first_time = true;
    vector<int> deadlist(N, 0);
   
    while(dead != N) {
        double min_length = 2 * (pow(h, 2.0) + 0.5);
        int temp_dead = 0;
        while(edges[pointer].first <= min_length && pointer < edges.size()) {
            int v1 = edges[pointer].second.first;
            int v2 = edges[pointer].second.second;
            if(deadlist[v1] == 0) { ++temp_dead; deadlist[v1] = 1; }
            if(deadlist[v2] == 0) { ++temp_dead; deadlist[v2] = 1; }
            ++pointer;
        }
        if(dead == 0 && temp_dead > 0) cout << h << " ";
        dead += temp_dead;
        if((N-dead)/(double)N < 0.5 && first_time) {
            cout << h << " ";
            first_time = false;
        }
        if(N == dead) cout << h << "\n";
        ++h;
    }
}

int main() {
     while(true) {
        int N; cin >> N;
        if(N == 0) return 0;
        testcase(N);
    }
}
