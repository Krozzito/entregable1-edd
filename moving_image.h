#ifndef MOVING_IMG_H
#define MOVING_IMG_H

#include "basics.h"
#include <stack>
#include <string>
//Clase que guarda informacion de la funcion
class FunctionSave{
  public:
    std::string function;
    int pixel;
  FunctionSave(std::string function, int pixel)
  {
    this->function = function;
    this->pixel = pixel;

  }  

};
// Clase que representa una imagen como una colección de 3 matrices siguiendo el
// esquema de colores RGB
class moving_image
{
private:
  unsigned char **red_layer;   // Capa de tonalidades rojas
  unsigned char **green_layer; // Capa de tonalidades verdes
  unsigned char **blue_layer;  // Capa de tonalidades azules

public:
  std::stack<FunctionSave*> undoStack;

  // Constructor de la imagen. Se crea una imagen por defecto

  moving_image()
  {
    // Reserva de memoria para las 3 matrices RGB
    red_layer = new unsigned char *[H_IMG];
    green_layer = new unsigned char *[H_IMG];
    blue_layer = new unsigned char *[H_IMG];

    for (int i = 0; i < H_IMG; i++)
    {
      red_layer[i] = new unsigned char[W_IMG];
      green_layer[i] = new unsigned char[W_IMG];
      blue_layer[i] = new unsigned char[W_IMG];
    }

    // Llenamos la imagen con su color de fondo
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
      {
        red_layer[i][j] = DEFAULT_R;
        green_layer[i][j] = DEFAULT_G;
        blue_layer[i][j] = DEFAULT_B;
      }

    // Dibujamos el objeto en su posición inicial
    for (int i = 0; i < 322; i++)
      for (int j = 0; j < 256; j++)
      {
        if (!s_R[i][j] && !s_G[i][j] && !s_B[i][j])
        {
          red_layer[INIT_Y + i][INIT_X + j] = DEFAULT_R;
          green_layer[INIT_Y + i][INIT_X + j] = DEFAULT_G;
          blue_layer[INIT_Y + i][INIT_X + j] = DEFAULT_B;
        }
        else
        {
          red_layer[INIT_Y + i][INIT_X + j] = s_R[i][j];
          green_layer[INIT_Y + i][INIT_X + j] = s_G[i][j];
          blue_layer[INIT_Y + i][INIT_X + j] = s_B[i][j];
        }
      }
  }

  // Destructor de la clase
  ~moving_image()
  {
    for (int i = 0; i < H_IMG; i++)
    {
      delete red_layer[i];
      delete green_layer[i];
      delete blue_layer[i];
    }

    delete red_layer;
    delete green_layer;
    delete blue_layer;
  }

  // Función utilizada para guardar la imagen en formato .png
  void draw(const char *nb)
  {
    _draw(nb);
  }

  // Función que similar desplazar la imagen, de manera circular, d pixeles a la izquierda
  void move_left(int d)
  {
    FunctionSave* currentFunction = new FunctionSave("move_left", d); // Guarda la informacion
    undoStack.push(currentFunction); // la mete al stack

    unsigned char **tmp_layer = new unsigned char *[H_IMG];
    for (int i = 0; i < H_IMG; i++)
      tmp_layer[i] = new unsigned char[W_IMG];

    // Mover la capa roja
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG-d; j++)
        tmp_layer[i][j] = red_layer[i][j + d];

    for (int i = 0; i < H_IMG; i++)
      for (int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
        tmp_layer[i][j] = red_layer[i][k];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        red_layer[i][j] = tmp_layer[i][j];

    // Mover la capa verde
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG - d; j++)
        tmp_layer[i][j] = green_layer[i][j + d];

    for (int i = 0; i < H_IMG; i++)
      for (int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
        tmp_layer[i][j] = green_layer[i][k];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        green_layer[i][j] = tmp_layer[i][j];

    // Mover la capa azul
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG - d; j++)
        tmp_layer[i][j] = blue_layer[i][j + d];

    for (int i = 0; i < H_IMG; i++)
      for (int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
        tmp_layer[i][j] = blue_layer[i][k];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        blue_layer[i][j] = tmp_layer[i][j];   
  }

  // Mover a la derecha de manera circular
  void move_right(int d)
  {
    FunctionSave* currentFunction = new FunctionSave("move_right", d);
    undoStack.push(currentFunction);
    unsigned char **tmp_layer = new unsigned char *[H_IMG];
    for (int i = 0; i < H_IMG; i++)
      tmp_layer[i] = new unsigned char[W_IMG];

    // Mover la capa roja
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG-d; j++)
        tmp_layer[i][j+d] = red_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
        tmp_layer[i][k] = red_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        red_layer[i][j] = tmp_layer[i][j];

    // Mover la capa verde
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG - d; j++)
        tmp_layer[i][j+d] = green_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
        tmp_layer[i][k] = green_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        green_layer[i][j] = tmp_layer[i][j];

    // Mover la capa azul
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG - d; j++)
        tmp_layer[i][j+d] = blue_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = W_IMG - d, k = 0; j < W_IMG; j++, k++)
        tmp_layer[i][k] = blue_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        blue_layer[i][j]=tmp_layer[i][j];
  }
  void move_up(int d)
  {
    FunctionSave* currentFunction = new FunctionSave("move_up", d);
    undoStack.push(currentFunction);
    unsigned char **tmp_layer = new unsigned char *[H_IMG];
    for (int i = 0; i < H_IMG; i++)
      tmp_layer[i] = new unsigned char[W_IMG];
  
       // Mover la capa roja
    for (int i = 0; i < H_IMG-d; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i][j] = red_layer[i+d][j];

    for (int i = H_IMG-d, k = 0; i < H_IMG; i++, k++)
      for (int j =0; j < W_IMG; j++)
        tmp_layer[i][j] = red_layer[k][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        red_layer[i][j] = tmp_layer[i][j];

    // Mover la capa verde
    for (int i = 0; i < H_IMG-d; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i][j] = green_layer[i+d][j];

    for (int k = 0, i = H_IMG - d; i < H_IMG; i++, k++)
      for (int j =0; j < W_IMG; j++)
        tmp_layer[i][j] = green_layer[k][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        green_layer[i][j] = tmp_layer[i][j];

        // Mover la capa azul
    for (int i = 0; i < H_IMG-d; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i][j] = blue_layer[i+d][j];

    for (int k = 0, i = H_IMG - d; i < H_IMG; i++, k++)
      for (int j =0; j < W_IMG; j++)
        tmp_layer[i][j] = blue_layer[k][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        blue_layer[i][j] = tmp_layer[i][j];
    
  }
  void move_down(int d)
  {
    FunctionSave* currentFunction = new FunctionSave("move_down", d);
    undoStack.push(currentFunction);
    unsigned char **tmp_layer = new unsigned char *[H_IMG];
    for (int i = 0; i < H_IMG; i++)
      tmp_layer[i] = new unsigned char[W_IMG];
  
       // Mover la capa roja
    for (int i = 0; i < H_IMG-d; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i+d][j] = red_layer[i][j];

    for (int i = H_IMG-d, k = 0; i < H_IMG; i++, k++)
      for (int j =0; j < W_IMG; j++)
        tmp_layer[k][j] = red_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        red_layer[i][j] = tmp_layer[i][j];

    // Mover la capa verde
    for (int i = 0; i < H_IMG-d; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i+d][j] = green_layer[i][j];

    for (int k = 0, i = H_IMG - d; i < H_IMG; i++, k++)
      for (int j =0; j < W_IMG; j++)
        tmp_layer[k][j] = green_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        green_layer[i][j] = tmp_layer[i][j];

        // Mover la capa azul
    for (int i = 0; i < H_IMG-d; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i+d][j] = blue_layer[i][j];

    for (int k = 0, i = H_IMG - d; i < H_IMG; i++, k++)
      for (int j =0; j < W_IMG; j++)
        tmp_layer[k][j] = blue_layer[i][j];

    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        blue_layer[i][j] = tmp_layer[i][j];
  }
  void rotate()
  {
    FunctionSave* currentFunction = new FunctionSave("rotate", 0);
    undoStack.push(currentFunction);
     unsigned char **tmp_layer = new unsigned char *[H_IMG];
    for (int i = 0; i < H_IMG; i++)
      tmp_layer[i] = new unsigned char[W_IMG];

    // Mover la capa roja
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i][j] = red_layer[j][H_IMG - i - 1];

     for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        red_layer[i][j] = tmp_layer[i][j];
    
    // Mover la capa azul
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i][j] = blue_layer[j][H_IMG - i - 1];

     for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        blue_layer[i][j] = tmp_layer[i][j];
    
    // Mover la capa roja
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[i][j] = green_layer[j][H_IMG - i - 1];

     for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        green_layer[i][j] = tmp_layer[i][j];
  }
  // Funcion para anular la rotacion
  void rerotate()
  {
     unsigned char **tmp_layer = new unsigned char *[H_IMG];
    for (int i = 0; i < H_IMG; i++)
      tmp_layer[i] = new unsigned char[W_IMG];

    // Mover la capa roja
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[j][H_IMG - i - 1] = red_layer[i][j];

     for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        red_layer[i][j] = tmp_layer[i][j];
    
    // Mover la capa azul
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[j][H_IMG - i - 1] = blue_layer[i][j];

     for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        blue_layer[i][j] = tmp_layer[i][j];
    
    // Mover la capa roja
    for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        tmp_layer[j][H_IMG - i - 1] = green_layer[i][j];

     for (int i = 0; i < H_IMG; i++)
      for (int j = 0; j < W_IMG; j++)
        green_layer[i][j] = tmp_layer[i][j];
  }
  void undo(){
    if(!undoStack.empty())
    {
      FunctionSave* tmp = undoStack.top();
      undoStack.pop();
      if(tmp->function == "rotate") // Si el movimiento es rotacion
      {
        rerotate();
      }
      if(tmp->function == "move_left") // Si el movimiento es la izquierda
      {
        move_right(tmp->pixel);
      }
      if (tmp->function == "move_right") // a la derecha
      {
      
        move_left(tmp->pixel);
      }
      if(tmp->function == "move_up") // hacia arriba
      {
        move_down(tmp->pixel);
      }
      if(tmp->function == "move_down") // hacia abajo
      {
        move_up(tmp->pixel);
      }
      delete tmp;
    }
  }

  

private:
  // Función privada que guarda la imagen en formato .png
  void _draw(const char *nb)
  {
    //    unsigned char rgb[H_IMG * W_IMG * 3], *p = rgb;
    unsigned char *rgb = new unsigned char[H_IMG * W_IMG * 3];
    unsigned char *p = rgb;
    unsigned x, y;

    // La imagen resultante tendrá el nombre dado por la variable 'nb'
    FILE *fp = fopen(nb, "wb");

    // Transformamos las 3 matrices en una arreglo unidimensional
    for (y = 0; y < H_IMG; y++)
      for (x = 0; x < W_IMG; x++)
      {
        *p++ = red_layer[y][x];   /* R */
        *p++ = green_layer[y][x]; /* G */
        *p++ = blue_layer[y][x];  /* B */
      }
    // La función svpng() transforma las 3 matrices RGB en una imagen PNG
    svpng(fp, W_IMG, H_IMG, rgb, 0);
    fclose(fp);
  }
};

#endif
