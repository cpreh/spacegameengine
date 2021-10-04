//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED

#include <sge/libpng/png.hpp>
#include <sge/libpng/write_ptr_fwd.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge::libpng
{

class write_context
{
	FCPPT_NONMOVABLE(
		write_context
	);
public:
	write_context(
		sge::media::optional_name &&,
		std::ostream &,
		sge::libpng::write_ptr const &
	);

	~write_context();
private:
	sge::media::optional_name const name_;

	std::ostream &stream_;

	static
	void
	handle_write(
		png_structp,
		png_bytep,
		png_size_t
	);

	void
	handle_write_impl(
		png_bytep,
		png_size_t
	);

	static
	void
	handle_flush(
		png_structp
	);

	void
	handle_flush_impl();

	static
	write_context &
	get_instance(
		png_structp
	);
};

}

#endif
