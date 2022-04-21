//========================================================
//主題名稱:那些年~我們一起玩過的掌機遊戲
//更新日期:2021/04/21 12:03 
//註:此空間無法使用".h"系列標頭檔，請至Dev C++或其他編譯器解碼
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
void SetColor(int);		//控制顏色
void SetPos(int i, int j);

class Tetris{
private:
	int rank;				//游戲難度等級
	int score;				// 得分
	int id;					//圖形ID
	int point[2];			//兩基點
	int top;					//最高點高度
public:
	Tetris();
	void Welocme();			//首界面
	void DrawMap();			//游戲界面
	void Draw(int, int, int);		//畫圖形
	void Run();				//運行游戲
	void ReDraw(int, int, int);			//清除圖形
	bool Judge(int, int, int);
	void Turn(int);				//旋轉
	void Updata();				// 更新界面
	void Pause();				//游戲暫停
	void Input_score();
	void esc();
};

int main(){
    SetConsoleTitle("那些年~我們一起玩過的掌機遊戲(選擇遊戲)");
    system("mode con cols=48 lines=27");

    unsigned int a=0;
    char yn;
    SetColor(6);
    cout<<"▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼\n";
    cout<<"================================================\n\n";
    cout<< "              請輸入編號選擇遊戲:\n\n";
    cout<< "            1.Brick Puzzle Classic\n\n";
    cout<< "            2.Racing Classic\n\n";
    cout<< "================================================\n";
    cout<<"▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲ \n\n\n";
    cout<<"  自主學習主題:那些年~我們一起玩過的掌機遊戲\n\n";
    cout<<"  成員:2年7班04林元隆、05林均憲、14黃俊謀\n\n";
    cout<<"  指導老師:陳怜伶老師\n";
    SetPos(0,11);
    cout<<"◇ 按1-2選擇遊戲,並按下ENTER ◇ ";
    while(1){
        SetPos(31,11);
        SetColor(5);
        cin >> a;
    if ( a == 2 ){
        SetColor(6);
        system("cls");
        SetConsoleTitle("那些年~我們一起玩過的掌機遊戲(跳轉畫面)");
        cout<<"To be contuine:\n五秒後將跳轉至俄羅斯方塊(Brick Puzzle Classic)\n";
        Sleep(5000);
        a=1;
    }

    else if(a>2){
        SetPos(0,12);
        SetColor(8);
        cout<<"輸入錯誤，請重新輸入。\n";
        SetPos(31,11);
        cout<<"              ";
        SetColor(5);
    }
    if(a==1){
        SetConsoleTitle("那些年~我們一起玩過的掌機遊戲(Brick Puzzle Classic)");
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
  if(yn =='y'){     //判斷是否存在y
  	system("cls");
    main();
	}
  else{                 //不存在y
  	system("cls");
    cout<<"Thanks for palying!";
    }

  return 0;
}

void SetColor(int color_num){			//設定顏色
	int n=0x0f;
	switch (color_num){
	case 0: n = 0x08; break; //灰色
	case 1: n = 0x0A; break; //綠色
	case 2: n = 0x0B; break; //淺藍
	case 3: n = 0x0C; break; //淺紅
	case 4: n = 0x0D; break; //桃紅
	case 5: n = 0x0E; break; //淡黃
	case 6: n = 0x0F; break; //白色
	case 7: n = 0x03; break; //水藍
	case 8: n = 0x04; break; //紅色
	case 9: n = 0x05; break; //紫色
	case 10: n = 0x06; break; //土黃
	case 11: n = 0x01; break; //深藍
	}
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), n);
}

void game_a(void){
	Tetris game;
	game.Welocme();
	system("cls");				//清除歡迎界面
	game.DrawMap();
	game.Run();
}

const int sharp[19][8] ={		//組成圖形的各個點的各個坐標，先縱后橫
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

#define a1 0			//條形
#define a2 1

#define b 2				// 方塊

#define c1 3			//L1形
#define c2 4
#define c3 5
#define c4 6

#define d1 7			//L2形
#define d2 8
#define d3 9
#define d4 10

#define e1 11			//閃電1形
#define e2 12

#define f1 13			//閃電2形
#define f2 14

#define g1 15
#define g2 16
#define g3 17
#define g4 18

Tetris::Tetris(){			//建構式， 初始化各個值
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

void Tetris::Turn(int num){				//旋轉函式
	switch (num){
	case a1: id = a2; break;    //條形互換
	case a2: id = a1; break;

	case b: id = b; break;        //方塊無法旋轉

	case c1: id = c2; break;		//兩種L形互換
	case c2: id = c3; break;
	case c3: id = c4; break;
	case c4: id = c1; break;

	case d1: id = d2; break;
	case d2: id = d3; break;
	case d3: id = d4; break;
	case d4: id = d1; break;

	case e1: id = e2; break;	//兩種閃電形互換
	case e2: id = e1; break;

	case f1: id = f2; break;
	case f2: id = f1; break;

	case g1: id = g2; break;     //T形互換
	case g2: id = g3; break;
	case g3: id = g4; break;
	case g4: id = g1; break;
	}
}

void SetPos(int i, int j){			//控制游標位置， 列， 行
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Tetris::Pause(){               // 暫停函式
    SetPos(32, 17);
    SetColor(8);
    printf("游戲暫停\n");
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
    SetPos(32, 17);                    // 清除暫停時顯示的資訊
    printf("         ");
}

void Tetris::Updata(){					//更新函式
	int i, flag;
	int nx, ny;
	for (i = 0; i < 4; i++){
		nx = point[0] + sharp[id][i * 2];
		ny = point[1] + sharp[id][i * 2 + 1];
		SetPos((ny + 1) * 2, nx + 1);
		SetColor(10);
		printf("■");
		map[nx][ny] = 1;					//界面各個點是否為空的更新
	}

	if (point[0] < top)
		top = point[0];					//最高點的更新

	for (i = point[0]; i < point[0] + high[id]; i++){			//消除行
		flag = 1;
		for (int j = 0; j < 13; j++)					//判定某一行是否滿， 用flag來標記gai
			if (map[i][j] == 0)
				flag = 0;
		if (flag == 1){
			for (int k = i; k >= top; k--){
				for (int p = 0; p < 13; p++){    //gai
					map[k][p] = map[k - 1][p];
					SetPos((p + 1) * 2, k + 1);
					if (map[k][p] == 1)
						cout << "■";
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
    cout << "得分: " << score;
}

void Tetris::Welocme(){            //歡迎界面
    SetColor(10);
    char x;
    while (1) {
        system("cls");
        cout << "▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼\n";
        cout << "                   俄羅斯方塊        \n" ;
        cout << "▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲\n";
        cout << "▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼▼▽▼\n\n";
        cout << "               ◇操作方式：    ◇\n";
        cout << "               ◆↑ - 旋轉     ◆\n";
        cout << "               ◇↓ - 加速下移 ◇\n";
        cout << "               ◆← - 左移     ◆\n";
        cout << "               ◇→ - 右移     ◇\n";
        cout << "               ◆空格 - 暫停   ◆\n";
        cout << "               ◇ESC - 離開遊戲◇\n\n";
        cout << "▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲▲△▲\n";
        cout << "◇ 按1-3選擇難度 ◇\n";
        SetPos(20, 14);
        x = getchar();
        if (x <= '4' && x >= '1'){
            rank = x - '0';
            break;
        }
    }
}

void Tetris::DrawMap(){                //畫游戲時界面
    int i;
    SetColor(0);

    for (i = 0; i < 24; i++){        //寬24格
        SetPos(i * 2, 0);
        printf("■");
        SetPos(i * 2, 26);
        printf("■");
    }

    for (i = 0; i < 26; i++){        //高26格
        SetPos(0, i);
        printf("■");
        SetPos(28, i);
        printf("■");
        SetPos(46, i);
        printf("■");
    }

    for (i = 14; i < 24; i++){
        SetPos(i * 2, 10);
        printf("■");
    }

    SetColor(3);
    Input_score();
    SetPos(32, 25);
    cout << "難度等級: " << rank;
    SetPos(34, 2);
    cout << "下一圖形";
}

void Tetris::Draw(int x, int y, int num){				//畫圖形
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
		printf("■");
	}
}

void Tetris::ReDraw(int x, int y, int num){				//為更新圖形的位置清除圖形
	int nx, ny;

	for (int i = 0; i < 4; i++){
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);
		cout << "  ";
	}
}

bool Tetris::Judge(int x, int y, int num)	{			//判定在x, y 所指位置是否可畫編號為
	int nx, ny;                                                       //num 的圖形， 若不可畫則反回true
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

void Tetris::Run(){                 //運行游戲
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
	int i = 0;                  //不同等級對應不同count
	int next=1;

	while (1){
		if (!(i < count)){				//i 與 count 用于控制時間
			i = 0;
			if (next==0){			//在某一位置不能下落的話
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
					cout << "游戲結束！\n";
					SetPos(20, 11);
					cout << "你的分數為 " << score <<"\n";
					system("pause");
					exit(1);
				}
			}
			else{					//繼續下落
				ReDraw(point[0], point[1], id);
				point[0]++;
				Draw(point[0], point[1], id);
			}
		}

		if (_kbhit()){				//鍵盤輸入值時
			int key, key2;
			key = _getch();
			if (key == 224){
				key2 = _getch();

				if (key2 == 72){			//按向上方向鍵時
					int temp = id;
					Turn(id);
					if (Judge(point[0], point[1], id))
						id = temp;
					ReDraw(point[0], point[1], temp);
					Draw(point[0], point[1], id);
				}
				if (key2 == 80){				//按向下方向鍵時
					if (!Judge(point[0] + 2, point[1], id)){
						ReDraw(point[0], point[1], id);
						point[0] += 2;
						Draw(point[0], point[1], id);
					}
				}
				else if (key2 == 75){				//按向左方向鍵時
					if (!Judge(point[0], point[1] - 1, id)){
						ReDraw(point[0], point[1], id);
						point[1]--;
						Draw(point[0], point[1], id);
					}
				}
				else if (key2 == 77){					//按向右方向鍵時
					if (!Judge(point[0], point[1] + 1, id)){
						ReDraw(point[0], point[1], id);
						point[1]++;
						Draw(point[0], point[1], id);
					}
				}
			}
			else if (key == 32)					// 按下空格暫停
				Pause();
		}

		if (Judge(point[0] + 1, point[1], id))
			next=0;
		else{
			next=1;
			Sleep(1); //等待1毫秒
		}
		i++;				//控制下落間隔
	}
}

void game_b(void){
  cout<<"遊戲B\n";
}

