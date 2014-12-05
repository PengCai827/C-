// grades.cpp
// CSCI 455 PA5
// Name:Peng Cai
// Loginid:pengcai
// 
/*
 * A program to test the Table class.
 * How to run it:
 *      grades [hashSize]
 * 
 * the optional argument hashSize is the size of hash table to use.
 * if it's not given, the program uses default size (Table::HASH_SIZE)
 *
 */

#include "Table.h"
#include <sstream>
#include <stdio.h>
#include<cstring>
// cstdlib needed for call to atoi
#include <cstdlib>
#include <string>

#include <vector>
std::string line;
std::vector<std::string> strings;
void summary();

int main(int argc, char * argv[]) {

  // gets the hash table size from the command line

  Table * grades;  // Table is dynamically allocated below, so we can call
                   // different constructors depending on input from the user.
    int hashSize ;
  if (argc > 1) {
    hashSize = atoi(argv[1]);  // atoi converts c-string to int

    if (hashSize < 1) {
      cout << "Command line argument (hashSize) must be a positive number" 
	   << endl;
      return 1;
    }

    grades = new Table(hashSize);

  }
  else {   // no command line args given -- use default table size
      hashSize = Table::HASH_SIZE;

    grades = new Table();
  }
    
    cerr<<""<<endl;
    grades->hashStats(cerr);// prints out the hashStats() for empty table
    bool flag=true;//To enable a inifinite loop to take user's input until user hit "q"
    while(flag){

    cout << "cmd>";
    //Read user input string separated by space and store each word into array;
    char c;
    char input[100];
    cin.getline(input,100);//Take into user input
    string newstr(input);
    c=input[0];
    string array[1024];
    string input_first;
    string input_second;
    int input_third=0;
    istringstream iss(newstr);
    int i=0;
    do
    {
        string sub;
        iss >> sub;
        array[i++]=sub;
    } while (iss);

        if((array[2]=="")&&(array[1]!="")){//When the number of input arguments are two

        input_first=array[0];
        input_second=array[1];
    }
        else if ((array[1]=="")&&(array[0]!="")){//When the number of input argument is one

        input_first=array[0];
    }
    else if((array[1]!="")&&(array[0]!="")&&(array[2]!="")){//When the number of input arguments are three
        input_first=array[0];
        input_second=array[1];
        input_third=std::stoi(array[2] );//Change number of string type into integer type
    }
        switch (c) {
            case 'i':{
                if((input_second!="")&&(input_third!=0)){
                    grades->insert(input_second, input_third);//Inser the name and score pair into the table
                    break;

                }
                break;}
            case 'c':{
                int* updateValue =grades->lookup(input_second);//Firstly check whether a name is already existed. If so, update the score with the new score;if not print out the information.
                if (updateValue!=NULL) {
                    *updateValue=input_third;
                }else{
                    cout<<"This name doesn't exist"<<endl;
                }
                break;}
            case 'l':{
                
                int* lookupValue =grades->lookup(input_second);//Look up a name , if the name exists in score table, print out the score; If not, print out the information indicating that the name doesn't exist;
                if(grades->lookup(input_second)==NULL){
                    cout<<"This name doesn't exist"<<endl;
                    
                }else{
                    cout<<"The score of name "<<input_second<<" is: "<<*lookupValue<<endl;

                }
                break;}
            case 'r':{
                int* removeStu=grades->lookup(input_second);//First, look up the name, if the name exists in the table, then execute the remove method; If not, print out the message.
                if(removeStu!=NULL){
                    grades->remove(input_second);
                }else{
                    cout<<"This name is not in the score table"<<endl;
                    
                }
                break;}
            case 'p':{
                cout << "Print name and score in table: " << endl;//print out all the name and score pairs in the table;
               grades->printAll();
                break;}
            case 'n':{
                cout<<"The number of entries is: "<<grades->numEntries()<<endl;//print out the number of entries;
                break;}
            case 's':{
                cerr<<"" <<endl;
                grades->hashStats(cerr);//Print out the  statistics about the hash table
                break;}

            case 'h':{
                summary();//Prints out a brief command summary.
                
                break;}

            case 'q':
                flag = false;//Exit the programe;
                
                break;

            default:
                break;
       }
    

   }

    return 0;
 
  
}
void summary(){
    cout<<"For intsert name and score: i name score;"<<endl;
    cout<<"For change score for the name: c name newscore;"<<endl;
    cout<<"For lookup name and print out score: l name;"<<endl;
    cout<<"For remove student: r name;"<<endl;
    cout<<"Prints out all names and scores in the table: p;"<<endl;
    cout<<"Prints out the number of entries in the table: n;"<<endl;
    cout<<"Prints out statistics about the hash table at this point: s;"<<endl;
    cout<<"Exits the program: q"<<endl;

}

