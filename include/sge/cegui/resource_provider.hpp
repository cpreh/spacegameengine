#ifndef SGE_CEGUI_RESOURCE_PROVIDER_HPP_INCLUDED
#define SGE_CEGUI_RESOURCE_PROVIDER_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <CEGUI/CEGUIResourceProvider.h>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sge
{
namespace cegui
{
class SGE_CLASS_SYMBOL resource_provider
:
	public CEGUI::ResourceProvider
{
FCPPT_NONCOPYABLE(
	resource_provider);
public:
	SGE_CEGUI_SYMBOL explicit
	resource_provider(
		fcppt::filesystem::path const &);

	SGE_CEGUI_SYMBOL void 
	loadRawDataContainer(
		CEGUI::String const &filename, 
		CEGUI::RawDataContainer &output, 
		CEGUI::String const &resourceGroup);

	SGE_CEGUI_SYMBOL void 
	unloadRawDataContainer(
		CEGUI::RawDataContainer&);

	SGE_CEGUI_SYMBOL size_t 
	getResourceGroupFileNames(
		std::vector<CEGUI::String>& out_vec,
		CEGUI::String const &file_pattern,
		CEGUI::String const &resource_group);

	SGE_CEGUI_SYMBOL fcppt::filesystem::path const
	to_absolute_path(
		CEGUI::String const &filename, 
		CEGUI::String const &resourceGroup);

	SGE_CEGUI_SYMBOL ~resource_provider();
private:
	fcppt::filesystem::path const prefix_;
};
}
}

#endif
