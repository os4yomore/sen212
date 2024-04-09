#include "renderer.hpp"

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* renderer, std::vector<Point3D>& _points, std::vector<Edge>& _edges) {
    SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
    SDL_render = renderer;
    points = _points;
    edges = _edges;
}

void Renderer3D::updateScale() {
    static double minScale = 0.5;
    static double maxScale = 1.5;
    static double step = 0.0001;
    static bool increasing = true;

    if (increasing) {
        scale += step;
        if (scale >= maxScale) {
            scale = maxScale;
            increasing = false;
        }
    } else {
        scale -= step;
        if (scale <= minScale) {
            scale = minScale;
            increasing = true;
        }
    }
}

Point3D Renderer3D::scales(Point3D point, double scaleFactor) {
    Point3D scaledPoint;
    scaledPoint.x = point.x * scaleFactor;
    scaledPoint.y = point.y * scaleFactor;
    scaledPoint.z = point.z * scaleFactor;
    return scaledPoint;
}

Point2D Renderer3D::projection(Point3D point) {
    return Point2D{ WindowSizeX / 2 + (point.x * FL) / (FL + point.z) * 100,
        WindowSizeY / 2 + (point.y * FL) / (FL + point.z) * 100 };
}

void Renderer3D::render() {
    auto time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration(0);

    SDL_SetRenderDrawColor(SDL_render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(SDL_render);
    SDL_SetRenderDrawColor(SDL_render, 255, 192, 203, SDL_ALPHA_OPAQUE);

    updateScale(); 

    for (auto& edge : edges) {
        Point3D scaledPointStart = scales(points[edge.start], scale);
        Point3D scaledPointEnd = scales(points[edge.end], scale);

        Point2D start = projection(scaledPointStart);
        Point2D end = projection(scaledPointEnd);

        SDL_RenderDrawLine(SDL_render, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(SDL_render);

    auto time2 = std::chrono::high_resolution_clock::now();
    duration = time2 - time1;
    DeltaTime = duration.count();
    time1 = time2;
}

