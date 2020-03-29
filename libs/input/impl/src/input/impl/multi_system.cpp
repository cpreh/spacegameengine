//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/impl/log_name.hpp>
#include <sge/input/impl/multi_processor.hpp>
#include <sge/input/impl/multi_system.hpp>
#include <sge/input/impl/system_ptr_vector.hpp>
#include <sge/input/plugin/collection.hpp>
#include <sge/input/plugin/context.hpp>
#include <sge/input/plugin/iterator.hpp>
#include <sge/input/plugin/object.hpp>
#include <sge/input/plugin/traits.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/log/context_reference.hpp>


sge::input::impl::multi_system::multi_system(
	fcppt::log::context_reference const _log_context,
	sge::input::plugin::collection const &_collection
)
:
	sge::input::system(),
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			sge::input::impl::log_name()
		)
	},
	plugins_(
		fcppt::algorithm::map<
			sge::input::impl::multi_system::plugin_vector
		>(
			_collection,
			[](
				sge::input::plugin::context const &_context
			)
			{
				return
					_context.load();
			}
		)
	),
	systems_(
		fcppt::algorithm::map<
			sge::input::impl::system_ptr_vector
		>(
			plugins_,
			[
				&_log_context
			](
				sge::input::plugin::object const &_plugin
			)
			{
				return
					_plugin.get()(
						_log_context
					);
			}
		)
	),
	capabilities_(
		fcppt::algorithm::fold(
			systems_,
			sge::input::capabilities_field::null(),
			[](
				sge::input::system_unique_ptr const &_system,
				sge::input::capabilities_field const &_state
			)
			{
				return
					_state
					|
					_system->capabilities();
			}
		)
	)
{
}

sge::input::impl::multi_system::~multi_system()
{
}

sge::input::processor_unique_ptr
sge::input::impl::multi_system::create_processor(
	sge::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::processor
		>(
			fcppt::make_unique_ptr<
				sge::input::impl::multi_processor
			>(
				log_,
				_window,
				systems_
			)
		);
}

sge::input::capabilities_field
sge::input::impl::multi_system::capabilities() const
{
	return
		capabilities_;
}
