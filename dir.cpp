/*
Created by

计创16------陈楠------161002107

on 6 June.
*/

#include "filesystem.h"

node i_node[I_NODE_NUM];				//i节点
dir root[ROOT_NUM];					//文件所在块
char cur_dir[20] = "filsystem";	//当前目录

/*显示当前目录下的文件列表*/
void display_curdir(){
	int i, k;
	cout << "用户名：" << user_array[login_userid].username << endl;
	printf("\t\t文件名字\t文件类型\t文件长度\t 所属目录\n");
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(cur_dir, root[i].dir_name) == 0 && i_node[root[i].i_num].file_UserId == login_userid)   //查询文件中 所在目录信息和当前目录信息相同的数据
		{
			k = root[i].i_num;
			printf("\t\t%8s  ", root[i].file_name);	//文件名
			printf(i_node[k].file_style? "\tregular  \t" :"\tdirectory\t");		//文件的类型
			printf("%8d\t", i_node[k].file_length);		//文件的长度
			printf("%10s\n", root[i].dir_name);			//文件所在的目录
		}
	}
}

/*进入指定的目录*/
void display_dir(char filename[])
{
	int i, k;
	for (i = 0; i<ROOT_NUM; i++)
	{
		k = root[i].i_num;     
		
		//判断文件类型是不是目录类型
		if ((strcmp(filename, root[i].file_name) == 0) && (i_node[k].file_style == 0) && (i_node[k].file_UserId == login_userid))
		{
			strcpy(cur_dir, filename);  //将要进入的指定目录设置为当前目录  赋值不要反了strcpy(目的，源)
			return;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("登录用户没有这个目录\n");
	}
}

/*返回上一级目录*/
void back_dir(){
	int  i, k;
	for (i = 0; i<ROOT_NUM; i++)       //查询和当前目录名相同的目录文件名
	{
		k = root[i].i_num;
		if (strcmp(cur_dir, root[i].file_name) == 0 && (i_node[k].file_style == 0))
		{
			strcpy(cur_dir, root[i].dir_name); //将查询到的目录文件名  所在的目录赋值给当前目录
		}
	}
}

/*创建目录*/
void create_dir(char filename[]){
	style = 0;         //0代表文件类型是目录文件
	create_file(filename, 4, login_userid, "o+r+w");
	style = 1;         //用完恢复初值
}



/*删除目录*/
void del_dir(char filename[]){
	int i, j, k;
	for (i = 0; i<ROOT_NUM; i++)       //判断要删除的目录是不是当前目录
	{
		k = root[i].i_num;      //找到目录名字
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(cur_dir, filename) != 0 && (i_node[k].file_style) == 0)
		{
			for (j = 0; j<ROOT_NUM; j++)
			{
				if (strcmp(filename, root[j].dir_name) == 0)
				{
					printf("目录不为空不能直接删除\n");
					return;
				}
			}
			if (j == ROOT_NUM && i_node[root[i].i_num].file_UserId == login_userid)
			{
				del_file(filename);
				return;
			}
			break;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("这个不是目录文件 或者已登录用户不存在这个目录,或者你要删除的是当前目录\n");
	}
}
