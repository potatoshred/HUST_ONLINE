package homework.ch11_13.p3;

public class CourseTest {

    public static void main(String[] args) throws CloneNotSupportedException {
        Faculty teacher1 = new Faculty("Hally", 32, 7355608, "Coach", "TeamSpirit@cs.com");
        Course course1 = new Course("Shanghai Major", teacher1);

        Student sDonk = new Student("Donk", 17, 10001, "Fragger", "CS2401");
        Student sZontix = new Student("Zontix", 18, 10002, "Supporter", "CS2401");
        Student sShiro = new Student("Shiro", 19, 10003, "Sniper", "CS2401");
        Student sMagixx = new Student("Magixx", 20, 10004, "Lurker", "CS2401");
        Student sChopper = new Student("Chopper", 21, 10005, "IGL", "CS2401");

        course1.register(sDonk);
        course1.register(sZontix);
        course1.register(sShiro);
        course1.register(sMagixx);
        course1.register(sChopper);

        Course course2 = (Course) course1.clone();
        System.out.println(course1.equals(course2));
        System.out.println(course1.getCourseName() != course2.getCourseName());
        System.out.println(course1.getTeacher() != course2.getTeacher());
        System.out.println(course1.getStudents() != course2.getStudents());
        System.out.println(course2);
    }
}
