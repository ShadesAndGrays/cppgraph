#include "graph.hpp"
#include <raylib.h>

#ifndef DENSISTY
#define DENSITY 200
#endif

void graph::drawlinear(std::function<int(int,float)> func,float dense,Color color){
    for(int i = 0; i < dense;i ++){
        int x = i;
        int y = func(x,dense);
        DrawPixel(x, y,color);
    }
}

void graph::drawGraph(float dense){
    for(int i = 0; i < dense ;i++){
        DrawPixel(i, 0, WHITE);
        DrawPixel(0, i, WHITE);
        DrawPixel(i, dense-1, GRAY);
        DrawPixel(dense, i, GRAY);
        for (int j = 0; j< 5 ;j++){
            DrawPixel(i, j * dense/5, GRAY);
            DrawPixel(j * dense/5, i, GRAY);
        }
    }

}

