#ifndef _LIST_H_
#define _LIST_H_
namespace MySTL {
	template<class T>
	struct Item {
		T data;
		Item* next;
		Item(const T& t, Item* n): data(t),next(n){}
		Item():data(),next(nullptr) {}
	};
	template<class T>
	class List {
	private:
		Item<T>* head;
		Item<T>* tail;
	public:
		List();
		class ListIterator;
		typedef ListIterator iterator;
		friend class iterator;
		iterator begin() {
			iterator iter = iterator(head, nullptr);
			return iter;
		}
		iterator end() {
			iterator iter = iterator(nullptr, tail);
			return iter;
		}
		/**
		 * \brief Add element to the end
		 * 
		 * \param t - element
		 */
		void push_back(const T& t) {
			Item<T>* newItem = new Item<T>(t, nullptr);
			if (head != nullptr) {
				tail->next = newItem;
				tail = newItem;
			}
			else {
				head = newItem;
				tail = newItem;
			}
		}
		void push_front(const T& t) {
			Item<T>* newItem = new Item<T>(t, this->head);
			if (head != nullptr) {
				head = newItem;
			}
			else {
				head = newItem;
				tail = newItem;
			}
		}
		iterator& erase(const iterator& iter) {
			Item<T>* ptr = iter.cur;
			Item<T>* prev = iter.prev;
			if (ptr == nullptr && prev != tail) {
				throw std::invalid_argument("Invalid iterator");
			}
			if (ptr == head) {
				head = ptr->next;
				if (ptr == tail) {
					tail = head;
				}
			}
			else {
				if (ptr == tail) {
					tail = prev;
					tail->next = nullptr;
				}
			}
			return ++ListIterator(iter.cur, iter.prev);
		}
		void clear() {
			for (auto iter = begin(); iter != end();) {
				iter = erase(iter);
			}
		}
		~List() {
			clear();
		}
		class ListIterator {
		private:
			Item<T>* cur = nullptr;
			Item<T>* prev = nullptr;
		public:
			friend class List<T>;
			//friend List<T>::ListIterator& List<T>::erase(List<T>::ListIterator& t);
			ListIterator(Item<T>* c, Item<T>* p);
			ListIterator& operator ++() {
				if (cur) {
					prev = cur;
					cur = cur->next;
				}
				return *this;
			}
			ListIterator operator ++(int) {
				ListIterator iter = ListIterator();
				iter.cur = cur;
				iter.prev = prev;
				if (cur) {
					prev = cur;
					cur = cur->next;
				}
				return iter;
			}
			bool operator !=(const ListIterator& iter) {
				 return this->cur != iter.cur || this->prev != iter.prev;
			}
			bool operator ==(const ListIterator& iter) {
				 return this->cur == iter.cur && this->prev == iter.prev;
			}
			T& operator *() {
				if (this->cur) {
					return this->cur->data;
				}
				else {
					throw std::invalid_argument("Element don't exist");
				}
			}
		};
	};
}
#endif // !_LIST_H_
