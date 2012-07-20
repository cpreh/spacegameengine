#ifndef SGE_SHADER_CONTEXT_HPP_INCLUDED
#define SGE_SHADER_CONTEXT_HPP_INCLUDED

#include <sge/cg/context/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/shader/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace shader
{
class context
{
FCPPT_NONCOPYABLE(
	context);
public:
	SGE_SHADER_SYMBOL
	explicit
	context(
		sge::renderer::device &);

	SGE_SHADER_SYMBOL
	sge::renderer::device &
	renderer() const;

	SGE_SHADER_SYMBOL
	sge::cg::context::object &
	cg_context();

	SGE_SHADER_SYMBOL
	sge::cg::context::object const &
	cg_context() const;

	SGE_SHADER_SYMBOL
	sge::cg::profile::object const &
	vertex_profile() const;

	SGE_SHADER_SYMBOL
	sge::cg::profile::object const &
	pixel_profile() const;

	SGE_SHADER_SYMBOL
	sge::cg::program::compile_options const
	vertex_compile_options() const;

	SGE_SHADER_SYMBOL
	sge::cg::program::compile_options const
	pixel_compile_options() const;

	SGE_SHADER_SYMBOL
	~context();
private:
	sge::renderer::device &renderer_;
	sge::cg::context::object cg_context_;
	sge::cg::profile::object const vertex_profile_;
	sge::cg::profile::object const pixel_profile_;
};
}
}

#endif
