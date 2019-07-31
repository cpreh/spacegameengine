//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_DIB_SECTION_HPP_INCLUDED
#define SGE_GDIFONT_DIB_SECTION_HPP_INCLUDED

#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/hbitmap_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gdifont
{

class dib_section
{
	FCPPT_NONCOPYABLE(
		dib_section
	);
public:
	dib_section(
		sge::gdifont::device_context const &,
		sge::image2d::dim const &
	);

	~dib_section();

	sge::image2d::view::object const
	view();

	sge::image2d::view::const_object const
	const_view() const;

	HBITMAP
	handle();
private:
	VOID *data_;

	sge::gdifont::hbitmap_unique_ptr const hbitmap_;

	BITMAP const bitmap_;
};

}
}

#endif
