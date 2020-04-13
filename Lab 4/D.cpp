#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

struct edge {
    long long from, to, weight;
};

const long long INF = 8228228228228228228;
long long vertexNum, edgeNum, start;
long long x = -1;
vector<edge> edgeList;
vector<vector<long long>> graph;
vector<long long> dist;
vector<long long> parent;
vector<bool> visited;

void ford(long long vertex) {
    dist[vertex] = 0;
    for (long long i = 0; i < vertexNum; i++) {
        x = -1;
        for (long long j = 0; j < edgeNum; j++) {
            if (dist[edgeList[j].from] < INF) {
                if (dist[edgeList[j].to] > dist[edgeList[j].from] + edgeList[j].weight) {
                    dist[edgeList[j].to] = max(-INF, dist[edgeList[j].from] + edgeList[j].weight);
                    parent[edgeList[j].to] = edgeList[j].from;
                    x = edgeList[j].to;
                }
            }
        }
    }
}

void dfs(long long from) {
    visited[from] = true;
    for (long long to : graph[from])
        if (!visited[to])
            dfs(to);
}

int main() {
    ifstream fin("path.in");
    ofstream fout("path.out");
    fin >> vertexNum >> edgeNum >> start;
    edgeList.resize(edgeNum);
    graph.resize(vertexNum);
    parent.resize(vertexNum, -1);
    dist.resize(vertexNum, INF);
    visited.resize(vertexNum);
    for (long long i = 0; i < edgeNum; i++) {
        long long from, to, weight;
        fin >> from >> to >> weight;
        edgeList.push_back({ from - 1, to - 1, weight });
        graph[from - 1].push_back(to - 1);
    }
    ford(start - 1);
    if (x != -1) {
        for (long long i = 0; i < vertexNum; i++)
            x = parent[x];
        dfs(x);
    }
    for (long long i = 0; i < vertexNum; i++) {
        if (visited[i])
            fout << "-\n";
        else if (dist[i] == INF)
            fout << "*\n";
        else
            fout << dist[i] << '\n';
    }
}
