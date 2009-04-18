#include <sge/gui/detail/submanager.hpp>

sge::gui::detail::submanager::submanager()
{}

void sge::gui::detail::submanager::update() {}
void sge::gui::detail::submanager::add(widgets::base &) {}
void sge::gui::detail::submanager::activation(widgets::base &,activation_state::type) {}
void sge::gui::detail::submanager::remove(widgets::base &) {}
void sge::gui::detail::submanager::dirty(
	widgets::base &,
	rect const &) {}
void sge::gui::detail::submanager::resize(
	widgets::base &,
	dim const &) {}
void sge::gui::detail::submanager::reposition(
	widgets::base &,
	point const &) {}
void sge::gui::detail::submanager::invalidate(
	widgets::base &,
	invalidation::type const &) {}
void sge::gui::detail::submanager::z(
	widgets::base &,
	depth_type) {}
sge::gui::detail::submanager::~submanager() {}
