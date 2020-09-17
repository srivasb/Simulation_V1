//Integrar Ecuacion Diferencial de primer orden Por Euler 
// (dx/dt) = f(t,m)

#include <iostream>
#include <cmath>
using namespace std;

const double  epsilon = pow(10,-8);

double f(double t,double x){
    return x/2.0; 
}


double UnPasoEuler(double & t, double & x, double dt){
    //Funcion que modifique valores de x y t
    double dx;
    dx=dt*f(t,x);
    x+=dx; t+=dt;
}

int main(void){
     
    double t,x;
    double dt=0.1;
    for(t=0,x=1;t<10; ){
        cout<<t<<" "<<x<<endl;
        UnPasoEuler(t,x,dt);
    }
    return 0;
}
