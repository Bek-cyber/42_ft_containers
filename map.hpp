#ifndef INC_42_FT_CONTAINERS_MAP_HPP
#define INC_42_FT_CONTAINERS_MAP_HPP

#include <iostream>
#include "pair.hpp"
#include "reverse_iterators.hpp"
#include "bidirectional_iterator.hpp"
#include "redBlackTree.hpp"

namespace ft {
	
	template < class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map {
	
	public:
		typedef Key											keyType;
		typedef T											mappedType;
		typedef ft::pair<Key, T>							valueType;
		typedef Compare										keyCompare;
		typedef Alloc										allocatorType;
		typedef typename allocatorType::reference					reference;
		typedef typename allocatorType::cosnt_reference				constReference;
		typedef typename allocatorType::pointer						pointer;
		typedef typename allocatorType::const_pointer				constPointer;
		typedef bidirectional_iterator<false, valueType>	iterator;
		typedef bidirectional_iterator<true, valueType>		constIterator;
		typedef reverse_iterator<iterator>					reverseIterator;
		typedef reverse_iterator<constIterator>				constReverseIterator;
		typedef size_t 										sizeType;
		typedef ptrdiff_t 									differenceType;
		
	private:
		typedef redBlackTree<valueType, keyCompare , allocatorType>	redBlackTreeType;
		
		class value_compare
		{
			friend class map;
		protected:
			Compare comp;
			
			value_compare(Compare c){
				comp = c;
			}
		
		public:
			typedef bool	result_type;
			typedef			valueType first_argument_type;
			typedef			valueType second_argument_type;
			
			bool operator()(const valueType& x, const valueType& y) const {
				return comp(x.first, y.first);
			}
		};
		
	public:
		explicit map (const keyCompare& comp = keyCompare(),
					  const allocatorType& alloc = allocatorType()) {
			rbTree(comp, alloc);
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
	   			const keyCompare& comp = keyCompare(),
				const allocatorType& alloc = allocatorType()) {
			rbTree(comp, alloc);
			rbTree.insertToRBT(first, last);
		}

		map (const map& copy) {
			rbTree = copy.rbTree;
			rbTree.insert(copy.begin(), copy.end());
		}
		
		~map() {};
		
		map& operator=(const map & other) {
			if (this == &other)
				return *this;
			if (rbTree)
				rbTree.clear();
			this = rbTree(other);
			insert(other.begin(), other.end());
			return *this;
		}
		
		allocatorType getAllocator() const {
			return rbTree.getAllocator();
		}
		
		iterator begin() {
			return rbTree.begin();
		}
		
		constIterator begin() const {
			return rbTree.begin();
		}
		
		iterator end() {
			return rbTree.end();
		}
		
		constIterator end() const {
			return rbTree.end();
		}
		
		reverseIterator rbegin() {
			return rbTree.rbegin();
		}
		
		constReverseIterator rbegin() const {
			return rbTree.rbegin();
		}
		
		reverseIterator rend() {
			return rbTree.rend();
		}
		
		constReverseIterator rend() const {
			return rbTree.rend();
		}
		
		bool empty() const {
			return rbTree.empty();
		}
		
		sizeType size() const {
			return rbTree.size();
		}
		
		sizeType max_size() const {
			return rbTree.maxSize();
		}
		
		mappedType& operator[] (const keyType& k) {
			return((*((this->insert(ft::make_pair(k, mappedType()))).first)).second);
		}
		
		pair<iterator,bool> insert (const valueType& val) {
			return rbTree.insert(val);
		}
		
		iterator insert (iterator position, const valueType& val) {
			return rbTree.insert(position, val);
		}
		
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			return rbTree.insert(first, last);
		}
		
		void erase (iterator position) {
			rbTree.erase(position);
		}
		
		sizeType erase (const keyType& k) {
			return rbTree.erase(ft::make_pair(k, mappedType()));
		}
		
		void erase (iterator first, iterator last) {
			rbTree.erase(first, last);
		}
		
		void swap(map& x) {
			rbTree.swap(x._tree);
		}
		
		void clear() {
			rbTree.clear();
		}
		
		keyCompare key_comp() const {
			return rbTree.value_comp().comp;
		}
		
		value_compare value_comp() const {
			return rbTree.value_comp();
		}
		
		iterator find (const keyType& k) {
			return rbTree.find(ft::make_pair(k, mappedType()));
		}
		
		constIterator find (const keyType& k) const {
			return rbTree.find(ft::make_pair(k, mappedType()));
		}
		
		sizeType count (const keyType& k) const {
			return rbTree.count(ft::make_pair(k, mappedType()));
		}
		
		iterator lower_bound (const keyType& k) {
			return rbTree.lower_bound(ft::make_pair(k, mappedType()));
		}
		
		constIterator lower_bound (const keyType& k) const {
			return rbTree.lower_bound(ft::make_pair(k, mappedType()));
		}
		
		iterator upper_bound (const keyType& k) {
			return rbTree.upper_bound(ft::make_pair(k, mappedType()));
		}
		
		constIterator upper_bound (const keyType& k) const {
			return rbTree.upper_bound(ft::make_pair(k, mappedType()));
		}
		
		pair<constIterator,constIterator> equal_range (const keyType& k) const {
			return rbTree.equal_range(ft::make_pair(k, mappedType()));
		}
		
		pair<iterator,iterator> equal_range (const keyType& k) {
			return  rbTree.equal_range(ft::make_pair(k, mappedType()));
		}

	private:
		redBlackTreeType	rbTree;
	};
}

#endif //INC_42_FT_CONTAINERS_MAP_HPP