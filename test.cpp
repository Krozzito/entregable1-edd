/* Compilación: g++ -g -o img test.cpp
 * Ejecución: ./img
 *
 * Luego de la ejecución se generarán 3 imagines: imagen.png,
 * imagen_desplazada_500.png e imagen_desplazada_600.png
 */

#include "moving_image.h"
#include <iostream>
#include <windows.h> // para sleep (linux). Usar  #include<windows.h> para Windows

int main() {
  moving_image im;

  im.draw("imagen.png");
  im.rotate();
  im.draw("1.png");
  im.move_left(500);
  im.draw("2.png");
  im.move_up(500);
  im.draw("3.png");
  std::cout<<im.undoStack.size();
  im.undo();
  im.undo();
  im.undo();
  std::cout<<im.undoStack.size();
  std::cout<<im.undoStack.empty();
  im.draw("4.png");

  /* NOTA 1: Si usan el mismo nombre para las imágenes, entonces cada llamada al
  método draw() sobreescribirá a la imagen */

  /* NOTA 2: Si usan un ciclo while(1) y usan el mismo nombre de imagen,
  entonces se puede generar un efecto de desplazamiento continuo (algo así como
  un video =D ) */
  return 0;
}
