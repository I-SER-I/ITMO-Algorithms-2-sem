#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
const long long INF = 228228228228;

vector <vector <long long>> graph;
vector <long long> distanc;
vector <bool> visited;
long long vertexNum, start, finish;

void dijkstra() {
	distanc[start - 1] = 0;
	for (long long i = 0; i < vertexNum; i++) {
		long long vertex = -1;
		for (long long j = 0; j < vertexNum; j++)
			if (!visited[j] && (vertex == -1 || distanc[j] < distanc[vertex]))
				vertex = j;
		if (distanc[vertex] == INF)
			break;
		visited[vertex] = true;
		for (long long j = 0; j < vertexNum; j++)
			distanc[j] = min(distanc[j], distanc[vertex] + graph[vertex][j]);
	}
}

int main()
{
	ifstream fin("pathmgep.in");
	ofstream fout("pathmgep.out");
	fin >> vertexNum >> start >> finish;
	graph.resize(vertexNum, vector <long long>(vertexNum, INF));
	distanc.resize(vertexNum, INF);
	visited.resize(vertexNum);
	for (long long i = 0; i < vertexNum; i++) {
		for (long long j = 0; j < vertexNum; j++) {
			fin >> graph[i][j];
			if (graph[i][j] < 0)
				graph[i][j] = INF;
		}
	}
	dijkstra();
	if (distanc[finish - 1] >= INF)
		fout << -1;
	else
		fout << distanc[finish - 1];
	return 0;
}