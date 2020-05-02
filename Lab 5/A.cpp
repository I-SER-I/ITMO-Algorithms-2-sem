#include <fstream>
#include <queue>

using namespace std;

int maxFlow;
int vertexNum = 0, edgeNum = 0;
vector<vector<int>> graph;
vector<int> parent;

bool bfs(int source, int sink) {
    vector<bool> visited(vertexNum);
    queue <int> q;
    q.push(source);
    visited[source] = true;
	while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (int to = 0; to < vertexNum; to++) {
            if (!visited[to] && graph[from][to] > 0) {
                q.push(to);
                parent[to] = from;
                visited[to] = true;
            }
        }
    }
    return visited[sink];   
}

void edmondsKarp(int source, int sink) {
	while (bfs(source, sink)) {
        int partFlow = INT_MAX;
        for (int to = sink; to != source; to = parent[to]) {
            int from = parent[to];
            partFlow = min(partFlow, graph[from][to]);
        }
        for (int to = sink; to != source; to = parent[to]) {
            int from = parent[to];
            graph[from][to] -= partFlow;
            graph[to][from] += partFlow;
        }
        maxFlow += partFlow;
    }
}

int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");
    fin >> vertexNum >> edgeNum;
    graph.resize(vertexNum, vector<int>(vertexNum, 0));
    parent.resize(vertexNum, -1);
    for (int i = 0; i < edgeNum; i++) {
        int from, to, flow;
        fin >> from >> to >> flow;
        graph[from - 1][to - 1] = flow;
    }
    edmondsKarp(0, vertexNum - 1);
    fout << maxFlow;
    return 0;
}