/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer PC;
	string response = "0", Item, num;
	int numItems;
	string* queue = PC.getQueue();
	while(response != "3")
	{
		cout << "*----------------------------------------*" << endl;
		menu();
		cout << "*----------------------------------------*" << endl;
		getline(cin, response);
		switch(stoi(response)){
			case 1:
				cout << "Enter the number of items to be produced:" << endl;
				getline(cin, num);
				numItems = stoi(num);
				for(int i = 0; i < numItems; i++)
				{
					cout << "Item" << i + 1 << ":" << endl;
					getline(cin, Item);
					PC.enqueue(Item);
					//if(isFull()) i = numItems;
				}
				break;
			case 2:
				cout << "Enter the number of items to be consumed:" << endl;
				getline(cin, num);
				numItems = stoi(num);
				for(int i = 0; i < numItems; i++)
				{
					if(PC.isEmpty()){
						i = numItems;
						cout<<"No more items to consume from queue"<< endl;
					}
					else{
						cout << "Consumed: ";
						cout << *(queue + PC.getQueueFront())<< endl;
						PC.dequeue();
					 }
				}
				break;
			case 3:
				cout << "Number of items in the queue:" << PC.queueSize();
				break;
			case 4:
				cout << PC.peek() << endl;
				break;
			case 5:
				cout << "size" << PC.queueSize() <<endl;
				break;
		}
	}

}
