/*
Created by

�ƴ�16------���------161002107

on 6 June.
*/

#include "filesystem.h"

command cmd[CMD_NUM];

/*����*/
void help(){
	printf("\n\n��ʼ��                        format\n");
	printf("�鿴��ǰĿ¼���ļ��б�        dir\n");
	printf("�鿴�ļ���Ϣ                  cat        (cat + �ļ���)  \n");
	printf("�鿴ϵͳ�ռ�ʹ����Ϣ          ls    \n");
	printf("����Ŀ¼                      md         (md  + Ŀ¼��)  \n");
	printf("�����ļ�                      touch      (touch  + �ļ��� + �ļ����� + Ȩ��)\n");
	printf("ɾ���ļ�                      del        (del + �ļ���) \n");
	printf("���ļ�                      open       (open + �ļ���) \n");
	printf("�����ļ�                      export     (export + �ļ��� + Ҫ�����ĵ�ַ) \n");
	printf("�����ļ�����                  rename     (rename + �ļ��� + ���ļ���) \n");
	printf("�����ļ�                      import     (import + Ҫ������ļ�) \n");
	printf("���ļ�                      open       (open + �ļ���) \n");
	printf("�ر��ļ�                      close      (close + �ļ���) \n");
	printf("��ȡ�ļ�                      read       (read + �ļ���) \n");
	printf("д���ļ�                      write      (write + �ļ��� + д�뷽ʽ(0:���ǣ�����1��׷��))\n");
	printf("�����ļ�                      copy       (copy + �ļ�����  \n");
	printf("�ƶ��ļ�                      move       (move + �ļ�����  \n");
	printf("ճ���ļ�                      paste      (paste + �ļ���)  \n");
	printf("ɾ��Ŀ¼                      rd         (rd + Ŀ¼��)\n");
	printf("�����ļ�Ȩ��                  attrib     (attrib + Ŀ¼��+Ȩ�ޣ�r,o,w��)\n");
	printf("���뵱ǰĿ¼�µ�ָ��Ŀ¼      cd         (cd + Ŀ¼��)\n");
	printf("������һ��Ŀ¼                cd..  \n");
	printf("��ʾʱ��                      time  \n");
	printf("��ʾϵͳ��Ϣ                  ver  \n");
	printf("��ʾ��������                  help  \n");
	printf("�˳��ļ�ϵͳ                  exit  \n");
	printf("�˳���¼                      logout\n");
	
}

/*��ʼ������*/
void init_cmd(command* cmd)
{
	strcpy(cmd[0].com, "attrib");
	strcpy(cmd[1].com, "cat");
	strcpy(cmd[2].com, "cd");
	strcpy(cmd[3].com, "cd..");
	strcpy(cmd[4].com, "close");
	strcpy(cmd[5].com, "copy");
	strcpy(cmd[6].com, "del");
	strcpy(cmd[7].com, "dir");
	strcpy(cmd[8].com, "exit");
	strcpy(cmd[9].com, "export");
	strcpy(cmd[10].com, "find");          //δʵ��
	strcpy(cmd[11].com, "format");
	strcpy(cmd[12].com, "help");
	strcpy(cmd[13].com, "import");
	strcpy(cmd[14].com, "logout");
	strcpy(cmd[15].com, "ls");            //
	strcpy(cmd[16].com, "md");
	strcpy(cmd[17].com, "more");
	strcpy(cmd[18].com, "move");
	strcpy(cmd[19].com, "open");
	strcpy(cmd[20].com, "paste");
	strcpy(cmd[21].com, "rd");
	strcpy(cmd[22].com, "read");
	strcpy(cmd[23].com, "rename");
	strcpy(cmd[24].com, "time");
	strcpy(cmd[25].com, "touch");
	strcpy(cmd[26].com, "ver");
	strcpy(cmd[27].com, "write");
	//strcpy(cmd[27].com, "xcopy");
}

/*���ֲ��ҷ��������±�*/
int find_cmd(string temp_cmd,int low,int high,command* com)
{
	int mid = (low + high) / 2;
	string temp = com[mid].com;
	if (low >=high)
		return -1;
	if (temp_cmd == temp)
		return mid;
	else if (temp_cmd < temp)
		return find_cmd(temp_cmd, low, mid, com);
	else
		return find_cmd(temp_cmd, mid+1, high, com);
}

/*������*/
int main()
{
	char tmp[20],  tmp1[20];
	struct command tmp2[10];
	int i, j = 0, p, len = 0;
	FILE *fp;
	//�����������������
	init_cmd(cmd);
	//��ʼ��
	if ((fp = fopen("filesave", "rb")) == NULL)   //�ж�ϵͳ�ļ��Ƿ����
	{
		cout << "���ڳ�ʼ��ϵͳ" << endl;
		format();
	}
	else
	{
		cout << "�����ļ�ϵͳ" << endl;
		read_file(fp);       //��ȡϵͳ�ļ�������
	}

	//ע���½
	while (1) {
		int log_com;
		cout << "1------��½------1" << endl;
		cout << "2------ע��------2" << endl;
		cin >> log_com;
		switch (log_com) 
		{
			case 1:login(); break;
			case 2:reg(); break;
			default:cout << "unknown command" << endl;
		}
		if (login_userid != -1)
			break;
	}
	write_file(fp);
	help();
	while (1)
	{
		j = 0;         //�������¸��ָ�0�������
		strcpy(tmp, cur_dir);
		while (strcmp(tmp, "filsystem") != 0)
		{
			for (i = 0; i<ROOT_NUM; i++)
			{
				p = root[i].i_num;
				if (strcmp(tmp, root[i].file_name) == 0 && (i_node[p].file_style == 0))
				{
					strcpy(tmp2[j].com, tmp);
					j++;
					strcpy(tmp, root[i].dir_name);
				}
			}
		}
		cout << endl;
			
		strcpy(tmp2[j].com, tmp);
		for (i = j; i >= 0; i--)
		{
			printf("%s>", tmp2[i].com);
		}
		string temp_cmd;
		cin >> temp_cmd;							//��������Ҳ����������ز���
		p = find_cmd(temp_cmd, 0, CMD_NUM, cmd);
		read_file(fp);								//��ȡϵͳ�ļ�������
		switch (p){
			case 11: {
				format();       //��ʼ��
				break;
			}
			case 7: {
				display_curdir();     //�鿴��ǰĿ¼�µ��ļ��б�
				break;
			}
			case 1: {
				scanf("%s", tmp);     //�鿴�ļ�
				show_file(tmp);
				break;
			}
			case 15: {
				display_sys();      //�鿴ϵͳ��Ϣ
				break; 
			}
			case 16: {
				scanf("%s", tmp);      //����Ŀ¼
				create_dir(tmp);
				break;
			}
			case 25: {
				scanf("%s", tmp);     //�����ļ�
				scanf("%d", &len);
				string limit;
				cin >> limit;
				create_file(tmp, len, login_userid, limit);
				break; 
			}
			case 6: {
				scanf("%s", tmp);     //ɾ���ļ�
				for (i = 0; i < ROOT_NUM; i++)     //�ж��ļ��ǲ��������ļ�
				{
					j = root[i].i_num;
					if (strcmp(tmp, root[i].file_name) == 0 && (i_node[j].file_style) == 1)
					{
						del_file(tmp);
						break;
					}
				}
				if (i == ROOT_NUM)
				{
					printf("������������ļ��ļ�\n");
				}
				break;
			}
			case 21:{
				scanf("%s", tmp);     //ɾ��Ŀ¼
				del_dir(tmp);
				break;
			}
			case 2: {
				scanf("%s", tmp1);     //���뵱ǰĿ¼�µ�ָ��Ŀ¼   �൱�ڽ���Ŀ¼  cd  +  Ŀ¼��
				display_dir(tmp1);
				break;
			}
			case 3: {
				back_dir();       //������һ��Ŀ¼
				break;
			}
			case 12: {
				help();
				break;
			}
			case 8: 
			{
				write_file(fp);      //������������Ϣд��ϵͳ�ļ����˳�
				//system("pause");
				return 0;
			}
			case 19:					//open
			{
				scanf("%s", tmp);
				open(tmp);
				break;
			}
			case 22: {							//read
				scanf("%s", tmp);
				if (!read(tmp))
				{
					cout << endl;
					show_file_content();

				}
				break;
			}
			case 27:							//write
			{
				scanf("%s", tmp);
				//getchar();
				int choice;
				cin >> choice;
				if (!is_open(tmp))
				{
					cout << "�ļ�δ�򿪻򲻴���." << endl;
					break;
				}
				cout << "��һ���������� EXITANYWAY ʱ����"<<endl;
				string writec,temp;
				getchar();
				getline(cin, temp);
				while (temp!="EXITANYWAY")
				{
					writec += "\n" + temp;
					getline(cin, temp);
				}
				write(tmp, writec, choice);
				break; 
			}
			case 14: {			//logout
				write_file(fp);
				logout();
				int l;
				for (l = 0; l < 8; l++)
				{
					file_array[l] = -1;
				}
				file_array_head = 0;
				while (1) {
					int log_com;
					cout << "1------��½------1" << endl;
					cout << "2------ע��------2" << endl;
					cin >> log_com;
					switch (log_com) {
					case 1:login(); break;
					case 2:reg(); break;
					default:cout << "unknown command" << endl;
					}
					if (login_userid != -1)
						break;
				}
				help();
				break;
			}
			case 4:				//close 
			{	
				scanf("%s", tmp);
				close(tmp);
				break; 
			}
			case 5:					//copy
			{
				scanf("%s", tmp);
				copy(tmp);
				break;
			}
			case 20:		//paste
			{
				scanf("%s", tmp);
				paste(tmp);
				break;
			}
			case 0:					//attrib
			{
				scanf("%s", tmp);
				string new_property;
				cin >> new_property;
				attrib_file(tmp, new_property);
				break;
			}
			case 24:					//time
			{
				//todo
				//system("time");
				SYSTEMTIME sys;
				GetLocalTime(&sys);
				printf("\t%4d/%02d/%02d %02d:%02d:%02d.%03d ���� %1d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek ? sys.wDayOfWeek : 7);
				break;	
			}
			case 23:					//rename
			{
				scanf("%s", tmp);
				string new_name;
				cin >> new_name;
				rename(tmp, new_name);
				//todo
				break;
			}
			case 17:					//more
			{
				scanf("%s", tmp);
				if (!read(tmp))
				{
					cout << endl;
					show_file_content();

				}
				break;
			}
			case 26:					//ver
			{
				//todo
				//system("ver");
				display_sys();
				ver_info();
				break;
			}
			case 18:					//move
			{
				scanf("%s", tmp);
				move_file(tmp);
				break;
			}
			//case 10:					//find 
			//{
			//	scanf("%s", tmp);
			//	string tar;
			//	getline(cin, tar);
			//	file_find(tmp, tar);
			//	paste(tmp);
			//	break;
			//}
			case 9:					//export
			{
				string s, temp, newtext,name;
				cin >> name;
				cin >> s;
				while (s.find('\\') != s.npos)
				{
					s[s.find('\\')] = '/';
				}
				fstream infile(s.c_str(), ios::out);
				if (infile.bad())
				{
					cout << "�����ļ�ʧ�ܡ�" << endl;
					break;
				}
				infile.close();
				export_file(name, s);
				//todo
				break;
			}
			case 13:					//import 
			{
				string s,temp,newtext;
				cin >> s;
				string name = s.substr(s.find_last_of('\\')+1, s.length());
				while (s.find('\\') != s.npos)
				{
					s[s.find('\\')] = '/';
				}
				fstream infile(s.c_str(), ios::in);
				if (!infile.is_open())
				{
					cout << "�����ļ�ʧ�ܡ�" << endl;
					break;
				}
				while (getline(infile,temp))
				{
					newtext += temp + '\n';
				}
				infile.close();
				import_file(name, newtext);
				//todo
				break;
			}
			default: 
			{
				cout << "��Чָ��" << endl;
				break;
			}
		}
		write_file(fp);
	}
	system("pause");
	return 0;
}