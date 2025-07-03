/* 1)在金融应用场景数据库环境中，创建用户，并给用户授予指定的权限。
 */
# 请填写语句，完成以下功能：
#(1) 创建用户tom和jerry，初始密码均为'123456'；
CREATE USER tom IDENTIFIED BY '123456';
CREATE USER jerry IDENTIFIED BY '123456';

#(2) 授予用户tom查询客户的姓名，邮箱和电话的权限,且tom可转授权限；
GRANT SELECT(c_name, c_mail, c_phone) 
ON client
TO tom 
WITH GRANT OPTION;

#(3) 授予用户jerry修改银行卡余额的权限；
GRANT UPDATE(b_balance) 
ON bank_card
TO jerry 
;

#(4) 收回用户Cindy查询银行卡信息的权限。
REVOKE SELECT
ON bank_card
FROM Cindy
;


/* 2）创建角色，授予角色一组权限，并将角色代表的权限授予指定的一组用户。 */

# 请填写语句，完成以下功能：
# (1) 创建角色client_manager和fund_manager；
CREATE ROLE client_manager;
CREATE ROLE fund_manager;
# (2) 授予client_manager对client表拥有select,insert,update的权限；
GRANT SELECT,INSERT,UPDATE
ON client
TO client_manager
;
# (3) 授予client_manager对bank_card表拥有查询除银行卡余额外的select权限；
GRANT SELECT(b_c_id,b_number, b_type)
ON bank_card
TO client_manager
;

# (4) 授予fund_manager对fund表的select,insert,update权限；
GRANT SELECT,INSERT,UPDATE
ON fund
TO fund_manager
;
# (5) 将client_manager的权限授予用户tom和jerry；
GRANT client_manager TO tom;
GRANT client_manager TO jerry;
# (6) 将fund_manager权限授予用户Cindy.
GRANT fund_manager TO Cindy;
