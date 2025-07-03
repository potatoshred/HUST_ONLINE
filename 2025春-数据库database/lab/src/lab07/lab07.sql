-- 1）创建包含所有保险资产记录的详细信息的视图v_insurance_detail，包括购买客户的名称、客户的身份证号、保险名称、保障项目、商品状态、商品数量、保险金额、保险年限、商品收益和购买时间。
-- 请用1条SQL语句完成上述任务：
use finance1;
CREATE VIEW v_insurance_detail AS
    SELECT c.c_name,c_id_card, i.i_name,i_project,p.pro_status,pro_quantity,i.i_amount,i_year,p.pro_income,pro_purchase_time
    FROM client c, insurance i, property p
    WHERE p.pro_type=2 AND p.pro_c_id=c.c_id AND p.pro_pif_id=i.i_id;

-- 2）基于上一关创建的视图v_insurance_detail进行分组统计查询，
-- 列出每位客户的姓名，身份证号，保险投资总额(insurance_total_amount)和保险投资总收益(insurance_total_revenue),结果依保险投资总额降序排列。

SELECT c_name, c_id_card,SUM(i_amount*pro_quantity) AS insurance_total_amount, SUM(pro_income) AS insurance_total_revenue
FROM v_insurance_detail
GROUP BY c_name, c_id_card
ORDER BY insurance_total_amount DESC
;