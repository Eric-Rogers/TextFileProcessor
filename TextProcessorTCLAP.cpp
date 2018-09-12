//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#include<iostream>
#include<map>
#include "tclap/CmdLine.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  map<int, string> cmla; //A map of the command line arguments keys are int values are string
  enum cmlaNames {u, l, o, i}; //The command line argument's enums for use with cmla map

  try 
  { 
    //First argument is program description and is printed at bottom of help
    //Second argument is delimiter
    //Third is version number
    TCLAP::CmdLine cmd("CS3376.001 Homework 2: Reads input text file and, based on command line arguments given, changes the text upon writing to an output file.",' ',"2.1");
  
    //Switch arguments
    //First argument is the short name of flag("u" means -u on command line)
    //Second argument is longname flag("upper" means --upper on command line)
    //Third argument is description of what the argument does
    //Fourth argument is name of CmdLine object that is going to parse the command line
    //Fifth argument is the default value of flag 
    TCLAP::SwitchArg upperSwitch("u", "upper","Convert all text to uppercase.",cmd,false);
    TCLAP::SwitchArg lowerSwitch("l","lower","Converts all text to lowercase.",cmd,false);
  
    //Value arguments - have a flag and a value
    //First argument is short name of flag
    //Second argument is long name of flag
    //Third argument is description of what the argument does
    //Fourth argument boolean for if argument is required
    //Fifth argument is default value
    //Sixth argument describes the type of value
    //Seventh argument is the CmdLine object that will parse the command line 
    TCLAP::ValueArg<string> outfileArg("o", "outfile", "The name of the output file.",false,"output.txt","output filename", cmd);

    //Unlabeled value arguments
    //First argument is the name of the parameter
    //Second argument is the description of the value
    //Third argument is a boolean that tells whether the argument is required
    //Fourth argument is the default value
    //Fifth argument is used in the <  > description in help
    //Sixth argument is the CmdLine object this arg is a part of
    //Seventh argument states whether you can ignore the parameter
    TCLAP::UnlabeledValueArg<string> infileArg("infile","The input file name.",true,"infile.txt","input filename",cmd,false);

    cmd.parse(argc,argv); //parse the command line looking for arguments associated with cmd

    //bool values stored in upperSwitch and lowerSwitch switch to string so it can be stored in the map cmla 
    if(upperSwitch.getValue())
      cmla[u] = "true";
    else
      cmla[u] = "false";
  
    if(lowerSwitch.getValue())
      cmla[l] = "true";
    else
      cmla[l] = "false";

    //store values from outfileArg and infileArg into map cmla
    cmla[o] = outfileArg.getValue();
    cmla[i] = infileArg.getValue();
  }
  catch(TCLAP::ArgException &e) //catches any exception
  {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }

  ifstream inputFile; //initialize ifstream for the input file
  inputFile.open(cmla[i].c_str(), ios::in); //open the input file using filename stored in map
  
  if(inputFile.is_open()) //make sure the file opened properly
  {
    ofstream outFile; //initialize ofstream for the output file
    outFile.open(cmla[o].c_str(), ios::out); //open the output file using the filename stored in the map
    
    string hold = ""; //used to hold the line from inputFile so that we can change characters in it if necessary 

    if(cmla[u] == "true" && cmla[l] == "false") //if upper SwitchArg was found and lower SwitchArg was not found
    {
      while(!inputFile.eof()) //loop through all lines of file
      {
	getline(inputFile, hold); //put current line in hold from inputFile
	for(int i = 0; i < hold.length(); i++) //loop through all characters of hold and change to uppercase
	{
	  hold[i] = toupper(hold[i]);
	}
	 
	outFile << hold << endl; //print new hold to outFile
      }
    }  
    else if(cmla[l] == "true" && cmla[u] == "false") //lower SwitchArg was found and upper SwitchArg was not found
    {
      while(!inputFile.eof()) //loop through all lines of inputFile
      {
	getline(inputFile, hold); //put current line in hold from inputFile
	for(int i = 0; i < hold.length(); i++) //loop through all characters of hold and change to lowercase
	{
	  hold[i] = tolower(hold[i]); 
	} 
	
	outFile << hold << endl; //print new hold to outFile
      }
    }
    else if(cmla[u] == "true" && cmla[l] == "true") //both lower and upper args are found
    {
      cout << "The case cannot be both upper and lower in the future use one or the other." << endl; //tell user what will happen now
    }
    else //file opened properly and neither -u or -l is given
    {
      //Copy contents of input file to the output file with no changes
      while(!inputFile.eof())
      {
	  getline(inputFile, hold);
	  outFile << hold << endl;
      }
    }

    outFile.close(); //close outFile
  }  
  else //Cannot open input file given
  {
    cout << "Cannot open input file given." << endl;
  }
     
  inputFile.close();  //close inputFile

  return 0;
}
