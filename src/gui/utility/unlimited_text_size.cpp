#include "unlimited_text_size.hpp"
#include <sge/gui/dim.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/font/object.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/text_size.hpp>
#include <sge/structure_cast.hpp>
#include <limits>

sge::gui::dim const sge::gui::utility::unlimited_text_size(
	font::metrics_ptr const f,
	string const &t)
{
	return sge::structure_cast<dim>(
		font::object(f).text_size(
			t,
			font::dim(
				std::numeric_limits<font::unit>::max(),
				std::numeric_limits<font::unit>::max())).size());
}
