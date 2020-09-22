#include<iostream>
#include<stdlib.h>
#include"graphics.h"
#include<stdio.h>
#include<time.h>
#include<string>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
string name;
char ch[100];
char c[10] = { '0','1','2','3','4','5','6','7','8','9' };
char a[10] = { '_','_','_','_','_','_','_','_','_','_' };
char temp[10] = { '_','_','_','_','_','_','_','_','_','_' };
int sc1 = 0, sc2 = 0, sc3 = 0, scp1 = 0, scp2 = 0;
bool turn;
string player1_turn;
int win = 0;
bool fail;
int deep[9][10], deep1[8] = { 0,0,0,0,0,0,0,0 }, gahrai = 0;
bool warning;
int count_turn = 1, best_move;
char mark1 = 'X', mark2 = 'O';                            //mark1 for player other for computer
bool ulta = false;
bool player_turn;
bool pvp = false;
void empty_map();
void map();
void print();
void checkp();
void checkc();
void possible_moves()
{
	for (int i = 1; i < 10; i++)
	{
		if (a[i] == '_')
			deep[gahrai][i] = 2;
		else
			deep[gahrai][i] = 3;
	}
}
bool temp_check_comp_lose()
{
	if ((a[1] == mark1 && a[2] == mark1 && a[3] == mark1) || 
		(a[4] == mark1 && a[5] == mark1 && a[6] == mark1) || 
		(a[7] == mark1 && a[8] == mark1 && a[9] == mark1) ||
		(a[1] == mark1 && a[4] == mark1 && a[7] == mark1) ||
		(a[2] == mark1 && a[5] == mark1 && a[8] == mark1) ||
		(a[3] == mark1 && a[6] == mark1 && a[9] == mark1) ||
		(a[1] == mark1 && a[5] == mark1 && a[9] == mark1) ||
		(a[3] == mark1 && a[5] == mark1 && a[7] == mark1))
	{
		return  true;
	}
	return false;
}
bool temp_check_comp_win()
{
	if ((a[1] == mark2 && a[2] == mark2 && a[3] == mark2) ||
		(a[4] == mark2 && a[5] == mark2 && a[6] == mark2) ||
		(a[7] == mark2 && a[8] == mark2 && a[9] == mark2) ||
		(a[1] == mark2 && a[4] == mark2 && a[7] == mark2) ||
		(a[2] == mark2 && a[5] == mark2 && a[8] == mark2) ||
		(a[3] == mark2 && a[6] == mark2 && a[9] == mark2) ||
		(a[1] == mark2 && a[5] == mark2 && a[9] == mark2) ||
		(a[3] == mark2 && a[5] == mark2 && a[7] == mark2))
	{
		return  true;
	}
	return false;
}
inline bool temp_check_tie()
{
	if (temp_check_comp_lose() == true || temp_check_comp_win() == true)return false;
	for (int i = 1; i < 10; i++)
		if (a[i] == '_')
			return false;
	return true;
}
inline bool check()
{
	if (temp_check_tie() == true || temp_check_comp_win() == true || temp_check_comp_lose() == true)return true;
	else return false;
}
int AI()
{
	int best_move;
	int temp_win = win;
	bool check_possible_moves = true;
	strcpy(temp, a);
	gahrai = 0;
	for (int i = 0; i < 8; i++)              //reset deep[][] array and deep1[] array
	{
		for (int j = 0; j < 10; j++)
			deep[i][j] = NULL;
		deep1[i] = 0;
	}
check_computer_turn1:
	{
		//cout << "entring comp turn\n";
		//print();
		if (check_possible_moves == true)possible_moves();   //possible moves = 2, alrady occupied spaces = 3 
		//for (int i = 1; i < 10; i++)cout << "gaharai: " << gahrai << "deep[gahrai][" << i << "]: " << deep[gahrai][i] << endl;
		for (int i = 1; i < 10; i++)
		{
			if (deep[gahrai][i] == 2)                                    //try only empty spaces or which are not aleready occupied  
			{
				a[i] = mark2;                                           //mark2 = computer's mark
				//cout << "done comp turn\n";
				//print();
				if (check() == false)
				{
					//cout << "nothing happened\n";
					deep1[gahrai] = i;
					gahrai++;
					check_possible_moves = true;
					goto check_player_turn1;
				}
				if (temp_check_tie() == true)
				{
					//cout << "tie\n";
					deep[gahrai][i] = 0;                              //mark this turn as tie = 0
					a[i] = '_';
					if (gahrai != 0)
					{
						//cout << "gahrai != 0\n";
						deep[gahrai - 1][deep1[gahrai - 1]] = 0;                 //player's last turn marked as tie = 0
						a[deep1[gahrai - 1]] = '_';                              //reset last move by player
						gahrai--;
						check_possible_moves = false; goto check_player_turn1;
					}
					return i;
				}
				if (temp_check_comp_win() == true)
				{
					//cout << "win\n";
					deep[gahrai][i] = 1;                              //mark this turn as win = 1
					a[i] = '_';
					if (gahrai != 0)
					{
						//cout << "gahrai != 0\n";
						deep[gahrai - 1][deep1[gahrai - 1]] = 1;           //palyer's last turn marked as win for computer
						a[deep1[gahrai - 1]] = '_';
						gahrai--;
						check_possible_moves = false; goto check_player_turn1;
					}
					return i;
				}
			}
			if (deep[gahrai][i] == 1)
			{
				//cout << "already winner\n";
				if (gahrai != 0)
				{
					//cout << "gahrai != 0\n";
					a[deep1[gahrai - 1]] = '_';
					deep[gahrai - 1][deep1[gahrai - 1]] = 1;
					gahrai--;
					check_possible_moves = false; goto check_player_turn1;
				}
				return i;
			}
		}
		for (int i = 1; i < 10; i++)
		{
			if (deep[gahrai][i] == 0)
			{
				//cout << "only tie\n";
				if (gahrai != 0)
				{
					//cout << "gahrai != 0\n";
					a[deep1[gahrai - 1]] = '_';
					deep[gahrai - 1][deep1[gahrai - 1]] = 0;
					gahrai--;
					check_possible_moves = false; goto check_player_turn1;
				}
				return i;
			}
		}
		for (int i = 1; i < 10; i++)
		{
			if (deep[gahrai][i] == -1)
			{
				//cout << "looser\n";
				if (gahrai != 0)
				{
					//cout << "gahrai != 0";
					a[deep1[gahrai - 1]] = '_';
					deep[gahrai - 1][deep1[gahrai - 1]] = -1;
					gahrai--;
					check_possible_moves = false; goto check_player_turn1;
				}
				return i;
			}
		}
	}
check_player_turn1:
	{
		//cout << "entring player turn\n";
		//print();
		if (check_possible_moves == true)possible_moves();
		for (int i = 1; i < 10; i++)//cout << "gaharai: " << gahrai << "deep[gahrai][" << i << "]: " << deep[gahrai][i] << endl;
		for (int i = 1; i < 10; i++)
		{
			if (deep[gahrai][i] == 2)
			{
				a[i] = mark1;
				//cout << "done player turn/n";
				//print();
				if (check() == false)
				{
					deep1[gahrai] = i;
					gahrai++;
					check_possible_moves = true;
					goto check_computer_turn1;
				}
				if (temp_check_tie() == true)
				{
					//cout << "tie\n";
					deep[gahrai][i] = 0;
					a[i] = '_';
					deep[gahrai - 1][deep1[gahrai - 1]] = 0;
					a[deep1[gahrai - 1]] = '_';
					gahrai--;
					check_possible_moves = false; goto check_computer_turn1;
				}
				if (temp_check_comp_lose() == true)
				{
					//cout << "lose\n";
					deep[gahrai][i] = -1;
					a[i] = '_';
					deep[gahrai - 1][deep1[gahrai - 1]] = -1;
					a[deep1[gahrai - 1]] = '_';
					gahrai--;
					check_possible_moves = false; goto check_computer_turn1;
				}
			}
			if (deep[gahrai][i] == -1)
			{
				//cout << "already loses\n";
				a[deep1[gahrai - 1]] = '_';
				deep[gahrai - 1][deep1[gahrai - 1]] = -1;
				gahrai--;
				check_possible_moves = false; goto check_computer_turn1;
			}
		}
		for (int i = 1; i < 10; i++)
		{
			if (deep[gahrai][i] == 0)
			{
				//cout << "already a tie\n";
				a[deep1[gahrai - 1]] = '_';
				deep[gahrai - 1][deep1[gahrai - 1]] = 0;
				gahrai--;
				check_possible_moves = false; goto check_computer_turn1;
			}
		}
		for (int i = 1; i < 10; i++)
		{
			if (deep[gahrai][i] == 1)
			{
				//cout << "winner\n";
				a[deep1[gahrai - 1]] = '_';
				deep[gahrai - 1][deep1[gahrai - 1]] = 1;
				gahrai--;
				check_possible_moves = false; goto check_computer_turn1;
			}
		}
	}
	win = temp_win;
	strcpy(a, temp);
	for (int i = 1; i < 10; i++)cout << "gaharai: " << gahrai << "deep[gahrai][" << i << "]: " << deep[gahrai][i] << endl;
	return best_move;
}
string cursor()
{
	char ch;
	while(1){
	ch = getch();
	string s(1, ch);
	return s;
	}
}
int c1()
{
	char ch;
	while (1)
	{
		ch = getch();
		switch (ch)
		{
		case '1':return 1;
		case '2': return 2;
		}
	}
}
void cursor(int &s)
{
	char cr;
	int l, x = 0, y = 0, x1 = 250, y1 = 250, x2 = 350, y2 = 350;
	setcolor(RED);
	rectangle(250, 250, 350, 350);
	while (1)
	{
		cr = getch();
		switch (cr) {
		case KEY_UP: {
			if (y != -1)
			{
				cleardevice();
				empty_map();
				map();
				y1 += -200;
				y2 += -200;
				rectangle(x1, y1, x2, y2);
				y += -1;
			}
			break;
		}
		case KEY_LEFT: {
			if (x != -1)
			{
				cleardevice();
				empty_map();
				map();
				x1 += -200;
				x2 += -200;
				rectangle(x1, y1, x2, y2);
				x += -1;
			}
			break;
		}
		case KEY_RIGHT: {
			if (x != 1)
			{
				cleardevice();
				empty_map();
				map();
				x1 += 200;
				x2 += 200;
				rectangle(x1, y1, x2, y2);
				x += 1;
			}
			break;
		}
		case KEY_DOWN: {
			if (y != 1)
			{
				cleardevice();
				empty_map();
				map();
				y1 += 200;
				y2 += 200;
				rectangle(x1, y1, x2, y2);
				y += 1;
			}
			break;
		}
		case 32: {
			if (x == -1 && y == -1)s = 1;
			else if (x == 0 && y == -1)s = 2;
			else if (x == 1 && y == -1)s = 3;
			else if (x == -1 && y == 0)s = 4;
			else if (x == 0 && y == 0)s = 5;
			else if (x == 1 && y == 0)s = 6;
			else if (x == -1 && y == 1)s = 7;
			else if (x == 0 && y == 1)s = 8;
			else if (x == 1 && y == 1)s = 9;
			return;
			break;
		}
		case 13: {
			if (x == -1 && y == -1)s = 1;
			else if (x == 0 && y == -1)s = 2;
			else if (x == 1 && y == -1)s = 3;
			else if (x == -1 && y == 0)s = 4;
			else if (x == 0 && y == 0)s = 5;
			else if (x == 1 && y == 0)s = 6;
			else if (x == -1 && y == 1)s = 7;
			else if (x == 0 && y == 1)s = 8;
			else if (x == 1 && y == 1)s = 9;
			return;
			break;
		}
		case 'r': {
			s = 0;
			return;
		}
		}
	}
r:;
}
void empty_map()
{
	cleardevice();
	setcolor(0);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(600, 0, 600, 600);
	setcolor(RED);
	settextstyle(10,HORIZ_DIR,2);
	settextjustify(1,1);
	outtextxy(900,20,"TIC TAC TOE");
	setcolor(0);
	settextstyle(8,HORIZ_DIR,1);
	settextjustify(0,0);
}
void checkfail()
{
	if (cin.fail())
	{
		cout << "enter number \n\n";
		cin.clear();
		cin.ignore(999, '\n');
		Sleep(750);
		fail = true;
	}
	else fail = false;
}
void secret()
{
	system("cls;");
	char option;
	string password;
	cout << "enter password\n";
	getline(cin, password);
	if (password == "vilsa")
	{
		mark1 = 'X';
		mark2 = 'O';
	secret:
		system("cls;");
		cout << "                            WELCOME VISHNU SIR\n\n";
		cout << "which thing you want to do \n";
		cout << "c) change score \n";
		cout << "n) to change name \n";
		cin >> option;
		switch (option)
		{
		case 'c':
		{
			cout << "enter score for player 1 \n";
			cin >> sc1;
			cout << "enter score for computer \n";
			cin >> sc2;
			cout << "enter number of ties: \n";
			cin >> sc3;
			cin.ignore();
			break;
		}
		case 'n':
		{
			cout << "enter new name\n";
			name = "";
			cin >> name;
			cin.ignore();
			break;
		}
		default:
		{
			cout << "enter valid choice";
			Sleep(1000);
			goto secret;
		}
		}
	}
	else
	{
		cout << "wrong password";
		Sleep(1000);
		system("cls;");
		cout << "character for player 1 is 's' now\n";
		cout << "enter character for computer (as default 'O') \n";
		cin >> mark2;
		cin.ignore();
	}
}
void impossible1c(string a1, int b)
{
	if (turn == false && a1 == "0"&&b == 1)
	{
		if (a[2] == mark1 || a[4] == mark1)
		{
			a[1] = mark2;
			turn = true;
		}
		else if (a[6] == mark1 || a[8] == mark1)
		{
			a[9] = mark2;
			turn = true;
		}
		else if (a[5] == '_')
		{
			a[5] = mark2;
			turn = true;
		}
		else
		{
			a[1] = mark2;
			turn = true;
		}
	}
}
void checkp()
{
	setcolor(RED);
	int i;
	if (win < 2) {
		if (a[1] == mark1&&a[2] == mark1&&a[3] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(25, 95 + i, 575, 95 + i);
			}
		}
		else if (a[4] == mark1&&a[5] == mark1&&a[6] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(25, 295 + i, 575, 295 + i);
			}
		}
		else if (a[7] == mark1&&a[8] == mark1&&a[9] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(25, 495 + i, 575, 495 + i);
			}
		}
		else if (a[1] == mark1&&a[4] == mark1&&a[7] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(95 + i, 25, 95 + i, 575);
			}
		}
		else if (a[2] == mark1&&a[5] == mark1&&a[8] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(295 + i, 25, 295 + i, 575);
			}
		}
		else if (a[3] == mark1&&a[6] == mark1&&a[9] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(495 + i, 25, 495 + i, 575);
			}
		}
		else if (a[1] == mark1&&a[5] == mark1&&a[9] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(20 + i, 30 - i, 570 + i, 580 - i);
			}
		}
		else if (a[3] == mark1&&a[5] == mark1&&a[7] == mark1)
		{
			win = 3;
			for (i = 0; i <= 10; i++)
			{
				line(570 + i, 20 + i, 20 + i, 570 + i);
			}
		}
		else
			win = 0;
	}
}
void checkc()
{
	setcolor(BLUE);
	int i;
	if (a[1] == mark2&&a[2] == mark2&&a[3] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(25, 95 + i, 575, 95 + i);
		}
	}
	else if (a[4] == mark2&&a[5] == mark2&&a[6] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(25, 295 + i, 575, 295 + i);
		}
	}
	else if (a[7] == mark2&&a[8] == mark2&&a[9] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(25, 495 + i, 575, 495 + i);
		}
	}
	else if (a[1] == mark2&&a[4] == mark2&&a[7] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(95 + i, 25, 95 + i, 575);
		}
	}
	else if (a[2] == mark2&&a[5] == mark2&&a[8] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(295 + i, 25, 295 + i, 575);
		}
	}
	else if (a[3] == mark2&&a[6] == mark2&&a[9] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(495 + i, 25, 495 + i, 575);
		}
	}
	else if (a[1] == mark2&&a[5] == mark2&&a[9] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(20 + i, 30 - i, 570 + i, 580 - i);
		}
	}
	else if (a[3] == mark2&&a[5] == mark2&&a[7] == mark2)
	{
		win = 4;
		for (i = 0; i <= 10; i++)
		{
			line(570 + i, 20 + i, 20 + i, 570 + i);
		}
	}
	else if (win < 2)
		win = 0;
}
void checkt()
{
	if (win<3)
	{
		if (a[1] == mark2 || a[1] == mark1)
		{
			if (a[2] == mark1 || a[2] == mark2)
			{
				if (a[3] == mark1 || a[3] == mark2)
				{
					if (a[4] == mark1 || a[4] == mark2)
					{
						if (a[5] == mark1 || a[5] == mark2)
						{
							if (a[6] == mark1 || a[6] == mark2)
							{
								if (a[7] == mark1 || a[7] == mark2)
								{
									if (a[8] == mark1 || a[8] == mark2)
									{
										if (a[9] == mark1 || a[9] == mark2)
										{
											win = 2;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void map()
{
	empty_map();
	char mark20 = mark2, mark10 = mark1;
	int c1 = 2, c2 = 4;
	if (ulta == true)
	{
		mark20 = mark1;
		mark10 = mark2;
		c1 = 4;
		c2 = 2;
	}
	setcolor(c1);
	if (a[1] == mark20)
	{
		circle(100, 100, 75);
	}
	if (a[2] == mark20)
	{
		circle(300, 100, 75);
	}
	if (a[3] == mark20)
	{
		circle(500, 100, 75);
	}
	if (a[4] == mark20)
	{
		circle(100, 300, 75);
	}
	if (a[5] == mark20)
	{
		circle(300, 300, 75);
	}
	if (a[6] == mark20)
	{
		circle(500, 300, 75);
	}
	if (a[7] == mark20)
	{
		circle(100, 500, 75);
	}
	if (a[8] == mark20)
	{
		circle(300, 500, 75);
	}
	if (a[9] == mark20)
	{
		circle(500, 500, 75);
	}
	setcolor(c2);
	if (a[1] == mark10)
	{
		line(25, 25, 175, 175);
		line(175, 25, 25, 175);
	}
	if (a[2] == mark10)
	{
		line(225, 25, 375, 175);
		line(375, 25, 225, 175);
	}
	if (a[3] == mark10)
	{
		line(425, 25, 575, 175);
		line(575, 25, 425, 175);
	}
	if (a[4] == mark10)
	{
		line(25, 225, 175, 375);
		line(175, 225, 25, 375);
	}
	if (a[5] == mark10)
	{
		line(225, 225, 375, 375);
		line(375, 225, 225, 375);
	}
	if (a[6] == mark10)
	{
		line(425, 225, 575, 375);
		line(575, 225, 425, 375);
	}
	if (a[7] == mark10)
	{
		line(25, 425, 175, 575);
		line(175, 425, 25, 575);
	}
	if (a[8] == mark10)
	{
		line(225, 425, 375, 575);
		line(375, 425, 225, 575);
	}
	if (a[9] == mark10)
	{
		line(425, 425, 575, 575);
		line(575, 425, 425, 575);
	}
	setcolor(RED);
	win = 0;
	checkp();
	checkc();
	checkt();
}
void print()
{
	cleardevice();
	setcolor(0);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	map();
	cout << "     -------------------------------------------------------------------\n";
	cout << "     |                     |" << "                     |" << "                     |\n";
	cout << "     |";
	for (int i = 1; i <= 3; ++i)
	{
		cout << "          " << a[i] << "          |";
	}
	cout << "\n";
	cout << "     |                     |" << "                     |" << "                     |\n";
	cout << "     -------------------------------------------------------------------\n";
	cout << "     |                     |" << "                     |" << "                     |\n";
	cout << "     |";
	for (int j = 4; j <= 6; j++)
	{
		cout << "          " << a[j] << "          |";
	}
	cout << "\n";
	cout << "     |                     |" << "                     |" << "                     |\n";
	cout << "     -------------------------------------------------------------------\n";
	cout << "     |                     |" << "                     |" << "                     |\n";
	cout << "     |";
	for (int k = 7; k <= 9; k++)
	{
		cout << "          " << a[k] << "          |";
	}
	cout << "\n";
	cout << "     |                     |" << "                     |" << "                     |\n";
	cout << "     -------------------------------------------------------------------\n";
	if (warning == true)
	{
		cout << "you will lose\n";
		cout << "you will not be able to win\n";
	}
}
void cturn(string b, int c, int d)
{
	int b1 = 0;
	if (turn == false && b == "0"&&c == 2 && a[5] == mark1&&a[9] == mark2&&a[2] == '_'&&a[4] == '_'&&a[6] == '_'&&a[8] == '_' && (a[3] == mark1 || a[7] == mark1))
		warning = true;
	if (turn == false && b == "2")
	{
		if ((a[1] == mark1&&a[2] == mark1&&a[3] == '_') || (a[1] == mark2&&a[2] == mark2&&a[3] == '_'))
		{
			a[3] = mark2;
			turn = true;
		}
		else if ((a[4] == mark1&&a[5] == mark1&&a[6] == '_') || (a[4] == mark2&&a[5] == mark2&&a[6] == '_'))
		{
			a[6] = mark2;
			turn = true;
		}
		else if ((a[7] == mark1&&a[8] == mark1&&a[9] == '_') || (a[7] == mark2&&a[8] == mark2&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[2] == '_'&&a[3] == mark1) || (a[1] == mark2&&a[2] == '_'&&a[3] == mark2))
		{
			a[2] = mark2;
			turn = true;
		}
		else if ((a[4] == mark1&&a[5] == '_'&&a[6] == mark1) || (a[4] == mark2&&a[5] == '_'&&a[6] == mark2))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[7] == mark1&&a[8] == '_'&&a[9] == mark1) || (a[7] == mark2&&a[8] == '_'&&a[9] == mark2))
		{
			a[8] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[2] == mark1&&a[3] == mark1) || (a[1] == '_'&&a[2] == mark2&&a[3] == mark2))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[4] == '_'&&a[5] == mark1&&a[6] == mark1) || (a[4] == '_'&&a[5] == mark2&&a[6] == mark2))
		{
			a[4] = mark2;
			turn = true;
		}
		else if ((a[7] == '_'&&a[8] == mark1&&a[9] == mark1) || (a[7] == '_'&&a[8] == mark2&&a[9] == mark2))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[4] == mark1&&a[7] == mark1) || (a[1] == '_'&&a[4] == mark2&&a[7] == mark2))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[2] == '_'&&a[5] == mark1&&a[8] == mark1) || (a[2] == '_'&&a[5] == mark2&&a[8] == mark2))
		{
			a[2] = mark2;
			turn = true;
		}
		else if ((a[3] == '_'&&a[6] == mark1&&a[9] == mark1) || (a[3] == '_'&&a[6] == mark2&&a[9] == mark2))
		{
			a[3] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[4] == '_'&&a[7] == mark1) || (a[1] == mark2&&a[4] == '_'&&a[7] == mark2))
		{
			a[4] = mark2;
			turn = true;
		}
		else if ((a[2] == mark1&&a[5] == '_'&&a[8] == mark1) || (a[2] == mark2&&a[5] == '_'&&a[8] == mark2))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[6] == '_'&&a[9] == mark1) || (a[3] == mark2&&a[6] == '_'&&a[9] == mark2))
		{
			a[6] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[4] == mark1&&a[7] == '_') || (a[1] == mark2&&a[4] == mark2&&a[7] == '_'))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[2] == mark1&&a[5] == mark1&&a[8] == '_') || (a[2] == mark2&&a[5] == mark2&&a[8] == '_'))
		{
			a[8] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[6] == mark1&&a[9] == '_') || (a[3] == mark2&&a[6] == mark2&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[5] == mark1&&a[9] == '_') || (a[1] == mark2&&a[5] == mark2&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[5] == mark1&&a[7] == '_') || (a[3] == mark2&&a[5] == mark2&&a[7] == '_'))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[5] == '_'&&a[9] == mark1) || (a[1] == mark2&&a[5] == '_'&&a[9] == mark2))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[5] == '_'&&a[7] == mark1) || (a[3] == mark2&&a[5] == '_'&&a[7] == mark2))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[5] == mark1&&a[9] == mark1) || (a[1] == '_'&&a[5] == mark2&&a[9] == mark2))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[3] == '_'&&a[5] == mark1&&a[7] == mark1) || (a[3] == '_'&&a[5] == mark2&&a[7] == mark2))
		{
			a[3] = mark2;
			turn = true;
		}
		else
		{
		random:
			srand(time(NULL));
			b1 = (rand() % 9) + 1;
			if (a[b1] != '_')
				goto random;
			else if (a[b1] == '_')
				a[b1] = mark2;
			turn = true;
		}
	}
	else if (turn == false && b == "0"&&c == 1 && a[5] == '_' && (d == 2 || d == 4 || d == 6 || d == 8))
	{
		a[5] = mark2;
		turn = true;
	}
	else if (turn == false && b == "0"&&c == 1 && a[5] == mark2 && (d == 1 || d == 3 || d == 7 || d == 9) && count_turn == 2)
	{
		if (((d == 1 && a[8] == mark1) || (d == 3 && a[4] == mark1) || (d == 9 && a[4] == mark1)) && a[7] == '_')
		{
			a[7] = mark2;
			turn = true;
		}
		else if (((d == 1 && a[6] == mark1) || (d == 3 && a[8] == mark1) || (d == 7 && a[6] == mark1)) && a[9] == '_')
		{
			a[9] = mark2;
			turn = true;
		}
		else if (((d == 9 && a[2] == mark1) || (d == 7 && a[2] == mark1)) && a[1] == '_')
		{
			a[1] = mark2;
			turn = true;
		}
		else goto hard;
	}
	else if (turn == false && b == "0"&&c == 2 && a[5] == mark1 && a[9] == '_' && count_turn == 1)
	{
		a[9] = mark2;
		turn = true;
	}
	else if (turn == false && b == "0"&&c == 2 && a[5] == '_' && (a[1] == '_' || a[3] == '_' || a[7] == '_' || a[9] == '_'))
	{
		cout << "command";
		warning = true;
		if ((a[1] == mark2&&a[2] == '_'&&a[3] == '_'&&a[5] == '_'&&a[4] == '_'&&a[7] == '_'&&a[8] == '_') || (a[1] == mark2&&a[3] == '_'&&a[5] == '_'&&a[2] == '_'&&a[9] == '_'&&a[6] == '_'&&a[8] == '_'))
		{
			a[3] = mark2;
			turn = true;
		}
		else if (a[1] == mark2 && ((a[9] == '_'&&a[8] == '_') || (a[2] == '_'&&a[3] == '_')) && a[5] == '_'&&a[4] == '_'&&a[7] == '_'&&a[6] == '_')
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[1] == mark2&&a[2] == '_'&&a[3] == mark2))
		{
			a[2] = mark2;
			turn = true;
		}
		else if ((a[1] == mark2&&a[4] == '_'&&a[7] == mark2))
		{
			a[4] = mark2;
			turn = true;
		}
		else if (a[5] == '_'&&a[1] == mark2)
		{
			cout << "command executed";
			if ((a[9] == '_'&&a[8] == '_'&&a[6] == '_') && (a[3] == mark2 || a[7] == mark2))
			{
				cout << "1";
				a[9] = mark2;
				turn = true;
			}
			else if (a[3] == mark2&&a[4] == '_'&&a[7] == '_'&&a[8] == '_')
			{
				cout << "2";
				a[7] = mark2;
				turn = true;
			}
			else if (a[2] == '_'&&a[3] == '_'&&a[6] == '_' && (a[9] == mark2 || a[7] == mark2))
			{
				cout << "3";
				a[3] = mark2;
				turn = true;
			}
			else goto hard;
		}
		else goto hard;
	}
	else if (turn == false && (b == "1" || b == "0"))
	{
	hard:
		if ((a[1] == mark2&&a[2] == mark2&&a[3] == '_'))
		{
			a[3] = mark2;
			turn = true;
		}
		else if ((a[4] == mark2&&a[5] == mark2&&a[6] == '_'))
		{
			a[6] = mark2;
			turn = true;
		}
		else if ((a[7] == mark2&&a[8] == mark2&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[1] == mark2&&a[2] == '_'&&a[3] == mark2))
		{
			a[2] = mark2;
			turn = true;
		}
		else if ((a[4] == mark2&&a[5] == '_'&&a[6] == mark2))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[7] == mark2&&a[8] == '_'&&a[9] == mark2))
		{
			a[8] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[2] == mark2&&a[3] == mark2))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[4] == '_'&&a[5] == mark2&&a[6] == mark2))
		{
			a[4] = mark2;
			turn = true;
		}
		else if ((a[7] == '_'&&a[8] == mark2&&a[9] == mark2))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[4] == mark2&&a[7] == mark2))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[2] == '_'&&a[5] == mark2&&a[8] == mark2))
		{
			a[2] = mark2;
			turn = true;
		}
		else if ((a[3] == '_'&&a[6] == mark2&&a[9] == mark2))
		{
			a[3] = mark2;
			turn = true;
		}
		else if ((a[1] == mark2&&a[4] == '_'&&a[7] == mark2))
		{
			a[4] = mark2;
			turn = true;
		}
		else if ((a[2] == mark2&&a[5] == '_'&&a[8] == mark2))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[3] == mark2&&a[6] == '_'&&a[9] == mark2))
		{
			a[6] = mark2;
			turn = true;
		}
		else if ((a[1] == mark2&&a[4] == mark2&&a[7] == '_'))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[2] == mark2&&a[5] == mark2&&a[8] == '_'))
		{
			a[8] = mark2;
			turn = true;
		}
		else if ((a[3] == mark2&&a[6] == mark2&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[1] == mark2&&a[5] == mark2&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[3] == mark2&&a[5] == mark2&&a[7] == '_'))
		{
			a[7] = mark2;
			turn = true;
		}
		else if (a[1] == mark2&&a[5] == '_'&&a[9] == mark2)
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[3] == mark2&&a[5] == '_'&&a[7] == mark2))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[5] == mark2&&a[9] == mark2))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[3] == '_'&&a[5] == mark2&&a[7] == mark2))
		{
			a[3] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[2] == mark1&&a[3] == '_'))
		{
			a[3] = mark2;
			turn = true;
		}
		else if ((a[4] == mark1&&a[5] == mark1&&a[6] == '_'))
		{
			a[6] = mark2;
			turn = true;
		}
		else if ((a[7] == mark1&&a[8] == mark1&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[2] == '_'&&a[3] == mark1))
		{
			a[2] = mark2;
			turn = true;
		}
		else if ((a[4] == mark1&&a[5] == '_'&&a[6] == mark1))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[7] == mark1&&a[8] == '_'&&a[9] == mark1))
		{
			a[8] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[2] == mark1&&a[3] == mark1))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[4] == '_'&&a[5] == mark1&&a[6] == mark1))
		{
			a[4] = mark2;
			turn = true;
		}
		else if ((a[7] == '_'&&a[8] == mark1&&a[9] == mark1))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[4] == mark1&&a[7] == mark1))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[2] == '_'&&a[5] == mark1&&a[8] == mark1))
		{
			a[2] = mark2;
			turn = true;
		}
		else if ((a[3] == '_'&&a[6] == mark1&&a[9] == mark1))
		{
			a[3] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[4] == '_'&&a[7] == mark1))
		{
			a[4] = mark2;
			turn = true;
		}
		else if ((a[2] == mark1&&a[5] == '_'&&a[8] == mark1))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[6] == '_'&&a[9] == mark1))
		{
			a[6] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[4] == mark1&&a[7] == '_'))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[2] == mark1&&a[5] == mark1&&a[8] == '_'))
		{
			a[8] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[6] == mark1&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[5] == mark1&&a[9] == '_'))
		{
			a[9] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[5] == mark1&&a[7] == '_'))
		{
			a[7] = mark2;
			turn = true;
		}
		else if ((a[1] == mark1&&a[5] == '_'&&a[9] == mark1))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[3] == mark1&&a[5] == '_'&&a[7] == mark1))
		{
			a[5] = mark2;
			turn = true;
		}
		else if ((a[1] == '_'&&a[5] == mark1&&a[9] == mark1))
		{
			a[1] = mark2;
			turn = true;
		}
		else if ((a[3] == '_'&&a[5] == mark1&&a[7] == mark1))
		{
			a[3] = mark2;
			turn = true;
		}
		else if (a[1] == mark1&&a[5] == mark2&&a[9] == mark1)
		{
		rand:
			srand(time(NULL));
			b1 = (rand() % 9) + 1;
			if (a[b1] != '_' || b1 == 3 || b1 == 7)
				goto rand;
			else if (a[b1] == '_')
				a[b1] = mark2;
			turn = true;
		}
		else if (a[3] == mark1&&a[5] == mark2&&a[7] == mark1)
		{
		ran:
			srand(time(NULL));
			b1 = (rand() % 9) + 1;
			if (a[b1] != '_' || b1 == 1 || b1 == 9)
				goto ran;
			else if (a[b1] == '_')
				a[b1] = mark2;
			turn = true;
		}
		else if ((a[1] == mark2&&a[2] == '_'&&a[3] == mark2))
		{
			a[2] = mark2;
			turn = true;
		}
		else if (a[1] == mark2&&a[5] == mark1&&a[9] == mark1)
		{
			if (a[3] == '_')
			{
				a[3] = mark2;
			}
			else if (a[7] == '_')
			{
				a[7] = mark2;
			}
			else goto rando;
			turn = true;
		}
		else
		{
		rando:
			srand(time(NULL));
			b1 = (rand() % 9) + 1;
			if (a[b1] != '_')
				goto rando;
			else if (a[b1] == '_')
				a[b1] = mark2;
			turn = true;
		}
	}
}
void level_4()
{
	int turn;
	int d[10];
	bool temp;
	string mark;
	empty_map();
	outtextxy(610, 45, "player 1's turn 1st/2nd");
	turn = c1();
	if (turn != 1 && turn != 2)level_4();
	else if (turn == 1)player_turn = true;
	else player_turn = false;
	temp = player_turn;
	firse:
		empty_map();
		outtextxy(610, 45, "you want O's or X's: ");
		mark = cursor();
		if (mark == "O" || mark == "o") { ulta = true; mark1 = 'O'; mark2 = 'X'; }
		else if (mark == "x" || mark == "X")ulta = false;
		else goto firse;
	replay:
		for (int i1 = 0; i1<10; i1++)a[i1] = '_';
		do {
			empty_map();
			win = 0;
			outtextxy(610, 45, "use arrow keys to navigate and space bar to select");
		b:
			map();
			count_turn = 0;
			system("cls;");
			warning = false;
			if (player_turn == true)outtextxy(610, 45, "player 1's choice");
			else outtextxy(610, 45, "player 2's choice");
			outtextxy(610, 65, "use arrow keys to navigate and spacebar to select");
			cursor(d[0]);
			if (fail == true) { goto b; }
			turn = false;
			if (d[0]<10)
			{
				if (d[0] == 0)goto replay;
				if (a[d[0]] == '_')
				{
					if (player_turn == true) { a[d[0]] = mark1; player_turn = false; }
					else { a[d[0]] = mark2; player_turn = true; }
					print();
					cout << "\a";
				}
				else if (a[d[0]] == mark2 || a[d[0] == mark1])
				{
					outtextxy(610, 125, "please enter valid choice ");
					goto b;
				}
			}
			else
			{
				cout << "please enter valid choice";
				goto b;
			}
			checkp();
			checkt();
			checkc();
		} while (win < 2);
		player_turn = temp;

}
void special()
{
	for (int i = 0; i < 10; i++)a[i] = '_';
	int chance, number, j;
	cin >> chance;
	cout << "enter possible: ";
	cin >> j;
	cout << "enter numbers: ";
	for (int i = 1; i <= j; i++)
	{
		cin >> number;
		if (i % 2 == 1)
		{
			if (chance == 1)a[number] = mark1;
			else a[number] = mark2;
		}
		else
		{
			if (chance == 1)a[number] = mark2;
			else a[number] = mark1;
		}
	}
	print();
	system("pause");
	if (chance == 1 && j % 2 != 0)
	{
		a[AI()] = mark2;
	}
	if (chance != 1 && j % 2 == 0)
	{
		a[AI()] = mark2;
	}
	print();
	for (int i = 1; i < 10; i++)cout << "gaharai: " << gahrai << "deep[gahrai][" << i << "]: " << deep[gahrai][i] << endl;
	special();
}
void super_special()
{
	empty_map();
	for (int i = 0; i < 10; i++)a[i] = '_';
	int rand_no;
	rand_no = rand() % 9 + 1;
	a[rand_no] = mark1;
	print();
	win = 0;
	cout << win << "\a";
	Sleep(1000);
	while (win < 2)
	{
		cout << " came here\n";
		a[AI()] = mark2;
		cout << "came from AI() \n";
		print();
		cout << "\a";
		Sleep(1000);
		checkc();
		checkt();
		for (int i = 1; i < 10; i++)
		{ 
			if (a[i] == mark1)a[i] = mark2;
			else if (a[i] == mark2)a[i] = mark1;
		}
		a[AI()] = mark2;
		for (int i = 1; i < 10; i++)
		{
			if (a[i] == mark1)a[i] = mark2;
			else if (a[i] == mark2)a[i] = mark1;
		}
		print();
		cout << "\a";
		Sleep(1000);
		checkp();
		checkt();
	}
}
int main()
{
	system("color 70");
	char sr1[100], sr2[100], sr3[100], srp1[100], srp2[100];
	string level, mark;
	cout << "                            WELCOME TO TIC-TAC-TOE";
	cout << "\nenter your name: ";
	getline(cin, name);
	mciSendString(TEXT("open \"all.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
    initwindow(1200, 600, "v");
	setbkcolor(WHITE);
	empty_map();
	int pl = 0;
	count_turn = 0;
	warning = false;
	system("cls;");
	srand(time(NULL));
	for (int i = 0; i<10; i++)
		a[i] = '_';
	int b, d[10];
	string e;
	win = 0;
	settextstyle(10, HORIZ_DIR, 4); setcolor(RED);
	outtextxy(610, 300, "CLICK HERE AND THEN ENTER");
	outtextxy(610, 350, "YOUR CHOICE");
a:
	empty_map();
	settextstyle(8, HORIZ_DIR, 1); setcolor(0);
	outtextxy(610, 45, "which level you want");
	outtextxy(610, 65, "0)impossible 1)hard 2)medium 3)easy 4)human vs human");
	level = cursor();
	if (level == "s") { secret(); goto a;}
	if (level == "v") { special(); goto a; }
	if (level == "S") { super_special(); goto a; }
	if (level != "0"&&level != "1"&&level != "2"&&level != "3" && level != "4" && level != "a")
	{
		outtextxy(610, 85, "please enter the desired option ");
		outtextxy(610, 105, "make sure the capslock is off");
		Sleep(750);
		goto a;
	}
	if (level == "4")
	{
		pvp:
		pvp = true;
		level_4(); goto win;
	}
firse:
    empty_map();
	outtextxy(610, 45 , "you want O's or X's: ");
	mark = cursor();
	if (mark == "O" || mark == "o") { ulta = true; mark1 = 'O'; mark2 = 'X'; }
	else if (mark == "x" || mark == "X")ulta = false;
	else goto firse;
mark:
	empty_map();
	win = 0;
	outtextxy(610, 45, "use arrow keys to navigate and space bar to select");
b:
	empty_map();
	count_turn = 0;
	system("cls;");
	warning = false;
	for (int i1 = 0; i1<10; i1++)
		a[i1] = '_';
    outtextxy(610, 45, "you want which turn 1st or 2nd");
	b = c1();
	checkfail();
	if (fail == true) { goto b; }
	if (b == 1 || b == 2)
	{
		if (b == 1)
			turn = true;
		else
			turn = false;
	}
	else
	{
		outtextxy(610, 65, "enter valid choice");
		Sleep(1000);
		goto b;
	}
	if (turn == true)
	{
	c:
		empty_map();
		count_turn = 0;
		system("cls;");
		warning = false;
		for (int i1 = 0; i1<10; i1++)
			a[i1] = '_';
		count_turn = 1;
		outtextxy(610, 45, "to retry between game enter 'r'");
		outtextxy(610, 65, "use arrow keys to navigate and spacebar to select");
		outtextxy(610, 105, "enter your 1st turn");
		cursor(d[0]);
		if (fail == true) { goto c; }
		turn = false;
		if (d[0]<10)
		{
			if (d[0] == 0)
				goto c;
			if (a[d[0]] == '_')
			{
				a[d[0]] = mark1;
				print();
				cout << "\a";
			}
			else if (a[d[0]] == mark2 || a[d[0] == mark1])
			{
				outtextxy(610, 125, "please enter valid choice ");
				goto c;
			}
		}
		else
		{
			cout << "please enter valid choice";
			goto c;
		}
	}
	map();
	if (turn == false && (level == "2" || level == "3" || (level == "a" && b == 2)))
	{
		outtextxy(610, 45, "loading");
		Sleep(2000);
		outtextxy(610, 65, "computer chooses ");
	srand:
		d[0] = (rand() % 9) + 1;
		if (a[d[0]] == '_')
			a[d[0]] = mark2;
		else
			goto srand;
		print();
		cout << "\a";
		turn = true;
	}
	else if (turn == false && level == "a" && b == 1)
	{
		a[AI()] = mark2;
		Sleep(2000);
		turn = true;
		print();
	}
	else if (turn == false && level == "1")
	{
		outtextxy(610, 45, "thinking");
		Sleep(2000);
	hrd:
		outtextxy(610, 65, "computer chooses ");
		if (a[5] == '_')
			a[5] = mark2;
		else if (a[5] == mark1)
		{
			a[1] = mark2;
		}
		else
		{
		again:
			d[0] = (rand() % 9) + 1;
			if (a[d[0]] == '_')
				a[d[0]] = mark2;
			else
				goto again;
		}
		print();
		cout << "\a";
		turn = true;
	}
	else if (turn == false && level == "0"&&b == 2)
	{
		outtextxy(610, 45, "thinking");
		Sleep(2000);
		outtextxy(610, 65, "computer chooses ");
		if (a[1] == '_')
			a[1] = mark2;
		print();
		cout << "\a";
		turn = true;
	}
	else if (turn == false && level == "0"&&b == 1)
	{
		outtextxy(610, 45, "thinking");
		Sleep(2000);
		outtextxy(610, 65, "computer chooses ");
		impossible1c(level, b);
		print();
		cout << "\a";
	}
	else
		goto hrd;
    map();
	do
	{
		if (turn == true && win<2)
		{
			count_turn++;
			switch (count_turn)
			{
			case 1:
			{
				player1_turn = "1st";
				break;
			}
			case 2:
			{
				player1_turn = "2nd";
				break;
			}
			case 3:
			{
				player1_turn = "3rd";
				break;
			}
			case 4:
			{
				player1_turn = "4th";
				break;
			}
			case 5:
			{
				player1_turn = "5th";
				break;
			}
			}
		ch:
			outtextxy(610, 45, "use arrow keys to navigate and space bar to select\n");
			outtextxy(610, 65, "enter your turn");
			cursor(d[1]);
			if (d[1] == 0)
				goto b;
			if (d[1]<10)
			{
				if (a[d[1]] == '_')
				{
					a[d[1]] = mark1;
					print();
					cout << "\a";
				}
				else
				{
					outtextxy(610, 85, "please enter valid  choice");
					goto ch;
				}
			}
			else
			{
				outtextxy(610, 105, "please enter valid choice ");
				goto ch;
			}
			checkp();
			checkt();
			turn = false;
			cout << win;
		}
		map();
		cout << win;
		if (turn == false && win<2 && (level == "1" || level == "2" || level == "0"))
		{
			outtextxy(610, 45, "thinking");
			Sleep(2000);
			outtext("....");
			cturn(level, b, d[0]);
			print();
			cout << "\a";
			checkc();
			checkt();
		}
		else if (turn == false && win < 2 && level == "a")
		{
			outtextxy(610, 45, "thinking");
			Sleep(2000);
			outtext("....");
			a[AI()] = mark2;
			print();
			checkc();
			checkt();
			turn = true;
		}
		else if (turn == false && win<2 && level == "3")
		{
			outtextxy(610, 45, "thinking");
			Sleep(2000);
		rand:
			d[3] = (rand() % 9) + 1;
			if (a[d[3]] == '_')
				a[d[3]] = mark2;
			else
				goto rand;
			print();
			cout << "\a";
			checkc();
			checkt();
			turn = true;
		}
	} while (win<2); 
	win:
	mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
	mciSendString(TEXT("close mp3"), NULL, 0, NULL);
	map();
	cout << win;
	if (win == 2)
	{
		mciSendString(TEXT("open \"tie.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
		settextstyle(8,HORIZ_DIR,4);
		settextjustify(1, 1);
		setcolor(RED);
		outtextxy(900,500,"TIE");
		setcolor(0);
		settextstyle(8,HORIZ_DIR,1);
		settextjustify(0, 0);
		sc3 += 1;
		mciSendString(TEXT("play mp3 wait"), NULL, 0, NULL);
		mciSendString(TEXT("close mp3"), NULL, 0, NULL);

	}
	else if (win == 3)
	{
		settextstyle(8, HORIZ_DIR, 4);
		settextjustify(1, 1);
		setcolor(RED);
	third:
		cout << player_turn << mark1;
		if (pvp == false) { outtextxy(900, 500, "YOU WIN"); sc1 += 1; }
		else if (win == 3) { outtextxy(900, 500, "player 1 WIN"); scp1 += 1; }
		else { outtextxy(900, 500, "player 2 WIN"); scp2 += 1; }
		setcolor(0);
		settextstyle(8,HORIZ_DIR,1);
		settextjustify(0, 0);
		cout << "reach";
		mciSendString(TEXT("open \"win.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play mp3 wait"), NULL, 0, NULL);
		mciSendString(TEXT("close mp3"), NULL, 0, NULL);
		cout << "reach";
		goto retry;
	}
	else if (win == 4)
	{
        settextstyle(8,HORIZ_DIR,4);
		settextjustify(1, 1);
		setcolor(RED);
		if (pvp == false)outtextxy(900,500,"YOU LOSE");
		else goto third;
		setcolor(0);
		settextstyle(8,HORIZ_DIR,1);
		settextjustify(0, 0);
		sc2 += 1;
		mciSendString(TEXT("open \"lose.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play mp3 wait"), NULL, 0, NULL);
		mciSendString(TEXT("close mp3"), NULL, 0, NULL);

	}
	retry:
	mciSendString(TEXT("open \"all.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
	map();
	win = 0;
	sprintf(sr1, "%d", sc1); sprintf(sr2, "%d", sc2); sprintf(sr3, "%d", sc3); sprintf(srp1, "%d", scp1); sprintf(srp2, "%d", scp2);
	outtextxy(610, 45, "computer score is: " ); outtextxy(900, 45, sr2);
	outtextxy(610, 65, "your score is: "); outtextxy(900, 65, sr1);
	outtextxy(610, 85, "number of ties are: "); outtextxy(900, 85, sr3);
	outtextxy(610, 105, "player 1 score is: "); outtextxy(900, 105, srp1);
	outtextxy(610, 125, "player 2 score is: "); outtextxy(900, 125, srp2);
	outtextxy(610, 165, "do you want to retry y)yes");
	outtextxy(610, 185, "n)no l)to change level also");
	e = cursor();
	if (e == "yes" || e == "y" || e == "Y" || e == "r" || e == "R") { if (pvp == false) goto mark; else goto pvp; }
	else if (e == "no" || e == "n" || e == "N")
		outtextxy(610, 165, "good bye");
	else if (e == "level" || e == "l" || e == "L"){
		if (pvp == true)pvp = false;
		goto a;
	}
	else{
		outtextxy(610, 185, "enter valid choice");
		goto retry;
	}
	return 0;
}
