//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GRAPH_OBJECT_HPP_INCLUDED
#define SGE_GRAPH_OBJECT_HPP_INCLUDED

#include <sge/graph/baseline.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/object_fwd.hpp>
#include <sge/graph/optional_axis_constraint.hpp>
#include <sge/graph/position.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/graph/detail/draw_visitor_fwd.hpp>
#include <sge/graph/detail/symbol.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
	SGE_GRAPH_DETAIL_SYMBOL
	object(
		sge::graph::position const &,
		sge::renderer::dim2 const &,
		sge::renderer::device::ffp &,
		sge::graph::baseline,
		sge::graph::optional_axis_constraint const &,
		sge::graph::color_scheme const &);

	SGE_GRAPH_DETAIL_SYMBOL
	void
	push(
		sge::graph::scalar _datum);

	SGE_GRAPH_DETAIL_SYMBOL
	void
	render(
		sge::renderer::context::ffp &);

	SGE_GRAPH_DETAIL_SYMBOL
	~object();

private:
	friend class sge::graph::detail::draw_visitor;

	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::always
		>,
		metal::list<
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

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	typedef sge::sprite::state::all_choices sprite_state_choices;

	typedef sge::sprite::state::object<
		sprite_state_choices
	> sprite_state;

	typedef sge::sprite::state::parameters<
		sprite_state_choices
	> sprite_state_parameters;

	typedef
	boost::circular_buffer<
		sge::graph::scalar
	>
	buffer_type;

	sge::renderer::dim2
	dim_;

	sge::renderer::texture::planar_unique_ptr const
	texture_;

	sprite_object const
	sprite_object_;

	sprite_buffers_type
	sprite_buffers_;

	sprite_state
	sprite_state_;

	buffer_type
	data_buffer_;

	sge::graph::scalar
	baseline_;

	sge::graph::color_scheme
	color_scheme_;

	sge::graph::optional_axis_constraint
	axis_constraint_;

	sge::graph::scalar
	current_min_;

	sge::graph::scalar
	current_max_;

	template<typename View>
	void
	clear(
		View const &_view);

	template<typename View>
	void
	draw_data(
		View const &_view);
};
}
}

#endif
