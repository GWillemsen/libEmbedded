#ifndef CUSTOM_HELPER_H
#define CUSTOM_HELPER_H

template<typename TIncrementStruct>
class CustomType
{
private:
	int value;

public:
	CustomType(int val) : value(val)
	{
		TIncrementStruct::constructorCount++;
	}

	CustomType(const CustomType &other) : value(other.value)
	{
		TIncrementStruct::copyConstructorCount++;
	}

	CustomType(CustomType &&other) : value(other.value)
	{
		TIncrementStruct::moveConstructorCount++;
	}

	CustomType &operator=(const CustomType &other) noexcept
	{
		this->value = other.value;
		TIncrementStruct::assignmentCount++;
		return *this;
	}

	CustomType &operator=(CustomType &&other) noexcept
	{
		this->value = other.value;
		TIncrementStruct::moveAssignmentCount++;
		return *this;
	}

	~CustomType() noexcept
	{
		TIncrementStruct::destructorCount++;
	}

	int getValue() const noexcept
	{
		return this->value;
	}

	bool operator==(const CustomType& other) const noexcept {
		return this->value == other.value;
	}
	bool operator!=(const CustomType& other) const noexcept {
		return this->value != other.value;
	}
};

#endif // CUSTOM_HELPER_H
