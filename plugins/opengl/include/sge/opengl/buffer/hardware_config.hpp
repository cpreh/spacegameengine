//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_HARDWARE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_HARDWARE_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/fun_ref_value_type.hpp>
#include <sge/opengl/buffer/hardware_config_fwd.hpp>
#include <sge/opengl/buffer/is_native.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class hardware_config
{
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
		sge::opengl::fun_ref_value_type<
			gl_map_buffer_range
		>
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
	sge::opengl::buffer::is_native is_native_;

	gl_gen_buffers gen_buffers_;

	gl_delete_buffers delete_buffers_;

	gl_bind_buffer bind_buffer_;

	gl_map_buffer map_buffer_;

	gl_unmap_buffer unmap_buffer_;

	gl_buffer_data buffer_data_;

	gl_buffer_sub_data buffer_sub_data_;

	optional_gl_map_buffer_range map_buffer_range_;
};

}
}
}

#endif
