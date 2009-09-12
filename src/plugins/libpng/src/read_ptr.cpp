#include "../read_ptr.hpp"
#include "../general_error.hpp"
#include <sge/text.hpp>
#include <sge/cerr.hpp>

sge::libpng::read_ptr::read_ptr(
	png_structp const _ptr)
:
	ptr_(
		_ptr),
	info_(
		0),
	end_info_(
		0)
{
	if (!ptr_)
		throw general_error(SGE_TEXT("couldn't allocate png read structure"));

	info_ = 
		png_create_info_struct(
			ptr_);

	if (!info_)
		throw general_error(SGE_TEXT("couldn't generate png info structure"));

	end_info_ = 
		png_create_info_struct(
			ptr_);

	if (!info_)
		throw general_error(SGE_TEXT("couldn't generate png info structure"));
}

sge::libpng::read_ptr::~read_ptr()
{
	if (ptr_)
		png_destroy_read_struct(
			&ptr_,
			&info_,
			&end_info_);
}

png_structp sge::libpng::read_ptr::ptr() const
{
	return ptr_;
}

png_infop sge::libpng::read_ptr::info() const
{
	return info_;
}

png_infop sge::libpng::read_ptr::end_info() const
{
	return end_info_;
}
