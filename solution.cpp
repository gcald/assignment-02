/* ----------------------------------------------------------------------------
* Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
*                  2015 George Calderon <gcald@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

/**
* A program to read unsigned integers from a text file and separate them into
* two files, one for primes, another for composites.
*/


#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

/**
* Find the maximum unsigned integer in `infilename`.
*
* Arguments:
* - `infilename`: A string representing the file path to open.
*     - Note: Since the string will not be changed, we declare it `const`.
*       Since strings are objects (and therefore larger than fundamental
*       types), we avoid copying it by passing it by reference.
*
* Returns:
* - The maximum integer, or `-1` on error.
*     - Note: It would be better style in C++ to throw an exception, but we
*       haven't learned about those yet.
*/
int find_max(const string& infilename);

/**
* Mark all prime indices in `primes` as `true` and all others as `false` using
* the Sieve of Eratosthenes algorithm.
*
* Arguments:
* - `size`: The size of (the number of elements in) the array.
* - `primes`: An array of boolean values.
*
* Notes:
* - The number `2` is the smallest prime.
* - When arrays are passed to functions, they decay into pointers (even though
*   arrays and pointers are not the same thing).  Thus what this function is
*   actually receiving is a pointer to the first element of the array `primes`
*   in `main()` (it doesn't make much difference for how we're using it in
*   this function, but the distinction is important).  This pointer is passed
*   by value, but the data inside the array is not passed at all: we access it
*   through the pointer.
* - It might be better to return the array from the function rather than pass
*   the array and modify it, but the syntax is relatively uncommon, and might
*   be confusing.
*/
void sieve(const int size, bool primes[]);

/**
* Read numbers from `infilename`, and if they are prime, output them to
* `outfilename`, separated by newlines.
*
* Arguments:
* - `size`: The size of (the number of elements in) the array.
* - `primes`: An array of boolean values, with each element set to `true` if
*   its index is prime, and `false` otherwise.
* - `infilename`: A string representing the file path to read from.
* - `outfilename`: A string representing the file path to write to.
*
* Returns:
* - 0 on success, or -1 on error.
*/
int write_primes(const int size,
	bool primes[],
	const string& infilename,
	const string& outfilename);

/**
* Read numbers from `infilename`, and if they are composite, output them to
* `outfilename`, separated by newlines.
*
* Arguments:
* - `size`: The size of (the number of elements in) the array.
* - `primes`: An array of boolean values, with each element set to `true` if
*   its index is prime, and `false` otherwise.
* - `infilename`: A string representing the file path to read from.
* - `outfilename`: A string representing the file path to write to.
*
* Returns:
* - 0 on success, or -1 on error.
*/
int write_composites(const int size,
	bool primes[],
	const string& infilename,
	const string& outfilename);

// ----------------------------------------------------------------------------

int main() {
	int max = find_max("input.txt");
	cout << max;
	if (max == -1) {
		cout << "ERROR in `find_max()`" << endl;
		return 1;  // error
	}

	bool * primes = (bool *)malloc(sizeof(bool) * (max + 1));;
	sieve(max + 1, primes);

	int ret;  // for storing return values, to check for error codes
	ret = write_primes(max + 1, primes, "input.txt", "primes.txt");
	if (ret == -1) {
		cout << "ERROR in `write_primes()`" << endl;
		return 1;  // error
	}
	//
	ret = write_composites(max + 1, primes, "input.txt", "composites.txt");
	if (ret == -1) {
		cout << "ERROR in `write_composites()`" << endl;
		return 1;  // error
	}
	system("pause");
	return 0;  // success
}

// ----------------------------------------------------------------------------

// TODO: write prototyped functions

	int find_max(const string& infilename) {
	int a = 0; //declares a return variable
	ifstream file;
	file.open(infilename);
	
	if (file.good() != 0) //check if the file is still good
		while (file.good()){
			int b;
			file >> b; //takes input from file and puts into an int
			if (a < b) //if the inputed int is greater than a 
				a = b;
		}
	else a = -1;
	file.close();
	return a;
}

void sieve(const int size, bool primes[]){
	for (int i = 0; i < size; i++) {
		if (i == 0 || i == 1)
			primes[i] = false; //0 and 1 not considered a prime number
		else 
			primes[i] = true;
	}
	
	for (int i = 2; i < size -1; i++) { //find non-prime numbers between size
		for (int k = i*i; k < size; k += i)
			primes[k] = false;
		cout << primes[i] << endl;
	}
}

int write_primes(const int size,
	bool primes[],
	const string& infilename,
	const string& outfilename){
	int a = 0;
	int b;
	ifstream inFile;
	ofstream outFile;
	inFile.open(infilename);
	outFile.open(outfilename);
	
	if (inFile.good() != 0 && outFile.good() != 0) //checks to see if file work
		for (int i = 0; i < size; i++){ //compares prime numbers to input 
			//numbers
			inFile >> b;
			if (primes[i] == true)
				if (i = b)
					outFile << b << endl; //outputs it
		}
	else a = -1;
	inFile.close();
	outFile.close();
	return a;
}

int write_composites(const int size,
	bool primes[],
	const string& infilename,
	const string& outfilename){
	int a = 0;
	int b;
	ifstream inFile;
	ofstream outFile;
	inFile.open(infilename);
	outFile.open(outfilename);

	if (inFile.good() != 0 && outFile.good() != 0)
		for (int i = 0; i < size; i++) {
			inFile >> b;
			if (primes[i] == false) //if number is not prime, output it 
				if(i = b)
					outFile << b << endl;
		}
	else a = -1;
	inFile.close();
	outFile.close();
	return a;
}
