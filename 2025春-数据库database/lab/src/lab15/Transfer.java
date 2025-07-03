import java.sql.*;
import java.util.Scanner;

public class Transfer {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://127.0.0.1:3306/finance?allowPublicKeyRetrieval=true&useUnicode=true&characterEncoding=UTF8&useSSL=false&serverTimezone=UTC";
    static final String USER = "root";
    static final String PASS = "123123";
    /**
     * 转账操作
     *
     * @param connection 数据库连接对象
     * @param sourceCard 转出账号
     * @param destCard 转入账号
     * @param amount  转账金额
     * @return boolean
     *   true  - 转账成功
     *   false - 转账失败
     */
    public static boolean transferBalance(Connection connection,
                             String sourceCard,
                             String destCard, 
                             double amount){
                                
        PreparedStatement ps1 = null, ps2 = null, ps3 = null, ps4 = null;
        ResultSet rs1 = null, rs2 = null;
        try {
            // 开启手动事务
            connection.setAutoCommit(false);

            // 1. 检查转出卡是否存在且不是信用卡
            String sql1 = "SELECT b_type, b_balance FROM bank_card WHERE b_number = ?";
            ps1 = connection.prepareStatement(sql1);
            ps1.setString(1, sourceCard);
            rs1 = ps1.executeQuery();
            if (!rs1.next()) {
                connection.rollback();
                return false; // 转出卡不存在
            }
            String sourceType = rs1.getString("b_type");
            double sourceBalance = rs1.getDouble("b_balance");
            if ("信用卡".equals(sourceType)) {
                connection.rollback();
                return false; // 转出卡是信用卡
            }
            if (sourceBalance < amount) {
                connection.rollback();
                return false; // 余额不足
            }

            // 2. 检查转入卡是否存在
            ps2 = connection.prepareStatement(sql1);
            ps2.setString(1, destCard);
            rs2 = ps2.executeQuery();
            if (!rs2.next()) {
                connection.rollback();
                return false; // 转入卡不存在
            }
            // 判断转入卡类型
            String destType = rs2.getString("b_type");

            // 3. 扣减转出卡余额
            String sql2 = "UPDATE bank_card SET b_balance = b_balance - ? WHERE b_number = ?";
            ps3 = connection.prepareStatement(sql2);
            ps3.setDouble(1, amount);
            ps3.setString(2, sourceCard);
            int update1 = ps3.executeUpdate();
            if (update1 != 1) {
                connection.rollback();
                return false;
            }

            // 4. 增加转入卡余额（信用卡为还款，余额减少负债，储蓄卡余额增加）
            String sql3 = "UPDATE bank_card SET b_balance = b_balance + ? WHERE b_number = ?";
            if ("信用卡".equals(destType)) {
                // 信用卡还款，b_balance为负债，减少负债
                sql3 = "UPDATE bank_card SET b_balance = b_balance - ? WHERE b_number = ?";
            }
            ps4 = connection.prepareStatement(sql3);
            ps4.setDouble(1, amount);
            ps4.setString(2, destCard);
            int update2 = ps4.executeUpdate();
            if (update2 != 1) {
                connection.rollback();
                return false;
            }

            // 5. 提交事务
            connection.commit();
            return true;
        } catch (Exception e) {
            try { connection.rollback(); } catch (Exception ex) {}
            return false;
        } finally {
            try { if (rs1 != null) rs1.close(); } catch (Exception e) {}
            try { if (rs2 != null) rs2.close(); } catch (Exception e) {}
            try { if (ps1 != null) ps1.close(); } catch (Exception e) {}
            try { if (ps2 != null) ps2.close(); } catch (Exception e) {}
            try { if (ps3 != null) ps3.close(); } catch (Exception e) {}
            try { if (ps4 != null) ps4.close(); } catch (Exception e) {}
            try { connection.setAutoCommit(true); } catch (Exception e) {}
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
            String payerCard = commands[0];
            String  payeeCard = commands[1];
            double  amount = Double.parseDouble(commands[2]);
            if (transferBalance(connection, payerCard, payeeCard, amount)) {
              System.out.println("转账成功。" );
            } else {
              System.out.println("转账失败,请核对卡号，卡类型及卡余额!");
            }
        }
    }

}
