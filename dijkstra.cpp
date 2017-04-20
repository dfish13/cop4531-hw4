#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct edgeNode {
	double w;
	struct vertex* vptr;
	struct edgeNode* next;
} Edge;


typedef struct vertex {
	string s;
	Edge* edges;
} Vertex;



// Adjacency list representation of a weighted, undirected graph
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
		int size, max;
};


int main(int argc, char* argv[]) {
	
	// test
	int i, j = 2, k = 3, n;
	string a, b, c;

	n = 26;

	Graph g(n);

	for(i=0;i<n;i++) {
		a = (char) ('a' + i%26) ;
		b = (char) ('a' + (i+1)%26) ;
		c = (char) ('a' + (i+25)%26) ;

		g.addVertex(a);
		g.addEdge(a, b, 1.0);
		g.addEdge(a, c, 1.0);
	}

	int* pred;
	double* dist;
	pred = new int[n];
	dist = new double[n];
	g.dijkstra("a", pred, dist);

	for(i=0;i<n;i++) {
		cout << g.v_list[i].s << " pred = " << g.v_list[pred[i]].s << " dist = " << dist[i] << '\n' ;
	}

	g.print();

	return 0;
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
}

Vertex* Graph::find(string s) {
	for(int i=0; i<size ; i++) {
		if(s == v_list[i].s)
			return & v_list[i];
	}
	return NULL;
}

int Graph::index(string s) {
	for(int i=0; i<size ; i++) {
		if(s == v_list[i].s)
			return i;
	}
	return -1;
}

Vertex* Graph::addVertex(string s) {
	if(size < max && find(s) == NULL) {
		v_list[size].s = s;
		v_list[size].edges = NULL;
		return &v_list[size++];
	}
	else {
		return NULL;
	}
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
		dist[i] = 1000.0 ;
		q[i] = true;
	}
	dist[index(src)] = 0;

	while (j > 0) {
		temp = (double) 1000.0 ;
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
