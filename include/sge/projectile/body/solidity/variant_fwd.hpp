/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PROJECTILE_BODY_SOLIDITY_VARIANT_FWD_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SOLIDITY_VARIANT_FWD_HPP_INCLUDED

#include <sge/projectile/body/solidity/nonsolid_fwd.hpp>
#include <sge/projectile/body/solidity/solid_fwd.hpp>
#include <sge/projectile/body/solidity/static_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
namespace body
{
namespace solidity
{

typedef
fcppt::variant::object
<
	boost::mpl::vector3
	<
		sge::projectile::body::solidity::static_,
		sge::projectile::body::solidity::solid,
		sge::projectile::body::solidity::nonsolid
	>
>
variant;

}
}
}
}

#endif
