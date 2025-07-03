import java.sql.*;
import java.util.Scanner;

public class AddClient {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://127.0.0.1:3306/finance?allowPublicKeyRetrieval=true&useUnicode=true&characterEncoding=UTF8&useSSL=false&serverTimezone=UTC";
    static final String USER = "root";
    static final String PASS = "123123";
    /**
     * 向Client表中插入数据
     *
     * @param connection 数据库连接对象
     * @param c_id 客户编号
     * @param c_name 客户名称
     * @param c_mail 客户邮箱
     * @param c_id_card 客户身份证
     * @param c_phone 客户手机号
     * @param c_password 客户登录密码
     */
    public static int insertClient(Connection connection,
                                   int c_id, String c_name, String c_mail,
                                   String c_id_card, String c_phone, 
                                   String c_password){

        String sql = "INSERT INTO client (c_id, c_name, c_mail, c_id_card, c_phone, c_password) VALUES (?, ?, ?, ?, ?, ?)";
        try (PreparedStatement pstmt = connection.prepareStatement(sql)) {
            pstmt.setInt(1, c_id);
            pstmt.setString(2, c_name);
            pstmt.setString(3, c_mail);
            pstmt.setString(4, c_id_card);
            pstmt.setString(5, c_phone);
            pstmt.setString(6, c_password);
            return pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }

    }

    // 不要修改main() 
    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(System.in);
        Class.forName(JDBC_DRIVER);

        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);

        while(sc.hasNext())
        {
            String input = sc.nextLine();
            if(input.equals(""))
                break;

            String[]commands = input.split(" ");
            if(commands.length ==0)
                break;
            int id = Integer.parseInt(commands[0]);
            String name = commands[1];
            String mail = commands[2];
            String idCard = commands[3];
            String phone = commands[4];
            String password = commands[5];

            insertClient(connection, id, name, mail, idCard, phone, password);
        }
    }

}
