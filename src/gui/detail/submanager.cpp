#include <sge/gui/detail/submanager.hpp>

sge::gui::detail::submanager::submanager()
{}

void sge::gui::detail::submanager::resize(widget &,dim const &) {}
void sge::gui::detail::submanager::reposition(widget &,point const &) {}
void sge::gui::detail::submanager::update() {}
void sge::gui::detail::submanager::add(widget &) {}
void sge::gui::detail::submanager::activation(widget &,activation_state::type) {}
void sge::gui::detail::submanager::remove(widget &) {}
void sge::gui::detail::submanager::dirty(
	widget &,
	rect const &) {}
void sge::gui::detail::submanager::invalidate(
	widget &) {}
sge::gui::detail::submanager::~submanager() {}
