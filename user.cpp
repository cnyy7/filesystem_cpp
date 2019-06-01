/*
Created by

计创16------陈楠------161002107

on 6 June.
*/

#include "filesystem.h"

user user_array[USER_NUM];            //用户组
int login_userid = -1;        //登陆用户ID
int user_num = 0;            //用户总数

/*注册*/
void reg() {
    string tempusername;
    string temppassword;
    if (user_num < USER_NUM + 1) {
        cout << "-----注册-----" << endl;
        while (true) {
            cout << "用户名：";
            cin >> tempusername;
            int i;

            //判断是否重名
            for (i = 0; i < user_num; i++) {
                if (user_array[i].username == tempusername) {
                    cout << "用户名已存在" << endl;
                    break;
                }
            }
            if (i == user_num)
                break;
        }
        strcpy(user_array[user_num].username, tempusername.c_str());
        cout << "密码：";
        cin >> temppassword;
        strcpy(user_array[user_num].password, temppassword.c_str());
        user_num++;
    } else {
        cout << "注册数已满" << endl;
    }
}

/*登陆*/
int login() {
    cout << "-----登陆-----" << endl;
    string getusername;
    string getpassword;
    cout << "用户名：";
    cin >> getusername;
    cout << "密码：";
    cin >> getpassword;
    int i;
    if (user_num == 0) {
        cout << "用户名或密码不正确" << endl;
        return 0;
    } else {
        for (i = 0; i < user_num; i++) {
            if (getusername == user_array[i].username && getpassword == user_array[i].password) {
                login_userid = i;
                cur_user = getusername;
                cout << "登陆成功" << endl;
                return 1;
            } else {
                continue;
            }
        }
        cout << "用户名或密码不正确" << endl;
        return 0;
    }
}

/*退出*/
void logout() {
    cur_user = "";
    login_userid = -1;
    system("cls");
}
