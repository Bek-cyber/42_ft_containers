#pragma once

#include <functional>
#include "bidirectional_iterator.hpp"
#include "reverse_iterators.hpp"
//#include "bidirectional_iterator.hpp"

#define BLACK	false;
#define RED		true;

namespace ft {
	
	template <class T,
			class Compare = std::less<T>,
			class Allocator = std::allocator<T> >
	class redBlackTree {
	public:
		typedef T                                          	valueType;
		typedef Compare                                    	valueComapre;
		typedef Allocator                                  	allocatorValueType;
		typedef typename allocatorValueType::size_type   	sizeType;
		typedef rbtNode<T>									rbtNode;
		typedef typename rbtNode::nodePtr              		nodePtr;
		typedef typename Allocator::template
		        rebind<rbtNode>::other        				allocatorNodeType;

		typedef bidirectional_iterator<true, T>				constIterator;
		typedef bidirectional_iterator<false, T>			iterator;
		reverse_iterator<constIterator>						constReverseIterator;
		reverse_iterator<iterator>							reverseIterator;
		
		explicit redBlackTree(const valueComapre & compareObject, const allocatorValueType & allocatorObject) {
			compare_ = compareObject;
			valueAllocator_ = allocatorObject;
			root_(NULL);
			nill_(NULL);
			size_(0);

			end_ = nodeAllocator_.allocate(1);
			valueAllocator_.constrcut(&(end_->value), valueType());
			end_->color = BLACK
			end_->isEnd = true;
			end_->rightNode = nill_;
			end_->leftNode = nill_;

			rend_ = nodeAllocator_.allocate(1);
			valueAllocator_.constrcut(&(rend_->value), valueType());
			rend_->isBlackColor = true;
			rend_->isEnd = true;
			rend_->rightNode = nill_;
			rend_->leftNode = nill_;
		}

		redBlackTree(const redBlackTree & other) {
			compare_ = other.compare_;
			valueAllocator_ = other.valueAllocator_;
			root_(NULL);
			nill_(NULL);
			size_(0);

			end_ = nodeAllocator_.allocate(1);
			valueAllocator_.constrcut(&(end_->value), valueType());
			end_->color = BLACK
			end_->isEnd = true;
			end_->rightNode = nill_;
			end_->leftNode = nill_;

			rend_ = nodeAllocator_.allocate(1);
			valueAllocator_.constrcut(&(rend_->value), valueType());
			rend_->isBlackColor = true;
			rend_->isEnd = true;
			rend_->rightNode = nill_;
			rend_->leftNode = nill_;
		}

		redBlackTree() {
			compare_ =valueComapre();
			valueAllocator_ = allocatorValueType ();
			root_(NULL);
			nill_(NULL);
			size_(0);

			end_ = nodeAllocator_.allocate(1);
			valueAllocator_.constrcut(&(end_->value), valueType());
			end_->color = BLACK
			end_->isEnd = true;
			end_->rightNode = nill_;
			end_->leftNode = nill_;

			rend_ = nodeAllocator_.allocate(1);
			valueAllocator_.constrcut(&(rend_->value), valueType());
			rend_->isBlackColor = true;
			rend_->isEnd = true;
			rend_->rightNode = nill_;
			rend_->leftNode = nill_;
		}

		~redBlackTree() {
//			clear();
//			deallocateAll();
		}

	private:
		
		void insertToRBT(nodePtr z) {
			if (isEmpty(z) == true) {
				root_ = z;
				z->parentNode = nill_;
			}
			else {
				nodePtr p = root_;
				nodePtr q = nill_;
				while (isEmpty(p) == false) {
					q = p;
					if (z->value < p->value)
						p = p->leftNode;
					else
						p = p->rightNode;
				}
				z->parentNode = q;
				if (z->value < q->value)
					q->leftNode = z;
				else
					q->rightNode = z;
			}
			z->leftNode = nill_;
			z->rightNode = nill_;
			fixInsertion(z);
		}
		
		void fixInsertion(nodePtr z) {
			if (z == root_) {
				z->color = BLACK
				return;
			}
			nodePtr parent = z->parent;
			while (parent == true) {
				if (parent == parent->parent->leftNode) {
					nodePtr uncle = z->parent->rightNode;
					if (isEmpty(uncle) == false && uncle->color == true) {
						parent = BLACK
						uncle = BLACK
						parent->parentNode->color = RED
						z = parent->parentNode;
					} else {
						if (z == z->parent->rightNode) {
							z = z->parent;
							rotateToLeft(z);
						}
						parent->color = BLACK
						parent->parentNode->color = RED
						rotateToRight(parent->parentNode);
					}
				} else {
					nodePtr uncle = z->parent->leftNode;
					if (isEmpty(uncle) == false && uncle->color == true) {
						parent = BLACK
						uncle = BLACK
						parent->parentNode->color = RED
						z = parent->parentNode;
					} else {
						if (z == z->parent->leftNode) {
							z = z->parent;
							rotateToRight(z);
						}
						parent->color = BLACK
						parent->parentNode->color = RED
						rotateToLeft(parent->parentNode);
					}
				}
			}
			root_->color = BLACK
		}
		
		void deleteFromRBT(nodePtr z) {
			nodePtr y = z, x;
			bool yColor = y->color;
			if (isEmpty(z->leftNode) == true) {
				x = z->rightNode;
				transplantRBT(z, z->rightNode);
			}
			else if (isEmpty(z->rightNode) == true) {
				x = z->leftNode;
				transplantRBT(z, z->leftNode);
			}
			else {
				y = minimumNode(z->rightNode);
				yColor = y->color;
				x = y->rightNode;
				if(y->parentNode == z) {
					x->parentNode = z;
				}
				else {
					rbTransplant(y, y->rightNode);
					y->rightNode = z->rightNode;
					y->rightNode->parentNode = y;
				}
				rbTransplant(z, y);
				y->leftNode = z->leftNode;
				y->leftNode->parentNode = y;
				y->color = z->color;
			}
			if(yColor == false)
				deleteFixup(x);
		}
		
		void fixDeletion(nodePtr x) {
			while (x != root_ && x->color == false) {
				if (x == x->parentNode->leftNode) {
					nodePtr brother = x->parentNode->rightNode;
					if (brother->color == true) {
						x->color = BLACK
						x->parentNode->color = RED
						rotateToLeft(x);
						brother = x->parentNode->rightNode;
					}
					if (brother->leftNode->color == false && brother->rightNode->color == false) {
						brother->color = RED
						x = x->parentNode;
					}
					else {
						if (brother->rightNode->color == false) {
							brother->leftNode->color = BLACK
							brother->color = RED
							rotateToRight(brother);
							brother = x->parentNode->rightNode;
						}
						brother->color = x->parentNode->color;
						x->parent->color = BLACK
						brother->rightNode->color = BLACK
						rotateToLeft(x->parentNode);
						x = root_;
					}
				}
				else {
					nodePtr brother = x->parentNode->leftNode;
					if (brother->color == true) {
						x->color = BLACK
						x->parentNode->color = RED
						rotateToRight(x);
						brother = x->parentNode->leftNode;
					}
					if (brother->leftNode->color == false && brother->rightNode->color == false) {
						brother->color = RED
						x = x->parentNode;
					}
					else {
						if (brother->leftNode->color == false) {
							brother->rightNode->color = BLACK
							brother->color = RED
							rotateToLeft(brother);
							brother = x->parentNode->leftNode;
						}
						brother->color = x->parentNode->color;
						x->parent->color = BLACK
						brother->leftNode->color = BLACK
						rotateToRight(x->parentNode);
						x = root_;
					}
				}
			}
			x->color = BLACK
		}
		
		void rotateToLeft(nodePtr x) {
			nodePtr y = x->rightNode;
			x->rightNode = y->leftNode;
			if (isEmpty(y->leftNode) == false)
				y->leftNode->parentNode = x;
			y->parentNode = x->parentNode;
			if (isEmpty(x->parentNode) == true)
				root_ = y;
			else if (x == x->parentNode->leftNode)
				x->parentNode->leftNode = y;
			else
				x->parentNode->rightNode = y;
			y->leftNode = x;
			x->parentNode = y;
		}
		
		void rotateToRight(nodePtr x) {
			nodePtr y = x->leftNode;
			x->leftNode = y->rightNode;
			if (isEmpty(y->rightNode) != false)
				y->rightNode->parentNode = x;
			y->parentNode = x->parentNode;
			if ((isEmpty(x->parent)) == true)
			root_ = y;
			else if (x == x->parentNode->rightNode)
				x->parentNode->rightNode = y;
			else
				x->parentNode->leftNode = y;
			y->rightNode = x;
			x->parentNode = y;
		}
		
		nodePtr minimumNode(nodePtr x) {
			if (isEmpty(x) == false) {
				while (isEmpty(x->leftNode) == false)
					x = x->leftNode;
			}
			return x;
		}
		
		void transplantRBT(nodePtr x, nodePtr z) {
			if (isEmpty(x->parentNode) == true)
				root_ = z;
			else if (x == x->parentNode->leftNode)
				x->parentNode->leftNode = z;
			else
				x->parerntNode->rightNode = z;
			z->parentNode = x->parentNode;
		}
		
		bool isEmpty(nodePtr node) {
			return node == nill_ || node->isEnd == true;
		}
	
	public:
		
		nodePtr link_end_value() {
			if (root_ == NULL) return root_;
			nodePtr x = rb_maximum(root_);
			nodePtr end_ptr = x->rightNode;
			if (end_ptr != NULL) return end_ptr;
			
			end_ptr =  end_;
			end_ptr->parentNode = x;
			x->rightNode = end_ptr;
			return end_ptr;
		}
		
		nodePtr link_end_value() const {
			if (root_ == NULL) return root_;
			nodePtr x = rb_maximum(root_);
			nodePtr end_ptr = x->rightNode;
			if (end_ptr != NULL) return end_ptr;
			
			end_ptr =  end_;
			end_ptr->parentNode = x;
			x->rightNode = end_ptr;
			return end_ptr;
		}
		
		void unlink_end_value() {
			if (root_ == NULL) return;
			nodePtr x = rb_maximum(root_);
			nodePtr end_ptr = x->rightNode;
			if (end_ptr == NULL) return;
			
			end_ptr->parentNode = NULL;
			end_ptr->leftNode = NULL;
			end_ptr->rightNode = NULL;
			x->rightNode = nill_;
			end_ptr = NULL;
		}
		
		nodePtr link_rend_value() {
			if (root_ == NULL) return root_;
			nodePtr x = rb_minimum(root_);
			nodePtr rend_ptr = x->leftNode;
			if (rend_ptr != NULL) return rend_ptr;
			
			rend_ptr =  rend_;
			rend_ptr->parentNode = x;
			x->leftNode = rend_ptr;
			return rend_ptr;
		}
		
		nodePtr link_rend_value() const {
			if (root_ == NULL) return root_;
			nodePtr x = rb_minimum(root_);
			nodePtr rend_ptr = x->leftNode;
			if (rend_ptr != NULL) return rend_ptr;
			
			rend_ptr = rend_;
			rend_ptr->parentNode = x;
			x->leftNode = rend_ptr;
			return rend_ptr;
		}
		
		void unlink_rend_value() {
			if (root_ == NULL) return;
			nodePtr x = rb_minimum(root_);
			nodePtr rend_ptr = x->leftNode;
			if (rend_ptr == NULL) return;
			
			rend_ptr->parentNode = NULL;
			rend_ptr->leftNode = NULL;
			rend_ptr->rightNode = NULL;
			x->leftNode = nill_;
			rend_ptr = NULL;
		}
		
		void insert(const valueType& value) {
			nodePtr z = nodeAllocator_.allocate(1);
			z->color = RED;
			z->is_end_rend = false;
			valueAllocator_.construct(&(z->value), value);
			unlink_end_value();
			unlink_rend_value();
			rb_insert(z);
			size_++;
			link_end_value();
			link_rend_value();
		}
		
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			for (; first != last; ++first)
				insert(*first);
		}
		
		void erase(const valueType &value) {
			if (root_ == NULL) return ;
			nodePtr z = root_;
			
			unlink_end_value();
			unlink_rend_value();
			while (z != NULL && z->value != value)
			{
				if (z->value < value)
					z = z->rightNode;
				else
					z = z->leftNode;
			}
			rb_delete(z);
			size_--;
			link_end_value();
			link_rend_value();
		}
		
		template<class InputIterator>
		void erase(InputIterator it) {
			if (root_ == NULL) return ;
			nodePtr z = root_;
			valueType value = *it;
			
			unlink_end_value();
			unlink_rend_value();
			while (z != NULL && z->value != value)
			{
				if (z->value < value)
					z = z->rightNode;
				else
					z = z->leftNode;
			}
			rb_delete(z);
			size_--;
			link_end_value();
			link_rend_value();
		}
		
		void clear_node(nodePtr z) {
			if (z == NULL || is_nil(z) == true) return;
			clear_node(z->leftNode);
			clear_node(z->rightNode);
			z->parent = NULL;
			z->right = NULL;
			z->left = NULL;
			valueAllocator_.destroy(&z->value);
			nodeAllocator_.deallocate(z, 1);
			z = NULL;
		}
		
		void clear() {
			unlink_end_value();
			unlink_rend_value();
			clear_node(root_);
			root_ = NULL;
			size_ = 0;
		}
		
		void deallocate_end_rend() {
			if (end_ != NULL) {
				valueAllocator_.destroy(&end_->value);
				nodeAllocator_.deallocate(end_, 1);
				end_ = NULL;
			}
			if (rend_ != NULL) {
				valueAllocator_.destroy(&rend_->value);
				nodeAllocator_.deallocate(rend_, 1);
				rend_ = NULL;
			}
		}
		
		
		template<class Key>
		iterator upper_bound(const Key& key) {
			nodePtr tmp = root_;
			nodePtr result = link_end_value();
			while (tmp != NULL) {
				if (compare_(key, tmp->value.first) == true) {
					result = tmp;
					tmp = tmp->leftNode;
				}
				else {
					tmp = tmp->rightNode;
				}
			}
			return (iterator)(result);
		}
		
		template<class Key>
		iterator lower_bound(const Key& key) {
			nodePtr tmp = root_;
			nodePtr result = link_end_value();
			while (tmp != NULL) {
				if (compare_(tmp->value.first, key) == false) {
					result = tmp;
					tmp = tmp->leftNode;
				}
				else {
					tmp = tmp->rightNode;
				}
			}
			return (iterator)(result);
		}
		
		template<class Key>
		constIterator upper_bound(const Key& key) const {
			nodePtr tmp = root_;
			nodePtr result = link_end_value();
			while (tmp != NULL) {
				if (compare_(key, tmp->value.first) == true) {
					result = tmp;
					tmp = tmp->leftNode;
				}
				else {
					tmp = tmp->rightNode;
				}
			}
			return (constIterator)(result);
		}
		
		template<class Key>
		constIterator lower_bound(const Key& key) const {
			nodePtr tmp = root_;
			nodePtr result = link_end_value();
			while (tmp != NULL) {
				if (compare_(tmp->value.first, key) == false) {
					result = tmp;
					tmp = tmp->leftNode;
				}
				else {
					tmp = tmp->rightNode;
				}
			}
			return (constIterator)(result);
		}
		
		template <class Key>
		iterator find(const Key &key) {
			iterator iter = lower_bound(key);
			if (iter != end() && compare_(key, (*iter).first) == false) {
				return iter;
			}
			return end();
		}
		
		template <class Key>
		sizeType count(const Key &key) const {
			nodePtr tmp = root_;
			while (tmp != NULL) {
				if (compare_(key, tmp->value.first)) {
					tmp = tmp->leftNode;
				}
				else if (compare_(tmp->value.first, key)) {
					tmp = tmp->rightNode;
				}
				else return 1;
			}
			return 0;
		}
		
		template <class Key>
		pair<iterator, iterator> equal_range(const Key& key) {
			nodePtr tmp = root_;
			nodePtr res = link_end_value();
			while (tmp != NULL) {
				if (compare_(key, tmp->value.first)) {
					res = tmp;
					tmp = tmp->leftNode;
				}
				else if (compare_(tmp->value.first, key)) {
					tmp = tmp->rightNode;
				}
				else {
					return ft::pair<iterator, iterator>(iterator(tmp),
														iterator(tmp->rightNode != NULL ? rb_minimum(tmp->rightNode) : res));
				}
			}
			return ft::pair<iterator, iterator>(iterator(res), iterator(res));
		}
		
		template <class Key>
		ft::pair<iterator, iterator> equal_range(const Key& key) const {
			nodePtr tmp = root_;
			nodePtr res = link_end_value();
			while (tmp != NULL) {
				if (compare_(key, tmp->value.first)) {
					res = tmp;
					tmp = tmp->leftNode;
				}
				else if (compare_(tmp->value.first, key)) {
					tmp = tmp->rightNode;
				}
				else {
					return ft::pair<constIterator, constIterator>(constIterator(tmp),
																  constIterator(tmp->rightNode != NULL ? rb_minimum(tmp->rightNode) : res));
				}
			}
			return ft::pair<constIterator, constIterator>(constIterator(res),
														  constIterator(res));
		}
		
		sizeType size() const {
			return size_;
		}
		
		bool empty() const {
			return size_ == 0;
		}
		
		sizeType max_size() const {
			return valueAllocator_.max_size();
		}
		
		valueComapre get_value_compare() const {
			return compare_;
		}
		
		allocatorValueType get_allocator() const {
			return valueAllocator_;
		}
		
		void swap(redBlackTree& other) {
			std::swap(this->compare_, other.compare_);
			std::swap(this->value_allocator_, other.value_allocator_);
			std::swap(this->root_, other.root_);
			std::swap(this->nil_, other.nil_);
			std::swap(this->size_, other.size_);
			std::swap(this->end_, other.end_);
			std::swap(this->rend_, other.rend_);
		}
		
		iterator begin() {
			return iterator( size_ == 0 ? root_ : rb_minimum(root_) );
		}
		
		iterator end() {
			return iterator(link_end_value());
		}
		
		constIterator begin() const {
			return iterator( size_ == 0 ? root_ : rb_minimum(root_) );
		}
		
		constIterator end() const {
			return const_iterator(link_end_value());
		}

//		reverseIterator rbegin() {
//			return iterator( size_ == 0 ? root_ : rb_maximum(root_) );
//		}
//
//		reverseIterator rend() {
//			return reverseIterator(link_rend_value());
//		}
//
//		constReverseIterator rbegin() const {
//			return iterator( size_ == 0 ? root_ : rb_maximum(root_) );
//		}
//
//		constReverseIterator rend() const {
//			return constReverseIterator(link_rend_value());
//		}
		
		bool isBalancedUtil(nodePtr root, int &maxh, int &minh) {
			if (root == NULL) {
				maxh = minh = 0;
				return true;
			}
			
			int lmxh, lmnh;
			int rmxh, rmnh;
			
			if (isBalancedUtil(root->left, lmxh, lmnh) == false)
				return false;
			
			if (isBalancedUtil(root->right, rmxh, rmnh) == false)
				return false;
			
			maxh = std::max(lmxh, rmxh) + 1;
			minh = std::min(lmnh, rmnh) + 1;
			
			if (maxh <= 2*minh)
				return true;
			
			return false;
		}
		
		bool isBalanced() {
			unlink_end_value();
			unlink_rend_value();
			int maxh, minh;
			return isBalancedUtil(root_, maxh, minh);
		}
	
	public:
		friend
		bool operator==(const redBlackTree& lhs, const redBlackTree& rhs) {
			return (lhs.size() == rhs.size() &&
					ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
		
		friend
		bool operator<(const redBlackTree& lhs,  const redBlackTree& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end()));
		}
		
		friend
		bool operator>(const redBlackTree& lhs,  const redBlackTree& rhs) {
			return (lhs < rhs);
		}

	private:
		valueComapre			compare_;
		allocatorValueType		valueAllocator_;
		allocatorNodeType		nodeAllocator_;
		nodePtr					root_; /* указатель на корень */
		nodePtr					nill_; /* указатель на пустоту */
		sizeType				size_; /* размер */
		nodePtr					end_; /* указатель на конец */
		nodePtr					rend_; /* указатель на "начало" */
	};
}