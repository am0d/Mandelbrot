#include <iostream>
#include "SFML/Graphics.hpp"

#include "mandelbrot.hpp"

int main (int argc, char* argv[]) {
    sf::RenderWindow App (sf::VideoMode (1024, 768), "Mandelbrot");
    App.SetFramerateLimit (10);
    Mandelbrot mandelbrot (App);
    int numIterations = 50;
    sf::Vector2i start; // the start of the mouse selection

    while (App.IsOpened()) {
        sf::Event Event;
        while (App.GetEvent (Event)) {
            switch (Event.Type) {
                case sf::Event::Closed:
                    App.Close ();
                    break;
                case sf::Event::KeyPressed:
                    switch (Event.Key.Code) {
                        case sf::Key::Escape:
                            App.Close ();
                            break;
                        case sf::Key::R:
                            mandelbrot.Reset ();
                            mandelbrot.SetNumIterations (50);
                            numIterations = 50;
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::MouseWheelMoved:
                    numIterations += Event.MouseWheel.Delta;
                    numIterations = (numIterations < 0) ? 0 : numIterations;
                    mandelbrot.SetNumIterations (numIterations);
                    break;
                case sf::Event::MouseButtonPressed:
                    start.x = Event.MouseButton.X;
                    start.y = Event.MouseButton.Y;
                    break;
                case sf::Event::MouseButtonReleased:
                    mandelbrot.Zoom (start, sf::Vector2i (Event.MouseButton.X, Event.MouseButton.Y));
                    break;
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
