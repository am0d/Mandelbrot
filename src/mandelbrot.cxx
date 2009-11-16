#include <iostream>
#include <algorithm>
#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot (sf::RenderWindow &window) :
    myWindow (window),
    myImage (window.GetWidth(), window.GetHeight()),
    mySprite (myImage) {
        myMinReal = -2.0;
        myMaxReal = 1.2;
        myMaxImg = 1.05;
}

Mandelbrot::~Mandelbrot () {

}

void Mandelbrot::Generate (int numIterations) {
    myMinImg = myMaxImg - (myMaxReal - myMinReal) *myWindow.GetHeight()/myWindow.GetWidth();
    float deltaReal = (myMaxReal - myMinReal) / (myWindow.GetWidth() - 1);
    float deltaImg = (myMaxImg - myMinImg) / (myWindow.GetHeight() - 1);

    for (int y = 0; y < myImage.GetHeight (); y++) {
        float curImg = myMaxImg - y*deltaImg;

        for (int x = 0; x < myImage.GetWidth (); x++) {
            float curReal = myMinReal + x*deltaReal;

            // set Z = c
            float zReal = curReal;
            float zImg = curImg;

            bool isInside = true;

            int n;
            for (n = 0; n < numIterations; n++) {
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
                myImage.SetPixel (x, y, sf::Color::Black);
            }
            else {
                char factor = (char)((float) n / (float) (numIterations/2 - 1) * 255.0);
                if (n < (numIterations/2 - 1)) {
                    myImage.SetPixel (x, y, sf::Color (factor, 0, 0));
                }
                else {
                    myImage.SetPixel (x, y, sf::Color (255, factor, factor));
                }
            }
        }
    }
}

void Mandelbrot::Draw () {
    myWindow.Draw (mySprite);
}

void Mandelbrot::Zoom (sf::Vector2i topLeft, sf::Vector2i botRight) {
    float deltaReal = (myMaxReal - myMinReal) / (myWindow.GetWidth() - 1);
    float deltaImg = (myMaxImg - myMinImg) / (myWindow.GetHeight() - 1);

    float newMinReal, newMaxReal;
    float newMinImg, newMaxImg;

    newMinReal = myMinReal + std::min(topLeft.x, botRight.x)*deltaReal;
    newMaxReal = myMinReal + std::max(topLeft.x, botRight.x)*deltaReal;
    newMaxImg = myMaxImg - std::min(topLeft.y, botRight.y)*deltaImg;

    myMinReal = newMinReal;
    myMaxReal = newMaxReal;
    myMaxImg = newMaxImg;
}

void Mandelbrot::Reset () {
    myMinReal = -2.0;
    myMaxReal = 1.2;
    myMaxImg = 1.05;
}
