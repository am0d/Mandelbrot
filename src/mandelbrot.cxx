#include <iostream>
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
    float maxReal = 1.2;
    float minImg = -1.2;
    float maxImg = minImg + (maxReal - minReal) *
        myWindow.GetHeight()/myWindow.GetWidth();
    float deltaReal = (maxReal - minReal) / (myWindow.GetWidth() - 1);
    float deltaImg = (maxImg - minImg) / (myWindow.GetHeight() - 1);

    std::cout << minReal << " " << maxReal << " " << deltaReal << std::endl;
    std::cout << minImg << " " << maxImg << " " << deltaImg << std::endl;

    for (int y = 0; y < myImage.GetHeight (); y++) {
        float curImg = maxImg - y*deltaImg;

        for (int x = 0; x < myImage.GetWidth (); x++) {
            float curReal = minReal + x*deltaReal;

            // set Z = c
            float zReal = curReal;
            float zImg = curImg;

            bool isInside = true;

            for (int n = 0; n < numIterations; n++) {
                // set Z^2
                float zReal2 = zReal * zReal;
                float zImg2 = zImg * zImg;
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
