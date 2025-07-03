# 第1关：备份与恢复
# src/test1/test1_1.sh
mysqldump -h127.0.0.1 -uroot --databases residents > residents_bak.sql
# src/test1/test1_2.sh
mysql -h127.0.0.1 -uroot < residents_bak.sql



# 第2关：备份+日志：介质故障的发生与数据库的恢复
# src/test2/test2_1.sh
mysqldump -h127.0.0.1 -uroot --flush-logs --databases train > train_bak.sql
# src/test2/test2_2.sh
mysql -h127.0.0.1 -uroot < train_bak.sql
mysqlbinlog --no-defaults log/binlog.000018 | mysql -h127.0.0.1 -uroot