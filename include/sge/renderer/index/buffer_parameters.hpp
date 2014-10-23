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


#ifndef SGE_RENDERER_INDEX_BUFFER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/dynamic/format.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

class buffer_parameters
{
public:
	/**
	\brief Parameters that describe an index buffer

	\param format The format of the indices
	\param count The number of indices the buffer will hold
	\param flags The capabilitiies of the buffer
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	buffer_parameters(
		sge::renderer::index::dynamic::format format,
		sge::renderer::index::count count,
		sge::renderer::resource_flags_field const &flags
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::index::dynamic::format
	format() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::index::count const
	count() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::resource_flags_field const &
	flags() const;
private:
	sge::renderer::index::dynamic::format format_;

	sge::renderer::index::count count_;

	sge::renderer::resource_flags_field flags_;
};

}
}
}

#endif
