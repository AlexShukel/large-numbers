#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>
#include "LargeMath.h"
#include "bubbleSort.h"

// other includes and definitions

/* YOUR CODE HERE */

class NotImplementedException {
};

using namespace std;

// define your datatype here
typedef LargeNumbers::LargeFloat myFloatType;
typedef LargeNumbers::LargeInt myIntType;

// convert from string to myFloatType
myFloatType convert(string s) {
    return myFloatType(s);
}

// convert from myFloatType to string
string toStr(myFloatType m) {
    return m.toString();
}

// compute a factorial
myFloatType myFactorial(int n);

// finds the next prime, bigger than n					
myFloatType myPrime(myFloatType n);

// finds d to the power of (positive) p					
myFloatType myPow(double d, int p);

// finds (natural) logarithm of d				
myFloatType myLog(double d);

// finds sinus of d						
myFloatType mySin(double d);

// finds square root of d						
myFloatType mySqrt(double d);

// finds a value of PI with n digits of precision (zeroes afterwards)						
myFloatType myPi(int n);

// computes an average of n valus in an array 					
myFloatType myAvg(myFloatType *data, int n);

// search for a value in an array of n numbers and return an index		
int myFind(myFloatType *data, int n, myFloatType value);

// sorts data in an array of n numbers by (optimized) bubble sort algorithm
void mySort(myFloatType *data, int n);

myFloatType myFactorial(int n) {
    return myFloatType(LargeNumbers::factorial(myIntType(n)));
}

myFloatType myPrime(myFloatType n) {
    n.floor();

    std::string decimal = n.toString();
    decimal.erase(decimal.end() - 2, decimal.end());
    myIntType integer(decimal);

    return myFloatType(LargeNumbers::nextPrime(integer));
}

myFloatType myPow(double d, int p) {
    return myFloatType("0.0");
}

myFloatType myLog(double d) {
    return myFloatType("0.0");
}

myFloatType mySin(double d) {
    return myFloatType("0.0");
}

myFloatType mySqrt(double d) {
    return myFloatType("0.0");
}

myFloatType myPi(int n) {
    return myFloatType("0.0");
}

myFloatType myAvg(myFloatType *data, int n) {
    return myFloatType("0.0");
}

int myFind(myFloatType *data, int n, myFloatType value) {
    for (int i = 0; i < n; ++i) {
        if (data[i] == value) {
            return i;
        }
    }

    return -1;
}

bool compare(const myFloatType &a, const myFloatType &b) {
    return a <= b;
}

void mySort(myFloatType *data, int n) {
    bubbleSort(data, data + n, compare);
}

/* DO NOT MODIFY CODE BELOW */

int main() {
    while (1) {
        int x = -1;
        cin >> x;
        if (x == 0)
            break;
        string s;
        double d;
        int n;
        myFloatType *data = NULL;
        string output;
        switch (x) {
            case 1:
                cin >> n;
                cout << (output = toStr(myFactorial(n))) << endl;
                break;
            case 2:
                cin >> s;
                cout << (output = toStr(myPrime(convert(s)))) << endl;
                break;
            case 3:
                int p;
                cin >> d >> p;
                cout << (output = toStr(myPow(d, p))) << endl;
                break;
            case 4:
                cin >> d;
                cout << (output = toStr(myLog(d))) << endl;
                break;
            case 5:
                cin >> d;
                cout << (output = toStr(mySin(d))) << endl;
                break;
            case 6:
                cin >> d;
                cout << (output = toStr(mySqrt(d))) << endl;
                break;
            case 7:
                cin >> n;
                cout << (output = toStr(myPi(n))) << endl;
                break;
            case 8:
                cin >> n;
                data = new myFloatType[n];
                for (int i = 0; i < n; ++i) {
                    string s;
                    cin >> s;
                    data[i] = convert(s);
                }
                cout << (output = toStr(myAvg(data, n))) << endl;
                delete[] data;
                break;
            case 9:
                cin >> n;
                data = new myFloatType[n];
                for (int i = 0; i < n; ++i) {
                    string s;
                    cin >> s;
                    data[i] = convert(s);
                }
                cin >> s;
                int f;
                cout << (f = myFind(data, n, convert(s))) << endl;
                delete[] data;
                break;
            case 10:
                cin >> n;
                data = new myFloatType[n];
                for (int i = 0; i < n; ++i) {
                    string s;
                    cin >> s;
                    data[i] = convert(s);
                }
                mySort(data, n);
                for (int i = 0; i < n; ++i) {
                    cout << (output = toStr(data[i])) << endl;
                }
                delete[] data;
                break;
        }
    }
    return 0;
}
