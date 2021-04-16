// INCLUDES
#include "../include/funciones.h"

// DEFINES
using namespace std;

// Gets the prediction in a index of the array BHT, for two bits counter.
string getPred(int addr, vector<int> &BHT){
    /*if( addr>BHT.size()){
        cout << "Wrong Choice (OutOfBounds). Please Check."<<endl;
        return 0;
    }
    else{ */
        if( BHT[addr]>=2    ){
            return "T";
        }
        else
        {
            return "N";
        }
    }
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int contadores(string &pred, string &outcome,double &bcount, int &Tbc, int &Tbi, int &Nbc, int &Nbi){
    if(pred==outcome & pred=="T"){       Tbc++;  bcount++; return 1;  }
    else if(pred==outcome & pred=="N"){  Nbc++;  bcount++; return 0;  }
    else if(pred!=outcome & pred=="T"){  Tbi++;  bcount++; return 0; }
    else{                                Nbi++;  bcount++; return 1; }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read a line of a trace file and saves PC & Outcome
void readTraceLine(FILE *f, string &PC, string &outcome){
    if (f == NULL) {                                                        // CChecking correct file open
        cout << "Can't open the file.\n"<< endl;
        exit(EXIT_FAILURE);
    }
   char aux [80];
    fscanf(f, "%s", aux);                                                    // scaning first word PC 
    PC = aux;
    fscanf(f, "%s", aux);
    outcome = aux;                                                          // scaning outcome                                                               // to bcount ++
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// makes the out table with results, like log. Needs rename function
void makeTable(string &add, char nombre[]){
    ofstream tabla;                                                                   // Abriendo archivo .tab para escribir tabla
    tabla.open("out.tab");
    //for(int j=0; j < add.size(); j++){
    tabla   <<  add;                                                           // Apend
    //}
    rename("out.tab", nombre);
    tabla.close();                                                                      // close
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//to print info and create a string add with individual results Concatenaded
string out(vector<int> &BHT, string add, string &PC, string &outcome, string &pred){
    string bht;
     for (int i = 0; i < BHT.size(); i++)
    {
    bht.push_back('N');
    }

    for (int i = 0; i < BHT.size(); i++)
    {
       switch (BHT[i])
       {
        case 0:
            bht[i] = 'N';
            break;
        case 1:
            bht[i] = 'n';
            break;
        case 2:
            bht[i] = 't';
            break;
        default:
            bht[i] = 'T';
            break;
       }
    }
    string c_i = "correct";                                                              // Variable auxiliar para guardar caracter.
    if(outcome!=pred){
        c_i = "incorrect";
    } //
    add = add + bht + "\t\t" + PC + "\t\t" + outcome + "\t\t" + pred + "\t\t" + c_i + "\n";             // Concatenando cadenas
    return add;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//to print info and create a string add with individual results Concatenaded for the TOURNAMENT BRANCH PREDICTOR
string outT(string predictor, string add, string &PC, string &outcome, string &pred){

    string c_i = "correct";                                                              // Variable auxiliar para guardar caracter.
    if(outcome!=pred){
        c_i = "incorrect";
    } //
    add = add +  PC + "\t\t" + predictor + "\t\t" + outcome + "\t\t" + pred + "\t\t" + c_i + "\n";             // Concatenando cadenas
    return add;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







// Top function to print the results resume
void console(string predName, int ss, int gh, int ph, int Tbc, int Tbi, int Nbc, int Nbi){
string console = "------------------------------------------------------------------------\nPrediction parameters:\n------------------------------------------------------------------------\n";
int bcount = Tbc+Tbi+Nbc+Nbi;
float percentCorrectPred = (float)(Tbc + Nbc)*100/((float)bcount);
string aux = to_string(ss);
console = console + "\nBranch prediction type: "+predName+"\n";
console = console + "\nBHT size (entries): "+aux+"\n";                              aux = to_string(gh);
console = console + "\nGlobal history register size: "+aux+"\n";                    aux = to_string(ph);
console = console + "\nPrivate history register size: "+aux+"\n";                   aux = to_string(bcount);
console = console + "\n------------------------------------------------------------------------\n";
console = console + "\n------------------------------------------------------------------------\n";
console = console + "\nSimulation results:\n";
console = console + "\n------------------------------------------------------------------------\n";
console = console + "\nNumber of branch: "+aux+"\n";                                aux = to_string(Tbc);
console = console + "\nCorrect prediction of T branches: "+aux+"\n";                aux = to_string(Tbi);
console = console + "\nIncorrect prediction of T branches: "+aux+"\n";              aux = to_string(Nbc);
console = console + "\nCorrect prediction of N branches: "+aux+"\n";                aux = to_string(Nbi);
console = console + "\nIncorrect prediction of N branches: "+aux+"\n";              aux = to_string(percentCorrectPred);
console = console + "\nPercentage of correct predictions: "+aux+"\n";
console = console + "\n------------------------------------------------------------------------\n";
cout << console;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void learning(int index,string &outcome,string &pred,vector<int> &BHT,int &counter, int limit){
    if(outcome == "T"){
        if ( counter < limit)
        {
            BHT[index]++;
        }
        else{
            BHT[index] = BHT[index];
        }
    }
    else{
         if (counter>0){
            BHT[index]--;
        }else
        {
            BHT[index] = BHT[index];
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LSB(string PC, int bits){
    int mask = pow(2,bits) - 1;           // 2^s - 1 bits
    long pc = (int)std::strtol(PC.c_str(), nullptr, 10); // 10 is the base which parse the string
    return pc&mask;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void shiftleft(int &GHR, int &bgh, int &ss, int &updateGHR){
    if(GHR>=bgh){      GHR = GHR-bgh;}
    if(updateGHR==0){
        GHR = 2*GHR;                // Desplazamiento a la izquierda actualizando con un NT
        }
    else{
        GHR = 2*GHR + 1;             // Desplazamiento a la izquierda actualizando con un T
    }
   if(GHR>=bgh){      GHR = GHR-bgh;}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void salidaBimodal(FILE *f,int &o,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi){
  if(o==1){   makeTable(add,"../build/bimodal.tab"); }
    console("bimodal",bits,0,0,Tbc,Tbi,Nbc,Nbi);
    fclose(f);
}


void salidaGshare(FILE *f,int &o,int &gh,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi){
  if(o==1){   makeTable(add,"../build/Gshare.tab"); }
    console("Gshare",bits,gh,0,Tbc,Tbi,Nbc,Nbi);
    fclose(f);
}

void salidaPshare(FILE *f,int &o,int &ph,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi){
  if(o==1){   makeTable(add,"../build/Pshare.tab"); }
    console("Pshare",bits,0,ph,Tbc,Tbi,Nbc,Nbi);
    fclose(f);
}

void salidaTour(FILE *f,int &o, int &gh, int &ph,string &add,int &bits, int &Tbc,int &Tbi,int &Nbc,int &Nbi){
  if(o==1){   makeTable(add,"../build/Tournament.tab"); }
    console("Tournament",bits,gh,ph,Tbc,Tbi,Nbc,Nbi);
    fclose(f);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

//
/* gets the
int LSB_PC(string &PC, int bits){
    char x = PC.at( PC.size()-1);
    char xx = PC[PC.size()-2];
    char xxx = PC.at( PC.size()-3);

int bit0 = (int)x-'0';
int bit1 = (int)xx-'0';
int bit2 = (int)xxx-'0';

int value2 = bit0 + bit1*10;
int value3 = value2 + bit2*100;

    if ( value3 < (bits-1) ){
        return value3;
    }
    else if (  value2 < (bits-1) )
    {
        return value2;
    }
    else if (bit0 < (bits-1))
    {   return bit0;
    }
    else{
        return bits-1;
        }
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
string prediccion(int addr, vector<string> &BHT){
    if( addr>BHT.size()){
        cout << "Direccion no valida (outofBounds) Verifique por favor."<<endl;
        return "N";
    }
    else{
        if((BHT[addr]=="ST") || (BHT[addr]=="WT")){
            return "T";
        }
        else
        {
            return "N";
        }
    }
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////