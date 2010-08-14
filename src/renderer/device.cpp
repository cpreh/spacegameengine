/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/copy.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/image/view/format.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/optional_impl.hpp>
#include <sstream>

sge::renderer::device::device()
{}

sge::renderer::glsl::program_ptr const
sge::renderer::device::create_glsl_program(
	glsl::optional_string const &vertex_shader_source_,
	glsl::optional_string const &pixel_shader_source_
)
{
	glsl::program_ptr const ret(
		create_glsl_program()
	);

	if(
		vertex_shader_source_
	)
		ret->vertex_shader(
			create_glsl_vertex_shader(
				*vertex_shader_source_	
			)
		);
	
	if(
		pixel_shader_source_
	)
		ret->pixel_shader(
			create_glsl_pixel_shader(
				*pixel_shader_source_
			)
		);

	ret->link();

	return ret;
}

sge::renderer::glsl::program_ptr const
sge::renderer::device::create_glsl_program(
	glsl::optional_istream const &vertex_shader_source_,
	glsl::optional_istream const &pixel_shader_source_
)
{
	typedef std::basic_ostringstream<
		renderer::glsl::char_type
	> osstream;

	osstream
		vs_stream,
		ps_stream;

	if(
		vertex_shader_source_
	)
		vs_stream << vertex_shader_source_->get().rdbuf();

	if(
		pixel_shader_source_
	)
		ps_stream << pixel_shader_source_->get().rdbuf();

	return
		create_glsl_program(
			vertex_shader_source_
			?
				vs_stream.str()
			:
				renderer::glsl::optional_string(),
			pixel_shader_source_
			?
				ps_stream.str()
			:
				renderer::glsl::optional_string()
		);
}

sge::renderer::texture_ptr const
sge::renderer::device::create_texture(
	image::view::const_object const &v,
	filter::texture const &filter,
	resource_flags_field const &flags
)
{
	texture_ptr const tex(
		create_texture(
			image::view::dim(v),
			image::view::format(v),
			filter,
			flags
		)
	);

	scoped_texture_lock const lock(
		tex,
		lock_mode::writeonly
	);

	image::algorithm::copy_and_convert(
		v,
		lock.value()
	);

	return tex;
}

/*
sge::renderer::volume_texture_ptr const
sge::renderer::device::create_volume_texture(
	image::view::const_object3 const &,
	filter::texture const &filter,
	resource_flags_field const & const flags
)
{
	volume_texture_ptr const tex(
		create_volume_texture(
			image::view::dim(v),
			image::view::format::(v),
			filter,
			flags
		)
	);

	scopde_volume_texture_lock const lock(
		tex,
		lock_mode::writeonly
	);

	image::algorithm::copy_and_convert(
		v,
		lock.value()
	);

	return tex;
}
*/


sge::renderer::vertex_buffer_ptr const
sge::renderer::device::create_vertex_buffer(
	vf::dynamic::const_view const &view,
	resource_flags_field const &flags
)
{
	vertex_buffer_ptr const vb(
		create_vertex_buffer(
			view.format(),
			view.size(),
			flags
		)
	);

	scoped_vertex_lock const lock(
		vb,
		lock_mode::writeonly
	);

	fcppt::algorithm::copy_n(
		view.data(),
		view.format().stride() * view.size(),
		lock.value().data()
	);

	return vb;
}

sge::renderer::index_buffer_ptr const
sge::renderer::device::create_index_buffer(
	index::dynamic::const_view const &view,
	resource_flags_field const &flags
)
{
	index_buffer_ptr const ib(
		create_index_buffer(
			view.format(),
			view.size(),
			flags
		)
	);

	scoped_index_lock const lock(
		ib,
		lock_mode::writeonly
	);

	index::dynamic::copy(
		view,
		lock.value()
	);

	return ib;
}

sge::renderer::device::~device()
{}
