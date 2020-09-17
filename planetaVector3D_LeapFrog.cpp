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
        void Arranque(double dt);
        void Muevase(double dt);
        void Dibujese(void);
        double Getx(void){return r.x();}; //inline
        double Gety(void){return r.y();}; //Inline
};

void Cuerpo::Inicie(double x0,double y0, double Vx0, double Vy0, double m0, double R0){
    r.cargue(x0,y0,0);
    V.cargue(Vx0,Vy0,0);
    m=m0; R=R0;
}

void Cuerpo::CalculeFuerza(void){
  double aux=GM*m*pow(norma2(r),-1.5);
  F=-aux*r;
} 

void Cuerpo::Arranque(double dt){
    V-=F*(dt/(2*m));
}

void Cuerpo::Muevase(double dt){
    r+=V*dt;
    V+=F*(dt/m);
}

void Cuerpo::Dibujese(void){
    cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)"<<endl;
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

    //InicieAnimacion(); //Dibujar

    //-----------(x0,y0,Vx0,Vy0,m0,R0)
    Planeta.Inicie(r0,0,0,0.5*V0,m0,0.5);
    Planeta.CalculeFuerza();
    Planeta.Arranque(dt);
    

    for(t=0,tdibujo=0; t<tmax; t+=dt,tdibujo+=0.1){
        //Dibujar
        /*
        if(tdibujo>tcuadro){
            InicieCuadro();
            Planeta.Dibujese();
            TermineCuadro();
            }
        */
       cout<<Planeta.Getx()<< " "<< Planeta.Gety()<<endl;
       
       Planeta.CalculeFuerza();
       Planeta.Muevase(dt);
    }
    return 0;
}
