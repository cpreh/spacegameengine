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


#ifndef SGE_SHADER_LOAD_EDITED_STRING_HPP_INCLUDED
#define SGE_SHADER_LOAD_EDITED_STRING_HPP_INCLUDED

#include <sge/cg/program/source.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
SGE_SHADER_DETAIL_SYMBOL
sge::cg::program::source
load_edited_string(
	sge::renderer::device::core &,
	sge::renderer::vertex::declaration const &,
	std::istream &);
}
}

#endif

