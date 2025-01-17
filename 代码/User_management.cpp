#include "header.h"
//用户管理
void User_management()
{
    if (userID != 0)
    {
        printf("只有申屠鹏会才可以管理用户!\n");
        return;
    }
    printf("欢迎来到用户管理!\n");
    char c, d;
    scanf("%c", &c);
    while (c != '0')
    {
        printf("\n1.查看 2.插入 3.删除 0.保存 & 退出\n");
        scanf("%c", &c);
        switch (c)
        {
        case '1':
            for (int i = 0; i < ACCOUNT_NUM; i++)
            {
                if (users.userName[i][0] != 0)
                    printf("%d\t%s\t%d\n", users.userID[i], users.userName[i], users.groupID[i]);
                else
                    break;
            }
            scanf("%c", &c);
            break;
        case '2':
            int i;
            for (i = 0; i < ACCOUNT_NUM; i++)
            {
                if (users.userName[i][0] == 0)
                    break;
            }
            if (i == ACCOUNT_NUM)
            {
                printf("用户太多了!\n");
                break;
            }
            printf("请输入用户名:");
            char str[USER_NAME_LENGTH];
            scanf("%s", str);
            for (i = 0; i < ACCOUNT_NUM; i++)
            {
                if (strcmp(users.userName[i], str) == 0)
                {
                    printf("已经有同名的用户名了!\n");
                }
                if (users.userName[i][0] == 0)
                {
                    strcpy(users.userName[i], str);
                    printf("请输入密码:");
                    scanf("%s", str);
                    strcpy(users.password[i], str);
                    printf("请输入 group ID:");
                    int t;
                    scanf("%d", &t);
                    scanf("%c", &c);
                    if (t > 0)
                    {
                        users.groupID[i] = t;
                        printf("成功!\n");
                    }
                    else
                    {
                        printf("插入失败!\n");
                        strcpy(users.userName[i], 0);
                        strcpy(users.password[i], 0);
                    }
                    break;
                }
            }
            break;
        case '3':
            printf("请输入userID:");
            int tmp;
            scanf("%d", &tmp);
            scanf("%c", &c);
            for (int j = tmp; j < ACCOUNT_NUM - 1; j++)
            {
                strcpy(users.userName[j], users.userName[j + 1]);
                strcpy(users.password[j], users.password[j + 1]);
                users.groupID[j] = users.groupID[j + 1];
            }
            printf("成功!\n");
        }
    }
    fseek(fd, DATA_START + BLOCK_SIZE, SEEK_SET);
    fwrite(&users, sizeof(users), 1, fd);
}
