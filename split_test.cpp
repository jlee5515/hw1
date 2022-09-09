#include "split.h"
#include <iostream>
using namespace std;

void print(Node* head){
	if(head == NULL){
		cout << "NULL/Empty List" << endl;
	}
	else{
		while(head != NULL){
			cout << head->value << "  ";
			head = head->next;
		}
		cout << endl;
	}
}

int main() {
	Node* head = new Node(0,NULL);
	Node* list1 = head;
	Node* evens_ = NULL;
	Node* odds_ = NULL;

	for (int i = 1; i < 9; i++){
		head->next = new Node(i, NULL);
		head = head->next;
	}

	cout << "Original List: " << endl;
	print(list1);

	split(list1, odds_, evens_);

	cout << "Evens:" << endl;
	print(evens_);

	cout << "Odds:" << endl;
	print(odds_);
}