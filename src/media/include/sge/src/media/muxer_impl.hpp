/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_MEDIA_MUXER_IMPL_HPP_INCLUDED
#define SGE_SRC_MEDIA_MUXER_IMPL_HPP_INCLUDED

#include <sge/media/all_extensions.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/loaders_exhausted.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/muxer_parameters.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/path_to_extension.hpp>
#include <sge/log/global.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/set_intersection.hpp>
#include <fcppt/algorithm/set_union.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


template<
	typename System,
	typename Capabilities
>
sge::media::muxer<
	System,
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
	for(
		plugin::iterator<system> it(
			_parameters.manager(). template begin<system>()
		);
		it != _parameters.manager().template end<system>();
		++it
	)
	{
		plugin_ptr const plugin(
			it->load()
		);

		system_ptr const system_instance(
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
				_parameters.extensions() == sge::media::all_extensions
				||
				!fcppt::algorithm::set_intersection(
					_parameters.extensions(),
					system_instance->extensions()
				).empty()
			)
		)
		{
			plugins_.push_back(
				plugin
			);

			systems_.push_back(
				system_instance
			);

			capabilities_ &=
				system_instance->capabilities();

			extensions_ =
				fcppt::algorithm::set_union(
					system_instance->extensions(),
					extensions_
				);
		}
		else
		{
			FCPPT_LOG_DEBUG(
				log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("system ")
					<< fcppt::type_name(typeid(system))
					<< FCPPT_TEXT(" didn't find plugin \"")
					<< it->base().path()
					<< FCPPT_TEXT("\" to be useful.")
			)
		}
	}
}

template<
	typename System,
	typename Capabilities
>
sge::media::muxer<
	System,
	Capabilities
>::~muxer()
{
}

template<
	typename System,
	typename Capabilities
>
typename sge::media::muxer<
	System,
	Capabilities
>::system &
sge::media::muxer<
	System,
	Capabilities
>::mux_path(
	fcppt::filesystem::path const &_file
) const
{
	try
	{
		return
			this->mux_extension(
				sge::media::path_to_extension(
					_file
				)
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
	typename Capabilities
>
typename sge::media::muxer<
	System,
	Capabilities
>::system &
sge::media::muxer<
	System,
	Capabilities
>::mux_extension(
	sge::media::optional_extension const &_extension
) const
{
	for(
		typename system_container::const_iterator it(
			systems_.begin()
		);
		it != systems_.end();
		++it
	)
	{
		if(
			!_extension
			||
			fcppt::algorithm::contains(
				(*it)->extensions(),
				*_extension
			)
		)
			return *it->get();
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
	typename Capabilities
>
typename sge::media::muxer<
	System,
	Capabilities
>::capabilities_field const
sge::media::muxer<
	System,
	Capabilities
>::capabilities() const
{
	return capabilities_;
}

template<
	typename System,
	typename Capabilities
>
sge::media::extension_set const
sge::media::muxer<
	System,
	Capabilities
>::extensions() const
{
	return extensions_;
}

#endif
