//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/impl/draw_image.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/image.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/rucksack/access_axis.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::gui::widget::image::image(
	sge::gui::style::base const &_style,
	sge::texture::part const &_texture
)
:
	style_(
		_style
	),
	texture_(
		_texture
	),
	layout_{
		sge::rucksack::make_axis_policy(
			sge::rucksack::axis_policy_function{
				[
					this
				](
					sge::rucksack::axis const _axis
				)
				{
					return
						sge::rucksack::axis_policy{
							sge::rucksack::preferred_size{
								fcppt::cast::size<
									sge::rucksack::scalar
								>(
									fcppt::cast::to_signed(
										sge::rucksack::access_axis(
											this->texture_.size(),
											_axis
										)
									)
								)
								+
								sge::rucksack::access_axis(
									this->style_.image_spacing(),
									_axis
								)
							}
						};
				}
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::gui::widget::image::~image()
{
}

sge::rucksack::widget::base &
sge::gui::widget::image::layout()
{
	return
		layout_;
}

void
sge::gui::widget::image::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_image(
		_renderer,
		_context,
		this->layout().area()
	);

	_renderer.draw_image(
		_context,
		texture_,
		layout_.position()
		+
		(
			(
				layout_.size()
				-
				fcppt::math::dim::structure_cast<
					sge::rucksack::dim,
					fcppt::cast::size_fun
				>(
					fcppt::math::dim::to_signed(
						texture_.area().size()
					)
				)
			)
			/
			fcppt::literal<
				sge::rucksack::scalar
			>(
				2
			)
		).get_unsafe()
	);
}
