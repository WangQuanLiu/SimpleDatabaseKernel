# SimpleDatabaseKernel
Implement a simple database kernel

1、这个项目大致是实现一个简易的数据库内核，可以实行简单的sql语句的查询，如数据库的创建、删除，表的创建、删除，以及插入语句等。
2、如果你对DFA，NFA，简易的文法翻译，B +树的实现，以及你也想要实现同类项目，那么这个项目可能会你有所帮助。


本项目仅支持简单的SQL语句,有如下   
the project support simple SQL statement,as follow   
create database id  创建库  
use id  使用库  
drop id  删除库  
create table id(  创建表   
id int,   
id float,  
id char( 数字)   最后一个不要有逗号，这是个BUG，因为时间原因，还未解决  
)  
仅支持int,float,char(数字)三种类型  
delete table id  删除表  
delete from id 删除数据  
where ….  
select *from  id,id...  查询  
select column_name,column_name where id compare_symob id logic id......   
update id  更新数据  
set column_id = values    
where column_id = values and ... operator = <= >= > <    
insert into id values(values,values...)  插入数据  
运行方式：  
在cmd上寻找程序文件，然后输入simpleDatabaseKernel -c 文件路径及名字   

running mode:  
First find program file in cmd ,and then input simpleDatabaserKernel -c file path and name  
