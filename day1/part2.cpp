#include <iostream>
#include <fstream>
#include <tuple>
#include <array>
#include <string>

struct Result
{
  uint position;
  uint zeroHits;
};

Result rotate(uint position, std::string &rotation, uint ticks = 100)
{

  uint distance = std::stoi(rotation.substr(1));
  uint zeroHits = distance / ticks;
  distance %= ticks; // Remove full turns from total distance

  uint distanceToZero;
  uint nextPosition;

  if (rotation[0] == 'L') // Decrease
  {
    distanceToZero = position;

    if (distance > distanceToZero)
    {
      nextPosition = ticks - (distance - distanceToZero);
    }
    else
    {
      nextPosition = position - distance;
    }
  }
  else // Increase
  {
    distanceToZero = ticks - position;

    if (distance >= distanceToZero)
    {
      nextPosition = distance - distanceToZero;
    }
    else
    {
      nextPosition = position + distance;
    }
  }

  if (position != 0 && distance > distanceToZero)
  {
    zeroHits++;
  }

  return {nextPosition, zeroHits};
}

struct TestCase
{
  uint startPosition;
  std::string rotation;
  Result result;
};

void debug()
{
  // Sanity checks
  // uint ticks = 10;

  // struct TestCase testCases[] = {
  //     {5, "L5", {0, 0}},
  //     {5, "L6", {9, 1}},
  //     {5, "L16", {9, 2}},
  //     {5, "R5", {0, 0}},
  //     {5, "R6", {1, 1}},
  //     {5, "R16", {1, 2}},
  // };

  // Derived from examples given in problem description
  uint ticks = 100;

  struct TestCase testCases[] = {
      {50, "L68", {82, 1}},
      {82, "L30", {52, 0}},
      {52, "R48", {0, 0}},
      {0, "L5", {95, 0}},
      {95, "R60", {55, 1}},
      {55, "L55", {0, 0}},
      {0, "L1", {99, 0}},
      {99, "L99", {0, 0}},
      {0, "R14", {14, 0}},
      {14, "L82", {32, 1}},
  };

  for (TestCase &testCase : testCases)
  {
    Result result = rotate(testCase.startPosition, testCase.rotation, ticks);

    if (result.position != testCase.result.position)
    {
      std::cerr << "Expected position to be " << testCase.result.position << " but received " << result.position << " for rotation " << testCase.rotation << " from position " << testCase.startPosition << std::endl;
    }

    if (result.zeroHits != testCase.result.zeroHits)
    {
      std::cerr << "Expected zero hits to be " << testCase.result.zeroHits << " but received " << result.zeroHits << " for rotation " << testCase.rotation << " from position " << testCase.startPosition << std::endl;
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
    Result result = rotate(position, rotation);
    position = result.position;

    if (position == 0)
    {
      password++;
    }

    password += result.zeroHits;

    std::cout << position << std::endl;
  }

  std::cout << "Password: " << password << std::endl;
}
