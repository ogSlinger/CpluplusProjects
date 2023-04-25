#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

void swapNumbers (int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(vector<int>& arr) {
    for (int i = 0; i < (arr.size() - 1); i++) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[minIndex] > arr[j]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swapNumbers(&arr[minIndex], &arr[i]);
        }
    }
}

void bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < (arr.size() - i - 1); j++) {
            if (arr[j] > arr[j + 1]) {
                swapNumbers(&arr[j], &arr[j + 1]);
            }
        }
    }
}

bool isSorted(int element, int currentIndex, vector<int>& arr) {
    for (int i = currentIndex; i > 0; i--) {
        if (element <= arr[i-1]) {
            return true;
        }
    }
    return false;    
}

void mySort(vector<int>& arr, int size) {
    int numCount = 0;
    int rank = 0;
    int index = 0;
    vector<int> tempArr(size);

    for (int i = 0; i < size; i++){
        if (isSorted(arr[i], i, arr)) {
            continue;
        }

        else {
            for (int j = i; j < size; j++) {
                if (arr[i] < arr[j]) {
                    continue;
                }
                else if (arr[i] == arr[j]) {
                    numCount++;
                }
                else if (arr[i] > arr[j]) {
                    rank++;
                }
            }
        }

        while (numCount > 0) {
            tempArr[rank] = arr[i];
            numCount--;
            rank++;
        }
        rank = i;        
    }
    arr = tempArr;
}


void myImprovedSort(vector<int>& arr, int size) {
    int numCount = 0;
    int rank = 0;
    int index = 0;
    vector<vector<int>> instructions(size, vector<int> (3)); //0 is the element, 1 is the numCount, 2 is the rank

    for (int i = 0; i < size; i++){
        if (isSorted(arr[i], i, arr)) {
            continue;
        }

        else {
            instructions[i][0] = arr[i];
            for (int j = i; j < size; j++) {
                if (arr[i] < arr[j]) {
                    continue;
                }
                else if (arr[i] == arr[j]) {
                    instructions[i][1]++;
                }
                else if (arr[i] > arr[j]) {
                    instructions[i][2]++;
                }
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = instructions[i][2]; instructions[i][1] > 0; j--) {
            arr[j] = instructions[i][0];
        }
    }
}


void startTest(vector<int>& arr, int choice) {
    chrono::high_resolution_clock::time_point start_time, end_time;
    chrono::duration<double> duration;
    start_time = chrono::high_resolution_clock::now();

    if (choice = 0) {
        mySort(arr, arr.size());
    } else if (choice = 1) {
        bubbleSort(arr);
    } else if (choice = 2) {
        myImprovedSort(arr, arr.size());
    } else {
        selectionSort(arr);
    }

    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
    double seconds = duration.count();

    cout <<"Duration: " <<seconds <<endl;
}

void printVector(vector<int>& vec) {
    cout <<"Vector: " <<endl;
    for (int i = 0; i < vec.size(); i++) {
        cout <<vec[i] <<" ";
    }
    cout <<endl;
}

int main() {
    random_device rd;                           //Rand Stuff
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 100);

    int vectorSize = 20000;                     //Vector Array Size
    
    vector<int> arr(vectorSize);                //Test Vectors
    vector<int> arrTwo(vectorSize);
    vector<int> arrThree(vectorSize);
    vector<int> arrFour(vectorSize);

    for (int i = 0; i < vectorSize; i++) {      //Generate the first vector
        arr[i] = dis(gen);
    }

    arrTwo = arr;                               //Make all vectors the same
    arrThree = arr;
    arrFour = arr;

    cout << "My algorithm on " <<arr.size() <<" random ints: " <<endl;              //Running tests on each vector
    startTest(arr, 0);
    cout << "Bubble Sort on " <<arrTwo.size() <<" of the same ints: " <<endl;
    startTest(arrTwo, 1);
    cout << "My algorithm #2 on " <<arrThree.size() <<" of the same ints: " <<endl;
    startTest(arrThree, 2);
    cout << "Selection Sort on " <<arrThree.size() <<" of the same ints: " <<endl;
    startTest(arrFour, 3);

    return 0;
}
    
