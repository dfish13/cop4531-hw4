#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <limits>

using namespace std;

/*
	Container which maps strings to integer
	values using a hash function.
*/

typedef struct pair {
	string s;
	int i;
	pair(string s, int i): s(s), i(i) {} ;
} Pair;

class StringMap {
	public:
		StringMap();
		StringMap(int n);
		int get(string s);
		int operator[](string s);
		void put(string s, int i);
		int hash(string s);

		list<Pair>* s_map;
		int size;
};

/*
	Adjacency list representation of a weighted,
	undirected graph. Uses a StringMap object to index
	into the vertex array.
*/

typedef struct edgeNode {
	double w;
	struct vertex* vptr;
	struct edgeNode* next;
} Edge;


typedef struct vertex {
	string s;
	Edge* edges;
} Vertex;

class Graph {
	public:
		Graph();
		Graph(int n);
		Vertex* find(string s);
		int index(string s);
		Vertex* addVertex(string s);
		bool addEdge(string a, string b, double w);
		int nodes();
		void print();
		void dijkstra(string src, int* pred, double* dist);

		Vertex* v_list;
		StringMap s_map;
		int size, max; 
};


int main(int argc, char* argv[]) {
	
	// main
	int i, j, n;
	string a, b, path, src(argv[2]), dest(argv[3]);
	double d;

	ifstream fin;
	fin.open(argv[1]);
	fin >> n;

	Graph g(n);

	// populate graph
	for(i=0;i<n;i++) {
		fin >> a;
		g.addVertex(a);
		while ((fin.get() != '\n') && fin.good()) {
			fin >> b >> d;
			g.addEdge(a, b, d);
		}
	}

	// perform dijkstra and build path from pred and dist
	int* pred;
	double* dist;
	pred = new int[n];
	dist = new double[n];
	g.dijkstra(src, pred, dist);

	i = g.index(dest);
	j = g.index(src);
	cout << dist[g.index(dest)] << '\n' ;
	while (i != j) {
		path = g.v_list[i].s + " " + path;
		i = pred[i];
	}
	cout << src + " " + path << '\n';

	fin.close();

	return 0;
}

StringMap::StringMap() {
	size = 0;
	s_map = NULL;
}

StringMap::StringMap(int n) {
	size = n;
	s_map = new list<Pair>[n];
}

void StringMap::put(string s, int i) {
	if (size > 0) {
		s_map[hash(s)].push_front(Pair(s, i));
	}
}

int StringMap::get(string s) {
	int i = hash(s);
	for (list<Pair>::iterator itr = s_map[i].begin(); itr != s_map[i].end(); itr++) {
		if ((*itr).s == s) 
			return (*itr).i ;
	}
	return -1;
}

int StringMap::operator[](string s) {
	return get(s);
}

int StringMap::hash(string s) {
	int h = 1, i;
	for (i = 0; i < s.size(); i++) {
		h = h*13 + s[i];
		h %= size;
	}
	return h;
}

Graph::Graph() {
	size = 0;
	max = 0;
	v_list = NULL;
}

Graph::Graph(int n) {
	size = 0;
	max = n;
	v_list = new Vertex[n];
	s_map = StringMap(n);
}

Vertex* Graph::find(string s) {
	int i = s_map[s];
	if (i >= 0)
		return &v_list[i];
	return NULL;
}

int Graph::index(string s) {
	return s_map[s];
}

Vertex* Graph::addVertex(string s) {
	if(size < max && find(s) == NULL) {
		v_list[size].s = s;
		v_list[size].edges = NULL;
		s_map.put(s, size);
		return &v_list[size++];
	}
	return NULL;
}

bool Graph::addEdge(string a, string b, double w) {
	Vertex *v1 = find(a), *v2 = find(b);
	if(v1 != NULL) {
		Edge * e = new Edge;
		if(v2 == NULL) {
			if((v2 = addVertex(b)) == NULL) {
				delete e;
				return false;
			}
		}
		e->w = w;
		e->next = v1->edges;
		e->vptr = v2;
		v1->edges = e;
		return true;
	}
	return false;
}

void Graph::dijkstra(string src, int* pred, double* dist) {
	int i , j = size, u, v;
	double temp, alt;
	Edge* e;
	bool* q = new bool[size];
	
	for (i=0;i<size;i++) {
		dist[i] = numeric_limits<double>::max();
		q[i] = true;
	}
	dist[index(src)] = 0;

	while (j > 0) {
		temp = numeric_limits<double>::max();
		for(i=0;i<size;i++) {
			if((dist[i] < temp) && q[i] == true) {
				temp = dist[i];
				u = i;
			}
		}
		q[u] = false;

		e = v_list[u].edges;
		while (e != NULL) {
			alt = dist[u] + e->w;
			v = index(e->vptr->s);
			if (alt < dist[v]) {
				dist[v] = alt;
				pred[v] = u;
			}
			e = e->next;
		}
		j--;
	}
	delete [] q;
}


int Graph::nodes() {
	return size;
}

void Graph::print() {
	int i;
	Edge* e;
	for(i=0;i<size;i++) {
		cout << v_list[i].s << ' ' ;
		e = v_list[i].edges;
		while(e != NULL) {
			cout << '(' << e->vptr->s << ',' << e->w << ") " ;
			e = e->next;
		}
		cout << '\n' ;
	}
}
