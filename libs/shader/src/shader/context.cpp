//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/shader/context.hpp>


sge::shader::context::context(
	sge::renderer::device::core_ref const _renderer
)
:
	renderer_(
		_renderer
	),
	cg_context_(),
	vertex_profile_(
		_renderer.get().create_cg_profile(
			sge::cg::profile::shader_type::vertex
		)
	),
	pixel_profile_(
		_renderer.get().create_cg_profile(
			sge::cg::profile::shader_type::pixel
		)
	)
{
}

sge::renderer::device::core &
sge::shader::context::renderer() const
{
	return
		renderer_.get();
}

sge::cg::context::object &
sge::shader::context::cg_context()
{
	return
		cg_context_;
}

sge::cg::context::object const &
sge::shader::context::cg_context() const
{
	return
		cg_context_;
}

sge::cg::profile::object const &
sge::shader::context::vertex_profile() const
{
	return
		vertex_profile_;
}

sge::cg::profile::object const &
sge::shader::context::pixel_profile() const
{
	return
		pixel_profile_;
}

sge::cg::program::compile_options
sge::shader::context::vertex_compile_options() const
{
	return
		renderer_.get().cg_compile_options(
			cg_context_,
			vertex_profile_
		);
}

sge::cg::program::compile_options
sge::shader::context::pixel_compile_options() const
{
	return
		renderer_.get().cg_compile_options(
			cg_context_,
			pixel_profile_
		);
}

sge::shader::context::~context()
= default;
