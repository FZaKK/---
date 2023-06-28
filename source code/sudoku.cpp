#include <iostream>
#include <fstream>
#include "sudoku.h"
#include "filedeal.h"
#include "cmdline.h"
using namespace std;

// ���������в��������ݲ���ִ����Ӧ�Ĳ����� 
int main(int argc, char* argv[]){
    // ����һ��parser�����ڽ��������в�����
    cmdline::parser a;

    // �����Ӧ�Ĳ�����ͨ��a.add��������˸��������Ķ���
    a.add<int>("create", 'c', "The number of Sudoku finals required", false, 0, cmdline::range(1, 1000000));
    a.add<string>("solve", 's', "The path to the Sudoku board file that needs to be solved", false, "");
    a.add<int>("number", 'n', "The number of Sudoku games needed", false, 0, cmdline::range(1, 10000));
    a.add<int>("manage", 'm', "The difficulty of generating a Sudoku game", false, 0, cmdline::range(1, 3));
    a.add<int>("range", 'r', "The range of the number of knockouts in the game", false, 0, cmdline::range(20, 55));
    a.add("unique", 'u', "The solution unique to the game");

    a.parse_check(argc, argv);

    // �ж�����������ʼ����

    // ���create������Ϊ0 sudoku.exe -c 20 [��ʾ����20����������]
    if (a.get<int>("create") != 0) {
        // ���������������̵��ļ�֮��
        create_sudoku(a.get<int>("create"));
    }
    // ����s  sudoku.exe -s game.txt [��ʾ��game.txt��ȡ���ɸ�������Ϸ���������������ɵ�sudoku.txt��] 
    if (a.get<string>("solve") != "") {
        solve_sudoku(a.get<string>("solve"));
    }
    // ����n sudoku.exe -n 1000 [��ʾ����1000��������Ϸ]
    if (a.get<int>("number") != 0 && a.get<int>("manage") == 0 && a.get<int>("range") == 0 && !a.exist("unique")) {
        create_game(a.get<int>("number"));
    }
    // ���������ͬʱ������m��n��r������
    if (a.get<int>("number") != 0 && a.get<int>("manage") != 0 && a.get<int>("range") != 0) {
        cout << "Error : "
             << "Too many parameters. Have the parameter n, m, r"
             << endl;
    }
    // ����m  sudoku.exe -n 1000 -m 1[��ʾ����1000��������Ϸ��ֻ��m��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
    if (a.get<int>("manage") != 0) {
        if (a.get<int>("number") != 0) {
            create_game(a.get<int>("number"), a.get<int>("manage"));
        }
        else {
            cout << "Error : "
                 << "Have the parameter m, but don't have the parameter n!!!"
                 << endl;
        }
    }
    // ����r  sudoku.exe -n 20 -r 20~55[��ʾ����20���ؿ�����20��55֮���������Ϸ��ֻ��r��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
    if (a.get<int>("range") != 0) {
        if (a.get<int>("number") != 0) {
            create_game_range(a.get<int>("number"), a.get<int>("range"));
        }
        else {
            cout << "Error : "
                 << "Have the parameter r, but don't have the parameter n!!!"
                 << endl;
        }
    }
    // ����u sudoku.exe -n 20 -u[��ʾ����20����Ψһ��������Ϸ��ֻ��u��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
    if (a.exist("unique")) {
        if (a.get<int>("number") != 0) {
            create_game_unique(a.get<int>("number"));
        }
        else {
            cout << "Error : "
                 << "Have the parameter u, but don't have the parameter n!!!"
                 << endl;
        }
    }
    // û�в�����ʱ������������example
    if (argc == 1) {
        cout << " ----- Show the sudoku example ----- " << endl;

        // ����һ��9*9�Ŀն�ά����
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku s(blank);
        s.create(50, blank);  // ����50���ո������
        if (s.active){
            cout << endl << " ----- The Gen of the sudoku ----- " << endl;
            s.printBoard(blank);
        }
        else{
            cout << endl << " ----- The sudoku is invalid -----" << endl;
        }

        // ����������
        s.dfs(blank, 0);
        if (s.active){
            cout << endl <<  " ----- The solution of the sudoku ----- " << endl;
            s.printBoard(blank);
        }
        else{
            cout << endl << " ----- The sudoku is invalid -----" << endl;
        }
    }

    system("pause");
    return 0;
}
