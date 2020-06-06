//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <sge/renderer/display_mode/dpi.hpp>
#include <sge/renderer/display_mode/dpi_unit.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/to_dpi.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/map.hpp>


sge::renderer::display_mode::dpi
sge::renderer::display_mode::to_dpi(
	sge::renderer::display_mode::optional_object const &_opt_mode
)
{
	return
		fcppt::optional::from(
			fcppt::optional::bind(
				_opt_mode,
				[](
					sge::renderer::display_mode::object const &_mode
				)
				{
					return
						fcppt::optional::bind(
							_mode.dimensions(),
							[
								&_mode
							](
								sge::renderer::display_mode::dimensions const &_dim
							)
							{
								return
									fcppt::optional::map(
										_mode.pixel_size().get()
										/
										fcppt::math::dim::structure_cast<
											sge::renderer::display_mode::dpi,
											fcppt::cast::int_to_float_fun
										>(
											_dim.get()
										),
										[](
											sge::renderer::display_mode::dpi const &_value
										)
										-> sge::renderer::display_mode::dpi
										{
											return
												_value
												*
												fcppt::literal<
													sge::renderer::display_mode::dpi_unit
												>(
													25.4
												);
										}
									);
							}
						);
				}
			),
			[]{
				constexpr auto const default_dpi{
					fcppt::literal<
						sge::renderer::display_mode::dpi_unit
					>(
						96.f
					)
				};

				return
					fcppt::math::dim::fill<
						sge::renderer::display_mode::dpi
					>(
						default_dpi
					);
			}
		);
}
