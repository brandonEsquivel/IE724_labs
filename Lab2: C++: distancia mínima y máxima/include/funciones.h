#pragma once
#include "header.h"

using namespace std;

/** @brief Implementacion de  funciones varias para predictores

    Implementa las funciones de los contadores/predictores branch history table(BHT) y Branch target buffer (BTB)
    @author Brandon ESquivel
    @date Setiembre 2020
    */

    /** Funcion abrirArchivo abre un archivo tipo trace y lee la primer linea en formato PC - T/N
     * @param nombre string nombre del archivo a abrir
     * @param PC referencia a string Donde se guardara el PC leido
     * @param outcome referencia a string donde se guardara el outcome leido(T/N)
     * @return Puntero FILE del archivo abierto para continuar manipulando/leyendo*/
    FILE* abrirArchivo(char nombre[], string &PC, string &outcome);

    /** Accede a una direccion de la BHT y devuelve la prediccion correspondiente
     * @param dir Direccion/entrada PC a buscar en la BHT
     * @param BHT referencia a una BHT creada.
     * @return string pred con la prediccion correspondiente de la BHT */
    string prediccion(int addr, vector<string> &BHT);


    /** Accede a una direccion de la BHT y devuelve la prediccion correspondiente
     * @param dir Direccion/entrada PC a buscar en la BHT
     * @param BHT referencia a una BHT creada.
     * @return string pred con la prediccion correspondiente de la BHT */
    string getPred(int addr, vector<int> &BHT);


        /** Lee una linea de un trace de entrada en formato PC - T/N, devuelve por referencia el PC y el outcome leidos
        @param f FILE * puntero a un archivo tipo trace abierto.
        @param PC referencia a string donde almacenar el PC leido
        @param outcome referencia a string donde almacenar el outcome leido*/
      void readTraceLine(FILE *f, string &PC,string &outcome);
       
       /** Crea la tabla para el archivo de salida con el nombre ingresado, la informacion se guarda en add de forma concatenada.
        * @param add referencia a string donde concatenar salida
        * @param nombre nombre del archivo de salida que concuerda con el predictor usado.*/
        void makeTable(string &add, char nombre[]);


    /** Crear el output a imprimir en el archivo de salida con los parametros dados de la simulacion.
     * @param add llena, tabla llena o no
     * @param add string donde se ha concatenado la info-output de la simulacion
     * @param PC string con la direcicon de la PC leida
     * @param outcome string con el outcome leido
     * @param pred string prediccion realizada
     * @return string ADD a sobreescribir/concatenar en cada linea leida      */
    string out(vector<int> &BHT, string add, string &PC, string &outcome, string &pred);


       /** Crear el output a imprimir en el archivo de salida con los parametros dados de la simulacion.
     * @param predictor indica el predictor tomado por el metapredictor, G o P
     * @param add string donde se ha concatenado la info-output de la simulacion
     * @param PC string con la direcicon de la PC leida
     * @param outcome string con el outcome leido
     * @param pred string prediccion realizada
     * @return string ADD a sobreescribir/concatenar en cada linea leida      */
    string outT(string predictor, string add, string &PC, string &outcome, string &pred);

    /** Imprime los resultados de la simulacion en console*/
    void console(string predName, int ss, int gh, int ph, int Tbc, int Tbi, int Nbc, int Nbi);
        
    /** Actualiza el valor del contador en la BHT con el ingresado.
     @param addr direccion/entrada de la BHT a sustituir */
    void actualizarBHT(int addr, string pred, vector<string> &BHT);

    /** Devuelve los n bits menos significativos del PC leido para analizar y predecir, segun el tamano ingresado
     * @return PC bits menos significativos en tipo int*/ 
    int LSB_PC(string &PC, int bits);

      /** Devuelve los n bits menos significativos del PC leido para analizar y predecir, segun el tamano ingresado
     * @return PC bits menos significativos en tipo int*/ 
    int LSB(string PC, int bits);

    /** Realiza el desplazamiento a la izquierda(shiftleft) de la Xor y mantiene el orden de bits y logica binaria
     * @param GHR bits del registro de historia global. */
    void shiftleft(int &GHR, int &bgh, int &ss,int &updateGHR);

    /** mantiene los contadores de saltos y predicciones para los resultados de simulacion*/
    int contadores(string &pred, string &outcome,double &bcount, int &Tbc, int &Tbi, int &Nbc, int &Nbi);

    /** Mantiene la logica de entrenamiento de los contadores y el BHT*/
    void learning(int addr,string &outcome,string &pred,vector<int> &BHT,int &counter, int limit);
    
    /** Realiza la terminacion de lectura, cierre del archivo trace y creacion de tabla output
     * @param FILE *f puntero al archivo trace que se esta leyendo
    */
    void salidaTour(FILE *f,int &o, int &gh, int &ph,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi);
    
    /** Realiza la terminacion de lectura, cierre del archivo trace y creacion de tabla output
     * @param FILE *f puntero al archivo trace que se esta leyendo
    */
    void salidaGshare(FILE *f,int &o,int &gh,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi);

    /** Realiza la terminacion de lectura, cierre del archivo trace y creacion de tabla output
     * @param FILE *f puntero al archivo trace que se esta leyendo
    */
    void salidaPshare(FILE *f,int &o,int &ph,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi);

    /** Realiza la terminacion de lectura, cierre del archivo trace y creacion de tabla output
     * @param FILE *f puntero al archivo trace que se esta leyendo
    */
    void salidaBimodal(FILE *f,int &o,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi);
