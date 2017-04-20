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


//Adjacency list representation of a weighted, undirected graph
class Graph {
	public:
		Graph();
		Graph(int n);
		Vertex* find(string s);
		Vertex* addVertex(string s);
		bool addEdge(string a, string b, double w);
		int nodes();
		void print();
		double shortestPath(string a, string b);

	private:
		Vertex* v_list;
		int size, max;
};


int main(int argc, char* argv[]) {
	
	// test
	int i, j = 2, k = 3, n;
	string a, b, c;

	n = 23;

	Graph g(n);

	for(i=0;i<n;i++) {
		a = (char) ('a' + i) ;
		g.addVertex(a);
		j = (j*j+1)%n;
		k = (k*k+3)%n;
		b = (char) ('a' + j) ;
		c = (char) ('a' + k) ;
		g.addEdge(b, c, (double) j);
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
