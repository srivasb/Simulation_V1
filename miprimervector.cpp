// Simular planeta por dinamica molecular


#include <iostream>
#include <cmath>
#include "Vector.h"
using namespace std;


int main(void){
    vector3D a,b,c;
    a.cargue(1,0,0);
    b.cargue(0,1,0);
    c=a+(a^b);
    a.show();
    b.show();
    c.show();
    return 0;
}
