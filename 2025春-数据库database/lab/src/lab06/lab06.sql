-- 1) 向客户表插入以下3条数据:

-- c_id	c_name	c_mail	c_id_card	c_phone	c_password
-- 1	林惠雯	960323053@qq.com	411014196712130323	15609032348	Mop5UPkl
-- 2	吴婉瑜	1613230826@gmail.com	420152196802131323	17605132307	QUTPhxgVNlXtMxN
-- 3	蔡贞仪	252323341@foxmail.com	160347199005222323	17763232321	Bwe3gyhEErJ7

INSERT INTO client (c_id, c_name, c_mail, c_id_card, c_phone, c_password) VALUES
(1, '林惠雯', '960323053@qq.com', '411014196712130323', '15609032348', 'Mop5UPkl'),
(2, '吴婉瑜', '1613230826@gmail.com', '420152196802131323', '17605132307', 'QUTPhxgVNlXtMxN'),
(3, '蔡贞仪', '252323341@foxmail.com', '160347199005222323', '17763232321', 'Bwe3gyhEErJ7');


-- 2) 已知33号客户部分信息如下:
-- c_id(编号):33
-- c_name(名称):蔡依婷
-- c_phone(电话):18820762130
-- c_id_card(身份证号):350972199204227621
-- c_password(密码):MKwEuc1sc6
-- 请用一条SQL语句将这名客户的信息插入到客户表(client)。
INSERT INTO client (c_id, c_name, c_phone, c_id_card, c_password) VALUES
(33, '蔡依婷', '18820762130', '350972199204227621', 'MKwEuc1sc6');

-- 3) 已知表new_client保存了一批新客户信息，该表与client表结构完全相同。请用一条SQL语句将new_client表的全部客户信息插入到客户表(client)。

INSERT INTO client SELECT * FROM new_client;

-- 4) 请用一条SQL语句删除client表中没有银行卡的客户信息。
-- 注意：MySQL的delete语句中from关键词不能省略。

DELETE FROM client
WHERE c_id NOT IN (SELECT b_c_id FROM bank_card);

-- 5) 请用一条update语句将手机号码为“13686431238”这位客户的投资资产(理财、保险与基金)的状态置为“冻结”。

UPDATE property
SET pro_status = '冻结'
WHERE pro_c_id = (
    SELECT c_id FROM client WHERE c_phone = '13686431238'
);

-- 6) 在金融应用场景数据库中，已在表property(资产表)中添加了客户身份证列，列名为pro_id_card，类型为char(18)，该列目前全部留空(null)。
-- 请用一条update语句，根据client表中提供的身份证号(c_id_card)，填写property表中对应的身份证号信息(pro_id_card)。

UPDATE property
JOIN client on c_id=pro_c_id
SET pro_id_card=c_id_card;