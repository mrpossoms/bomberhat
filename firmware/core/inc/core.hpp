#pragma once
#include <ostream>

namespace bh
{

struct Error
{
	char* where = nullptr;
	int   line = -1;
	char* what = nullptr;
	char* why = nullptr;

	inline operator bool() const
	{
		return where && what && why;
	}


};

std::ostream& operator<<(std::ostream& os, const Error& e)
{
    return os << e.where << ":" << e.line << "| " << e.what << "; " << e.why;
}

} // namespace bh

#define BH_ERROR(what, why) (Error{(char*)__FILE__, __LINE__, (char*)what, (char*)why})
#define BH_OK() (Error{})