//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_BACKGROUND_BASE_HPP_INCLUDED
#define SGE_GUI_BACKGROUND_BASE_HPP_INCLUDED

#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace gui
{
namespace background
{

class base
{
	FCPPT_NONMOVABLE(
		base
	);
protected:
	explicit
	base(
		sge::gui::main_area::reference
	);
public:
	virtual
	~base();

	void
	draw(
		sge::gui::renderer::base &, // NOLINT(google-runtime-references)
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	sge::gui::widget::base &
	widget();
private:
	virtual
	void
	on_draw(
		sge::gui::renderer::base &, // NOLINT(google-runtime-references)
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::rucksack::rect const &
	) = 0;

	sge::gui::main_area::reference const main_area_;
};

}
}
}

#endif
