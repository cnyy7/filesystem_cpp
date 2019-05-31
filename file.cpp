/*
Created by

�ƴ�16------���------161002107

on 6 June.
*/

#include "filesystem.h"

int style = 1;			//�ļ�������
int file_array_head;	//�ļ�����ͷ
int physic[100];		//�ļ���ַ������
string cur_user;		//��ǰ�û�
int file_array[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };  //���ļ�����
node temp_file;
string temp_write;
string copy_temp_write;
//char cur_dir[10];

/*�����ļ�*/
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
		cout << "�����ļ�ʧ�ܡ�" << endl;
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

/*�����ļ�*/
void import_file(string filename,string new_text)
{
	char file[20];
	strcpy(file, filename.c_str());
	create_file(file, new_text.length() / 1000 + 3, login_userid, "r+w+o");
	open(file);
	write(file, new_text, 1);
	close(file);
}

/*�ƶ��ļ�*/
void move_file(char filename[20])
{
	copy(filename);
	del_file(filename);
}

/*�����ļ�*/
void create_file(char filename[], int length, int userid, string limit)
{
	int i, j;
	for (i = 0; i<ROOT_NUM; i++)
	{
		//�ж�����
		if (strcmp(filename, root[i].file_name) == 0 && strcmp(cur_dir, root[i].dir_name) == 0)
		{
			printf("�Ѿ�����ͬ���ļ������������������ļ�\n");
			return;
		}
	}
	for (i = 0; i<ROOT_NUM; i++)
	{
		//�ҵ����п�
		if (root[i].i_num == -1)
		{
			root[i].i_num = i;
			strcpy(root[i].file_name, filename);
			strcpy(root[i].dir_name, cur_dir);  //�ѵ�ǰĿ¼�� ���½������ļ�
			i_node[i].file_style = style;//style==0 ˵���ļ���Ŀ¼�ļ�
			i_node[i].file_length = length;
			strcpy(i_node[i].limit , limit.c_str());
			i_node[i].file_UserId = userid; 
			allot(length);
			for (j = 0; j<length; j++)
			{
				i_node[i].file_address[j] = physic[j];
			}

			//��ʼ���ļ�
			for (int add = 0; add < 100; add++)
				for (int c = 0; c < length; c++) {
					memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
				}
			int u;
			for (u = 0; u<100; u++)//��������ջ�����
			{
				physic[u] = -1;
			}
			break;
		}
	}
}

/*ɾ���ļ�*/
void del_file(char filename[])     
{
	int i, j, k;
	for (i = 0; i<ROOT_NUM; i++)
	{

		if ((strcmp(filename, root[i].file_name) == 0) && (strcmp(cur_dir, root[i].dir_name) == 0) && (i_node[root[i].i_num].file_UserId == login_userid))
		{
			int add, c;
			for (add = 0; add<i_node[root[i].i_num].file_length; add++)//�ļ��������
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
			callback(i_node[k].file_length); //���� ���պ���
			int u;//��������ջ�����
			for (u = 0; u<100; u++)
			{
				physic[u] = -1;
			}
			for (j = 0; j<100; j++)     //ɾ���ļ���Ҫ���ļ����Ժ�Ŀ¼��ĸ���ֵ�ָ���ֵ
			{
				i_node[k].file_address[j] = -1; //�ļ�ռ�õĿ�ŵ�ַ�ָ���ֵ
			}
			strcpy(root[i].file_name, "");  //�ļ����ָ���ֵ
			root[i].i_num = -1;				//Ŀ¼���I�����Ϣ�ָ���ֵ
			strcpy(root[i].dir_name, "");	//Ŀ¼����ļ�Ŀ¼��Ϣ�ָ���ֵ
			i_node[k].file_length = -1;		//�ļ����Ȼָ�
			i_node[k].file_style = -1;		//�ļ����ͻָ���ֵ
			break;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("��¼�û��ĸ�Ŀ¼�²���������ļ�\n");
	}
}

/*���ļ�*/
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
				printf("�򿪵��ļ��Ѵ����ޣ��޷��򿪱��ļ�\n");
			}
			return root[i].i_num;
		}
	}
	if (i = ROOT_NUM)
	{
		printf("��Ҫ�򿪵��ļ������ڻ����ڸ��û�\n");
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
		printf("��Ҫ�������Ե��ļ������ڻ����ڸ��û�\n");
	}
	return;
}

/*�ļ�������*/
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
		printf("û������ļ���");
		return false;
	}
	return false;
}

/*�ļ��Ƿ��*/
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

/*�ر��ļ�*/
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
				printf("��Ҫ�رյ��ļ�δ�򿪹���\n");
			}
			return;
		}
	}
	if (i = 640)
	{
		printf("��Ҫ�رյ��ļ������ڻ����ڸ��û�\n");
	}
	return;
}

/*��ȡ�ļ�*/
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
						printf("��û��Ȩ�޶�ȡ�ļ����ݣ���\n");
						return 1;
					}
					return 0;
				}
			}
			if (j == 8)
			{
				printf("\n  ���ļ�δ�򿪣����ȴ��ļ��ٽ��ж�д����!!\n");
				return 1;
			}
			return 0;
		}
	}
	if (i == 640)
	{
		printf("��Ҫ��ȡ���ļ�������\n");
		return 1;
	}
	return 0;
}

void show_file_content() 
{
	cout << "�ļ�����Ϊ��";
	cout << temp_write << endl;
}

/*д���ļ�*/
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
							printf("\n�ļ��ռ�������д��ʧ�ܣ���\n");
						}
						return;
					}
					else
					{
						printf("��û��Ȩ�޽�����д���ļ�����\n");
						return;
					}
					return;
				}
			}
			if (j == 8)
			{
				printf("\n  ���ļ�δ�򿪣����ȴ��ļ��ٽ��ж�д����!!\n");
			}
			return;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("��Ҫд����ļ�������\n");
	}
	return;
}

/*��ʾ�ļ���Ϣ*/
void show_file(char filename[])
{
	int i, j, k;
	
	for (i = 0; i<ROOT_NUM; i++)
	{
		k = root[i].i_num;
		if (strcmp(filename, root[i].file_name) == 0 && strcmp(cur_dir, root[i].dir_name) == 0 && (i_node[k].file_style == 1))
		{
			printf("\t\t�ļ�����\t�ļ�����\t�ļ�����\t��ȡȨ��\t����Ŀ¼\t�����û�\n");
			printf("\t\t  %s\t", root[i].file_name);	//�ļ���
			//printf("\t%d\t", i_node[k].file_style);		//�ļ�������
			printf(i_node[k].file_style ? "\tregular  \t" : "\tdirectory\t");		//�ļ�������
			printf("%8d\t", i_node[k].file_length);		//�ļ��ĳ���
			cout << i_node[k].limit << "\t\t";
			printf("%8s\t", root[i].dir_name);			//�ļ����ڵ�Ŀ¼
			cout << cur_user << endl;
			printf("\t\t�ļ�ռ�õ������ַ\n\t\t");
			for (j = 0; j<i_node[k].file_length; j++)   //��ʾ�����ַ
			{
				printf("%d  ", i_node[k].file_address[j]); //�ļ�����ռ�õ��̿��
			}
			printf("\n");
			break;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("û������ļ� ��������ļ����������ļ�\n");
	}
}

/*�����ļ�*/
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

/*ճ��*/
void paste(char filename[20])
{
	create_file(filename, temp_file.file_length, login_userid, temp_file.limit);
	open(filename);
	write(filename, copy_temp_write,1);
	close(filename);
}