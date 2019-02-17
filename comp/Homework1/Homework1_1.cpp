#include<iostream>
using namespace std;
#include <string>
#include <fstream>

int insertIntoSortedArray(int myArray[], int numEntries, int newValue)
{
  for(int i = 0; i < numEntries; i++)
  {
    if(myArray[i] > newValue)
    {
     for(int j = numEntries; j > i; j--)
     {
       myArray[j] = myArray[j-1];
     }
      myArray[i] = newValue;
      return numEntries + 1;
    }
  }
  myArray[numEntries] = newValue;
  return numEntries +1;
}

int main ( int argc, char const *argv[])
{
  ifstream read;
  read.open(argv[1]);
  if(!read.is_open()) cout << "Failed to open the file." <<endl;
  string number;
  int myarray[100];
  int i = 0;
  while(getline(read, number))
  {
    int newValue = stoi(number);
    insertIntoSortedArray(myarray, i, newValue);
    for(int j = 0; j < i+1; j++)
    {

      cout << myarray[j];
      if(j != i) cout << ",";
    }
    cout << endl;
    i++;

  }
  return 0;

}
