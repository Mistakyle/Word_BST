#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <queue>	
#include <stack>
#include <sstream>

using namespace std;

#include "treeCell.h"
#include "tree.h"

void tree :: read(string fileName)
{
	ifstream myFile;
	myFile.open(fileName.c_str());
	
	string newWord = " ";
	treeCell* newCell;
	
	//verifying file was valid
	if(!myFile.is_open())
	{
		cout<<"ERROR: INVALID FILE NAME"<<endl;
		return;
	}
	
	while(!myFile.eof())
	{
		//Normalizing the data in the treeCell by removing all punctuation and caps
		myFile>>newWord;
		for(int i=0; i<newWord.length(); i++)
		{
			if(ispunct(newWord[i]))
			{
				newWord.erase(i,1);
			}
			
			else if (isupper(newWord[i]))
			{
				newWord[i]=tolower(newWord[i]);
			}
			else
			{
				//do nothing
			}
		}
		
		insert(newWord,root);
		
	}
}

//inserting a new cell to the tree recursively, maintaining the binary search property
//since we use pass by reference antics 'treeCell* & t) we have access to the parent node
void tree :: insert(string newWord, treeCell* & t)
{
	//if we are at the bottom of the tree/tree is empty
	if(t==NULL)
	{
		t = new(nothrow) treeCell;
		t->data = newWord;
		t->left=NULL;
		t->right=NULL;
	}
	else
	{
		//maintiaing the binary search property
		if(newWord < t->data)
		{
			insert(newWord, t->left);
		}
		else if(newWord > t->data)
		{
			insert(newWord, t->right);
		}
		else
		{
			//word must be the same, so increase frequency 
			t->frequency++;
		}
	}
}


//method that interacts with the user to obtain commands
void tree :: processCommands()
{
	string command = " ";
	string fileName;	

	
	while(command!="stop")
	{
		cout<<"Please enter a command: "<<endl;
		
		//tempC (temp command) is used to grab the whole line of the command entered.  Following that 
		//we stream into the individual parts of the line that toal to the whole command.
		//the benefit of doing it this way is to make our input much more durable and malleable, through
		//preventing a crash due to bad input.  
		
		string tempC;
		getline(cin, tempC);
		istringstream myStream(tempC);
		myStream>>command;
		
		
		//The below branch handles the entered commands by calling the appropriate methods 
		if(command=="add")
		{
			myStream>>fileName;
			
			
		
			read(fileName);
		}
		else if(command=="inorder")
		{
			inorder();
		}
		else if(command=="postorder")
		{
			postorder();
		}
		else if(command=="breadthfirst")
		{
			breadthfirst();
		}
		else if(command=="bottomup")
		{
			bottomup();
		}
		else if(command=="stop")
		{
			exit(3);
		}
		else 
		{
			cout<< "Invalid Command"<<endl;
		}
	}
}

//basic public method that calls the recursive traversal
void tree :: inorder()
{
	inorder_traversal(root);
}

//recursive privare method that traverses the tree then prints the tree in order from smallest to largest
void tree :: inorder_traversal(treeCell* t)
{
	if(t==NULL)
	{
		return;
	}
	else
	{
		inorder_traversal(t->left);
		visit(t);
		inorder_traversal(t->right);
	}
}

//basic public method used to call private recursive method
void tree :: postorder()
{
	postorder_traversal(root);
}

//recursive method that traverses the list, left->right->root and prints out the nodes as it traverses
void tree :: postorder_traversal(treeCell* t)
{
	if(t==NULL)
	{
		return;
	}
	else{
		postorder_traversal(t->left);
		postorder_traversal(t->right);
		visit(t);
	}
}

//prints out the data members of the treecell passed into the method
void tree :: visit(treeCell* t)
{
	
	if(t->frequency>1)
	{
		cout<<t->data<<" "<<"("<< t->frequency<< ")" <<endl;
	}
	else
	{
		cout<<t->data<< " " <<endl;
	}
}

//public method that calls the private traversal on the root  
void tree :: breadthfirst()
{
	breadthfirst_traversal(root);
}

//Using a queue and recursion, we print the tree out in levels
void tree :: breadthfirst_traversal(treeCell* t)
{
	//using the c++ queue class to declare a queue of treeCell pointers
	queue<treeCell*> myQueue;
	
	//push root onto the queue, now we have the whole tree
	myQueue.push(t);
	
	//this while will run the whole length of the tree since when the only case in which the 
	//queue will have no elements is when the last leaf is popped off
	while(!myQueue.empty())
	{
		t=myQueue.front();
		myQueue.pop();
		visit(t);
		
		//he fact that t is the root to go down the whole tree, storing it into a queue
		if(t->left!=NULL)
		{
			myQueue.push(t->left);
		}
	
		if(t->right!=NULL)
		{
			myQueue.push(t->right);
		}
	}
}


//public method that calls the private traversal on the root
void tree :: bottomup()
{
	bottomup_traversal(root);
}

void tree :: bottomup_traversal(treeCell* t)
{
	//using the c++ stack and queue classes creating a stack and queue of treeCell pointers
	queue<treeCell*> myQueue;
	stack<treeCell*> myStack;
	
	//push the root giving us access to the whole tree
	myQueue.push(t);
	
	//while the queue(tree) is not empty
	while(!myQueue.empty())
	{
		
		//very similar logic to the breadthfirst method, but instead of
		//visiting t after it is popped off the queue, we push it onto the stack 
		t=myQueue.front();
		myQueue.pop();
		myStack.push(t);
		if(t->left!=NULL)
		{
			myQueue.push(t->left);
		}
		if(t->right!=NULL)
		{
			myQueue.push(t->right);
		}
	}

	//after the stack has been filled with the tree, we now print it out giving us
	//a list of the nodes from the bottom->top
	while(!myStack.empty())
	{
		t=myStack.top();
		visit(t);
		myStack.pop();
		
	}
}
		
	
	
	
	
		
