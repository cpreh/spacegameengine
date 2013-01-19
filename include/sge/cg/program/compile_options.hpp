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


#ifndef SGE_CG_PROGRAM_COMPILE_OPTIONS_HPP_INCLUDED
#define SGE_CG_PROGRAM_COMPILE_OPTIONS_HPP_INCLUDED

#include <sge/cg/char_type.hpp>
#include <sge/cg/string.hpp>
#include <sge/cg/symbol.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace program
{

class compile_options
{
public:
	typedef
	std::vector<sge::cg::string>
	string_sequence;

	typedef
	fcppt::container::raw_vector<sge::cg::char_type const *>
	pointer_sequence;

	SGE_CG_SYMBOL
	compile_options();

	SGE_CG_SYMBOL
	explicit
	compile_options(
		sge::cg::char_type const **);

	SGE_CG_SYMBOL
	explicit
	compile_options(
		string_sequence const &);

	SGE_CG_SYMBOL
	compile_options(
		string_sequence const &,
		string_sequence const &);

	SGE_CG_SYMBOL
	pointer_sequence
	pointers() const;

	SGE_CG_SYMBOL
	string_sequence const &
	value() const;
private:
	mutable string_sequence value_;
};

}
}
}

#endif
