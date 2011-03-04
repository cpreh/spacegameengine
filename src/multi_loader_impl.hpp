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


#ifndef SGE_MULTI_LOADER_IMPL_HPP_INCLUDED
#define SGE_MULTI_LOADER_IMPL_HPP_INCLUDED

#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/loaders_exhausted.hpp>
#include <sge/log/global.hpp>
#include <sge/all_extensions.hpp>
#include <sge/extension.hpp>
#include <sge/multi_loader.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/set_intersection.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

template<
	typename Loader,
	typename File,
	typename Exception,
	typename Capabilities
>
sge::multi_loader<Loader, File, Exception, Capabilities>::multi_loader(
	plugin::manager &_pm,
	extension_set const &_extensions,
	capabilities const &_capabilities
)
:
	plugins_(),
	loaders_()
{
	for (
		plugin::iterator<loader> i = _pm.begin<loader>();
		i != _pm.end<loader>();
		++i
	)
	{
		plugin_ptr const plugin(
			i->load()
		);

		loader_ptr const loader_instance(
			plugin->get()()
		);

		// check if this plugin might be useful
		if(
			fcppt::container::bitfield::is_subset_eq(
				_capabilities,
				loader_instance->capabilities()
			)
			&&
			(
				_extensions == sge::all_extensions
				||
				!fcppt::algorithm::set_intersection(
					_extensions,
					loader_instance->extensions()
				).empty()
			)
		)
		{
			plugins_.push_back(
				plugin
			);

			loaders_.push_back(
				loader_instance
			);
		}
		else
		{
			FCPPT_LOG_DEBUG(
				log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("loader ")
					<< fcppt::type_name(typeid(loader))
					<< FCPPT_TEXT(" didn't find plugin \"")
					<< i->base().path()
					<< FCPPT_TEXT("\" to be useful.")
			)
		}
	}
}

template<
	typename Loader,
	typename File,
	typename Exception,
	typename Capabilities
>
sge::multi_loader<Loader, File, Exception, Capabilities>::~multi_loader()
{}

template<
	typename Loader,
	typename File,
	typename Exception,
	typename Capabilities
>
typename sge::multi_loader<Loader, File, Exception, Capabilities>::file_ptr const
sge::multi_loader<Loader, File, Exception, Capabilities>::load(
	fcppt::filesystem::path const &_file
)
{
	if(
		!fcppt::filesystem::exists(
			_file
		)
	)
		throw sge::exception(
			FCPPT_TEXT("file \"")
			+ fcppt::filesystem::path_to_string(
				_file
			)
			+ FCPPT_TEXT("\" does not exist")
		);

	if(
		!fcppt::filesystem::is_regular(
			_file
		)
	)
		throw sge::exception(
			FCPPT_TEXT("file \"")
			+ fcppt::filesystem::path_to_string(
				_file
			)
			+ FCPPT_TEXT("\" is not a regular file")
		);

	fcppt::string const extension(
		fcppt::filesystem::extension_without_dot(
			_file
		)
	);

	if (
		extension.empty()
	)
		throw sge::loaders_exhausted(
			FCPPT_TEXT("File ")
			+
			fcppt::filesystem::path_to_string(
				_file
			)
			+
			FCPPT_TEXT(" has no extension!")
		);

	BOOST_FOREACH(
		typename loader_container::const_reference ref,
		loaders_
	)
	{
		if(
			!fcppt::algorithm::contains(
				ref->extensions(),
				extension
			)
		)
			continue;

		return
			ref->load(
				_file
			);
	}

	throw sge::loaders_exhausted(
		FCPPT_TEXT("Tried all loaders for ")
		+ 
		fcppt::filesystem::path_to_string(
			_file
		)
		+
		FCPPT_TEXT(" but none matched!")
	);
}

template<
	typename Loader,
	typename File,
	typename Exception,
	typename Capabilities
>
typename sge::multi_loader<Loader, File, Exception, Capabilities>::file_ptr const
sge::multi_loader<Loader, File, Exception, Capabilities>::load(
	sge::const_raw_range const &_range,
	sge::optional_extension const &_extension
)
{
	BOOST_FOREACH(
		typename loader_container::const_reference ref,
		loaders_
	)
	{
		if(
			_extension
			&&
			!fcppt::algorithm::contains(
				ref->extensions(),
				*_extension
			)
		)
			continue;

		file_ptr const ret(
			ref->load(
				_range,
				_extension
			)
		);

		if(
			ret
		)
			return ret;
	}

	throw sge::loaders_exhausted(
		FCPPT_TEXT("Couldn't load file from memory.")
		+
		(
			_extension
			?
				FCPPT_TEXT(" It has extension ")
				+ *_extension
				+ FCPPT_TEXT('.')
			:
				sge::extension(
					FCPPT_TEXT(" It has not extension provided.")
				)
		)
	);

}

template<
	typename Loader,
	typename File,
	typename Exception,
	typename Capabilities
>
typename sge::multi_loader<Loader, File, Exception, Capabilities>::loader_container const &
sge::multi_loader<Loader, File, Exception, Capabilities>::loaders() const
{
	return loaders_;
}

#endif
