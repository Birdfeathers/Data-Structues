#include<iostream>
using namespace std;
#include <string>
#include <fstream>
#include <iomanip>

struct wordItem {
string word;
int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
  ifstream ignore;
  ignore.open(ignoreWordFileName);
  if(!ignore.is_open()) cout << "Failed to open " << ignoreWordFileName << endl;
  string line;
  for(int i = 0; getline(ignore, line); i++)
  {
    ignoreWords[i] = line;
  }
  ignore.close();

}

bool isStopWord(string word, string ignoreWords[])
{
  for(int i = 0; i < 50; i++)
  {
    if(ignoreWords[i] == word) return true;
  }
  return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
  int total = 0;
  for(int i = 0; i < length; i++)
  {
    total += uniqueWords[i].count;
  }
  return total;
}
int insertIntoSortedArray(wordItem myArray[], int numEntries, wordItem newValue)
{
  for(int i = 0; i < numEntries; i++)
  {
    if(myArray[i].count > newValue.count)
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

void arraySort(wordItem uniqueWords[], int length)
{
  wordItem temp[length];
  for(int i = 0; i < length; i++)
  {
    insertIntoSortedArray(temp, i, uniqueWords[i]);
  }
  for(int j = 0; j < length; j++)
  {
    uniqueWords[j] = temp[length - 1 -j];
  }
}

void printTopN(wordItem uniqueWords[], int topN, int totalNumWords)
{
  for(int i = 0; i < topN; i++)
  {
    float count = uniqueWords[i].count;
    float prob = count / totalNumWords;
    cout << fixed << setprecision(4) << prob << " - " << uniqueWords[i].word << endl;
  }
}

int main ( int argc, char const *argv[])
{
  if(argc != 4){
    cout <<"Usage: Assignment2Solution <number of words><inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
    return 0;
  }
  string ignoreWords[50];
  getStopWords(argv[3], ignoreWords);
  ifstream book;
  book.open(argv[2]);
  wordItem *uniqueWords = new wordItem[100];
  int size = 0, max = 100, doubles = 0;
  string Word;
  while(book >> Word)
  {
    if(!isStopWord(Word,ignoreWords)){
    bool repeat = false;
    for(int i = 0; i < size; i++)
    {
      if(uniqueWords[i].word == Word){
       uniqueWords[i].count++;
      repeat = true;
    }
  }
    if(!repeat)
    {
      if(size == max)
      {
        max = 2 * max;
        wordItem* temp = new wordItem[max];
        for(int i = 0; i < (max/2); i++) temp[i] = uniqueWords[i];
        delete [] uniqueWords;
        uniqueWords = temp;
        temp = NULL;
        doubles++;
      }
        uniqueWords[size].word = Word;
        uniqueWords[size].count = 1;
        size++;
    }

  }
  }
  book.close();
  float totalNumWords = getTotalNumberNonStopWords(uniqueWords, size);
  arraySort(uniqueWords, size);
  cout << "Array doubled: " << doubles << endl << "#" <<endl;
  cout << "Unique non-common words: " << size << endl << "#" <<endl;
  cout << "Total non-common words: " << totalNumWords << endl << "#" <<endl;
  cout << "Probabilities of top "<<argv[1] <<" most frequent words" << endl << "---------------------------------------" <<endl;
  printTopN(uniqueWords, stoi(argv[1]), totalNumWords);
  return 0;
}
