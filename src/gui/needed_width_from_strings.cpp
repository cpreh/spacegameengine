#include <sge/gui/needed_width.hpp>
#include <sge/gui/needed_width_from_strings.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::gui::needed_width const
sge::gui::needed_width_from_strings(
	sge::font::object &_font,
	sge::gui::string_container const &_strings
)
{
	return
		fcppt::algorithm::fold(
			_strings,
			sge::gui::needed_width(
				0
			),
			[
				&_font
			](
				sge::font::string const &_text,
				sge::gui::needed_width const _prev_width
			)
			{
				return
					sge::gui::needed_width(
						std::max(
							_prev_width.get(),
							_font.create_text(
								_text,
								sge::font::text_parameters(
									sge::font::align_h::variant{
										sge::font::align_h::left()
									}
								).flags(
									sge::font::flags_field{
										sge::font::flags::no_multi_line
									}
								)
							)->logical_size().w()
						)
					);
			}
		);
}
