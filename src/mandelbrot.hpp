#include "SFML/Graphics.hpp"

class Mandelbrot {
    public:
        Mandelbrot (sf::RenderWindow &window);
        ~Mandelbrot ();
        
        void Generate (int numIterations);
        
        void Draw ();

    private:
        sf::RenderWindow &myWindow;
        sf::Image myImage;
        sf::Sprite mySprite;
};


