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
			while (parent == RED) {
				if (parent == parent->parent->leftNode) {
					nodePtr uncle = z->parent->rightNode;
					if (isEmpty(uncle) == false && uncle->color == RED) {
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
					if (isEmpty(uncle) == false && uncle->color == RED) {
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
			while (x != root_ && x->color == BLACK) {
				if (x == x->parentNode->leftNode) {
					brother = x->parentNode->rightNode;
					if (brother->color == RED) {
						x->color = BLACK
						x->parentNode->color = RED
						rotateToLeft(x);
						brother = x->parentNode->rightNode;
					}
					if (brother->leftNode->color == BLACK && brother->rightNode->color == BLACK) {
						brother->color = RED
						x = x->parentNode;
					}
					else {
						if (brother->rightNode->color == BLACK) {
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
					brother = x->parentNode->leftNode;
					if (brother->color == RED) {
						x->color = BLACK
						x->parentNode->color = RED
						rotateToRight(x);
						brother = x->parentNode->leftNode;
					}
					if (brother->leftNode->color == BLACK && brother->rightNode->color == BLACK) {
						brother->color = RED
						x = x->parentNode;
					}
					else {
						if (brother->leftNode->color == BLACK) {
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
				x-.parerntNode->rightNode = z;
			z->parentNode = x->parentNode;
		}
		
		bool isEmpty(nodePtr node) {
			return node == nill_ || node->isEnd == true;
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