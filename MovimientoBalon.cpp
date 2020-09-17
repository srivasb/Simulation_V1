// Simular el movimiento de un balon por Dinámina Molecular

#include <iostream>
#include <cmath>
using namespace std;

// Constante
const double g=9.8;

// Creacion de un objeto

class Cuerpo{
    private:
        double x,y,Vx,Vy,Fx,Fy,m,R;
    public:
        void Inicie(double x0,double y0, double Vx0, double Vy0, double m, double R);
        void CalculeFuerza(void);
        void Muevase(double dt);
        void Dibujese(void);
        double Getx(void){return x;}; //inline
        double Gety(void){return y;}; //Inline
};

void Cuerpo::Inicie(double x0,double y0, double Vx0, double Vy0, double m0, double R0){
    x=x0; y=y0;
    Vx=Vx0; Vy=Vy0;
    m=m0; R=R0;
}

void Cuerpo::CalculeFuerza(void){
    Fx=0;Fy=-m*g;
}

void Cuerpo::Muevase(double dt){
    x+=Vx*dt;
    y+=Vy*dt;
    Vx+=(Fx/m)*dt;
    Vy+=(Fy/m)*dt;
}

void Cuerpo::Dibujese(void){
    cout<<" , "<<x<<"+"<<R<<"*cos(t),"<<y<<"+"<<R<<"*sin(t)";
}

//------Funciones Globales de Animacion-------
void InicieAnimacion(void){
    cout<<"set terminal gif animate"<<endl;
    cout<<"set output 'Balon.gif'"<<endl;
    cout<<"unset key"<<endl;
    cout<<"set xrange[-0.5:21]"<<endl;
    cout<<"set yrange[-3:5]"<<endl;
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
    Cuerpo Balon;
    double t,tmax=2,dt=0.1;
    double tdibujo;
    //---------(x0,y0,Vx0,Vy0,m0,R0)
    Balon.Inicie(0,0,5,8,0.5,0.5);
    InicieAnimacion(); //Dibujar
    for(t=0,tdibujo=0;t<tmax;t+=dt){
        //Dibujar
        InicieCuadro();
        Balon.Dibujese();
        TermineCuadro();
       //cout<<t<<" "<<Balon.Getx()<< " "<< Balon.Gety()<<endl;
       Balon.CalculeFuerza();
       Balon.Muevase(dt);
    }
    return 0;
}
