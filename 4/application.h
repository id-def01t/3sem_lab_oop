#ifndef APPLICATION_H
#define APPLICATION_H
#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Grades {
protected:
  vector<int> m_grades;
public:
  Grades();
  virtual ~Grades() {}

  void read(istream& ist);
  virtual void read(ostream& ost, istream& ist) = 0;
  virtual void print(ostream&) = 0;
};

class SeniorGrades : public Grades {
public:
  SeniorGrades();
  ~SeniorGrades(){}

  void read(ostream& ost, istream& ist) override;
  void print(ostream&) override;
};

class JuniorGrades : public Grades {
public:
  JuniorGrades();

  void read(ostream& ost, istream& ist) override;
  void print(ostream&) override;
};

class GraduateGrades : public Grades {
public:
  GraduateGrades();

  void read(ostream& ost, istream& ist) override;
  void print(ostream&) override;
};

struct Student {
protected:
  string m_name;
  int m_group;
  int m_chair;
  Grades* m_grades;
public:
  virtual ~Student() {}
  Student();
  Student(string name, int group, int chair);

  void read_grades(ostream& ost, istream& ist);
  void read_grades(istream& ist);

  void group(int _group);

  string name() const;
  int group() const;
  int chair() const;
  Grades* grades() const;

  virtual void print(ostream& ost);
  virtual void read(ostream& ost, istream& ist);
  virtual void read_transfer(ostream& ost, istream& ist);
};

class SeniorStudent : public Student {
protected:
  string m_research_work;
  string m_research_place;
public:
  SeniorStudent(string name, int group, int chair,
              string research_work, string research_place);

  string work();
  string place();

  void print(ostream& ost) override;
  void read(ostream& ost, istream& ist) override;
  void read_transfer(ostream& ost, istream& ist) override;
};

class JuniorStudent : public Student {
public:
  JuniorStudent();
  JuniorStudent(string _name, int _group, int _chair);
  void print(ostream& ost) override;
};

class GraduateStudent : public Student {
protected:
  string m_graduate_work;
  string m_graduate_place;
public:
  GraduateStudent(string name, int group, int chair,
              string graduate_work, string graduate_place);

  void print(ostream& ost) override;
  void read(ostream& ost, istream& ist) override;
  void read_transfer(ostream& ost, istream& ist) override;
};

class Application {
public:
  Application();
  ~Application();
  void menu();
  void add_student();
  void transfer_student();
  void remove_student();
  void print_students();
  void find_student();
private:
  bool read_bool();

  map<int, Student*> students;
};

#endif // APPLICATION_H
