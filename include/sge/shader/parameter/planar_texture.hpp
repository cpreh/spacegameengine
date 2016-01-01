/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>


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
	fcppt::optional::object<sge::renderer::texture::planar &>
	optional_value;

	typedef
	fcppt::optional::object<sge::renderer::cg::loaded_texture &>
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
	fcppt::optional::object<
		sge::renderer::context::core &
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
