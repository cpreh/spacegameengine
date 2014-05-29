/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_MEDIA_DETAIL_MUXER_IMPL_HPP_INCLUDED
#define SGE_SRC_MEDIA_DETAIL_MUXER_IMPL_HPP_INCLUDED

#include <sge/media/extension_set.hpp>
#include <sge/media/muxer_parameters.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/path_to_extension.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/load_with_log_options.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/media/logger.hpp>
#include <sge/src/media/detail/muxer.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/algorithm/set_intersection.hpp>
#include <fcppt/algorithm/set_union.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <memory>
#include <utility>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


template<
	typename System,
	typename File,
	typename Capabilities
>
sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::muxer(
	parameters const &_parameters
)
:
	plugins_(
		fcppt::algorithm::map_optional<
			plugin_system_pair_container
		>(
			_parameters.collection(),
			[
				&_parameters
			](
				sge::plugin::context<
					System
				> const &_context
			)
			{
				plugin_type plugin(
					sge::plugin::load_with_log_options(
						_context,
						_parameters.log_options()
					)
				);

				system_unique_ptr system_instance(
					plugin.get()()
				);

				typedef
				fcppt::optional<
					plugin_system_pair
				>
				optional_plugin_system_pair;

				// check if this plugin might be useful
				optional_plugin_system_pair result(
					fcppt::container::bitfield::is_subset_eq(
						_parameters.capabilities(),
						system_instance->capabilities()
					)
					&&
					(
						!_parameters.extensions().has_value()
						||
						!fcppt::algorithm::set_intersection(
							*_parameters.extensions(),
							system_instance->extensions()
						).empty()
					)
					?
						optional_plugin_system_pair(
							std::make_pair(
								std::move(
									plugin
								),
								std::move(
									system_instance
								)
							)
						)
					:
						optional_plugin_system_pair()
				);

				if(
					!result
				)
					FCPPT_LOG_DEBUG(
						sge::media::logger(),
						fcppt::log::_
							<< FCPPT_TEXT("System ")
							<< fcppt::type_name_from_info(
								typeid(
									system
								)
							)
							<< FCPPT_TEXT(" didn't find plugin ")
							<< fcppt::filesystem::path_to_string(
								_context.path()
							)
							<< FCPPT_TEXT(" to be useful.")
					);

				return
					std::move(
						result
					);
			}
		)
	),
	capabilities_(
		fcppt::algorithm::fold(
			plugins_,
			_parameters.capabilities(),
			[](
				plugin_system_pair const &_plugin,
				capabilities_field const &_state
			)
			{
				return
					_state
					&
					_plugin.second->capabilities();
			}
		)
	),
	extensions_(
		fcppt::algorithm::fold(
			plugins_,
			sge::media::extension_set(),
			[](
				plugin_system_pair const &_plugin,
				sge::media::extension_set const &_state
			)
			{
				return
					fcppt::algorithm::set_union(
						_plugin.second->extensions(),
						_state
					);

			}
		)
	)
{
}

template<
	typename System,
	typename File,
	typename Capabilities
>
sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::~muxer()
{
}

template<
	typename System,
	typename File,
	typename Capabilities
>
typename sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::file_unique_ptr
sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::mux_path(
	boost::filesystem::path const &_file,
	load_function const &_function
) const
{
	return
		this->mux_extension(
			sge::media::path_to_extension(
				_file
			),
			_function
		);
}

template<
	typename System,
	typename File,
	typename Capabilities
>
typename sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::file_unique_ptr
sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::mux_extension(
	sge::media::optional_extension const &_extension,
	load_function const &_function
) const
{
	for(
		auto &cur_plugin
		:
		plugins_
	)
	{
		auto &cur_system(
			cur_plugin.second
		);

		if(
			_extension
			&&
			!fcppt::algorithm::contains(
				cur_system->extensions(),
				*_extension
			)
		)
			continue;

		file_unique_ptr result(
			_function(
				*cur_system
			)
		);

		if(
			result
		)
			return
				std::move(
					result
				);
	}

	return
		file_unique_ptr();
}

template<
	typename System,
	typename File,
	typename Capabilities
>
typename sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::capabilities_field const
sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::capabilities() const
{
	return
		capabilities_;
}

template<
	typename System,
	typename File,
	typename Capabilities
>
sge::media::extension_set
sge::media::detail::muxer<
	System,
	File,
	Capabilities
>::extensions() const
{
	return
		extensions_;
}

#endif
