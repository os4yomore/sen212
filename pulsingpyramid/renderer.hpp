#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

struct Point2D { float x; float y; };
struct Point3D { float x; float y; float z; };
struct Edge { int start; int end; };

class Renderer3D {
public:
    Renderer3D(SDL_Window* _window, SDL_Renderer* renderer, std::vector<Point3D>& _points, std::vector<Edge>& _edges);
    void render();
    void updateScale();
    Point3D scales(Point3D point, double scaleFactor);
    Point2D projection(Point3D point);

private:
    float FL = 5;
    double scale = 1.0; // Initial scale value
    int WindowSizeX;
    int WindowSizeY;
    float DeltaTime = 0;
    SDL_Renderer* SDL_render;
    std::vector<Point3D> points;
    std::vector<Edge> edges;
};

