-- 1) 查询所有客户的名称、手机号和邮箱信息。查询结果按照客户编号排序。
--    请用一条SQL语句实现该查询：

SELECT c_name, c_phone, c_mail
FROM client
ORDER BY c_id ASC 

-- 2) 查询客户表(client)中邮箱信息为null的客户的编号、名称、身份证号、手机号。
--    请用一条SQL语句实现该查询：
SELECT c_id, c_name, c_id_card, c_phone
FROM client
WHERE c_mail IS NULL


-- 3) 查询既买了保险又买了基金的客户的名称、邮箱和电话。结果依c_id排序
-- 请用一条SQL语句实现该查询：

SELECT c_name, c_mail, c_phone
FROM client
WHERE c_id in (
    SELECT p1.pro_c_id
    FROM property p1, property p2
    WHERE p1.pro_c_id=p2.pro_c_id AND p1.pro_type=2 AND p2.pro_type=3
)
ORDER BY c_id ASC;


-- 4) 查询办理了储蓄卡的客户名称、手机号、银行卡号。 查询结果结果依客户编号排序。
--    请用一条SQL语句实现该查询：

SELECT c.c_name, c_phone, b.b_number
FROM client c, bank_card b
WHERE c.c_id=b.b_c_id AND b.b_type='储蓄卡'
ORDER BY c.c_id;


-- 5) 查询理财产品中每份金额在30000～50000之间的理财产品的编号,每份金额，理财年限，并按照金额升序排序，金额相同的按照理财年限降序排序。
--    请用一条SQL语句实现该查询：
SELECT p_id, p_amount, p_year
FROM finances_product
WHERE p_amount BETWEEN 30000 AND 50000
ORDER BY p_amount ASC, p_year DESC;


-- 6) 查询资产表中所有资产记录里商品收益的众数和它出现的次数。
--    请用一条SQL语句实现该查询：
SELECT pro_income, COUNT(*) AS presence 
FROM property
GROUP BY pro_income
HAVING COUNT(*)>=ALL(
    SELECT COUNT(*)
    FROM property 
    GROUP BY pro_income
);


-- 7) 查询身份证隶属武汉市没有买过任何理财产品的客户的名称、电话号、邮箱。
--    请用一条SQL语句实现该查询：
SELECT c_name, c_phone, c_mail
FROM client c
WHERE c.c_id_card LIKE '4201%' AND NOT EXISTS (
    SELECT p.pro_c_id
    FROM property p
    WHERE c.c_id=p.pro_c_id AND pro_type=1 
)
ORDER BY c.c_id ASC;


-- 8) 查询持有两张(含）以上信用卡的用户的名称、身份证号、手机号。
--    请用一条SQL语句实现该查询：

SELECT c.c_name,c_id_card,c_phone
FROM client c
WHERE c.c_id IN (
    SELECT b_c_id
    FROM bank_card b
    WHERE b.b_type='信用卡'
    GROUP BY b.b_c_id
    HAVING COUNT(*)>=2
    )
ORDER BY c.c_id ASC;


-- 9) 查询购买了货币型(f_type='货币型')基金的用户的名称、电话号、邮箱。
--   请用一条SQL语句实现该查询：

SELECT c.c_name,c_phone,c_mail
FROM client c, property p, fund f
WHERE c.c_id=p.pro_c_id AND p.pro_type=3 AND f.f_id=p.pro_pif_id AND f.f_type='货币型'
GROUP BY c.c_id, c.c_name, c.c_phone, c.c_mail
ORDER BY c.c_id ASC;


-- 10) 查询当前总的可用资产收益(被冻结的资产除外)前三名的客户的名称、身份证号及其总收益，按收益降序输出，总收益命名为total_income。不考虑并列排名情形。
--    请用一条SQL语句实现该查询：

SELECT c.c_name,c_id_card, SUM(p.pro_income) AS total_income
FROM client c, property p
WHERE c.c_id=p.pro_c_id AND p.pro_status='可用'
GROUP BY c.c_id,c_name,c_id_card
ORDER BY total_income DESC
LIMIT 3;


-- 11) 给出黄姓用户的编号、名称、办理的银行卡的数量(没有办卡的卡数量计为0),持卡数量命名为number_of_cards,
--     按办理银行卡数量降序输出,持卡数量相同的,依客户编号排序。
-- 请用一条SQL语句实现该查询：
SELECT c.c_id,c_name, COUNT(b.b_number) AS number_of_cards 
FROM client c
LEFT JOIN bank_card b ON c.c_id = b.b_c_id
WHERE c.c_name LIKE '黄%'
GROUP BY c.c_id
ORDER BY number_of_cards DESC, c_id ASC;

 -- 12) 综合客户表(client)、资产表(property)、理财产品表(finances_product)、保险表(insurance)和
 --     基金表(fund)，列出客户的名称、身份证号以及投资总金额（即投资本金，
 --     每笔投资金额=商品数量*该产品每份金额)，注意投资金额按类型需要查询不同的表，
 --     投资总金额是客户购买的各类资产(理财,保险,基金)投资金额的总和，总金额命名为total_amount。
 --     查询结果按总金额降序排序。
 -- 请用一条SQL语句实现该查询：

SELECT 
    c.c_name,c_id_card,
    IFNULL(SUM(t.amount), 0) AS total_amount
FROM client c
LEFT JOIN (
    SELECT p.pro_c_id, p.pro_quantity * fp.p_amount AS amount
    FROM property p
    JOIN finances_product fp ON p.pro_type = 1 AND p.pro_pif_id = fp.p_id

    UNION ALL

    SELECT p.pro_c_id, p.pro_quantity * i.i_amount AS amount
    FROM property p
    JOIN insurance i ON p.pro_type = 2 AND p.pro_pif_id = i.i_id

    UNION ALL

    SELECT p.pro_c_id, p.pro_quantity * f.f_amount AS amount
    FROM property p
    JOIN fund f ON p.pro_type = 3 AND p.pro_pif_id = f.f_id
) t ON c.c_id = t.pro_c_id
GROUP BY c.c_id
ORDER BY total_amount DESC;

-- 13) 综合客户表(client)、资产表(property)、理财产品表(finances_product)、
--     保险表(insurance)、基金表(fund)和投资资产表(property)，
--     列出所有客户的编号、名称和总资产，总资产命名为total_property。
--     总资产为储蓄卡余额，投资总额，投资总收益的和，再扣除信用卡透支的金额
--     (信用卡余额即为透支金额)。客户总资产包括被冻结的资产。
--    请用一条SQL语句实现该查询：

SELECT c.c_id,c_name, IFNULL(SUM(t.prop), 0) AS total_property
FROM client c
LEFT JOIN (
    SELECT b_c_id AS tid, SUM(b_balance) AS prop
    FROM bank_card
    WHERE b_type='储蓄卡'
    GROUP BY b_c_id

    UNION ALL

    SELECT b_c_id AS tid, SUM(b_balance*-1) AS prop
    FROM bank_card
    WHERE b_type='信用卡'
    GROUP BY b_c_id

    UNION ALL
    
    SELECT p.pro_c_id AS tid, p.pro_quantity * fp.p_amount  + p.pro_income AS prop
    FROM property p
    JOIN finances_product fp ON p.pro_type = 1 AND p.pro_pif_id = fp.p_id

    UNION ALL

    SELECT p.pro_c_id AS tid, p.pro_quantity * i.i_amount + p.pro_income AS prop
    FROM property p
    JOIN insurance i ON p.pro_type = 2 AND p.pro_pif_id = i.i_id

    UNION ALL

    SELECT p.pro_c_id AS tid, p.pro_quantity * f.f_amount + p.pro_income AS prop
    FROM property p
    JOIN fund f ON p.pro_type = 3 AND p.pro_pif_id = f.f_id
) AS t ON c.c_id=t.tid
GROUP BY c.c_id;

-- 14) 查询每份保险金额第4高保险产品的编号和保险金额。
--     在数字序列8000,8000,7000,7000,6000中，
--     两个8000均为第1高，两个7000均为第2高,6000为第3高。
-- 请用一条SQL语句实现该查询：

SELECT a.i_id,i_amount
FROM insurance a
WHERE a.i_amount=(
    select distinct b.i_amount
    from insurance b
    order by i_amount desc
    limit 3,1
);


-- 15) 查询资产表中客户编号，客户基金投资总收益,基金投资总收益的排名(从高到低排名)。
--     总收益相同时名次亦相同(即并列名次)。总收益命名为total_revenue, 名次命名为rank。
--     第一条SQL语句实现全局名次不连续的排名，
--     第二条SQL语句实现全局名次连续的排名。

--      (1) 基金总收益排名(名次不连续)
SELECT 
    pro_c_id, 
    SUM(pro_income) AS total_revenue, 
    RANK() OVER (ORDER BY SUM(pro_income) DESC) AS `rank`
FROM property
WHERE pro_type=3 
GROUP BY pro_c_id;


--      (2) 基金总收益排名(名次连续)
SELECT 
    pro_c_id, 
    SUM(pro_income) AS total_revenue, 
    DENSE_RANK() OVER (ORDER BY SUM(pro_income) DESC) AS `rank`
FROM property
WHERE pro_type=3 
GROUP BY pro_c_id;

-- 16) 查询持有相同基金组合的客户对，
-- 如编号为A的客户持有的基金，编号为B的客户也持有，反过来，编号为B的客户持有的基金，编号为A的客户也持有，则(A,B)即为持有相同基金组合的二元组，请列出这样的客户对。
-- 为避免过多的重复，如果(1,2)为满足条件的元组，则不必显示(2,1)，即只显示编号小者在前的那一对，这一组客户编号分别命名为c_id1,c_id2。
-- 请用一条SQL语句实现该查询：
SELECT 
    a.pro_c_id AS c_id1,
    b.pro_c_id AS c_id2
FROM 
    (SELECT pro_c_id, GROUP_CONCAT(DISTINCT pro_pif_id ORDER BY pro_pif_id) AS fund_set
     FROM property
     WHERE pro_type = 3
     GROUP BY pro_c_id) a
JOIN 
    (SELECT pro_c_id, GROUP_CONCAT(DISTINCT pro_pif_id ORDER BY pro_pif_id) AS fund_set
     FROM property
     WHERE pro_type = 3
     GROUP BY pro_c_id) b
ON a.fund_set = b.fund_set AND a.pro_c_id < b.pro_c_id;

SELECT DISTINCT a.pro_c_id AS c_id1, b.pro_c_id AS c_id2
FROM property a, property b 
WHERE a.pro_type = 3 AND b.pro_type = 3 AND a.pro_c_id < b.pro_c_id
  -- a有的基金b都有
  AND NOT EXISTS (
    SELECT 1 FROM property pa
    WHERE pa.pro_c_id = a.pro_c_id AND pa.pro_type = 3
      AND NOT EXISTS (
        SELECT 1 FROM property pb
        WHERE pb.pro_c_id = b.pro_c_id AND pb.pro_type = 3
          AND pb.pro_pif_id = pa.pro_pif_id
      )
  )
  -- b有的基金a都有
  AND NOT EXISTS (
    SELECT 1 FROM property pb
    WHERE pb.pro_c_id = b.pro_c_id AND pb.pro_type = 3
      AND NOT EXISTS (
        SELECT 1 FROM property pa
        WHERE pa.pro_c_id = a.pro_c_id AND pa.pro_type = 3
          AND pa.pro_pif_id = pb.pro_pif_id
      )
  );


-- 17) 查询2022年2月购买基金的高峰期。至少连续三个交易日，所有投资者购买基金的总金额超过100万(含)，则称这段连续交易日为投资者购买基金的高峰期。
-- 只有交易日才能购买基金,但不能保证每个交易日都有投资者购买基金。2022年春节假期之后的第1个交易日为2月7日,周六和周日是非交易日，其余均为交易日。
-- 请列出高峰时段的日期和当日基金的总购买金额，按日期顺序排序。总购买金额命名为total_amount。
--    请用一条SQL语句实现该查询：
SELECT t2.pro_purchase_time, total_amount
FROM(
    SELECT t1.pro_purchase_time, total_amount,
        IF(incL1=1 AND incL2=2, MIN(t1.total_amount) OVER (ROWS BETWEEN 2 PRECEDING AND CURRENT ROW), 0) AS min1,
        IF(incL1=1 AND incR1=4, MIN(t1.total_amount) OVER (ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING), 0) AS min2,
        IF(incR1=4 AND incR2=3, MIN(t1.total_amount) OVER (ROWS BETWEEN CURRENT ROW AND 2 FOLLOWING), 0) AS min3
    FROM(
        SELECT pro_purchase_time, 
            SUM(pro_quantity*f_amount) AS total_amount, 
            (weekday(pro_purchase_time)-weekday(LAG(pro_purchase_time, 1) OVER (ORDER BY pro_purchase_time)) +5)%5 AS incL1,
            (weekday(pro_purchase_time)-weekday(LAG(pro_purchase_time, 2) OVER (ORDER BY pro_purchase_time)) +5)%5 AS incL2,
            (weekday(pro_purchase_time)-weekday(LEAD(pro_purchase_time, 1)OVER (ORDER BY pro_purchase_time)) +5)%5 AS incR1,
            (weekday(pro_purchase_time)-weekday(LEAD(pro_purchase_time, 2)OVER (ORDER BY pro_purchase_time)) +5)%5 AS incR2
        FROM property, fund 
        WHERE pro_type=3 AND pro_pif_id=f_id AND pro_purchase_time BETWEEN '2022-02-01' AND '2022-02-28' 
        GROUP BY pro_purchase_time
        ORDER BY pro_purchase_time ASC
        ) t1
    ) t2
WHERE t2.min1>=1000000 OR t2.min2>=1000000 OR t2.min3>=1000000;



 -- 18) 查询至少有一张信用卡余额超过5000元的客户编号，以及该客户持有的信用卡总余额，总余额命名为credit_card_amount。
--    请用一条SQL语句实现该查询：

SELECT b_c_id, SUM(b_balance) AS credit_card_amount
FROM bank_card
WHERE b_type='信用卡'
GROUP BY b_c_id
HAVING MAX(b_balance)>5000
ORDER BY b_c_id;

-- 19) 以日历表格式列出2022年2月每周每日基金购买总金额，输出格式如下：
-- week_of_trading Monday Tuesday Wednesday Thursday Friday
--               1
--               2    
--               3
--               4
--   请用一条SQL语句实现该查询：-- pro_quantity*f_amount AS amount
SELECT week_of_trading,
    SUM(IF(wday=0,amount,NULL)) AS Monday,
    SUM(IF(wday=1,amount,NULL)) AS Tuesday,
    SUM(IF(wday=2,amount,NULL)) AS Wednesday,
    SUM(IF(wday=3,amount,NULL)) AS Thursday,
    SUM(IF(wday=4,amount,NULL)) AS Friday
FROM (SELECT week(pro_purchase_time)-5 AS week_of_trading, weekday(pro_purchase_time) AS wday, SUM(pro_quantity*f_amount) AS amount
    FROM property, fund
    WHERE pro_type=3 AND pro_pif_id=f_id AND pro_purchase_time BETWEEN '2022-02-01' AND '2022-02-28'
    GROUP BY pro_purchase_time
    ORDER BY pro_purchase_time ASC) t
GROUP BY week_of_trading;



