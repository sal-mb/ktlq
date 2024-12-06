#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <vector>

class Data {
private:
  int bin_capacity;
  int n_items;
  std::vector<int> weights;

public:
  void readData(char *filePath);

  void printData();
  int getNItems();

  int getBinCapacity();

  int getItemWeight(unsigned int item);

  const std::vector<int>& getWeights();
};

#endif
