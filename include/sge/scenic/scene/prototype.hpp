/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SCENIC_SCENE_PROTOTYPE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_PROTOTYPE_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/fog/optional_properties.hpp>
#include <sge/scenic/render_context/fog/properties.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/scene/camera_properties.hpp>
#include <sge/scenic/scene/entity_sequence.hpp>
#include <fcppt/optional.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
class prototype
{
FCPPT_NONCOPYABLE(
	prototype);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	prototype(
		sge::scenic::scene::camera_properties const &,
		sge::scenic::render_context::fog::optional_properties const &,
		sge::scenic::render_context::ambient_color const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::entity_sequence const &
	entities() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::entity_sequence &
	entities();

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::sequence const &
	lights() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::sequence &
	lights();

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::camera_properties const &
	camera() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::fog::optional_properties const &
	fog() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::ambient_color const &
	ambient_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	~prototype();
private:
	sge::scenic::scene::camera_properties camera_;
	sge::scenic::render_context::fog::optional_properties fog_;
	sge::scenic::render_context::ambient_color ambient_color_;
	sge::scenic::scene::entity_sequence entities_;
	sge::scenic::render_context::light::sequence lights_;
};
}
}
}

#endif
