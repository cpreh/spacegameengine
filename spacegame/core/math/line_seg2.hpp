#ifndef SGE_LINE_SEG2_HPP_INCLUDED
#define SGE_LINE_SEG2_HPP_INCLUDED

#include "./vector2.hpp"
#include "./solve2.hpp"

namespace sge
{
	template<typename T> class ray2;

	template<typename T> class line_seg2 {
		friend class ray2<T>;
	public:
		typedef vector2<T> vec;
		line_seg2(vec p, vec q) : p(p), d(q-p) {}
		bool intersects(const line_seg2& r) const
		{
			T x1,x2;
			if(!solve2(d.x,d.y,-r.d.x,-r.d.y,r.p.x-p.x,r.p.y-p.y,x1,x2))
				return false;
			return !(x1 < 0 || x1 > 1 || x2 < 0 || x2 > 1);
		}
	private:
		vec p,d;
	};

	template<typename T> inline bool intersects(const line_seg2<T>& l, const line_seg2<T>& r)
	{
		return l.intersects(r);
	}
}

#endif
