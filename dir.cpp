/*
Created by

�ƴ�16------���------161002107

on 6 June.
*/

#include "filesystem.h"

node i_node[I_NODE_NUM];				//i�ڵ�
dir root[ROOT_NUM];					//�ļ����ڿ�
char cur_dir[20] = "filsystem";	//��ǰĿ¼

/*��ʾ��ǰĿ¼�µ��ļ��б�*/
void display_curdir(){
	int i, k;
	cout << "�û�����" << user_array[login_userid].username << endl;
	printf("\t\t�ļ�����\t�ļ�����\t�ļ�����\t ����Ŀ¼\n");
	for (i = 0; i<ROOT_NUM; i++)
	{
		if (strcmp(cur_dir, root[i].dir_name) == 0 && i_node[root[i].i_num].file_UserId == login_userid)   //��ѯ�ļ��� ����Ŀ¼��Ϣ�͵�ǰĿ¼��Ϣ��ͬ������
		{
			k = root[i].i_num;
			printf("\t\t%8s  ", root[i].file_name);	//�ļ���
			printf(i_node[k].file_style? "\tregular  \t" :"\tdirectory\t");		//�ļ�������
			printf("%8d\t", i_node[k].file_length);		//�ļ��ĳ���
			printf("%10s\n", root[i].dir_name);			//�ļ����ڵ�Ŀ¼
		}
	}
}

/*����ָ����Ŀ¼*/
void display_dir(char filename[])
{
	int i, k;
	for (i = 0; i<ROOT_NUM; i++)
	{
		k = root[i].i_num;     
		
		//�ж��ļ������ǲ���Ŀ¼����
		if ((strcmp(filename, root[i].file_name) == 0) && (i_node[k].file_style == 0) && (i_node[k].file_UserId == login_userid))
		{
			strcpy(cur_dir, filename);  //��Ҫ�����ָ��Ŀ¼����Ϊ��ǰĿ¼  ��ֵ��Ҫ����strcpy(Ŀ�ģ�Դ)
			return;
		}
	}
	if (i == ROOT_NUM)
	{
		printf("��¼�û�û�����Ŀ¼\n");
	}
}

/*������һ��Ŀ¼*/
void back_dir(){
	int  i, k;
	for (i = 0; i<ROOT_NUM; i++)       //��ѯ�͵�ǰĿ¼����ͬ��Ŀ¼�ļ���
	{
		k = root[i].i_num;
		if (strcmp(cur_dir, root[i].file_name) == 0 && (i_node[k].file_style == 0))
		{
			strcpy(cur_dir, root[i].dir_name); //����ѯ����Ŀ¼�ļ���  ���ڵ�Ŀ¼��ֵ����ǰĿ¼
		}
	}
}

/*����Ŀ¼*/
void create_dir(char filename[]){
	style = 0;         //0�����ļ�������Ŀ¼�ļ�
	create_file(filename, 4, login_userid, "o+r+w");
	style = 1;         //����ָ���ֵ
}



/*ɾ��Ŀ¼*/
void del_dir(char filename[]){
	int i, j, k;
	for (i = 0; i<ROOT_NUM; i++)       //�ж�Ҫɾ����Ŀ¼�ǲ��ǵ�ǰĿ¼
	{
		k = root[i].i_num;      //�ҵ�Ŀ¼����
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(cur_dir, filename) != 0 && (i_node[k].file_style) == 0)
		{
			for (j = 0; j<ROOT_NUM; j++)
			{
				if (strcmp(filename, root[j].dir_name) == 0)
				{
					printf("Ŀ¼��Ϊ�ղ���ֱ��ɾ��\n");
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
		printf("�������Ŀ¼�ļ� �����ѵ�¼�û����������Ŀ¼,������Ҫɾ�����ǵ�ǰĿ¼\n");
	}
}
