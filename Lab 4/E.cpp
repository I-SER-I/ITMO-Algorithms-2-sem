#include <fstream>
#include <vector>
using namespace std;

struct edge {
    int from, to, weight;
};

const int INF = 228228228;
int vertexNum;
int negCycleStart = -1;
vector<edge> graph;
vector<int> dist;
vector<int> parent;

void ford() {
    dist[0] = 0;
    for (int i = 0; i < vertexNum; i++) {
        negCycleStart = -1;
        for (edge edge : graph) {
            if (dist[edge.to] > dist[edge.from] + edge.weight) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                parent[edge.to] = edge.from;
                negCycleStart = edge.to;
            }
        }
    }
}

int main() {
    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");
    fin >> vertexNum;
    dist.resize(vertexNum, INF);
    graph.resize(vertexNum);
    parent.resize(vertexNum);
    for (int from = 0; from < vertexNum; from++) {
        for (int to = 0; to < vertexNum; to++) {
            int weight;
        	fin >> weight;
            graph.push_back({ from, to, weight });
        }
    }
    ford();
    if (negCycleStart != -1) {
        vector<int> way;
        int negCycleEnd = negCycleStart;
        for (int i = 0; i < vertexNum; i++)
            negCycleEnd = parent[negCycleEnd];
        for (int negCycleNow = negCycleEnd; negCycleNow != negCycleEnd || way.empty(); negCycleNow = parent[negCycleNow])
            way.push_back(negCycleNow);
        way.push_back(negCycleEnd);
        reverse(way.begin(), way.end());
        fout << "YES\n";
        fout << way.size() << endl;
        for (int vertex : way)
            fout << vertex + 1 << ' ';
    }
    else
		fout << "NO";
	return 0;
}