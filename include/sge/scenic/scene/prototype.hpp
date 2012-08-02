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


#ifndef SGE_SCENIC_SCENE_PROTOTYPE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_PROTOTYPE_HPP_INCLUDED

#include <sge/renderer/ambient_color.hpp>
#include <sge/scenic/camera_properties.hpp>
#include <sge/scenic/light_sequence.hpp>
#include <sge/scenic/mesh_sequence.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/fog/properties.hpp>


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
	SGE_SCENIC_SYMBOL
	prototype(
		sge::scenic::camera_properties const &,
		sge::scenic::fog::properties const &,
		sge::renderer::ambient_color const &);

	SGE_SCENIC_SYMBOL
	sge::scenic::mesh_sequence const &
	meshes() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::mesh_sequence &
	meshes();

	SGE_SCENIC_SYMBOL
	sge::scenic::light_sequence const &
	lights() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::light_sequence &
	lights();

	SGE_SCENIC_SYMBOL
	sge::scenic::camera_properties const &
	camera() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::fog::properties const &
	fog() const;

	SGE_SCENIC_SYMBOL
	sge::renderer::ambient_color const &
	ambient_color() const;

	SGE_SCENIC_SYMBOL
	~prototype();
private:
	sge::scenic::camera_properties camera_;
	sge::scenic::fog::properties fog_;
	sge::renderer::ambient_color ambient_color_;
	sge::scenic::mesh_sequence meshes_;
	sge::scenic::light_sequence lights_;
};
}
}
}

#endif
