#include <iostream>
#include <stdlib.h>
#include "BinaryTree.hpp"

using namespace std;

int options(){

	int choice;

	cout<<std::endl;
	cout<<"[1] Insert an element\n";
	cout<<"[2] Delete an element\n";
	cout<<"[3] View an element\n";
	cout<<"[4] Check a key\n";
	cout<<"[5] Find predecessor\n";
	cout<<"[6] Find successor\n";
	cout<<"[7] Find maximum\n";
	cout<<"[8] Find minimum\n";
	cout<<"[9] Print in order\n";
	cout<<"[10] Print pre order\n";
	cout<<"[11] Print post order\n";
	cout<<"[0] Exit\n";

	cout<<"Enter your choice : ";
	cin>>choice;
	cout<<endl;

	return choice;
}

int main(int arc, char* argv[]){

	cout<<"|||||\tBinary Tree\t|||||\n";
	BinaryTree<int, int> tree;
	int key;
	int value;

	while(1){
		switch(options()){

			case 1 :	cout<<"Enter key : ";
						cin>>key;
						cout<<"Enter value : ";
						cin>>value;
						tree.put(key, value);
						break;

			case 2 :	cout<<"Enter key : ";
						cin>>key;
						tree.remove(key);
						break;

			case 3 :	cout<<"Enter key : ";
						cin>>key;
						try{
							cout<<"["<<key<<"] : "<<tree.get(key)<<endl;
						}
						catch(const char* err){
							cout<<err<<endl;
						}
						break;

			case 4 :	cout<<"Enter key : ";
						cin>>key;
						cout<< tree.has(key) ? "Key exists.\n" : "Key doesn't exists.\n";
						break;

			case 5 :	cout<<"Enter key : ";
						cin>>key;
						try{
							cout<<"Predecessor : "<<tree.predecessor(key)<<endl;
						}
						catch(const char* err){
							cout<<err<<endl;
						}
						break;

			case 6 :	cout<<"Enter key : ";
						cin>>key;
						try{
							cout<<"Successor : "<<tree.successor(key)<<endl;
						}
						catch(const char* err){
							cout<<err<<endl;
						}
						break;

			case 7 :	try{
							cout<<"Maximum : "<<tree.maximum()<<endl;
						}
						catch(const char* err){
							cout<<err<<endl;
						}
						break;

			case 8 :	try{
							cout<<"Minimum : "<<tree.minimum()<<endl;
						}
						catch(const char* err){
							cout<<err<<endl;
						}
						break;

			case 9 :	tree.print_in_order();
						cout<<endl;
						break;

			case 10 :	tree.print_pre_order();
						cout<<endl;
						break;

			case 11 :	tree.print_post_order();
						cout<<endl;
						break;

			case 0 :	exit(EXIT_SUCCESS);

			default :	cout<<"Invalid choice.\n";
		}
	}

	return 0;
}