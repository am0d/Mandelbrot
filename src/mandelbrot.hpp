#include "SFML/Graphics.hpp"

class Mandelbrot {
    public:
        Mandelbrot (sf::RenderWindow &window);
        ~Mandelbrot ();
        
        void SetNumIterations (int numIterations);
        
        void Draw ();
        void Zoom (sf::Vector2i topLeft, sf::Vector2i botRight);
        void Reset ();

        void Generate (int startRow, int endRow);
    private:
        sf::RenderWindow &myWindow;
        sf::Image myImage;
        sf::Sprite mySprite;
        sf::String myString;

        double myMinReal;
        double myMaxReal;
        double myMinImg;
        double myMaxImg;

        bool myAmDirty;
        int myNumIterations;
};

struct GenerateParams {
    Mandelbrot *object;
    int startRow;
    int endRow;
};

