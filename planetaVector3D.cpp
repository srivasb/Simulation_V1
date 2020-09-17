// Simular planeta por dinamica molecular


#include <iostream>
#include <cmath>
#include "Vector.h"
using namespace std;

// Constante
const double GM=1.0;

// Creacion de un objeto

class Cuerpo{
    private:
        vector3D r,V,F; double m,R;
    public:
        void Inicie(double x0,double y0, double Vx0, double Vy0, double m, double R);
        void CalculeFuerza(void);
        void Muevase(double dt);
        void Dibujese(void);
        double Getx(void){return r[0];}; //inline
        double Gety(void){return r[1];}; //Inline
};

void Cuerpo::Inicie(double x0,double y0, double Vx0, double Vy0, double m0, double R0){
    r.cargue(x0,y0,0);
    V.cargue(Vx0,Vy0,0);
    m=m0; R=R0;
}

void Cuerpo::CalculeFuerza(void){
    double aux=-GM*m*pow(r[0]*r[0]+r[1]*r[1],-1.5);
    F.cargue(aux*r[0],aux*r[1],0);
}

void Cuerpo::Muevase(double dt){
    r[0]+=V[0]*dt;
    r[1]+=V[1]*dt;
    V[0]+=(F[0]/m)*dt;
    V[1]+=(F[1]/m)*dt;
}

void Cuerpo::Dibujese(void){
    cout<<" , "<<r[0]<<"+"<<R<<"*cos(t),"<<r[1]<<"+"<<R<<"*sin(t)";
}

//------Funciones Globales de Animacion-------
void InicieAnimacion(void){
    cout<<"set terminal gif animate"<<endl;
    cout<<"set output 'Planeta.gif'"<<endl;
    cout<<"unset key"<<endl;
    cout<<"set xrange[-15:15]"<<endl;
    cout<<"set yrange[-15:15]"<<endl;
    cout<<"set size ratio -1"<<endl;
    cout<<"set parametric"<<endl;
    cout<<"set trange[0:7]"<<endl;
    cout<<"set isosamples 12"<<endl;
}

void InicieCuadro(void){
    cout<<"plot 0,0"<<endl;
}

void TermineCuadro(void){
    cout<<endl;
}


int main(void){
    Cuerpo Planeta;
    double r0=10, m0=1;
    double omega, V0, T;

    omega=pow(GM/(r0*r0*r0),0.5);
    T = 1*M_PI/omega;
    V0=omega*r0;

    double t,tdibujo,tmax=3.3*T,dt=0.001;
    double tcuadro=T/100;

    //-----------(x0,y0,Vx0,Vy0,m0,R0)
    Planeta.Inicie(r0,0,0,V0,m0,0.5);
    //InicieAnimacion(); //Dibujar

    for(t=0,tdibujo=0; t<tmax; t+=dt,tdibujo+=0.1){
        //Dibujar
        /*
        if(tdibujo>tcuadro){
            InicieCuadro();
            Planeta.Dibujese();
            TermineCuadro();
            }
        */
       cout<<t<<" "<<Planeta.Getx()<< " "<< Planeta.Gety()<<endl;
       Planeta.CalculeFuerza();
       Planeta.Muevase(dt);
    }
    return 0;
}
