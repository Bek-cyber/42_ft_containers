#pragma once

#include <memory>
#include "conditional.hpp"
#include "map.hpp"
#include <cstddef>
#include <iterator>

namespace ft {

	template <bool isConst, class T>
	class bidirectional_iterator {
	public:
		typedef typename ft::conditional<isConst, const T, T>::type	value_type;
		typedef value_type*											pointer;
		typedef value_type&											reference;
		typedef std::ptrdiff_t										difference_type;
		typedef std::bidirectional_iterator_tag						iterator_category;
		
		bidirectional_iterator(): _ptr(NULL), NIL(NULL) {}
		
		~bidirectional_iterator() {}
		
		bidirectional_iterator(bidirectional_iterator const & other) {
			this->_ptr = other.getPointer();
			NIL = NULL;
		}
		
		bidirectional_iterator & operator=(bidirectional_iterator const other) {
			if (this == &other) { return *this; }
			this->_ptr = other.getPointer();
			NIL = NULL;
			return *this;
		}
		
		bidirectional_iterator(rbtNode<T>* ptr): _ptr(ptr), NIL(NULL) {}
		
		rbtNode<T>* const getPointer() const { return _ptr; }
		
		reference operator*() { return _ptr; }
		
		pointer operator->() {return &_ptr; }
		
		bidirectional_iterator & const operator++() {
			++this->_ptr;
			return *this;
		}
		
		bidirectional_iterator & const operator++(int) {
			bidirectional_iterator tmp(*this);
			++this->_ptr;
			return tmp;
		}
		
		bidirectional_iterator & const operator--() {
			++this->_ptr;
			return *this;
		}
		
		bidirectional_iterator & const operator--(int) {
			bidirectional_iterator tmp(*this);
			++this->_ptr;
			return tmp;
		}
	
	private:
		rbtNode<T>* _ptr;
		rbtNode<T>* NIL;
	};
	
	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator==(bidirectional_iterator<firstIsConst, T1> const & lhs, bidirectional_iterator<secondIsConst, T2> const & rhs) {
		return (lhs.getPointer() == rhs.getPointer());
	}
	
	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator!=(bidirectional_iterator<firstIsConst, T1> const & lhs, bidirectional_iterator<secondIsConst, T2> const & rhs) {
		return (lhs.getPointer() == rhs.getPointer());
	}
}