#include <iostream>
#include <fstream>
#include <tuple>
#include <array>
#include <string>

uint rotate(uint position, std::string &rotation, uint ticks = 100)
{

  uint distance = std::stoi(rotation.substr(1));
  distance %= ticks; // Remove full turns from total distance

  uint distanceToZero;

  if (rotation[0] == 'L') // Decrease
  {
    distanceToZero = position;

    if (distance > distanceToZero)
    {
      return ticks - (distance - distanceToZero);
    }
    else
    {
      return position - distance;
    }
  }
  else // Increase
  {
    distanceToZero = ticks - position;

    if (distance >= distanceToZero)
    {
      return distance - distanceToZero;
    }
    else
    {
      return position + distance;
    }
  }
}

struct TestCase
{
  uint startPosition;
  std::string rotation;
  uint endPosition;
};

void debug()
{
  // Sanity checks
  // uint ticks = 10;

  // struct TestCase testCases[] = {
  //     {5, "L5", 0},
  //     {5, "L6", 9},
  //     {5, "L16", 9},
  //     {5, "R5", 0},
  //     {5, "R6", 1},
  //     {5, "R16", 1},
  // };

  // Derived from examples given in problem description
  uint ticks = 100;

  struct TestCase testCases[] = {
      {50, "L68", 82},
      {82, "L30", 52},
      {52, "R48", 0},
      {0, "L5", 95},
      {95, "R60", 55},
      {55, "L55", 0},
      {0, "L1", 99},
      {99, "L99", 0},
      {0, "R14", 14},
      {14, "L82", 32},
  };

  for (TestCase &testCase : testCases)
  {
    uint endPosition = rotate(testCase.startPosition, testCase.rotation, ticks);

    if (endPosition != testCase.endPosition)
    {
      std::cerr << "Expected position to be " << testCase.endPosition << " but received " << endPosition << " for rotation " << testCase.rotation << " from position " << testCase.startPosition << std::endl;
    }
  }
}

int main()
{
  // Uncomment to debug
  // debug();
  // return 0;

  const char *path = "day1/input.txt";
  std::ifstream fileStream{path};

  if (!fileStream)
  {
    std::cerr << "Error opening file " << path << std::endl;
    return 1;
  }

  uint position = 50;
  uint password = 0;
  std::string rotation{};

  while (std::getline(fileStream, rotation))
  {
    position = rotate(position, rotation);

    if (position == 0)
    {
      password++;
    }

    std::cout << position << std::endl;
  }

  std::cout << "Password: " << password << std::endl;
}
