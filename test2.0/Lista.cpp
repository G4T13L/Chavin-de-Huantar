#include "iostream"
using namespace std;
class Elemento{
public:
   Elemento(float x,float y,float z,float r){
      ex = x;
      ey = y;
      ez = z;
      er = r;

   }
   void setPos(float x,float y,float z);
   void getPos(float &x,float &y,float &z);
   void setR(float r);
   static bool compare(Elemento e1,Elemento e2);
   Elemento* sig;
private:
   float ex,ey,ez;
   float ea,eb,ec;
   float er;
};

static bool compare(Elemento e1,Elemento e2){

}

void setRot(float r){
   this->er=r;
}

void Elemento::setPos(float x,float y,float z){
   this->ex = x;
   this->ey = y;
   this->ez = z;
}
void Elemento::getPos(float &x,float &y,float &z){
   x = ex;
   y = ey;
   z = ez;
}

class Lista{
public:
   Lista(){
      inicio = NULL;
      fin = NULL;
      tam=0;
   }

   Elemento* inicio;
   Elemento* fin;
   int tam;
   void Init();
   void agregar(float x,float y,float z,float r);
   void quitar();
};

void Lista::agregar(float x,float y,float z,float r){
   if (inicio = NULL){
      tam = 1;
      Elemento* nuevo_elemento = new Elemento(x,y,z,r);
      inicio = nuevo_elemento;
      fin = nuevo_elemento;
   }else {
      tam++;
      Elemento* nuevo_elemento = new Elemento(x,y,z,r);
      inicio = nuevo_elemento;
   }
}

void Lista::quitar(){
   if (inicio = NULL){
      return;
   } else {
      Elemento* aux = inicio;
      inicio = inicio->sig;
   }
}

int main (int argc, char **argv){
   Lista l;
   l.agregar(5,8,10,1);
   float x,y,z;
   l.inicio->getPos(x,y,z);
   cout << x<<" "<< y <<" "<< z<<endl;
}
