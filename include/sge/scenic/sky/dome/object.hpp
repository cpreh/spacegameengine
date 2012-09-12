/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SCENIC_SKY_DOME_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SKY_DOME_OBJECT_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/index_buffer_scoped_ptr.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/scenic/texture_manager_fwd.hpp>
#include <sge/scenic/sky/dome/latitude.hpp>
#include <sge/scenic/sky/dome/longitude.hpp>
#include <sge/scenic/sky/dome/texture_path.hpp>
#include <sge/scenic/sky/dome/y_translation.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace sky
{
namespace dome
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	object(
		sge::renderer::device &,
		sge::shader::context &,
		sge::scenic::texture_manager &,
		sge::scenic::sky::dome::texture_path const &,
		sge::camera::base &,
		sge::scenic::sky::dome::longitude const &,
		sge::scenic::sky::dome::latitude const &,
		sge::scenic::sky::dome::y_translation const &);

	void
	render(
		sge::renderer::context::object &);

	~object();
private:
	sge::scenic::sky::dome::y_translation const y_translation_;
	sge::scenic::texture_manager &texture_manager_;
	sge::scenic::sky::dome::texture_path const texture_path_;
	sge::renderer::device &renderer_;
	sge::camera::base &camera_;
	sge::renderer::vertex_declaration_scoped_ptr vertex_declaration_;
	sge::renderer::vertex_buffer_scoped_ptr vertex_buffer_;
	sge::renderer::index_buffer_scoped_ptr index_buffer_;
	sge::shader::pair shader_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> mvp_parameter_;
	sge::shader::parameter::planar_texture texture_parameter_;
};
}
}
}
}

#endif
