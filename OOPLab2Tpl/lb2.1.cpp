#include <iostream>

using namespace std;

int main(){
    int a,b,c,d,x,y;
    cin>>a>>b>>c>>d;
    x=b+(b<<5)+(((d<<4)-d+(a<<3)+(a<<2))>>9)-(c+(c<<6))+(d<<1)+(d<<3)+(d<<2);
    y=33*b+((15*d+12*a)/512)-65*c+14*d;
    cout<<"Result(bits):"<<x<<"\n";
    cout<<"Result:"<<y;

    return 0;
}