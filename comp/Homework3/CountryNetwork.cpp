/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  head = nullptr;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
  if(head == nullptr) return true;
  return false;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
  Country *newCountry = new Country;
  newCountry -> name = countryName;
  newCountry -> numberMessages = 0;
  //if previous is NULL, then add the new country to the beginning of the list
  if(previous == nullptr)
  {
    newCountry -> next = head;
    head = newCountry;
    //newCountry = nullptr;
    // If you are adding at the beginning use this:
    cout << "adding: " << countryName << " (HEAD)" << endl;
    // cout << "USA, head: " << head <<endl;
    // if(head == nullptr) cout << "head null" <<endl;
    // else cout<< "not null" << endl;
  }
  else{
    newCountry -> next = previous -> next;
    previous -> next = newCountry;
    //newCountry = nullptr;
    // Otherwise use this:
    cout << "adding: " << countryName << " (prev: " << previous->name <<")" << endl;
    // cout << "new head: " << head <<endl;
    // if(head == nullptr) cout << "head null" <<endl;
    // else cout<< "not null" << endl;
  }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName)
{
  if(head == nullptr) cout << "Country does not exist." <<endl;
  else{
  if(head ->name == countryName)
  {
    delete head;
    head = head -> next;
  }
  else{
  Country *deleteCountry = head -> next, *last = head;
  bool found = false;
  while(!found && deleteCountry != nullptr)
  {
    if(deleteCountry -> name == countryName) found = true;
    else{
      last = deleteCountry;
      deleteCountry = deleteCountry -> next;
    }
  }
  if(!found) cout << "Country does not exist." <<endl;
  else{
    last -> next = deleteCountry -> next;
  }
  delete deleteCountry;
  deleteCountry = nullptr;
  last = nullptr;
}
}
}


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
  deleteEntireNetwork();
//   Then add the following six countries, in order, to the network with
// insertCountry: "United States", "Canada", "Brazil", "India", "China", "Austraila"
  insertCountry(nullptr, "United States");
  insertCountry(searchNetwork("United States"), "Canada");
  insertCountry(searchNetwork("Canada"), "Brazil");
  insertCountry(searchNetwork("Brazil"), "India");
  insertCountry(searchNetwork("India"), "China");
  insertCountry(searchNetwork("China"), "Australia");
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
  Country *temp= head;
  while(temp != nullptr)
  {
    if(temp -> name == countryName) return temp;
    temp = temp -> next;
  }
  return NULL;

}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
//   Delete every node in the linked list and set head to NULL. Print the name of each node
// as you are deleting it according to the following format:
// cout << "deleting: " << node->name << endl;
// After the entire linked list is deleted, print:
// cout << "Deleted network" << endl;
  Country *temp, *current = head;
  while(current != nullptr)
  {
    cout << "deleting: " << current->name << endl;
    temp = current -> next;
    delete current;
    //cout << "deleting" <<endl;
    current = temp;
  }
  if(head != nullptr) cout << "Deleted network" << endl;
  head = nullptr;
}


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  if(head == nullptr) cout << "Empty list" << endl;
  else{
    Country *current = head;
    bool found = false;
    while(current != nullptr && !found)
    {
      if(current -> name == receiver) found = true;
      current -> numberMessages++;
      current -> message = message;
      cout << current->name << " [# messages received: " << current->numberMessages << "] received: " << current->message << endl;
      current = current -> next;

    }
    cout << endl;
  }

}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    cout << "== CURRENT PATH ==" << endl;
    Country *current = head;
    if(head == nullptr) cout << "nothing in path" << endl;
    else{
    while(current != nullptr)
    {
      cout << current -> name << " -> ";
      current = current -> next;
    }
    cout << "NULL" << endl;

  }
   cout << "==="<< endl << endl;
}


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork()
{
  if(head == nullptr || head -> next == nullptr);
  else{
  Country *current = head -> next, *last = head;
  while(current != nullptr)
  {
    //cout << "m";
    if(last == head) last -> next = nullptr;
    Country *trueNext = current -> next;
    current -> next = last;
    last = current;
    current = trueNext;
  }
  head = last;

}

}
