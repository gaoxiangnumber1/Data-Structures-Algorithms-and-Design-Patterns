#ifndef CPPLIB_DATA_STRUCTURE_LINEAR_LIST_STRING_STRING_INTERVIEW
#define CPPLIB_DATA_STRUCTURE_LINEAR_LIST_STRING_STRING_INTERVIEW

#include <stdio.h>
#include <string.h> // str*()

#include <utility> // std::swap()

class String
{
public:
	String(): data_(new char[1]), length_(0) // Default ctor
	{
		*data_ = '\0';
		printf("Default_ctor    ");
	}
	String(const char *data, int length):
		data_(length > 0 ? new char[length + 1] : new char[1]),
		length_(length)
	{
		if(length_ > 0)
		{
			memcpy(data_, data, length_);
		}
		else
		{
			length_ = 0;
		}
		data_[length] = '\0';
		printf("Const_char_*ctor_length    ");
	}
	String(const char *data): String(data, static_cast<int>(strlen(data)))
	{
		printf("Const_char_*ctor    ");
	}
	String(const String &rhs): String(rhs.data_, rhs.length_) // Copy ctor
	{
		printf("Copy_ctor    ");
	}
	String(String &&rhs): data_(rhs.data_), length_(rhs.length_) // Move ctor
	{
		rhs.data_ = nullptr;
		rhs.length_ = 0;
		printf("Move_ctor    ");
	}

//	Traditional:
//	String &operator=(const String &rhs)
//	{
//		String temp(rhs);
//		Swap(temp);
//		return *this;
//	}
	// For `String s1 = "xiang";`: `String &operator=(String rhs)` or `(String &&rhs)`
	// are both okay. So we can only define one of them.
	// http://stackoverflow.com/questions/17961719/
	String &operator=(String rhs) // Copy-assignment operator
	{
		Swap(rhs);
		printf("Copy-assignment operator    ");
		return *this;
	}
//	String &operator=(String &&rhs) // Move-assignment operator
//	{
//		Swap(rhs);
//		printf("Move_assignment_operator    ");
//		return *this;
//	}
	void Swap(String &rhs)
	{
		std::swap(data_, rhs.data_);
		std::swap(length_, rhs.length_);
	}

	~String() // Dtor
	{
		printf("Dtor    ");
		delete [] data_;
	}

	int Size() const
	{
		return length_;
	}
	const char *c_str() const
	{
		return data_;
	}

private:
	char *data_;
	int length_;
};

#endif
