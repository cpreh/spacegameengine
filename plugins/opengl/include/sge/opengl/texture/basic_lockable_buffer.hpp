//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_HPP_INCLUDED

#include <sge/image/pitch_fwd.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_buffer_parameters_fwd.hpp>
#include <sge/opengl/texture/basic_fwd.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/box/object_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic_lockable_buffer
:
	public
		sge::opengl::texture::basic_buffer<
			Types
		>
{
	FCPPT_NONCOPYABLE(
		basic_lockable_buffer
	);
public:
	typedef
	sge::opengl::texture::basic_buffer<
		Types
	>
	gl_base;

	typedef
	typename
	gl_base::image_tag
	image_tag;

	typedef
	typename
	gl_base::color_tag
	color_tag;

	typedef
	typename
	gl_base::format_type
	format_type;

	typedef
	typename
	gl_base::dim
	dim;

	typedef
	sge::opengl::texture::config<
		dim::static_size::value
	>
	config_type;

	basic_lockable_buffer(
		format_type,
		config_type const &,
		sge::opengl::texture::basic_buffer_parameters const &
	);

	~basic_lockable_buffer()
	override;

	typedef
	sge::opengl::texture::lock_base::pointer
	pointer;

	typedef
	sge::opengl::texture::lock_base::const_pointer
	const_pointer;

	typedef
	typename
	gl_base::base_type
	base_type;

	typedef
	typename
	base_type::lock_area
	lock_area;

	typedef
	typename
	base_type::view
	view;

	typedef
	typename
	base_type::const_view
	const_view;
private:
	view
	lock(
		lock_area const &,
		sge::renderer::lock_mode
	)
	override;

	const_view
	lock_c(
		lock_area const &
	) const
	override;

	void
	unlock() const
	override;

	void
	lock_me(
		lock_area const &,
		sge::renderer::lock_flags::method
	) const;

	view
	lock_view();

	const_view
	lock_view() const;

	dim
	lock_dim() const;

	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	config_type const &config_;

	sge::opengl::texture::type const type_;

	sge::renderer::resource_flags_field const resource_flags_;

	sge::opengl::color_order const color_order_;

	sge::opengl::color_base_type const color_base_type_;

	sge::opengl::internal_color_format const internal_color_format_;

	sge::renderer::size_type const stride_;

	typedef
	fcppt::unique_ptr<
		sge::opengl::texture::lock_base
	>
	lock_unique_ptr;

	typedef
	fcppt::optional::object<
		lock_unique_ptr
	>
	optional_lock_unique_ptr;

	mutable optional_lock_unique_ptr lock_;

	typedef
	fcppt::optional::object<
		lock_area
	>
	optional_lock_area;

	mutable optional_lock_area lock_area_;

	typedef
	sge::image::pitch<
		image_tag
	>
	pitch;
};

}
}
}

#endif
