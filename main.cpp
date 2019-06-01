/*
Created by

计创16------陈楠------161002107

on 6 June.
*/

#include "filesystem.h"

command cmd[CMD_NUM];

/*帮助*/
void help() {
    printf("\n\n初始化                        format\n");
    printf("查看当前目录下文件列表           dir\n");
    printf("查看文件信息                   cat        (cat + 文件名)  \n");
    printf("查看系统空间使用信息            ls    \n");
    printf("创建目录                      md         (md  + 目录名)  \n");
    printf("创建文件                      touch      (touch  + 文件名 + 文件长度 + 权限)\n");
    printf("删除文件                      del        (del + 文件名) \n");
    printf("打开文件                      open       (open + 文件名) \n");
    printf("导出文件                      export     (export + 文件名 + 要导出的地址) \n");
    printf("更改文件名字                   rename     (rename + 文件名 + 新文件名) \n");
    printf("导入文件                      import     (import + 要导入的文件) \n");
    printf("打开文件                      open       (open + 文件名) \n");
    printf("关闭文件                      close      (close + 文件名) \n");
    printf("读取文件                      read       (read + 文件名) \n");
    printf("写入文件                      write      (write + 文件名 + 写入方式(0:覆盖，大于1：追加))\n");
    printf("复制文件                      copy       (copy + 文件名）  \n");
    printf("移动文件                      move       (move + 文件名）  \n");
    printf("粘贴文件                      paste      (paste + 文件名)  \n");
    printf("删除目录                      rd         (rd + 目录名)\n");
    printf("更改文件权限                   attrib     (attrib + 目录名+权限（r,o,w）)\n");
    printf("进入当前目录下的指定目录         cd         (cd + 目录名)\n");
    printf("返回上一级目录                 cd..  \n");
    printf("显示时间                      time  \n");
    printf("显示系统信息                   ver  \n");
    printf("显示帮助命令                   help  \n");
    printf("退出文件系统                   exit  \n");
    printf("退出登录                      logout\n");

}

/*初始化命令*/
void init_cmd(command *command) {
    strcpy(command[0].com, "attrib");
    strcpy(command[1].com, "cat");
    strcpy(command[2].com, "cd");
    strcpy(command[3].com, "cd..");
    strcpy(command[4].com, "close");
    strcpy(command[5].com, "copy");
    strcpy(command[6].com, "del");
    strcpy(command[7].com, "dir");
    strcpy(command[8].com, "exit");
    strcpy(command[9].com, "export");
    strcpy(command[10].com, "find");          //未实现
    strcpy(command[11].com, "format");
    strcpy(command[12].com, "help");
    strcpy(command[13].com, "import");
    strcpy(command[14].com, "logout");
    strcpy(command[15].com, "ls");            //
    strcpy(command[16].com, "md");
    strcpy(command[17].com, "more");
    strcpy(command[18].com, "move");
    strcpy(command[19].com, "open");
    strcpy(command[20].com, "paste");
    strcpy(command[21].com, "rd");
    strcpy(command[22].com, "read");
    strcpy(command[23].com, "rename");
    strcpy(command[24].com, "time");
    strcpy(command[25].com, "touch");
    strcpy(command[26].com, "ver");
    strcpy(command[27].com, "write");
    //strcpy(command[27].com, "xcopy");
}

/*二分查找返回命令下标*/
int find_cmd(const string &temp_cmd, int low, int high, command *com) {
    int mid = (low + high) / 2;
    string temp = com[mid].com;
    if (low >= high)
        return -1;
    if (temp_cmd == temp)
        return mid;
    else if (temp_cmd < temp)
        return find_cmd(temp_cmd, low, mid, com);
    else
        return find_cmd(temp_cmd, mid + 1, high, com);
}

/*主函数*/
int main() {
    char tmp[20], tmp1[20];
    struct command tmp2[10];
    int i, j = 0, p, len = 0;
    FILE *fp;
    //将各个命令存进命令表
    init_cmd(cmd);
    //初始化
    if ((fp = fopen("filesave", "rb")) == nullptr)   //判断系统文件是否存在
    {
        cout << "正在初始化系统" << endl;
        format();
    } else {
        cout << "加载文件系统" << endl;
        read_file(fp);       //读取系统文件的内容
    }

    //注册登陆
    while (true) {
        int log_com;
        cout << "1------登陆------1" << endl;
        cout << "2------注册------2" << endl;
        cin >> log_com;
        switch (log_com) {
            case 1:
                login();
                break;
            case 2:
                reg();
                break;
            default:
                cout << "unknown command" << endl;
        }
        if (login_userid != -1)
            break;
    }
    write_file(fp);
    help();
    while (true) {
        j = 0;         //必须重新给恢复0否则出错
        strcpy(tmp, cur_dir);
        while (strcmp(tmp, "filsystem") != 0) {
            for (i = 0; i < ROOT_NUM; i++) {
                p = root[i].i_num;
                if (strcmp(tmp, root[i].file_name) == 0 && (i_node[p].file_style == 0)) {
                    strcpy(tmp2[j].com, tmp);
                    j++;
                    strcpy(tmp, root[i].dir_name);
                }
            }
        }
        cout << endl;

        strcpy(tmp2[j].com, tmp);
        for (i = j; i >= 0; i--) {
            printf("%s>", tmp2[i].com);
        }
        string temp_cmd;
        cin >> temp_cmd;                            //输入命令并且查找命令的相关操作
        p = find_cmd(temp_cmd, 0, CMD_NUM, cmd);
        read_file(fp);                                //读取系统文件的内容
        switch (p) {
            case 11: {
                format();       //初始化
                break;
            }
            case 7: {
                display_curdir();     //查看当前目录下的文件列表
                break;
            }
            case 1: {
                scanf("%s", tmp);     //查看文件
                show_file(tmp);
                break;
            }
            case 15: {
                display_sys();      //查看系统信息
                break;
            }
            case 16: {
                scanf("%s", tmp);      //创建目录
                create_dir(tmp);
                break;
            }
            case 25: {
                scanf("%s", tmp);     //创建文件
                scanf("%d", &len);
                string limit;
                cin >> limit;
                create_file(tmp, len, login_userid, limit);
                break;
            }
            case 6: {
                scanf("%s", tmp);     //删除文件
                for (i = 0; i < ROOT_NUM; i++)     //判断文件是不是正规文件
                {
                    j = root[i].i_num;
                    if (strcmp(tmp, root[i].file_name) == 0 && (i_node[j].file_style) == 1) {
                        del_file(tmp);
                        break;
                    }
                }
                if (i == ROOT_NUM) {
                    printf("这个不是正规文件文件\n");
                }
                break;
            }
            case 21: {
                scanf("%s", tmp);     //删除目录
                del_dir(tmp);
                break;
            }
            case 2: {
                scanf("%s", tmp1);     //进入当前目录下的指定目录   相当于进入目录  cd  +  目录名
                display_dir(tmp1);
                break;
            }
            case 3: {
                back_dir();       //返回上一级目录
                break;
            }
            case 12: {
                help();
                break;
            }
            case 8: {
                write_file(fp);      //将磁盘利用信息写进系统文件，退出
                //system("pause");
                return 0;
            }
            case 19:                    //open
            {
                scanf("%s", tmp);
                open(tmp);
                break;
            }
            case 22: {                            //read
                scanf("%s", tmp);
                if (!read(tmp)) {
                    cout << endl;
                    show_file_content();

                }
                break;
            }
            case 27:                            //write
            {
                scanf("%s", tmp);
                //getchar();
                int choice;
                cin >> choice;
                if (!is_open(tmp)) {
                    cout << "文件未打开或不存在." << endl;
                    break;
                }
                cout << "在一整行内输入 EXITANYWAY 时结束" << endl;
                string writec, temp;
                getchar();
                getline(cin, temp);
                while (temp != "EXITANYWAY") {
                    writec += "\n" + temp;
                    getline(cin, temp);
                }
                write(tmp, writec, choice);
                break;
            }
            case 14: {            //logout
                write_file(fp);
                logout();
                int l;
                for (l = 0; l < 8; l++) {
                    file_array[l] = -1;
                }
                file_array_head = 0;
                while (true) {
                    int log_com;
                    cout << "1------登陆------1" << endl;
                    cout << "2------注册------2" << endl;
                    cin >> log_com;
                    switch (log_com) {
                        case 1:
                            login();
                            break;
                        case 2:
                            reg();
                            break;
                        default:
                            cout << "unknown command" << endl;
                    }
                    if (login_userid != -1)
                        break;
                }
                help();
                break;
            }
            case 4:                //close
            {
                scanf("%s", tmp);
                close(tmp);
                break;
            }
            case 5:                    //copy
            {
                scanf("%s", tmp);
                copy(tmp);
                break;
            }
            case 20:        //paste
            {
                scanf("%s", tmp);
                paste(tmp);
                break;
            }
            case 0:                    //attrib
            {
                scanf("%s", tmp);
                string new_property;
                cin >> new_property;
                attrib_file(tmp, new_property);
                break;
            }
            case 24:                    //time
            {
                //system("time");
                SYSTEMTIME sys;
                GetLocalTime(&sys);
                printf("\t%4d/%02d/%02d %02d:%02d:%02d.%03d 星期 %1d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour,
                       sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek ? sys.wDayOfWeek : 7);
                break;
            }
            case 23:                    //rename
            {
                scanf("%s", tmp);
                string new_name;
                cin >> new_name;
                rename(tmp, new_name);
                break;
            }
            case 17:                    //more
            {
                scanf("%s", tmp);
                if (!read(tmp)) {
                    cout << endl;
                    show_file_content();

                }
                break;
            }
            case 26:                    //ver
            {
                //system("ver");
                display_sys();
                ver_info();
                break;
            }
            case 18:                    //move
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
            case 9:                    //export
            {
                string s, temp, newtext, name;
                cin >> name;
                cin >> s;
                while (s.find('\\') != std::__cxx11::string::npos) {
                    s[s.find('\\')] = '/';
                }
                fstream infile(s.c_str(), ios::out);
                if (infile.bad()) {
                    cout << "导出文件失败。" << endl;
                    break;
                }
                infile.close();
                export_file(name, s);
                break;
            }
            case 13:                    //import
            {
                string s, temp, newtext;
                cin >> s;
                string name = s.substr(s.find_last_of('\\') + 1, s.length());
                while (s.find('\\') != std::__cxx11::string::npos) {
                    s[s.find('\\')] = '/';
                }
                fstream infile(s.c_str(), ios::in);
                if (!infile.is_open()) {
                    cout << "导入文件失败。" << endl;
                    break;
                }
                while (getline(infile, temp)) {
                    newtext += temp + '\n';
                }
                infile.close();
                import_file(name, newtext);
                break;
            }
            default: {
                cout << "无效指令" << endl;
                break;
            }
        }
        write_file(fp);
    }
}