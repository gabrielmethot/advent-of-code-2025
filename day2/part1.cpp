#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<std::string> split(const std::string &value, const char delimiter)
{
  std::vector<std::string> tokens;
  std::size_t start = 0UL;
  std::size_t end = value.find(delimiter, start);

  while (end != std::string::npos)
  {
    std::string token = value.substr(start, end - start);
    tokens.push_back(token);
    start = end + 1;
    end = value.find(delimiter, start);
  }

  std::string token = value.substr(start);
  tokens.push_back(token);

  return tokens;
}

std::tuple<std::string, std::string> parseRange(const std::string &value)
{
  std::vector<std::string> tokens = split(value, '-');
  return std::make_tuple(tokens[0], tokens[1]);
};

bool isInvalidId(const std::string &id)
{
  size_t len = id.length();

  if (len % 2 != 0)
  {
    return false;
  }

  return id.substr(0UL, len / 2) == id.substr(len / 2, len);
}

int main()
{
  constexpr const char *path = "day2/input.txt";
  std::ifstream fileStream{path};

  if (!fileStream)
  {
    std::cerr << "Error opening file " << path << std::endl;
    return 1;
  }

  std::string line;

  if (std::getline(fileStream, line))
  {
    std::vector<std::string> strRanges = split(line, ',');
    std::vector<std::tuple<std::string, std::string>> ranges;
    std::transform(strRanges.begin(), strRanges.end(), std::back_inserter(ranges), parseRange);

    unsigned long invalidIdsSum = 0;

    for (const auto &range : ranges)
    {
      const std::string &start = std::get<0>(range);
      const std::string &end = std::get<1>(range);

      for (unsigned long id = std::stoul(start); id < std::stoul(end); id++)
      {
        const std::string strId = std::to_string(id);

        if (isInvalidId(strId))
        {
          invalidIdsSum += id;
        }
      }
    }

    std::cout << "Sum of invalid IDs: " << invalidIdsSum << std::endl;
  }

  return 0;
}
