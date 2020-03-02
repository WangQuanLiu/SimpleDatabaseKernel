# SimpleDatabaseKernel
Implement a simple database kernel

1、这个项目大致是实现一个简易的数据库内核，可以实行简单的sql语句的查询，如数据库的创建、删除，表的创建、删除，以及插入语句等。
2、如果你对DFA，NFA，简易的文法翻译，B +树的实现，以及你也想要实现同类项目，那么这个项目可能会你有所帮助。

1.This Project is implement a simple database kernel. It can  execution of simplely sql statement,for example create,delete of database ,create,delete,constraint and insert of table.
2.if you want to learn DFA,NFA,simple grammar translate,implement of B+ tree or you want to implement to analogous the project then the project wile be help to you.
本项目仅支持简单的SQL语句,有如下   
the project support simple SQL statement,as follow   
create database id  
use database id  
drop id  
create table id(  
id int,  
id float,  
id char( )  
)  
drop table id  
select *from  id,id...  
update id  
set column_id = values  
where column_id = values and ... operator = <= >= > <  
insert into id values(values,values...)  
delete id from   
where ...  
运行方式：  
在cmd上寻找程序文件，然后输入simpleDatabaseKernel -c 文件路径及名字  
running mode:  
First find program file in cmd ,and then input simpleDatabaserKernel -c file path and name  
