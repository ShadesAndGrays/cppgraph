#include <raylib.h>
#include <raymath.h>
#include <string>

#include "graph/graph.hpp"

#define DENSITY 200


Rectangle calculateScale(RenderTexture2D texture);

int main() {

    InitWindow(800, 800, "Grapher");

    // x = 10
    std::function<int(int,float)> eq = 
        [](int x ,float dense){ 

            return 10;
        };
    // y = x
    std::function<int(int,float)> eq1 = 
        [](int x ,float dense){ 
            return x;
        };

    // 2y = x + 10
    std::function<int(int,float)> eq2 = 
        [](int x ,float dense){ 
            return x*0.5+5;
        };

    RenderTexture2D graphText = LoadRenderTexture(DENSITY +1,DENSITY+1);

    SetWindowState(FLAG_WINDOW_RESIZABLE);


    while (!WindowShouldClose()) {

        BeginTextureMode(graphText);

        ClearBackground(RAYWHITE);

        graph::drawGraph(DENSITY);

        // Lines between two points
        DrawLineV(Vector2{0,30},Vector2{75,0}, RED);

        DrawLineV(Vector2{0,100},Vector2{20,0}, GREEN);

        DrawLineV(Vector2{0,60},Vector2{37.5,0}, BLUE);

        // This is where the magic happens >:)
        graph::drawlinear(eq,DENSITY, RED);
        graph::drawlinear(eq1,DENSITY, YELLOW);
        graph::drawlinear(eq2,DENSITY, VIOLET);


        EndTextureMode();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Rectangle port =  calculateScale(graphText);

        DrawTexturePro(
                graphText.texture,
                Rectangle{
                0.0,
                0.0,
                (float) graphText.texture.width,
                (float)graphText.texture.height
                },
                port,
                Vector2Zero(),0,WHITE);

        auto pos = GetMousePosition();

        // convoluted conversion from world space to graph space
        const std::string str =(
                std::to_string(static_cast<int>((pos.x-port.x)/port.width *DENSITY))
                +","
                +std::to_string(static_cast<int>(DENSITY-(pos.y-port.y)/port.height *DENSITY))

                );


        const char* coords = str.c_str();
        DrawRectangleRec(Rectangle {10,20,GetFontDefault().recs->width*str.length()*14,GetFontDefault().recs->height*7}, BLACK);
        DrawText(coords,20,20,70,YELLOW);
        EndDrawing();
    }
}



// Scales up and centers the texture to the midle of the screen
Rectangle calculateScale(RenderTexture2D texture){
    float unit;
    float screen;
    float scaleFactor;
    if (GetScreenWidth() <  GetScreenHeight()){

        unit = texture.texture.width;
        screen = GetScreenWidth();
    }
    else {
        unit = texture.texture.width;
        screen = GetScreenHeight();
    }
    scaleFactor = screen/unit;
    float x = GetScreenWidth()/2.0 - texture.texture.width/2.0 * scaleFactor ;
    float y = GetScreenHeight()/2.0 - texture.texture.height/2.0 * scaleFactor;
    return Rectangle{x,y,texture.texture.width * scaleFactor, texture.texture.height * scaleFactor};
}
