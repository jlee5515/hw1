#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val){
	if(empty()){ //if no list exists, create a head and tail and push val to the first index in tail
		head_ = new Item;
		tail_ = head_;

		tail_->first = 0;
		tail_->last = 1;
		tail_->val[tail_->first] = val;
	}
	else if(tail_->last != ARRSIZE){ //if there is room to push to the back of the current node, do so
		tail_->val[tail_->last] = val;
		tail_->last++;
	}
	else{ //no room in current node. create a node and push val to the first index and reassign tail
		Item *temp = tail_;
		tail_ = new Item;
		temp->next = tail_;
		tail_->prev = temp;

		tail_->first = 0;
		tail_->last = 1;	
		tail_->val[tail_->first] = val;
	}
	size_++;
}

void ULListStr::push_front(const std::string& val){
	if(empty()){ //if no list exists, create a head and tail and push val to the last index in head
		head_ = new Item;
		tail_ = head_;

		head_->first = 0;
		head_->last = 1;
		head_->val[head_->first] = val;
	}
	else if(head_->first != 0){ //if there is room to push to the front of the current node, do so
		head_->first--;
		head_->val[head_->first] = val;
	}
	else{	//no room in current node. create a node and push val to the last index in head and reassign head
		Item *temp = head_;
		head_ = new Item;
		temp->prev = head_;
		head_->next = temp;
		
		head_->first = ARRSIZE - 1;
		head_->last = ARRSIZE;
		head_->val[head_->first] = val;
	}

	size_++;
}

void ULListStr::pop_back(){
	if(empty()){ //node is empty/does not exist. return
		return;
	}
	if(size_ == 1){ //if there is only one node (head = tail), delete both
		delete tail_;
		head_ = NULL;
		tail_ = NULL;
	}
	else{
		if(tail_->last != 1){	//if pop_back() will not leave the array empty, move the 'last' pointer back one
			tail_->last--;
		}
		else{	//pop_back() will leave the node empty. reassign tail prev and head next, and delete the empty node
			Item *temp;
			temp = tail_->prev;
			delete tail_;
			tail_ = temp;
			tail_->next = NULL;
		}
	}
	size_--;
}

void ULListStr::pop_front(){
	if(empty()){	//node is empty/does not exist. return
		return;
	}
	if(size_ == 1){ //if there is only one node (head = tail), delete both
		delete head_;
		head_ = NULL;
		tail_ = NULL;
	}
	else{
		if(head_->first != ARRSIZE-1){ //if pop_front() will not leave the array empty, move the 'first' pointer forward one
			head_->first++;
		}
		else{ //pop_front() will leave the node empty. reassign head prev and head next, and delete the empty node
			Item *temp;
			temp = head_->next;
			delete head_;
			head_ = temp;
			head_->prev = NULL;
		}
	}
	size_--;
}

std::string const & ULListStr::front() const { //returns the value of the first index of the entire list
	return head_->val[head_->first];
}

std::string const & ULListStr::back() const { //returns the value of the last index of the entire list
	return tail_->val[tail_->last-1];
}

std::string* ULListStr::getValAtLoc(size_t loc) const { 
	if(loc > size_){ //if loc > size_, no such location exists
		return NULL;
	}
	
	Item* temp = head_;
	size_t len = temp->last - temp->first;

	while(loc >= len){ //search until the location and the value is found, return address
		loc -= len;
		if(temp->next == NULL){
			return NULL;
		}
		temp = temp->next;
	}
	return &(temp->val[temp->first+loc]);
}