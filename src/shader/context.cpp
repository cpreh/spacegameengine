#include <sge/shader/context.hpp>
#include <sge/renderer/device.hpp>

sge::shader::context::context(
	sge::renderer::device &_renderer)
:
	renderer_(
		_renderer),
	cg_context_(),
	vertex_profile_(
		_renderer.create_cg_profile(
			sge::cg::profile::shader_type::vertex)),
	pixel_profile_(
		_renderer.create_cg_profile(
			sge::cg::profile::shader_type::pixel))
{
}

sge::renderer::device &
sge::shader::context::renderer() const
{
	return
		renderer_;
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

sge::cg::program::compile_options const
sge::shader::context::vertex_compile_options() const
{
	return
		renderer_.cg_compile_options(
			cg_context_,
			vertex_profile_);
}

sge::cg::program::compile_options const
sge::shader::context::pixel_compile_options() const
{
	return
		renderer_.cg_compile_options(
			cg_context_,
			pixel_profile_);
}

sge::shader::context::~context()
{
}
