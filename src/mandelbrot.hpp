#include "SFML/Graphics.hpp"

struct GenerateParams {
    int startRow;
    int endRow;
};

class Mandelbrot {
    public:
        Mandelbrot (sf::RenderWindow &window);
        ~Mandelbrot ();
        
        void SetNumIterations (int numIterations);
        
        void Draw ();
        void Zoom (sf::Vector2i topLeft, sf::Vector2i botRight);
        void Reset ();

    private:
        void Generate (GenerateParams params);

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


