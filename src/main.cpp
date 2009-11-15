#include <iostream>
#include "SFML/Graphics.hpp"

#include "mandelbrot.hpp"

int main (int argc, char* argv[]) {
    sf::RenderWindow App (sf::VideoMode (1024, 768), "Mandelbrot");
    App.SetFramerateLimit (10);
    Mandelbrot mandelbrot (App);
    int numIterations = 1;

    mandelbrot.Generate (numIterations);

    while (App.IsOpened()) {
        sf::Event Event;
        while (App.GetEvent (Event)) {
            switch (Event.Type) {
                case sf::Event::Closed:
                    App.Close ();
                    break;
                case sf::Event::KeyPressed:
                    if (Event.Key.Code == sf::Key::Escape) {
                        App.Close ();
                    }
                    break;
                case sf::Event::MouseWheelMoved:
                    numIterations += Event.MouseWheel.Delta;
                    numIterations = (numIterations < 0) ? 0 : numIterations;
                    mandelbrot.Generate (numIterations);
                default:
                    break;
            }
        }

       //Clear the screen
       App.Clear();

       mandelbrot.Draw();
       App.Display();
    }

    return 0;
}
