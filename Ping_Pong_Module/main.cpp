#include<iostream>

using namespace std;

class Ball
{
    private:

    public:
        Ball(int x, int y);
        void reset();
        void changeDir();
        void randomDir();
        inline int getX();
        inline int getY();
        void move();
        friend ostream & operator << (ostream &, Ball ball);
};

int main()
{


    return 0;
}