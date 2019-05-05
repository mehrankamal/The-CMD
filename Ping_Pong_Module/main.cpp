#include<iostream>
#include<cstdlib>
#include<time.h>
#include<conio.h>
#include<windows.h>



using namespace std;

enum DIR {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

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
        char up1, down1, up2, down2;
        bool quit;
        Ball *ball;
        Paddle *p1;
        Paddle *p2;
    public:
        PingPong(int w, int h)
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
            cout << "******Scores******"<< endl;
            cout << "Player 1: " << scoreP1 << endl;
            cout << "Player 2: " << scoreP2 << endl;
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
				cout << "\t\t\t**********************************" << endl;
				cout << "\t\t\t*                                *" << endl;
				cout << "\t\t\t********** Player 1 won!! ********" << endl;
				cout << "\t\t\t*                                *" << endl;
				cout << "\t\t\t**********************************" << endl;
				quit = true;
			}
			if(scoreP2>scoreP1 && scoreP2 >= 10)
			{
				system("cls");
				cout << endl << endl;
				cout << "\t\t\t**********************************" << endl;
				cout << "\t\t\t*                                *" << endl;
				cout << "\t\t\t********** Player 2 won!! ********" << endl;
				cout << "\t\t\t*                                *" << endl;
				cout << "\t\t\t**********************************" << endl;
				quit = true;
			}
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

	char prompt = 'y';

	do
	{
    	PingPong game(60, 15);
    	game.run();
    	cout << endl << endl << "Do you want to play another round?? (y/n)  ";
    	cin >> prompt;
    	system("cls");
	}
	while(!(prompt == 'n' || prompt == 'N'));


    cout << "\n\n";
    system("pause");

    return 0;
}
