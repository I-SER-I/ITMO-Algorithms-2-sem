#include <fstream>
using namespace std;

bool checker(bool matrix[100][100], int n){
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if ((matrix[i][j] != matrix[j][i]) || (i == j && matrix[i][j] == true))
                return false;
    return true;
}

int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    bool matrix[100][100] = {false};
    fin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> matrix[i][j];
    if (checker(matrix, n))
        fout << "YES";
    else
        fout << "NO";
    fin.close();
    fout.close();
    return 0;
}