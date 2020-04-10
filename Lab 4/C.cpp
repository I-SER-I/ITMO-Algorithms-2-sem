#include <fstream>
#include <vector>
#include <set>
using namespace std;
const int INF = 228228228;

vector <vector <pair <int, int>>> graph;
vector <int> distanc;
set <pair<int, int>> rawEdges;

void dijkstra() {
    distanc[0] = 0;
    rawEdges.emplace(distanc[0], 0);
    while (!rawEdges.empty()) {
        int from = rawEdges.begin()->second;
        rawEdges.erase(rawEdges.begin());
        for (auto& edge : graph[from]) {
            int to = edge.first;
            int weight = edge.second;
            if (distanc[from] + weight < distanc[to]) {
                rawEdges.erase({distanc[to], to});
                distanc[to] = distanc[from] + weight;
                rawEdges.emplace(distanc[to], to);
            }
        }
    }
}

int main() {
	ifstream fin("pathbgep.in");
	ofstream fout("pathbgep.out");
	int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    graph.resize(vertexNum);
    distanc.resize(vertexNum, INF);
	for (int i = 0; i < edgeNum; i++) {
		int from, to, weight;
		fin >> from >> to >> weight;
		graph[from - 1].emplace_back(to - 1, weight);
		graph[to - 1].emplace_back(from - 1, weight);
	}
    dijkstra();
    for (int weight : distanc)
	    fout << weight << " ";
	return 0;
}