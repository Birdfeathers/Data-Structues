#include<iostream>
using namespace std;
#include <string>
#include <fstream>

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


struct User {
string username;
float gpa;
int age;
};

void addUser(User users[], string _username, float _gpa, int _age, int length)
{
  User newUser;
  newUser.username = _username;
  newUser.gpa = _gpa;
  newUser.age = _age;
  users[length] = newUser;
}

void printList(const User users[], int length)
{
  for(int i = 0; i < length; i++)
  {
    cout << users[i].username << " [" << users[i].gpa << "] age: " << users[i].age <<endl;
  }
}



int main ( int argc, char const *argv[])
{
  User students[100];
  ifstream read;
  read.open(argv[1]);
  if(!read.is_open()) cout << "Failed to open the file." <<endl;
  string line;
  int numadded = 0;
  while(getline(read,line))
  {
    string arr[3];
    split(line, ',', arr, 3);
    students[numadded].username = arr[0];
    students[numadded].gpa = stof(arr[1]);
    students[numadded].age = stoi(arr[2]);
    numadded++;
  }
  read.close();
  ofstream write;
  write.open(argv[2]);
  for(int i = 0; i < numadded; i++)
  {
    if(students[i].gpa > stof(argv[3]))
    {
      write << students[i].username << "," << students[i].gpa << "," << students[i].age <<endl;
    }
  }
  write.close();
  printList(students, numadded);
}
