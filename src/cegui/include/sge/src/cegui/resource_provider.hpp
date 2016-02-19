/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_CEGUI_RESOURCE_PROVIDER_HPP_INCLUDED
#define SGE_SRC_CEGUI_RESOURCE_PROVIDER_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/ResourceProvider.h>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace cegui
{
class RawDataContainer;
class String;
}

namespace sge
{
namespace cegui
{

class resource_provider
:
	public CEGUI::ResourceProvider
{
	FCPPT_NONCOPYABLE(
		resource_provider
	);
public:
	resource_provider();

	~resource_provider()
	override;
private:
	void
	loadRawDataContainer(
		CEGUI::String const &filename,
		CEGUI::RawDataContainer &output,
		CEGUI::String const &resourceGroup
	)
	override;

	void
	unloadRawDataContainer(
		CEGUI::RawDataContainer &
	)
	override;

	size_t
	getResourceGroupFileNames(
		std::vector<CEGUI::String>& out_vec,
		CEGUI::String const &file_pattern,
		CEGUI::String const &resource_group
	)
	override;
};

}
}

#endif
