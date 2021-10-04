//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PARAMETER_PLANAR_TEXTURE_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_PLANAR_TEXTURE_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/shader/pair_ref.hpp>
#include <sge/shader/detail/symbol.hpp>
#include <sge/shader/parameter/name.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge::shader::parameter
{

class planar_texture
{
	FCPPT_NONMOVABLE(
		planar_texture
	);
public:
	using
	optional_value
	=
	fcppt::optional::reference<
		sge::renderer::texture::planar
	>;

	using
	optional_loaded_texture
	=
	fcppt::optional::reference<
		sge::renderer::cg::loaded_texture
	>;

	SGE_SHADER_DETAIL_SYMBOL
	planar_texture(
		sge::cg::program::object_ref,
		sge::shader::parameter::name const &,
		sge::shader::pair_ref,
		sge::renderer::device::core_ref,
		optional_value const &
	);

	SGE_SHADER_DETAIL_SYMBOL
	void
	set(
		optional_value const &
	);

	SGE_SHADER_DETAIL_SYMBOL
	void
	activate(
		sge::renderer::context::core_ref
	);

	SGE_SHADER_DETAIL_SYMBOL
	void
	deactivate();

	[[nodiscard]]
	SGE_SHADER_DETAIL_SYMBOL
	optional_loaded_texture
	loaded_texture();

	[[nodiscard]]
	SGE_SHADER_DETAIL_SYMBOL
	sge::renderer::texture::stage
	stage() const;

	SGE_SHADER_DETAIL_SYMBOL
	~planar_texture();
private:
	using
	optional_render_context
	=
	fcppt::optional::reference<
		sge::renderer::context::core
	>;

	sge::shader::pair_ref const parent_;

	sge::renderer::device::core_ref const renderer_;

	sge::cg::parameter::named const parameter_;

	using
	optional_loaded_texture_ptr
	=
	fcppt::optional::object<
		sge::renderer::cg::loaded_texture_unique_ptr
	>;

	optional_loaded_texture_ptr loaded_texture_;

	using
	scoped_texture_unique_ptr
	=
	fcppt::unique_ptr<
		sge::renderer::cg::scoped_texture
	>;

	using
	optional_scoped_texture_ptr
	=
	fcppt::optional::object<
		scoped_texture_unique_ptr
	>;

	optional_scoped_texture_ptr scoped_texture_;

	optional_render_context optional_render_context_;

	optional_value value_;
};

}

#endif
