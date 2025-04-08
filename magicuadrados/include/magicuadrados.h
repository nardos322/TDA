#ifndef MAGICUADRADOS_H
#define MAGICUADRADOS_H
#include <iostream>
#include <vector>
using namespace std;

bool esMagico(const vector<vector<int>>& board);
bool poda (const vector<vector<int>>& board, const int i, const int j);
void backtrack(vector<vector<int>>& board, vector<bool>& used, int i, int j, int& count);


#endif //MAGICUADRADOS_H
