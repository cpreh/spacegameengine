/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_ATTENUATION_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_ATTENUATION_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/light/attenuation_fwd.hpp>
#include <sge/scenic/render_context/light/constant_attenuation.hpp>
#include <sge/scenic/render_context/light/linear_attenuation.hpp>
#include <sge/scenic/render_context/light/quadratic_attenuation.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace light
{
class attenuation
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	attenuation(
		sge::scenic::render_context::light::constant_attenuation const &,
		sge::scenic::render_context::light::linear_attenuation const &,
		sge::scenic::render_context::light::quadratic_attenuation const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::constant_attenuation
	constant_attenuation() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::linear_attenuation
	linear_attenuation() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::quadratic_attenuation
	quadratic_attenuation() const;
private:
	sge::scenic::render_context::light::constant_attenuation constant_attenuation_;
	sge::scenic::render_context::light::linear_attenuation linear_attenuation_;
	sge::scenic::render_context::light::quadratic_attenuation quadratic_attenuation_;
};
}
}
}
}

#endif
