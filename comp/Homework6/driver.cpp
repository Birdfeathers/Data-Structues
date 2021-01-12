#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int split(string split, char del,string arr[] , int length)
{
    int splitlength = split.length();
    int entry = 0, wordlength=0, i=0;
    for( i; entry < length && i < splitlength; i++ )
     {
       if(split[i] != del)
         {
            while(split[i] != del&& i < splitlength)
            {
                i++;
                wordlength++;
            }
            arr[entry]= split.substr(i-wordlength, wordlength);
            wordlength =0;
            entry++;
         }
     }
    for(i; i < splitlength; i++)
    {
        if(split[i] != del) return -1;
    }
    return entry;

}

void menu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Print the inventory" << endl;
  cout << "2. Delete a movie" << endl;
  cout << "3. Quit" << endl;

}

int main ( int argc, char const *argv[])
{
  //cout << argv[1];
  MovieTree tree;
  ifstream read;
  read.open(argv[1]);
  //cout << argv[1];
  string line;
  string arr[4];
  while(getline(read, line))
  {
    //cout << argv[1];
    split(line, ',', arr, 4);
    // cout << argv[1] << endl;
    // cout << arr[0] << "," << arr[1] << "," << arr[2] << "," << arr[3] << endl;
    tree.addMovie(stoi(arr[0]),arr[1], stoi(arr[2]), stof(arr[3]));
  }
  read.close();
  string user_response = "0", title;
  while(user_response != "3")
  {
    menu();
    getline(cin, user_response);
    switch(stoi(user_response))
    {
      case 1:
      //Print the inventory: Call your tree’s printMovieInventory function
      tree.printMovieInventory();


      break;
      case 2:
        // Delete a movie: Call your deleteMovie function on a title specified by the user. Prompt
        // the user for a movie title using the following code:
        cout << "Enter title:" << endl;
        getline(cin, title);
        tree.deleteMovie(title);
      break;
      case 3:
        cout << "Goodbye!" << endl;
      break;

    }
  }

}
