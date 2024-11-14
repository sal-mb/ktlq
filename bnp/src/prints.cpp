
#include <iostream>
#include <vector>

using std::cout, std::endl;

void printColumns(std::vector<std::vector<bool>> columns){
  cout << "\ncolumns:" << endl;
  for(auto row : columns){
    for(auto j : row){
      cout << j << " ";
    }
    cout << endl;;
  }
}

void printZ_ij(std::vector<std::vector<double>> z_ij){
  cout << "\nz_ij:" << endl;
  for(auto row : z_ij){
    for(auto j : row){
      cout << j << " ";
    }
    cout << endl;;
  }
}

void printVector(std::vector<int> vector){
  for(auto i : vector){
    cout << i << " ";
  }
    cout << endl;;
}

void printVector(std::vector<double> vector){
  for(auto i : vector){
    cout << i << " ";
  }
    cout << endl;;
}

void printItems(std::vector<std::pair<int,int>> items){
  cout << "items: " << endl;
  for(auto i : items){
    cout << i.first << ", " << i.second << " / ";
  }
  cout << endl;
}

void printSepJoin(std::vector<bool> sep_join){
  cout << "sep_join: " << endl;
  for(auto k : sep_join){
    cout << k << " / ";
  }
  cout << endl;
}
