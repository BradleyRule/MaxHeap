#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

//declaring functions
int lChild(int);
int rChild(int);
int parent(int);
void swap(int[], int, int);
void maxHeap(int[], int);
void heapify(int[], int, int);
void heapSort(int[], int);


int main(){

  //input variable
  char input[500];
  //table to store data
  int table[100];
  //gets the number input
  int numberInt = 0;
  int count = 0;
  //keeps track of how many numbers were entered
  int size = 0;

  cout << "Would you like to input numbers manually or using a file? (enter: 'manual' or 'file')" << endl;
  // get user input  
  cin.get(input, 500);
  cin.get();
  
  if(strcmp(input, "manual") == 0){//if the user wants a manual input
    cout << "Enter one number at a time. You can enter up to 100 numbers between 0 - 1000. When done entering numbers enter 99999." << endl;
    //repeatedly get numbers and put them into the table
    cin >> numberInt;
    while (numberInt != 99999){
      //store the number in the table
      table[size] = numberInt;
      //update the size of the table
      size++;
      cin >> numberInt;
    }
    
  }
  else if(strcmp(input, "file") == 0){//if the user chooses a file input
    
    cout << "Enter the name of the file. (example.txt)" << endl;
    //get the name of the file
    cin.get(input, 500);
    cin.get();
    //create a file object that accesses the file name entered
    ifstream file(input);

    if(file.is_open()){//open the file
      while(!file.eof()){//while the end of the file has not been reached
	//add the next number to the table
	file >> table[size];
	//update the size of the table
	size++;
      }
      //close the file
      file.close();
    }
  }
  else {
    return 0;
  }

  //set size to be one less (table starts at 0 not 1)
  size = size-1;
  //organie the table into a max heap
  maxHeap(table, size);
  //sort the table from least to greatest 
  heapSort(table, size);
  //print out the numbers in order
  for(int i = size; i >= 0; i--){
    cout << table[i] << " ";
  }

  


  
  return 0;
}

//returns the left child of parent index
int lChild(int index){
  return (2*index+1);
}

//returns the right child of parent index
int rChild(int index){
  return (2*index+2);
}

//returns the parent of the child index
int parent(int index){
  return ((index - 1)/2);
}

//swaps any to indexes
void swap(int table[], int pindex, int cindex){
  int temp = table[pindex];
  table[pindex] = table[cindex];
  table[cindex] = temp;
}

//creates initial max heap
void maxHeap(int table[], int size){
  //starts at the last left most parent
  int lastParent = floor(size/2);
  for (int i = lastParent; i >= 0; i--){
    //go through all parents and call heapify
    heapify(table, i, size);
  }
}

//checks children and decides if they should swap with parent as well as wich child to switch
void heapify(int table[], int index, int size){
  //this keeps track of the index storing with the largest number (parent is set to largest at the start)
  int largest = index;
  if(table[lChild(index)] > table[index] && lChild(index) <= size){//if lChild has a greater value than the parent and is in the array
    //set left child as largest
    largest = lChild(index);
  }
  //if the right child is larger than the current largest index
  if(table[rChild(index)] > table[largest] && rChild(index) <= size){
    //set right child as largest
    largest = rChild(index);
  }
  if(largest != index) {//if the parent is not the largest
    //swap the parent value with the largest of the children
    swap(table, index, largest);
    //heapify the children of the child that was swapped
    heapify(table, largest, size);
  }
}

//this code will remove the highest value and then reorganize the max heap repeatedly to organize the numbers
void heapSort(int table[], int size){
  for (int i = size; i > 0; i--){
    //move the highest value out of the array
    swap(table, 0, i);
    //heapify to correct for errors
    heapify(table, 0, i-1);
  }
}
