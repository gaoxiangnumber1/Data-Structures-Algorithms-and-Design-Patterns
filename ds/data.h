#ifndef CPPLIB_DS_DATA_H_
#define CPPLIB_DS_DATA_H_

#include <stdio.h>
#include <utility>

template<typename KeyType, typename ValueType>
struct Data
{
	Data(): key_(KeyType()), value_(ValueType()) {}
	Data(const KeyType &key, const ValueType &value): key_(key), value_(value) {}
	Data &operator=(Data rhs)
	{
		Swap(rhs);
		return *this;
	}

	void Swap(Data &rhs)
	{
		std::swap(key_, rhs.key_);
		std::swap(value_, rhs.value_);
	}

	KeyType key_;
	ValueType value_;
};
template<typename KeyType, typename ValueType>
bool operator>(const Data<KeyType, ValueType> &lhs, const Data<KeyType, ValueType> &rhs)
{
	return lhs.key_ > rhs.key_;
}
#endif // CPPLIB_DS_DATA_H_
