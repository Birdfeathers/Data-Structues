/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
  string choice = "0";
  string country1;
  string previousCountry;
  string message;
  CountryNetwork country;
  string Continue = "true";
  Country *myCountry;
  while(choice != "8")
  {
    displayMenu();
    getline( cin, choice);
    switch(stoi(choice)){
      case 1:
        country.loadDefaultSetup();
        country.printPath();
      break;
      case 2:
        country.printPath();
      break;
      case 3:
        cout << "Enter name of the country to receive the message:" << endl;
        getline( cin, country1);
        cout << "Enter the message to send:" << endl;
        getline( cin, message);
        country.transmitMsg(country1, message);
      break;
      case 4:
        cout << "Enter a new country name:" << endl;
        getline( cin, country1);
        cout << "Enter the previous country name (or First):" <<endl;
        Continue = "true";
        while(Continue == "true"){
        getline( cin, previousCountry);
        if(previousCountry == "First"){
           country.insertCountry(nullptr, country1);
           Continue = "false";
         }
        else{
          myCountry = country.searchNetwork(previousCountry);
          if(myCountry == NULL) cout << "INVALID country...Please enter a VALID previous country name:" << endl << endl;
          else{
            country.insertCountry(myCountry, country1);
            Continue = "false";
          }
        }
        }
        country.printPath();
      break;
      case 5:
        cout << "Enter a country name:" << endl;
        getline( cin, country1);
        country.deleteCountry(country1);
        country.printPath();
      break;
      case 6:
        country.reverseEntireNetwork();
        country.printPath();
      break;
      case 7:
        country.deleteEntireNetwork();
      break;
      case 8:
        cout << "Quitting... cleaning up path: " << endl;
        country.printPath();
        country.deleteEntireNetwork();
        if(country.isEmpty()) cout << "Path cleaned" << endl;
        else cout << "Error: Path NOT cleaned" << endl;
        cout << "Goodbye!" << endl;
      break;
    }
  }
}

/*
 * Purpose: displays a menu with options
 */
void displayMenu()
{
  //  cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Delete Country " << endl;
    cout << " 6. Reverse Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
