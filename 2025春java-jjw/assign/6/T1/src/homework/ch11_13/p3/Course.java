package homework.ch11_13.p3;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Course class represents a course in a university.
 * It has a name, a list of students, and a teacher.
 * It also provides methods to register and unregister students.
 *
 * @author potatoshred
 * @version 1.0
 * @date 2025-03-26
 */
public class Course implements Cloneable{

    private String courseName;
    private List<Person> students;
    private Person teacher;

    public Course(String courseName, Person teacher) {
        this.courseName = courseName;
        this.teacher = teacher;
        this.students = new ArrayList<Person>();
    }

    public String getCourseName() {
        return courseName;
    }

    public List<Person> getStudents() {
        return students;
    }

    public Person getTeacher() {
        return teacher;
    }

    public int getNumberOfStudent() {
        return students.size();
    }

    public void register(Person student) {
        if (students.contains(student)) { return; }
        students.add(student);
    }

    public void unregister(Person student) {
        int len = students.size();
        for (int i = 0; i < len; ++i) {
            if (students.get(i).equals(student)){
                students.remove(i);
                break;
            }
        }
    }

    @Override
    public String toString() {
        return "Course{" +
                "courseName='" + courseName + '\'' +
                ", students=" + students.toString() +
                ", teacher=" + teacher.toString() +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Course course)) return false;
        return Objects.equals(courseName, course.courseName)
                && students.size()==course.students.size()
                && students.containsAll(course.students)
                && Objects.equals(teacher, course.teacher);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Course newCourse = (Course) super.clone();

        newCourse.courseName = new String(courseName);
        newCourse.teacher = (Person) teacher.clone();
        newCourse.students = new ArrayList<Person>();
        for (Person p : students){
            newCourse.register((Person) p.clone());
        }
        return newCourse;
    }
}
