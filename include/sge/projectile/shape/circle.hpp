/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/shape/base.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


class btCollisionShape;

namespace sge
{
namespace projectile
{
namespace shape
{
class SGE_CORE_DETAIL_CLASS_SYMBOL circle
:
	public sge::projectile::shape::base
{
FCPPT_NONCOPYABLE(
	circle);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	explicit
	circle(
		sge::projectile::scalar const radius);

	// No symbol needed here
	btCollisionShape &
	bullet_shape()
	override;

	btCollisionShape const &
	bullet_shape() const
	override;

	SGE_PROJECTILE_DETAIL_SYMBOL
	~circle()
	override;
private:
	fcppt::unique_ptr<btCollisionShape> const bullet_shape_;
};
}
}
}

#endif
