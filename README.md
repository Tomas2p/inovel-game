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

    drgybmcw

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
    #Comentario
    A.drgybmcw
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
|      #      |      Comentario       |
|      A      |       PixelArt        |
|      +      |    Avanza 1 escena    |
|     +n      |   Avanza n escenas    |
|      -      |  Retrocede 1 escena   |
|     -n      |  Retrocede n escenas  |
|      F      | Final de la historia  |

Las lineas vacias y los comentarios son ignorados, los '.' sirven para separar el texto de las abreviaturas.

### PixelArt

Para el pixelart comentado anteriormente con la opción 'A' tienes diponibles los siguientes colores en formato ANSI, si no los puedes ver quizás esa terminal no sea compatible.

| Abreviatura |      Color       |
| :---------: | :--------------: |
|      d      | negro/dark/black |
|      r      |     rojo/red     |
|      g      |   verde/green    |
|      y      | amarillo/yellow  |
|      b      |    azul/blue     |
|      m      |  magenta/purple  |
|      c      |       cyan       |
|      w      |   blanco/white   |

### Ejecución con pixelart

El cargar_el_movil.txt de esa escena es el siguiente

    E.Necesitas cargar el móvil con el cargador.
    A.wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
    A.ww                                 ww
    A.ww    ccc                          ww
    A.ww   cccccr       ggg             yww
    A.ww    c c         www        wwwwwwww
    A.wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
    +.Coger el cargador.
    -.Jugar al minecraft.

Este markdown no es compatile, pero el pixelart se ve con los colores designados, en vez de el carácter '█' en blanco.

    * La Carga del Móvil : Escena [1-3] *

    █████████████████████████████████████
    ██                                 ██
    ██    ███                          ██
    ██   ██████       ███             ███
    ██    █ █         ███        ████████
    █████████████████████████████████████

    Necesitas cargar el móvil con el cargador.

    [1] - Coger el cargador.
    [2] - Jugar al minecraft.

    Elige una opción [1-2] >>> 
