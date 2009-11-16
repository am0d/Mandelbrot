#include "SFML/Graphics.hpp"

class Mandelbrot {
    public:
        Mandelbrot (sf::RenderWindow &window);
        ~Mandelbrot ();
        
        void Generate (int numIterations);
        
        void Draw ();
        void Zoom (sf::Vector2i topLeft, sf::Vector2i botRight);
        void Reset ();

    private:
        sf::RenderWindow &myWindow;
        sf::Image myImage;
        sf::Sprite mySprite;

        float myMinReal;
        float myMaxReal;
        float myMinImg;
        float myMaxImg;
};


