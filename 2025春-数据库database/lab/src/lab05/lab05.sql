-- 1)综合客户表(client)、薪资表(wage)，列出客户的名称、年份、身份证号、全职酬劳总金额（full_t_amount）、兼职酬劳总金额（part_t_amount）。
-- 查询结果按全职和兼职总金额降序排序。数据确保不存在全职和兼职总金额相等的客户。
-- 提示：确保只统计与有效客户关联的记录(客户表可能存在悬浮元组)
-- 输出表结构为：c_name, year, c_id_card, full_t_amount，part_t_amount
SELECT t.c_name,year,c_id_card,full_t_amount,part_t_amount
FROM(SELECT 
        c.c_name, 
        year(w.w_time) AS `year`, 
        c.c_id_card, 
        SUM(IF(w.w_type=1, w.w_amount, 0)) AS full_t_amount,
        SUM(IF(w.w_type=2, w.w_amount, 0)) AS part_t_amount
    FROM client c, wage w
    WHERE c.c_id=w.w_c_id
    GROUP BY w.w_c_id, year(w.w_time)) t
ORDER BY (t.full_t_amount+t.part_t_amount) DESC, part_t_amount ASC
;

/* 2)在均不计兼职的情况下，统计各单位的薪资总额、月平均薪资、最高薪资、最低薪资、中位薪资
client 表结构和 wage 表结构参考第一关。
计算各单位的薪资总额(total_amount), 月平均薪资（average_wage）、最高及最低薪资(max_wage，min_wage)、中位薪资（mid_wage）。查询结果按总金额降序排序。

注意：
1）月平均工资是薪资总额除以人数及月份。
2）最高及最低薪资是实际月薪资，非平均后的最高及最低薪资。
3）中位薪资是该单位员工人数中处于中间位置的人的月平均工资。例如，单位X共有9人，月平均薪资排第5人的工资即为中位薪资。若为偶数时，是中间两位的工资的平均数。
4) 确保只统计与有效客户关联的记录(客户表可能存在悬浮元组)
（平均工资保留两位小数）
输出格式：w_org, total_amount, average_wage, max_wage, min_wage, mid_wage */
WITH net_wage AS(
    SELECT *
    FROM wage
    JOIN client ON client.c_id=wage.w_c_id
),
personal AS(
    SELECT w_org, w_c_id,
    SUM(w_amount) AS person_total,
    ROUND(SUM(w_amount)/COUNT(DISTINCT DATE_FORMAT(w_time, '%Y-%m')), 2) AS person_avg

    FROM net_wage
    WHERE w_type=1
    GROUP BY w_org, w_c_id
),
minmax AS (
    SELECT w_org,
        MAX(w_amount) AS max_wage,
        MIN(w_amount) AS min_wage
    FROM net_wage
    WHERE w_type=1
    GROUP BY w_org
),
months AS (
    SELECT w_org, COUNT(DISTINCT DATE_FORMAT(w_time, '%Y-%m')) AS cnt_month
    FROM net_wage
    WHERE w_type=1
    GROUP BY w_org
),
stats AS (
    SELECT p.w_org,
        SUM(p.person_total) AS total_amount,
        COUNT(DISTINCT p.w_c_id) AS cnt_person,
        ROUND(SUM(p.person_total)/COUNT(DISTINCT p.w_c_id)/m.cnt_month,2) AS average_wage,
        mm.max_wage,min_wage
    FROM personal p, months m, minmax mm
    WHERE p.w_org=m.w_org AND p.w_org=mm.w_org
    GROUP BY w_org
),
ranks AS (
    SELECT w_org, person_avg,
        ROW_NUMBER() OVER(PARTITION BY w_org ORDER BY person_total) AS rn_asc
    FROM personal
)

SELECT p.w_org, s.total_amount,average_wage,max_wage,min_wage,
    ROUND(IF(s.cnt_person%2=1, 
        -- 奇数，取中间
        (SELECT person_avg FROM ranks WHERE w_org = s.w_org AND rn_asc = (s.cnt_person + 1) / 2),
        -- 偶数，取中间两人平均
        (
            (SELECT person_avg FROM ranks WHERE w_org = s.w_org AND rn_asc = (s.cnt_person / 2)) +
            (SELECT person_avg FROM ranks WHERE w_org = s.w_org AND rn_asc = (s.cnt_person / 2) + 1)
        ) / 2
    ),2) AS mid_wage
    
FROM personal p, months m, stats s
WHERE p.w_org=m.w_org AND p.w_org=s.w_org
GROUP BY s.w_org, s.total_amount, s.cnt_person, m.cnt_month
ORDER BY s.total_amount DESC
;



/* 3)获得兼职总酬劳前三名的客户
查询当前兼职总酬劳前三名的客户的姓名、身份证号及其总酬劳，按酬劳降序输出，总酬劳命名为total_salary。不需要考虑并列排名情形。
注意： 
1)本题目不需要考虑并列排名情形，这意味着前5名为16000，12900，12900，8000，8000时，也只需要给出16000，12900，12900即可。
2)确保只统计与有效客户关联的记录(客户表可能存在悬浮元组)
输出表结构为：c_name, c_id_card, total_salary */

SELECT c_name, c_id_card, 
       SUM(w_amount) AS total_salary
FROM client, wage
WHERE c_id=w_c_id AND w_type=2
GROUP BY c_id
ORDER BY total_salary DESC
LIMIT 3
;


/* 4)查找兼职酬劳的前三单位

client 表结构和 wage 表结构参考第一关。
查询发放兼职酬劳前三个单位名字，及发放兼职酬劳，按酬劳降序输出，总酬劳命名为total_salary。
注意： 不需要考虑并列排名情形;
并确保只统计与有效客户关联的记录(客户表可能存在悬浮元组)

输出格式：w_org, total_salary */

SELECT w_org, SUM(w_amount) AS total_salary
FROM client, wage
WHERE c_id=w_c_id AND w_type=2
GROUP BY w_org
ORDER BY total_salary DESC
LIMIT 3
;

/* 5）
已知表new_wage（表结构如下）保存了一批待发放的酬劳信息。用一条SQL语句将new_wage表的全部酬劳信息插入到薪资表(wage)。
注意：
（1）对于兼职人员，发放单位采用一事一酬。因此，某月内，对于某人，new_wage可能有多条待支付酬劳记录。插入wage表时需按月汇总后再插入，w_memo也同时合并(使用GROUP_CONCAT（）函数)。
（2）当多条记录中的c_id_card，w_amount，w_org，w_time都相同时，认为是重复记录，只保留一条。
（3）全职的酬劳时间按照原w_time插入，兼职的酬劳时间按照当月的最早w_time插入。
（4）缴纳税标志默认为N
（5） w_type为1代表全职,为2代表兼职
（6）插入wage的顺序为（w_c_id, w_amount, w_org, w_time, w_type, w_memo, w_tax），w_id会自动增加1。
w_id    w_c_id    w_org    w_time    w_type    w_tax    w_amount    w_memo
 */

INSERT INTO wage (w_c_id, w_amount, w_org, w_time, w_type, w_memo, w_tax)
WITH dedup AS (
  SELECT DISTINCT c_id_card, w_amount, w_org, w_time, w_type, w_memo
  FROM new_wage
)
SELECT
  c.c_id,
  t.w_amount,
  t.w_org,
  t.w_time,
  t.w_type,
  t.w_memo,
  'N'
FROM (
  -- 全职直接插入
  SELECT
    c_id_card,
    w_amount,
    w_org,
    w_time,
    w_type,
    w_memo
  FROM dedup
  WHERE w_type = 1

  UNION ALL

  -- 兼职按月、单位合并
  SELECT
    c_id_card,
    SUM(w_amount) AS w_amount,
    w_org,
    MIN(w_time) AS w_time,
    w_type,
    GROUP_CONCAT(w_memo ORDER BY w_time) AS w_memo
  FROM dedup
  WHERE w_type = 2
  GROUP BY c_id_card, w_org, DATE_FORMAT(w_time, '%Y-%m')
) t
JOIN client c ON t.c_id_card = c.c_id_card
ORDER BY c_id, w_org, w_time
;


/* 6)对身份证号为420108199702144323的客户2023年的酬劳代扣税

假设个人年所得total_salary低于60000，免交个人所得税，高于60000部分的税率为20%，即（total_salary-60000)* 0.2。
应扣税从当年的每月按比例扣除，即当月扣除（total_salary-60000）* 0.2 * (w_amount/ total_salary)，并设置扣税标志为Y。 */

SELECT c_id INTO @cid FROM client WHERE c_id_card = '420108199702144323';

SELECT SUM(w_amount) INTO @total_salary
FROM wage
WHERE w_c_id = @cid AND YEAR(w_time) = 2023;

UPDATE wage
SET w_tax=IF(@total_salary>60000,'Y','N'),
    w_amount=w_amount-IF(@total_salary>60000,ROUND((@total_salary-60000)*0.2*(w_amount/@total_salary), 2),0)
WHERE w_c_id=@cid AND year(w_time)='2023';
SELECT 