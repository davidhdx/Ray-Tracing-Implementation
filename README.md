#Ray tracer
------------------
David Antonio de la Rosa Hernández
Licenciatura en Computación Matemática

**Tabla de contenidos**

[TOCM]

[TOC]


##Instrucciones para compilar
1. Descargar el archivo .zip y extraer.
2. Usar el comando "g++ -o ejecutable raytracer.cpp"
2. Usar el comando "./ejecutable"
4. Aparecera un archivo "image.ppm"
[Imágenes de apoyo](https://drive.google.com/drive/folders/12PZvwtWbqLY6aprK--m5pIVOpGP8U60b?usp=sharing "Imágenes de apoyo")

##Imagenes de renderizado y video de explicacion
[Video e imagenes](https://drive.google.com/drive/folders/1Bz-qb3doHMr8oGBgu29-cgqRoQb0A2cc?usp=sharing "Video e imagenes")

##Apartado de Caractersticas

1. Los objetos son visibles en la imagen. Pues el programa es capaz de generar los rayos primarios a partir de la camara. En adición de lo anterior se crea un archivo PPM como archivo de salida.
2. Se generan adecuadamente imágenes con cubos y mallas poligonales. El codigo es capaz de renderizar cualquier malla poligonal que se le proporcione sus puntos, el orden de los triangulos y la cantidad de los mismos. Se entrego con predeterminados para cubos, piramides triangulares e icosaedros.
3. Los objetos se ordenan adecuadamente de atrás hacia adelante.
4. Existe una función que al detectar que no hubo mas impactos con objetos retorna un valor dependiente de la posicion Y del rayo de vision. 
5. El modelo de iluminación permite la iluminacion especular (basada en la posicion de la camara) y la difuminación.
6. Las sombras funcionan correctamente.
7. Se proporciona el texto (o script) que define y dibuja (render) una escena original:
      Icosaedro (esmeralda mate) Centro en (2.5, -0.3, 2.5).
      Icosaedro (amatista) Centro en (6.5, 0.7, -7.5).
      Icosaedro (sol amarillo) Centro en (7.5, 1.7, -17.5).
      Esfera (tierra) Centro en (0, -200.17, 0), Radio en 200.
      Esfera (azul) Centro en (4, 0, -2), Radio en 0.5.
      Piramide (oro) Coordenadas en el codigo.
      Cubo (dorado) Coordenadas en el codigo.
      Esfera (plateado) Centro en (3.5, -0.75, -6), Radio en 0.7.
      Esfera (rojo) Centro en (-3.5, -1.25, -1), Radio en 0.3.
      Cubo (rubi) Coordenadas en el código.
      Cubo (plata) Coordenadas en el código.
      Piramide (enana azul) Coordenadas en el codigo.
      Esfera (foco blanco) Centro en (0, 100, 0), Radio en 80.
      Esfera (enana blanca) Centro en (0, 1, 0), Radio en 0.5.
      Esfera (sol rojo) Centro en (0, 0.4, 7), Radio en 0.1.
      Esfera (amatista mate) Centro en (3.6, 0.5, 5), Radio en 0.3.
      Esfera (esmeralda) Centro en (-0.5, 2, -4), Radio en 2.3.
10. La mejora implementada fue un antialiasing con muestreo estocastico. Adjunto fotos de "preantialiasing.ppm" y "posantialiasing.ppm" con un muestreo de 50 por pixel.

##Problemas y soluciones
A veces la normal coincidia con el rayo de vision debido al calculo del producto cruz. La solucion fue checar el producto punto y cambiar la normal a una en contra del rayo de vision.

Otro problema fue generar las mallas poligonales, primero se genero una funcion plano por medio de geometria analitica. Luego la clase de triangulo que checa si el impacto es dentro del triangulo a partir de coordenadas baricentricas. Finalmente la clase mesh que es un conjuto de objetos impactables de triangulos.

Debido al tiempo no alcance a implementar el script por LUA, sin embargo en el codigo se incluyen demasiados materiales a escoger. Además de funciones de movimiento y de ampliacion de figuras. Por lo que es amigable para el usuario.

## Enlaces de apoyo

- [Ray Tracing in One Weekend C++ Tutorial [Youtube]](https://www.youtube.com/watch?v=nQ3TRft18Qw "Ray Tracing in One Weekend C++ Tutorial [Youtube]")
- [Ray Tracing in One Weekend [Libro]](https://raytracing.github.io/books/RayTracingInOneWeekend.html "Ray Tracing in One Weekend [Libro]")
- [Geogebra](https://www.geogebra.org/classic#graphing "Geogebra")
- [Modelo de reflexión de Phong](https://es.wikipedia.org/wiki/Modelo_de_reflexi%C3%B3n_de_Phong "Modelo de reflexión de Phong")
- [How to do ray plane intersection?](https://stackoverflow.com/questions/23975555/how-to-do-ray-plane-intersection "How to do ray plane intersection?")

