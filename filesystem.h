/*
Created by

�ƴ�16------���------161002107

on 6 June.
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <iostream>
using namespace std;
#define CMD_NUM 28			//�������
#define MEMORY_NUM 20449	//�ڴ�����
#define I_NODE_NUM 640		//i_node������
#define ROOT_NUM 640		//Ŀ¼���ļ�����
#define USER_NUM 8			//����û���

//����
struct command{
	char com[10];
};

//�̿���Ϣ��1KB/�飩
struct block
{
	int n;				//��ſ����̿�ĸ���
	int free[50];		//��ſ����̿�ĵ�ַ
	int a;				//�̿��Ƿ�ռ�ñ�־
	char content[1000];	//����ÿ���ֽڴ�ŵķ���
};

//������
struct block_super{
	int n;			 //���е��̿�ĸ���
	int free[50];    //��Ž���ջ�еĿ��п�					
};

//i�����Ϣ��32B/i�ڵ㣩
struct node{
	int file_style;				 //i��� �ļ�����
	int file_length;			 //i��� �ļ�����
	int file_address[100];		 //�ļ�ռ�õ������š�
	char limit[20];				 //�򿪶�дȨ�ޣ�0��ʾ�ܴ򿪶�д��1��ʾ�ܴ򿪶���2��ʾ�ܴ�д��3��ʾֻ�ܴ�
	int file_UserId;			//�û�id
};

//�û���Ϣ
struct user {
	char username[20];
	char password[20];
} ;

//Ŀ¼���ļ���
struct dir{
	char file_name[20];		 //�ļ���
	int  i_num;				 //�ļ��Ľ���
	char dir_name[20];		 //Ŀ¼������˵�ļ�����Ŀ¼
};

extern int user_num;				//��ע���û�����
extern int login_userid;			//��ǰ��¼���û�ID
extern string cur_user;				//��ǰ�û�
extern int file_array[8];			// ���ļ�����
extern int file_array_head;			//�ļ�����ͷ
extern int physic[100];				//�ļ���ַ������
extern int style;					//�ļ�������
extern char cur_dir[20];			//��ǰĿ¼
extern string temp_write;			//��ʱ�ļ�����
extern string copy_temp_write;			//��ʱ�ļ�����
extern node temp_file;			//��ʱ�ļ�


extern command cmd[CMD_NUM];		//����
extern block memory[MEMORY_NUM];	//�ڴ��
extern block_super super_block;		//������ 
extern node i_node[I_NODE_NUM];		//i_node���
extern user user_array[USER_NUM];	//�û�
extern dir root[ROOT_NUM];			//�ļ���Ŀ¼

/*��������*/
extern void export_file(string filename,string newtext);	//�����ļ�
extern void import_file(string filename,string newtext);	//�����ļ�
extern void move_file(char filename[20]);					//�ƶ��ļ�
extern void ver_info();										//��ʾϵͳ��Ϣ
extern bool rename(char filename[20],string new_name);		//�ļ�������
extern bool is_open(char filename[20]);						//�ж��ļ��Ƿ��
extern void init_cmd(command*);							//�����ʼ��
extern int find_cmd(string,int,int,command*);			//���������±�
extern void del_dir(char filename[]);					//ɾ��Ŀ¼
extern void back_dir();									//������һ��
extern void create_dir(char filename[]);				//����Ŀ¼
extern void display_curdir();							//��ʾ��ǰĿ¼�µ��ļ��б�
extern void display_dir(char filename[]);				//����ָ����Ŀ¼
extern void close(char filename[20]);					//�ر��ļ�
extern void del_file(char filename[]);					//ɾ���ļ�
extern int open(char filename[20]);						//���ļ�
extern void copy(char filename[20]);					//�����ļ�
extern void paste(char filename[20]);					//ճ���ļ�
extern int read(char filename[20]);						//��ȡ�ļ�����
extern void show_file_content();						//��ʾ�ļ�����
extern void show_file(char filename[]);					//��ʾ�ļ���Ϣ
extern void help();										//�������
extern void attrib_file(char filename[],string);		//�����ļ�����
extern void display_sys();								//��ʾϵͳ��Ϣ������ʹ�������
extern void read_file(FILE *fp);						//����ϵͳ�ļ�����Ϣ
extern void write_file(FILE *fp);						//����Ϣд��ϵͳ�ļ�
extern int login();										//��½
extern void logout();									//�ǳ�
extern void reg();										//ע��
extern void format();									//��ʼ��
extern void allot(int length);							//����ռ�
extern void callback(int length);						//���տռ�
extern void write(char filename[20], string writec,int choice);//д���ļ�
extern void create_file(char filename[], int length, int userid, string limit); //�����ļ�