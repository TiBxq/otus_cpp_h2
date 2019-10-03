#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

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

void print(const IPList& ip_pool)
{
	for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
	{
		for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
		{
			if (ip_part != ip->cbegin())
			{
				std::cout << ".";
			}
			std::cout << *ip_part;
		}
		std::cout << std::endl;
	}
}

int main(/*int argc, char const *argv[]*/)
{
    try
    {
        IPList ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            IPValue v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // reverse lexicographically sort
		std::sort(ip_pool.begin(), ip_pool.end(), [](const IPValue& lhs, const IPValue& rhs)
		{
			for (unsigned i = 0; i < lhs.size(); ++i)
			{
				int lhsVal = atoi(lhs[i].c_str());
				int rhsVal = atoi(rhs[i].c_str());
				if (lhsVal > rhsVal)
				{
					return true;
				}
				else if (lhsVal < rhsVal)
				{
					return false;
				}
			}
			return false;
		});

		print(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first byte and output
		{
			int byte1 = 1;
			auto result = filter(ip_pool, [byte1](const IPValue& ip)
			{
				return atoi(ip[0].c_str()) == byte1;
			});
			print(result);
		}

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first and second bytes and output
		{
			int byte1 = 46;
			int byte2 = 70;
			auto result = filter(ip_pool, [byte1, byte2](const IPValue& ip)
			{
				return atoi(ip[0].c_str()) == byte1 && atoi(ip[1].c_str()) == byte2;
			});
			print(result);
		}

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // filter by any byte and output
		{
			int byte = 46;
			auto result = filter(ip_pool, [byte](const IPValue& ip)
			{
				return std::any_of(ip.begin(), ip.end(), [byte](const std::string& ip_part)
				{
					return atoi(ip_part.c_str()) == byte;
				});
			});
			print(result);
		}

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
