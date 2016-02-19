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


#ifndef SGE_OPENGL_BUFFER_HARDWARE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_HARDWARE_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/buffer/hardware_config_fwd.hpp>
#include <sge/opengl/buffer/is_native.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class hardware_config
{
	FCPPT_NONASSIGNABLE(
		hardware_config
	);
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLGENBUFFERSPROC
	>
	gl_gen_buffers;

	typedef
	sge::opengl::fun_ref<
		PFNGLDELETEBUFFERSPROC
	>
	gl_delete_buffers;

	typedef
	sge::opengl::fun_ref<
		PFNGLBINDBUFFERPROC
	>
	gl_bind_buffer;

	typedef
	sge::opengl::fun_ref<
		PFNGLMAPBUFFERPROC
	>
	gl_map_buffer;

	typedef
	sge::opengl::fun_ref<
		PFNGLUNMAPBUFFERPROC
	>
	gl_unmap_buffer;

	typedef
	sge::opengl::fun_ref<
		PFNGLBUFFERDATAPROC
	>
	gl_buffer_data;

	typedef
	sge::opengl::fun_ref<
		PFNGLBUFFERSUBDATAPROC
	>
	gl_buffer_sub_data;

	typedef
	sge::opengl::fun_ref<
		PFNGLMAPBUFFERRANGEPROC
	>
	gl_map_buffer_range;

	typedef
	fcppt::optional::reference<
		typename
		std::remove_reference<
			gl_map_buffer_range
		>::type
	>
	optional_gl_map_buffer_range;

	hardware_config(
		sge::opengl::buffer::is_native,
		gl_gen_buffers,
		gl_delete_buffers,
		gl_bind_buffer,
		gl_map_buffer,
		gl_unmap_buffer,
		gl_buffer_data,
		gl_buffer_sub_data,
		optional_gl_map_buffer_range
	);

	sge::opengl::buffer::is_native
	is_native() const;

	gl_gen_buffers
	gen_buffers() const;

	gl_delete_buffers
	delete_buffers() const;

	gl_bind_buffer
	bind_buffer() const;

	gl_map_buffer
	map_buffer() const;

	gl_unmap_buffer
	unmap_buffer() const;

	gl_buffer_data
	buffer_data() const;

	gl_buffer_sub_data
	buffer_sub_data() const;

	optional_gl_map_buffer_range
	map_buffer_range() const;
private:
	sge::opengl::buffer::is_native const is_native_;

	gl_gen_buffers gen_buffers_;

	gl_delete_buffers delete_buffers_;

	gl_bind_buffer bind_buffer_;

	gl_map_buffer map_buffer_;

	gl_unmap_buffer unmap_buffer_;

	gl_buffer_data buffer_data_;

	gl_buffer_sub_data buffer_sub_data_;

	optional_gl_map_buffer_range const map_buffer_range_;
};

}
}
}

#endif
