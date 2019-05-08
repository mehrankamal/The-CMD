#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<time.h>
#include<conio.h>
#include<windows.h>



using namespace std;

enum DIR {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

void startGame();
void leadBoard();

void gotoxy(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Ball
{
    private:
        int x, y;
        int orgX, orgY;
        DIR direction;
    public:
        Ball(int posX, int posY)
        {
            orgX = posX;
            orgY = posY;
            x = posX;
            y = posY;
            direction = STOP;
        }
        void reset()
        {
            x = orgX;
            y = orgY;
            direction = STOP;
        }
        void changeDir(DIR d)
        {
            direction = d;
        }
        void randomDir()
        {
            direction = (DIR) ((rand()%6)+1);
        }
        inline int getX()
        {
            return x;
        }
        inline int getY()
        {
            return y;
        }
        inline DIR getDirection()
        {
            return direction;
        }
        void move()
        {
            switch(direction)
            {
                case STOP:
                    break;
                case LEFT:
                    x--;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UPLEFT:
                    x--;
                    y--;
                    break;
                case DOWNLEFT:
                    x--;
                    y++;
                    break;
                case UPRIGHT:
                    x++;
                    y--;
                    break;
                case DOWNRIGHT:
                    x++;
                    y++;
                    break;
                default:
                    break;
            }
        }
        friend ostream & operator << (ostream & out, Ball ball)
        {
            out << "Ball [" << ball.x << ", " << ball.y << "]["<< ball.direction << "]";
            return out;
        }
};

class Paddle
{
    private:
        int x, y;
        int originalX, originalY;
    public:
        Paddle()
        {
            x = y = 0;
        }
        Paddle(int posX, int posY) : Paddle()
        {
            originalX = posX;
            originalY = posY;
            x = posX;
            y = posY;
        }
        inline void reset()
        {
            x = originalX;
            y = originalY;
        }
        inline int getX()
        {
            return x;
        }
        inline int getY()
        {
            return y;
        }
        inline void moveUp()
        {
            y--;
        }
        inline void moveDown()
        {
            y++;
        }
        friend ostream & operator << (ostream & out, Paddle pad)
        {
            out << "Paddle [" << pad.x << ", " << pad.y << "]";
        }

};

class PingPong
{
    private:
        int width, height;
        int scoreP1, scoreP2;
        string nameP1, nameP2;
        char up1, down1, up2, down2;
        bool quit;
        Ball *ball;
        Paddle *p1;
        Paddle *p2;
    public:
        PingPong(int w, int h, string name1, string name2)
        {
            srand(time(NULL));
            quit = false;
            up1 = 'w';
            up2 = 'i';
            down1 = 's';
            down2 = 'k';
            scoreP1 = scoreP2 = 0;
            width = w;
            height = h;
            ball = new Ball(w/2, h/2);
            p1 = new Paddle(1, h/2 - 3);
            p2 = new Paddle(w-2, h/2 - 3);
            nameP1 = name1;
            nameP2 = name2;
        }

        void scoreUp(Paddle * player)
        {
            if(player == p1)
                scoreP1++;
            else if(player == p2)
                scoreP2++;

            ball -> reset();
            p1 -> reset();
            p2 -> reset();
        }

        void draw()
        {
//            system("cls");
			gotoxy(0, 0);
            for(int i=0; i<=width+1; i++) cout << "\xB2";
            cout << endl;

            for(int i=0; i<height; i++)
            {

                for(int j=0; j<width; j++)
                {
                    
                    int ballX = ball->getX();
                    int ballY = ball->getY();
                    int player1x = p1->getX();
                    int player2x = p2->getX();
                    int player1y = p1->getY();
                    int player2y = p2->getY();
					
					if (j == 0)	cout << "\xB2";
 
	                if (ballX == j && ballY == i)	cout << "O"; //ball
	                else if (player1x == j && player1y == i)	cout << "\xDB"; //player1
	                else if (player2x == j && player2y == i)	cout << "\xDB"; //player2
	                else if (player1x == j && player1y + 1 == i)	cout << "\xDB"; //player1
	                else if (player1x == j && player1y + 2 == i)	cout << "\xDB"; //player1
	                else if (player1x == j && player1y + 3 == i)	cout << "\xDB"; //player1
	                else if (player2x == j && player2y + 1 == i)	cout << "\xDB"; //player1
	                else if (player2x == j && player2y + 2 == i)	cout << "\xDB"; //player1
	                else if (player2x == j && player2y + 3 == i)	cout << "\xDB"; //player1
					else	cout << " ";
					
					if(j == width-1) cout << "\xB2";
                    
                }
                cout << endl;
            }

            for(int i=0; i<=width+1; i++) cout << "\xB2";
            cout << endl;
            cout << "\n\n\n\t\t\t\t******Scores******"<< endl;
            cout << "\t\t\t\t" << nameP1 << "\t\t" << scoreP1 << endl;
            cout << "\t\t\t\t" << nameP2 << "\t\t" << scoreP2 << endl;
        }

		void input()
		{
			ball->move();
			
			int ballX = ball->getX();
			int ballY = ball->getY();
			int player1x = p1->getX();
			int player2x = p2->getX();
			int player1y = p1->getY();
			int player2y = p2->getY();
			
			if(kbhit())
			{
				char curr = getch();
				if(curr == up1)
					if (player1y > 0)	p1->moveUp();
				if(curr == up2)
					if (player2y > 0)	p2->moveUp();
					
				if(curr == down1)
					if (player1y+4 < height)	p1->moveDown();
				
				if(curr == down2)
					if (player2y+4 < height)	p2->moveDown();
					
				if(ball->getDirection() == STOP)
					ball->randomDir();
				
				if(curr == 'q')
					quit = true;
			}
		}
		
		void logic()
		{
			int ballX = ball->getX();
			int ballY = ball->getY();
			int player1x = p1->getX();
			int player2x = p2->getX();
			int player1y = p1->getY();
			int player2y = p2->getY();
			
			//For left paddle
			for(int i=0; i<4; i++)
				if(ballX == player1x+1)
					if(ballY == player1y+i)	ball->changeDir((DIR)((rand()%3)+4));
			for(int i=0; i<4; i++)
				if(ballX == player2x-1)
					if(ballY == player2y+i)	ball->changeDir((DIR)((rand()%3)+1));
					
			if(ballY == height-1)	ball->changeDir(ball->getDirection()==DOWNRIGHT ? UPRIGHT:UPLEFT);
			if(ballY == 0)	ball->changeDir(ball->getDirection()==UPRIGHT ? DOWNRIGHT:DOWNLEFT);
			if(ballX == width-1)	scoreUp(p1);
			if(ballX == 0)	scoreUp(p2);
			
			if(scoreP1>scoreP2 && scoreP1 >=10)
			{
				system("cls");
				cout << endl << endl;
				cout << "\t\t\t*********************************" << endl;
				cout << "\t\t\t*                               *" << endl;
				cout << "\t\t\t" << nameP1 << " Won!!" << endl;
				cout << "\t\t\t*                               *" << endl;
				cout << "\t\t\t*********************************" << endl;
                writeToFile();
				quit = true;
			}
			if(scoreP2>scoreP1 && scoreP2 >= 10)
			{
				system("cls");
				cout << endl << endl;
				cout << "\t\t\t**********************************" << endl;
				cout << "\t\t\t*                                *" << endl;
				cout << "\t\t\t" << nameP2 << " Won!!" << endl;
				cout << "\t\t\t*                                *" << endl;
				cout << "\t\t\t**********************************" << endl;
				writeToFile();
                quit = true;
			}
		}
		
        void writeToFile()
        {
            ofstream file_out;
            file_out.open("high_scores.csv", ios::app);
            file_out.seekp(0, ios::beg);
            file_out << nameP1 << "," << scoreP1 << "," << nameP2 << "," << scoreP2 << endl;
            file_out.close();
        }

		void run()
		{
			while(!quit)
			{
				draw();
				input();
				logic();
			}
		}

        ~PingPong()
        {
            delete ball, p1, p2;
        }
};

int main()
{
//    keybd_event(VK_MENU,0x38,0,0);
//    keybd_event(VK_RETURN,0x1c,0,0);
//    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
//    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);


    char select;

    do
    {
        system("cls");
        cout << "\n\n\n\n\t\t\t**********Main Menu**********" << endl;
        cout << "\t\t\t** 1.| Play" << endl;
        cout << "\t\t\t** 2.| Leader Board" << endl;
        cout << "\t\t\t** 3.| Exit" << endl;
        select = getch();
        switch(select)
        {
            case '1':
                startGame();
                break;
            case '2':
                leadBoard();
                break;
            case '3':
                cout << "Exitting ";
                for(int i=0; i<3; i++)
                {
                    for(int i=0; i<100000000; i++);
                        cout << " .";
                }
                cout << endl;
                break;
            default:
                break;
        }
    }
    while(!(select=='3'));

    return 0;
}

void leadBoard()
{
    ifstream file_in;
    file_in.open("high_scores.csv");

    if(file_in.fail())
    {
        cout << "No record found!" << endl;
        return;
    }

    vector<string> arr1D(4);
    vector<vector<string>> arr2D;
    do
    {
        getline(file_in, arr1D[0], ',');
        getline(file_in, arr1D[1], ',');
        getline(file_in, arr1D[2], ',');
        getline(file_in, arr1D[3]);
        arr2D.push_back(arr1D);
    }
    while(file_in);

    system("cls");

    cout << "\n\n\n\n\t\t\tPlayer 1 Name\t\t\tScore 1\t\t\tPlayer 2 Name\t\t\tScore 2\n";
    for(int i=0; i<arr2D.size(); i++)
    {
        cout << "\t\t\t"<< arr2D[i][0] << "\t\t\t\t" << arr2D[i][1] << "\t\t\t" << arr2D[i][2] << "\t\t\t\t" << arr2D[i][3] << endl;
    }

    cout << "Press Enter key to continue..." << endl;
    getch();

    file_in.close();
}

void startGame()
{
    char prompt = 'y';

    system("cls");

	do
	{
        string n1, n2;
        cout << "\n\n\n\t\t\t\tEnter name for Player 1:  ";
        getline(cin, n1);
        cout << "\t\t\t\tEnter name for Player 2:  ";
        getline(cin, n2);
        system("cls");
    	PingPong game(60, 15, n1, n2);
    	game.run();
    	cout << "\t\t\t\tPress any key to continue..." << endl;
        getch();
    	system("cls");
	}
	while(!(prompt == 'n' || prompt == 'N'));


    cout << "\n\n";
    system("cls");
}