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
    
    * Título de la Historia : Escena [1-1] *

    Texto escena 1
    
     [1] - Opción 1
     [2] - Opción 2

    Elige una opción [1-2] >>> 1

    Final de la historia

    Presiona Enter para continuar...

## Plantilla de historia

Con el objetivo en mente de que las historias puedan ser creadas por otros usuarios les ofrezco la plantilla que se encuentra en stories/story_template.txt

    T.Título de la Historia

    E.Texto escena 1
    +.Opción 1
    -.Opción 2

    F.Final de la historia

Donde las cosas funcionan de la siguiente manera:

| Abreviatura |      Explicación      |
| :---------: | :-------------------: |
|      T      | Título de la historia |
|      E      |        Escena         |
|      +      |    Opción correcta    |
|      -      |   Opción incorrecta   |
|      F      | Final de la historia  |

Cualquier otro caracter que empieze la linea es ignorado, los '.' sirven para separar el texto de las abreviaturas.
