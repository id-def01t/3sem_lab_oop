#ifndef APPLICATION_H
#define APPLICATION_H
#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

/*!

\brief класс оценок который в последующем переопределяется для каждого класса студента

*/

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

/*!

\brief класс оценок студента сеньора методы класса оценок переопределены

*/


class SeniorGrades : public Grades {
public:
  SeniorGrades();
  ~SeniorGrades(){}

  void read(ostream& ost, istream& ist) override;
  void print(ostream&) override;
};

/*!

\brief класс оценок младшекурсника методы класса оценок переопределены

*/


class JuniorGrades : public Grades {
public:
  JuniorGrades();

  void read(ostream& ost, istream& ist) override;
  void print(ostream&) override;
};


/*!

\brief класс оценок выпускника методы класса оценок переопределены

*/

class GraduateGrades : public Grades {
public:
  GraduateGrades();

  void read(ostream& ost, istream& ist) override;
  void print(ostream&) override;
};


/*!

\brief структура студента 

*/

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


/*!

\brief класс студента сеньора. Наследник класса студент с модификациями под задание

*/

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

/*!

\brief класс студента младшекурсника. Наследник класса студент с модификациями под задание

*/


class JuniorStudent : public Student {
public:
  JuniorStudent();
  JuniorStudent(string _name, int _group, int _chair);
  void print(ostream& ost) override;
};

/*!

\brief класс студента выпускника. Наследник класса студент с модификациями под задание

*/


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
/*!

\brief меню диалога ( прикладной программы )

*/
  void menu();
/*!

\brief меню добавления студента. вводим ключ проверяем на наличие в таблице. выделяем память. вызываем метод считывания данных. вызываем метод вставки в таблицу

*/
  void add_student();
/*!

\brief метод перевода студента на следующий курс с подтверждением

*/
  void transfer_student();
/*!

\brief метод для удаления студента из таблицы. ищем студента и удаляем информацию о нем

*/
  void remove_student();
/*!

\brief вывод всех студентов из таблицы

*/
  void print_students();
/*!

\brief метод поиска студента по таблице. используем метод find из map

*/
  void find_student();
private:
/*!

\brief маленькая функция для подтверждения перевода студента ( void transder_student(); )
*/
  bool read_bool();

  map<int, Student*> students;
};

#endif // APPLICATION_H
