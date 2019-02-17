#include<iostream>
using namespace std;
#include <string>
#include <fstream>
struct Distance
{
int feet ;
int inch ;
};
int main()
{
Distance d;
// declare a pointer to Distance variable
Distance* ptr;
d.feet=8;
d.inch=6;
//store the address of d in p
ptr = &d;
cout<<"Distance="<< ptr->feet << "ft"<< ptr->inch << "inches";
return 0;
}
