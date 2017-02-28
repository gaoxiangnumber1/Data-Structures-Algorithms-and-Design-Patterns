#include "string_interview.h"

#include <vector>

using std::vector;

void PassByValue(String s)
{
	printf("passed_string = %s    ", s.c_str());
}
void PassByConstReference(const String &s)
{
	printf("\npassed_string = %s\n", s.c_str());
}
String ReturnByValue(const char *data)
{
	String ret(data);
	printf("ret = %s\t", ret.c_str());
	return ret;
}

int main()
{
	printf("----------Test Ctor----------\n");
	String s0;
	printf("s0 = %s, s0.Size() = %d\n", s0.c_str(), s0.Size());
	String s1("gao");
	printf("s1 = %s\n", s1.c_str());
	String s2 = "xiang"; // Equivalent to `String s3("xiang");`
	printf("s2 = %s\n", s2.c_str());
	String s3(s1);
	printf("s3 = %s\n", s3.c_str());
	String s4(std::move(String("number1")));
	printf("s4 = %s\n", s4.c_str());

	printf("----------Test Copy/Move Assignment Operator----------\n");
	// The following two assignment are errors if define move ctor/assignment_operator.
	// error: use of deleted function ‘String& String::operator=(const String&)’
	// note: ‘String& String::operator=(const String&)’ is implicitly declared as deleted
	// because ‘String’ declares a move constructor or move assignment operator
	s2 = s4;
	printf("s2 = %s\n", s2.c_str());
	s2 = s2;
	printf("s2 = %s\n", s2.c_str());
	s2 = std::move(s1);
	printf("s2 = %s, s1 = %s\n", s2.c_str(), s1.c_str());
	s2 = std::move(s2);
	printf("s2 = %s\n", s2.c_str());
	s1 = "xiang";
	printf("s1 = %s\n", s1.c_str());

	printf("----------Test as Parameter/Return type----------\n");
	PassByValue(s1);
	PassByConstReference(s1);
	String s5 = ReturnByValue("hello"); // TODO: Which ctor called?
	printf("s5 = %s\n", s5.c_str());
	s5 = ReturnByValue("world");
	printf("s5 = %s\n", s5.c_str());

	printf("----------Test as value_type of STL container----------\n");
	vector<String> vec;
	vec.push_back(s1);
	printf("vec[0] = %s\n", vec[0].c_str());
	vec.push_back(s2);
	printf("vec[0] = %s\tvec[1] = %s\n", vec[0].c_str(), vec[1].c_str());
	vec.push_back("gaoxiangnumber1");
	printf("vec[0] = %s\tvec[1] = %s\tvec[2] = %s\n", vec[0].c_str(), vec[1].c_str(), vec[2].c_str());

	printf("----------All Test Passed!----------\n");
}

/*
// When define `String &operator=(String&&)`
----------Test Ctor----------
Default_ctor	s0 = , s0.size() = 0
Const_char_*ctor_length	Const_char_*ctor	s1 = gao
Const_char_*ctor_length	Const_char_*ctor	s2 = xiang
Const_char_*ctor_length	Copy_ctor	s3 = gao
Const_char_*ctor_length	Const_char_*ctor	Move_ctor	Dtor	s4 = number1
----------Test Copy/Move Assignment Operator----------
Move_assignment_operator	s2 = gao, s1 = xiang
Move_assignment_operator	s2 = gao
Const_char_*ctor_length	Const_char_*ctor	Move_assignment_operator	Dtor	s1 = xiang
----------Test as Parameter/Return type----------
Const_char_*ctor_length	Copy_ctor	passed_string = xiang	Dtor
passed_string = xiang
Const_char_*ctor_length	Const_char_*ctor	ret = hello	s5 = hello
Const_char_*ctor_length	Const_char_*ctor	ret = world	Move_assignment_operator	Dtor	s5 = world
----------Test as value_type of STL container----------
Const_char_*ctor_length	Copy_ctor	vec[0] = xiang
Const_char_*ctor_length	Copy_ctor	Const_char_*ctor_length	Copy_ctor	Dtor	vec[0] = xiang	vec[1] = gao
Const_char_*ctor_length	Const_char_*ctor	Move_ctor	Const_char_*ctor_length	Copy_ctor	Const_char_*ctor_length	Copy_ctor	Dtor	Dtor	Dtor	vec[0] = xiang	vec[1] = gao	vec[2] = gaoxiangnumber1
----------All Test Passed!----------
Dtor	Dtor	Dtor	Dtor	Dtor	Dtor	Dtor	Dtor	Dtor
// When define `String &operator=(String)`
----------Test Ctor----------
Default_ctor    s0 = , s0.Size() = 0
Const_char_*ctor_length    Const_char_*ctor    s1 = gao
Const_char_*ctor_length    Const_char_*ctor    s2 = xiang
Const_char_*ctor_length    Copy_ctor    s3 = gao
Const_char_*ctor_length    Const_char_*ctor    Move_ctor    Dtor    s4 = number1
----------Test Copy/Move Assignment Operator----------
Const_char_*ctor_length    Copy_ctor    Copy-assignment operator    Dtor    s2 = number1
Const_char_*ctor_length    Copy_ctor    Copy-assignment operator    Dtor    s2 = number1
Move_ctor    Copy-assignment operator    Dtor    s2 = gao, s1 = (null)
Move_ctor    Copy-assignment operator    Dtor    s2 = gao
Const_char_*ctor_length    Const_char_*ctor    Copy-assignment operator    Dtor    s1 = xiang
----------Test as Parameter/Return type----------
Const_char_*ctor_length    Copy_ctor    passed_string = xiang    Dtor
passed_string = xiang
Const_char_*ctor_length    Const_char_*ctor    ret = hello	s5 = hello
Const_char_*ctor_length    Const_char_*ctor    ret = world	Copy-assignment operator    Dtor    s5 = world
----------Test as value_type of STL container----------
Const_char_*ctor_length    Copy_ctor    vec[0] = xiang
Const_char_*ctor_length    Copy_ctor    Const_char_*ctor_length    Copy_ctor    Dtor    vec[0] = xiang	vec[1] = gao
Const_char_*ctor_length    Const_char_*ctor    Move_ctor    Const_char_*ctor_length    Copy_ctor    Const_char_*ctor_length    Copy_ctor    Dtor    Dtor    Dtor    vec[0] = xiang	vec[1] = gao	vec[2] = gaoxiangnumber1
----------All Test Passed!----------
Dtor    Dtor    Dtor    Dtor    Dtor    Dtor    Dtor    Dtor    Dtor
*/
