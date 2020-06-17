#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "../Graph.h"

using namespace std;

//Adjacency Matrix Graph class
class AdjacencyMatrixGraph : public Graph<string, int> {

public:

  //typedef Vertex<string><string> Vertex<string> ;
  //typedef Edge<int><int> Edge<int> ;

	//the Vertex<string> class
	class InnerVertex : public Vertex<string> {
		int pos;
		string element;
	public:
		//constructor with position and element
		InnerVertex(int i, string e) {
			pos = i;
			element = e;
		}

		//element getter
		string getElement() {
			return element;
		}

		//position getter
		int getPosition() {
			return pos;
		}

		void setPosition(int p) {
			pos = p;
		}
	};

	//Edge<int> class
	class InnerEdge : public Edge<int> {
		int element;
		Vertex<string>* u;
		Vertex<string>* v;
		/*
			u -> v for directed
			u - v for undirected
		*/

	public:

		//constructor with two endpoints and element
		InnerEdge(Vertex<string>* a, Vertex<string>* b, int elem) {
			u = static_cast<InnerVertex*>(a); v = static_cast<InnerVertex*>(b);
			element = elem;
		}

		//element getter
		int getElement() {
			return element;
		}

		//endpoints getter
		vector<Vertex<string>*> getEndpoints() {
			return vector<Vertex<string>*>{u, v};
		}
	};


	AdjacencyMatrixGraph(bool d = false) : directed(d) {}

	~AdjacencyMatrixGraph() {
		vertices.clear(); edges.clear(); matrix.clear();
		vertices.shrink_to_fit(); matrix.shrink_to_fit(); edges.shrink_to_fit();
	}

	//number of vertices
	int numVertices() {
		return vertices.size();
	}

	//number of edges
	int numEdges() {
		return edges.size();
	}

	//vertices getter
	list<Vertex<string>*> getVertices() {

		return list<Vertex<string>*>(vertices.begin(), vertices.end());
	}

	//edges getter
	list < Edge<int>*> getEdges() {
		return list<Edge<int>*>(edges.begin(), edges.end());
	}

	//degree of a Vertex<string>
	int inDegree(Vertex<string>* v) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		int degree = 0;
		int indx = iv->getPosition();
		for (int i = 0; i < matrix.size(); i++)
			if (matrix[i][indx] != 0)
				degree++;
		return degree;
	}

	//degree of a Vertex<string>
	int outDegree(Vertex<string>* v) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		int degree = 0;
		int indx = iv->getPosition();
		for (int i = 0; i < matrix[indx].size(); i++)
			if (matrix[indx][i] != 0)
				degree++;
		return degree;
	}


  vector<Edge<int>*> outgoingEdges(Vertex<string>* v){}


  vector<Edge<int>*> incomingEdges(Vertex<string>* v){}



	//insert a Vertex<string>
	Vertex<string>* insertVertex(string element) {
		Vertex<string>* v = new InnerVertex(vertices.size(), element);
		vertices.push_back(v);

		//resize the matrix
		matrix.resize(vertices.size());
		matrix[vertices.size() - 1] = vector<int>(vertices.size(), 0);
		for (int i = 0; i < matrix.size() - 1; i++) {
			matrix[i].resize(vertices.size());
			matrix[i][vertices.size() - 1] = 0;
		}

		return v;
	}


	//insert an Edge<int>
	Edge<int>* insertEdge(Vertex<string>* u, Vertex<string>* v, int element) {
		InnerVertex* iu = static_cast<InnerVertex*>(u);
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		Edge<int>* e = new InnerEdge(u, v, element);
		edges.push_back(e);

		//settering Edge<int> element in matrix
		matrix[iu->getPosition()][iv->getPosition()] = element;
		if (!directed)
			matrix[iv->getPosition()][iu->getPosition()] = element;

		return e;
	}


	Edge<int>* getEdge(Vertex<string>* u, Vertex<string>* v) {
		InnerEdge* e;
		for (int i = 0; i < edges.size(); i++) {
			e = static_cast<InnerEdge*>(edges[i]);
			if (e->getEndpoints()[0] == u && e->getEndpoints()[1] == v)
				return e;

			//checking other direction (if not directed)
			if (!directed && e->getEndpoints()[0] == v && e->getEndpoints()[1] == u)
				return e;
		}
		return nullptr;
	}

	//end vertices of a given Edge<int>
	vector<Vertex<string>*> endVertices(Edge<int>* e) {
		InnerEdge* ie = static_cast<InnerEdge*>(e);
		vector<Vertex<string>*> endpoints = ie->getEndpoints();
		return endpoints;
	}

	//opposite Vertex<string> given Vertex<string> and Edge<int>
	Vertex<string>* opposite(Vertex<string>* v, Edge<int>* e) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		InnerEdge* ie = static_cast<InnerEdge*>(e);
		vector<Vertex<string>*> endpoints = ie->getEndpoints();

		if (endpoints[0] == iv)
			return endpoints[1];

		return endpoints[0];
	}



	void removeVertex(Vertex<string>* v) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		//removing the row and column at the index of the postiion of v in the matrix
		matrix.erase(matrix.begin() + iv->getPosition());
		for (int i = 0; i < matrix.size(); i++)
			matrix[i].erase(matrix[i].begin() + iv->getPosition());

		//removing v from  the vertices
		vertices.erase(vertices.begin() + iv->getPosition());
		//adjusting the positions
		for (vector<Vertex<string>*>::iterator it = vertices.begin() + iv->getPosition(); it != vertices.end(); ++it)
			static_cast<InnerVertex*>((*it))->setPosition(static_cast<InnerVertex*>((*it))->getPosition() - 1);

	}


	void removeEdge(Edge<int>* e) {
		InnerEdge* ie = static_cast<InnerEdge*>(e);
		//setting the two matrix elements at the two endpoint positions to 0
		vector<Vertex<string>*> uv = ie->getEndpoints();
		matrix[static_cast<InnerVertex*>(uv[0])->getPosition()][static_cast<InnerVertex*>(uv[1])->getPosition()] = 0;
		matrix[static_cast<InnerVertex*>(uv[1])->getPosition()][static_cast<InnerVertex*>(uv[0])->getPosition()] = 0;

		//removing e from edges
		edges.erase(edges.begin() + distance(edges.begin(), find(edges.begin(), edges.end(), e)));
	}

	//print function
	void print() {
		string u, v;
		for (int i = 0; i < matrix.size(); i++) {
			//printing the current Vertex<string> and its degree if it has any adjacencies
			if (!matrix[i].empty()) {
				u = vertices.at(i)->getElement();
				cout << "Vertex<string> " << u << endl;

				cout << " " << outDegree(vertices.at(i)) << (directed ? " outgoing edges:" : " adjacencies:");
			}

			//printing all the adjacencies
			for (int j = 0; j < matrix.size(); j++) {
				if (matrix[i][j] != 0) {
					v = vertices.at(j)->getElement();
					cout << "(" << v << ", " << matrix[i][j] << ") ";

				}
			}

			if (directed) {
				if (!matrix[i].empty()) {
					u = vertices.at(i)->getElement();

					cout << "\n " << inDegree(vertices.at(i)) << " incoming edges:";
				}

				//printing all the adjacencies
				for (int j = 0; j < matrix.size(); j++) {
					if (matrix[j][i] != 0) {
						v = vertices.at(j)->getElement();
						cout << "(" << v << ", " << matrix[j][i] << ") ";

					}
				}
			}



			cout << endl;
		}

	}

	//print function
	void printMatrix() {
		cout << "  ";
		for (int i = 0; i < vertices.size(); i++)
			cout << vertices[i]->getElement() << " \n"[i == vertices.size() - 1];
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++) {
				if (j == 0)
					cout << vertices[i]->getElement() << " ";
				cout << matrix[i][j] << " \n"[j == matrix[i].size() - 1];
			}
	}


private:
	bool directed;
	vector<Edge<int>*> edges;
	vector<Vertex<string>*> vertices;
	vector<vector<int>> matrix;
};