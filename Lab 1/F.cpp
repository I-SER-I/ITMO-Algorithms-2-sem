#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct coords {
    int x, y;
} start, finish;


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int graph[228][228];
    int n, m;
    char obj;
    vector <char> result;
    fin >> m >> n;
   for(int i = 0; i < n + 2; i++)
    {
        graph[0][i] = -1;
        graph[m + 1][i] = -1;
    }
    for(int i = 0; i < m + 2; i++)
    {
        graph[i][0] = -1;
        graph[i][n + 1] = -1;
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            fin >> obj;
            if(obj == '.')
                graph[i + 1][j + 1] = 0;
            if(obj == '#')
                graph[i + 1][j + 1] = -1;
            if(obj == 'S') {
                start.x = j + 1;
                start.y = i + 1;
                graph[i + 1][j + 1] = 1;
            }
            if(obj == 'T') {
                finish.x = j + 1;
                finish.y = i + 1;
                graph[i + 1][j + 1] = 0;
            }
        }
    }
    queue <coords> route;
    route.push(start);
    coords pos;
    while(!route.empty() && ((pos.x != finish.x) || (pos.y != finish.y))) {
        coords now = route.front();
        route.pop();
        if(!graph[now.y + 1][now.x]) {
            graph[now.y + 1][now.x] = graph[now.y][now.x] + 1;
            pos.x = now.x;
            pos.y = now.y + 1;
            route.push(pos);
        }
        if(!graph[now.y - 1][now.x]) {
            graph[now.y - 1][now.x] = graph[now.y][now.x] + 1;
            pos.x = now.x;
            pos.y = now.y - 1;
            route.push(pos);
        }
        if(!graph[now.y][now.x + 1]) {
            graph[now.y][now.x + 1] = graph[now.y][now.x] + 1;
            pos.x = now.x + 1;
            pos.y = now.y;
            route.push(pos);
        }
        if(!graph[now.y][now.x - 1]) {
            graph[now.y][now.x - 1] = graph[now.y][now.x] + 1;
            pos.x = now.x - 1;
            pos.y = now.y;
            route.push(pos);
        }
    }
    if(graph[finish.y][finish.x] == 0) {
        fout << "-1" << endl;
    }
    else {
        int curr = graph[finish.y][finish.x];
        while((finish.y != start.y) || (finish.x != start.x)) {
            if(graph[finish.y + 1][finish.x] == curr - 1) {
                result.push_back('U');
                finish.y++;
            }
            else if(graph[finish.y - 1][finish.x] == curr - 1) {
                result.push_back('D');
                finish.y--;
            }
            else if(graph[finish.y][finish.x + 1] == curr - 1) {
                result.push_back('L');
                finish.x++;
            }
            else if(graph[finish.y][finish.x - 1] == curr - 1) {
                result.push_back('R');
                finish.x--;
            }
            curr--;
        }
        fout << result.size() << endl;
        for(int i = result.size() - 1; i >= 0; i--)
            fout << result[i];
        fout << endl;
    }
    fin.close();
    fout.close();
    return 0;
}
