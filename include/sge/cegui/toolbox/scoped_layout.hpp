#ifndef SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED

#include <sge/charconv/system_ptr.hpp>
#include <sge/cegui/symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>

namespace CEGUI
{
class Window;
}

namespace sge
{
namespace cegui
{
namespace toolbox
{
class scoped_layout
{
FCPPT_NONCOPYABLE(
	scoped_layout);
public:
	SGE_CEGUI_SYMBOL explicit
	scoped_layout(
		fcppt::filesystem::path const &,
		sge::charconv::system_ptr);

	SGE_CEGUI_SYMBOL ~scoped_layout();

	SGE_CEGUI_SYMBOL
	CEGUI::Window &
	window() const;
private:
	CEGUI::Window *const window_;
};
}
}
}

#endif
