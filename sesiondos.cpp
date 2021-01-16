//Metodo de Biseccion
#include <iostream>
#include <cmath>
using namespace std;

const double  epsilon = pow(10,-8);

double f(double x){
    return sin(x); 
}

double BesselIntegrant(double t,double x, double Alpha){
    return cos(Alpha*t-x*sin(t)); 
}

double biseccion(double a, double b){
    double m = (a+b)/2.0;
    double fm = f(m);
    double fa = f(a);
    if ( b-a > epsilon ){
            if (fm*fa > 0) a = m; 
            else  b = m;
            return biseccion(a,b);
    }
    return m;
}

double IntegralSimpson(double a, double b, int n,double x, double Alpha){
    n=2*n;
    double area=0, t=0;
    double h = abs(b-a)/n;
    for (int i=0; i<=n;i++){
        t=a+i*h;
        if((i==0)||(i==n)) area+=BesselIntegrant(t,x,Alpha);
        else if (i%2 == 0) area += 2*BesselIntegrant(t,x,Alpha);
        else  area+=4*BesselIntegrant(t,x,Alpha);
        }
    return area*h/3;
};

double Bessel(double Alpha, double x,int n){
    return (1.0/M_PI)*IntegralSimpson(0,M_PI,n,x, Alpha);
}

int main(void){
    // cout << "raiz = " << biseccion(4,8) << endl;
    int n=50;
    double Alpha = 1;
    for (double x=0;x<10;x+=0.1)
        cout <<x << " " << Bessel(Alpha,x,n) << endl; 
    return 0;
} 
