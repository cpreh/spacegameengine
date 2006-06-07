#ifndef SGE_LINE2_HPP_INCLUDED
#define SGE_LINE2_HPP_INCLUDED

#include "./vector2.hpp"

namespace sge
{
	template<typename T> class line2 {
	public:
		typedef vector2<T> point;
		line2(const point o, point d) : o(o), d(d) {}
		bool intersects(const line2& r) const
		{
			const T& a1 = d.x, a2 = d.y, a3 = r.d.x, a4 = r.d.y;
			return (a2*a3 - a1*a4);
		}
	private:
		point o,d;
	};
	template<typename T> inline bool intersects(const line2<T>& l, const line2<T>& r)
	{
		return l.intersects(r);
	}
}

#endif
