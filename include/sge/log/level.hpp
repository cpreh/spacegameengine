#ifndef SGE_LOG_LEVEL_HPP_INCLUDED
#define SGE_LOG_LEVEL_HPP_INCLUDED

namespace sge
{
namespace log
{

namespace level
{
enum type {
	debug,
	info,
	warn,
	error,
	off,
	size = off
};
}

}
}

#endif
