Mandelbrot
----------

This is just a simple Mandelbrot viewer, written in c++ using an SFML front-end.
I wrote it just to get practice with SFML, and to test out another bit build script.

To compile, first download bit from http://github.com/sahchandler/bit/downloads.
Then, run
    bit
in the current directory.

Controls:
    ESC - quits the program
    R   - resets the zoom and iteration levels
    Click and drag
        - zoom in on a section of the mandelbrot
        - to cancel the zoom, press ESC before releasing the mouse button
    Middle scroll wheel
        - increase / decrease the number of iterations

This code is released under the LGPL license.
If you modify and release it, you must make your modifications
publically available.
However, you may link this code (as is) without your code being forced under
the LGPL.
