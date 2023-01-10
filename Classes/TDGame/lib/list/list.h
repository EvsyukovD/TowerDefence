#ifndef _LIST_H_
#define _LIST_H_
namespace MySTL {
	template<class T>
	struct Item {
		T data;
		Item* next;
		Item(const T& t, Item* n): data(t), next(n){}
		Item():data(),next(nullptr) {}
	};
	template<class T>
	class List {
	private:
		Item<T>* head;
		Item<T>* tail;
		int _size;
	public:
		List(): head(nullptr), tail(nullptr), _size(0) {}
		class ListIterator;
		class ConstListIterator;
		typedef ListIterator iterator;
		typedef ConstListIterator const_iterator;
		friend class iterator;
		friend class const_iterator;
		iterator begin() {
			iterator iter = iterator(*this);
			return iter;
		}
		iterator end() {
			iterator iter = iterator(nullptr, tail, *this);
			return iter;
		}
		const_iterator begin() const{
			const_iterator iter = const_iterator(*this);
			return iter;
		}
		const_iterator end() const {
			const_iterator iter = const_iterator(nullptr, tail, *this);
			return iter;
		}
		int size() const{
			return _size;
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
			_size++;
		}
		/**
		 * \brief Add element to the begining
		 *
		 * \param t - element
		 */
		void push_front(const T& t) {
			Item<T>* newItem = new Item<T>(t, this->head);
			if (head != nullptr) {
				head = newItem;
			}
			else {
				head = newItem;
				tail = newItem;
			}
			_size++;
		}
		/**
		 * \brief Remove element by respective iterator
		 *
		 * \param iter - iterator with respective element
		 * \throw std::invalid_argument - if iter - iterator of\n
		 *  other list or if iterator is invalid 
		 */
		iterator& erase(iterator& iter) {
			Item<T>* ptr = iter.cur;
			Item<T>* prev = iter.prev;
			if (iter.thisList != this) {
				std::invalid_argument("Other list iterator");
			}
			if (ptr == nullptr) {
				throw std::invalid_argument("Invalid iterator");
			}
			Item<T>* next = ptr->next;
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
				} else {
					prev->next = next;
				}
			}
			delete iter.cur;
			iter.prev = nullptr;
			iter.thisList = nullptr;
			_size--;
			return ListIterator(next, prev, *this);
		}
		/**
		 * \brief Remove all elements from list
		 */
		void clear() {
			for (auto iter = begin(); iter != end();) {
				iter = erase(iter);
			}
		}
		bool empty() const{
			return size() == 0;
		}
		List<T>& operator =(const List<T>& list) {
			if (this == &list) {
				return *this;
			}
			clear();
			for (auto e : list) {
				push_back(e);
			}
			return *this;
		}
		List<T>& operator =(List<T>&& list) {
			swap(list);
			return *this;
		}
		List(const List<T>& list) {
			for (auto e : list) {
				push_back(e);
			}
		}
		List(List<T>&& list) {
			move(list);
		}
		~List() {
			clear();
		}
		protected:
			virtual void swap(List<T>&& list) {
				Item<T>* hptr = list.head, * tptr = list.tail;
				int tmpSize = list._size;
				list.head = head;
				list.tail = tail;
				list._size = _size;
				head = hptr;
				tail = tptr;
				_size = tmpSize;
			}
			virtual void move(List<T>&& list) {
				head = list.head;
				tail = list.tail;
				_size = list._size;
				list.head = nullptr;
				list.tail = nullptr;
				list._size = 0;
			}
		public:
		class ListIterator {
		private:
			Item<T>* cur = nullptr;
			Item<T>* prev = nullptr;
			List<T>* thisList = nullptr;
		public:
			friend class List<T>;
			ListIterator(List<T>& list): cur(list.head), prev(nullptr), thisList(&list) {
			    
			}
		private:
			ListIterator(Item<T>* c, Item<T>* p, List<T>& l) : cur(c), prev(p), thisList(&l) {
			}
		public:
			ListIterator& operator ++() {
				if (cur) {
					prev = cur;
					cur = cur->next;
				}
				return *this;
			}
			ListIterator operator ++(int) {
				ListIterator iter = ListIterator(cur,prev,thisList);
				if (cur) {
					prev = cur;
					cur = cur->next;
				}
				return iter;
			}
			bool operator !=(const ListIterator& iter) const{
				 return this->cur != iter.cur || this->prev != iter.prev;
			}
			bool operator ==(const ListIterator& iter) const{
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
		class ConstListIterator {
		private:
			Item<T>* cur = nullptr;
			Item<T>* prev = nullptr;
			const List<T>* thisList = nullptr;
		public:
			friend class List<T>;
			ConstListIterator(const List<T>& list) : cur(list.head), prev(nullptr), thisList(&list) {

			}
		private:
			ConstListIterator(Item<T>* c, Item<T>* p, const List<T>& l) : cur(c), prev(p), thisList(&l) {
			}
		public:
			ConstListIterator& operator ++() {
				if (cur) {
					prev = cur;
					cur = cur->next;
				}
				return *this;
			}
			ConstListIterator operator ++(int) {
				ConstListIterator iter = ConstListIterator(cur, prev, thisList);
				if (cur) {
					prev = cur;
					cur = cur->next;
				}
				return iter;
			}
			bool operator !=(const ConstListIterator& iter) const {
				return this->cur != iter.cur || this->prev != iter.prev;
			}
			bool operator ==(const ConstListIterator& iter) const {
				return this->cur == iter.cur && this->prev == iter.prev;
			}
			const T& operator *() {
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
