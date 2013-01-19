/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/program/source_type.hpp>


sge::cg::program::from_string_parameters::from_string_parameters(
	sge::cg::context::object const &_context,
	sge::cg::program::source_type const _source_type,
	sge::cg::profile::object const &_profile,
	sge::cg::program::source const &_source,
	sge::cg::program::main_function const &_main_function,
	sge::cg::program::compile_options const &_compile_options
)
:
	context_(
		_context
	),
	source_type_(
		_source_type
	),
	profile_(
		_profile
	),
	source_(
		_source
	),
	main_function_(
		_main_function
	),
	compile_options_(
		_compile_options
	)
{
}

sge::cg::context::object const &
sge::cg::program::from_string_parameters::context() const
{
	return
		context_;
}

sge::cg::program::source_type
sge::cg::program::from_string_parameters::source_type() const
{
	return
		source_type_;
}

sge::cg::profile::object const &
sge::cg::program::from_string_parameters::profile() const
{
	return
		profile_;
}

sge::cg::program::source const &
sge::cg::program::from_string_parameters::source() const
{
	return
		source_;
}

sge::cg::program::main_function const
sge::cg::program::from_string_parameters::main_function() const
{
	return
		main_function_;
}

sge::cg::program::compile_options const
sge::cg::program::from_string_parameters::compile_options() const
{
	return
		compile_options_;
}
