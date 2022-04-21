//========================================================
//�D�D�W��:���Ǧ~~�ڭ̤@�_���L���x���C��
//��s���:2021/04/21 12:03 
//��:���Ŷ��L�k�ϥ�".h"�t�C���Y�ɡA�Ц�Dev C++�Ψ�L�sĶ���ѽX
//========================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<cstdio>
using namespace std;

void game_a(void);
void game_b(void);
void SetColor(int);		//�����C��
void SetPos(int i, int j);

class Tetris{
private:
	int rank;				//�������׵���
	int score;				// �o��
	int id;					//�ϧ�ID
	int point[2];			//����I
	int top;					//�̰��I����
public:
	Tetris();
	void Welocme();			//���ɭ�
	void DrawMap();			//�����ɭ�
	void Draw(int, int, int);		//�e�ϧ�
	void Run();				//�B�����
	void ReDraw(int, int, int);			//�M���ϧ�
	bool Judge(int, int, int);
	void Turn(int);				//����
	void Updata();				// ��s�ɭ�
	void Pause();				//�����Ȱ�
	void Input_score();
	void esc();
};

int main(){
    SetConsoleTitle("���Ǧ~~�ڭ̤@�_���L���x���C��(��ܹC��)");
    system("mode con cols=48 lines=27");

    unsigned int a=0;
    char yn;
    SetColor(6);
    cout<<"������������������������������������������������\n";
    cout<<"================================================\n\n";
    cout<< "              �п�J�s����ܹC��:\n\n";
    cout<< "            1.Brick Puzzle Classic\n\n";
    cout<< "            2.Racing Classic\n\n";
    cout<< "================================================\n";
    cout<<"������������������������������������������������ \n\n\n";
    cout<<"  �ۥD�ǲߥD�D:���Ǧ~~�ڭ̤@�_���L���x���C��\n\n";
    cout<<"  ����:2�~7�Z04�L�����B05�L���ˡB14���T��\n\n";
    cout<<"  ���ɦѮv:��̰�D�Ѯv\n";
    SetPos(0,11);
    cout<<"�� ��1-2��ܹC��,�ë��UENTER �� ";
    while(1){
        SetPos(31,11);
        SetColor(5);
        cin >> a;
    if ( a == 2 ){
        SetColor(6);
        system("cls");
        SetConsoleTitle("���Ǧ~~�ڭ̤@�_���L���x���C��(����e��)");
        cout<<"To be contuine:\n�����N����ܫXù�����(Brick Puzzle Classic)\n";
        Sleep(5000);
        a=1;
    }

    else if(a>2){
        SetPos(0,12);
        SetColor(8);
        cout<<"��J���~�A�Э��s��J�C\n";
        SetPos(31,11);
        cout<<"              ";
        SetColor(5);
    }
    if(a==1){
        SetConsoleTitle("���Ǧ~~�ڭ̤@�_���L���x���C��(Brick Puzzle Classic)");
        Tetris();
        game_a();
        }
    }

    //else{
        //game_b();
        //system("cls");
        //cout<<"Game over!";
    //}
  cout<<"Continue?(y/n)\n";
  cin >> yn;
  if(yn =='y'){     //�P�_�O�_�s�by
  	system("cls");
    main();
	}
  else{                 //���s�by
  	system("cls");
    cout<<"Thanks for palying!";
    }

  return 0;
}

void SetColor(int color_num){			//�]�w�C��
	int n=0x0f;
	switch (color_num){
	case 0: n = 0x08; break; //�Ǧ�
	case 1: n = 0x0A; break; //���
	case 2: n = 0x0B; break; //�L��
	case 3: n = 0x0C; break; //�L��
	case 4: n = 0x0D; break; //���
	case 5: n = 0x0E; break; //�H��
	case 6: n = 0x0F; break; //�զ�
	case 7: n = 0x03; break; //����
	case 8: n = 0x04; break; //����
	case 9: n = 0x05; break; //����
	case 10: n = 0x06; break; //�g��
	case 11: n = 0x01; break; //�`��
	}
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), n);
}

void game_a(void){
	Tetris game;
	game.Welocme();
	system("cls");				//�M���w��ɭ�
	game.DrawMap();
	game.Run();
}

const int sharp[19][8] ={		//�զ��ϧΪ��U���I���U�ӧ��СA���a�Z��
{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
{0,0,1,0,0,1,1,1},
{0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
{1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
{0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
{0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1},
{0,0,1,0,1,1,2,0},{0,1,1,0,1,1,1,2},{0,1,1,0,1,1,2,1},{0,0,0,1,0,2,1,1}
};

const int high[19] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3 };
int map[28][16];

#define a1 0			//����
#define a2 1

#define b 2				// ���

#define c1 3			//L1��
#define c2 4
#define c3 5
#define c4 6

#define d1 7			//L2��
#define d2 8
#define d3 9
#define d4 10

#define e1 11			//�{�q1��
#define e2 12

#define f1 13			//�{�q2��
#define f2 14

#define g1 15
#define g2 16
#define g3 17
#define g4 18

Tetris::Tetris(){			//�غc���A ��l�ƦU�ӭ�
  for(int xm=0;xm<28;xm++){
		for(int ym=0;ym<16;ym++){
			map[xm][ym]=0;
		}
	}
	point[0] = 0;
	point[1] = 5;
	score = 0;
	top = 25;
}

void Tetris::Turn(int num){				//����禡
	switch (num){
	case a1: id = a2; break;    //���Τ���
	case a2: id = a1; break;

	case b: id = b; break;        //����L�k����

	case c1: id = c2; break;		//���L�Τ���
	case c2: id = c3; break;
	case c3: id = c4; break;
	case c4: id = c1; break;

	case d1: id = d2; break;
	case d2: id = d3; break;
	case d3: id = d4; break;
	case d4: id = d1; break;

	case e1: id = e2; break;	//��ذ{�q�Τ���
	case e2: id = e1; break;

	case f1: id = f2; break;
	case f2: id = f1; break;

	case g1: id = g2; break;     //T�Τ���
	case g2: id = g3; break;
	case g3: id = g4; break;
	case g4: id = g1; break;
	}
}

void SetPos(int i, int j){			//�����Ц�m�A �C�A ��
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Tetris::Pause(){               // �Ȱ��禡
    SetPos(32, 17);
    SetColor(8);
    printf("�����Ȱ�\n");
    char temp;
    while (1){
        while (1){
            if (_kbhit()){
                temp = _getch();
                break;
            }
        }
        if (temp == 32)
            break;
        if (temp == 27)
            main();
    }
    SetPos(32, 17);                    // �M���Ȱ�����ܪ���T
    printf("         ");
}

void Tetris::Updata(){					//��s�禡
	int i, flag;
	int nx, ny;
	for (i = 0; i < 4; i++){
		nx = point[0] + sharp[id][i * 2];
		ny = point[1] + sharp[id][i * 2 + 1];
		SetPos((ny + 1) * 2, nx + 1);
		SetColor(10);
		printf("��");
		map[nx][ny] = 1;					//�ɭ��U���I�O�_���Ū���s
	}

	if (point[0] < top)
		top = point[0];					//�̰��I����s

	for (i = point[0]; i < point[0] + high[id]; i++){			//������
		flag = 1;
		for (int j = 0; j < 13; j++)					//�P�w�Y�@��O�_���A ��flag�ӼаOgai
			if (map[i][j] == 0)
				flag = 0;
		if (flag == 1){
			for (int k = i; k >= top; k--){
				for (int p = 0; p < 13; p++){    //gai
					map[k][p] = map[k - 1][p];
					SetPos((p + 1) * 2, k + 1);
					if (map[k][p] == 1)
						cout << "��";
					else cout << "  ";
				}
			}
			score += 10;
			Input_score();
		}
	}
}

void Tetris::Input_score(){
    SetColor(7);
    SetPos(33, 12);
    cout << "�o��: " << score;
}

void Tetris::Welocme(){            //�w��ɭ�
    SetColor(10);
    char x;
    while (1) {
        system("cls");
        cout << "������������������������������������������������\n";
        cout << "                   �Xù�����        \n" ;
        cout << "������������������������������������������������\n";
        cout << "������������������������������������������������\n\n";
        cout << "               ���ާ@�覡�G    ��\n";
        cout << "               ���� - ����     ��\n";
        cout << "               ���� - �[�t�U�� ��\n";
        cout << "               ���� - ����     ��\n";
        cout << "               ���� - �k��     ��\n";
        cout << "               ���Ů� - �Ȱ�   ��\n";
        cout << "               ��ESC - ���}�C����\n\n";
        cout << "������������������������������������������������\n";
        cout << "�� ��1-3������� ��\n";
        SetPos(20, 14);
        x = getchar();
        if (x <= '4' && x >= '1'){
            rank = x - '0';
            break;
        }
    }
}

void Tetris::DrawMap(){                //�e�����ɬɭ�
    int i;
    SetColor(0);

    for (i = 0; i < 24; i++){        //�e24��
        SetPos(i * 2, 0);
        printf("��");
        SetPos(i * 2, 26);
        printf("��");
    }

    for (i = 0; i < 26; i++){        //��26��
        SetPos(0, i);
        printf("��");
        SetPos(28, i);
        printf("��");
        SetPos(46, i);
        printf("��");
    }

    for (i = 14; i < 24; i++){
        SetPos(i * 2, 10);
        printf("��");
    }

    SetColor(3);
    Input_score();
    SetPos(32, 25);
    cout << "���׵���: " << rank;
    SetPos(34, 2);
    cout << "�U�@�ϧ�";
}

void Tetris::Draw(int x, int y, int num){				//�e�ϧ�
	int nx, ny;

	for (int i = 0; i < 4; i++){
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);
		if (num==0 or num==1)
            SetColor(2);
        else if (num==2)
            SetColor(1);
        else if (num<=6)
            SetColor(9);
        else if (num<=10)
            SetColor(3);
        else if (num <= 12)
            SetColor(8);
        else if (num<=14)
            SetColor(1);
        else
            SetColor(11);
		printf("��");
	}
}

void Tetris::ReDraw(int x, int y, int num){				//����s�ϧΪ���m�M���ϧ�
	int nx, ny;

	for (int i = 0; i < 4; i++){
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);
		cout << "  ";
	}
}

bool Tetris::Judge(int x, int y, int num)	{			//�P�w�bx, y �ҫ���m�O�_�i�e�s����
	int nx, ny;                                                       //num ���ϧΡA �Y���i�e�h�Ϧ^true
	for (int i = 0; i < 4; i++){
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		if (!(nx < 25 && nx >= 0 && ny < 13 && ny >= 0 && !map[nx][ny]))
			return true;
	}
	return false;
}

int change(int a){
    if (0<=a and 19>=a)
        return a;
    else {
        if(a<=21)
            return 0;
        else if(a<=24)
            return 2;
        else if(a<=26)
            return 11;
        else
            return 13;
    }
}

void Tetris::Run(){                 //�B�����
	int next_id;
	srand((int)time(0));

	id = change(rand() % 18);
	next_id = change(rand() % 18);

	Draw(point[0], point[1], id);
	Draw(5, 16, next_id);

	int count;
	if (rank == 1)
		count = 150;
	else if (rank == 2)
		count = 100;
	else if (rank ==3)
		count = 50;
	else
	    count = 0.1;
	int i = 0;                  //���P���Ź������Pcount
	int next=1;

	while (1){
		if (!(i < count)){				//i �P count �Τ_����ɶ�
			i = 0;
			if (next==0){			//�b�Y�@��m����U������
				next=1;
				Updata();
				id = next_id;

				ReDraw(5, 16, next_id);
				next_id = change(rand() % 18);

				point[0] = 0; point[1] = 5;
				Draw(point[0], point[1], id);
				Draw(5, 16, next_id);

				if (Judge(point[0], point[1], id)){
					system("cls");
					SetPos(20, 10);
					cout << "���������I\n";
					SetPos(20, 11);
					cout << "�A�����Ƭ� " << score <<"\n";
					system("pause");
					exit(1);
				}
			}
			else{					//�~��U��
				ReDraw(point[0], point[1], id);
				point[0]++;
				Draw(point[0], point[1], id);
			}
		}

		if (_kbhit()){				//��L��J�Ȯ�
			int key, key2;
			key = _getch();
			if (key == 224){
				key2 = _getch();

				if (key2 == 72){			//���V�W��V���
					int temp = id;
					Turn(id);
					if (Judge(point[0], point[1], id))
						id = temp;
					ReDraw(point[0], point[1], temp);
					Draw(point[0], point[1], id);
				}
				if (key2 == 80){				//���V�U��V���
					if (!Judge(point[0] + 2, point[1], id)){
						ReDraw(point[0], point[1], id);
						point[0] += 2;
						Draw(point[0], point[1], id);
					}
				}
				else if (key2 == 75){				//���V����V���
					if (!Judge(point[0], point[1] - 1, id)){
						ReDraw(point[0], point[1], id);
						point[1]--;
						Draw(point[0], point[1], id);
					}
				}
				else if (key2 == 77){					//���V�k��V���
					if (!Judge(point[0], point[1] + 1, id)){
						ReDraw(point[0], point[1], id);
						point[1]++;
						Draw(point[0], point[1], id);
					}
				}
			}
			else if (key == 32)					// ���U�Ů�Ȱ�
				Pause();
		}

		if (Judge(point[0] + 1, point[1], id))
			next=0;
		else{
			next=1;
			Sleep(1); //����1�@��
		}
		i++;				//����U�����j
	}
}

void game_b(void){
  cout<<"�C��B\n";
}

