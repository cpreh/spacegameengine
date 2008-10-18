/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/helper.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/circle_impl.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/texture/part.hpp>
#include <cmath>
#include <limits>

sge::sprite::dim const sge::sprite::texture_dim(
	std::numeric_limits<unit>::max(),
	std::numeric_limits<unit>::max());

sge::texture::part_ptr const sge::sprite::no_texture;

sge::sprite::point const sge::sprite::defaults::pos_(0,0);
sge::texture::part_ptr const sge::sprite::defaults::texture_(no_texture);
sge::sprite::dim const sge::sprite::defaults::dim_(0,0);
sge::sprite::color const sge::sprite::defaults::color_(sge::renderer::colors::white());
sge::sprite::depth_type const sge::sprite::defaults::depth_(0);
sge::sprite::rotation_type const sge::sprite::defaults::rotation_(0);
bool const sge::sprite::defaults::visible_(true);

sge::sprite::object::object(
	const boost::optional<point> pos_,
	const boost::optional<texture::part_ptr> vtex,
	const boost::optional<dim> size_,
	const boost::optional<color> color_,
	const boost::optional<depth_type> z_,
	const boost::optional<rotation_type> rotation_,
	const boost::optional<bool> visible_)
 :
	pos_(pos_ ? *pos_ : defaults::pos_),
	size_(
		size_
		? *size_ == texture_dim
			? dim(
				math::structure_cast<unit>(
					(*vtex)->area().dim()))
			: *size_
		: defaults::dim_),
	z_(z_ ? *z_ : defaults::depth_),
	rotation_(rotation_ ? *rotation_ : defaults::rotation_),
	tex(vtex ? *vtex : defaults::texture_),
	rot_around_(no_initialization_tag()),
	repeat_(1),
	color_(color_ ? *color_ : defaults::color_),
	visible_(visible_ ? *visible_ : defaults::visible_),
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

void sge::sprite::object::set_texture(const texture::part_ptr vtex)
{
	tex = vtex;
}

void sge::sprite::object::rotation(const rotation_type rot)
{
	rotation_ = rot;
}

void sge::sprite::object::rotate_around(const point p)
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

void sge::sprite::object::set_color(const color c)
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

void sge::sprite::object::set_center(const sge::sprite::point &p)
{
	pos() = p-sge::sprite::point(w()/2,h()/2);
}

sge::sprite::point sge::sprite::object::center() const
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

sge::sprite::color sge::sprite::object::get_color() const
{
	return color_;
}

const sge::texture::part_ptr sge::sprite::object::get_texture() const
{
	return tex;
}

sge::space_unit sge::sprite::object::radius() const
{
	return std::max(std::sqrt(static_cast<space_unit>(center().x() * center().x() + x() * x())),
	                std::sqrt(static_cast<space_unit>(center().y() * center().y() + y() * y()))
	               );
}

sge::sprite::rect sge::sprite::object::get_rect() const
{
	return rect(pos(),size());
}

sge::sprite::rect sge::sprite::object::bounding_quad() const
{
	if(math::almost_zero(rotation()))
		return get_rect();
	const space_unit rad = radius();
	return rect(static_cast<sprite::unit>(static_cast<space_unit>(center().x()) - rad),
	            static_cast<sprite::unit>(static_cast<space_unit>(center().y()) - rad),
	            static_cast<sprite::unit>(static_cast<space_unit>(center().x()) + rad),
	            static_cast<sprite::unit>(static_cast<space_unit>(center().y()) + rad));
}

sge::math::circle sge::sprite::object::bounding_circle() const
{
	return math::circle(
		static_cast<math::circle::value_type>(x()),
		static_cast<math::circle::value_type>(y()),
		radius());
}

const sge::sprite::point sge::sprite::object::rotation_center() const
{
	if(!use_rot_around)
		return center();
	return pos() + rot_around_;
}
