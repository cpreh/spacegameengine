#ifndef SGE_GUI_BACKGROUND_BASE_HPP_INCLUDED
#define SGE_GUI_BACKGROUND_BASE_HPP_INCLUDED

#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace background
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	explicit
	base(
		sge::gui::main_area::base &
	);
public:
	virtual
	~base() = 0;

	void
	draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	);

	sge::gui::widget::base &
	widget();
private:
	virtual
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) = 0;

	sge::gui::main_area::base &main_area_;
};

}
}
}

#endif
