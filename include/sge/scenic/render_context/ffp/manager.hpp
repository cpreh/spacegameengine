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


#ifndef SGE_SCENIC_RENDER_CONTEXT_FFP_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FFP_MANAGER_HPP_INCLUDED

#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/manager_base.hpp>
#include <sge/scenic/render_context/ffp/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace ffp
{
class manager
:
	public sge::scenic::render_context::manager_base
{
FCPPT_NONCOPYABLE(
	manager);
public:
	SGE_SCENIC_SYMBOL
	manager(
		sge::renderer::device::ffp &,
		sge::renderer::vertex::declaration &);

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::base_unique_ptr
	create_context(
		sge::renderer::context::core &);

	SGE_SCENIC_SYMBOL
	~manager();
private:
	friend class sge::scenic::render_context::ffp::object;

	sge::renderer::device::ffp &renderer_;
	sge::renderer::vertex::declaration &vertex_declaration_;
};
}
}
}
}

#endif
