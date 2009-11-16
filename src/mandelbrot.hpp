#include "SFML/Graphics.hpp"

class Mandelbrot {
    public:
        Mandelbrot (sf::RenderWindow &window);
        ~Mandelbrot ();
        
        void Generate ();
        void SetNumIterations (int numIterations);
        
        void Draw ();
        void Zoom (sf::Vector2i topLeft, sf::Vector2i botRight);
        void Reset ();

    private:
        sf::RenderWindow &myWindow;
        sf::Image myImage;
        sf::Sprite mySprite;

        double myMinReal;
        double myMaxReal;
        double myMinImg;
        double myMaxImg;

        bool myAmDirty;
        int myNumIterations;
};


