#ifndef SGE_ALGORITHM_HPP_INCLUDED
#define SGE_ALGORITHM_HPP_INCLUDED

#include <memory>
#include <algorithm>
#include <boost/type_traits/is_pod.hpp>

namespace sge
{
	template<typename In, typename Out> inline
		Out* memcpy(const In* first, const In* last, Out* dest)
	{
		std::memcpy(dest,first,(last-first)*sizeof(In));
		return dest + (last - first);
	}

	template<typename In, typename Out> inline
		Out* _copy(In* first, In* last, Out* dest, boost::true_type)
	{
		return sge::memcpy(first,last,dest);
	}

	template<typename In, typename Out> inline
		Out* _copy(In* first, In* last, Out* dest, boost::false_type)
	{
		return std::copy(first,last,dest);
	}

	template<typename In, typename Out> inline
		Out* copy(In* first, In* last, Out* dest)
	{
		return _copy(first,last,dest, typename boost::is_pod<In>::type());
	}

	template<typename InputIterator, typename Size, typename T>
		InputIterator find_nth(InputIterator first, InputIterator last, Size count, const T& t)
		{
			Size c = 0;
			for(; first != last; ++first)
			{
				if(t==*first)
				{
					++c;
					if(c==count) 
						return first; 
				}
			}
			return last;
		}
	template<typename InputIterator, typename Size, typename UnaryPredicate>
		InputIterator find_nth_if(InputIterator first, InputIterator last, Size count, UnaryPredicate pred)
		{
			Size c = 0;
			for(; first != last; ++first)
			{
				if(pred(*first))
				{
					++c;
					if(c==count)
						return first;
				}
			}
			return last;
		}

	template<typename T> struct bit_and_fun {
		T operator()(T a, T b) const { return a&b; }
	};
}

#endif
