#include <iostream>
#include <cmath>
#include "../../src/math/constants.hpp"
#include "mathstuff.hpp"

sge::frustum_info::frustum_info(const sge::math::vector3 &_pos,const sge::space_unit _fovy,const sge::space_unit _rot,const sge::space_unit near,const sge::space_unit far,const sge::space_unit aspect)
	: pos(_pos),rot(_rot),fovy(_fovy),near(near),far(far),aspect(aspect)
{
	space_unit hnear = 2*std::tan(fovy()/2)*near,wnear = 2 * hnear * aspect;
	fovx(2*std::atan((wnear/2)/near));

	// Richtung der rechten Clipping Plane.
	space_unit angle_right = rot()+fovx()/2,angle_left = rot()-fovx()/2;
	
	right_dir(math::vector3(std::sin(angle_right),0,-std::cos(angle_right)));
	left_dir(math::vector3(std::sin(angle_left),0,-std::cos(angle_left)));

	// Normale der rechten Clipping Plane. Diese muss, da es im Uhrzeigersinn ist, invnormal sein.
	math::vector2 rightnormal = invnormal(math::vector2(right_dir().x(),right_dir().z()));
	// Hier allerdings normal, da gegen den Uhrzeigersinn
	math::vector2 leftnormal = normal(math::vector2(left_dir().x(),left_dir().z()));

	std::wcout << L"rightnormal=" << rightnormal << L"\n";

	// Und die beiden Planes zusammensetzen
	left(plane(pos(),math::normalize(math::vector3(leftnormal.x(),0,leftnormal.y()))));
	right(plane(pos(),math::normalize(math::vector3(rightnormal.x(),0,rightnormal.y()))));
}

// See http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
bool sge::line_intersection_2d(const line &a,const line &b,sge::space_unit &a_mult,sge::space_unit &b_mult)
{
	// The demoninators for both equations are equal
	space_unit denominator = b.direction().y()*a.direction().x()-b.direction().x()*a.direction().y();
	
	// If the denominator is 0 the lines are parallel => no point of
	// intersection
	if (almost_zero(denominator))
		return false;
	
	space_unit a_numerator = b.direction().x()*(a.point().y()-b.point().y())-b.direction().y()*(a.point().x()-b.point().x());
	space_unit b_numerator = a.direction().x()*(a.point().y()-b.point().y())-a.direction().y()*(a.point().x()-b.point().x());
	a_mult = a_numerator / denominator;
	b_mult = b_numerator / denominator;

	return true;
}

// Gibt zurueck, ob sich zwei Geradenabschnitte ueberschneiden
bool sge::line_segments_intersect_2d(const line &a,const line &b)
{
	space_unit a_mult,b_mult;

	if (!line_intersection_2d(a,b,a_mult,b_mult))
		return false;
	
	return a_mult > 0 && b_mult > 0 && a_mult <= 1 && b_mult <= 1;
}

// Gibt zurueck, ob ein Dreieck sich mit einem Rect ueberschneidet
bool sge::triangle_inside_2d(const triangle &t,const sge::math::rect &rect)
{
	// Punkte des Dreiecks, zweidimensional
	math::vector2 A = math::vector2(t.a().x(),t.a().y()),
										 B = math::vector2(t.b().x(),t.b().y()),
										 C = math::vector2(t.c().x(),t.c().y());
	
	// 1. Fall: Mindestens ein Punkt des Dreiecks im Quadrat
	if (point_inside_2d(A,rect) || 
			point_inside_2d(B,rect) || 
			point_inside_2d(C,rect))
		return true;

	// 2. Fall: Mindestens ein Punkt des Quadrats ist im Rechteck
	math::vector2 lefttop(rect.left,rect.top);
	math::vector2 righttop(rect.right,rect.top);
	math::vector2 leftbottom(rect.left,rect.bottom);
	math::vector2 rightbottom(rect.right,rect.bottom);
	
	// Seiten des Dreiecks
	math::vector2 a = B - A,b = C - B,c = A - C;

	// Ebenen der Seiten
	plane pa(t.a(),normal(a));
	plane pb(t.b(),normal(b));
	plane pc(t.c(),normal(c));

	if (point_inside_2d(lefttop,pa,pb,pc) || point_inside_2d(righttop,pa,pb,pc) || point_inside_2d(leftbottom,pa,pb,pc) || point_inside_2d(rightbottom,pa,pb,pc))
		return true;
	
	// 3. Fall: Die Strukturen schneiden sich, enthalten aber gegenseitig keine Punkte
	
	// Seiten des Dreiecks als Gerade
	line la(A,a),lb(B,b),lc(C,c);
	// Seiten des Vierecks als Gerade
	line rla(leftbottom,rightbottom - leftbottom),rlb(rightbottom,righttop - rightbottom);
	line rlc(righttop,lefttop - righttop),rld(lefttop,leftbottom - lefttop);

	if (line_segments_intersect_2d(la,rla) || line_segments_intersect_2d(la,rlb) || line_segments_intersect_2d(la,rlc) || line_segments_intersect_2d(la,rld))	
		return true;
	if (line_segments_intersect_2d(lb,rlb) || line_segments_intersect_2d(lb,rlb) || line_segments_intersect_2d(lb,rlc) || line_segments_intersect_2d(lb,rld))	
		return true;
	if (line_segments_intersect_2d(lc,rla) || line_segments_intersect_2d(la,rlb) || line_segments_intersect_2d(la,rlc) || line_segments_intersect_2d(la,rld))	
		return true;
	
	return false;
}

// Gibt zurueck, ob ein Rechteck komplett im Frustum ist
bool sge::completely_inside(const sge::math::rect &rect,const sge::frustum_info &frustum)
{
	// Ein Rechteck ist komplett drin, wenn alle Vertizes rechts von oder auf der linken Clipping Plane
	// und gleichzeitig links von oder auf der rechten Clipping Plane sind
	
	// Eckpunkte des Rects
	math::vector3 lt(rect.left,0,rect.top),rt(rect.right,0,rect.top),lb(rect.left,0,rect.bottom),rb(rect.right,0,rect.bottom);
	return !in_front(frustum.left(),lt) && !in_front(frustum.left(),rt) && !in_front(frustum.left(),lb) && !in_front(frustum.left(),rb) && 
				 !in_front(frustum.right(),lt) && !in_front(frustum.right(),rt) && !in_front(frustum.right(),lb) && !in_front(frustum.right(),rb);
}

bool sge::possibly_inside(const sge::math::rect &rect,const sge::frustum_info &frustum)
{
	const math::vector3 center = math::vector3(rect.left + rect.width()/2,0,rect.top + rect.height()/2);
	const space_unit radius(std::sqrt(rect.width()*rect.width()/4+rect.height()*rect.height()/4));

	const math::vector3 forward_dir = math::normalize(math::vector3(std::sin(frustum.rot()),0,-std::cos(frustum.rot())));
	const space_unit df = math::dot(forward_dir,frustum.pos());

	// Man spannt von der Spielerposition aus eine Ebene mit Normalenvektor in Blickrichtung auf und guckt,
	// ob das Objekt weiter als -radius von der Ebene entfernt ist. Ist dem so, ist das Objekt zu weit hinter dem Spieler
	if (math::dot(forward_dir,center) - df < -radius)
	{
		std::cout << "Komplett hinter dem Spieler.\n";
		return false;
	}

	const math::vector3 nl = math::normalize(frustum.left().normal());
	const space_unit dl = math::dot(nl,frustum.left().point());

	if (math::dot(nl,center) - dl > radius)
		return false;
	//if (std::fabs(math::dot(nl,center) - dl) <= radius)
	//	return true;

	const math::vector3 nr = math::normalize(frustum.right().normal());
	const space_unit dr = math::dot(nr,frustum.right().point());

	if (math::dot(nr,center) - dr > radius)
		return false;
	//if (std::fabs(math::dot(nr,center) - dr) <= radius)
	//	return true;

	return true;
}

bool sge::partially_inside(const sge::math::rect &rect,const sge::frustum_info &frustum)
{
	// Wenn etwas nur teilweise im Frustum ist, schneiden sich die Frustumseiten mit den Rectseiten "vor"
	// dem Beobachtungspunkt
	
	// Frustumseiten, zeigend in Blickrichtung
	line frustum_left(frustum.pos(),frustum.left_dir());
	line frustum_right(frustum.pos(),frustum.right_dir());

	// Eckpunkte des Rects
	math::vector3 lt(rect.left,rect.top,0),rt(rect.right,rect.top,0),lb(rect.left,rect.bottom,0),rb(rect.right,rect.bottom,0);

	// Geraden des Rects (Richtung ist hier ja egal)
	line rect_top(lt,rt - lt),rect_bottom(lb,rb-lb),rect_left(lb,lb-lt),rect_right(rb,rb-rt);

	// Koeffizienten
	space_unit frustum_mult,rect_mult;

	if (line_intersection_2d(frustum_right,rect_top,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;
	if (line_intersection_2d(frustum_right,rect_bottom,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;
	if (line_intersection_2d(frustum_right,rect_left,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;
	if (line_intersection_2d(frustum_right,rect_right,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;
	if (line_intersection_2d(frustum_left,rect_top,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;
	if (line_intersection_2d(frustum_left,rect_bottom,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;
	if (line_intersection_2d(frustum_left,rect_left,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;
	if (line_intersection_2d(frustum_left,rect_right,frustum_mult,rect_mult))
		if (frustum_mult > 0 && rect_mult <= 1 && rect_mult >= 0)
			return true;

	return false;
}
