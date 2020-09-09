//Modelo SIR Punto uno
// (dx/dt) = f(t,m)

#include <iostream>
#include <cmath>
using namespace std;

const double a=0.35;
const double b=0.08;

double f1(double t,double s, double ii){
    return -a*s*ii; 
}

double f2(double t,double s, double ii){ 
    return a*s*ii - b*ii;
}

double f3(double t, double r, double ii){
    return b*ii;
}


double UnPasoRungeKutta4(double & t, double & s, double & ii, double & r, double dt){
    //funcion que modifique valores de s, ii y t
    double ds1,dii1,dx31,dx41; 
    double di1,dii2,dx32,dx42;

    ds1=dt*f1(t,s,ii);   
    di1=dt*f2(t,s,ii);

    dii1=dt*f1(t+dt/2.0,s+ds1*0.5,ii+di1/2.0);
    dii2=dt*f2(t+dt/2.0,s+0.5*ds1,ii+di1/2.0);

    dx31=dt*f1(t+dt/2.0,s+dii1/2.0,s+dii2/2.0);
    dx32=dt*f2(t+dt/2.0,s+dii1/2.0,s+dii2/2.0);

    dx41=dt*f1(t+dt,s+dx31,ii+dx32);
    dx42=dt*f2(t+dt,s+dx31,ii+dx32);

    s+=(ds1+2.0*dii1+2.0*dx31+dx41)/6.0;
    ii+=(di1+2.0*dii2+2.0*dx32+dx42)/6.0;

    r=1-s-ii;

    t+=dt;
}


int main(void){
    double t,s,ii,r;
    double dt=0.1;
    // Condiciones Iniciales: 
    s=0.999;
    ii=0.001;
    r=0.0;
    for(t=0;t<100; ){
        cout<<t<<","<<s<<","<<ii<<","<<r<<endl;
        UnPasoRungeKutta4(t,s,ii,r,dt);
    }
    return 0;
}
