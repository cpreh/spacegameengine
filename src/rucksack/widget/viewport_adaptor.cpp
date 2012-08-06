#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::rucksack::widget::viewport_adaptor::viewport_adaptor(
	sge::viewport::manager &_viewport,
	sge::renderer::device &_renderer)
:
	widget::base(
		widget::optional_parent()),
	renderer_(
		_renderer),
	viewport_connection_(
		_viewport.manage_callback(
			std::tr1::bind(
				&viewport_adaptor::manage_callback,
				this))),
	child_(
		0)
{
}
FCPPT_PP_POP_WARNING

void
sge::rucksack::widget::viewport_adaptor::size(
	sge::rucksack::dim const &_size)
{
	renderer_.onscreen_target().viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				renderer_.onscreen_target().viewport().get().pos(),
				fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim>(
					_size))));
}

void
sge::rucksack::widget::viewport_adaptor::position(
	sge::rucksack::vector const &_pos)
{
	renderer_.onscreen_target().viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				fcppt::math::vector::structure_cast<sge::renderer::pixel_rect::vector>(
					_pos),
				renderer_.onscreen_target().viewport().get().size())));
}

sge::rucksack::dim const
sge::rucksack::widget::viewport_adaptor::size() const
{
	return
		fcppt::math::dim::structure_cast<sge::rucksack::dim>(
			renderer_.onscreen_target().viewport().get().size());
}

sge::rucksack::vector const
sge::rucksack::widget::viewport_adaptor::position() const
{
	return
		fcppt::math::vector::structure_cast<sge::rucksack::vector>(
			renderer_.onscreen_target().viewport().get().pos());
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::viewport_adaptor::axis_policy() const
{
	// A dummy for now, until there's a use case
	return
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					sge::rucksack::scalar()),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					false)),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					sge::rucksack::scalar()),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					false)),
			sge::rucksack::aspect(
				1,
				1));
}

void
sge::rucksack::widget::viewport_adaptor::relayout()
{
	if(child_)
		child_->relayout();
}

void
sge::rucksack::widget::viewport_adaptor::child(
	widget::base &_child)
{
	if(child_)
		child_->parent(
			widget::optional_parent());

	child_ = &_child;
	child_->parent(
		widget::optional_parent(
			*this));
}


sge::rucksack::widget::viewport_adaptor::~viewport_adaptor()
{
	if(child_)
		child_->parent(
			widget::optional_parent());
}

void
sge::rucksack::widget::viewport_adaptor::manage_callback()
{
	sge::rucksack::dim const this_size =
		this->size();

	if(!child_)
		return;

	child_->position(
		sge::rucksack::vector::null());
	child_->size(
		this_size);
	child_->relayout();
}

void
sge::rucksack::widget::viewport_adaptor::child_destroyed(
	widget::base &_child)
{
	FCPPT_ASSERT_PRE(
		&_child == child_);

	child_ =
		0;
}
