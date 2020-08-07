/*
Student Name:
Student Number:
Project Number: 3
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){
    this->N= N;
    this->M= M;
    this->lines[0].resize(N);
    this->lines[1].resize(M);
    // IMPLEMENT ME!
}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    // IMPLEMENT ME!
    char lineLetter = ticketInfo.front();
    int seat = stoi(ticketInfo.substr(1,ticketInfo.length()-1));
    int line;
    int module;
    if(lineLetter=='A'){
        line = 0;
        module = (seat-1)%N;
    }else {
        line = 1;
        module = (seat-1)%M;
    }
    Person neu {personType, line, seat, 0};
    if(lines[line][module].seatNumber!=0){
        Person arbitrary = lines[line][module];
        lines[line][module] = neu;
        changeSeat(arbitrary, line, module);
    }else{
        lines[line][module] = neu;
    }
}

void SeatOperations::printAllSeats(ofstream& outFile){
    for(int i = 0; i<N; i++){
        if(lines[0][i].seatNumber==0){
            outFile << 0 << endl;
        }else {
            char lineLetter = (lines[0][i].line == 0) ? 'A' : 'B';
            outFile << lines[0][i].type << " " << lineLetter << lines[0][i].seatNumber<< endl;
        }
    }
    for(int i = 0; i<M; i++){
        if(lines[1][i].seatNumber==0){
            outFile << 0 << endl;
        }else {
            char lineLetter = (lines[1][i].line == 0) ? 'A' : 'B';
            outFile << lines[1][i].type << " " << lineLetter << lines[1][i].seatNumber<< endl;
        }
    }
    // IMPLEMENT ME!
}
void SeatOperations::changeSeat(Person p, int line, int number) {
    int neuLine;
    int neuModule;
    if(p.type == 1){
        neuLine = (line+1)%2;
        neuModule = (p.seatNumber-1)%lines[((line+1)%2)].size();
    }else if(p.type == 2){
        if(lines[line].size()-1==number){
            neuLine = (line+1)%2;
            neuModule = 0;
        }else {
            neuLine = line;
            neuModule = number+1;
        }
    }else if(p.type == 3){
        int x = ((p.type3LastOperation+1)*(p.type3LastOperation+1))-((p.type3LastOperation)*(p.type3LastOperation));
        int neu = number + x;
        neuLine = line;
        neuModule = (number+x)%lines[line].size();
        while(neu>=lines[neuLine].size()){
            neu = neu - lines[neuLine].size();
            neuLine =  (neuLine+1)%2;
            neuModule = neu;
        }
        p.type3LastOperation = p.type3LastOperation+1;
    }
    if(lines[neuLine][neuModule].seatNumber!=0){
        Person arbitrary = lines[neuLine][neuModule];
        lines[neuLine][neuModule]= p;
       // printing();
        changeSeat(arbitrary,neuLine, neuModule);
    }else {
        lines[neuLine][neuModule] = p;
       // printing();
    }
}



// YOU CAN ADD YOUR HELPER FUNCTIONS