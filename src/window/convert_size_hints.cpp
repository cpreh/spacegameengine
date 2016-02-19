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


#include <sge/window/convert_size_hints.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/optional_dim.hpp>
#include <sge/window/size_hints.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>


awl::window::parameters
sge::window::convert_size_hints(
	awl::window::parameters const &_parameters,
	sge::window::optional_dim const &_opt_dim,
	sge::window::size_hints const &_size_hints
)
{
	auto const convert_dim(
		[](
			sge::window::dim const _sge_dim
		)
		-> awl::window::dim
		{
			return
				fcppt::math::dim::structure_cast<
					awl::window::dim,
					fcppt::cast::size_fun
				>(
					_sge_dim
				);
		}
	);

	awl::window::parameters ret{
		_parameters
	};

	fcppt::optional::maybe_void(
		_opt_dim,
		[
			&ret,
			convert_dim
		](
			sge::window::dim const _dim
		)
		{
			ret.size(
				convert_dim(
					_dim
				)
			);
		}
	);

	fcppt::optional::maybe_void(
		_size_hints.exact_size_hint(),
		[
			&ret,
			convert_dim
		](
			sge::window::dim const _dim
		)
		{
			ret.exact_size_hint(
				convert_dim(
					_dim
				)
			);
		}
	);

	fcppt::optional::maybe_void(
		_size_hints.minimum_size_hint(),
		[
			&ret,
			convert_dim
		](
			sge::window::dim const _dim
		)
		{
			ret.minimum_size_hint(
				convert_dim(
					_dim
				)
			);
		}
	);

	fcppt::optional::maybe_void(
		_size_hints.maximum_size_hint(),
		[
			&ret,
			convert_dim
		](
			sge::window::dim const _dim
		)
		{
			ret.maximum_size_hint(
				convert_dim(
					_dim
				)
			);
		}
	);

	return
		ret;
}
