#include <vector>
#include <fstream>

using namespace std;

vector<vector <int>> graph; 
vector<vector <int>> transGraph;
vector<int> topsort;
vector<int> component;
vector<bool> visited;
int componentCount = 1;

void dfs(int from) {
    visited[from] = true;
    for (int i = 0; i < graph[from].size(); i++) {
        int to = graph[from][i];
        if (!visited[to])
            dfs(to);
    }
    topsort.push_back(from);
}

void transdfs(int from) {
    visited[from] = true;
    component[from] = componentCount;
    for (int i = 0; i < transGraph[from].size(); i++) {
        int to = transGraph[from][i];
        if (!visited[to])
            transdfs(to);
    }
}

int main() {
    ifstream fin("cond.in");
    ofstream fout("cond.out");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    transGraph.resize(vertexNum);
    graph.resize(vertexNum);
    visited.resize(vertexNum, false);
    component.resize(vertexNum);
    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
        transGraph[to - 1].push_back(from - 1);
    }
    for (int i = 0; i < vertexNum; i++)
        if (!visited[i])
            dfs(i);
    visited.assign(vertexNum, false);
    for (int i = 0; i < vertexNum; i++) {
        int v = topsort[vertexNum - 1 - i];
        if (!visited[v]) {
            transdfs(v);
            componentCount++;
        }
    }
    fout << componentCount - 1 << endl;
    for (int i = 0; i < vertexNum; i++)
        fout << component[i] << " ";
    fin.close();
    fout.close();
    return 0;
}