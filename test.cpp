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
using namespace LargeNumbers;

// define your datatype here
typedef LargeFloat myType;

// convert from string to myType
myType convert(string s) {
    return myType(s);
}

// convert from myType to string
string toStr(myType m) {
    return m.toString();
}

// compute a factorial
myType myFactorial(int n);

// finds the next prime, bigger than n					
myType myPrime(myType n);

// finds d to the power of (positive) p					
myType myPow(double d, int p);

// finds (natural) logarithm of d				
myType myLog(double d);

// finds sinus of d						
myType mySin(double d);

// finds square root of d						
myType mySqrt(double d);

// finds a value of PI with n digits of precision (zeroes afterwards)						
myType myPi(int n);

// computes an average of n valus in an array 					
myType myAvg(myType *data, int n);

// search for a value in an array of n numbers and return an index		
int myFind(myType *data, int n, myType value);

// sorts data in an array of n numbers by (optimized) bubble sort algorithm
void mySort(myType *data, int n);

myType myFactorial(int n) {
    return myType(LargeNumbers::factorial(LargeInt(n)));
}

myType myPrime(myType n) {
    n.floor();

    std::string decimal = n.toString();
    decimal.erase(decimal.end() - 2, decimal.end());
    LargeInt integer(decimal);

    return myType(LargeNumbers::nextPrime(integer));
}

myType myPow(double d, int p) {
    return LargeNumbers::pow(myType(d), LargeInt(p));
}

myType myLog(double d) {
    return LargeNumbers::ln(LargeFloat(d));
}

myType mySin(double d) {
    return myType("0.0");
}

myType mySqrt(double d) {
    return myType("0.0");
}

myType myPi(int n) {
    return myType("0.0");
}

myType myAvg(myType *data, int n) {
    return myType("0.0");
}

int myFind(myType *data, int n, myType value) {
    for (int i = 0; i < n; ++i) {
        if (data[i] == value) {
            return i;
        }
    }

    return -1;
}

bool compare(const myType &a, const myType &b) {
    return a <= b;
}

void mySort(myType *data, int n) {
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
        myType *data = NULL;
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
                data = new myType[n];
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
                data = new myType[n];
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
                data = new myType[n];
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
