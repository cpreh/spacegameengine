//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED

#include <sge/cegui/system_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


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
		scoped_layout
	);
public:
	SGE_CEGUI_DETAIL_SYMBOL
	scoped_layout(
		sge::cegui::system &,
		boost::filesystem::path const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	~scoped_layout();

	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::Window &
	window() const;
private:
	sge::cegui::system &system_;

	CEGUI::Window *const window_;
};

}
}
}

#endif
