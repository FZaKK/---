#include <iostream>
#include "sudoku.h"
using namespace std;


int main()
{
    /*vector<vector<char>>board = { vector<char>{'5','3','.','.','7','.','.','.','.'},
                                  vector<char>{'6','.','.','1','9','5','.','.','.'},
                                  vector<char>{'.','9','8','.','.','.','.','6','.'},
                                  vector<char>{'8','.','.','.','6','.','.','.','3'},
                                  vector<char>{'4','.','.','8','.','3','.','.','1'},
                                  vector<char>{'7','.','.','.','2','.','.','.','6'},
                                  vector<char>{'.','6','.','.','.','.','2','8','.'},
                                  vector<char>{'.','.','.','4','1','9','.','.','5'},
                                  vector<char>{'.','.','.','.','8','.','.','7','9'}, };*/

    vector<vector<char>>blank(9, vector<char>(9, '$'));//����һ��9*9�Ŀն�ά����

    sudoku s(blank);
    s.create(50, blank);//����50���ո������
    if (s.active){
        cout << "����������Ϊ��" << endl;
        s.printBoard(blank);
    }
    else {
        cout << "�������Ϸ���û�н⣡" << endl;
    }
    s.dfs(blank, 0);//����������
    if (s.active){
        cout << "�������Ľ��ǣ�" << endl;
        s.printBoard(blank);
    }
    else {
        cout << "����ʧ�ܣ�" << endl;
    }

    return 0;
}
