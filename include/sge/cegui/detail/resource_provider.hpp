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


#ifndef SGE_CEGUI_DETAIL_RESOURCE_PROVIDER_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_RESOURCE_PROVIDER_HPP_INCLUDED

#include <sge/charconv/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIResourceProvider.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{
namespace detail
{
class resource_provider
:
	public CEGUI::ResourceProvider
{
FCPPT_NONCOPYABLE(
	resource_provider);
public:
	explicit
	resource_provider(
		sge::charconv::system &);

	void
	loadRawDataContainer(
		CEGUI::String const &filename,
		CEGUI::RawDataContainer &output,
		CEGUI::String const &resourceGroup);

	void
	unloadRawDataContainer(
		CEGUI::RawDataContainer&);

	size_t
	getResourceGroupFileNames(
		std::vector<CEGUI::String>& out_vec,
		CEGUI::String const &file_pattern,
		CEGUI::String const &resource_group);

	~resource_provider();
private:
	sge::charconv::system &charconv_system_;
};
}
}
}

#endif
