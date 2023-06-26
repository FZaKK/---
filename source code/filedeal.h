#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "sudoku.h"
using namespace std;


// �Ѷȵȼ���ո���Ŀ�ļ�ֵ��
map<int, int> diff_map = {
        {1, 20},
        {2, 40},
        {3, 55}
};


// ��Ӧc����������sudo�վ��ļ�
void create_sudo(int num){
    // �Ƚ��������ɵ��������
    ofstream f("board.txt", ios_base::out);

    cout << "Begin to create the sudo board ..." << endl;
    for (int i = 0; i < num; i++){
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(0, blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the sudo board !!!" << endl;
    f.close();
}

// ��Ӧn����������game������Ϸ
void create_game(int num, int m = 1){
    // �Ƚ��������ɵ��������
    ofstream f("game.txt", ios_base::out);

    cout << "Begin to create the game board ..." << endl;
    for (int i = 0; i < num; i++){
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(diff_map[m], blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the game board !!!" << endl;
    f.close();
}
