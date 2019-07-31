//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PARAMETER_PLANAR_TEXTURE_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_PLANAR_TEXTURE_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/shader/pair_fwd.hpp>
#include <sge/shader/detail/symbol.hpp>
#include <sge/shader/parameter/name.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace shader
{
namespace parameter
{

class planar_texture
{
FCPPT_NONCOPYABLE(
	planar_texture);
public:
	typedef
	fcppt::optional::reference<
		sge::renderer::texture::planar
	>
	optional_value;

	typedef
	fcppt::optional::reference<
		sge::renderer::cg::loaded_texture
	>
	optional_loaded_texture;

	SGE_SHADER_DETAIL_SYMBOL
	planar_texture(
		sge::cg::program::object &,
		sge::shader::parameter::name const &,
		sge::shader::pair &,
		sge::renderer::device::core &,
		optional_value const &);

	SGE_SHADER_DETAIL_SYMBOL
	void
	set(
		optional_value const &);

	SGE_SHADER_DETAIL_SYMBOL
	void
	activate(
		sge::renderer::context::core &);

	SGE_SHADER_DETAIL_SYMBOL
	void
	deactivate();

	SGE_SHADER_DETAIL_SYMBOL
	optional_loaded_texture
	loaded_texture();

	SGE_SHADER_DETAIL_SYMBOL
	sge::renderer::texture::stage
	stage() const;

	SGE_SHADER_DETAIL_SYMBOL
	~planar_texture();
private:
	typedef
	fcppt::optional::reference<
		sge::renderer::context::core
	>
	optional_render_context;

	sge::shader::pair &parent_;

	sge::renderer::device::core &renderer_;

	sge::cg::parameter::named const parameter_;

	typedef
	fcppt::optional::object<
		sge::renderer::cg::loaded_texture_unique_ptr
	>
	optional_loaded_texture_ptr;

	optional_loaded_texture_ptr loaded_texture_;

	typedef
	fcppt::unique_ptr<
		sge::renderer::cg::scoped_texture
	>
	scoped_texture_unique_ptr;

	typedef
	fcppt::optional::object<
		scoped_texture_unique_ptr
	>
	optional_scoped_texture_ptr;

	optional_scoped_texture_ptr scoped_texture_;

	optional_render_context optional_render_context_;

	optional_value value_;
};

}
}
}

#endif
