#include <vector>
#include <fstream>

using namespace std;

vector<vector <int>> graph;
vector<int> way;
vector<bool> visited;

void dfs(int from) {
    visited[from] = true;
    for (int i = 0; i < graph[from].size(); i++) {
        int to = graph[from][i];
        if (!visited[to])
            dfs(to);
    }
    way.push_back(from);
}
        
bool exist(int from, int to) {
    for (int i = 0; i < graph[from].size(); i++)
        if (graph[from][i] == to)
            return true;
    return false;
}

int main() {
    ifstream fin("hamiltonian.in");
    ofstream fout("hamiltonian.out");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    graph.resize(vertexNum);
    visited.resize(vertexNum);
    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    for (int i = 0; i < vertexNum; i++)
        if (!visited[i])
            dfs(i);
    bool flag = true;
    for (int i = vertexNum - 1; i > 0; i--)
        if (!exist(way[i], way[i - 1])) {
            fout << "NO";
            return 0;
        }
    fout << "YES";
    fin.close();
    fout.close();
    return 0;
}