// Simular planeta por dinamica molecular
#include <iostream>
#include <cmath>
using namespace std;

// Constante
const double GM=1.0;

// Creacion de un objeto

class Cuerpo{
    private:
        double x,y,Vx,Vy,Fx,Fy,m,R;
    public:
        void Inicie(double x0,double y0, double Vx0, double Vy0, double m0, double R0);
        void CalculeFuerza(void);
        void Muevase(double dt);
        void Dibujese(void);
        double Getx(void){return x;}; //inline
        double Gety(void){return y;}; //Inline
};

void Cuerpo::Inicie(double x0,double y0, double Vx0, double Vy0, double m0, double R0){
    x=x0; y=y0; Vx=Vx0; Vy=Vy0; m=m0; R=R0;
}

void Cuerpo::CalculeFuerza(void){
    double aux=-GM*m*pow(x*x+y*y,-1.5);
    Fx=aux*x;
    Fy=aux*y;
}

void Cuerpo::Muevase(double dt){
    x+=Vx*dt; y+=Vy*dt;
    Vx+=(Fx/m)*dt; Vy+=(Fy/m)*dt;
}

void Cuerpo::Dibujese(void){
    cout<<", "<<x<<"+"<<R<<"*cos(t),"<<y<<"+"<<R<<"*sin(t)";
}

//------Funciones Globales de Animacion-------
void InicieAnimacion(void){
    //cout<<"set terminal gif animate"<<endl;
    //cout<<"set output 'Planeta.gif'"<<endl;
    cout<<"unset key"<<endl;
    cout<<"set xrange[-12:12]"<<endl;
    cout<<"set yrange[-12:12]"<<endl;
    cout<<"set size ratio -1"<<endl;
    cout<<"set parametric"<<endl;
    cout<<"set trange[0:7]"<<endl;
    cout<<"set isosamples 12"<<endl;
}

void InicieCuadro(void){
    cout<<"plot 0,0 "<<endl;
}

void TermineCuadro(void){
    cout<<endl;
}

//----------------Main Program----------------
int main(void){
    Cuerpo Planeta;
    double r0=10, m0=1;
    double omega, V0, T;

    omega=sqrt(GM/(r0*r0*r0));
    T = 2*M_PI/omega;
    V0=r0*omega;

    double t,tdibujo,tmax=3.3*T,dt=0.0001;
    double tcuadro=T/100;

    //------Inicio Animacion----------
    InicieAnimacion(); //Dibujar

    //---------Condiciones Iniciales-------
    //-----------(x0,y0,Vx0,Vy0,m0,R0)
    Planeta.Inicie(r0,0,0,V0,m0,0.5);
    

    for(t=0,tdibujo=0; t<tmax; t+=dt,tdibujo+=dt){
        //Dibujar
        if(tdibujo>tcuadro){
            InicieCuadro();
            Planeta.Dibujese();
            TermineCuadro();
            }
        //cout<<t<<" "<<Planeta.Getx()<< " "<< Planeta.Gety()<<endl;
       Planeta.CalculeFuerza();
       Planeta.Muevase(dt);
    }
    return 0;
}
