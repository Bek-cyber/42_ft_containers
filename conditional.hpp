#pragma once

namespace ft {

	template<bool B, class T, class F>
	struct conditional { typedef T type; };

	template<class T, class F>
	struct conditional<false, T, F> {
		typedef F type;
	};
}