//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_FIND_PLUGIN_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_FIND_PLUGIN_HPP_INCLUDED

#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/object.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/impl/find_plugin_opt.hpp>
#include <sge/systems/impl/plugin_pair_decl.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
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
sge::systems::impl::plugin_pair<
	System
>
find_plugin(
	fcppt::log::context_reference const _log_context,
	sge::plugin::collection<
		System
	> const &_collection,
	sge::systems::optional_name const &_opt_name,
	TestFunction const &_test_function
)
{
	return
		fcppt::optional::to_exception(
			fcppt::optional::maybe(
				_opt_name,
				[
					&_log_context,
					&_collection,
					&_test_function
				]{
					return
						sge::systems::impl::find_plugin_opt(
							_log_context,
							_collection,
							_test_function
						);
				},
				[
					&_log_context,
					&_collection,
					&_test_function
				](
					sge::plugin::name const &_name
				)
				{
					using
					return_type
					=
					sge::systems::impl::plugin_pair<
						System
					>;

					return
						fcppt::algorithm::find_by_opt<
							return_type
						>(
							_collection,
							[
								&_log_context,
								&_test_function,
								&_name
							](
								sge::plugin::context<
									System
								> const &_element
							)
							{
								using
								optional_result
								=
								fcppt::optional::object<
									return_type
								>;

								if(
									_element.info().name()
									!=
									_name
								)
								{
									return
										optional_result{};
								}

								using
								plugin_type
								=
								sge::plugin::object<
									System
								>;

								plugin_type plugin(
									_element.load()
								);

								using
								system_unique_ptr
								=
								fcppt::unique_ptr<
									System
								>;

								system_unique_ptr system(
									plugin.get()(
										_log_context
									)
								);

								if(
									_test_function(
										*system
									)
								)
								{
									return
										optional_result{
											return_type{
												std::move(
													plugin
												),
												std::move(
													system
												)
											}
										};
								}

								throw
									sge::systems::exception{
										FCPPT_TEXT("Plugin of type ")
										+
										fcppt::from_std_string(
											fcppt::type_name_from_info(
												typeid(
													System
												)
											)
										)
										+
										FCPPT_TEXT(" and name ")
										+
										_name.get()
										+
										FCPPT_TEXT(" was explicitly requested but doesn't match the requested capabilities.")
									};
							}
						);
				}
			),
			[
				&_opt_name
			]{
				return
					sge::systems::exception(
						FCPPT_TEXT("No plugin of type ")
						+
						fcppt::from_std_string(
							fcppt::type_name_from_info(
								typeid(
									System
								)
							)
						)
						+
						fcppt::optional::maybe(
							_opt_name,
							[]{
								return
									fcppt::string{
										FCPPT_TEXT(" matched the requested capabilities.")
									};
							},
							[](
								sge::plugin::name const &_name
							)
							{
								return
									FCPPT_TEXT(" and with name ")
									+
									_name.get()
									+
									FCPPT_TEXT(" found.");
							}
						)
					);
			}
		);
}

}
}
}

#endif
