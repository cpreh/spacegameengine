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


#ifndef SGE_MULTI_LOADER_HPP_INCLUDED
#define SGE_MULTI_LOADER_HPP_INCLUDED

#include <sge/multi_loader_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/plugin/context.hpp>
#include <sge/const_raw_range.hpp>
#include <sge/extension_set.hpp>
#include <sge/instantiate_symbol.hpp>
#include <sge/optional_extension.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr.hpp>
#include <vector>

namespace sge
{

template<
	typename Loader,
	typename File,
	typename Exception,
	typename Capabilities
>
class multi_loader
{
	FCPPT_NONCOPYABLE(
		multi_loader
	);
public:
	typedef Loader loader;
	typedef File file;
	typedef Exception exception;
	typedef Capabilities capabilities;
	typedef fcppt::shared_ptr<loader> loader_ptr;
	typedef fcppt::shared_ptr<file> file_ptr;

	typedef std::vector<
		loader_ptr
	> loader_container;

	SGE_INSTANTIATE_SYMBOL
	explicit multi_loader(
		plugin::manager &,
		extension_set const &,
		capabilities const &
	);

	SGE_INSTANTIATE_SYMBOL
	~multi_loader();

	SGE_INSTANTIATE_SYMBOL
	file_ptr const
	load(
		fcppt::filesystem::path const &
	);

	SGE_INSTANTIATE_SYMBOL
	file_ptr const
	load_raw(
		sge::const_raw_range const &,
		sge::optional_extension const &
	);

	SGE_INSTANTIATE_SYMBOL
	loader_container const &
	loaders() const;
private:
	typedef typename plugin::context<
		loader
	>::ptr_type plugin_ptr;

	typedef std::vector<
		plugin_ptr
	> plugin_container;

	plugin_container plugins_;

	loader_container loaders_;
};

}

#endif
