//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_SCOPED_LOCALE_HPP_INCLUDED
#define SGE_X11INPUT_XIM_SCOPED_LOCALE_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace xim
{

class scoped_locale
{
	FCPPT_NONCOPYABLE(
		scoped_locale
	);
public:
	explicit
	scoped_locale(
		std::string const &
	);

	~scoped_locale();
private:
	std::string const old_locale_;
};

}
}
}

#endif
