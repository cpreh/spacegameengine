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


#ifndef SGE_CG_PARAMETER_NAMED_HPP_INCLUDED
#define SGE_CG_PARAMETER_NAMED_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/named_fwd.hpp>
#include <sge/cg/parameter/object.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{

class named
{
	FCPPT_NONASSIGNABLE(
		named
	);
public:
	explicit
	named(
		sge::cg::parameter::object const &
	);

	SGE_CG_DETAIL_SYMBOL
	named(
		named const &
	);

	SGE_CG_DETAIL_SYMBOL
	~named();

	SGE_CG_DETAIL_SYMBOL
	sge::cg::parameter::object const &
	object() const;
private:
	sge::cg::parameter::object const impl_;
};

}
}
}

#endif
