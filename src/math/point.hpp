#ifndef SGE_POINT_HPP_INCLUDED
#define SGE_POINT_HPP_INCLUDED

namespace sge
{

template<typename T> class basic_point {
public:
	typedef T value_type;
	basic_point(const value_type& x = value_type(), const value_type& y = value_type())
		: x(x), y(y) {}
	value_type x,y;
};

}

#endif
