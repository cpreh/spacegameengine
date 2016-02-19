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


#ifndef SGE_SCENIC_RENDER_CONTEXT_MANAGER_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_MANAGER_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
class SGE_CORE_DETAIL_CLASS_SYMBOL manager_base
{
FCPPT_NONCOPYABLE(
	manager_base);
public:
	virtual sge::scenic::render_context::base_unique_ptr
	create_context(
		sge::renderer::context::core &) = 0;

	virtual
	~manager_base() = 0;
protected:
	manager_base();
};
}
}
}

#endif
