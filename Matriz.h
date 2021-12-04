//
// Created by andre on 12/3/21.
//

#ifndef MATRIZDISPERSAPROYECTO__MATRIZ_H_
#define MATRIZDISPERSAPROYECTO__MATRIZ_H_

#include <utility>
#include <list>

class Matriz {
  unsigned int _fila_dim, _columna_dim;
  std::list<std::pair<unsigned int,std::list<std::pair<unsigned int,int>>>> _matriz;
  int GetValue(unsigned int fila, unsigned int columna) const;
 public:
  Matriz(unsigned int fila_dim, unsigned int columna_dim);
  void Print();
  void PrintAsMatriz();
  void InsertElement(unsigned int fila, unsigned int columna, int valor);
  friend Matriz operator+(Matriz const &matriz1, Matriz const &matriz2);
  friend Matriz operator*(Matriz const &matriz1, Matriz const &matriz2);
  friend Matriz operator*(int const &value, Matriz const &matriz);
};

#endif //MATRIZDISPERSAPROYECTO__MATRIZ_H_
