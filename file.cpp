/*
Created by

计创16------陈楠------161002107

on 6 June.
*/

#include "filesystem.h"

int style = 1;			//文件的类型
int file_array_head;	//文件表组头
int physic[100];		//文件地址缓冲区
string cur_user;		//当前用户
int file_array[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };  //打开文件表组
node temp_file;
string temp_write;
string copy_temp_write;
//char cur_dir[10];

/*导出文件*/
void export_file(string filename, string source)
{
	if (source[source.length()-1]!='/')
	{
		source.append("/");
	}
	source += filename;
	if (filename.find(".txt") == filename.npos)
		source += ".txt";
	fstream outfile(source.c_str(), ios::out);
	if (!outfile.is_open())
	{
		cout << "导出文件失败。" << endl;
		return;
	}
	char file[20];
	strcpy(file, filename.c_str());
	open(file);
	read(file);
	close(file);
	outfile << temp_write;
	outfile.close();
	return;
}

/*导入文件*/
void import_file(string filename,string new_text)
{
	char file[20];
	strcpy(file, filename.c_str());
	create_file(file, new_text.length() / 1000 + 3, login_userid, "r+w+o");
	open(file);
	write(file, new_text, 1);
	close(file);
}

/*移动文件*/
void move_file(char filename[20])
{
	copy(filename);
	del_file(filename);
}

/*创建文件*/
void create_file(char filename[], int length, int userid, string limit)
{
	int i, j;
	for (i = 0; i<ROOT_NUM; i++)
	{
		//判断重名
		if (strcmp(filename, root[i].file_name) == 0 && strcmp(cur_dir, root[i].dir_name) == 0)
		{
			printf("已经存在同名文件，不允许建立重名的文件\n");
			return;
		}
	}
	for (i = 0; i<ROOT_NUM; i++)
	{
		//找到空闲块
		if (root[i].i_num == -1)
		{
			root[i].i_num = i;
			strcpy(root[i].file_name, filename);
			strcpy(root[i].dir_name, cur_dir);  //把当前目录名 给新建立的文件
			i_node[i].file_style = style;//style==0 说明文件是目录文件
			i_node[i].file_length = length;
			strcpy(i_node[i].limit , limit.c_str());
			i_node[i].file_UserId = userid; 
			allot(length);
			for (j = 0; j<length; j++)
			{
				i_node[i].file_address[j] = physic[j];
			}

			//初始化文件
			for (int add = 0; add < 100; add++)
				for (int c = 0; c < length; c++) {
					memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
				}
			int u;
			for (u = 0; u<100; u++)//分配完清空缓冲区
			{
				physic[u] = -1;
			}
			break;
		}
	}
}

/*删除文件*/
void del_file(char filename[])     
{
	int i, j, k;
	for (i = 0; i<ROOT_NUM; i++)
	{

		if ((strcmp(filename, root[i].file_name) == 0) && (strcmp(cur_dir, root[i].dir_name) == 0) && (i_node[root[i].i_num].file_UserId == login_userid))
		{
			int add, c;
			for (add = 0; add<i_node[root[i].i_num].file_length; add++)//文件内容清空
			{
				for (c = 0; memory[i_node[root[i].i_num].file_address[add]].content[c] != '\0'; c++)
				{
					memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
				}
			}
			temp_write = "";
			k = root[i].i_num; 
			i_node[k].file_UserId = -1;
			strcpy(i_node[k].limit , "");
			for (j = 0; j<i_node[k].file_length; j++)
			{
				physic[j] = i_node[k].file_address[j];
			}
			callback(i_node[k].file_length); //调用 回收函数
			int u;//回收完清空缓存区
			for (u = 0; u<100; u++)
			{
				physic[u] = -1;
			}
			for (j = 0; j<100; j++)     //删除文件后要将文件属性和目录项的各个值恢复初值
			{
				i_node[k].file_address[j] = -1; //文件占用的块号地址恢复初值
			}
			strcpy(root[i].file_name, "");  //文件名恢复初值
			root[i].i_num = -1;				//目录项的I结点信息恢复初值
			strcpy(root[i].dir_name, "");	//目录项的文件目录信息恢复初值
			i_node[k].file_length = -1;		//文件长度恢复
			i_node[k].file_style = -1;		//文件类型恢复初值
			break;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("登录用户的该目录下不存在这个文件\n");
	}
}

/*打开文件*/
int open(char filename[20])
{
	int i;
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(root[i].dir_name, cur_dir) == 0 && i_node[root[i].i_num].file_style == 1 && i_node[root[i].i_num].file_UserId == login_userid)
		{
			if (file_array_head<8)
			{
				file_array[file_array_head] = root[i].i_num;
				file_array_head++;
			}
			else
			{
				printf("打开的文件已达上限，无法打开本文件\n");
			}
			return root[i].i_num;
		}
	}
	if (i = ROOT_NUM)
	{
		printf("您要打开的文件不存在或不属于该用户\n");
	}
	return 0;
}
void attrib_file(char filename[],string new_property)
{
	int i;
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(root[i].dir_name, cur_dir) == 0 && i_node[root[i].i_num].file_style == 1 && i_node[root[i].i_num].file_UserId == login_userid)
		{
			cout << ""<<endl;
			strcpy(i_node[root[i].i_num].limit , new_property.c_str());
			return;
		}
	}
	if (i = ROOT_NUM)
	{
		printf("您要更改属性的文件不存在或不属于该用户\n");
	}
	return;
}

/*文件重命名*/
bool rename(char filename[20], string new_name)
{
	int i, k;

	for (i = 0; i < ROOT_NUM; i++)
	{
		k = root[i].i_num;
		if (strcmp(filename, root[i].file_name) == 0 && strcmp(cur_dir, root[i].dir_name) == 0 && (i_node[k].file_style == 1))
		{
			strcpy(root[i].file_name, new_name.c_str());
			return true;
		}
	}
	if (i = ROOT_NUM)
	{
		printf("没有这个文件。");
		return false;
	}
	return false;
}

/*文件是否打开*/
bool is_open(char filename[20])
{
	int i;
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(root[i].dir_name, cur_dir) == 0 && i_node[root[i].i_num].file_style == 1 && i_node[root[i].i_num].file_UserId == login_userid)
		{
			int j;
			for (j = 0; j<file_array_head; j++)
			{
				if (root[i].i_num == file_array[j])
				{
					
					return true;
				}
			}
			if (j == file_array_head)
			{
				return false;
			}
		}
	}
	if (i = ROOT_NUM)
	{
		return false;
	}
	return false;
}

/*关闭文件*/
void close(char filename[20])
{
	int i;
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(root[i].dir_name, cur_dir) == 0 && i_node[root[i].i_num].file_style == 1 && i_node[root[i].i_num].file_UserId == login_userid)
		{
			int j;
			for (j = 0; j<file_array_head; j++)
			{
				if (root[i].i_num == file_array[j])
				{
					int m;
					for (m = j; m<file_array_head; m++)
					{
						file_array[m] = file_array[m + 1];
					}
					file_array_head--;
					return;
				}
			}
			if (j == file_array_head)
			{
				printf("您要关闭的文件未打开过！\n");
			}
			return;
		}
	}
	if (i = 640)
	{
		printf("您要关闭的文件不存在或不属于该用户\n");
	}
	return;
}

/*读取文件*/
int read(char filename[20])
{
	int i;
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(root[i].dir_name, cur_dir) == 0 && i_node[root[i].i_num].file_style == 1)
		{
			int j;
			for (j = 0; j<8; j++)
			{          
				if (root[i].i_num == file_array[j])
				{
					string temp = i_node[root[i].i_num].limit;
					if (temp.find('r')!=temp.npos)
					{
						int  add;
						temp_write.clear();
						for (add = 0; add < i_node[root[i].i_num].file_length; add++)
						{
							string temp_str= memory[i_node[root[i].i_num].file_address[add]].content;
							if (temp_str.length() == 0)
								break;
							temp_write += temp_str;
						}
						printf("\n ");
					}
					else
					{
						printf("你没有权限读取文件内容！！\n");
						return 1;
					}
					return 0;
				}
			}
			if (j == 8)
			{
				printf("\n  该文件未打开，请先打开文件再进行读写操作!!\n");
				return 1;
			}
			return 0;
		}
	}
	if (i == 640)
	{
		printf("您要读取的文件不存在\n");
		return 1;
	}
	return 0;
}

void show_file_content() 
{
	cout << "文件内容为：";
	cout << temp_write << endl;
}

/*写入文件*/
void write(char filename[20], string writec,int choice)
{
	int i;
	bool t = true;
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(root[i].dir_name, cur_dir) == 0 && i_node[root[i].i_num].file_style == 1)
		{
			int j; 
			for (j = 0; j<8; j++)
			{
				if (root[i].i_num == file_array[j])
				{
					string temp = i_node[root[i].i_num].limit;
					if (temp.find('w') != temp.npos)
					{
						int c, add, write_length = 0;
						for (add = 0; add < i_node[root[i].i_num].file_length; add++)
						{
							for (c = 0; c<1000; c++)
							{
								if (choice)
								{
									if (memory[i_node[root[i].i_num].file_address[add]].content[c] == '\0')
									{
										for (/*write_length = 0*/; write_length < writec.length() && c<1000; c++, write_length++) 
										{
											memory[i_node[root[i].i_num].file_address[add]].content[c] = writec[write_length];
										}
										if(write_length == writec.length())
											return;
									}
								}
								else
								{
									for (/*write_length = 0*/; write_length < writec.length() && c<1000; c++, write_length++)
									{
										memory[i_node[root[i].i_num].file_address[add]].content[c] = writec[write_length];
									}
									for (; c<1000; c++)
									{
										memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
									}
									if (t)
									{
										t = false;
										for (int k = add + 1; k < i_node[root[i].i_num].file_length; k++)
										{
											for (c = 0; c < 1000; c++)
											{
												memory[i_node[root[i].i_num].file_address[k]].content[c] = '\0';
											}
										}
									}
									if (write_length == writec.length())
										return;
								}
							}
						}
						if (add == i_node[root[i].i_num].file_length)
						{
							printf("\n文件空间已满，写入失败！！\n");
						}
						return;
					}
					else
					{
						printf("你没有权限将内容写入文件！！\n");
						return;
					}
					return;
				}
			}
			if (j == 8)
			{
				printf("\n  该文件未打开，请先打开文件再进行读写操作!!\n");
			}
			return;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("您要写入的文件不存在\n");
	}
	return;
}

/*显示文件信息*/
void show_file(char filename[])
{
	int i, j, k;
	
	for (i = 0; i<ROOT_NUM; i++)
	{
		k = root[i].i_num;
		if (strcmp(filename, root[i].file_name) == 0 && strcmp(cur_dir, root[i].dir_name) == 0 && (i_node[k].file_style == 1))
		{
			printf("\t\t文件名字\t文件类型\t文件长度\t读取权限\t所属目录\t所属用户\n");
			printf("\t\t  %s\t", root[i].file_name);	//文件名
			//printf("\t%d\t", i_node[k].file_style);		//文件的类型
			printf(i_node[k].file_style ? "\tregular  \t" : "\tdirectory\t");		//文件的类型
			printf("%8d\t", i_node[k].file_length);		//文件的长度
			cout << i_node[k].limit << "\t\t";
			printf("%8s\t", root[i].dir_name);			//文件所在的目录
			cout << cur_user << endl;
			printf("\t\t文件占用的物理地址\n\t\t");
			for (j = 0; j<i_node[k].file_length; j++)   //显示物理地址
			{
				printf("%d  ", i_node[k].file_address[j]); //文件具体占用的盘块号
			}
			printf("\n");
			break;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("没有这个文件 或者这个文件不是正规文件\n");
	}
}

/*复制文件*/
void copy(char filename[20]) 
{
	int i;
	open(filename);
	read(filename);
	close(filename);
	copy_temp_write = temp_write;
	for ( i= 0; i < ROOT_NUM; i++) 
	{
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(root[i].dir_name, cur_dir) == 0 && i_node[root[i].i_num].file_style == 1)
			temp_file = i_node[root[i].i_num];
	}
}

/*粘贴*/
void paste(char filename[20])
{
	create_file(filename, temp_file.file_length, login_userid, temp_file.limit);
	open(filename);
	write(filename, copy_temp_write,1);
	close(filename);
}