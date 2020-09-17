//Integrar Ecuacion Diferencial de primer orden Por Euler 
// (dx/dt) = f(t,m)

#include <iostream>
#include <cmath>
using namespace std;

const double  T=2*M_PI;
const double Omega=2*M_PI/T;

double f1(double t,double x1, double x2){
    return -1.0*Omega*Omega*x2; 
}

double f2(double t,double x1, double x2){ 
    return x1;
}


double UnPasoRungeKutta4(double & t, double & x1, double & x2, double dt){
    //Funcion que modifique valores de x1, x2 y t
    double dx11,dx21,dx31,dx41; 
    double dx12,dx22,dx32,dx42;

    dx11=dt*f1(t,x1,x2);   
    dx12=dt*f2(t,x1,x2);

    dx21=dt*f1(t+dt/2.0,x1+dx11*0.5,x2+dx12/2.0);
    dx22=dt*f2(t+dt/2.0,x1+0.5*dx11,x2+dx12/2.0);

    dx31=dt*f1(t+dt/2.0,x1+dx21/2.0,x1+dx22/2.0);
    dx32=dt*f2(t+dt/2.0,x1+dx21/2.0,x1+dx22/2.0);

    dx41=dt*f1(t+dt,x1+dx31,x2+dx32);
    dx42=dt*f2(t+dt,x1+dx31,x2+dx32);

    x1+=(dx11+2.0*dx21+2.0*dx31+dx41)/6.0;
    x2+=(dx12+2.0*dx22+2.0*dx32+dx42)/6.0;
    t+=dt;
}

int main(void){
    double t,x1,x2;
    double dt=0.1;
    for(t=0,x1=1,x2=0;t<100; ){
        cout<<t<<" "<<x1<<" "<<x2<<endl;
        UnPasoRungeKutta4(t,x1,x2,dt);
    }
    return 0;
}
