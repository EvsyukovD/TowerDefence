#include "list.h"
#include <iostream>
namespace MySTL {
  template<class T>
  List<T>::List(): head(nullptr), tail(nullptr){
     
  }
  template<class T>
  List<T>::ListIterator::ListIterator(Item<T>* head, Item<T>* p): cur(head), prev(p){

  }
}
