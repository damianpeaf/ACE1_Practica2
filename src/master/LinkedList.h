#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <Arduino.h>

class Package {
    public:
        int color, width, height, length;
        double  volumen;
        int stage;
        bool isReprocessed = false;
        Package(int,int,int,int, double, int);
        Package() = default;
        ~Package();

        void setIsReprocessed(bool);
};

class Node{
    public: 
    Package package;
    Node*siguiente;
    Node*anterior;
    Node();
};

class LinkedList{
    public:
    Node*primero;
    Node*ultimo;
    int size;

    LinkedList();
    void Insert(Package package);
    int getSize();
    String getColor(int i);
    double getMedia();
    void Sort();
    void Print();
    int getMediana();
    int getRed(int i);
    int getYellow(int i);
    int getBlue(int i);
    int getColorVolumeMediana(int color);
    int getColorVolumeMedia(int color);
    String getStageName(int i);
    Package getPackage(int i);
};


#endif