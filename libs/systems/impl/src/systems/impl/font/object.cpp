//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/system.hpp>
#include <sge/font/plugin/collection_fwd.hpp>
#include <sge/font/plugin/traits.hpp>
#include <sge/plugin/object.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/impl/font/find_plugin.hpp>
#include <sge/systems/impl/font/object.hpp>
#include <fcppt/log/context_reference.hpp>


sge::systems::impl::font::object::object(
	fcppt::log::context_reference const _log_context,
	sge::font::plugin::collection const &_collection,
	sge::systems::font const &_parameters
)
:
	font_plugin_(
		sge::systems::impl::font::find_plugin(
			_collection,
			_parameters
		)
	),
	font_system_(
		font_plugin_.get()(
			_log_context
		)
	)
{
}

sge::systems::impl::font::object::~object()
{
}

sge::font::system &
sge::systems::impl::font::object::system() const
{
	return
		*font_system_;
}
