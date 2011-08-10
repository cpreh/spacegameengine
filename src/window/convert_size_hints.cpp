/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/window/convert_size_hints.hpp>
#include <sge/window/size_hints.hpp>
#include <sge/window/optional_dim.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/optional_dim.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional_impl.hpp>

namespace
{

awl::window::dim const
convert_dim(
	sge::window::optional_dim const &_dim
)
{
	return
		fcppt::math::dim::structure_cast<
			awl::window::dim
		>(
			*_dim
		);
}

}

awl::window::parameters
sge::window::convert_size_hints(
	awl::window::parameters const &_parameters,
	sge::window::size_hints const &_size_hints
)
{
	awl::window::parameters ret(
		_parameters
	);

	if(
		_size_hints.exact_size_hint()
	)
		ret.exact_size_hint(
			convert_dim(
				_size_hints.exact_size_hint()
			)
		);

	if(
		_size_hints.minimum_size_hint()
	)
		ret.minimum_size_hint(
			convert_dim(
				_size_hints.minimum_size_hint()
			)
		);

	if(
		_size_hints.maximum_size_hint()
	)
		ret.maximum_size_hint(
			convert_dim(
				_size_hints.maximum_size_hint()
			)
		);

	return ret;
}
