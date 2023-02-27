#ifndef PACKAGE_H
#define PACKAGE_H

#include "Arduino.h"


class Package {
  public:
  //constructor
  Package(int color, int width, int height, int length);
  Package(int color, int width, int height, int length, bool isReprocessed);
  Package();

  // public methods
  void getValues(void);

  // private variables
  private:
  int color;
  int width;
  int height;
  int length;
  bool isReprocessed;

};

#endif