//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/create_multi_system.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/impl/multi_system.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::input::system_unique_ptr
sge::input::create_multi_system(
	fcppt::log::context &_log_context,
	sge::input::plugin::collection const &_collection
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::system
		>(
			fcppt::make_unique_ptr<
				sge::input::impl::multi_system
			>(
				_log_context,
				_collection
			)
		);
}
