//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_WRITE_PTR_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_PTR_HPP_INCLUDED

#include <sge/libpng/error_context_fwd.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/write_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace libpng
{

class write_ptr
{
	FCPPT_NONCOPYABLE(
		write_ptr
	);
public:
	explicit
	write_ptr(
		sge::libpng::error_context &
	);

	~write_ptr();

	png_structp
	ptr() const;
private:
	png_structp ptr_;
};

}
}

#endif
