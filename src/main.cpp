#include <iostream>
#include "SFML/Graphics.hpp"

#include "mandelbrot.hpp"

int main (int argc, char* argv[]) {
    sf::RenderWindow App (sf::VideoMode (1024, 768), "Mandelbrot");
    App.SetFramerateLimit (10);
    Mandelbrot mandelbrot (App);
    int numIterations = 50;
    sf::Vector2i start, end; // the start of the mouse selection
    bool dragging = false;
    sf::Color transparent (0, 0, 0, 0);   // used for drawing the inside of the zoom rect

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
                            if (dragging)  {
                                dragging = false;
                                App.SetFramerateLimit (10);
                            }
                            else {
                                App.Close ();
                            }
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
                    end = start;
                    dragging = true;
                    App.SetFramerateLimit (30); // so that the app doesn't lag when drawing the rect
                    break;
                case sf::Event::MouseButtonReleased:
                    if (dragging) {
                        mandelbrot.Zoom (start, sf::Vector2i (Event.MouseButton.X, Event.MouseButton.Y));
                        dragging = false;
                        App.SetFramerateLimit (10);
                    }
                    break;
                case sf::Event::MouseMoved:
                    end.x = Event.MouseMove.X;
                    end.y = Event.MouseMove.Y;
                    break;
                default:
                    break;
            }
        }

       //Clear the screen
       App.Clear();

       mandelbrot.Draw();
       if (dragging) {
           App.Draw (sf::Shape::Rectangle (start.x, start.y, end.x, end.y,
                                           transparent, 1, sf::Color::Blue));
       }
       App.Display();
    }

    return 0;
}
