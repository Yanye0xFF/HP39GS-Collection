//hp39gs土星文件目录名
/*
'calcdir //计算器根目录
'pgmdir  //PROGRAM目录，存储用户编辑的BASIC程序
'notesdir  //NOTEPAD目录，存储用户编辑的记事本文本
'apletdir //APLET目录，存储下载/创建的应用程序
*/

//使用简介
#include <satdir.h>

//这里的'需要使用转义字符/'替代
SAT_DIR_NODE *dir = _sat_find_path("/'calcdir");

//结构体介绍

typedef
struct _sat_dir_node {
        char *name;
        struct _sat_dir_node *parent,*sibling,*child;
        struct _sat_dir_entry *object;
} SAT_DIR_NODE;

//目录名称，与_sat_find_path传入参数相同
//即调用_sat_find_path("/'calcdir")
//返回的SAT_DIR_NODE *dir->name也为'calcdir
char *name;
             
//同样为SAT_DIR_NODE结构体的父目录(文件夹)、同级目录、子目录指针
struct _sat_dir_node *parent,*sibling,*child;

//该目录下的文件，(不包含文件夹！)
struct _sat_dir_entry *object;

//SAT_DIR_ENTRY由单链表形式存储
typedef
struct _sat_dir_entry {
        SAT_OBJ_DSCR *sat_obj;       
		struct _sat_dir_entry *next;
} SAT_DIR_ENTRY;

//文件对象信息
SAT_OBJ_DSCR *sat_obj;  
//下一个文件实体
struct _sat_dir_entry *next;


//文件对象描述信息
typedef
struct _sat_obj_dscr {
    char *name;
    unsigned addr;
} SAT_OBJ_DSCR;


//文件名称，与显示的名称不同的是*(name + 0)存在一个 ' 符号
//在实际代码中获取文件名请从*(name + 1)开始读取
char *name;

//文件地址指针，通常为5个半字(nibbles)
//即2个半字节
//注意addr为半字移动
unsigned addr;

//读取到SAT_OBJ_DSCR后，使用sat_peek即可打开该文件内容
//注意：由于土星为4位cpu，每次读取只能读半字，即4位

//读取土星指定地址内容
//@param sat_addr 对象地址
//@param nibbles 读取数量(单位为半字节)
//@return 数据
unsigned sat_peek(int sat_addr,int nibbles);

return ((int) sat_peek_sat_addr(sat_addr + 5) - 5) / 2;
//2c 2a b0 35 00

//sat文件结构
//小端模式,一次读取半字，每隔一字添加空格
/*
sample
此处测试文件大小为0x1AB即427字节
(注意：文件大小是文件内容本身,不包含"HP39AscC"这些描述信息,该描述信息以0x0D 0x0A结尾)
即文件内容是0x0D 0x0A 后面的字节

文件前10字节
字节小端模式   |  字节大端模式
c2 a2 0b 53 00 |  2c 2a b0 35 00

前五半字表示文件类型
c2 a2 0 表明该文件为NOTEPAD文件

后五半字为文件大小(注意：此处文件大小为字节数而不是半字数！)

文件大小算法
将后前10字节的5字节合成int
即 b 53 00 转换成大端模式为 0x0035b 为859
文件大小 = (0x0035b - 0x5) >> 1
         = 1AB
与上文文件大小相符
*/

