#include <iostream>
#include <algorithm>
#include <sstream>
#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot (sf::RenderWindow &window) :
    myWindow (window),
    myImage (window.GetWidth(), window.GetHeight()),
    mySprite (myImage),
    myString ("Iterations: 50") {
        myMinReal = -2.0;
        myMaxReal = 1.2;
        myMaxImg = 1.05;
        myNumIterations = 50;
        myAmDirty = true;
        myString.SetPosition (10, 10);
        myString.SetColor (sf::Color::Blue);
}

Mandelbrot::~Mandelbrot () {

}

void Mandelbrot::Generate (int startRow, int endRow) {
    myMinImg = myMaxImg - (myMaxReal - myMinReal) * myWindow.GetHeight()/myWindow.GetWidth();
    double deltaReal = (myMaxReal - myMinReal) / (myWindow.GetWidth() - 1);
    double deltaImg = (myMaxImg - myMinImg) / (myWindow.GetHeight() - 1);

    for (int y = startRow; y < endRow; y++) {
        double curImg = myMaxImg - y*deltaImg;

        for (int x = 0; x < myImage.GetWidth (); x++) {
            double curReal = myMinReal + x*deltaReal;

            // set Z = c
            double zReal = curReal;
            double zImg = curImg;

            bool isInside = true;

            int n;
            for (n = 0; n < myNumIterations; n++) {
                // set Z^2
                double zReal2 = zReal * zReal;
                double zImg2 = zImg * zImg;
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
                char factor = (char)((double) n / (double) (myNumIterations/2 - 1) * 255.0);
                if (n < (myNumIterations/2 - 1)) {
                    myImage.SetPixel (x, y, sf::Color (factor, 0, 0));
                }
                else {
                    myImage.SetPixel (x, y, sf::Color (255, factor, factor));
                }
            }
        }
    }
}

void generateThread (void *data) {
    GenerateParams* params = static_cast<GenerateParams *>(data);
    (params->object)->Generate (params->startRow, params->endRow);
}

void Mandelbrot::Draw () {
    if (myAmDirty) {
        // generate the 'bot
        GenerateParams topParams, botParams;
        topParams.object = this;
        topParams.startRow = 0;
        topParams.endRow = myImage.GetHeight () / 2;
        sf::Thread topThread(&generateThread, (void *)&topParams);
        topThread.Launch ();
        botParams.object = this;
        botParams.startRow = topParams.endRow;
        botParams.endRow = myImage.GetHeight ();
        sf::Thread botThread (&generateThread, (void *)&botParams);
        botThread.Launch();
        topThread.Wait ();
        botThread.Wait ();
        myAmDirty = false;
    }
    myWindow.Draw (mySprite);
    myWindow.Draw (myString);
}

void Mandelbrot::Zoom (sf::Vector2i topLeft, sf::Vector2i botRight) {
    double deltaReal = (myMaxReal - myMinReal) / (myWindow.GetWidth() - 1);
    double deltaImg = (myMaxImg - myMinImg) / (myWindow.GetHeight() - 1);

    double newMinReal, newMaxReal;
    double newMinImg, newMaxImg;

    newMinReal = myMinReal + std::min(topLeft.x, botRight.x)*deltaReal;
    newMaxReal = myMinReal + std::max(topLeft.x, botRight.x)*deltaReal;
    newMaxImg = myMaxImg - std::min(topLeft.y, botRight.y)*deltaImg;

    myMinReal = newMinReal;
    myMaxReal = newMaxReal;
    myMaxImg = newMaxImg;
    myAmDirty = true;
}

void Mandelbrot::Reset () {
    myMinReal = -2.0;
    myMaxReal = 1.2;
    myMaxImg = 1.05;
    myAmDirty = true;
}

void Mandelbrot::SetNumIterations (int numIterations) {
    myNumIterations = numIterations;
    myAmDirty = true;

    // draw text on screen
    std::ostringstream text;
    text << "Iterations: ";
    text << myNumIterations;
    myString.SetText (sf::Unicode::Text (text.str ()));
}
