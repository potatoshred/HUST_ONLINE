 -- 1) 查询2010年和2011年这两年每年销售总额前3名（如果有并列排名，则后续排名号跳过之前的并列排名个数，例如1、1、3）的统计年份（pyear）、销售总额排名值(rk)、理财产品编号(p_id)、销售总额(sumamount)。
--   注意结果输出要求：
--      (1)按照年份升序排列，同一年份按照销售总额的排名值升序排列，如遇到并列排名则按照理财产品编号升序排列;
--      (2)属性显示：统计年份（pyear）、销售总额排名值(rk)、理财产品编号(p_id)、销售总额(sumamount)
--      (3)结果显示顺序：先按照统计年份（pyear）升序排,同一年份按照销售总额排名值（rk）升序排,同一排名值的按照理财产品编号（p_id ）升序排。
--   请用一条SQL语句实现该查询：
SELECT t.pyear, rk, p_id, sumamount
FROM(
    SELECT year(pro_purchase_time) AS pyear, rank() OVER(PARTITION BY year(pro_purchase_time) ORDER BY SUM(pro_quantity*p_amount) DESC) AS rk, p_id, SUM(pro_quantity*p_amount) AS sumamount
    FROM property p, finances_product fp
    WHERE p.pro_type=1 AND p.pro_pif_id=fp.p_id AND pro_purchase_time BETWEEN '2010-1-1' AND '2011-12-31'
    GROUP BY year(pro_purchase_time), fp.p_id
    ) t
WHERE t.rk<4
ORDER BY t.pyear, rk, p_id;


  -- 2) 投资积极且偏好理财类产品的客户
--  购买了3种（同一编号的理财产品记为一种）以上理财产品的客户被认为投资积极的客户，
--  若该客户持有基金产品种类数（同一基金编号记为相同的基金产品种类）小于其持有的理财产品种类数，则认为该客户为投资积极且偏好理财产品的客户。查询所有此类客户的编号(pro_c_id)。
--  注意结果输出要求：按照客户编号的升序排列，且去除重复结果。
--   请用一条SQL语句实现该查询：
SELECT DISTINCT t1.pro_c_id
FROM
    (SELECT p.pro_c_id, COUNT(DISTINCT fp.p_id) AS cnt_finance
    FROM property p, finances_product fp
    WHERE p.pro_type=1 AND p.pro_pif_id=fp.p_id
    GROUP BY p.pro_c_id) t1,

    (SELECT p.pro_c_id, COUNT(DISTINCT f.f_id) AS cnt_fund
    FROM property p, fund f
    WHERE p.pro_type=3 AND p.pro_pif_id=f.f_id
    GROUP BY p.pro_c_id) t2
WHERE t1.pro_c_id=t2.pro_c_id AND t1.cnt_finance>t2.cnt_fund
ORDER BY t1.pro_c_id;


-- 3) 若定义持有人数超过2的理财产品称为畅销理财产品。查询购买了所有畅销理财产品的客户编号(pro_c_id)。
--  注意结果输出要求：按照客户编号的升序排列，且去除重复结果。
--   请用一条SQL语句实现该查询：
SELECT pro_c_id,COUNT(DISTINCT pro_pif_id)
FROM property
WHERE pro_type = 1
  AND pro_pif_id IN (
    SELECT pro_pif_id
    FROM property
    WHERE pro_type = 1
    GROUP BY pro_pif_id
    HAVING COUNT(DISTINCT pro_c_id) > 2
  ) 
GROUP BY pro_c_id
HAVING COUNT(DISTINCT pro_pif_id) = (
  SELECT COUNT(*)
  FROM (
    SELECT pro_pif_id
    FROM property
    WHERE pro_type = 1
    GROUP BY pro_pif_id
    HAVING COUNT(DISTINCT pro_c_id) > 2
  ) t
)
ORDER BY pro_c_id;


-- 4 请用一条SQL语句完成以下查询任务：
--   在某些推荐方法中，需要查找某款理财产品相似的其他理财产品，不妨设其定义为：
-- 对于某款理财产品A，可找到持有A数量最多的“3”个（包括所有持有相同数量的客户，因此如有3个并列第一、1个第二、一个第三，则排列结果是1,1,1,2,3）客户，
-- 然后对于这“3”个客户持有的所有理财产品（不包含产品A自身），每款产品被全体客户持有总人数被认为是和产品A的相似度，
-- 若有相似度相同的理财产品，则为了便于后续处理的确定性，则这些相似度相同的理财产品间按照产品编号的升序排列。
-- 按照和产品A的相似度，最多的“3”款（同上理，前3名允许并列的情况，例如排列结果是1,2,2,2,3）理财产品，就是产品A的相似的理财产品。
-- 请查找产品14的相似理财产品编号（不包含14自身）（pro_pif_id）、该编号的理财产品的客购买客户总人数（cc）以及该理财产品对于14 号理财产品的相似度排名值（prank）。
-- 注意结果输出要求：按照相似度值降序排列，相同相似度的理财产品之间则按照产品编号的升序排列。
-- 请用一条SQL语句实现该查询：
WITH ranked_customers AS (
    SELECT 
        pro_c_id, 
        DENSE_RANK() OVER (ORDER BY pro_quantity DESC) AS drk
    FROM property 
    WHERE pro_pif_id = 14 AND pro_type = 1
),
top_customers AS (
    SELECT pro_c_id 
    FROM ranked_customers 
    WHERE drk <= 3
),
customer_products AS (
    SELECT DISTINCT pro_pif_id
    FROM property 
    WHERE pro_c_id IN (SELECT pro_c_id FROM top_customers)
        AND pro_pif_id <> 14 
        AND pro_type = 1
),
product_counts AS (
    SELECT 
        pro_pif_id, 
        COUNT(DISTINCT pro_c_id) AS cc
    FROM property 
    WHERE pro_pif_id IN (SELECT pro_pif_id FROM customer_products)
        AND pro_type = 1
    GROUP BY pro_pif_id
),
ranked_products AS (
    SELECT 
        pro_pif_id, 
        cc,
        DENSE_RANK() OVER (ORDER BY cc DESC) AS prank
    FROM product_counts
)
SELECT 
    pro_pif_id, 
    cc, 
    prank
FROM ranked_products
WHERE prank <= 3
ORDER BY cc DESC, pro_pif_id ASC;



-- 5 请用一条SQL语句完成以下查询任务：
--   查询任意两个客户之间持有的相同理财产品种数，并且结果仅保留相同理财产品数至少2种的用户对。
--   注意结果输出要求：第一列和第二列输出客户编号(pro_c_id,pro_c_id)，第三列输出他们持有的相同理财产品数(total_count)，按照第一列的客户编号的升序排列。
SELECT p1.pro_c_id, p2.pro_c_id, COUNT(*) AS total_count
FROM property p1, property p2
WHERE p1.pro_type=1 AND p2.pro_type=1 AND p1.pro_pif_id=p2.pro_pif_id AND p1.pro_c_id!=p2.pro_c_id
GROUP BY p1.pro_c_id, p2.pro_c_id
HAVING total_count>1
ORDER BY p1.pro_c_id
;

-- 6 在某些推荐方法中，需要查找某位客户在理财行为上相似的其他客户，不妨设其定义为：
-- 对于A客户，其购买的理财产品集合为{P}，另所有买过{P}中至少一款产品的其他客户集合为{B}，则{B}中每位用户购买的{P}中产品的数量为他与A客户的相似度值。
-- 将{B}中客户按照相似度值降序排列，得到A客户的相同相似度值则按照客户编号升序排列，这样取前两位客户即为A客户的相似理财客户列表。
--   查询每位客户(列名：pac)的相似度排名值小于3的相似客户(列名：pbc)列表，以及该每位客户和他的每位相似客户的共同持有的理财产品数(列名：common)、相似度排名值(列名：crank)。
--   注意结果输出要求：要求结果先按照左边客户编号(pac)升序排列，同一个客户的相似客户则按照客户相似度排名值（crank）顺序排列。
SELECT t.pac,pbc,common,crank
FROM(SELECT p1.pro_c_id AS pac,  p2.pro_c_id AS pbc, COUNT(*) AS common, RANK() OVER (PARTITION BY p1.pro_c_id ORDER BY COUNT(*) DESC, p2.pro_c_id ASC) AS crank
    FROM property p1, property p2
    WHERE p1.pro_type=1 AND p2.pro_type=1 AND p1.pro_pif_id=p2.pro_pif_id AND p1.pro_c_id!=p2.pro_c_id
    GROUP BY p1.pro_c_id, p2.pro_c_id) t
WHERE t.crank<3 
ORDER BY t.pac, crank 
;