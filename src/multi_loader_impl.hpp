/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/multi_loader.hpp>
#include <sge/all_extensions.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/set_intersection.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>
#include <fcppt/log/headers.hpp>
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
	plugin::manager &pm,
	extension_set const &extensions,
	capabilities const &capabilities_
)
:
	plugins_(),
	loaders_()
{
	for (
		plugin::iterator<loader> i = pm.begin<loader>();
		i != pm.end<loader>();
		++i
	)
	{
		plugin_ptr const plugin_(
			i->load()
		);

		loader_ptr const loader_(
			plugin_->get()()
		);

		// check if this plugin might be useful
		if(
			fcppt::container::bitfield::is_subset_eq(
				capabilities_,
				loader_->capabilities()
			)
			&&
			(
				extensions == sge::all_extensions
				||
				!fcppt::algorithm::set_intersection(
					extensions,
					loader_->extensions()
				).empty()
			)
		)
		{
			plugins_.push_back(
				plugin_
			);

			loaders_.push_back(
				loader_
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
					<< i->info().name()
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
	fcppt::filesystem::path const &file
)
{
	if (!fcppt::filesystem::exists(file))
		throw exception(
			FCPPT_TEXT("file \"")
			+ fcppt::filesystem::path_to_string(
				file
			)
			+ FCPPT_TEXT("\" does not exist")
		);

	if (!fcppt::filesystem::is_regular(file))
		throw exception(
			FCPPT_TEXT("file \"")
			+ fcppt::filesystem::path_to_string(
				file
			)
			+ FCPPT_TEXT("\" is not a regular file")
		);

	fcppt::string const extension(
		fcppt::filesystem::extension_without_dot(
			file
		)
	);

	if (extension.empty())
		throw loaders_exhausted(
			file,
			FCPPT_TEXT("File has no extension!")
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
				file
			);
	}

	throw loaders_exhausted(
		file,
		FCPPT_TEXT("Tried all loaders but none matched!")
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
