#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include "Matriz.h"

int main() {
  /*
   * Archivo:
   * num: número de matrices
   * fila_dim columna_dim: dimensiones
   * num_entradas: número de entradas
   * fila columna valor
   * */

  /*Matrices*/
  std::vector<Matriz> matrices;

  /*Leer archivo*/
  std::ifstream input("matriz.data", std::ifstream::in);

  std::string num_matrices_line;
  std::getline(input,num_matrices_line);

  /*Extraer número de matrices*/
  unsigned int num_matrices = std::stoi(num_matrices_line);
  while (num_matrices--){
    unsigned int fila_dim, columna_dim, num_entradas;
    /*linea dimensiones*/
    std::string dim_line;
    std::getline(input, dim_line);
    std::stringstream dim_line_ss(dim_line);
    dim_line_ss >> fila_dim >> columna_dim;

    /*Crear matriz*/
    Matriz matriz(fila_dim, columna_dim);

    /*número de entradas*/
    std::string num_entradas_line;
    std::getline(input, num_entradas_line);
    std::stringstream num_entradas_ss(num_entradas_line);
    num_entradas_ss >> num_entradas;

    while (num_entradas--){
      /*entrada*/
      unsigned int fila, columna;
      int valor;
      std::string entrada_line;
      std::getline(input, entrada_line);
      std::stringstream entrada_ss(entrada_line);
      entrada_ss >> fila >> columna >> valor;
      matriz.InsertElement(fila, columna, valor);
    }
    /*imprimir matriz insertada como prueba de inserción*/
    std::cout << "Matriz " << num_matrices << std::endl;
//    matriz.Print();
    matriz.PrintAsMatriz();
    std::cout << std::endl;
    matrices.push_back(matriz);
  }

  /*Pruebas de clase*/

  /*Suma*/
  Matriz resSuma(7,7);
  resSuma = matrices[0] + matrices[2];
  std::cout << "resultado de suma de la matriz 0 con la 2" << std::endl;
  resSuma.PrintAsMatriz();
  std::cout << std::endl;

  std::cout << "resultado de suma consigo mismo" << std::endl;
  resSuma = resSuma + resSuma;
  resSuma.PrintAsMatriz();
  std::cout << std::endl;

  /*Multiplicación*/
  Matriz resMult(7,7);
  resMult = matrices[0] * matrices[2];
  std::cout << "Matriz 2" << std::endl;
  matrices[0].PrintAsMatriz();
  std::cout << "Matriz 0" << std::endl;
  matrices[2].PrintAsMatriz();
  std::cout << "resultado de multiplicación de la matriz 2 con la 0" << std::endl;
  resMult.PrintAsMatriz();
  std::cout << std::endl;

  std::cout << "resultado de multiplicación consigo mismo" << std::endl;
  resMult = resSuma * resSuma;
  resMult.PrintAsMatriz();
  std::cout << std::endl;

  /*Multiplicación por escalar*/
  Matriz resMultEsc(7,7);
  resMultEsc = 5 * matrices[0];
  std::cout << "Matriz 2" << std::endl;
  matrices[0].PrintAsMatriz();
  std::cout << "resultado de multiplicación de la matriz 2 con el número 5" << std::endl;
  resMultEsc.PrintAsMatriz();
  std::cout << std::endl;

  return 0;
}