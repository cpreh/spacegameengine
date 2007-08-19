#ifndef MATHSTUFF_HPP_INCLUDED
#define MATHSTUFF_HPP_INCLUDED

#include <ostream>
#include "../../src/math/vector.hpp"
#include "../../src/math/matrix.hpp"
#include "../../src/math/rect.hpp"
#include "../../src/accessor.hpp"

// FIXME: Accessor wegnehmen
namespace sge
{
struct plane
{
	math::vector3 n;
	space_unit d;

	plane() {}
	plane(const math::vector3 &n,const space_unit d) : n(n),d(d) {}
	plane(const math::vector3 &r,const math::vector3 &_n) : n(_n) 
	{
		n = math::normalize(n);
		//d = math::dot(-n,r);
	//	d = (-math::dot(n,r))/n.length();
		d = -math::dot(n,r);
	}
};

struct triangle
{
	accessor<math::vector3> a,b,c;

	triangle() {}
	triangle(const math::vector3 &a,const math::vector3 &b,const math::vector3 &c) : a(a),b(b),c(c) {}
};

struct line
{
	accessor<math::vector3> point,direction;

	line() {}
	line(const math::vector3 &point,const math::vector3 &direction) : point(point),direction(direction) {}
};

inline math::vector2 normal(const math::vector2 &a)
{
	return math::vector2(a.y(),-a.x());
}

inline math::vector2 invnormal(const math::vector2 &a)
{
	return math::vector2(-a.y(),a.x());
}

struct frustum_info
{
	plane left,right,top,bottom;
	
	frustum_info() {}
	frustum_info(math::space_matrix projection);
};

// Gibt zurueck, ob ein Punkt in 'nem Rect ist
inline bool point_inside_2d(const math::vector2 &v,const math::rect &rect)
{
	// Achtung! Angepasst an negative Z-Achse!
	if (v.x() < rect.left || v.x() > rect.right || v.y() > rect.bottom || v.y() < rect.top)
		return false;
	return true;
}

// Gibt zurueck, ob ein Punkt in einem Dreieck ist
inline bool point_inside_2d(const math::vector3 &point,const plane &pa,const plane &pb,const plane &pc)
{
	if (math::dot(pa.n,point) + pa.d > 0)
		return false;
	if (math::dot(pb.n,point) + pb.d > 0)
		return false;
	if (math::dot(pc.n,point) + pc.d > 0)
		return false;
	return true;
}

inline bool almost_zero(const space_unit &a)
{
	return a > -0.001 && a < 0.001;
}

// See http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
bool line_intersection_2d(const line &,const line &,space_unit &,space_unit &);

// Gibt zurueck, ob sich zwei Geradenabschnitte ueberschneiden
bool line_segments_intersect_2d(const line &,const line &);

// Gibt zurueck, ob ein Dreieck sich mit einem Rect ueberschneidet
bool triangle_inside_2d(const triangle &,const math::rect &);

// Gibt zurueck, ob ein Punkt _vor_ der Ebene ist (also der Normalenvektor darauf zeigt)
inline bool in_front(const plane &p,const math::vector3 &a)
{
	//return math::dot(a - p.point(),p.normal()) > 0;
	return math::dot(p.n,a) + p.d > 0;
}

// Gibt zurueck, ob ein Rechteck komplett im Frustum ist
bool completely_inside(const math::rect &,const frustum_info &);

// Gibt zurueck, ob ein Rechteck nur teilweise (aber nicht komplett!) im Frustum ist
bool partially_inside(const math::rect &,const frustum_info &);

// Gibt zurueck, ob ein Rechteck eventuell im Frustum ist
bool possibly_inside(const math::rect &,const frustum_info &);
}

#endif
