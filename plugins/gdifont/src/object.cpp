//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/gdifont/create_font.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/make_metrics.hpp>
#include <sge/gdifont/object.hpp>
#include <sge/gdifont/text.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::gdifont::object::object(
	sge::gdifont::device_context const &_device_context,
	sge::font::parameters const &_parameters
)
:
	sge::font::object(),
	device_context_(
		_device_context
	),
	font_(
		sge::gdifont::create_font(
			_parameters
		)
	),
	metrics_(
		sge::gdifont::make_metrics(
			device_context_,
			font_.get_pointer()
		)
	)
{
}

sge::gdifont::object::~object()
{
}

sge::font::text_unique_ptr
sge::gdifont::object::create_text(
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::font::text
		>(
			fcppt::make_unique_ptr<
				sge::gdifont::text
			>(
				device_context_,
				font_.get_pointer(),
				_string,
				_text_parameters
			)
		);
}

sge::image::color::optional_format
sge::gdifont::object::preferred_color_format() const
{
	return
		sge::image::color::optional_format(
			sge::image::color::format::a8
		);
}

sge::font::metrics
sge::gdifont::object::metrics() const
{
	return
		metrics_;
}
