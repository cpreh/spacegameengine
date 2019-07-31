//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_SCOPED_SELECT_HPP_INCLUDED
#define SGE_GDIFONT_SCOPED_SELECT_HPP_INCLUDED

#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gdifont
{

class scoped_select
{
	FCPPT_NONCOPYABLE(
		scoped_select
	);
public:
	scoped_select(
		sge::gdifont::device_context const &,
		HGDIOBJ
	);

	~scoped_select();
private:
	sge::gdifont::device_context const &device_context_;

	HGDIOBJ const previous_;
};

}
}

#endif
