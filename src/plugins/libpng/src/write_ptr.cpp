#include "../write_ptr.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>
#include <sge/cerr.hpp>

sge::libpng::write_ptr::write_ptr(
	png_structp const _ptr)
:
	ptr_(
		_ptr),
	info_(
		0)
{
	if (!ptr_)
		throw exception(SGE_TEXT("couldn't allocate png write structure"));

	info_ = 
		png_create_info_struct(
			ptr_);

	if (!info_)
		throw exception(SGE_TEXT("couldn't generate png info structure"));
}

sge::libpng::write_ptr::~write_ptr()
{
	if (ptr_)
		png_destroy_write_struct(
			&ptr_,
			&info_);
}

png_structp sge::libpng::write_ptr::ptr() const
{
	return ptr_;
}

png_infop sge::libpng::write_ptr::info() const
{
	return info_;
}
