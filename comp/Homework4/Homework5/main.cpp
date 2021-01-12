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
  cout << "1. Find a movie" << endl;
  cout << "2. Query movies" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Average Rating of movies" << endl;
  cout << "5. Quit" << endl;

}

int main ( int argc, char const *argv[])
{
  // Your main function should first read information about each movie from a file and store that
  // information in a MovieTree. The name of the file with this information should be passed in
  // as a command-line argument. An example file is Movies.csv on Moodle. It is in the format:
  // <Movie 1 ranking>,<Movie 1 title>,<Movie 1 year>,<Movie 1 rating>
  // <Movie 2 ranking>,<Movie 2 title>,<Movie 2 year>,<Movie 2 rating>
  // Etc…
  MovieTree tree;
  ifstream read;
  read.open(argv[1]);
  string line;
  string arr[4];
  while(getline(read, line))
  {
    split(line, ',', arr, 4);
    tree.addMovieNode(stoi(arr[0]),arr[1], stoi(arr[2]), stof(arr[3]));
  }
  read.close();
  string user_response = "0", t, r, y;
  while(user_response != "5")
  {
    menu();
    getline(cin, user_response);
    switch(stoi(user_response))
    {
      case 1:
        // Find a movie: Call your tree’s findMovie function on a movie specified by the user.
        // Prompt the user for a movie title using the following code:
        cout << "Enter title:" << endl;
        getline(cin, t);
        tree.findMovie(t);

      break;
      case 2:
        // Query movies: Call your tree’s queryMovies function on a rating and year specified by
        // the user. Prompt the user for a rating and year using the following code:
        cout << "Enter minimum rating:" << endl;
        // // get user input
        getline(cin, r);
        cout << "Enter minimum year:" << endl;
        getline(cin, y);
        tree.queryMovies(stof(r), stoi(y));

      break;
      case 3:
        // Print the inventory: Call your tree’s printMovieInventory function
        tree.printMovieInventory();
      break;
      case 4:
       // Average Rating of movies: Call your averageRating function
       tree.averageRating();
      break;
      case 5:
        cout << "Goodbye!" << endl;
      break;
    }
  }

}
