#ifndef SGE_LIBPNG_READ_PTR_HPP_INCLUDED
#define SGE_LIBPNG_READ_PTR_HPP_INCLUDED

#include <png.h>

namespace sge
{
namespace libpng
{
class read_ptr
{
public:
	read_ptr(
		png_structp);
	~read_ptr();
	png_structp ptr() const;
	png_infop info() const;
	png_infop end_info() const;
private:
	png_structp ptr_;
	png_infop info_,end_info_;
};
}
}

#endif
