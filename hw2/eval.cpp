//
//  main.cpp
//  hw2-eval2
//
//  Created by Aditya Pimplaskar on 2/1/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include "Set.h"
#include <cassert>
using namespace std;

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result);

// Evaluate a boolean expression
//   If infix is a syntactically valid infix boolean expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values sets), then postfix is set to the postfix
//   form of the expression.  If not, postfix might or might not be
//   changed, result is unchanged, and the function returns 1.
//
//   If infix is a syntactically valid infix boolean expression whose
//   only operands are single lower case letters:
//
//      If every operand letter in the expression appears in either
//      trueValues or falseValues but not both, then result is set to the
//      result of evaluating the expression (using for each letter in the
//      expression the value true if that letter appears in trueValues or
//      false if that letter appears in false values) and the function
//      returns 0.
//
//      Otherwise, result is unchanged and the value the function returns
//      depends on these two conditions:
//        at least one letter in the expression is in neither the
//            trueValues nor the falseValues sets; and
//        at least one letter in the expression is in both the
//            trueValues and the falseValues set.
//      If only the first condition holds, the function returns 2; if
//      only the second holds, the function returns 3.  If both hold
//      the function returns either 2 or 3 (and the function is not
//      required to return the same one if called another time with the
//      same arguments).

bool isValid(string infix); //checks for validity of infix statement

bool precedence(char o1, char o2); //checks operator precedence

void convert(string infix, string &postfix); //converts
/*
Initialize postfix to empty
Initialize the operator stack to empty
For each character ch in the infix string
 Switch (ch)
    case operand:
        append ch to end of postfix
        break
    case '(':
        push ch onto the operator stack
        break
    case ')':
        // pop stack until matching '('
        While stack top is not '('
            append the stack top to postfix
            pop the stack
        pop the stack  // remove the '('
        break
    case operator:
        While the stack is not empty and the stack top is not '('
        and precedence of ch <= precedence of stack top
            append the stack top to postfix
            pop the stack
        push ch onto the stack
        break
While the stack is not empty
append the stack top to postfix
pop the stack
 */

bool evalPostFix(string postfix); //evaluates the post fix expression
/*
 Initialize the operand stack to empty
 For each character ch in the postfix string
    if ch is an operand
        push the value that ch represents onto the operand stack
    else // ch is a binary operator
        set operand2 to the top of the operand stack
        pop the stack
        set operand1 to the top of the operand stack
        pop the stack
        apply the operation that ch represents to operand1 and operand2, and push the result onto the stack
 When the loop is finished, the operand stack will contain one item, the result of evaluating the expression
*/


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result){
    
    if (!isValid(infix)){ return 1; }
    if (infix == ""){return 1;}
    
    convert(infix, postfix); //now postfix works
    
    stack<char> operand;
    stack<bool> b_operand;
    
    string noSpaces = ""; //avoid annoying spaces
    for (int i = 0; i < postfix.size(); i++){
        if (postfix[i] != ' '){ noSpaces += postfix[i]; }
    }
    
    postfix = noSpaces;
    
    
    //char operand2;
    //char operand1;
    bool b_operand2;
    bool b_operand1;
    bool b_operand0;
    
    for (int j = 0; j < noSpaces.size(); j++){
        switch(noSpaces[j]){
            case '!':
                b_operand0 = b_operand.top();
                b_operand.pop();
                //operand.pop();
                b_operand.push(!b_operand0);
                break;
                
            case '|':
            case '&':
                b_operand2 = b_operand.top();
                b_operand.pop();
                //operand.pop();
                b_operand1 = b_operand.top();
                b_operand.pop();
                //operand.pop();
                
                //now apply operator
                if (noSpaces[j] == '|'){ b_operand.push(b_operand1 || b_operand2); }
                else if (noSpaces[j] == '&') { b_operand.push(b_operand1 && b_operand2); }
                break;
                
                
            default:
                operand.push(noSpaces[j]);
                //if (!trueValues.contains(noSpaces[j]) && !trueValues.contains(noSpaces[j])){};
                if(trueValues.contains(noSpaces[j]) && falseValues.contains(noSpaces[j])) { return 3; }
                if(!trueValues.contains(noSpaces[j]) && !falseValues.contains(noSpaces[j])) { return 2; }
                
                if(trueValues.contains(noSpaces[j])){ b_operand.push(true); }
                else if (falseValues.contains(noSpaces[j])) { b_operand.push(false); }
                break;
        }
    }
    result = b_operand.top();
    
    return 0;
}


bool isValid(string infix){
    string noSpaces;
    for (int i = 0; i < infix.size(); i++){
        if (infix[i] != ' '){noSpaces += infix[i];} //get rid of spaces in infix string
    }
    
    //THINGS TO CHECK FOR:
    // All chars are lower case letters OR ( ) ! & |
    // Matching parentheses
    // All operations must have operands around them
        // | and & must have operands on either side
        // ! must have an operand directly after it
    //two operands cannot be directly next to each other
    
    int parenCtr = 0;
    for (int j = 0; j < noSpaces.size(); j++){
        
        //lower case/operators
        if(!isalpha(noSpaces[j]) && noSpaces[j] != '(' && noSpaces[j] != ')' && noSpaces[j] != '&' && noSpaces[j] != '|' && noSpaces[j] != '!'){
            return false;
        }
        if(isalpha(noSpaces[j]) && !islower(noSpaces[j])) { return false;}
        
        // paren checker
        if(noSpaces[j] == '(') {
            parenCtr++;
            if(noSpaces[j+1] == ')'){ return false; } //can't have empty contents of parens
            if(isalpha(noSpaces[j-1])) { return false; } // parens must follow operator
        }
        if(noSpaces[j] == ')') {
            parenCtr--;
            if (parenCtr < 0) { return false; } //not balanced
        }
        
        // operands and operations locations
        if (noSpaces[j] == '&' || noSpaces[j] == '|'){
            if (j == 0 || j == noSpaces.size() -1) { return false; } //can't start or end with one of these
            if(noSpaces[j+1] == '&' || noSpaces[j-1] == '|' || noSpaces[j+1] == '&' || noSpaces[j+1] == '|')
            { return false; }
        }
        if (noSpaces[j] == '!') {
            if (j == noSpaces.size()-1) { return false; } //can't end with one of these
            if (!isalpha(noSpaces[j+1])) { return false; }
        }
        
        if (isalpha(noSpaces[j]) && isalpha(noSpaces[j+1])){ return false; }
}
    if (parenCtr != 0) { return false; }
    return true;
}




bool precedence(char o1, char o2){
    int n_op1 = 0; int n_op2 = 0;
    //assigns numbers for each level of precedence
    
    if (o1 == '!'){ n_op1 = 3; }
    else if (o1 == '&') { n_op1 = 2; }
    else if (o1 == '|') { n_op1 = 1; }
    if (o2 == '!'){ n_op2 = 3; }
    else if (o2 == '&') { n_op2 = 2; }
    else if (o2 == '|') { n_op2 = 1; }
    
    return (n_op1 <= n_op2);
    
}


void convert(string infix, string& postfix){
    //ISSUE WITH PRECEDENCE
    postfix = "";
    stack<char> op;
    for(int i = 0; i < infix.size(); i++){
        switch (infix[i]){
            case '&':
            case '!':
            case '|':
                while(!op.empty() && op.top() != '(' && precedence(infix[i], op.top()) ){
                    postfix += op.top();
                    op.pop();
                }
                op.push(infix[i]);
                break;
            case '(':
                op.push(infix[i]);
                break;
            case ')':
                while(op.top() != '('){
                    postfix += op.top();
                    op.pop();
                }
                op.pop();
                break;
            default:
                postfix += infix[i];
                break;
        }
    }
    while (!op.empty()){
        postfix += op.top();
        op.pop();
    }
}


/*

bool evalPostFix(string postfix){
    stack<char> operand;
    
    
    string noSpaces = ""; //avoid annoying spaces
    for (int i = 0; i < postfix.size(); i++){
        if (postfix[i] != ' '){ noSpaces += postfix[i]; }
    }
    
    char operand2;
    char operand1;
    
    for (int j = 0; j < noSpaces.size(); j++){
        switch(noSpaces[j]){
        case '!':
        case '|':
        case '&':
            operand2 = operand.top();
            operand.pop();
            operand1 = operand.top();
            operand.pop();
           
            //now apply operator
                
            break;
        
                
        default:
            operand.push(noSpaces[j]);
            break;
        }
    }
    return operand.top();
}
 */

/*
int main() {
    
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cout << "Passed all tests" << endl;
    
}
 */
