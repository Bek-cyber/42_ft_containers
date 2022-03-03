#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <iterator>
#include "random_access_iterators.hpp"
#include "reverse_iterators.hpp"

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef random_access_iterator<false, T>			iterator;
		typedef random_access_iterator<true, const T>		const_iterator;
		typedef reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef reverse_iterator<iterator>					reverse_iterator;

		/************************CONSTRUCTORS************************/

		explicit vector (const allocator_type& alloc = allocator_type()) {
			size_ = 0;
			capacity_ = 0;
			ptr_ = NULL;
			alloc_ = alloc;
		}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) {
			size_ = n;
			capacity_ = n;
			alloc_ = alloc;
			ptr_ = alloc_.allocate(n);
			for (size_type i = 0; i < n; ++i) {
				alloc_.construct(ptr_ + i, val);
			}
		}

		template <class InputIt>
		vector(InputIt first, InputIt last, const allocator_type& allctr_obj = allocator_type(),
			   typename std::enable_if<!std::is_integral<InputIt>::value, bool>::type* = 0): alloc_(allctr_obj) {
			size_ = std::distance(first, last);
			capacity_ = std::distance(first, last);
			ptr_ = alloc_.allocate(capacity_);
			for (size_type i = 0; i < size_; ++i) {
				alloc_.construct(ptr_ + i, *(first + i));
			}
		}

		vector (const vector& other) {
			size_ = other.size_;
			capacity_ = other.capacity_;
			alloc_ = other.alloc_;
			ptr_ = alloc_.allocate(size_);
			for (size_type i = 0; i < size_; ++i) {
				alloc_.construct(ptr_ + i, *(other.ptr_ + i));
			}
		}

		~vector() {
			for (size_type i = 0; i < size_; ++i) {
				if (ptr_ + i) {
					alloc_.destroy(ptr_ + i);
				}
			}
			alloc_.deallocate(ptr_, capacity_);
			ptr_ = NULL;
		}

		vector & operator= (vector const & other) {
			if (this == &other) { return *this; }
			this->~vector();
			size_ = other.size_;
			capacity_ = other.capacity_;
			alloc_ = other.alloc_;
			ptr_ = alloc_.allocate(size_);
			for (int i = 0; i < size_; ++i) {
				alloc_.construct(ptr_ + i, *(other.ptr_ + i));
			}
			return *this;
		}
		
		/************************ITERATORS************************/
		
		iterator begin() { return iterator(ptr_); }

		const_iterator	begin() const { return const_iterator(ptr_); }

		iterator end() { return iterator(ptr_ + size_); }

		const_iterator end() const { return const_iterator(ptr_ + size_); }

		reverse_iterator rbegin() {
			if (size() == 0) {
				return (reverse_iterator (iterator (ptr_)));
			}
			return reverse_iterator (iterator (ptr_ + size_ - 1));
		}

		const_reverse_iterator rbegin() const {
			if (size() == 0) {
				return (const_reverse_iterator (iterator (ptr_)));
			}
			return const_reverse_iterator (iterator (ptr_ + size_ - 1));
		}

		reverse_iterator rend() {
			if (size() == 0) {
				return (reverse_iterator(iterator(ptr_)));
			}
			return (reverse_iterator(iterator(ptr_ - 1)));
		}

		const_reverse_iterator rend() const {
			if (size() == 0) {
				return (const_reverse_iterator (iterator(ptr_)));
			}
			return (const_reverse_iterator (iterator(ptr_ - 1)));
		}
		
		/************************CAPACITY************************/

		size_type size() const { return size_; }

		size_type max_size() const { return  alloc_.max_size(); }

		void resize (size_type n, value_type val = value_type()) {
			if (n < size_) {
				for (size_type i = n; i < size_; ++i) {
					if (ptr_ + i) { alloc_.destroy(ptr_ + i); }
				}
				size_ = n;
			}
			if (n > size_) {
				reserve(n);
				for (size_type i = size_; i < n; ++i) {
					alloc_.construct(ptr_ + i, val);
				}
				size_ = n;
			}
		}

		size_type capacity() const { return capacity_; }

		bool empty() const { return size_ == 0; }

		void reserve (size_type n) {
			if (n > capacity_) {
				pointer new_ptr = alloc_.allocate(n);
				for (size_type i = 0; i < size_; ++i) {
					alloc_.construct(new_ptr + i, *(ptr_ + i));
					alloc_.destroy(ptr_ + i);
				}
				alloc_.deallocate(ptr_, capacity_);
				ptr_ = new_ptr;
				capacity_ = n;
			}
		}

		/************************ELEMENT_ACCESS************************/
		
		reference operator[] (size_type n) { return *(ptr_ + n); }

		const_reference operator[] (size_type n) const { return *(ptr_ + n); }


		reference at (size_type n) {
			if (n < size_) { return *(ptr_ + n); }
			else { std::cout << "ERROR: function at"; }
		}
		const_reference at (size_type n) const {
			if (n < size_) { return *(ptr_ + n); }
			else { std::cout << "ERROR: function const_at"; }
		}

		reference front() { return *ptr_; }

		const_reference front() const { return *ptr_; }

		reference back() { return *(ptr_ + size_ - 1); }

		const_reference back() const { return *(ptr_ + size_ - 1); }
		
		/************************MODIFIERS************************/
		
		void push_back (const value_type& val) {
			if (size_ == capacity_) { reserve(capacity_ == 0 ? 1 : capacity_ * 2); }
			alloc_.construct(ptr_ + size_, val);
			++size_;
		}

		void pop_back() {
			if (size_ > 0) {
				alloc_.destroy(ptr_ + size_ - 1);
				--size_;
			}
		}

		template <class Q>
		void my_swap(Q & a, Q & b) {
			Q tmp = a;
			a = b;
			b = tmp;
		}

		void swap (vector& x) {
			my_swap(ptr_, x.ptr_);
			my_swap(size_, x.size_);
			my_swap(capacity_, x.capacity_);
			my_swap(alloc_, x.alloc_);
		}

		void clear() {
			for (size_type i = 0; i < size_; ++i) { alloc_.destroy(ptr_ + i); }
			size_ = 0;
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			clear();
			for (; first != last; ++first) { push_back(*first); }
		}

		void assign(size_type n, const value_type& val) {
			clear();
			for (size_type i = 0; i < n; ++i) { push_back(val); }
		}

		iterator insert (iterator position, const value_type& val) {
			if (position == end()) {
				push_back(val);
				difference_type diff = std::distance(begin(), position);
				return (begin() + diff);
			}
			vector tmp(position, end());
			iterator finish = end();
			while (finish-- > position) { pop_back(); }
			push_back(val);
			iterator it = tmp.begin();
			for (; it != tmp.end(); ++it) { push_back(*it); }
			difference_type diff = std::distance(begin(), position);
			return (begin() + diff);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			vector tmp(position, end());
			iterator finish = end();
			while (finish > position) {
				pop_back();
				--finish;
			}
			for (size_type i = 0; i < n; ++i) { push_back(val); }
			iterator it = tmp.begin();
			for (; it != tmp.end(); ++it) { push_back(*it); }
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
			   typename std::enable_if<!std::is_integral<InputIterator>::value, bool>::type* = 0) {
			vector tmp(position, end());
			iterator start = first;
			iterator end = end();
			while (end-- > position) { pop_back(); }
			for (; first != last; ++first) { push_back(*start); }
			iterator it = tmp.begin();
			for (; it != tmp.end(); ++it) { push_back(*it); }
		}
		
		template <class InputIterator>
		iterator erase (InputIterator position) {
			if (position == end()) {
				pop_back();
				return (position);
			}
			vector tmp(position + 1, end());
			iterator it = position;
			iterator finish = end();
			for (; it != finish; ++it) {
 				pop_back();
			}
			it = tmp.begin();
			for (; it != tmp.end(); ++it) {
				push_back(*it);
			}
			return (position);
		}
		
		template <class InputIterator>
		iterator erase (InputIterator first, InputIterator last) {
			vector tmp(last, end());
			while (begin() != end()) { pop_back(); }
			for (iterator it = tmp.begin(); it != tmp.end(); ++it) { push_back(*it); }
			return first;
		}
		
		/************************GETTER************************/

		allocator_type	get_allocator() const { return alloc_; }

	private:
		size_type		size_;
		size_type		capacity_;
		pointer 		ptr_;
		allocator_type	alloc_;

	};
}

#endif