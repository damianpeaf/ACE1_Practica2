
using namespace std;

class Package {
    
    public:
        int color, width, height, length, volumen;
        Package(int,int,int,int, int);
        Package() = default;
        ~Package();
};

Package::Package(int _color, int _width, int _height, int _length, int _volume){
    color = _color;
    width = _width;
    height = _height;
    length = _length;
    volumen = _volume;
}

Package::~Package(){

}

class Node{
    public:	
    Package package;
    Node*siguiente;
    Node*anterior;
    Node() {
        siguiente = 0;
        anterior = 0;
    }
};

class LinkedList{
    public:
    Node*primero;
    Node*ultimo;
    int size;

    LinkedList(){
        primero = 0;
        ultimo = 0;
        size = 0;
    }

    void Insert(Package package);
    int getSize();
    int getColor(int i);
    double getMedia();
    void Sort();
    void Print();
    int getMediana();
};

void ::LinkedList::Insert(Package package){
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

int ::LinkedList::getSize(){
    return size;
}

int ::LinkedList::getColor(int i){
    Node* aux = primero;
    int j = 0;
    while(j < i){
        aux = aux->siguiente;
        j++;
    }
    return aux->package.color;
}

double ::LinkedList::getMedia(){
    Node*aux = primero;
    double sum = 0;
    while(aux != 0){
        sum = sum + aux->package.volumen;
        aux = aux->siguiente;
        if (aux == primero){
            break;
        }
    }
    return sum/size;
}

void :: LinkedList::Sort(){
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
    cout<<"Color"<<" "<<"Width"<<" "<<"Height"<<" "<<"Length"<<" "<<"Volume"<< "\n";
    while (aux != NULL) {
        cout << aux->package.color<<" "<<aux->package.width<<" "<<aux->package.height<<" "<<aux->package.length<<" "<<aux->package.volumen<< "\n";
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