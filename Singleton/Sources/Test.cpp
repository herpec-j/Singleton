#include <iostream>
#include <queue>
#include <stack>
#include <cassert>

#include "Singleton/Singleton.hpp"

static char const *__success = "Success!";
static std::queue<char> __letters;
static std::stack<std::size_t> __numbers;

template <std::size_t N>
class Class final : public AO::Singleton::Singleton < Class<N> >
{
private:
	friend typename Class::Access;

	// Constructors
	Class(void)
	{
		initialize();
		__numbers.push(N);
		__letters.push(*__success++);
	}

	Class(Class const &) = default;

	Class(Class &&) = default;

	// Assignment Operators
	Class &operator=(Class const &) = default;

	Class &operator=(Class &&) = default;

	// Destructor
	~Class(void)
	{
		assert(__numbers.top() == N && "Invalid destruction order");
		__numbers.pop();
		std::cout << __letters.front();
		__letters.pop();
		if (__letters.empty())
		{
			std::cout << std::endl;
		}
	}
	
	// Methods
	void initialize(void) const;
};

template <>
void Class<1>::initialize(void) const
{
	Class<4>::GetInstance();
	Class<6>::GetInstance();
}

template <>
void Class<2>::initialize(void) const
{
	return;
}

template <>
void Class<3>::initialize(void) const
{
	Class<1>::GetInstance();
}

template <>
void Class<4>::initialize(void) const
{
	Class<2>::GetInstance();
}

template <>
void Class<5>::initialize(void) const
{
	return;
}

template <>
void Class<6>::initialize(void) const
{
	return;
}

template <>
void Class<7>::initialize(void) const
{
	Class<8>::GetInstance();
}

template <>
void Class<8>::initialize(void) const
{
	Class<6>::GetInstance();
	Class<5>::GetInstance();
	Class<3>::GetInstance();
}

int main(int argc, char *argv[])
{
  std::cout << Class<1>::GetInstancePointer() << std::endl;
  std::cout << Class<2>::GetInstancePointer() << std::endl;
  std::cout << Class<3>::GetInstancePointer() << std::endl;
  std::cout << Class<4>::GetInstancePointer() << std::endl;
  std::cout << Class<5>::GetInstancePointer() << std::endl;
  std::cout << Class<6>::GetInstancePointer() << std::endl;
  std::cout << Class<7>::GetInstancePointer() << std::endl;
  std::cout << Class<8>::GetInstancePointer() << std::endl;
	return EXIT_SUCCESS;
}
