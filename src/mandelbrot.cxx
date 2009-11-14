#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot (sf::RenderWindow &window) :
    myWindow (window),
    myImage (window.GetWidth(), window.GetHeight()),
    mySprite (myImage) {

    }

Mandelbrot::~Mandelbrot () {

}

void Mandelbrot::Generate (int numIterations) {
    float minReal = -2.0;
    float maxReal = 1.0;
    float minImg = -1.2;
    float maxImg = minImg + (maxReal - minReal) *
        myWindow.GetHeight()/myWindow.GetWidth();
    float deltaReal = (maxReal - minReal) / (myWindow.GetWidth() - 1);
    float deltaImg = (maxImg - minImg) / (myWindow.GetHeight() - 1);

    for (int y = 0; y < myWindow.GetHeight (); y++) {
        float curImg = maxImg - y*deltaImg;

        for (int x = 0; x < myWindow.GetWidth (); x++) {
            float curReal = minReal + x*deltaReal;

            // set Z = c
            float zReal = curReal;
            float zImg = curImg;

            // set Z^2
            float zReal2 = zReal * zReal;
            float zImg2 = zImg2 * zImg2;
            bool isInside = true;

            for (int n = 0; n < numIterations; n++) {
                if (zReal2 + zImg2 > 4) {
                    isInside = false;
                    break;
                }

                zImg = 2*zReal*zImg + curImg;
                zReal = zReal2 - zImg2 + curReal;
            }

            if (isInside) {
                myImage.SetPixel (x, y, sf::Color::White);
            }

        }
    }
}

void Mandelbrot::Draw () {
    myWindow.Draw (mySprite);
}
