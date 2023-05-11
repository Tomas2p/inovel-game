# INovel++ - Juego de novela interactivo por terminal en C++

Juego de novela interactiva por terminal implementado en C++ y haciendo uso de txt para la creación de historias.

## Constructor

Requisitos: `make` y `g++`

    $ make
    rm -f story
    g++ -std=c++17 -Wall -o  story src/story.cpp src/main.cpp

## Ejemplo de ejecución

    $ ./story stories
    * INovel++ novela interactiva *

    Hay 1 historias disponibles en stories/:
    
     [1] - story_template

    Seleccione la historia a jugar >>> 1
    
    * La Carga del Móvil : Escena [1-3] *

    Necesitas cargar el móvil con el cargador.
    
     [1] - Coger el cargador de tu cuarto.
     [2] - Jugar al minecraft.

    Elige una opción [1-2] >>> 1

    Gracias a alguien tu móvil no ha explotado o si.

    Presiona Enter para continuar...

## Plantilla de historia

Con el objetivo en mente de que las historias puedan ser creadas por otros usuarios les ofrezco la plantilla que se encuentra en stories/story_template.txt

    T.Título de la Historia

    E.Texto escena 1
    +.Avanza 1 escena
    -.Retrocede 1 escena
    +2.Avanza 2 escenas
    -2.Retrocede 2 escenas

    F.Final de la historia

Donde las cosas funcionan de la siguiente manera:

| Abreviatura |      Explicación      |
| :---------: | :-------------------: |
|      T      | Título de la historia |
|      E      |        Escena         |
|      +      |    Avanza 1 escena    |
|     +n      |   Avanza n escenas    |
|      -      |  Retrocede 1 escena   |
|     -n      |  Retrocede n escenas  |
|      F      | Final de la historia  |

Cualquier otro caracter que empieze la linea es ignorado, los '.' sirven para separar el texto de las abreviaturas.
