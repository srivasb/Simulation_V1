// Simular planeta por dinamica molecular
#include <iostream>
#include <cmath>
#include "Vector.h"
using namespace std;

// Constante
const double GM=1.0;
const double theta = (1.0/(2-pow(2,1.0/3)));
const double theta_medios=theta/2;
const double Unomenos_thetamedios = 1.0-theta_medios;
const double Unomenos_DosTheta= 1.0-2.0*theta;

// Creacion de un objeto

class Cuerpo{
    private:
        vector3D r,V,F; double m,R;
    public:
        void Inicie(double x0,double y0, double Vx0, double Vy0, double m, double R);
        void CalculeFuerza(void);
        void Muevar(double dt, double Coeficiente);
        void MuevaV(double dt,double Coeficiente);
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

void Cuerpo::Muevar(double dt,double Coeficiente){
    r+=V*(Coeficiente*dt);
}

void Cuerpo::MuevaV(double dt,double Coeficiente){
    V+=F*Coeficiente*dt/m;
}


//------Funciones Globales de Animacion-------
void Cuerpo::Dibujese(void){
    cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)"<<endl;
}

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

    omega=sqrt(GM/(r0*r0*r0));
    T = 1*M_PI/omega;
    V0=omega*r0;

    double t,tdibujo,tmax=3.3*T,dt=0.01;
    double tcuadro=T/100;

    //InicieAnimacion(); //Dibujar

    //-----------(x0,y0,Vx0,Vy0,m0,R0)
    Planeta.Inicie(r0,0,0,0.5*V0,m0,0.5);
    Planeta.CalculeFuerza();

    for(t=0,tdibujo=0; t<tmax; t+=dt,tdibujo+=0.1){
        
        if(tdibujo>tcuadro){
             //Dibujar
             /*
            InicieCuadro();
            Planeta.Dibujese();
            TermineCuadro();
            */
        cout<<Planeta.Getx()<< " "<< Planeta.Gety()<<endl;
            }
        
       //Forest-Roth
       Planeta.Muevar(dt,theta_medios);
       Planeta.CalculeFuerza(); Planeta.MuevaV(dt,theta);
       Planeta.Muevar(dt,Unomenos_thetamedios); Planeta.CalculeFuerza();
       Planeta.MuevaV(dt,Unomenos_DosTheta);
       Planeta.Muevar(dt,Unomenos_thetamedios);
       Planeta.CalculeFuerza(); Planeta.MuevaV(dt,theta);
       Planeta.Muevar(dt,theta_medios);
    }
    return 0;
}