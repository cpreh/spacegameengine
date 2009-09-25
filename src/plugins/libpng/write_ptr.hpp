#ifndef SGE_LIBPNG_WRITE_PTR_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_PTR_HPP_INCLUDED

#include <png.h>

namespace sge
{
namespace libpng
{
class write_ptr
{
public:
	write_ptr(
		png_structp);
	~write_ptr();
	png_structp ptr() const;
	png_infop info() const;
private:
	png_structp ptr_;
	png_infop info_;
};
}
}

#endif
