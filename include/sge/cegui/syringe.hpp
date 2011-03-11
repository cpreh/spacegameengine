#ifndef SGE_CEGUI_SYRINGE_HPP_INCLUDED
#define SGE_CEGUI_SYRINGE_HPP_INCLUDED

#include <sge/cegui/system_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace cegui
{
class syringe
{
FCPPT_NONCOPYABLE(
	syringe);
public:
	SGE_CEGUI_SYMBOL explicit
	syringe(
		system &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::keyboard::key_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::keyboard::key_repeat_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::keyboard::char_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::cursor::button_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::cursor::move_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::cursor::position const &);
private:
	system &system_;
	sge::charconv::system_ptr charconv_system_;
};
}
}

#endif
