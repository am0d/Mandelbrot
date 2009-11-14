from buildit import Unix, CXX

mandelbrot = Unix('Mandelbrot')
mandelbrot.compiler = CXX()
mandelbrot.add_library(['sfml-graphics', 'sfml-window', 'sfml-system', 'GLU', 'GL'])
mandelbrot.add('src')
mandelbrot.run()
