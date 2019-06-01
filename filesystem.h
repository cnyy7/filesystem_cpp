/*
Created by

计创16------陈楠------161002107

on 6 June.
*/
#pragma once

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <iostream>

using namespace std;
#define CMD_NUM 28            //命令个数
#define MEMORY_NUM 20449    //内存块个数
#define I_NODE_NUM 640        //i_node结点个数
#define ROOT_NUM 640        //目录、文件个数
#define USER_NUM 8            //最大用户数

//命令
struct command {
    char com[10];
};

//盘块信息（1KB/块）
struct block {
    int n;                //存放空闲盘块的个数
    int free[50];        //存放空闲盘块的地址
    int a;                //盘块是否被占用标志
    char content[1000];    //块上每个字节存放的符号
};

//超级块
struct block_super {
    int n;             //空闲的盘块的个数
    int free[50];    //存放进入栈中的空闲块
};

//i结点信息（32B/i节点）
struct node {
    int file_style;                 //i结点 文件类型
    int file_length;             //i结点 文件长度
    int file_address[100];         //文件占用的物理块号。
    char limit[20];                 //打开读写权限，0表示能打开读写，1表示能打开读，2表示能打开写，3表示只能打开
    int file_UserId;            //用户id
};

//用户信息
struct user {
    char username[20];
    char password[20];
};

//目录、文件项
struct dir {
    char file_name[20];         //文件名
    int i_num;                 //文件的结点号
    char dir_name[20];         //目录名或者说文件所在目录
};

extern int user_num;                //已注册用户数量
extern int login_userid;            //当前登录的用户ID
extern string cur_user;                //当前用户
extern int file_array[8];            // 打开文件表组
extern int file_array_head;            //文件表组头
extern int physic[100];                //文件地址缓冲区
extern int style;                    //文件的类型
extern char cur_dir[20];            //当前目录
extern string temp_write;            //临时文件内容
extern string copy_temp_write;            //临时文件内容
extern node temp_file;            //临时文件


extern command cmd[CMD_NUM];        //命令
extern block memory[MEMORY_NUM];    //内存块
extern block_super super_block;        //超级块
extern node i_node[I_NODE_NUM];        //i_node结点
extern user user_array[USER_NUM];    //用户
extern dir root[ROOT_NUM];            //文件、目录

/*函数定义*/
extern void export_file(const string &filename, string newtext);    //导出文件
extern void import_file(const string &filename, const string &newtext);    //导入文件
extern void move_file(char filename[20]);                    //移动文件
extern void ver_info();                                        //显示系统信息
extern bool rename(char filename[20], const string &new_name);        //文件重命名
extern bool is_open(char filename[20]);                        //判断文件是否打开
extern void init_cmd(command *);                            //命令初始化
extern int find_cmd(const string &, int, int, command *);            //返回命令下标
extern void del_dir(char filename[]);                    //删除目录
extern void back_dir();                                    //返回上一级
extern void create_dir(char filename[]);                //创建目录
extern void display_curdir();                            //显示当前目录下的文件列表
extern void display_dir(char filename[]);                //进入指定的目录
extern void close(char filename[20]);                    //关闭文件
extern void del_file(char filename[]);                    //删除文件
extern int open(char filename[20]);                        //打开文件
extern void copy(char filename[20]);                    //复制文件
extern void paste(char filename[20]);                    //粘贴文件
extern int read(char filename[20]);                        //读取文件内容
extern void show_file_content();                        //显示文件内容
extern void show_file(char filename[]);                    //显示文件信息
extern void help();                                        //命令帮助
extern void attrib_file(char filename[], const string &);        //更改文件属性
extern void display_sys();                                //显示系统信息（磁盘使用情况）
extern void read_file(FILE *fp);                        //读出系统文件的信息
extern void write_file(FILE *fp);                        //将信息写入系统文件
extern int login();                                        //登陆
extern void logout();                                    //登出
extern void reg();                                        //注册
extern void format();                                    //初始化
extern void allot(int length);                            //分配空间
extern void callback(int length);                        //回收空间
extern void write(char filename[20], string writec, int choice);//写入文件
extern void create_file(char filename[], int length, int userid, const string &limit); //创建文件
#endif //FILESYSTEM_FILESYSTEM_H
