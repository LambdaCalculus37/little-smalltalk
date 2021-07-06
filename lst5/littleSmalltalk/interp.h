/* $Id: $
 *
 * LittleSmalltalk system
 * Originally written by Timothy Budd.
 * Timothy Budd allowed me (Danny Reinhold) to replace
 * his original copyright notice and to push a
 * LittleSmalltalk project.
 *
 * The new LittleSmalltalk distribution is licensed
 * as follows:
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions: 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software. 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. 
 *
 * Author of the original version: Timothy Budd
 * Maintainer after version 4: Danny Reinhold
 *
 * For more detailed information visit our web site:
 * http://www.littlesmalltalk.org
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H


int execute (struct object *);

void flushCache();

/*
	symbolic definitions for the bytecodes
*/

#define Opcode_Extended         0
#define Opcode_PushInstance     1
#define Opcode_PushArgument     2
#define Opcode_PushTemporary    3
#define Opcode_PushLiteral      4
#define Opcode_PushConstant     5
#define Opcode_AssignInstance   6
#define Opcode_AssignTemporary  7
#define Opcode_MarkArguments    8
#define Opcode_SendMessage      9
#define Opcode_SendUnary       10
#define Opcode_SendBinary      11
#define Opcode_PushBlock       12
#define Opcode_DoPrimitive     13
#define Opcode_DoSpecial       15

/* types of special instructions (opcode 15) */

#define SelfReturn 1
#define StackReturn 2
#define BlockReturn 3
#define Duplicate 4
#define PopTop 5
#define Branch 6
#define BranchIfTrue 7
#define BranchIfFalse 8
#define SendToSuper 11

/* special constants */

/* constants 0 to 9 are the integers 0 to 9 */
#define nilConst 10
#define trueConst 11
#define falseConst 12

/*
	The following are the objects with ``hard-wired'' 
	field offsets
*/

/*
	A Process has two fields
		* a current context
		* status of process (running, waiting, etc)
*/

#define contextInProcess 0
#define statusInProcess 1
#define resultInProcess 2

/*
	A Context has:
		* method (which has bytecode pointer)
		* bytecode offset (an integer)
		* arguments
		* temporaries and stack
		* stack pointer
*/

#define contextSize 7
#define methodInContext 0
#define argumentsInContext 1
#define temporariesInContext 2
#define stackInContext 3
#define bytePointerInContext 4
#define stackTopInContext 5
#define previousContextInContext 6

/*
	A Block is subclassed from Context
	shares fields with creator, plus a couple new ones
*/

#define blockSize 10
#define methodInBlock methodInContext
#define argumentsInBlock argumentsInContext
#define temporariesInBlock temporariesInContext
#define stackInBlock stackInContext
#define stackTopInBlock stackTopInContext
#define previousContextInBlock previousContextInContext
#define argumentLocationInBlock 7
#define creatingContextInBlock 8
/* the following are saved in different place so they don't get clobbered*/
#define bytePointerInBlock 9

/*
	A Method has:
		* name (a Symbol)
		* bytecodes
		* literals
		* stack size
		* temp size
*/

#define nameInMethod          0
#define byteCodesInMethod     1
#define literalsInMethod      2
#define stackSizeInMethod     3
#define temporarySizeInMethod 4
#define classInMethod         5
#define textInMethod          6
#define methodSize            7

/*
	A Class has:
		* pointer to parent class
		* pointer to tree of methods
*/

#define nameInClass         0
#define parentClassInClass  1
#define methodsInClass      2
#define instanceSizeInClass 3
#define variablesInClass    4
#define ClassSize           5

/*
	A node in a tree has
		* value field
		* left subtree
		* right subtree
*/

#define valueInNode 0
#define leftInNode  1
#define rightInNode 2

/*
	misc defines
*/

#define rootInTree          0
#define receiverInArguments 0
#define symbolsInSymbol     5


#endif

