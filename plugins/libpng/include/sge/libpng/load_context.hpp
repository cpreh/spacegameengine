//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED

#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr_fwd.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

class load_context
{
	FCPPT_NONMOVABLE(
		load_context
	);
public:
	load_context(
		std::istream &,
		sge::media::optional_name &&,
		sge::libpng::read_ptr const &
	);

	~load_context();
private:
	std::istream &stream_;

	sge::media::optional_name const name_;

	static
	void
	handle_read(
		png_structp,
		png_bytep data,
		png_size_t length
	);

	void
	handle_read_impl(
		png_bytep data,
		png_size_t length
	);
};

}
}

#endif
