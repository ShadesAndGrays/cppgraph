#pragma once
#include <functional>
#include <raylib.h>

namespace graph{
   void drawlinear(std::function<int(int,float)> func,float dense,Color color);
   void drawGraph(float dense);
}
