#include <sge/gui/invalidation.hpp>

sge::gui::invalidation::type const sge::gui::invalidation::all(
	sge::gui::invalidation::type(sge::gui::invalidation::position) | 
	sge::gui::invalidation::size);
