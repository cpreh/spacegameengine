#ifndef SGE_GUI_IMPL_STYLE_SIMPLE_HPP_INCLUDED
#define SGE_GUI_IMPL_STYLE_SIMPLE_HPP_INCLUDED

#include <sge/gui/fill_color_fwd.hpp>
#include <sge/gui/fill_level_fwd.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace impl
{
namespace style
{

class simple
:
	public sge::gui::style::base
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	simple();

	~simple()
	override;
private:
	sge::rucksack::dim const
	button_spacing() const
	override;

	void
	draw_button(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	void
	draw_bar(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::axis,
		sge::gui::fill_level,
		sge::gui::fill_color const &
	) const
	override;

	sge::rucksack::padding const
	frame_padding() const
	override;

	void
	draw_frame(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::padding
	) const
	override;

	sge::rucksack::dim const
	edit_spacing() const
	override;

	void
	draw_edit(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::rucksack::dim const
	image_spacing() const
	override;

	void
	draw_image(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::rucksack::dim const
	text_spacing() const
	override;

	void
	draw_text(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::gui::text_color
	text_color() const
	override;

	sge::rucksack::dim const
	spacing() const;
};

}
}
}
}

#endif
