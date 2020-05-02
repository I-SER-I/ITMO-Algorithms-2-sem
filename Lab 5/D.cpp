#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int from, to, capacity, flow;
};
vector<vector<int>> answer;
vector<vector<int>> graph;
vector<Edge> edges;
vector<int> ptr;
vector<int> level;
int vertexNum = 0, edgeNum = 0, source = 0, sink = 0;

bool bfs() {
	level.assign(vertexNum, 0);
	queue<int> q;
	q.push(source);
	level[source] = 1;
	while (!q.empty() && !level[sink]) {
		int from = q.front();
		q.pop();
		for (auto& edge : graph[from]) {
			if (!level[edges[edge].to] && edges[edge].capacity > edges[edge].flow) {
				q.push(edges[edge].to);
				level[edges[edge].to] = level[from] + 1;
			}
		}
	}
	return level[sink];
}

int dfs(int vertex = source, int flow = INT_MAX) {
	if (!flow)
		return 0;
	if (vertex == sink)	
		return flow;
	while (ptr[vertex] < graph[vertex].size()) {
		int edge = graph[vertex][ptr[vertex]];
		if (level[vertex] + 1 == level[edges[edge].to]){
			int pushed = dfs(edges[edge].to, min(flow, edges[edge].capacity - edges[edge].flow));
			if (pushed) {
				edges[edge].flow += pushed;
				edges[edge ^ 1].flow -= pushed;
				return pushed;
			}
		}
		ptr[vertex]++;
	}
	return 0;
}

void add(int from, int to, int capacity) {
	graph[from].push_back(edges.size());
	edges.emplace_back(Edge{ from, to, capacity, 0});
	graph[to].push_back(edges.size());
	edges.emplace_back(Edge{ to, from, 0, 0 });
}

int main() {
	ifstream fin("circulation.in");
	ofstream fout("circulation.out");
	fin >> vertexNum >> edgeNum;
	vertexNum += 2;
	graph.resize(vertexNum);
	ptr.resize(vertexNum, 0);
	sink = vertexNum - 1;
	for (int i = 0; i < edgeNum; i++) {
		int from, to, lowFlow, highFlow;
		fin >> from >> to >> lowFlow >> highFlow;
		add(source, to, lowFlow);
		add(from, to, highFlow - lowFlow);
		add(from, sink, lowFlow);
	}
	while (bfs()) {
		while (dfs());
		ptr.assign(vertexNum, 0);
	}
	for (int edge : graph[0]) {
		if (edges[edge].flow < edges[edge].capacity) {
			fout << "NO\n";
			return 0;
		}
	}
	fout << "YES\n";
	for (int i = 0; i < edges.size(); i += 6)
		fout << edges[i + 2].flow + edges[i + 4].flow << endl;
	return 0;
}