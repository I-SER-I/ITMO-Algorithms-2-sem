#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 3000000;
int dis[INF];
vector < vector <int> > graph;


void bfs(int start) {
    dis[1] = 1;
    queue<int> ququ;
    ququ.push(start);
    while(!ququ.empty()) {
        int now = ququ.front();
        ququ.pop();
        for(int i = 0; i < graph[now].size(); i++) {
            int to = graph[now][i];
            if(dis[to] == 0) {
                dis[to] = dis[now] + 1;
                ququ.push(to);
            }
        }
    }
}



int main() {
    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    graph.resize(vertexNum + 1);
    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    bfs(1);
    for(int i = 1; i <= vertexNum; i++)
        fout << dis[i] - 1 << ' ';
    fin.close();
    fout.close();
    return 0;
}
