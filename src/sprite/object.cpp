/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/



#include <sge/sprite/object.hpp>
#include <sge/sprite/texture_dim.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/circle/basic_impl.hpp>
#include <sge/math/almost_zero.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/texture/part.hpp>
#include <cmath>

sge::sprite::object::object(
	point const &pos_,
	texture::const_part_ptr const vtex,
	dim const &size_,
	sprite::color const &color_,
	depth_type const z_,
	rotation_type const rotation_,
	bool const visible_)
 :
	pos_(pos_),
	size_(
		size_ == texture_dim()
			? dim(
				math::dim::structure_cast<dim>(
					vtex->area().dim()
				)
			)
			: size_),
	z_(z_),
	rotation_(rotation_),
	tex(vtex),
	repeat_(1),
	color_(color_),
	visible_(visible_),
	use_rot_around(false)
{}

sge::sprite::unit& sge::sprite::object::x()
{
	return pos().x();
}

sge::sprite::unit& sge::sprite::object::y()
{
	return pos().y();
}

sge::sprite::point& sge::sprite::object::pos()
{
	return pos_;
}

sge::sprite::unit& sge::sprite::object::w()
{
	return size().w();
}

sge::sprite::unit& sge::sprite::object::h()
{
	return size().h();
}

sge::sprite::dim& sge::sprite::object::size()
{
	return size_;
}

sge::sprite::depth_type& sge::sprite::object::z()
{
	return z_;
}

void sge::sprite::object::visible(const bool nvisible)
{
	visible_ = nvisible;
}

void sge::sprite::object::texture(
	::sge::texture::const_part_ptr const vtex)
{
	tex = vtex;
}

void sge::sprite::object::rotation(const rotation_type rot)
{
	rotation_ = rot;
}

void sge::sprite::object::rotate_around(
	point const & p)
{
	use_rot_around = true;
	rot_around_ = p;
}

void sge::sprite::object::rotate_around()
{
	use_rot_around = false;
}

void sge::sprite::object::repeat(const repetition_type r)
{
	repeat_ = r;
}

void sge::sprite::object::color(
	sprite::color const &c)
{
	color_ = c;
}

const sge::sprite::unit& sge::sprite::object::x() const
{
	return pos().x();
}

const sge::sprite::unit& sge::sprite::object::y() const
{
	return pos().y();
}

const sge::sprite::point& sge::sprite::object::pos() const
{
	return pos_;
}

const sge::sprite::unit& sge::sprite::object::w() const
{
	return size().w();
}

const sge::sprite::unit& sge::sprite::object::h() const
{
	return size().h();
}

const sge::sprite::dim& sge::sprite::object::size() const
{
	return size_;
}

const sge::sprite::depth_type& sge::sprite::object::z() const
{
	return z_;
}

bool sge::sprite::object::visible() const
{
	return visible_;
}

void sge::sprite::object::center(
	point const &p)
{
	pos() = p - sge::sprite::point(
		w() / 2,
		h() / 2);
}

sge::sprite::point const
sge::sprite::object::center() const
{
	return  point(x() + w() / 2, y() + h() / 2);
}

sge::sprite::rotation_type sge::sprite::object::rotation() const
{
	return rotation_;
}

sge::sprite::repetition_type sge::sprite::object::repeat() const
{
	return repeat_;
}

sge::sprite::color const
sge::sprite::object::color() const
{
	return color_;
}

sge::texture::const_part_ptr const
sge::sprite::object::texture() const
{
	return tex;
}

sge::sprite::funit
sge::sprite::object::radius() const
{
	return std::max(
		std::sqrt(
			static_cast<funit>(
				center().x() * center().x() + x() * x())),
		std::sqrt(
			static_cast<funit>(
				center().y() * center().y() + y() * y()))
		);
}

sge::sprite::rect const
sge::sprite::object::rect() const
{
	return sprite::rect(
		pos(),
		size());
}

sge::sprite::rect const
sge::sprite::object::bounding_quad() const
{
	if(math::almost_zero(rotation()))
		return rect();
	funit const rad = radius();
	return sprite::rect(
		static_cast<sprite::unit>(
			static_cast<funit>(
				center().x()) - rad),
		static_cast<unit>(
			static_cast<funit>(
				center().y()) - rad),
		static_cast<unit>(
			static_cast<funit>(
				center().x()) + rad),
		static_cast<unit>(
			static_cast<funit>(
				center().y()) + rad));
}

sge::sprite::circle const
sge::sprite::object::bounding_circle() const
{
	return circle(
		// TODO: structure_cast!
		circle::point_type(
			static_cast<circle::value_type>(x()),
			static_cast<circle::value_type>(y())
		),
		radius());
}

sge::sprite::point const
sge::sprite::object::rotation_center() const
{
	if(!use_rot_around)
		return center();
	return pos() + rot_around_;
}
