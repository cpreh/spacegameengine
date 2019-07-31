//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_FIND_PLUGIN_OPT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_FIND_PLUGIN_OPT_HPP_INCLUDED

#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <sge/systems/impl/plugin_pair_decl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace impl
{

template<
	typename System,
	typename TestFunction
>
fcppt::optional::object<
	sge::systems::impl::plugin_pair<
		System
	>
>
find_plugin_opt(
	fcppt::log::context &_log_context,
	sge::plugin::collection<
		System
	> const &_collection,
	TestFunction const &_test_function
)
{
	return
		fcppt::algorithm::find_by_opt(
			_collection,
			[
				&_log_context,
				&_test_function
			](
				sge::plugin::context<
					System
				> const &_element
			)
			{
				typedef
				sge::systems::impl::plugin_pair<
					System
				>
				pair_type;

				typedef
				fcppt::optional::object<
					pair_type
				>
				return_type;

				typedef
				sge::plugin::object<
					System
				>
				plugin_type;

				plugin_type plugin{
					_element.load()
				};

				typedef
				fcppt::unique_ptr<
					System
				>
				system_unique_ptr;

				system_unique_ptr system{
					plugin.get()(
						_log_context
					)
				};

				return
					_test_function(
						*system
					)
					?
						return_type{
							pair_type{
								std::move(
									plugin
								),
								std::move(
									system
								)
							}
						}
					:
						return_type{}
					;
			}
		);
}

}
}
}

#endif
