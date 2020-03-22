#include <fstream>
using namespace std;

int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    bool matrix[100][100] = {false};
    for (int i = 0; i < edgeNum; i++){
        int from, to;
        fin >> from >> to;
        matrix[from - 1][to - 1] = true;
    }
    for (int i = 0; i < vertexNum; i++){
        for (int j = 0; j < vertexNum; j++){
            fout << matrix[i][j] << " ";
        }
        fout << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}