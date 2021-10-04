//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_RESOURCE_PROVIDER_HPP_INCLUDED
#define SGE_CEGUI_IMPL_RESOURCE_PROVIDER_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/ResourceProvider.h>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class RawDataContainer;
class String;
}

namespace sge::cegui::impl
{

class resource_provider
:
	public CEGUI::ResourceProvider
{
	FCPPT_NONMOVABLE(
		resource_provider
	);
public:
	explicit
	resource_provider(
		fcppt::log::object & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

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

	[[nodiscard]]
	size_t
	getResourceGroupFileNames(
		std::vector<CEGUI::String>& out_vec, // NOLINT(google-runtime-references)
		CEGUI::String const &file_pattern,
		CEGUI::String const &resource_group
	)
	override;

	fcppt::log::object log_;
};

}

#endif
