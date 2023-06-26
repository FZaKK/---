#pragma once
#include <iostream>
#include <fstream>
#include "sudoku.h"
using namespace std;

// 对应c参数，生成sudo终局文件
void create_sudo(int num) {
    // 先将曾经生成的内容清空
    ofstream f("board.txt", ios_base::out);

    cout << "Begin to create the sudo board ..." << endl << endl;
    for (int i = 0; i < num; i++) {
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(0, blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the sudo board !!!" << endl;
    f.close();
}
