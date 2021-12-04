//
// Created by andre on 12/3/21.
//

#include <iostream>
#include <algorithm>
#include "Matriz.h"

Matriz::Matriz(unsigned int fila_dim, unsigned int columna_dim) : _fila_dim(fila_dim), _columna_dim(columna_dim) {}

/*
 * Imprime los valores
 * */
void Matriz::Print() {
  for (auto const &column: this->_matriz) {
    std::cout << "[fila: " << column.first << "{";
    for (auto const &fila: column.second) {
      std::cout << " (columna: " << fila.first << " valor: " << fila.second << "),";
    }
    std::cout << "}]" << std::endl;
  }
}

/*
 * Imprime valores como matriz
 * */
void Matriz::PrintAsMatriz() {
  /*Multiplicación*/
  for (int rowIndex = 0; rowIndex < this->_fila_dim; ++rowIndex) {
    for (int columnIndex = 0; columnIndex < this->_columna_dim; ++columnIndex) {
      std::cout << GetValue(rowIndex, columnIndex) << ", ";
    }
    std::cout << std::endl;
  }
}

/*
 * Inserta un elemento con su fila, columna y valor,
 * si existe solo lo reescribe, si no existe entonces
 * lo inserta
 * */
void Matriz::InsertElement(unsigned int fila, unsigned int columna, int valor) {

  /*Si los valores no están en donde deben estar entonces no se inserta*/
  if (!(0 <= fila < this->_fila_dim && 0 <= columna < this->_columna_dim && valor != 0))
    return;

  /*Buscar fila*/
  auto matrizIter = std::find_if(this->_matriz.begin(), this->_matriz.end(),
   [&fila](const std::pair<unsigned int, std::list<std::pair<unsigned int, int>>> &el) {
     if (el.first == fila) {
       return true;
     } else {
       return false;
     }
   });

  /*Si no está la fila*/
  if (matrizIter == this->_matriz.end()) {
    /*Si está vacio insertar así nomás*/
    if (this->_matriz.empty()) {
      std::list<std::pair<unsigned int, int>> lista_fila;
      lista_fila.emplace_back(columna, valor);
      this->_matriz.emplace_back(fila, lista_fila);
    } else {
      /*Si no está vacio entonces buscar después de que fila va*/
      auto matrizIterFila = this->_matriz.begin();

      /*Buscamos el apuntador donde la fila sea menor al siguiente*/
      while (matrizIterFila != this->_matriz.end()) {
        if (matrizIterFila->first < fila)
          ++matrizIterFila;
        else
          break;
      }

      /*Insertamos la fila*/
      std::list<std::pair<unsigned int, int>> lista_fila;
      lista_fila.emplace_back(columna, valor);
      std::pair<unsigned int, std::list<std::pair<unsigned int, int>>> fila_pair;
      fila_pair.first = fila;
      fila_pair.second = lista_fila;
      this->_matriz.insert(matrizIterFila, fila_pair);
    }
  } else {
    /*Si está la fila entonces solo hay que acomodar en la columna o reescribir el valor*/

    /*Buscamos el apuntador donde la columna sea menor al siguiente*/
    auto listaFilaIter = matrizIter->second.begin();
    while (listaFilaIter != matrizIter->second.end()) {
      if (listaFilaIter->first < columna)
        ++listaFilaIter;
      else
        break;
    }

    /*Si es igual entonces solo cambiar el valor*/

    if (listaFilaIter->first == columna) {
      listaFilaIter->second = valor;
      return;
    }

    /*Si no es igual entonces hay que insertar el valor*/
    std::pair<int, int> lista_fila_valor;
    lista_fila_valor.first = (int) columna;
    lista_fila_valor.second = valor;
    matrizIter->second.insert(listaFilaIter, lista_fila_valor);
  }
}

/*Busca un elemento y regresa su valor, si no está entonces regresa 0
 * esto es necesario para la multiplicación
 * */
  int Matriz::GetValue(unsigned int fila, unsigned int columna) const {
    int result = 0;
    /*Si los valores no están en donde deben estar entonces es un error de uso de la función*/
    if (!(0 <= fila < this->_fila_dim && 0 <= columna < this->_columna_dim))
      throw std::runtime_error("no existe tal fila o columna");

    /*Buscar fila*/
    auto matrizIter = std::find_if(this->_matriz.begin(), this->_matriz.end(),
     [&fila](const std::pair<unsigned int, std::list<std::pair<unsigned int, int>>> &el) {
       if (el.first == fila) {
         return true;
       } else {
         return false;
       }
     });

    if (matrizIter != this->_matriz.end()) {
      /*Buscar columna si se encontró la fila*/
      auto ColumnaIter = std::find_if(matrizIter->second.begin(), matrizIter->second.end(),
      [&columna](const std::pair<unsigned int, int> &el) {
       if (el.first == columna) {
         return true;
       } else {
         return false;
       }
      });
      /*Regresar valor si se encontró la fila*/
      if(ColumnaIter != matrizIter->second.end()){
        result = ColumnaIter->second;
      }
    }

    return result;
  }

/*
 * Suma de una matriz con otra
 * */
Matriz operator+(const Matriz &matriz1, const Matriz &matriz2) {

  /*Si las dimensiones no concuerdan entonces es un error*/
  if (!(matriz1._fila_dim == matriz2._fila_dim && matriz1._columna_dim == matriz2._columna_dim)) {
    throw std::runtime_error("No se pueden sumar matrices con dimensiones diferentes");
  }

  Matriz resultado(matriz1._fila_dim, matriz1._columna_dim);

  /*Suma*/

  /*Iteradores de las listas de filas*/
  auto matrix1It = matriz1._matriz.begin();
  auto matrix2It = matriz2._matriz.begin();

  while (true) {

    /* Si ya llegamos al final de la matriz 1 y faltan elementos en la matriz 2
     * entonces copiar los elementos restantes de la matriz 2
     * */
    if (matrix1It == matriz1._matriz.end() && matrix2It != matriz2._matriz.end()) {
      while (matrix2It != matriz2._matriz.end()) {
        resultado._matriz.push_back(*matrix2It++);
      }
      break;
      /* Si ya llegamos al final de la matriz 2 y faltan elementos en la matriz 1
       * entonces copiar los elementos restantes de la matriz 1
       * */
    } else if (matrix1It != matriz1._matriz.end() && matrix2It == matriz2._matriz.end()) {
      while (matrix1It != matriz1._matriz.end()) {
        resultado._matriz.push_back(*matrix1It++);
      }
      break;
      /* Si ya llegamos al final de ambos entonces damos por terminado todo
       * */
    } else if (matrix1It == matriz1._matriz.end() && matrix2It == matriz2._matriz.end()) {
      break;
      /*Si ninguno a llegado al final entonces ir avanzando*/
    } else {
      /*Alcanzar a la fila con mayor valor*/
      if (matrix1It->first < matrix2It->first) {
        resultado._matriz.push_back(*matrix1It++);
        continue;
      } else if (matrix1It->first > matrix2It->first) {
        resultado._matriz.push_back(*matrix2It++);
        continue;
      } else {
        /*Suma en lista de filas*/
        auto fila1 = matrix1It->second.begin();
        auto fila2 = matrix2It->second.begin();

        std::list<std::pair<unsigned int, int>> filaresult;
        while (true) {
          /*Si una fila acabó entonces hay que copiar las demás restantes*/
          if (fila1 == matrix1It->second.end() && fila2 != matrix2It->second.end()) {
            while (fila2 != matrix2It->second.end()) {
              filaresult.push_back(*fila2++);
            }
            break;
          } else if (fila2 == matrix2It->second.end() && fila1 != matrix1It->second.end()) {
            while (fila1 != matrix1It->second.end()) {
              filaresult.push_back(*fila1++);
            }
            break;
          } else if (fila2 == matrix2It->second.end() && fila1 == matrix1It->second.end()) {
            break;
          } else {
            if (fila1->first < fila2->first) {
              filaresult.push_back(*fila1++);
              continue;
            } else if (fila1->first > fila2->first) {
              filaresult.push_back(*fila2++);
              continue;
            } else {
              int sum = fila1->second + fila2->second;
              filaresult.emplace_back(fila1->first, sum);
              ++fila1, ++fila2;
            }
          }
        }

        resultado._matriz.emplace_back(matrix1It->first, filaresult);

        ++matrix1It, ++matrix2It;
      }
    }
  }

  return resultado;
}

/*
 * Producto entre matrices dispersas
 * */
Matriz operator*(const Matriz &matriz1, const Matriz &matriz2) {
  /*Si las dimensiones no concuerdan entonces es un error*/
  if (matriz1._columna_dim != matriz2._fila_dim) {
    throw std::runtime_error("No se pueden sumar matrices con dimensiones diferentes");
  }

  Matriz resultado(matriz1._fila_dim, matriz2._columna_dim);

  /*Multiplicación*/
  for (int rowIndex = 0; rowIndex < resultado._fila_dim; ++rowIndex) {
    for (int columnIndex = 0; columnIndex < resultado._columna_dim; ++columnIndex) {
      int sum = 0;
      for (int rowcolumnIndex = 0; rowcolumnIndex < matriz1._columna_dim; ++rowcolumnIndex) {
        int a = matriz1.GetValue(rowIndex, rowcolumnIndex);
        int b = matriz2.GetValue(rowcolumnIndex, columnIndex);
        sum += a*b;
      }
      if(sum != 0){
        resultado.InsertElement(rowIndex, columnIndex, sum);
      }
    }
  }

  return resultado;
}

/*
 * Producto entre un escalar y una matriz
 * */
Matriz operator*(const int &value, const Matriz &matriz) {

  Matriz resultado(matriz);

  /*Multiplicación escalar*/
  for (auto &resFila: resultado._matriz) {
    for (auto &resColuma: resFila.second) {
      resColuma.second *= value;
    }
  }

  return resultado;
}
