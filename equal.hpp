#ifndef INC_42_FT_CONTAINERS_EQUAL_HPP
#define INC_42_FT_CONTAINERS_EQUAL_HPP

namespace ft {
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
}

#endif //INC_42_FT_CONTAINERS_EQUAL_HPP
