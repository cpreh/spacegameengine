#ifndef SGE_CONSOLE_DETAIL_CURSOR_HPP_INCLUDED
#define SGE_CONSOLE_DETAIL_CURSOR_HPP_INCLUDED

#include <sge/string.hpp>
#include <sge/console/variable_map.hpp>
#include <sge/console/function_map.hpp>

namespace sge
{
namespace console
{
namespace detail
{
class cursor
{
	public:
	cursor();
	void reset();
	sge::string const edited(bool) const;
	sge::string const string() const;
	void string(sge::string const &);
	void erase_word();
	void erase_char();
	void left();
	void right();
	void to_start();
	void to_end();
	bool empty() const;
	void insert(char_type);
	bool at_start() const;
	void complete_word(
		variable_map const &,
		function_map const &);
	private:
	sge::string line_;
	sge::string::size_type pos_;
};
}
}
}

#endif
