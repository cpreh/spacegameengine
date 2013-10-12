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

#include <sge/log/global.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/loaders_exhausted.hpp>
#include <sge/media/muxer_parameters.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/path_to_extension.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/object_unique_ptr.hpp>
#include <sge/src/media/detail/muxer.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/set_intersection.hpp>
#include <fcppt/algorithm/set_union.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <memory>
#include <typeinfo>
#include <utility>
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
	plugins_(),
	systems_(),
	capabilities_(
		_parameters.capabilities()
	),
	extensions_()
{
	sge::plugin::collection<
		system
	> const &collection(
		_parameters.collection()
	);

	for(
		sge::plugin::iterator<
			system
		> it(
			collection.begin()
		);
		it != collection.end();
		++it
	)
	{
		typedef typename sge::plugin::object_unique_ptr<
			System
		>::type plugin_unique_ptr;

		plugin_unique_ptr plugin(
			it->load()
		);

		typedef std::unique_ptr<
			System
		> system_unique_ptr;

		system_unique_ptr system_instance(
			plugin->get()()
		);

		// check if this plugin might be useful
		if(
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
		)
		{
			capabilities_ &=
				system_instance->capabilities();

			extensions_ =
				fcppt::algorithm::set_union(
					system_instance->extensions(),
					extensions_
				);

			fcppt::container::ptr::push_back_unique_ptr(
				plugins_,
				std::move(
					plugin
				)
			);

			fcppt::container::ptr::push_back_unique_ptr(
				systems_,
				std::move(
					system_instance
				)
			);
		}
		else
		{
			FCPPT_LOG_DEBUG(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("system ")
					<<
					fcppt::type_name_from_info(
						typeid(
							system
						)
					)
					<< FCPPT_TEXT(" didn't find plugin ")
					<< it->path()
					<< FCPPT_TEXT(" to be useful.")
			)
		}
	}
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
	try
	{
		return
			this->mux_extension(
				sge::media::path_to_extension(
					_file
				),
				_function
			);
	}
	catch(
		sge::media::loaders_exhausted const &
	)
	{
		throw sge::media::loaders_exhausted(
			FCPPT_TEXT("Tried all loaders for ")
			+ fcppt::filesystem::path_to_string(
				_file
			)
			+ FCPPT_TEXT(" but none matched!")
		);
	}
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
		auto &cur_system : systems_
	)
	{
		if(
			_extension
			&&
			!fcppt::algorithm::contains(
				cur_system.extensions(),
				*_extension
			)
		)
			continue;

		file_unique_ptr result(
			_function(
				cur_system
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

	throw sge::media::loaders_exhausted(
		FCPPT_TEXT("Tried all loaders for ")
		+
		(
			_extension
			?
				_extension->get()
			:
				FCPPT_TEXT("any extension")
		)
		+
		FCPPT_TEXT(" but none matched!")
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
sge::media::extension_set const
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
