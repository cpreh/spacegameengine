#ifndef SGE_SRC_RUCKSACK_TESTBED_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SRC_RUCKSACK_TESTBED_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/systems/instance.hpp>
#include <sge/window/title.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <utility>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace testbed
{
class object_impl
{
FCPPT_NONCOPYABLE(
	object_impl);
public:
	explicit
	object_impl(
		sge::window::title const &);

	void
	add_widget(
		sge::rucksack::widget::base &,
		sge::image::color::any::object const &);

	awl::main::exit_code const
	run();

	void
	update();

	void
	render(
		sge::renderer::context::object &);

	sge::systems::instance const &
	systems() const;

	~object_impl();
private:
	typedef
	sge::sprite::config::choices
	<
		sge::sprite::config::type_choices
		<
			sge::sprite::config::unit_type<rucksack::scalar>,
			sge::sprite::config::float_type<float>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1
		<
			sge::sprite::config::with_color<sge::image::color::rgba8_format>
		>
	>
	sprite_choices;

	typedef
	sge::sprite::buffers::with_declaration
	<
		sge::sprite::buffers::single<sprite_choices>
	>
	sprite_buffers;

	typedef
	sge::sprite::object<sprite_choices>
	sprite_object;

	typedef
	sge::sprite::parameters<sprite_choices>
	sprite_parameters;

	typedef
	std::vector
	<
		std::pair
		<
			sge::rucksack::widget::base*,
			sprite_object
		>
	>
	sprite_list;

	sge::systems::instance const systems_;
	sprite_buffers buffers_;
	sprite_list sprites_;
	fcppt::signal::scoped_connection const quit_connection_;
};
}
}
}

#endif

