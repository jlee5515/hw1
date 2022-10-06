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
		Item* temp = new Item;
		temp->val[0] = val;
		temp->first = 0;
		temp->last = 1;
		head_ = temp;
		tail_ = head_;
	}
	else if(head_->first != 0){ //if there is room to push to the front of the current node, do so
		head_->val[head_->first-1] = val;
		head_->first--;
	}
	else{	//no room in current node. create a node and push val to the last index in head and reassign head
		Item *temp = new Item;
		temp->prev = NULL;
		head_->prev = temp;
		temp->next = head_;
		temp->val[ARRSIZE-1] = val;
		temp->first = ARRSIZE-1;
		temp->last = ARRSIZE;
		head_ = temp;
	}

	size_++;
}

void ULListStr::pop_back(){
	if (empty()){//if list is empty
		return;
  }
  else if (size_ == 1){
		delete tail_;
		tail_ = NULL;
		head_ = NULL;
	}
	else if(tail_->last == 1 && tail_ != head_){
		Item* temp = tail_;
		temp->prev->next = NULL;
		tail_ = tail_->prev;
		delete temp;
	}
	else{
		(tail_->val[tail_->last-1]).clear();
		--(tail_->last);
	}
	size_--;
}

void ULListStr::pop_front(){
	if(empty()){//if list is empty
		return;
  }
  else if(size_ == 1){ 
		delete head_;
		tail_ = NULL;
		head_ = NULL;
	}
	else if(head_->first == ARRSIZE && head_ != tail_){
		Item* temp = head_;
		head_->next->prev = NULL;
		head_ = head_->next;
		delete temp;
	}
	else{
		(head_->val[head_->first]).clear();
		++(head_->first);
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