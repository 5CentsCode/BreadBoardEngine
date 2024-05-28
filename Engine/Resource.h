#pragma once
#include <string>
#include "Typedefs.h"

class Resource
{
public:
	Resource(Guid& guid, std::string& name)
	{
		m_guid = guid;
		m_name = name;
	}

	~Resource()
	{
	}

protected:

	Guid m_guid;
	std::string m_name;
};