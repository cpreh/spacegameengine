#ifndef MATHSTUFF_HPP_INCLUDED
#define MATHSTUFF_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <sge/math/rect.hpp>
#include "accessor.hpp"

struct plane
{
	accessor<sge::math::vector3> point,normal;

	plane() {}
	plane(const sge::math::vector3 &point,const sge::math::vector3 &normal) : point(point),normal(normal) {}
};
inline std::ostream &operator<<(std::ostream &stream,const plane &t) { return stream << "(" << t.normal() << "," << t.point() << ")"; }

struct triangle
{
	accessor<sge::math::vector3> a,b,c;

	triangle() {}
	triangle(const sge::math::vector3 &a,const sge::math::vector3 &b,const sge::math::vector3 &c) : a(a),b(b),c(c) {}
};
inline std::ostream &operator<<(std::ostream &stream,const triangle &t) { return stream << "(" << t.a() << "," << t.b() << "," << t.c() << ")"; }

struct line
{
	accessor<sge::math::vector3> point,direction;

	line() {}
	line(const sge::math::vector3 &point,const sge::math::vector3 &direction) : point(point),direction(direction) {}
};
inline std::ostream &operator<<(std::ostream &stream,const line &t) { return stream << "(" << t.point() << "," << t.direction() << ")"; }

inline sge::math::vector2 normal(const sge::math::vector2 &a)
{
	return sge::math::vector2(a.y(),-a.x());
}

inline sge::math::vector2 invnormal(const sge::math::vector2 &a)
{
	return sge::math::vector2(-a.y(),a.x());
}

struct frustum_info
{
	accessor<sge::math::vector3> pos;
	accessor<sge::space_unit> rot,fov;
	accessor<sge::math::vector3> left_dir,right_dir;
	accessor<plane> left,right;
	
	frustum_info() {}
	frustum_info(const sge::math::vector3 &,const sge::space_unit fov,const sge::space_unit rot);
	void fill(const sge::math::vector3 &,const sge::space_unit,const sge::space_unit);
};
inline std::ostream &operator<<(std::ostream &stream,const frustum_info &t) { return stream << "(pos=" << t.pos() << ",rot=" << t.rot() << ",fov=" << t.fov() << ",left_dir=" << t.left_dir() << ",right_dir=" << t.right_dir() << ")"; }

// Gibt zurueck, ob ein Punkt in 'nem Rect ist
inline bool point_inside_2d(const sge::math::vector2 &v,const sge::math::rect &rect)
{
	// Achtung! Angepasst an negative Z-Achse!
	if (v.x() < rect.left || v.x() > rect.right || v.y() > rect.bottom || v.y() < rect.top)
		return false;
	return true;
}

// Gibt zurueck, ob ein Punkt in einem Dreieck ist
inline bool point_inside_2d(const sge::math::vector2 &point,const plane &pa,const plane &pb,const plane &pc)
{
	if (sge::math::dot(sge::math::vector3(point) - pa.point(),pa.normal()) > 0)
		return false;
	if (sge::math::dot(sge::math::vector3(point) - pb.point(),pb.normal()) > 0)
		return false;
	if (sge::math::dot(sge::math::vector3(point) - pc.point(),pc.normal()) > 0)
		return false;
	return true;
}

inline bool almost_zero(const sge::space_unit &a)
{
	return a > -0.001 && a < 0.001;
}

// See http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
bool line_intersection_2d(const line &,const line &,sge::space_unit &,sge::space_unit &);

// Gibt zurueck, ob sich zwei Geradenabschnitte ueberschneiden
bool line_segments_intersect_2d(const line &,const line &);

// Gibt zurueck, ob ein Dreieck sich mit einem Rect ueberschneidet
bool triangle_inside_2d(const triangle &,const sge::math::rect &);

// Gibt zurueck, ob ein Punkt _vor_ der Ebene ist (also der Normalenvektor darauf zeigt)
inline bool in_front(const plane &p,const sge::math::vector3 &a)
{
	return sge::math::dot(a - p.point(),p.normal()) > 0;
}

// Gibt zurueck, ob ein Rechteck komplett im Frustum ist
bool completely_inside(const sge::math::rect &,const frustum_info &);

// Gibt zurueck, ob ein Rechteck nur teilweise (aber nicht komplett!) im Frustum ist
bool partially_inside(const sge::math::rect &,const frustum_info &);

#endif
