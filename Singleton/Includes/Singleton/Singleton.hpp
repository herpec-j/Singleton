#include <mutex>
#include <utility>
#include <cstdlib>

#include "Singleton/Private/SpinLock.hpp"

namespace AO
{
	namespace Singleton
	{
		inline namespace Version_1
		{
			template <class Derived>
			class Singleton
			{
			public:
				// Static Methods
				template <typename... Args>
				static inline Derived &GetInstance(Args &&...args)
				{
					return *GetInstancePointer(std::forward<Args>(args)...);
				}

				template <typename... Args>
				static inline Derived *GetInstancePointer(Args &&...args)
				{
					static Derived *instancePointer = CreateInstance(std::forward<Args>(args)...);
					return instancePointer;
				}

			protected:
				using Access = Singleton<Derived>;

				// Constructors
				Singleton(void) = default;

				Singleton(Singleton const &) = default;

				Singleton(Singleton &&) = default;

				// Assignment Operators
				Singleton &operator=(Singleton const &) = default;

				Singleton &operator=(Singleton &&) = default;

				// Destructor
				virtual ~Singleton(void) = default;

			private:
			  // Static Attributes
			  static Derived *InstancePointer;

			  static Private::SpinLock Lock;

				// Static Methods
				template <typename... Args>
				static inline Derived *CreateInstance(Args &&...args)
				{
				  if (InstancePointer == nullptr)
				    {
				      std::lock_guard<decltype(Lock)> lock(Lock);
				      if (InstancePointer == nullptr)
					{
					  void *data = static_cast<void *>(GetData());
					  new (data) Derived(std::forward<Args>(args)...);
					  InstancePointer = reinterpret_cast<Derived *>(data);
					  std::atexit(&Singleton::DestroyInstance);
					}
				    }
				  return InstancePointer;
				}

				static inline void DestroyInstance(void)
				{
					reinterpret_cast<Derived *>(GetData())->~Derived();
				}

				static inline unsigned char *GetData(void)
				{
					static unsigned char data[sizeof(Derived)];
					return data;
				}
			};

		  template <class Derived>
		  Derived *Singleton<Derived>::InstancePointer = nullptr;

		  template <class Derived>
		  Private::SpinLock Singleton<Derived>::Lock;
		}
	}
}
