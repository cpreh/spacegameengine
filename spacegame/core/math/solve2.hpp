#ifndef SGE_SOLVE2_HPP_INCLUDED
#define SGE_SOLVE2_HPP_INCLUDED

namespace sge
{

template<typename T> inline T determinant2(const T& a1, const T& a2, const T& a3, const T& a4)
{
	return a1*a4 - a2*a3;
}

template<typename T> inline bool solve2(const T& a1, const T& a2, const T& a3, const T& a4, const T& r1, const T& r2, T& x1, T& x2)
{
	const T det = determinant2(a1,a2,a3,a4);
	if(det==0)
		return false;
	x1 = (a4*r1 - a3*r2) / det;
	x2 = (a1*r2 - a2*r1) / det;
	return true;
}

}

#endif
