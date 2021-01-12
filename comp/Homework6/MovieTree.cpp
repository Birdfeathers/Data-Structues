#include "MovieTree.hpp"
#include <iostream>
using namespace std;

MovieTree :: MovieTree()
{
  // Constructor: Initialize any member variables of the class to default
  root = nullptr;

}

void deleteAllLL(LLMovieNode* head)
{
  LLMovieNode* current = head -> next;
  LLMovieNode* last = head;
  while(current != nullptr)
  {
    last = current;
    current = current -> next;
    delete last;
    last = nullptr;
  }
}

void deleteAll(TreeNode* current)
{
  if(current -> leftChild != nullptr) deleteAll(current -> leftChild);
  if(current -> rightChild != nullptr) deleteAll(current -> rightChild);
  deleteAllLL(current -> head);
  delete current -> head;
  current -> head = nullptr;
  if(current -> parent != nullptr)
  {
    delete current;
    //current = nullptr;
    if(current == current -> parent -> leftChild) current -> parent -> leftChild = nullptr;
    else current -> parent -> rightChild = nullptr;
  }
}

 MovieTree :: ~MovieTree()
 {
   // Destructor: Free all memory that was allocated
   if(root != nullptr){
   deleteAll(root);
   delete root;
   root = nullptr;
 }

 }

void printLL(LLMovieNode* head)
{
  LLMovieNode* current = head;
  while(current != nullptr)
  {
    cout << " >> " << current->title << " " << current->rating << endl;
    current = current -> next;
  }
}

void printTreeNode(TreeNode* current)
{
  if(current == nullptr) return;
  if(current -> leftChild != nullptr) printTreeNode(current -> leftChild);
  cout << "Movies starting with letter: " << current->titleChar << endl;
  printLL(current -> head);
  if(current -> rightChild != nullptr) printTreeNode(current -> rightChild);
  //delete current;
}
void MovieTree :: printMovieInventory()
{
  // Print every movie in the data structure in alphabetical order of titles using the following
  // format. For TreeNode t and LLMovieNode m:
  // // for every TreeNode (t) in the tree
  // cout << "Movies starting with letter: " << t->titleChar << endl;
  // // for every LLMovieNode (m) attached to t
  // cout << " >> " << m->title << " " << m->rating << endl;
  printTreeNode(root);

}

TreeNode* findLetter(char first, TreeNode* current)
{
  if(current == nullptr) return nullptr;
  while(true)
  {
    if(current -> titleChar == first) return current;
    else if(current -> titleChar > first)
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

void addLetter(TreeNode *addnode, TreeNode* current, TreeNode* prev)
{
  if(current == nullptr)
  {
    if(prev -> titleChar > addnode -> titleChar) prev -> leftChild = addnode;
    else prev -> rightChild = addnode;
    addnode -> parent = prev;
  }
  else if(current -> titleChar > addnode -> titleChar) addLetter(addnode, current -> leftChild, current);
  else addLetter(addnode, current -> rightChild, current);

}

void addLL(TreeNode* place, LLMovieNode* add)
{
  if(add -> title <= place -> head -> title)
  {
    add -> next = place -> head;
    place -> head = add;
  }
  else{
    LLMovieNode* current = place -> head;
    bool end = false;
    while(!end)
    {
      if(current -> next == nullptr)
      {
        current -> next = add;
        end = true;
      }
      else if(current -> next -> title > add -> title)
      {
        add-> next = current -> next;
        current -> next = add;
        end = true;
      }
      else current = current -> next;
    }
  }


}
void MovieTree :: addMovie(int ranking, std::string title, int year, float rating)
{
  // Add a movie to the data structure in the correct place based on its title.
  // ◆ If there is no tree node corresponding to the first letter of title, create it and insert
  // it in the tree in the alphabetically correct position
  LLMovieNode *movie = new LLMovieNode(ranking, title, year, rating);
  //cout << "l" << endl;
  //TreeNode *place = new TreeNode;
  TreeNode* place = findLetter(title[0], root);
  if(place == nullptr)
  {
    //cout << "l" << endl;
    place = new TreeNode;
    place -> titleChar = title[0];
    place -> head = movie;
    if(root == nullptr) root = place;
    else addLetter(place, root, nullptr);
    //delete place;
  }
  else
  {
    //cout << "l" << endl;
    addLL(place, movie);
  }

}

TreeNode* findMin(TreeNode* from)
{
  while(from -> leftChild != nullptr) from = from -> leftChild;
  return from;
}
void twoChildDelete(TreeNode* n)
{
  TreeNode* min = findMin(n -> rightChild); // min of right subtree
  if(min == n -> rightChild)
  {
    if(n == n -> parent -> leftChild) n -> parent -> leftChild = min;
    else n -> parent -> rightChild = min;
    min -> parent = n -> parent;
    min -> leftChild = n -> leftChild;
    min -> leftChild -> parent = min;
  }
  else
  {
    // replace min RC with min
    min -> parent -> leftChild = min -> rightChild;
    if(min -> rightChild != nullptr) min -> rightChild -> parent = min -> parent;
    // insert min into n's old spot
    if(n == n -> parent -> leftChild) n -> parent -> leftChild = min;
    else n -> parent -> rightChild = min;
    min -> parent = n -> parent;
    min -> leftChild = n -> leftChild;
    min -> rightChild = n -> rightChild;
    min -> rightChild -> parent = min;
    min -> leftChild -> parent = min;
  }
}

void deleteTreeNode(TreeNode* n)
{
  if(n -> leftChild != nullptr && n -> rightChild != nullptr)
  { // two child case
    twoChildDelete(n);
  }
  else if(n -> rightChild == nullptr && n -> leftChild == nullptr)
  { // the leaf case
      if(n == n -> parent -> leftChild) n -> parent -> leftChild = nullptr;
      else n -> parent -> rightChild = nullptr;
  }
  else
  {// the one child case
    if(n -> leftChild != nullptr)
    {
      if(n == n -> parent -> leftChild) n -> parent -> leftChild = n -> leftChild;
      else n -> parent -> rightChild = n -> leftChild;
      n -> leftChild -> parent = n -> parent;
    }
    else
    {
      if(n == n -> parent -> leftChild) n -> parent -> leftChild = n -> rightChild;
      else n -> parent -> rightChild = n -> rightChild;
      n -> rightChild -> parent = n -> parent;
    }
  }
  delete n;
  n = nullptr;

}

LLMovieNode* findLL(string title, LLMovieNode* current)
{
  while(current != nullptr)
  {
    if(current -> title == title) return current;
    else current = current -> next;
  }
  return nullptr;
}

bool deleteLL(LLMovieNode* toDelete, TreeNode* tnode) // delete node, return true if last to be deleted, else return false
{
  if(toDelete == tnode -> head)
  {
    if(tnode -> head -> next == nullptr)
    {
      delete tnode -> head;
      tnode -> head = nullptr;
      return true;
    }
    else
    {
      LLMovieNode* temp = tnode -> head;
      tnode -> head = tnode -> head -> next;
      delete temp;
      temp = nullptr;
      return false;
    }
  }
  else
  {
    LLMovieNode* previous = tnode -> head;
    while(previous -> next != toDelete) previous = previous -> next;
    previous -> next = previous -> next -> next;
    delete toDelete;
    toDelete = nullptr;
    return false;
  }
}

void MovieTree :: deleteMovie(std::string title)
{
  //  Delete the linked list node that contains title. If as a result of this deletion, the linked list
  // becomes empty, delete the associated tree node. If the movie does not exist in the data
  // structure, print the following message
  // cout << "Movie: " << title << " not found, cannot delete." << endl;
  TreeNode* Tnode = findLetter(title[0], root);
  if(Tnode == nullptr) cout << "Movie: " << title << " not found, cannot delete." << endl;
  else{
    LLMovieNode* LLNode = findLL(title, Tnode -> head);
    if(LLNode == nullptr)  cout << "Movie: " << title << " not found, cannot delete." << endl;
    else{
      if(deleteLL(LLNode, Tnode))
      {
        if(Tnode == root)
        {
            if(Tnode -> rightChild != nullptr && Tnode -> leftChild != nullptr)
            { // two child case
              TreeNode* min = findMin(root -> rightChild);
              if(min == Tnode -> rightChild)
              {
                min -> leftChild = Tnode -> leftChild;
                min -> leftChild -> parent = min;
              }
              else
              {
                // replace min RC with min
                min -> parent -> leftChild = min -> rightChild;
                if(min -> rightChild != nullptr) min -> rightChild -> parent = min -> parent;
                min -> leftChild = Tnode -> leftChild;
                min -> rightChild = Tnode -> rightChild;
                min -> rightChild -> parent = min;
                min -> leftChild -> parent = min;
              }
              root = min;
            }
            else if(Tnode -> leftChild == nullptr && Tnode -> rightChild == nullptr) root = nullptr;
            else if(Tnode -> rightChild != nullptr) root = Tnode -> rightChild;
            else root = Tnode -> leftChild;
            if(root != nullptr) root -> parent = nullptr;
          delete Tnode;
        }
        else deleteTreeNode(Tnode);
      }

    }
  }
}
