#include <mutex>
#include <utility>
#include <cstdlib>

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
				static std::once_flag Flag;

				// Static Methods
				template <typename... Args>
				static inline Derived *CreateInstance(Args &&...args)
				{
					void *data = static_cast<void *>(GetData());
					std::call_once(Flag, [&](void (*destroyer)(void), Args &&...args) -> void
					{
						new (data) Derived(std::forward<Args>(args)...);
						std::atexit(destroyer);
					}, &Singleton::DestroyInstance, std::forward<Args>(args)...);
					return reinterpret_cast<Derived *>(data);
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

			// Static Attributes
			template <typename Derived>
			std::once_flag Singleton<Derived>::Flag;
		}
	}
}