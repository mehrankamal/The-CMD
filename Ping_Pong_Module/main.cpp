#include<iostream>
#include<cstdlib>
#include<time.h>

using namespace std;

enum DIR {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

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

int main()
{
    srand(time(NULL));

    Ball ball(0, 0);
    cout << ball << endl;
    ball.randomDir();
    ball.move();
    cout << ball << endl;
    ball.randomDir();
    ball.move();
    cout << ball << endl;

    return 0;
}