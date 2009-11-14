#include "SFML/Graphics.hpp"

#include "mandelbrot.hpp"

int main (int argc, char* argv[]) {
    sf::RenderWindow App (sf::VideoMode (640, 480), "Mandelbrot");
    Mandelbrot mandelbrot (App);

    mandelbrot.Generate (1);

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
