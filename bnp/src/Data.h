#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <stdio.h>

class Data
{
   private:

      int bin_capacity;
      int n_items;
      std::vector<int> weights;

   public:

      void readData(char* filePath);

      int getNItems();

      int getBinCapacity();

      int getItemWeight(unsigned int item);

      std::vector<int> getWeights();
};

#endif

