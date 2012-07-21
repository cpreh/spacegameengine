/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SHADER_SCOPED_PAIR_HPP_INCLUDED
#define SGE_SHADER_SCOPED_PAIR_HPP_INCLUDED

#include <sge/renderer/cg/scoped_program.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/shader/pair_fwd.hpp>
#include <sge/shader/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace shader
{
class scoped_pair
{
	FCPPT_NONCOPYABLE(
		scoped_pair);
public:
	SGE_SHADER_SYMBOL
	scoped_pair(
		sge::renderer::context::object &,
		sge::shader::pair &);

	SGE_SHADER_SYMBOL
	~scoped_pair();
private:
	sge::shader::pair &parent_;
	sge::renderer::cg::scoped_program scoped_vertex_program_;
	sge::renderer::cg::scoped_program scoped_pixel_program_;
};
}
}

#endif
