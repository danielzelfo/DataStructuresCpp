#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "Graph.h"

using namespace std;

//Adjacency Matrix Graph class
class AdjacencyMatrixGraph : public Graph{

public:

	//the vertex class
	class InnerVertex : public Vertex {
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

	//edge class
	class InnerEdge : public Edge {
		int element;
		Vertex* u;
		Vertex* v;
		/*
			u -> v for directed
			u - v for undirected
		*/

	public:

		//constructor with two endpoints and element
		InnerEdge(Vertex* a, Vertex* b, int elem) {
			u = static_cast<InnerVertex*>(a); v = static_cast<InnerVertex*>(b);
			element = elem;
		}

		//element getter
		int getElement() { 
			return element; 
		}

		//endpoints getter
		vector<Vertex*> getEndpoints() { 
			return vector<Vertex*>{u, v};
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
	vector<Vertex*> getVertices() {
		return vertices;
	}

	//edges getter
	vector < Edge*> getEdges() {
		return edges;
	}

	//degree of a vertex
	int inDegree(Vertex* v) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		int degree = 0;
		int indx = iv->getPosition();
		for (int i = 0; i < matrix.size(); i++)
			if (matrix[i][indx] != 0)
				degree++;
		return degree;
	}

	//degree of a vertex
	int outDegree(Vertex* v) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		int degree = 0;
		int indx = iv->getPosition();
		for (int i = 0; i < matrix[indx].size(); i++)
			if (matrix[indx][i] != 0)
				degree++;
		return degree;
	}

	//insert a vertex
	Vertex* insertVertex(string element) {
		Vertex* v = new InnerVertex(vertices.size(), element);
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


	//insert an edge
	Edge* insertEdge(Vertex* u, Vertex* v, int element) {
		InnerVertex* iu = static_cast<InnerVertex*>(u);
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		Edge* e = new InnerEdge(u, v, element);
		edges.push_back(e);

		//settering edge element in matrix
		matrix[iu->getPosition()][iv->getPosition()] = element;
		if(!directed)
			matrix[iv->getPosition()][iu->getPosition()] = element;

		return e;
	}


	Edge* getEdge(Vertex* u, Vertex* v) {
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

	//end vertices of a given edge
	vector<Vertex*> endVertices(Edge* e) {
		InnerEdge* ie = static_cast<InnerEdge*>(e);
		vector<Vertex*> endpoints = ie->getEndpoints();
		return endpoints;
	}

	//opposite vertex given vertex and edge
	Vertex* opposite(Vertex* v, Edge* e) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		InnerEdge* ie = static_cast<InnerEdge*>(e);
		vector<Vertex*> endpoints = ie->getEndpoints();

		if (endpoints[0] == iv)
			return endpoints[1];
		
		return endpoints[0];
	}



	void removeVertex(Vertex* v) {
		InnerVertex* iv = static_cast<InnerVertex*>(v);
		//removing the row and column at the index of the postiion of v in the matrix
		matrix.erase(matrix.begin() + iv->getPosition());
		for(int i = 0; i <matrix.size(); i++)
			matrix[i].erase(matrix[i].begin() + iv->getPosition());

		//removing v from  the vertices
		vertices.erase(vertices.begin() + iv->getPosition());
		//adjusting the positions
		for (vector<Vertex*>::iterator it = vertices.begin() + iv->getPosition(); it != vertices.end(); ++it)
			static_cast<InnerVertex*>((*it))->setPosition(static_cast<InnerVertex*>((*it))->getPosition() - 1);

	}


	void removeEdge(Edge* e) {
		InnerEdge* ie = static_cast<InnerEdge*>(e);
		//setting the two matrix elements at the two endpoint positions to 0
		vector<Vertex*> uv = ie->getEndpoints();
		matrix[static_cast<InnerVertex*>(uv[0])->getPosition()][static_cast<InnerVertex*>(uv[1])->getPosition()] = 0;
		matrix[static_cast<InnerVertex*>(uv[1])->getPosition()][static_cast<InnerVertex*>(uv[0])->getPosition()] = 0;

		//removing e from edges
		edges.erase(edges.begin() + distance(edges.begin(), find(edges.begin(), edges.end(), e)) );
	}

	//print function
	void print() {
		string u, v;
		for (int i = 0; i < matrix.size(); i++) {
			//printing the current vertex and its degree if it has any adjacencies
			if (!matrix[i].empty()) {
				u = vertices.at(i)->getElement();
				cout << "Vertex " << u << endl;

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



private:
	bool directed;
	vector<Edge*> edges;
	vector<Vertex*> vertices;
	vector<vector<int>> matrix;
};