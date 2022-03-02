# repo-Team7
Team7 (Golemo, Huynh, Ly, Vang)
The purpose of these documents is to provide detailed documentation of the Aegis program that operates on the two types of voting systems, namely Open Party Listing(OPL) and Instant Runoff(IR). This software will take in a csv file and determine the outcome based on the two types of voting systems (OPL or IR). This documentation is provided to show the structure, classes and functions used in order to run a voting system.

## Running Aegis
The program Aegis can be built with a provided makefile is the src folder

$ make

from within the folder where the executable is built usage of Aegis is done using:

$ ./Aegis <file_name> 

## Running Unit Tests
To run the unit tests, enter the "testing" directory. To compile, run cmake on the provided CMakeList.txt file. If there are more than one files, simply include their file names in the terminal. 
For example, if there are three files, you would do the following: $ ./Aegis <file_name> <file_name> <file_name> 

$ cmake CMakeLists.txt

then run make to create the executable runTests, then run runTests to run the tests.

$ make<br />
$ ./runTests
