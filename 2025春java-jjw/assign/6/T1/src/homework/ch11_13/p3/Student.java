package homework.ch11_13.p3;

import java.util.Objects;


/**
 * This class represents a student in a department.
 * It extends the Person class and adds the studentId, department, and classNo fields.
 * It also overrides the toString(), equals(), and clone() methods.
 *
 * @author potatoshred
 * @version 1.0
 * @date 2025-03-26
 */
public class Student extends Person{
    int studentId;
    String department;
    String classNo;

    public Student() {
    }

    public Student(String name, int age, int studentId, String department, String classNo) {
        super(name, age);
        this.studentId = studentId;
        this.department = department;
        this.classNo = classNo;
    }

    public int getStudentId() {
        return studentId;
    }

    public void setStudentId(int studentId) {
        this.studentId = studentId;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public String getClassNo() {
        return classNo;
    }

    public void setClassNo(String classNo) {
        this.classNo = classNo;
    }

    @Override
    public String toString() {
        return "Student{" + super.toString() +
                ", studentId=" + studentId +
                ", department='" + department + '\'' +
                ", classNo='" + classNo + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Student student)) return false;
        if (!super.equals(o)) return false;
        return studentId == student.studentId
                && Objects.equals(department, student.department)
                && Objects.equals(classNo, student.classNo);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Student newStudent = (Student)super.clone();
        newStudent.studentId = studentId;
        newStudent.department = new String(department);
        newStudent.classNo = new String(classNo);
        return newStudent;
    }
}
