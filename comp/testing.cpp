#include<iostream>
using namespace std;
#include <string>
#include <fstream>

int test()
{
  int a[] = {1, 3, 5, 7};

  cout <<   *a+2  << endl;
}

void reset( int *ip)
{
  ip = 0;
}
int test2()
{
  int i = 100;
  int *p = &i;
  reset (p);
  cout << "i :" << *p <<endl;
}

int main()
{
  test2();
}
