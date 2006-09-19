#ifndef SGE_MUSIC_HPP_INCLUDED
#define SGE_MUSIC_HPP_INCLUDED

#include "../main/shared_ptr.hpp"

namespace sge
{

class music {
public:
	virtual ~music(){}
	virtual void play(bool loop = true) = 0;
	virtual void stop() = 0;
};

typedef shared_ptr<music> music_ptr;

}

#endif
