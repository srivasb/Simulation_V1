// Simular planeta por dinamica molecular
//PEDRL
#include <iostream>
#include <cmath>
#include "Vector.h"
using namespace std;

//--------------Declarar Constante----------------
const int N=2;//Numero de cuerpos
const double G=1.0;

const double zeta=0.1786178958448091e0;
const double lambda=-0.2123418310626526054e0;
const double xi=-0.6626458266981849e-1;

//-----------------Declarar Clases------------------

class Cuerpo;
class Colisionador;

//----------- Interfase e Implementacion -----------

//----------------- Clase Cuerpo -----------------
class Cuerpo{
    private:
        vector3D r,V,F; 
        double m,R;
    public:
        void Inicie(double x0,double y0, double Vx0, double Vy0, double m, double R);
        void BorreFuerza(void){F.cargue(0,0,0);}; //inline
        void SumeFuerza(vector3D F0){F+=F0;}; //inline
        void Muevar(double dt, double Coeficiente);
        void MuevaV(double dt,double Coeficiente);
        void Dibujese(void);
        double Getx(void){return r.x();}; //inline
        double Gety(void){return r.y();}; //Inline
        friend class Colisionador;
};


void Cuerpo::Inicie(double x0,double y0, double Vx0, double Vy0, double m0, double R0){
    r.cargue(x0,y0,0);
    V.cargue(Vx0,Vy0,0);
    m=m0; R=R0;
}


void Cuerpo::Muevar(double dt,double Coeficiente){
   r += Coeficiente*V*dt;
}

void Cuerpo::MuevaV(double dt,double Coeficiente){
    V+=dt*Coeficiente*(F/m);
}


//------------------ Clase Colisionador ---------------
class Colisionador{
    private:
    public: 
        void CalculeFuerzas(Cuerpo * Planeta);
        void CalculeFuerzasEntre(Cuerpo & Planeta1,Cuerpo & Planeta2);
};

void Colisionador::CalculeFuerzas(Cuerpo * Planeta){
    int i,j;
    for(i=0;i<N;i++) Planeta[i].BorreFuerza();

    for(i=0;i<N;i++)
       for(j=i+1;j<N;j++)
            CalculeFuerzasEntre(Planeta[i], Planeta[j]);
               
}

void Colisionador::CalculeFuerzasEntre(Cuerpo & Planeta1,Cuerpo & Planeta2){
    vector3D r21=Planeta2.r-Planeta1.r;
    double aux=G*Planeta2.m*Planeta1.m*pow(norma2(r21),-1.5);
    vector3D F1=r21*aux;
    Planeta1.SumeFuerza(F1); Planeta2.SumeFuerza(-1.0*F1);
}



//---------------- Funciones Globales de Animacion ------------------
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


//------------------- Funcion Principal -------------------
int main(void){
    Cuerpo Planeta[N];
    Colisionador Newton;
    double r=100.0;
    double m0=10,m1=1.0,R0=10.0,R1=5.0;
    
    double M=m0+m1; double mu=(m0*m1)/M; 
    double x0=-r*m1/M, x1=r+x0; 

    double omega=sqrt(G*M/(r*r*r)),T = 2*M_PI/omega; 
    double V0=omega*x0, V1=omega*x1; 

    double t,tdibujo,tmax=3.3*T,tcuadro=T/100,dt=0.01; 
    int i;

    //Dibujar
    //InicieAnimacion(); 

    //-----------(x0,y0,Vx0,Vy0,m0,R0)
    Planeta[0].Inicie(x0,0,0,V0,m0,R0);
    Planeta[1].Inicie(x1,0,0,V1,m1,R1);

    cout<<"x0"<<","<<"y0"<<","<<"x1"<< ","<<"y1"<<endl;
    for(t=0,tdibujo=0; t<tmax; t+=dt,tdibujo+=0.1){

        //Dibujar
        if(tdibujo>tcuadro){
             /*
            InicieCuadro();
            Planeta.Dibujese();
            TermineCuadro();
            */
        // Imprimir en Pantalla
        cout<<Planeta[0].Getx()<<","<< Planeta[0].Gety()<<","<<Planeta[1].Getx()<< ","<< Planeta[1].Gety()<<endl;
            }
        
       //PEFRL
        for(i=0;i<N;i++) Planeta[i].Muevar(dt,zeta);
        Newton.CalculeFuerzas(Planeta); for(i=0;i<N;i++) Planeta[i].MuevaV(dt,(1-2*lambda)/2);
        for(i=0;i<N;i++) Planeta[i].Muevar(dt,xi); 
        Newton.CalculeFuerzas(Planeta); for(i=0;i<N;i++) Planeta[i].MuevaV(dt,lambda);
        for(i=0;i<N;i++) Planeta[i].Muevar(dt,1-2.0*(xi+zeta));
        Newton.CalculeFuerzas(Planeta); for(i=0;i<N;i++) Planeta[i].MuevaV(dt,lambda);
        for(i=0;i<N;i++) Planeta[i].Muevar(dt,xi);
        Newton.CalculeFuerzas(Planeta); for(i=0;i<N;i++) Planeta[i].MuevaV(dt,(1.0-2.0*lambda)/2.0);
        for(i=0;i<N;i++) Planeta[i].Muevar(dt,zeta);
    }

    return 0;
}