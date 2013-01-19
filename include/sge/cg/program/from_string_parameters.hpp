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


#ifndef SGE_CG_PROGRAM_FROM_STRING_PARAMETERS_HPP_INCLUDED
#define SGE_CG_PROGRAM_FROM_STRING_PARAMETERS_HPP_INCLUDED

#include <sge/cg/symbol.hpp>
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/from_string_parameters_fwd.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/program/source_type.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace cg
{
namespace program
{

class from_string_parameters
{
	FCPPT_NONASSIGNABLE(
		from_string_parameters
	);
public:
	SGE_CG_SYMBOL
	from_string_parameters(
		sge::cg::context::object const &,
		sge::cg::program::source_type,
		sge::cg::profile::object const &,
		sge::cg::program::source const &,
		sge::cg::program::main_function const &,
		sge::cg::program::compile_options const &
	);

	sge::cg::context::object const &
	context() const;

	sge::cg::program::source_type
	source_type() const;

	sge::cg::profile::object const &
	profile() const;

	sge::cg::program::source const &
	source() const;

	sge::cg::program::main_function const
	main_function() const;

	sge::cg::program::compile_options const
	compile_options() const;
private:
	sge::cg::context::object const &context_;

	sge::cg::program::source_type const source_type_;

	sge::cg::profile::object const &profile_;

	sge::cg::program::source const source_;

	sge::cg::program::main_function const main_function_;

	sge::cg::program::compile_options const compile_options_;
};

}
}
}

#endif
