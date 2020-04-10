#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
const int INF = 228228228;
int vertexNum, edgeNum;
vector <vector <int>> graph;

void floyd() {
	for (int k = 0; k < vertexNum; k++)
		for (int i = 0; i < vertexNum; i++)
			for (int j = 0; j < vertexNum; j++) 
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			
}

int main() {
	ifstream fin("pathsg.in");
	ofstream fout("pathsg.out");	
	fin >> vertexNum >> edgeNum;
	graph.assign(vertexNum, vector <int>(vertexNum, INF));
	for (int i = 0; i < edgeNum; i++) {
		int from, to, weight;
		fin >> from >> to >> weight;
		graph[from - 1][to - 1] = weight;
	}
	floyd();	
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			if (i == j)
				graph[i][j] = 0;
			fout << graph[i][j] << ' ';
		}
		fout << '\n';
	}
	return 0;
}