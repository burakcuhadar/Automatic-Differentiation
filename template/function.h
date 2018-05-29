#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include "variable.h"

using namespace std;

/*
An abstract subclass of node class and represents the functions.
Due to the different functionality, we have variable and function classes.
*/
class Function : public Node{
    
public:

    // represents the list of variables that are inputs of this function
    vector<Variable *> inputs;

    // represents the output variable of the function.
    Variable * output;

    Function(int _id, string _name=""); // custom constructor

    ~Function(); // destructor
    
    // adds given variable as an input of this function
    void addInput(Variable *input);

    // sets the output variable of the function
    void setOutput(Variable *_output);

    // following two functions are inherited features from node class
    vector<Node *> getIncomings();
    vector<Node *> getOutgoings();
    
    // following two functions will be implemented by the subclasses of Function class

    // performs forward pass and sets the value of output variable
    virtual void doForward() = 0;

    // performs backward pass and sets the derivative values of the input variables
    virtual void doBackward() = 0; 

};

/*
Subclass of function class that provides forward and backward pass functionalities 
for multiplication
*/
class Multiplication : public Function{
public:
    Multiplication(int _id, string _name="");
    void doForward();
    void doBackward();
};

/*
Subclass of function class that provides forward and backward pass functionalities 
for addition
*/
class Addition : public Function{
public:
    Addition(int _id, string _name="");
    void doForward();
    void doBackward();
};

/*
Subclass of function class that provides forward and backward pass functionalities 
for sine
*/
class Sine : public Function{
public:
    Sine(int _id, string _name="");
    void doForward();
    void doBackward();
};

#endif // VARIABLE