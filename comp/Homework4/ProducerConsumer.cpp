#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

ProducerConsumer :: ProducerConsumer()
{
  queueFront = -1;
  queueEnd = -1;
}

bool ProducerConsumer :: isEmpty()
{
  if(queueFront == -1) return true;
  return false;

}

bool ProducerConsumer :: isFull()
{
  if(queueFront == (queueEnd + 1)) return true;
  if(queueFront == 0 && queueEnd == SIZE -1) return true;
  return false;
}

void  ProducerConsumer :: enqueue(std::string player)
{
//   ➔ If the queue is not full, then add the item to the end of the queue and modify
// queueFront and/or queueEnd if appropriate, else print “Queue full, cannot add new
// item”
  if(isFull()) cout << "Queue full, cannot add new item" << endl;
  else{
    if(queueEnd == -1){
      queue[0] = player;
      queueFront = 0;
      queueEnd = 0;
    }
    else
    {
      if(queueEnd == (SIZE -1)){
        queue[0] = player;
        queueEnd = 0;
      }
      else {
        queue[queueEnd + 1] = player;
        queueEnd++;
      }
    }
  }

}

void ProducerConsumer :: dequeue()
{
//   ➔ Remove the first item from the queue if the queue is not empty and modify queueFront
// and/or queueEnd if appropriate. Otherwise print "Queue empty, cannot dequeue an
// item"
  if(isEmpty()) cout <<  "Queue empty, cannot dequeue an item" << endl;
  else{
    if(queueSize() == 1)
    {
      queueFront = -1;
      queueEnd = -1;
    }
    else if(queueFront == SIZE - 1) queueFront = 0;
    else queueFront++;
  }
}

int ProducerConsumer :: queueSize()
{
    //➔ Return the number of items in the queue
    if(isEmpty()) return 0;
    if(isFull()) return 20;
    if(queueEnd >= queueFront) return queueEnd - queueFront + 1;
    return ((SIZE - queueFront) + queueEnd) + 1;

}

std::string ProducerConsumer :: peek()
{
//   ➔ If the queue is empty then print “Queue empty, cannot peek” and return an empty string.
  if(isEmpty())
  {
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
// Otherwise, return the frontmost item in the queue
  return queue[queueFront];
}
