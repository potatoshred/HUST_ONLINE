import java.sql.*;
// 第7关：把稀疏表格转为键值对存储
public class Transform {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://127.0.0.1:3306/sparsedb?allowPublicKeyRetrieval=true&useUnicode=true&characterEncoding=UTF8&useSSL=false&serverTimezone=UTC";
    static final String USER = "root";
    static final String PASS = "123123";

    /**
     * 向sc表中插入数据
     *
     */
    public static int insertSC( Connection conn, int sno, String colName, String colValue) throws SQLException {
        String sql = "INSERT INTO sc (sno, col_name, col_value) VALUES (?, ?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, sno);
            pstmt.setString(2, colName);
            pstmt.setString(3, colValue);
            return pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        String[] columns = {"chinese", "math", "english", "physics", "chemistry", "biology", "history", "geography", "politics"};
        try {
            Class.forName(JDBC_DRIVER);
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
                 Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery("SELECT * FROM entrance_exam")) {

                while (rs.next()) {
                    int sno = rs.getInt("sno");
                    for (String col : columns) {
                        String value = rs.getString(col);
                        if (value != null) {
                            insertSC(conn, sno, col, value);
                        }
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}