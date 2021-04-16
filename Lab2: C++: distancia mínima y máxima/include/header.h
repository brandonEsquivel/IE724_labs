/** 
 * @author Brandon Esquivel Molina
 * @date setiembre 2020
 * @warning UCR EIE
 * @mainpage Predictores de salto: implementacion y prueba en C++
 * @brief Implementacion del proyecto propuesto en la tarea 1 del curso IE0521 Estructuras de computadoras digitales II.
 * @section intro_sec Introduccion
 * En el presente codigo se muestra la solucion implementada de la tarea 1 del curso IE0521 Estructuras de computadoras digitales II, de la escuela de Ingenieria Electrica , EIE, UCR.
 * Se implementa en C++, un algoritmo de simulacion y prueba para predictores dinamicos, con historia globa, privada y por torneo. Se utiliza un archivo trace con formato PC - T/N para usar en el testbench.
 * Se utilizo memoria dinamica para optimizar el programa. El predictor Tournament, a diferencia de los otros 3 contiene su logica interna, llamando a los otros, mientras que los oros se consideran secuenciales, es decir son manejados desde fuera, en el codigo main.
 * 
 * @section compile_sec Compilacion
 * Ejecute el comando make all en la carpeta raiz (Tarea1) para realizar todo el proceso completo y compilar con parametros de prueba.
 * Para correr el ejecutable ejecute make run o bien ./bin/exe -s < # > -bp < # > -gh < # > -ph < # > -o < # > con sus parametros.
 * Para compilar ejecute make COMPILAR, Para extraer ejecute make unzip
 * 
 * @section doc_sec Documentacion
 * Ejecute make doc para generar la documentacion en formato latex pdf y HTML
 * 
 * @section clean_sec Limpieza
 * ejecute make clean para limpiar archivos de produccion.
 * 
 * **/ 



//INCLUDES
#pragma once

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string.h>