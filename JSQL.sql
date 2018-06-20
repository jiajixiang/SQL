create database mybook;
use mybook;
show tables;
create table User(
id  char(8) primary key,
password    nvarchar(20),
IP nvarchar(20),
mac nvarchar(30));
show tables;
insert into User(id,password) value('admin','247');
select * from User;
desc User;
desc video;
create table video(
Bno int primary key,
Title   nvarchar(40), -- 名称
Category    nvarchar(10), -- 类别
Press   nvarchar(30), -- 出版社名称
Added_Time  nvarchar(50), -- 添加时间
Author  nvarchar(20), -- 作者
Url nvarchar(50) -- 链接
);
desc video;
create table Borrow_records(
BRno int primary key,
Btime Varchar(50),
Etime Varchar(50),
who char(8)
); 
select id,password from User where id='123';
select id,password from User where id='admin';
CREATE USER 'pig'@'%' IDENTIFIED BY '123456';
grant select, insert, update, delete on mybook.* to pig@'%';
show grants for pig;
GRANT SELECT, INSERT,UPDATE ON snake.* TO 'pig'@'%';
GRANT SELECT, INSERT,UPDATE,delete ON mybook.* TO 'pig'@'%';
show tables;
alter table video change Bno Bno int integer primary key;
alter table  video modify Bno integer auto_increment ; 
select * from video;
alter table video change Url Url nvarchar(150);

insert into video values(12,'爱情三脚猫','动漫','爱情公寓','2017-12-17','关谷神奇','www.jixiang-year.cn');