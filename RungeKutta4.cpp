//Integrar Ecuacion Diferencial de primer orden Por Euler 
// (dx/dt) = f(t,m)

#include <iostream>
#include <cmath>
using namespace std;

const double  epsilon = pow(10,-8);

double f(double t,double x){
    return x/2.0; 
}


double UnPasoRungeKutta4(double & t, double & x, double dt){
    //Funcion que modifique valores de x y t
    double dx1,dx2,dx3,dx4;
    dx1=dt*f(t,x);
    dx2=dt*f(t+dt/2.0,x+dx1/2.0);
    dx3=dx2=dt*f(t+dt/2.0,x+dx2/2.0);
    dx4=dt*f(t+dt,x+dx3);
    x+=(dx1+2.0*dx2+2.0*dx3+dx4)/6.0;
    t+=dt;
}

int main(void){
    double t,x;
    double dt=0.1;
    for(t=0,x=1;t<10; ){
        cout<<t<<" "<<x<<" "<<exp(t/2)<<endl;
        UnPasoRungeKutta4(t,x,dt);
    }
    return 0;
}
