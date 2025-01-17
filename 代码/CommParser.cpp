<<<<<<< HEAD
#include "header.h"
void CommParser(inode *&currentInode)
=======
#include"header.h"

//主要功能选择集合
void CommParser(inode*& currentInode)
>>>>>>> 1908043cba3e84dd20701c109089c18e4b21c8db
{
    char para1[11];//存储功能前缀
    char para2[1024];
    bool flag = false;
    int n = 0;
    vector<string> v;
    while (true)
    {
        unsigned int f1[BLOCK_SIZE / sizeof(unsigned int)] = {0};
        fseek(fd, DATA_START + 8 * BLOCK_SIZE, SEEK_SET);
        fread(f1, sizeof(f1), 1, fd);
        memset(para1, 0, 11);
        memset(para2, 0, 1024);
        Printsign();
        string system;
        getline(cin, system);
        if (system.length() == 0)
        {
            continue;
        }
        v = split(system, " "); //根据多个字符切片
        n = v.size();
        strcpy(para1, v[0].c_str());
        para1[10] = 0;
        //选择功能
        if (strcmp("ls", para1) == 0) //显示当前文件
        {
            flag = false;
            List();
        }
        else if (strcmp("cp", para1) == 0)
        { //文件复制
            flag = false;
            scanf("%s", para2);
            para2[1023] = 0; //安全保护
            Copy(para2, currentInode);
        }
        else if (strcmp("mv", para1) == 0)
        { //重命名
            flag = false;
            scanf("%s", para2);
            para2[1023] = 0; //安全保护
            Rename(para2);
        }
        else if (strcmp("pwd", para1) == 0)
        { //显示当前目录
            flag = false;
            Ab_dir();
        }
        else if (strcmp("passwd", para1) == 0)
        {
            flag = false;
            Passwd();
        }
        else if (strcmp("chmod", para1) == 0)
        { //用户权限
            flag = false;
            strcpy(para2, v[1].c_str());
            //scanf("%s", para2);
            para2[1023] = 0;
            Chmod(para2);
        }
        else if (strcmp("chown", para1) == 0)
        { //更改用户权限
            flag = false;
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0;
            Chown(para2);
        }
        else if (strcmp("chgrp", para1) == 0)
        { //更改所属组
            flag = false;
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0;
            Chgrp(para2);
        }
        else if (strcmp("info", para1) == 0)
        {
            printf("系统信息:\n总共的block:%d\n空闲block:%d\n总inode:%d\n剩余inode:%d\n\n", superBlock.s_num_block, superBlock.s_num_fblock, superBlock.s_num_inode, superBlock.s_num_finode);
            for (int i = 0; i < 50; i++)
            {
                if (i > superBlock.special_free)
                    printf("-1\t");
                else
                    printf("%d\t", superBlock.special_stack[i]);
                if (i % 10 == 9)
                    printf("\n");
            }
            printf("\n\n");
        }
        //创建文件
        else if (strcmp("create", para1) == 0)
        {
            flag = false;
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0;
            CreateFile(para2);
        }
        //删除文件
        else if (strcmp("rm", para1) == 0)
        {
            flag = false;
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0;
            DeleteFile(para2);
        }
        //打开文件
        else if (strcmp("open", para1) == 0)
        {
            flag = true;
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0;
            currentInode = OpenFile(para2);
        }
        //写文件
        else if (strcmp("insert", para1) == 0 && flag)
        {
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0;
            Write(*currentInode, para2);
        }
        //读文件
        else if (strcmp("cat", para1) == 0 && flag)
        {
            PrintFile(*currentInode);
        }
        //打开一个目录
        else if (strcmp("cd", para1) == 0)
        {
            flag = false;
            //scanf("%s", para2);
            // strcpy(para2, v[1].c_str());
            // para2[1023] = 0;
            // OpenDir(para2);
            OpenMutipleDir(v[1]);
        }
        //创建目录
        else if (strcmp("mkdir", para1) == 0)
        {
            flag = false;
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0; //security protection
            MakeDir(para2);
        }
        //删除目录
        else if (strcmp("rmdir", para1) == 0)
        {
            flag = false;
            //scanf("%s", para2);
            strcpy(para2, v[1].c_str());
            para2[1023] = 0; //security protection

            RemoveDir(para2);
        }
        //登出系统
        else if (strcmp("logout", para1) == 0)
        {
            flag = false;
            Logout();
            char tmp_userName[USER_NAME_LENGTH], tmp_userPassword[USER_PASSWORD_LENGTH * 5];
            do
            {
                memset(tmp_userName, 0, USER_NAME_LENGTH);
                memset(tmp_userPassword, 0, USER_PASSWORD_LENGTH * 5);
                printf("用户登录\n\n");
                printf("用户名:\t");
                scanf("%s", tmp_userName);
                printf("密码:\t");
                char c;
                scanf("%c", &c);
                int i = 0;
                while (1)
                {
                    char ch;
                    ch = getch();
                    if (ch == '\b')
                    {
                        if (i != 0)
                        {
                            printf("\b \b");
                            i--;
                        }
                        else
                        {
                            tmp_userPassword[i] = '\0';
                        }
                    }
                    else if (ch == '\r')
                    {
                        tmp_userPassword[i] = '\0';
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        putchar('*');
                        tmp_userPassword[i++] = ch;
                    }
                }
            } while (Login(tmp_userName, tmp_userPassword) != true);

            inode *currentInode = new inode;
        }
        else if (strcmp("ln", para1) == 0)
        {
            flag = false;
            scanf("%s", para2);
            para2[1023] = 0;
            ln(para2);
        }
        //登录
        else if (strcmp("su", para1) == 0)
        {
            Logout();
            flag = false;
            char para3[USER_PASSWORD_LENGTH * 5];
            memset(para3, 0, USER_PASSWORD_LENGTH + 1);
            scanf("%s", para2);
            para2[1023] = 0;
            printf("密码: ");
            char c;
            scanf("%c", &c);
            int i = 0;
            while (1)
            {
                char ch;
                ch = getch();
                if (ch == '\b')
                {
                    if (i != 0)
                    {
                        printf("\b \b");
                        i--;
                    }
                }
                else if (ch == '\r')
                {
                    para3[i] = '\0';
                    printf("\n\n");
                    break;
                }
                else
                {
                    putchar('*');
                    para3[i++] = ch;
                }
            }
            para3[USER_PASSWORD_LENGTH] = 0; //security protection

            Login(para2, para3);
        }
        else if (strcmp("Muser", para1) == 0)
        {
            flag = false;
            User_management();
        }
        //退出系统
        else if (strcmp("exit", para1) == 0)
        {
            flag = false;
            break;
        }
        else if ((strcmp("rm-rf/*", para1) == 0))
        {
            if (userID == 0)
            {
                printf("您真的要删除跑路吗？[y/n]");
                char label;
                cin >> label;
                while (label != 'n' && label != 'N')
                {
                    if (label == 'y' || label == 'Y')
                    {
                        Format();
                        Mount();
                        break;
                    }
                    else
                    {
                        printf("输入错误，请重新输入[y/n]");
                        cin >> label;
                    }
                }
            }
            else
            {
                printf("您的权限不够，请联系管理员操作！");
            }
        }
        //help
        else
        {
            flag = false;
            Help();
        }
    }
};