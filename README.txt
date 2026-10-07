        ============ STURM ============
          Sturmtruppen: Sky Adventure

             A game written in C++

Version:    1.0
Developer:  Luca Malucelli
Contact:    luca.malucelli@studenti.unimi.install

Copyright: open source


STURM is a program written in C++ creating the game
"Sturmtruppen: Sky Adventure", based on the italian
comic books "Sturmtruppen" by Bonvi.
The program uses OpenGl for graphical rendering and 
was developed in an Ubuntu environment.

It is developed whithout commercial purposes only
for the university exam Trattamento Numerico dei Dati 
Sperimentali at Physics Department in Milan.


        ++++++ BEFORE COMPILING ++++++

If you want to compile the game, you need the following
additional resources on your machine:

    - GLFW3 ("API for creating windows, context,
            surfaces annd events" from www.glfw.org)

    - GLAD (An OpenGL Loading Library)

On Ubuntu, you can install GLFW3 by entering the following
lines in terminal:

    sudo apt-get update
    sudo apt-get install libglfw3
    sudo apt-get install libglfw3-dev

For installing GLAD, you can go to the GLAD webservice
    https://glad.dav1d.de/
and download the proper files you need (in this case
Specification is "OpenGL", Language "C/C++" and Prifile
"Core").
After downloading the files, copy glad and KHR folders in
your include files.

Remember to modify in the right way the Makefile you
find in this folder.

===================================================

                Version info:

The program consists in modifying sprites loaded to
screen thanks to OpenGL-based classes like Texture.h
and Sprite.h. 
Operations are made on these sprites' attributes (position,
rotation, scaling) and updated in the game while cicle.
The game state (start, gameplay or gameover) is regulated
by the GameManager.h class, which operates initializing
the game instances and controlling their behavious in
the main rendering while cicle.

The results (number of flyed meters) are to find in the 
terminal. Text rendering was not implemented in this version.

===================================================

A compiled version (executable) is in this folder.
You can launch it from terminal by typing

    ./STURM

Thanks for your attention.

                Have fun!