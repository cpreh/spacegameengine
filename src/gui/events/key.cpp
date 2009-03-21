#include <sge/gui/events/key.hpp>
#include <sge/input/classification.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/assert.hpp>

sge::gui::events::key::key(
	input::key_pair const &kp,
	input::modifier::states const &s,
	bool const repeated_) 
:
	kp(kp),
	s(s),
	repeated_(repeated_)
{
}

sge::input::key_pair const &
sge::gui::events::key::value() const
{
	return kp;
}

sge::input::modifier::states const &
sge::gui::events::key::modifiers() const
{
	return s;
}

bool
sge::gui::events::key::repeated() const
{
	return repeated_;
}
