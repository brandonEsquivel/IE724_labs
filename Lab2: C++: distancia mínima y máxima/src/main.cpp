
// Brandon Esquivel Molina
// B52571
// IE724 Laboratorio de programacion y microcontroladores
// EIE, UCR
// Lab 2: N Distancias, C++
// Ubuntu 18.04 LTS
// C++
// cmd to run: -make all- (in root)




/* INCLUDES */
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

/* DEFINES */
using namespace std;

#define INTRO "\nEste es un programa que le ayudará a calcular la distancia máxima y mínima entre cualquier par de puntos, de una lista de puntos."
#define HMpoints "¿Cuantos puntos va a introducir?: "
#define INSERT "Digite un punto bi-dimensional de la forma x,y: "
#define DMax "\nLa distancia maxima se da entre los puntos: "
#define Dmin "\nLa distancia minima se da entre los puntos: "
#define nDMax "\nLa distancia maxima se da (tambien) entre los puntos: "
#define nDmin "\nLa distancia minima se da (tambien) entre los puntos: "
#define Distance(x1, y1, x2, y2) sqrt(  pow( (x2 - x1), 2) + pow( (y2 - y1) , 2) * 1.0 )      // calc euclidian distance

/* Variables */
int N, pos_coma = 0;                      // N: the number of points to enter.        pos_coma: used to save the position of the comma (",") in the input, ordered pair
float dist_min, dist_max, aux;            // dist min and max: to save this values.   aux: auxiliary variable
bool flag1, flag2 = false;                // Control flags: indicate when more than a maximum or minimum distance have been detected(true), respectively
string par, check;                        // control input variables.

/*Main*/
int main(int argc, char const *argv[]) {

  /*Program introduction*/
  cout << INTRO << endl;
  reingrese:
  cout << HMpoints << endl;

  /*Input int N verification: Checking format */
  cin >> check;
  for (size_t i = 0; i < check.size(); i++)
  {
    if (!isdigit(check[i]) )                                  // checking form
    {
      cout << "\nPor favor ingrese un numero entero mayor a 1. \n";
      goto reingrese;
    }

  }
  N = stoi(check);                                        // cast to int, check OK
  if (N<2)                                                // CHECKING FOR 2 OR MORE POINTS CASE
  {
    cout << "\nPor favor ingrese un numero entero mayor a 1. \n";
      goto reingrese;
  }

  /*Defining operational structures */
  vector <float> equis(N);                                // vector that contains the AXIS X VALUES of the input points, directly correlated with yess vector
  vector <float> yess(N);                                 // vector that contains the AXIS Y VALUES of the input points, directly correlated with equis vector
  vector <float> distances;                               // vector that contains the calculated distance of all point combination, directly correlated with tags vector
  vector <string> tags;                                   // vector that contains the names of the two related points, directly correlated with distances vector

  // Obtaining number of points and other input variables
  /* taking user values */
  for (size_t i = 0; i < N; i++)
  { pairs:
    cout << i << ") " << INSERT << endl;
    cin >> par;                                                 // input point storage

    /*Checking point format*/
    if (par.find(",") == -1  || (!isdigit(par[0]) && par[0]!='-') )                     // check: the comma and format
    {
      cout << "\nPor favor, reingrese el punto en la forma X,Y \n" << endl;
      goto pairs;
    }


    pos_coma = par.find(",");                                   // comma check OK, now detecting the position of the comma in the input array (point)

    /*Checking for multiple commas*/
    if (  par.substr(0,pos_coma).find(",")!=-1 || par.substr(pos_coma+1).find(",")!=-1 )
    {
      cout << "\nPor favor, reingrese el punto en la forma X,Y \n" << endl;
      goto pairs;
    }


    /* check: Checking format for X value*/
    check = par.substr(0,pos_coma);
    for (size_t i = 0; i < check.size(); i++)
    {
      if (!isdigit(check[i]) && check[i]!='-' && check[i]!='.' )          // only numbers, dot or -
      {
        cout << "\nPor favor, ingrese el punto en la forma X,Y \n" << endl;
        goto pairs;
      }
    }

    equis[i] = stof(par.substr(0,pos_coma));                      // takin the AXIS X value, check OK
    /*Checking format for Y value*/
    check = par.substr(pos_coma+1);
    for (size_t i = 0; i < check.size(); i++)
    {
      if (!isdigit(check[i]) && check[i]!='-' && check[i]!='.' )
      {
        cout << "\nPor favor, ingrese el punto en la forma X,Y \n" << endl;
        goto pairs;
      }
    }
    yess[i] = stof(par.substr(pos_coma+1));                     // takin the AXIS Y value, check OK
  }

  /* Two points special case*/
  if (N==2)
  {
    aux = Distance( equis[0], yess[0], equis[1], yess[1]);    // calculating the distance
    string auxs = "(" + to_string(equis[0]) + "," + to_string(yess[0])+") y "+"(" + to_string(equis[1]) + "," + to_string(yess[1])+") ";   // packing points in (x,y) form
    cout << "Solo se ingresaron dos puntos, por ello la distancia maxima y minima es la misma entre ellos: " << auxs << aux << endl;       // output
    exit(1);
  }
  else
  /* Storage/Calculating distances and max min comparison */
  for (size_t j = 0; j < N; j++){                               // These two nested for loops are to cover all the possibilities of distances between different points,
    for (size_t k = j+1; k < N; k++)                            // that is, without repeating distances: A-> B, B-> A
    {
      aux = Distance( equis[j], yess[j], equis[k], yess[k]);    // calculating the distances
      string auxs = "(" + to_string(equis[j]) + "," + to_string(yess[j])+") y "+"(" + to_string(equis[k]) + "," + to_string(yess[k])+")";   // packing points in (x,y) form
      tags.push_back(auxs);                                     // storing tags values
      distances.push_back(aux);                                 // storing distance values
    }
  }

  /* Calc min distance */
  dist_min = distances[0];                                    // init value definition
  for (size_t m = 0; m < N; m++){
    if ( distances[m] < dist_min)                             // Comparison
    {
      dist_min = distances[m];                                // updating min value
    }
  }

    /* Calc max distance */
  dist_max = distances[0];                                    // init value definition
  for (size_t m = 0; m < N; m++){
    if ( distances[m] > dist_max)                             // Comparison
    {
      dist_max = distances[m];                                // updating max value
    }
  }


  /*Final print and many max-min results*/
  for (size_t f = 0; f < distances.size(); f++){                                   // Reading all distances to compare with min distance
    if (flag1)                                                      // flag1 indicates if there is more than one maximum distance or several equal
    {
      if ( distances[f] == dist_max)                                // Comparing
      {
        cout << nDMax << tags[f] << "-> " << dist_max << endl;      // Printing result
      }
    }
    else                                                            //non-multiple max distances detected yet case
      if ( distances[f] == dist_max)
      {
        cout << DMax << tags[f] << "-> " << dist_max << endl;
        flag1 = true;
      }

    if(flag2)                                                       // flag2 indicates if there is more than one Minimun distance or several equal
    {
      if ( distances[f] == dist_min)                                // Comparing
      {
        cout << nDmin << tags[f] << "-> " << dist_min << endl;      // Printing result
      }
    }
    else                                                            // Non-multiple min distances detected yet case
      if ( distances[f] == dist_min)
      {
        cout << Dmin << tags[f] << "-> " << dist_min << endl;       // Printing result
        flag2 = true;
      }
    }



/*For print all point and distance combinations*/
/*for (size_t i = 0; i < tags.size(); i++)
{
  cout <<"\n"<< i+1 << ") " << tags[i] << endl;
  cout << "\nDistancia: "  << distances[i] << endl;
}*/

/*For print max and min distances*/
/*cout << dist_max << endl;
  cout << dist_min << endl;
*/



  return 0;
}
