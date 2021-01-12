#include "MovieTree.hpp"
#include <iostream>
using namespace std;

// float Drill(MovieNode *root, string id, float rating, int year, int number, float total)
// {
//   if(root -> leftChild != nullptr) Drill(root -> leftChild, id, rating, year, number, total);
//   // place middle instructions here
//   if(id == "print") cout << "Movie: " << root->title << " " << root->rating << endl;
//   if(id == "q"){
//    if(root -> year > year && root -> rating >= rating) cout << root->title << "(" << root->year << ") " << root->rating << endl;
//  }
//   number++;
//   total+= root -> rating;
//   if(root -> rightChild != nullptr) Drill(root -> rightChild, id, rating, year, number, total);
//   // put end instructions here
//   if(id == "delete")
//   {
//     delete root;
//     root = nullptr;
//   }
//   if(number != 0) return total / number;
//
// }

MovieTree :: MovieTree()
{
  // Constructor: Initialize any member variables of the class to default
  // Variables:
  //   MovieNode *root;
  root = nullptr;
  // variables of the struct?

}

void deleteAll(MovieNode* node)
{

  if(node -> leftChild != nullptr) deleteAll(node -> leftChild);
  if(node -> rightChild != nullptr) deleteAll(node -> rightChild);
  delete node;
  node = nullptr;


}

MovieTree :: ~MovieTree()
{
  // Destructor: Free all memory that was allocated
  deleteAll(root);

}


MovieNode* MovieTree ::search(std::string title)
{
  // This private function is meant to be a helper function. Return a pointer to the node with
  // the given title, or nullptr if no such movie exists
  MovieNode* current= root;
  while(true)
  {
    if(current -> title == title) return current;
    else if(current -> title > title)
    {
      if(current -> leftChild == nullptr) return nullptr;
      else current = current -> leftChild;
    }
    else{
      if(current -> rightChild == nullptr) return nullptr;
      else current = current -> rightChild;
    }
  }


}

void printer(MovieNode* node)
{
  if(node -> leftChild != nullptr) printer(node -> leftChild);
  cout << "Movie: " << node->title << " " << node->rating << endl;
  if(node -> rightChild != nullptr) printer(node -> rightChild);

}

void MovieTree :: printMovieInventory()
{
  //   Print every node in the tree in alphabetical order of titles using the following format
  // // for every Movie node (m) in the tree
  if(root != nullptr) printer(root);
  // cout << "Movie: " << m->title << " " << m->rating << endl;

}
void add(MovieNode *movie, MovieNode* current, MovieNode* prev)
{
  if(current == nullptr){
    if(prev -> title > movie -> title) prev -> leftChild = movie;
    else prev -> rightChild = movie;
    movie -> parent = prev;
   }
  else if(current -> title > movie -> title){
   add(movie, current -> leftChild, current);
 }
  else{
     add(movie, current -> rightChild, current);
   }

}

void MovieTree :: addMovieNode(int ranking, std::string title, int year, float rating)
{
    //   Add a node to the tree in the correct place based on its title. Every node’s left children
    //  should come before it alphabetically, and every node’s right children should come after it
    //  alphabetically. Hint: you can compare strings with <, >, ==, string::compare() function
    //  etc. You may assume that no two movies have the same title
    MovieNode* movie = new MovieNode(ranking, title, year, rating);
    if(root == nullptr) root = movie;
    else add(movie, root, nullptr);

}
void MovieTree :: findMovie(std::string title)
{
  // Find the movie with the given title, then print out its information:
  MovieNode* movie = new MovieNode;
  movie= search(title);
  if(movie != nullptr){
  cout << "Movie Info:" << endl;
  cout << "==================" << endl;
  cout << "Ranking:" << movie->ranking << endl;
  cout << "Title :" << movie->title << endl;
  cout << "Year :" << movie->year << endl;
  cout << "rating :" << movie->rating << endl;
  }
  // If the movie isn’t found print the following message instead:
  else cout << "Movie not found." << endl;

}

void query(MovieNode* node, float rating, int year)
{
  if(node -> rating >= rating && node -> year > year) cout << node->title << "(" << node->year << ") " << node->rating << endl;
  if(node -> leftChild != nullptr) query(node -> leftChild, rating, year);
  // if(node -> rating >= rating && node -> year > year) cout << node->title << "(" << node->year << ") " << node->rating << endl;
  if(node -> rightChild != nullptr) query(node -> rightChild, rating, year);
}

void MovieTree :: queryMovies(float rating, int year)
{
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  // each movie that satisfies the constraints should be printed with
  // Drill(root, "q", rating, year, 0, 0);
  query(root, rating, year);
  // cout << m->title << "(" << m->year << ") " << m->rating << endl;

}


int func(MovieNode* node, int return_value)
{
  if(node -> leftChild != nullptr) return_value = 1 + func(node -> leftChild, return_value );
  if(node -> rightChild != nullptr) return_value =  1 + func(node -> rightChild, return_value);
  return return_value;
}

float Total(MovieNode* node, float return_value)
{
  if(node -> leftChild != nullptr) return_value = node -> leftChild-> rating + Total(node -> leftChild, return_value );
  if(node -> rightChild != nullptr) return_value =  node -> rightChild-> rating + Total(node -> rightChild, return_value);
  return return_value;
}

void MovieTree :: averageRating()
{
  // Print the average rating for all movies in the tree. If the tree is empty, print 0.0. Ue the
  // // following format
  float average = 0, total;
  int number;
  if(root != nullptr){
    number = func(root, 1);
    total = Total(root, root -> rating);
    average = total / number;


  }

  cout << "Average rating:" << average << endl;
}
