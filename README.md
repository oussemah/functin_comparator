# Introduction

A command line tool to comapre 2 functions in 2 different (or same) files.

The tool detects automatically the start and end of the function code in the given file.

The output will be like follows (with colored output) :

1::145 -> int a = 5;
2::134 -> int a = 7;

1::163 -> call_function(a,b,c,d);
2::163 -> call_function(a,b,c, 2*d);

# Building

To build the tool just call :
 $ make clean all
 
# Run
A sample execution call can be :
 $ comparator function_a file_1 function_b file_2

# ToDo
The tool can still evolve to support command line parameters for verbosity level, [not ]ignoring white spaces
and indentation differences, comparing 2 functions in the same file with same functino name (in case this scenario is useful).

# License
MIT

# Author
Oussema HARBI <oussema.elharbi@gmail.com>
