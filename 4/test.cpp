#include "pch.h"
#include "gtest/gtest.h"
#include "../ConsoleApplication3/application.h"
#include "../ConsoleApplication3/application.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(AppConstructor, Constructor) {
	SUCCEED(Application());
}

TEST(StudentConstructor, Constructor) {
	SUCCEED(Student("Max", 1, 123));
}

TEST(SeniorStudentConstructor, Constructor) {
	SUCCEED(SeniorStudent("Zheka", 3, 63, "MeowPHI", "MEPH"));
}

TEST(JuniorStudentConstructor, Constructor) {
	SUCCEED(JuniorStudent("Egor", 4, 1234));
}

TEST(GraduateStudentConstructor, Constructor) {
	SUCCEED(GraduateStudent("Pasha", 5, 987, "MeoPHI", "MEPHI"));
}

TEST(GraduateStudentDestructor, Destructor) {
	SUCCEED(~GraduateStudent());
}

TEST(JuniorStudentDestructor, Destructor) {
	SUCCEED(~JuniorStudent());
}

TEST(SeniorStudentDestructor, Destructor) {
	SUCCEED(~SeniorStudent());
}

TEST(SeniorGetters, Getters)
{
	SUCCEED(SeniorStudent("Zheka", 3, 63, "MeowPHI", "MEPH"));
	SeniorStudent set("Zheka", 3, 63, "MeowPHI", "MEPH");
	ASSERT_EQ("MeowPHI", set.work());
	ASSERT_EQ("MEPH", set.place());
	ASSERT_EQ("Zheka", set.name());
	ASSERT_EQ(3, set.group());
	ASSERT_EQ(63, set.chair());
}

TEST(JuniorGetters, Getters)
{
	SUCCEED(JuniorStudent("Egor", 4, 1234));
	JuniorStudent jst("Egor", 4, 1234);
	ASSERT_EQ("Egor", jst.name());
	ASSERT_EQ(4, jst.group());
	ASSERT_EQ(1234, jst.chair());
}

TEST(StudentGetters, Getters)
{
	SUCCEED(Student("Max", 1, 123));
	Student st("Max", 1, 123);
	ASSERT_EQ("Max", st.name());
	ASSERT_EQ(1, st.group());
	ASSERT_EQ(123, st.chair());
}

TEST(GraduateStudentGetters, Getters)
{
	SUCCEED(GraduateStudent("Pasha", 5, 987, "MeoPHI", "MEPHI"));
	GraduateStudent gst("Pasha", 5, 987, "MeoPHI", "MEPHI");
	ASSERT_EQ("Pasha", gst.name());
	ASSERT_EQ(5, gst.group());
	ASSERT_EQ(987, gst.chair());
}
