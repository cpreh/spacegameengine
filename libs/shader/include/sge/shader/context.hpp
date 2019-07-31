//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_CONTEXT_HPP_INCLUDED
#define SGE_SHADER_CONTEXT_HPP_INCLUDED

#include <sge/cg/context/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/shader/detail/symbol.hpp>
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
	SGE_SHADER_DETAIL_SYMBOL
	explicit
	context(
		sge::renderer::device::core &);

	SGE_SHADER_DETAIL_SYMBOL
	sge::renderer::device::core &
	renderer() const;

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::context::object &
	cg_context();

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::context::object const &
	cg_context() const;

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::profile::object const &
	vertex_profile() const;

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::profile::object const &
	pixel_profile() const;

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::program::compile_options
	vertex_compile_options() const;

	SGE_SHADER_DETAIL_SYMBOL
	sge::cg::program::compile_options
	pixel_compile_options() const;

	SGE_SHADER_DETAIL_SYMBOL
	~context();
private:
	sge::renderer::device::core &renderer_;
	sge::cg::context::object cg_context_;
	sge::cg::profile::object const vertex_profile_;
	sge::cg::profile::object const pixel_profile_;
};
}
}

#endif
