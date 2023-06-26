#pragma once
#include <iostream>
#include <fstream>
#include "sudoku.h"
using namespace std;

// ��Ӧc����������sudo�վ��ļ�
void create_sudo(int num) {
    // �Ƚ��������ɵ��������
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
