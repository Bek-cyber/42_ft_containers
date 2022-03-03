#pragma once

#include <memory>
#include "../conditional/conditional.hpp"
#include <cstddef>
#include <iterator>

namespace ft {
	
	template <class Iterator>
	class reverse_iterator {
	
	public:
		typedef std::ptrdiff_t	difference_type;
		
		reverse_iterator ():iterator_(NULL) {}
		
		explicit reverse_iterator (Iterator it):iterator_(it)  {}
		
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) {
			iterator_ = rev_it.getIterator();
		}
		
		template <class Iter>
		reverse_iterator& operator= (const reverse_iterator<Iter>& othe_it) {
			if (this == &othe_it) { return *this; }
			iterator_ = othe_it.getIterator();
			return *this;
		}
		
		~reverse_iterator () {}
		
		Iterator const getIterator() const {
			return iterator_;
		}
		
		typename Iterator::reference operator*() {
			return *iterator_;
		}
		
		typename Iterator::reference operator->() {
			return iterator_;
		}
		
		reverse_iterator operator+ (difference_type n) const {
			return iterator_ - n;
		}
		
		reverse_iterator operator- (difference_type n) const {
			return iterator_ + n;
		}
		
		reverse_iterator& operator--() {
			++iterator_;
			return *this;
		}
		
		reverse_iterator& operator--(int) {
			reverse_iterator tmp(*this);
			++iterator_;
			return tmp;
		}
		
		reverse_iterator& operator++() {
			--iterator_;
			return *this;
		}
		
		reverse_iterator& operator++(int) {
			reverse_iterator tmp(*this);
			--iterator_;
			return tmp;
		}
		
		reverse_iterator& operator+= (difference_type n) {
			iterator_ -= n;
			return *this;
		}
		
		reverse_iterator& operator-= (difference_type n) {
			iterator_ += n;
			return *this;
		}
		
		typename Iterator::reference operator[] (difference_type n) const {
			return *(iterator_ - n);
		}
		
	private:
		Iterator iterator_;
	};
	
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.getIterator() == rhs.getIterator();
	}
	
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.getIterator() != rhs.getIterator();
	}
	
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.getIterator() > rhs.getIterator();
	}
	
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.getIterator() >= rhs.getIterator();
	}
	
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.getIterator() < rhs.getIterator();
	}
	
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.getIterator() <= rhs.getIterator();
	}
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return rev_it.getIterator() - n;
	}
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
		return lhs.getIterator() + rhs.getIterator();
	}
}