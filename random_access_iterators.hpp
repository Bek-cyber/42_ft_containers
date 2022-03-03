#pragma once

#include <memory>
#include "../conditional/conditional.hpp"
#include <cstddef>
#include <iterator>

namespace ft {
	
	template <bool isConst, class T>
	class random_access_iterator {
	public:
		typedef typename ft::conditional<isConst, const T, T>::type	value_type;
		typedef value_type*											pointer;
		typedef value_type&											reference;
		typedef std::ptrdiff_t										difference_type;
		typedef std::random_access_iterator_tag						iterator_category;

		random_access_iterator(): _pointer(NULL) {}

		random_access_iterator(pointer pointer): _pointer(pointer) {}

		random_access_iterator(random_access_iterator const & other): _pointer(other._pointer) {}

		random_access_iterator & operator=(random_access_iterator const & other) {
			if (this == &other) { return *this; }
			_pointer = other._pointer;
			return *this;
		}

		~random_access_iterator() {}
		
		pointer getPointer() const { return _pointer; }
		
		reference operator*() { return *_pointer; }
		
		pointer operator->() { return _pointer; }
		
		random_access_iterator& operator++() {
			++this->_pointer;
			return *this;
		}
		
		random_access_iterator& operator++(int) {
			random_access_iterator tmp(*this);
			++this->_pointer;
			return tmp;
		}
		
		random_access_iterator& operator--() {
			--this->_pointer;
			return *this;
		}
		
		random_access_iterator& operator--(int) {
			random_access_iterator tmp(*this);
			--_pointer;
			return tmp;
		}
		
		random_access_iterator operator-=(size_t n) {
			return _pointer - n;
		}
		
		random_access_iterator operator+=(size_t n) {
			return _pointer + n;
		}
		
		reference operator[](size_t n) {
			return *(_pointer + n);
		}
		
		random_access_iterator operator+(int n) const {
			return this->getPointer() + n;
		}
		
		random_access_iterator operator-(size_t n) const {
			return this->getPointer() - n;
		}
		
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		bool operator==(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() == dsd.getPointer();
//		}
//
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		bool operator!=(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() != dsd.getPointer();
//		}
//
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		random_access_iterator& operator+(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() + dsd.getPointer();
//		}
//
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		difference_type & operator-(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() - dsd.getPointer();
//		}
//
//		template<bool firstIsConst, class T>
//		reference operator-(size_t n, random_access_iterator<firstIsConst, T> const & dsd) {
//			return dsd.getPointer() - n;
//		}
//
//		template<bool firstIsConst, class T>
//		reference operator+(size_t n, random_access_iterator<firstIsConst, T> const & dsd) {
//			return dsd.getPointer() + n;
//		}
//
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		bool operator>(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() > dsd.getPointer();
//		}
//
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		bool operator>=(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() > dsd.getPointer();
//		}
//
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		bool operator<(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() > dsd.getPointer();
//		}
//
//		template<bool firstIsConst, bool secondIsConst, class T1, class T2>
//		bool operator<=(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
//			return dsa.getPointer() > dsd.getPointer();
//		}
		
	private:
		pointer _pointer;
	};
	
	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator==(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
		return dsa.getPointer() == dsd.getPointer();
	}

	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator!=(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
		return dsa.getPointer() != dsd.getPointer();
	}

	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	typename random_access_iterator<firstIsConst, T1>::difference_type operator-(random_access_iterator<firstIsConst, T1> const & dsa,
				random_access_iterator<secondIsConst, T2> const & dsd) {
		return dsa.getPointer() - dsd.getPointer();
	}

//	template<bool firstIsConst, class T>
//	typename random_access_iterator<firstIsConst, T>::reference operator-(size_t n, random_access_iterator<firstIsConst, T> const & dsd) {
//		return dsd.getPointer() - n;
//	}
	
//	template<bool firstIsConst, class T>
//	random_access_iterator<firstIsConst, T> operator+(int n) {
//		return this->getPointer() + n;
//	}
	
//	template<bool firstIsConst, class T>
//	typename random_access_iterator<firstIsConst, T>::reference operator+(size_t n, random_access_iterator<firstIsConst, T> const & dsd) {
//		return dsd.getPointer() + n;
//	}

	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator>(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
		return dsa.getPointer() > dsd.getPointer();
	}

	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator>=(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
		return dsa.getPointer() >= dsd.getPointer();
	}

	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator<(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
		return dsa.getPointer() < dsd.getPointer();
	}

	template<bool firstIsConst, bool secondIsConst, class T1, class T2>
	bool operator<=(random_access_iterator<firstIsConst, T1> const & dsa, random_access_iterator<secondIsConst, T2> const & dsd) {
		return dsa.getPointer() <= dsd.getPointer();
	}
}