#ifndef TEMPLATE_POINTER_H
#define TEMPLATE_POINTER_H

template<class T>
class Pointer
{
	T* pointer;

public:

	Pointer()
		:pointer(nullptr)
	{
	}

	Pointer(T* address)
		:pointer(address)
	{
	}

	~Pointer()
	{
		delete pointer;
	}

	Pointer(const Pointer& obj)
		:pointer(obj.pointer)
	{
	}

	Pointer(Pointer&& obj) noexcept
		:pointer(obj.pointer)
	{
		obj.pointer = nullptr;
	}

	Pointer& operator = (const Pointer& obj)
	{
		if (this == &obj)
			return *this;

		pointer = nullptr;

		pointer = obj.pointer;

		return *this;
	}

	Pointer& operator = (Pointer&& obj) noexcept
	{
		if (this == &obj)
			return *this;

		pointer = nullptr;

		pointer = obj.pointer;

		obj.pointer = nullptr;

		return *this;
	}

	T& operator* ()
	{
		return *pointer;
	}

	T* operator-> ()
	{
		return pointer;
	}
};

#endif