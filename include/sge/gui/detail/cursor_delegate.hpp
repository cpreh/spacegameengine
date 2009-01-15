#ifndef SGE_GUI_DETAIL_CURSOR_DELEGATE_HPP_INCLUDED
#define SGE_GUI_DETAIL_CURSOR_DELEGATE_HPP_INCLUDED

#include "../../string.hpp"
#include "../../input/key_pair_fwd.hpp"

namespace sge
{
namespace gui
{
namespace detail
{
class cursor_delegate
{
	public:
	cursor_delegate(string &);
	string::size_type pos() const { return pos_; }
	void key_callback(input::key_pair const &);
	private:
	string &text;
	string::size_type pos_;
};
}
}
}

#endif
