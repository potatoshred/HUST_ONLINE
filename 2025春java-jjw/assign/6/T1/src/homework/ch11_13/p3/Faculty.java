package homework.ch11_13.p3;

import java.util.Objects;

/**
 * This class represents a faculty member in the university.
 * It extends the Person class and adds the facultyId, title, and email fields.
 * It overrides the toString(), equals(), and clone() methods to provide custom functionality.
 * It also provides getters and setters for the facultyId, title, and email fields.
 *
 * @author potatoshred
 * @version 1.0
 * @date 2025-03-26
 */
public class Faculty extends Person{
    private int facultyId;
    private String title;
    private String email;

    public Faculty() {
    }

    public Faculty(String name, int age, int facultyId, String title, String email) {
        super(name, age);
        this.facultyId = facultyId;
        this.title = title;
        this.email = email;
    }

    public int getFacultyId() {
        return facultyId;
    }

    public void setFacultyId(int facultyId) {
        this.facultyId = facultyId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public String toString() {
        return "Faculty{" + super.toString() +
                ", facultyId=" + facultyId +
                ", title='" + title + '\'' +
                ", email='" + email + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Faculty faculty)) return false;
        if (!super.equals(o)) return false;
        return facultyId == faculty.facultyId
                && Objects.equals(title, faculty.title)
                && Objects.equals(email, faculty.email);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Faculty newFaculty = (Faculty)super.clone();
        newFaculty.facultyId = facultyId;
        newFaculty.title = new String(title);
        newFaculty.email = new String(email);
        return newFaculty;
    }
}
