/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SHADER_CONTEXT_HPP_INCLUDED
#define SGE_SHADER_CONTEXT_HPP_INCLUDED

#include <sge/cg/context/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/renderer/device/core_fwd.hpp>
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
		sge::renderer::device::core &);

	SGE_SHADER_SYMBOL
	sge::renderer::device::core &
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
	sge::renderer::device::core &renderer_;
	sge::cg::context::object cg_context_;
	sge::cg::profile::object const vertex_profile_;
	sge::cg::profile::object const pixel_profile_;
};
}
}

#endif
