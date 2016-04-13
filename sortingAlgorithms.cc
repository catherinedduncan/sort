#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
// strategy:  pick a pivot point, arrange elements higher than pivot point after in array and elements lower 
// than pivot point before, then recursively call quicksort on the pre and post array slices.

std::vector<int> quickSort(std::vector<int> toSort){
	int leftIndex = 0;
	int pivotIndex = toSort.size() - 1;
	int tmp = 0;
	// while we have not met in the middle, continue sorting
	while(leftIndex != pivotIndex){
		// test if this greedy optimization saves more time on average than it costs
		if(toSort[pivotIndex] <= toSort[pivotIndex-1]){
			tmp = toSort[pivotIndex-1];
			toSort[pivotIndex-1] = toSort[pivotIndex];
			toSort[pivotIndex] = tmp;
			pivotIndex--;
		} else if(toSort[pivotIndex] < toSort[leftIndex]){
			tmp = toSort[pivotIndex-1];
			toSort[pivotIndex-1] = toSort[leftIndex];
			toSort[leftIndex] = tmp;
			tmp = toSort[pivotIndex];
			toSort[pivotIndex] = toSort[pivotIndex-1];
			toSort[pivotIndex-1] = tmp;
			pivotIndex--;
		} else {
			leftIndex++;
		}
	}
	// now the list is partitioned, recursively call quickSort on the pre and post slices;
	std::vector<int> result;
	std::vector<int> leftPartition;
	std::vector<int> rightPartition;
	for(unsigned i=0; i<pivotIndex; i++){
		leftPartition.push_back(toSort[i]);
	}
	if(leftPartition.size() > 1){ leftPartition = quickSort(leftPartition); }
	
	for(unsigned i=pivotIndex+1; i<toSort.size(); i++){
		rightPartition.push_back(toSort[i]);
	}
	if(rightPartition.size() > 1){ rightPartition = quickSort(rightPartition); }

	// now combine sorted results and return
	leftPartition.push_back(toSort[pivotIndex]);
	leftPartition.insert( leftPartition.end(), rightPartition.begin(), rightPartition.end() );
	return leftPartition;
}

// Strategy: divide toSort into half, repeat until you reach size 1, then return, 
// take advantage of fact that sub-partitions are already sorted to merge the sorted lists together and return.
std::vector<int> mergeSort(std::vector<int> toSort){
	// note, this will be floored automatically by being cast to an int
	int midPoint = toSort.size() / 2;  
	// sort each half of the list recursively
	std::vector<int> leftPartition;
	for(unsigned i=0; i<midPoint; i++){ leftPartition.push_back(toSort[i]); }
	std::vector<int> rightPartition;
	for(unsigned i=midPoint; i<toSort.size(); i++){ rightPartition.push_back(toSort[i]); }
	if(leftPartition.size() > 1){ leftPartition = mergeSort(leftPartition); }
	if(rightPartition.size() > 1){ rightPartition = mergeSort(rightPartition); };
	// initialize return value array
	std::vector<int> result;
	int leftSortIndex = 0;
	int rightSortIndex = 0;
	int index = 0;
	while(index < toSort.size()){
		if(leftSortIndex == leftPartition.size()){
			result.push_back(rightPartition[rightSortIndex]);
			index++;
			rightSortIndex++;
		} else if(rightSortIndex == rightPartition.size()){
			result.push_back(leftPartition[leftSortIndex]);
			index++;
			leftSortIndex++;
		} else{
			if(leftPartition[leftSortIndex] < rightPartition[rightSortIndex]){
				result.push_back(leftPartition[leftSortIndex]);
				leftSortIndex++;
			} else{
				result.push_back(rightPartition[rightSortIndex]);
				rightSortIndex++;
			}
			index++;
		}
	}
	return result;
}

// Strategy:  continually iterate through list, sorting elements in pairs until entire list is sorted.
std::vector<int> bubbleSort(std::vector<int> toSort){
	int index = 0;
	bool foundSwap = false;
	// if we have reached the end of the list and not found a swap, 
	// that means the list has been sorted, we should return at this juncture.
	while((index != toSort.size()) || foundSwap){
		// if we've reached the end of the list, but we found a swap, 
		// we should reset the index to 0 to begin again.	
		if(index == toSort.size()){ index = 0; foundSwap = false; }		
		if(toSort[index] > toSort[index+1]){
			foundSwap = true;
			int tmp = toSort[index+1];
			toSort[index+1] = toSort[index];
			toSort[index] = tmp;
		}
		index++;
	} 
	return toSort;
}

// utility function for generating arbitrary length unsorted lists, used for testing efficiency of sorting algorithms.
std::vector<int> generateUnsortedList(int length){
	std::vector<int> result (length);
	for(unsigned i=0; i<length; i++){
		result[i] = rand() % 100 + 1;
	}
	return result;
}


int main(){
	srand(time(NULL));
	int listSize = 11;
	
	// bubbleSort!
	std::cout << "Bubble sort: \n";

	std::vector<int> toSort = generateUnsortedList(listSize);
	std::cout << "Unsorted List is: [ ";
	for(unsigned i=0; i<listSize; i++){	
		std::cout << toSort[i];
		std::cout << " ";
	}
	std::cout << " ]\n";

	// sorting algorithm goes here!
	toSort = bubbleSort(toSort);

	std::cout << "Sorted List is:   [ ";
	for(unsigned i=0; i<listSize; i++){	
		std::cout << toSort[i];
		std::cout << " ";
	}
	std::cout << " ]\n";

	// mergeSort!
	std::cout << "Merge sort: \n";

	toSort = generateUnsortedList(listSize);
	std::cout << "Unsorted List is: [ ";
	for(unsigned i=0; i<listSize; i++){	
		std::cout << toSort[i];
		std::cout << " ";
	}
	std::cout << " ]\n";

	// sorting algorithm goes here!
	toSort = mergeSort(toSort);

	std::cout << "Sorted List is:   [ ";
	for(unsigned i=0; i<listSize; i++){	
		std::cout << toSort[i];
		std::cout << " ";
	}
	std::cout << " ]\n";
	
	// quickSort!
	std::cout << "Quick sort: \n";

	toSort = generateUnsortedList(listSize);
	std::cout << "Unsorted List is: [ ";
	for(unsigned i=0; i<listSize; i++){	
		std::cout << toSort[i];
		std::cout << " ";
	}
	std::cout << " ]\n";

	// sorting algorithm goes here!
	toSort = quickSort(toSort);

	std::cout << "Sorted List is:   [ ";
	for(unsigned i=0; i<listSize; i++){	
		std::cout << toSort[i];
		std::cout << " ";
	}
	std::cout << " ]\n";
	
	
}


