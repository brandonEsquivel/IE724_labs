#include "../lib/bimodal.h"

using namespace std;

void bimodal_P(const char *TraceFilePath, int s , int gh, int ph){

    // VARIABLES

/////////////       INT Variables         ////////////////////////////////////////
    int counter = 0;                                                // temp variable, current state of the counter, taken from BHT
    int bits = pow(2,s);                                            // size 2^s bits
    int index;                                                      // index of BHT
    double bcount = 0;                                                 // branch counter
    int Tbc = 0;                                                    // statdistic variable, Taken branches Correct
    int Tbi = 0;                                                    // statdistic variable, Taken branches Incorrect
    int Nbc = 0;                                                    // statdistic variable, Not Taken branches Correct
    int Nbi = 0;                                                    // statdistic variable, Not Taken branches InCorrect

//////////       String Variables         ////////////////////////////////////////////
    string prediction;                                              // prediction
    string output = "gunzip -c ./branch-trace-gcc.trace.gz | ./src/branch\n Debug on bimodal branch predictor\n";                                                 // Output results Log string, concatenated results.
    vector<int> BHT (bits,0);                                       // 2^s ints counters with value 00
    string PC, Outcome;                                             // temp variables to save from the Trace
//////////       TRACE file openned to read   ////////////////////////////////////////////
    FILE *f;
    f = fopen(TraceFilePath,"r+");                                          // Opening the file on Read mode
    if (f == NULL) {                                                        // open error handling
        cout << "Can't open the file.\n"<< endl;
        exit(EXIT_FAILURE);
    }
    while ( !(!feof(f)^(bcount < 200) ) ){                              // traversing the file to the limit
        readTraceLine(f, PC, Outcome);                                      // Read one line of the trace, getting PC & Outcome from file.
        index = LSB(PC, s);                                                  // getting the index( -s LSB of the PC)
        prediction = getPred(index, BHT);                                   // getting the prediction, actual state of the BHT index
        learning(index, Outcome, prediction, BHT, BHT[index], 3);              // Update the BHT entry, Counters training

        contadores(prediction,Outcome,bcount,Tbc,Tbi,Nbc,Nbi);              // Update stadistic counters
        output = out(BHT,output, PC, Outcome, prediction);                      //  Update output string to create a output log file with a resume of the results
        } // end while

    makeTable(output, "./results/bimodalResults.log");                                // make the output results log table.
    console("Bimodal", bits, gh, ph, Tbc, Tbi, Nbc, Nbi);                     // print the result on console
    rewind(f);
    fclose(f);
}