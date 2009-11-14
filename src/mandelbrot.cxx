#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot (sf::RenderWindow &window) :
    myWindow (window),
    myImage (window.GetWidth(), window.GetHeight()),
    mySprite (myImage) {

}

Mandelbrot::~Mandelbrot () {

}

void Mandelbrot::Generate (int numIterations) {

    return;
}

void Mandelbrot::Draw () {
    myWindow.Draw (mySprite);
}
