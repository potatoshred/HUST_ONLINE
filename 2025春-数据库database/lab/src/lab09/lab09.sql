/* 1）为表property(资产表)编写一个触发器
(1) 查阅MySQL的字符串函数，构造出错信息；
(2) 当数据不合法时，用signal sqlstate 语句抛出异常，并设置出错信息：
SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = msg;
其中，通用SQLSTATE '45000'意指用户定义的待处理异常，msg需替换成你想要显示的提示信息(不超过128个字符)。
 */
use finance1;
drop trigger if exists before_property_inserted;
-- 请在适当的地方补充代码，完成任务要求：
delimiter $$
CREATE TRIGGER before_property_inserted BEFORE INSERT ON property
FOR EACH ROW 
BEGIN

    DECLARE msg char(128) DEFAULT NULL;
    -- 检查pro_type是否合法
    IF NEW.pro_type NOT IN (1, 2, 3) THEN
        set msg = CONCAT('type ', NEW.pro_type, ' is illegal!');
        SIGNAL SQLSTATE '45000'SET MESSAGE_TEXT = msg;
    END IF;

    -- 检查pro_type=1时pro_pif_id是否存在于finances_product
    IF NEW.pro_type = 1 THEN
        IF NOT EXISTS (SELECT 1 FROM finances_product WHERE p_id = NEW.pro_pif_id) THEN
            set msg = CONCAT('finances product #', NEW.pro_pif_id, ' not found!');
            SIGNAL SQLSTATE '45000'SET MESSAGE_TEXT = msg;
        END IF;
    END IF;

    -- 检查pro_type=2时pro_pif_id是否存在于insurance
    IF NEW.pro_type = 2 THEN
        IF NOT EXISTS (SELECT 1 FROM insurance WHERE i_id = NEW.pro_pif_id) THEN
            set msg = CONCAT('insurance #', NEW.pro_pif_id, ' not found!');
            SIGNAL SQLSTATE '45000'SET MESSAGE_TEXT = msg;
        END IF;
    END IF;

    -- 检查pro_type=3时pro_pif_id是否存在于fund
    IF NEW.pro_type = 3 THEN
        IF NOT EXISTS (SELECT 1 FROM fund WHERE f_id = NEW.pro_pif_id) THEN
            set msg = CONCAT('fund #', NEW.pro_pif_id, ' not found!');
            SIGNAL SQLSTATE '45000'SET MESSAGE_TEXT = msg;
        END IF;
    END IF;

END$$
 
delimiter ;
