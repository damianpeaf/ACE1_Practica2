#include <cstdlib>
#include <iostream>
#include <string>

//#include "ListaDobleCircular.cpp"


#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>
#include "LinkedList.cpp"

using namespace std;
 
int main(int argc, char** argv) {
    LinkedList prueba;
    Package paquete;
    paquete = Package(1,2,3,4,3);
    prueba.Insert(paquete);
    paquete = Package(1,2,3,4,2);
    prueba.Insert(paquete);
    paquete = Package(1,2,3,4,4);
    prueba.Insert(paquete);
    paquete = Package(1,2,3,4,8);
    prueba.Insert(paquete);
    paquete = Package(1,2,3,4,10);
    prueba.Insert(paquete);
    cout << prueba.getMedia() << endl;

    prueba.Sort();
    prueba.Print();
    cout << prueba.getMediana() << endl;
    return 0;
}
