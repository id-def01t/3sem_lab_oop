#include "application.h"

Application::Application() {
}

Application::~Application() {
  for (auto it = students.begin(); it != students.end(); ++it) {
    delete (it->second);
  }
}

void Application::menu() {
  while (true) {
    int menu_point;
    cout << "enter: " << endl
         << "\t0 - exit" << endl
         << "\t1 - add student" << endl
         << "\t2 - transfer student" << endl
         << "\t3 - remove student" << endl
         << "\t4 - print all" << endl
         << "\t5 - find by key" << endl
         << ": ";
    cin >> menu_point;

    if (menu_point == 0) {
      break;
    }
    switch (menu_point) {
    case 1:
      add_student();
      break;
    case 2:
      transfer_student();
      break;
    case 3:
      remove_student();
      break;
    case 4:
      print_students();
      break;
    case 5:
      find_student();
      break;
    default:
      cout << "wrong menu point" << endl;
      break;
    }
  }
}

void Application::add_student() {
  int key;
  Student* student;

  while (true) {
    cout << "key: ";
    cin >> key;

    if (students.find(key) == students.end())
      break;
    cout << "Error: such key is existed in list already" << endl;
  }

  student = new JuniorStudent();
  student->read(cout, cin);

  students.insert(make_pair(key, student));
}

void Application::transfer_student() {
  int key;
  cout << "key: ";
  cin >> key;

  auto it = students.find(key);

  if (it == students.end()) {
    cout << "no such student";
    return;
  }

  Student *student = it->second;
  Student* student_new;

  if (dynamic_cast<JuniorStudent*>(student)) {
    cout << "make him SeniorStudent? ";
    bool need = read_bool();

    if (need == true) {
      student_new = new SeniorStudent(
            student->name(), student->group(),
            student->chair(), "", "");
      student_new->read_transfer(cout, cin);
    }
    else {
      student_new = new JuniorStudent(
            student->name(), student->group(),
            student->chair());
      student_new->read_transfer(cout, cin);
    }
  }

  SeniorStudent* senior = dynamic_cast<SeniorStudent*>(student);
  if (dynamic_cast<SeniorStudent*>(student)) {
    cout << "make him GraduateStudent? ";
    bool need = read_bool();

    if (need == true) {
      student_new = new GraduateStudent(
            student->name(), student->group(),
            student->chair(), "", ""
      );
      student_new->read_transfer(cout, cin);
    }
    else {
      student_new = new SeniorStudent(
            student->name(), student->group(),
            student->chair(),
            senior->work(), senior->place()
      );
      student_new->read_transfer(cout, cin);
    }
  }

  students.erase(it);
  if (dynamic_cast<GraduateStudent*>(student) == nullptr) {
    students.insert(make_pair(key, student_new));
  }
  delete student;
}

bool Application::read_bool() {
  while (true) {
    string str;
    cout << "y/n: ";
    cin >> str;

    if (str == "y")
      return true;
    if (str == "n")
      return false;
  }
}

void Application::remove_student() {
  int key;
  cout << "key: ";
  cin >> key;

  auto it = students.find(key);

  if (it == students.end()) {
    cout << "no such student";
    return;
  }

  students.erase(it);
}

void Application::print_students() {
  cout << "type\tkey\tinformation" << endl;
  for (auto it = students.begin(); it != students.end(); ++it) {
    auto student = it->second;

    if (dynamic_cast<JuniorStudent*>(student))
      cout << "jun\t";
    if (dynamic_cast<SeniorStudent*>(student))
      cout << "sen\t";
    if (dynamic_cast<GraduateStudent*>(student))
      cout << "super\t";

    cout << it->first << "\t";
    it->second->print(cout);
  }
}

void Application::find_student() {
  int key;
  cout << "key: ";
  cin >> key;

  auto it = students.find(key);

  if (it == students.end()) {
    cout << "no such student" << endl;
    return;
  }

  it->second->print(cout);
}


Grades::Grades() {
}

void Grades::read(istream& ist) {
  for (int i = 0; i < m_grades.size(); ++i) {
    ist >> m_grades[i];
  }
}

SeniorGrades::SeniorGrades() {
  m_grades.resize(4+2);
}

void SeniorGrades::print(ostream &ost) {
  for (int i = 0; i < 4; ++i) {
    ost << m_grades[i] << " ";
  }
  ost << "#" << m_grades[4] << " #" << m_grades[5];
}

void SeniorGrades::read(ostream& ost, istream& ist) {
  ost << "enter 4 grades in last semester:";
  for (int i = 0; i < 4; ++i) {
    ist >> m_grades[i];
  }
  ost << "enter chief grade:";
  ist >> m_grades[4];
  ost << "enter committee grade:";
  ist >> m_grades[5];
}

JuniorGrades::JuniorGrades() {
  m_grades.resize(5);
}

void JuniorGrades::print(ostream &ost) {
  for (int i = 0; i < 5; ++i) {
    ost << m_grades[i] << " ";
  }
}

void JuniorGrades::read(ostream& ost, istream& ist) {
  ost << "enter 5 grades in last semester:";
  for (int i = 0; i < 5; ++i) {
    ist >> m_grades[i];
  }
}

GraduateGrades::GraduateGrades() {
  m_grades.resize(3);
}

void GraduateGrades::print(ostream &ost) {
  ost << "#" << m_grades[0] <<
         " #" << m_grades[1] << endl <<
         " #" << m_grades[2];
}

void GraduateGrades::read(ostream& ost, istream& ist) {
  ost << "enter chief grade:";
  ist >> m_grades[0];

  ost << "enter reviewer grade:";
  ist >> m_grades[1];

  ost << "enter committee grade:";
  ist >> m_grades[2];
}

Student::Student() {}

Student::Student(string name, int group, int chair)
  : m_name(name), m_group(group), m_chair(chair),
    m_grades(nullptr) {
}

void Student::read_grades(ostream& ost, istream& ist) {
  m_grades->read(ost, ist);
}

void Student::read_grades(istream& ist) {
  m_grades->read(ist);
}

void Student::group(int group) {
  m_group = group;
}

string Student::name() const {
  return m_name;
}

int Student::group() const {
  return m_group;
}

int Student::chair() const {
  return m_chair;
}

Grades* Student::grades() const {
  return m_grades;
}

void Student::print(ostream& ost) {
  ost << m_name << "\t" << m_group << "\t"
      << m_chair << "\t";
  m_grades->print(ost);
}

void Student::read(ostream &ost, istream &ist) {
  ost << "name: ";
  ist >> m_name;

  ost << "group: ";
  ist >> m_group;

  ost << "chair: ";
  ist >> m_chair;

  m_grades->read(ost, ist);
}

void Student::read_transfer(ostream& ost, istream& ist) {
  m_grades->read(ost, ist);
}

JuniorStudent::JuniorStudent() {
  m_grades = new JuniorGrades();
}

void JuniorStudent::print(ostream& ost) {
   Student::print(ost);
   ost << endl;
}

JuniorStudent::JuniorStudent(string name, int group, int chair)
  : Student(name, group, chair) {
  m_grades = new JuniorGrades();
}

SeniorStudent::SeniorStudent(string name, int group, int chair,
              string research_work, string research_place)
  : Student(name, group, chair),
    m_research_work(research_work),
    m_research_place(research_place) {
  m_grades = new SeniorGrades();
}

string SeniorStudent::work() {
  return m_research_work;
}

string SeniorStudent::place() {
  return m_research_place;
}

void SeniorStudent::read_transfer(ostream& ost, istream& ist) {
  m_grades->read(ost, ist);

  ost << "research work: ";
  ist >> m_research_work;

  ost << "research place: ";
  ist >> m_research_place;
}

void SeniorStudent::print(ostream& ost) {
  Student::print(ost);
  ost << " " << m_research_work << "\t"
      << m_research_place << endl;
}

void SeniorStudent::read(ostream &ost, istream &ist) {
  Student::read(ost, ist);

  ost << "research work: ";
  ist >> m_research_work;

  ost << "research place: ";
  ist >> m_research_place;
}

GraduateStudent::GraduateStudent(
    string name, int group, int chair,
    string graduate_work, string graduate_place)
  : Student(name, group, chair),
    m_graduate_work(graduate_work),
    m_graduate_place(graduate_place) {
   m_grades = new GraduateGrades();
}

void GraduateStudent::print(ostream& ost) {
  Student::print(ost);
  ost << " " << m_graduate_work << "\t"
      << m_graduate_place << endl;
}

void GraduateStudent::read(ostream &ost, istream &ist) {
  Student::read(ost, ist);

  ost << "graduate work: ";
  ist >> m_graduate_work;

  ost << "graduate place: ";
  ist >> m_graduate_place;
}

void GraduateStudent::read_transfer(ostream& ost, istream& ist) {
  m_grades->read(ost, ist);

  ost << "graduate work: ";
  ist >> m_graduate_work;

  ost << "graduate place: ";
  ist >> m_graduate_place;
}

