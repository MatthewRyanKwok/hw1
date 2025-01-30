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
std::string const& ULListStr::front() const
{
    return head_->val[head_->first];//returns first item
}
std::string const& ULListStr::back() const
{
    return tail_->val[tail_->last - 1];//returns last item
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
    if (loc >= size_) { //makes sure loc is within bounds
        return NULL;
    }
    Item* current = head_;
    size_t ind = loc;

    while (current != NULL) { //iterates through to find right item/index
        size_t elements = current->last - current->first;
        if (ind < elements) {
            return &(current->val[current->first + ind]); //returns pointer
        }
        ind -= elements;
        current = current->next;
    }
    return NULL;
}

void ULListStr::push_back(const std::string& val) {
    if (tail_ == NULL || tail_->last == ARRSIZE) { //checks if list is empty/last node full
        Item* temp = new Item();

        if (!head_) { //sets head to the temp/new node if list was empty
            head_ = temp;
        }
        else {
            tail_->next = temp; //otherwise links new node to current tail
            temp->prev = tail_;
        }
        tail_ = temp; //updates tail 
    }
    tail_->val[tail_->last] = val; //adds new val at next position in tail node
    tail_->last++;
    size_++;
}


void ULListStr::pop_back()
{
    if (!tail_) { //if empty
        return;
    }
    if (--tail_->last == tail_->first) { //if last item empty, remove
        Item* temp = tail_;
        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = NULL;
        }
        else {
            head_= NULL;
        }
        delete temp; //removes the last item
    }
    size_--;
}

void ULListStr::push_front(const std::string& val) {
    if (head_ == NULL || head_->first == 0) { //checks list and if head is full
        Item* temp = new Item(); //new temp node

        if (!tail_) {
            tail_ = temp; //tail set to new node
        }
        else {
            head_->prev = temp; //link head's prev pointer to new node
        }

        temp->next = head_;
        head_ = temp; //update head ptr

        head_->first = ARRSIZE; //initialize first and last ptrs
        head_->last = ARRSIZE;
    }

    head_->first--;
    head_->val[head_->first] = val; //stores new val at pos of new first
    size_++;
}



void ULListStr::pop_front()
{
    if (!head_) { //if empty
        return;
    }
    if (head_->first == head_->last) {  
        Item* temp = head_;
        head_ = head_->next;  //moves head
        if (head_) {
            head_->prev = NULL;  //updates prev of new head
        }
        else {
            tail_ = NULL;  //if list empty sets tail to null
        }
        delete temp;  //deletes old head
    }
    else {
        ++head_->first;
    }
    size_--;  //decrements

}


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
