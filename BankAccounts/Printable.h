#pragma once
#include <iostream>


class Printable
{
	friend std::ostream& operator<<(std::ostream& os, const Printable& rhs);
public:
	Printable() = default;
	virtual ~Printable() = default;
	virtual void print(std::ostream& os) const = 0;
};

