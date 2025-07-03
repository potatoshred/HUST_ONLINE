-- 第1关：并发控制与事务的隔离级别
-- 请不要在本代码文件中添加空行！！！ 
use testdb1;
# 设置事务的隔离级别为 read uncommitted
set session transaction isolation level read uncommitted;
-- 开启事务
start transaction;
insert into dept(name) values('运维部');
# 回滚事务：
rollback;
/* 结束 */

-- 第2关：读脏
-- 事务1:
use testdb1;
## 请设置适当的事务隔离级别
set session transaction isolation level read uncommitted;

start transaction;

-- 时刻2 - 事务1读航班余票,发生在事务2修改之后
## 添加等待代码，确保读脏
do sleep(3);
select tickets from ticket where flight_no = 'CA8213';
commit;

-- 事务2
use testdb1;
## 请设置适当的事务隔离级别
set session transaction isolation level read uncommitted;
start transaction;
-- 时刻1 - 事务2修改航班余票
update ticket set tickets = tickets - 1 where flight_no = 'CA8213';

-- 时刻3 - 事务2 取消本次修改
## 请添加代码，使事务1在事务2撤销前读脏;
do sleep(3);

rollback;


-- 第3关：不可重复读
-- 事务1:
## 请设置适当的事务隔离级别
set session transaction isolation level read committed;

-- 开启事务
start transaction;
-- 时刻1 - 事务1读航班余票:
insert into result 
select now(),1 t, tickets from ticket where flight_no = 'CZ5525';

## 添加等待代码，确保事务2的第一次读取在事务1修改前发生
do sleep(2);

-- 时刻3 - 事务1修改余票，并立即读取:
update ticket set tickets = tickets - 1 where flight_no = 'CZ5525';
insert into result
select now(),1 t, tickets from ticket where flight_no = 'CZ5525';

## 添加代码，使事务2 的第2次读取在事务1修改之后，提交之前发生
do sleep(3);

commit;

-- 时刻6 - 事务1在t2也提交后读取余票
## 添加代码，确保事务1在事务2提交后读取
do sleep(3);

insert into result
select now(), 1 t, tickets from ticket where flight_no = 'CZ5525';


-- 事务2
## 请设置适当的事务隔离级别以构造不可重复读
set session transaction isolation level read uncommitted;
start transaction;
-- 时刻2 - 事务2在事务1读取余票之后也读取余票
## 添加代码，确保事务2的第1次读发生在事务1读之后，修改之前
do sleep(1);

insert into result 
select now(),2 t, tickets from ticket where flight_no = 'CZ5525';

-- 时刻4 - 事务2在事务1修改余票但未提交前再次读取余票，事务2的两次读取结果应该不同
## 添加代码，确保事务2的读取时机
do sleep(3);

insert into result 
select now(), 2 t, tickets from ticket where flight_no = 'CZ5525';

-- 事务2立即修改余票
update ticket set tickets = tickets - 1 where flight_no = 'CZ5525';

-- 时刻5 - 事务2 读取余票（自己修改但未交的结果）:
-- set @n = sleep(1);
insert into result 
select now(), 2 t, tickets from ticket where flight_no = 'CZ5525';

commit;


-- 第4关：幻读
-- 事务1（采用默认的事务隔离级别- repeatable read）:
use testdb1;
select @@transaction_isolation;
start transaction;
## 第1次查询余票超过300张的航班信息
select * from ticket where tickets > 300;
do sleep(2);
-- 修改航班MU5111的执飞机型为A330-300：
update ticket set aircraft = 'A330-300' where flight_no = 'MU5111'; 
-- 第2次查询余票超过300张的航班信息
select * from ticket where tickets > 300;
commit;


-- 第5关：主动加锁保证可重复读
-- 事务1:
use testdb1;
set session transaction isolation level read uncommitted;
start transaction;
# 第1次查询航班'MU2455'的余票
select tickets from ticket where flight_no='MU2455' for share;
set @n = sleep(5);
# 第2次查询航班'MU2455'的余票
select tickets from ticket where flight_no='MU2455' for share;
commit;
-- 第3次查询所有航班的余票，发生在事务2提交后
set @n = sleep(1);
select * from ticket;


-- 事务2:
use testdb1;
set session transaction isolation level read uncommitted;
start transaction;
set @n = sleep(1);
# 在事务1的第1，2次查询之间，试图出票1张(航班MU2455)：
update ticket set tickets = tickets - 1 where flight_no='MU2455';
commit;



-- 第6关：可串行化
-- 事务1:
use testdb1;
start transaction;
set @n = sleep(2);
select tickets from ticket where flight_no = 'MU2455';
select tickets from ticket where flight_no = 'MU2455';
commit;
-- 事务2:
use testdb1;
start transaction;
set @n = sleep(1);
update ticket set tickets = tickets - 1 where flight_no = 'MU2455';
commit;
