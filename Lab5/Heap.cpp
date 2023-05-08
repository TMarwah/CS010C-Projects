#include "Heap.h"
#include <stdexcept>
//default constructor
Heap::Heap()
: numItems(0){}

void Heap::enqueue(PrintJob* job){
    if (numItems < MAX_HEAP_SIZE){
        if(numItems == 0){
            arr[numItems] = job;
            ++numItems;
        }
        else{
            int currItem = numItems; //initialize location to last job
            //while not at first item, keep halving until priority is in order (find location for new printjob insert)
            while (currItem > 0 && arr[(currItem -1) / 2]->getPriority() < job->getPriority() ){
                //last item becomes val of mid
                arr[currItem] = arr[(currItem-1)/ 2];
                currItem = (currItem-1) / 2;
            }
            arr[currItem] = job; //place job into location with proper priority
        }
    }
    else{
        //throw exception for full queue
        throw overflow_error("Overflow Error: Enqeue attempted on full queue");
    }
}

void Heap::dequeue(){
    if(numItems == 0){
        throw underflow_error("Underflow Error: Deqeue attempted on empty queue");
    }

    if (numItems > 2 && arr[1]->getPriority() < arr[numItems-1]->getPriority() && arr[2]->getPriority() < arr[numItems-1]->getPriority()){
        //first item swaps for dequeue item
        arr[0] = arr[numItems-1];
        --numItems;
    }
    else{
        trickleDown(0);
        --numItems;
    }
}