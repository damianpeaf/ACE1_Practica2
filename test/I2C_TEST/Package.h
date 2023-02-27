#ifndef PACKAGE_H
#define PACKAGE_H



class Package {
  public:
  //constructor
  Package(int color, int widht, int height, int length);
  // public methods
  void getValues(void);

  // private variables
  private:
  int color;
  int width;
  int height;
  int length;

}

#endif