#pragma once

#include <functional>
#include <vector>
#include <string>

using IPValue = std::vector<std::string>;
using IPList = std::vector<IPValue>;

IPList filter(const IPList& ip_pool, std::function<bool(const IPValue&)> filterFunc)
{
	IPList result;
	for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
	{
		if (filterFunc(*ip))
		{
			result.emplace_back(*ip);
		}
	}
	return result;
}