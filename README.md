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

Con el objetivo en mente de que las historias puedan ser creadas por otros usuarios les ofrezco la plantilla que se encuentra en stories/template/story_template.txt y su pixelart se encontraría en stories/template/story_template.art:

    T.Título de la Historia

    E.Texto escena 1
    #Comentario
    A.Escena1
    +.Avanza 1 escena
    -.Retrocede 1 escena
    +2.Avanza 2 escenas
    -2.Retrocede 2 escenas

    F.Final de la historia

Y este sería el archivo del pixelart:

    #PixelArt de la historia

    A.Escena1
    adwdfsdd
    qwdqwdqw
    dqwdwddw

    A.Escena2

Donde las cosas funcionan de la siguiente manera:

|                                 .txt|       .art|
| Abreviatura |      Explicación      | Abreviatura |     Explicación     |
| :---------: | :-------------------: | :---------: | :-----------------: |
|      T      | Título de la historia |      #      |     Comentarios     |
|      E      |        Escena         |      A      | nombre del pixelart |
|      #      |      Comentario       |
|      A      |  Titulo del pixelart  |
|      +      |    Avanza 1 escena    |
|     +n      |   Avanza n escenas    |
|      -      |  Retrocede 1 escena   |
|     -n      |  Retrocede n escenas  |
|      F      | Final de la historia  |

Las lineas vacias y los comentarios son ignorados, los '.' sirven para separar el texto de las abreviaturas.

### PixelArt NO FUNCIONAL

Actualmente no funcionan los colores.

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

El cargar_el_movil.txt de esa escena es el siguiente:

    E.Necesitas cargar el móvil con el cargador.
    A.Escena1
    +.Coger el cargador.
    -.Jugar al minecraft.

El cargar_el_movil.art de esa escena es:

    A.Escena1
    wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
    ww                                 ww
    ww    ccc                          ww
    ww   cccccr       ggg             yww
    ww    c c         www        wwwwwwww
    wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

Y se vería lo siguiente:

    * La Carga del Móvil : Escena [1-3] *

     wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
     ww                                 ww
     ww    ccc                          ww
     ww   cccccr       ggg             yww
     ww    c c         www        wwwwwwww
     wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

    Necesitas cargar el móvil con el cargador.
     [1] - Coger el cargador.
     [2] - Jugar al minecraft.
    Elige una opción [1-2] >>> 
