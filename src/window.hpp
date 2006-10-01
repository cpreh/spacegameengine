#ifndef SGE_WINDOW_HPP_INCLUDED
#define SGE_WINDOW_HPP_INCLUDED

#include "./types.hpp"
#include "./shared_ptr.hpp"
#include "./math/dim.hpp"
#include "./shared_ptr.hpp"

namespace sge
{

class window {
public:
	typedef unsigned size_type;
	typedef basic_dim<size_type> window_size;

	virtual void title(const std::string& title) = 0;
	virtual window_size size() const = 0;
	virtual void size(window_size newsize) = 0;
	virtual const std::string& title() const = 0;
	virtual ~window(){}
};

typedef shared_ptr<window> window_ptr;

}

#endif
