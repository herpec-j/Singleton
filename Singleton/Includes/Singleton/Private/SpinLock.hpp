#pragma once

#include <atomic>

namespace AO
{
  namespace Singleton
  {
    inline namespace Version_1
    {
      namespace Private
      {
	class SpinLock final
	{
	public:
	  // Constructors
	  inline SpinLock(void)
	    : atomicLock(false)
	  {
	    return;
	  }

	  SpinLock(SpinLock const &) = default;

	  SpinLock(SpinLock &&) = default;

	  // Assignment Operators
	  SpinLock &operator=(SpinLock const &) = default;

	  SpinLock &operator=(SpinLock &&) = default;

	  // Destructor
	  ~SpinLock(void) = default;

	  // Methods
	  inline void lock(void)
	  {
	    while (atomicLock.exchange(true));
	  }

	  inline void unlock(void)
	  {
	    atomicLock = false;
	  }
	  
	  inline bool isLocked(void) const
	  {
	    return atomicLock;
	  }

	private:
	  // Attributes
	  std::atomic_bool atomicLock;
	};
      }
    }
  }
}
