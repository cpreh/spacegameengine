/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CG_PROGRAM_FROM_FILE_PARAMETERS_HPP_INCLUDED
#define SGE_CG_PROGRAM_FROM_FILE_PARAMETERS_HPP_INCLUDED

#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/from_file_parameters_fwd.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/source_type.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace program
{

class from_file_parameters
{
	FCPPT_NONASSIGNABLE(
		from_file_parameters
	);
public:
	SGE_CG_DETAIL_SYMBOL
	from_file_parameters(
		sge::cg::context::object const &,
		sge::cg::program::source_type,
		sge::cg::profile::object const &,
		boost::filesystem::path const &,
		sge::cg::program::main_function const &,
		sge::cg::program::compile_options const &
	);

	sge::cg::context::object const &
	context() const;

	sge::cg::program::source_type
	source_type() const;

	sge::cg::profile::object const &
	profile() const;

	boost::filesystem::path const &
	path() const;

	sge::cg::program::main_function const
	main_function() const;

	sge::cg::program::compile_options const
	compile_options() const;
private:
	sge::cg::context::object const &context_;

	sge::cg::program::source_type const source_type_;

	sge::cg::profile::object const &profile_;

	boost::filesystem::path const path_;

	sge::cg::program::main_function const main_function_;

	sge::cg::program::compile_options const compile_options_;
};

}
}
}

#endif
