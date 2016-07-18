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


#ifndef SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED

#include <sge/projectile/log_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/size.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace ghost
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	parameters(
		sge::projectile::log const &,
		sge::projectile::ghost::position const &,
		sge::projectile::ghost::size const &
	);

	fcppt::log::object &
	log() const;

	sge::projectile::ghost::position const &
	position() const;

	sge::projectile::ghost::size const &
	size() const;
private:
	fcppt::log::object &log_;

	sge::projectile::ghost::position position_;

	sge::projectile::ghost::size size_;
};

}
}
}

#endif
