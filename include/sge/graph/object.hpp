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


#ifndef SGE_GRAPH_OBJECT_HPP_INCLUDED
#define SGE_GRAPH_OBJECT_HPP_INCLUDED

#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/graph/position.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/graph/symbol.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/rgba8.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace graph
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_GRAPH_SYMBOL
	object(
		sge::graph::position const &,
		sge::image2d::dim const &,
		sge::renderer::device &,
		sge::graph::foreground_color const &,
		sge::graph::background_color const &,
		sge::graph::baseline);

	SGE_GRAPH_SYMBOL
	void
	push(
		sge::graph::scalar _datum);

	SGE_GRAPH_SYMBOL
	void
	render(
		sge::renderer::context::object &);

	SGE_GRAPH_SYMBOL
	~object();

private:
	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::shared
			>
		>
	> sprite_choices;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	typedef
	boost::circular_buffer<
		sge::graph::scalar
	>
	buffer_type;

	sge::renderer::dim2
	dim_;

	sge::renderer::texture::planar_scoped_ptr const
	texture_;

	sprite_object const
	sprite_object_;

	sprite_buffers_type
	sprite_buffers_;

	sge::image::color::any::object const &
	foreground_color_;

	sge::image::color::any::object const &
	background_color_;

	buffer_type
	data_buffer_;

	sge::graph::scalar
	baseline_;

	sge::graph::scalar
	current_min_;

	sge::graph::scalar
	current_max_;

	void
	clear(sge::image2d::view::object const _view);

	void
	draw_data(sge::image2d::view::object const _view);
};
}
}

#endif
