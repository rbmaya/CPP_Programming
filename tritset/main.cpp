#include <iostream>
#include "tritset"

using namespace std;

int main() {

    TritSet setA(10);

    TritSet setB(3);

    setA[6] = True;
    setA[3] = False;
    setA[2] = False;

    cout << setA.length();


    return 0;
}