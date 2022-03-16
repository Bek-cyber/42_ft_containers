#ifndef INC_42_FT_CONTAINERS_PAIR_HPP
#define INC_42_FT_CONTAINERS_PAIR_HPP

namespace ft {
	template <typename T1, typename T2>
	struct pair {
		typedef T1 firstType;
		typedef T2 secondType;
		
		firstType first_;
		secondType second_;
		
		pair() {
			first_ = firstType();
			second_ = secondType();
		};
		
		template<typename U, typename V>
		pair(const pair<U, V> &pr) {
			first_ = firstType(pr.first_);
			second_ = secondType(pr.second_);
		};
		
		pair(const firstType & first, const secondType & second) {
			first_ = first;
			second_ = second;
		};
		
		pair& operator=(const pair& pr) {
			if (this == &pr)
				return *this;
			first_ = pr.first_;
			second_ = pr.second_;
			return *this;
		};
	};
	
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}
	
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs==rhs);
	}
	
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}
	
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(rhs<lhs);
	}
	
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return rhs<lhs;
	}
	
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs<rhs);
	}
	
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 first, T2 second)
	{
		return ( pair<T1,T2>(first, second) );
	}
}

#endif //INC_42_FT_CONTAINERS_PAIR_HPP
