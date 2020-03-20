#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
using namespace std;
const long long INF = 228228228228228;

bool bfs(vector <vector <pair<long long, long long>>>& graph, long long start) {
	set <long long> coronaVirus;
	coronaVirus.insert(start);
	queue<long long> ququ;
	ququ.push(start);
	while (!ququ.empty()) {
		long long now = ququ.front();
		ququ.pop();
		for (long long i = 0; i < graph[now].size(); i++) {
			long long to = graph[now][i].first;
			if (coronaVirus.find(to) == coronaVirus.end()) {
				ququ.push(to);
				coronaVirus.insert(to);
			}
		}
	}
	return coronaVirus.size() == graph.size();
}
void dfs(vector <vector <pair<long long, long long>>>& graph, vector <bool>& coronaVirus, vector <long long>& topsort, long long from) {
	coronaVirus[from] = true;
	for (auto& edge : graph[from])
	{
		long long to = edge.first;
		if (!coronaVirus[to])
			dfs(graph, coronaVirus, topsort, to);
	}
	topsort.push_back(from);
}
void transdfs(vector <vector <pair<long long, long long>>>& transGraph, vector <bool>& coronaVirus, vector <long long>& component, long long componentCount, long long from) {
	coronaVirus[from] = true;
	component[from] = componentCount;
	for (auto& edge : transGraph[from])
	{
		long long to = edge.first;
		if (!coronaVirus[to])
			transdfs(transGraph, coronaVirus, component, componentCount, to);
	}
}
long long condensation(vector <vector <pair<long long, long long>>>& graph, vector<long long>& component) {
	vector <vector <pair<long long, long long>>> transGraph(graph.size());
	vector <long long> topsort;
	vector <bool> coronaVirus(graph.size(), false);
	for (long long from = 0; from < graph.size(); from++)
		for (auto edge : graph[from]) {
			long long to = edge.first;
			long long weight = edge.second;
			transGraph[to].emplace_back(from, weight);
		}
	for (long long i = 0; i < graph.size(); i++)
		if (!coronaVirus[i])
			dfs(graph, coronaVirus, topsort, i);
	reverse(topsort.begin(), topsort.end());
	coronaVirus.assign(graph.size(), false);
	long long componentCount = 0;
	for (long long i = 0; i < topsort.size(); i++) {
		long long v = topsort[i];
		if (!coronaVirus[v])
			transdfs(transGraph, coronaVirus, component, componentCount++, topsort[i]);
	}
	return componentCount;
}
long long findMst(vector <vector <pair <long long, long long>>>& graph, long long vertexNum, long long root) {
	long long result = 0;
	vector<long long> minEdge(vertexNum, INF);
	vector <vector <pair<long long, long long>>> zeroGraph(vertexNum);
	vector<long long> component(vertexNum);
	for (long long i = 0; i < vertexNum; i++)
		for (auto edge : graph[i]) {
			long long to = edge.first;
			long long weight = edge.second;
			minEdge[to] = min(minEdge[to], weight);
		}
	for (long long i = 0; i < vertexNum; i++)
		if (i != root)
			result += minEdge[i];
	for (long long i = 0; i < vertexNum; i++) {
		for (auto e : graph[i])
			if (e.second == minEdge[e.first]) {
				e.second = 0;
				zeroGraph[i].push_back(e);
			}
	}
	if (bfs(zeroGraph, root))
		return result;
	long long componentCount = condensation(zeroGraph, component);
	vector <vector <pair<long long, long long>>> newGraph(componentCount);
	for (long long from = 0; from < vertexNum; from++) {
		for (auto edge : graph[from]) {
			long long to = edge.first;
			long long weight = edge.second;
			if (component[from] != component[edge.first])
				newGraph[component[from]].emplace_back(component[to], weight - minEdge[to]);
		}
	}
	result += findMst(newGraph, componentCount, component[root]);
	return result;
}
int main() {
	ifstream fin("chinese.in");
	ofstream fout("chinese.out");
	long long vertexNum, edgeNum;
	fin >> vertexNum >> edgeNum;
	vector <vector <pair<long long, long long>>> graph(vertexNum);
	for (long long i = 0; i < edgeNum; i++) {
		long long from, to, weight;
		fin >> from >> to >> weight;
		graph[from - 1].emplace_back(to - 1, weight);
	}
	if (bfs(graph, 0)) {
		fout << "YES\n";
		fout << findMst(graph, vertexNum, 0);
	}
	else
		fout << "NO";
	fin.close();
	fout.close();
	return 0;
}