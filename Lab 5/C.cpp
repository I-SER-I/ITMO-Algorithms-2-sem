#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int from, to, capacity, flow, number;
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

int decomposition(int vertex, int minFlow = INT_MAX) {
	if (vertex == sink) {
		answer.emplace_back();
		return minFlow;
	}
	for (int edge : graph[vertex]) {
		if (edges[edge].flow > 0) {
			int result = decomposition(edges[edge].to, min(minFlow, edges[edge].flow));
			if (result) {
				answer.back().push_back(edges[edge].number);
				if (vertex == source) {
					answer.back().push_back(answer[answer.size() - 1].size());
					answer.back().push_back(result);
					reverse(answer.back().begin(), answer.back().end());
				}
				edges[edge].flow -= result;
				return result;
			}
		}
	}
	return 0;
}

int main() {
	ifstream fin("decomposition.in");
	ofstream fout("decomposition.out");
	fin >> vertexNum >> edgeNum;
	graph.resize(vertexNum);
	ptr.resize(vertexNum, 0);
	for (int i = 0; i < edgeNum; i++) {
		int from, to, capacity;
		fin >> from >> to >> capacity;
		graph[from - 1].push_back(edges.size());
		edges.emplace_back(Edge{from - 1, to - 1, capacity, 0, i + 1});
		graph[to - 1].push_back(edges.size());
		edges.emplace_back(Edge{to - 1, from - 1, 0, 0, i + 1});
	}
	sink = vertexNum - 1;
	while (bfs()) {
		while (dfs());
		ptr.assign(vertexNum, 0);
	}
	while (decomposition(source));
	fout << answer.size() << "\n";
	for (auto& i : answer) {
		for (auto& j : i)
			fout << j << ' ';
		fout << '\n';
	}
	return 0;
}