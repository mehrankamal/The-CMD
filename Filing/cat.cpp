#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream file;
    file.open(argv[1]);
    char str[251];

    while(file)
    {
        file.getline(str, 250);
        cout << str << endl;
    }

    file.close();

    return 0;
}