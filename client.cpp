#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student
{
    char name[35];
    char lastname[35];
    char birthday[12];
    char number[6];
} students[100];
int main()
{
    struct sockaddr_in peer;
    int s, t, t1;
    int rc;
    char buf[256], p, p1, b[256];
    ;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(7500);
    peer.sin_addr.s_addr = inet_addr("127.0.0.1");
    s = socket(AF_INET, SOCK_STREAM, 0);
    rc = connect(s, (struct sockaddr *)&peer, sizeof(peer));
    while (true)
    {
        // Выбор пункта меню и отправка его серверу puts("Choose:");
        // puts("\t1 - Select");
        puts("\t1 - Search");
        puts("\t2 - Add");
        puts("\t3 - Delete last student");
        puts("\t4 - Exit");
        scanf("%s", buf);
        buf[1] = '\0';
        send(s, buf, sizeof(buf), 0);
        p = buf[0];
        switch (p)
        {
        case '1':
        { // Выбрать
            puts("Выберите свойтво: \n1 - Name\n2 - Lastname\n3 - Birthday\n4 - Number");
            scanf("%s", buf);
            send(s, buf, sizeof(buf), 0);
            puts("Ваш запрос:\n");
            scanf("%s", buf);
            send(s, buf, sizeof(buf), 0);
            int foundedStudentsLength = 0;
            recv(s, &foundedStudentsLength, sizeof(int), 0);

            recv(s, students, sizeof(struct Student) * 100, 0);
            for (int i = 0; i < foundedStudentsLength; i++)
            {
                puts(students[i].name);
                puts(students[i].lastname);
                puts(students[i].birthday);
                puts(students[i].number);
            }
            break;
        }
        case '2': // Подредактировать puts("What number (1-5) to edit");
            puts("Введите свойство нового студента");
            puts("\t1 - Name");
            scanf("%s", buf);
            strcpy(students[99].name, buf);
            printf("Новое имя: %s", students[99].name);
            puts("\t2 - Lastname");
            scanf("%s", buf);
            strcpy(students[99].lastname, buf);
            puts("\t3 - Birthday");
            scanf("%s", buf);
            strcpy(students[99].birthday, buf);
            puts("\t4 - Number");
            scanf("%s", buf);
            strcpy(students[99].number, buf);
            send(s, (Student *)&students[99], sizeof(struct Student), 0);

            break;
        case '3': // Просмотреть 5 записей recv(s,buf,sizeof(buf),0);printf("%s",buf);
            break;
        case '4': // Выход
            exit(0);
        }
    }
}