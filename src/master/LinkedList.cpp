
#include "LinkedList.h"

Package::Package(int _color, int _width, int _height, int _length, double _volume, int _stage){
    color = _color;
    width = _width;
    height = _height;
    length = _length;
    volumen = _volume;
    stage = _stage;
}

Package::~Package(){

}

void Package::setIsReprocessed(bool _isReprocessed){
    isReprocessed = _isReprocessed;
}

Node::Node(){
    siguiente = 0;
    anterior = 0;
}

LinkedList::LinkedList(){
    primero = 0;
    ultimo = 0;
    size = 0;
}

void LinkedList::clear(){
    Node* aux = primero;
    while(aux != 0){
        primero = primero->siguiente;
        delete aux;
        aux = primero;
    }
    size = 0;
}

void LinkedList::Insert(Package package){
    Node* nuevo = new Node();
    nuevo->package = package;
    if(primero == 0){
        primero = nuevo;
        ultimo = nuevo;
    }else{
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }
    size++;
}

int LinkedList::getSize(){
    return size;
}

String LinkedList::getColor(int i){
    Node* aux = primero;
    int j = 0;
    while(j < i){
        aux = aux->siguiente;
        j++;
    }

    switch (aux->package.color)
    {
    case 1:
        return "Red";
        break;
    case 2:

        return "Yellow";
        break;
    case 3:
        return "Blue";
        break;
    default:
        return "Error";
        break;
    }
}

double LinkedList::getMedia(){
    Node*aux = primero;
    double sum = 0;
    while(aux != 0){
        sum = sum + aux->package.volumen;
        aux = aux->siguiente;
        if (aux == primero){
            break;
        }
    }
    
    if(size == 0){
        return 0;
    }

    return sum/size;
}

void LinkedList::Sort(){
    Node* aux = primero;
    Node* aux2 = primero;
    int i = 0;
    int j = 0;
    int temp = 0;
    while(i < size){
        while(j < size){
            if(aux->package.volumen > aux2->package.volumen){
                temp = aux->package.volumen;
                aux->package.volumen = aux2->package.volumen;
                aux2->package.volumen = temp;
            }
            aux2 = aux2->siguiente;
            j++;
        }
        aux = aux->siguiente;
        i++;
    }
}

void LinkedList::Print() {
    Node*aux = primero;
    //cout<<"Color"<<" "<<"Width"<<" "<<"Height"<<" "<<"Length"<<" "<<"Volume"<< "\n";
    while (aux != NULL) {
        //cout << aux->package.color<<" "<<aux->package.width<<" "<<aux->package.height<<" "<<aux->package.length<<" "<<aux->package.volumen<< "\n";
        aux = aux->siguiente;
        if(aux == primero){
            break;
        }
    }
}


int LinkedList::getMediana(){
    Node* aux = primero;
    int i = 0;
    while(i < size/2){
        aux = aux->siguiente;
        i++;
    }
    return aux->package.volumen;
}

int LinkedList::getRed(int stage){
    Node*aux = primero;
    int i = 0;
    int count = 0;
    while(i < size){
        if(aux->package.color == 1 && aux->package.stage == stage){
            count++;
        }
        aux = aux->siguiente;
        i++;
        if(aux == primero){
            break;
        }
        
    }
    return count;
}

String LinkedList::getStageName(int stage){
    Node*aux = primero;

    int intitial_stage_count = 0;
    int reprocess_stage_count = 0;

    while(aux != 0){
        if(aux->package.stage == stage){
            if(aux->package.isReprocessed){
                reprocess_stage_count++;
                return "REP" + String(reprocess_stage_count);
            }else{
                intitial_stage_count++;
                return "INI" + String(intitial_stage_count);
            }
        }
        aux = aux->siguiente;
    }

    return "DEF";
}

int LinkedList::getYellow(int stage){
    Node*aux = primero;
    int i = 0;
    int count = 0;
    while(i < size){
        if(aux->package.color == 2 && aux->package.stage == stage){
            count++;
        }
        aux = aux->siguiente;
        i++;
        if(aux == primero){
            break;
        }
        
    }
    return count;
}

int LinkedList::getBlue(int stage){
    Node*aux = primero;
    int i = 0;
    int count = 0;
    while(i < size){
        if(aux->package.color == 3 && aux->package.stage == stage){
            count++;
        }
        aux = aux->siguiente;
        i++;
        if(aux == primero){
            break;
        }
        
    }
    return count;
}


int LinkedList::getColorVolumeMedia(int color){

    Node*aux = primero;
    int i = 0;
    int count = 0;
    int sum = 0;
    while(i < size){
        if(aux->package.color == color){
            count++;
            sum = sum + aux->package.volumen;
        }
        aux = aux->siguiente;
        i++;
        if(aux == primero){
            break;
        }
        
    }

    if(count == 0){
        return 0;
    }

    return sum/count;
}

int LinkedList::getColorVolumeMediana(int color){
    
    // Create a new list
    LinkedList* list = new LinkedList();

    // Add the packages with the color to the new list
    Node*aux = primero;
    int i = 0;
    while(i < size){
        if(aux->package.color == color){
            list->Insert(aux->package);
        }
        aux = aux->siguiente;
        i++;
        if(aux == primero){
            break;
        }
        
    }

    // Sort the new list
    list->Sort();

    // Get the mediana
    int mediana = list->getMediana();

    // Delete the new list
    delete list;

    return mediana;
}

Package LinkedList::getPackage(int i){
    Node* aux = primero;
    int j = 0;
    while(j < i){
        aux = aux->siguiente;
        j++;
    }
    return aux->package;
}