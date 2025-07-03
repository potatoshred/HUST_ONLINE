-- 1）推导公式为：fib(n) = fib(n-1) + fib(n-2)。
-- 请根据提示，在右侧代码文件编辑器补充代码，创建存储过程sp_fibonacci(in m int)，向表fibonacci插入斐波拉契数列的前m项，及其对应的斐波拉契数。fibonacci表初始值为一张空表。请保证你的存储过程可以多次运行而不出错。
-- 创建存储过程`sp_fibonacci(in m int)`，向表fibonacci插入斐波拉契数列的前m项，及其对应的斐波拉契数。fibonacci表初始值为一张空表。请保证你的存储过程可以多次运行而不出错。

use fib;


drop procedure if exists sp_fibonacci;
delimiter $$
create procedure sp_fibonacci(in m int)
begin
######## 请补充代码完成存储过程体 ########

    declare i int default 0;
    declare a bigint default 0;
    declare b bigint default 1;

    truncate table fibonacci;

    while i<=m do
        insert into fibonacci(n,fibn) values (i, a);
        set i = i+1;
        set b = a+b;
        set a = b-a;
    end while

end $$

delimiter ;

-- 2）未完成

-- 3）使用事务的存储过程
-- 在金融应用场景数据库中，编程实现一个转账操作的存储过程sp_transfer_balance，实现从一个帐户向另一个帐户转账。
-- 请补充代码完成该过程：
use finance1;
delimiter $$
create procedure sp_transfer(
	                 IN applicant_id int,      
                     IN source_card_id char(30),
					 IN receiver_id int, 
                     IN dest_card_id char(30),
					 IN	amount numeric(10,2),
					 OUT return_code int)
proc_label: BEGIN
    DECLARE source_type CHAR(20);
    DECLARE dest_type CHAR(20);
    DECLARE source_balance NUMERIC(10,2);
    DECLARE dest_balance NUMERIC(10,2);
    DECLARE source_owner INT;
    DECLARE dest_owner INT;

    -- 检查付款卡
    SELECT b_type, b_balance, b_c_id INTO source_type, source_balance, source_owner
      FROM bank_card WHERE b_number = source_card_id FOR UPDATE;
    -- 检查收款卡
    SELECT b_type, b_balance, b_c_id INTO dest_type, dest_balance, dest_owner
      FROM bank_card WHERE b_number = dest_card_id FOR UPDATE;

    -- 仅当转款人是转出卡的持有人时，才可转出
    IF source_owner != applicant_id THEN
        SET return_code = 0;
        LEAVE proc_label;
    END IF;

    -- 仅当收款人是收款卡的持有人时，才可转入
    IF dest_owner != receiver_id THEN
        SET return_code = 0;
        LEAVE proc_label;
    END IF;

    -- 信用卡不能向储蓄卡转账
    IF source_type = '信用卡' AND dest_type = '储蓄卡' THEN
        SET return_code = 0;
        LEAVE proc_label;
    END IF;

    -- 转账金额不能超过储蓄卡余额
    IF source_type = '储蓄卡' AND source_balance < amount THEN
        SET return_code = 0;
        LEAVE proc_label;
    END IF;

    -- 开始事务
    START TRANSACTION;

    -- 储蓄卡扣款
    IF source_type = '储蓄卡' THEN
        UPDATE bank_card SET b_balance = b_balance - amount WHERE b_number = source_card_id;
    END IF;

    -- 储蓄卡或信用卡收款
    IF dest_type = '储蓄卡' THEN
        UPDATE bank_card SET b_balance = b_balance + amount WHERE b_number = dest_card_id;
    ELSE
        -- 信用卡收款(还款)，余额可以为负
        UPDATE bank_card SET b_balance = b_balance - amount WHERE b_number = dest_card_id;
    END IF;

    COMMIT;
    SET return_code = 1;
END$$

delimiter ;

