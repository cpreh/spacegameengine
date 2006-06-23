#ifndef SGE_RAY2_HPP_INCLUDED
#define SGE_RAY2_HPP_INCLUDED

#include "./vector2.hpp"
#include "./solve2.hpp"
#include "./line_seg2.hpp"

namespace sge
{
template<typename T> class ray2 {
public:
	typedef vector2<T> vec;
	ray2(vec o, vec d) : o(o), d(d) {}
	bool intersection(const line_seg2<T>& r, vec& v) const 
	{
		T x1,x2;
		if(!solve2(d.x,d.y,-r.d.x,-r.d.y,r.p.x-o.x,r.p.y-o.y,x1,x2))
			return false;
		if(x1 < 0 || x2 < 0 || x2 > 1)
			return false;
		v = vec(o.x + x1*d.x, o.y + x1*d.y);
		return true;
	}
private:
	vec o,d;
};

template<typename T> inline bool intersection(const ray2<T>& l, const line_seg2<T>& r, typename ray2<T>::vec& v)
{
	return l.intersection(r,v);
}

}

#endif
