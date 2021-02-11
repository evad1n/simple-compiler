# Simple Compiler

A simple compiler made in C++

`make` and run with input files, similar to g++ and others.


3. Enhance your code to support the “&&” and “||” operators, as they work in C.  As with terms and factors, you should allow multiple AND and OR operators.  Enforce the following priorities on order of operations, from highest to lowest:
* /
+ -
< <= > >= == !=
&&
||
Follow the same pattern as before to get the priorities, and left to right order within a priority.  That is, enhance the grammar itself by adding two more layers to the existing three layers, and then write Parser methods to correspond to the grammar rules.
