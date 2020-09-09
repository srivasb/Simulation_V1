//Modelo SIR Para Colombia N=45000000
// Ecucaciones: 
//            ds/dt = -b*s*i
//            di/dt = b*s*i-a*i
//            dr/dt = a*1
//            s+i+r=1 (para todo t)



#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

const double rata=1.0388469;
const double log_rata=log(rata);

double f_gamma(double a){
    return log_rata+a;
}

double f1(double a, double b, double t,double s, double ii){
    return -b*s*ii; 
}

double f2(double a, double b,double t,double s, double ii){ 
    return b*s*ii - a*ii;
} 

double f3(double a, double b,double t, double r, double ii){
    return a*ii;
}


double UnPasoRungeKutta4(double a, double b,double & t, double & s, double & ii, double & r, double dt){
    //funcion que modifique valores de s, ii y t
    double ds1,dii1,dx31,dx41; 
    double di1,dii2,dx32,dx42;

    ds1=dt*f1(a,b,t,s,ii);   
    di1=dt*f2(a,b,t,s,ii);

    dii1=dt*f1(a,b,t+dt/2.0,s+ds1*0.5,ii+di1/2.0);
    dii2=dt*f2(a,b,t+dt/2.0,s+0.5*ds1,ii+di1/2.0);

    dx31=dt*f1(a,b,t+dt/2.0,s+dii1/2.0,s+dii2/2.0);
    dx32=dt*f2(a,b,t+dt/2.0,s+dii1/2.0,s+dii2/2.0);

    dx41=dt*f1(a,b,t+dt,s+dx31,ii+dx32);
    dx42=dt*f2(a,b,t+dt,s+dx31,ii+dx32);
  
    s+=(ds1+2.0*dii1+2.0*dx31+dx41)/6.0;
    ii+=(di1+2.0*dii2+2.0*dx32+dx42)/6.0;
 
    r=1-s-ii;

    t+=dt;
}


int main(void){

   //-----gamma,beta
    double a,b;

    double t,s,i,r;
    double dt=0.1;

    // Condiciones Iniciales: 
    i=0.00006;
    s=0.99994;
    r=0;


    // To pick initial values of Gamma
    /* initialize random seed: */
    // srand (time(NULL));

    /* Generate random number between 0 and 1: */
    /* Select values for a and b */
    /* Betta always greater than Gamma */

    //a = (rand() % 10 + 1)/10.0;
    //b = f_gamma(a);

    a=0.013;
    b=f_gamma(a);
  
  cout<<0.0<<","<<rata<<","<<a<<","<<b<<endl;

    for(t=0;t<1000; ){
        cout<<t<<","<<s<<","<<i<<","<<r<<endl;
        UnPasoRungeKutta4(a,b,t,s,i,r,dt);
        }
    return 0;
}