#include <sys/types.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
struct Student
{
    char name[35];
    char lastname[35];
    char birthday[10];
    char number[4];
} students[100], foundedStudents[100];
int studentsLength;
// процедура для обслуживания соединения
int Func(int newS)
{
    long int i, num, t, mon, doh, nal;
    float sum;
    int m;
    char p, p1, s;
    char buf[256], b[256];
    while (true)
    {
        recv(newS, buf, sizeof(buf), 0);
        puts(buf);
        p = buf[0];
        switch (p)
        {
        case '1':
        {
            // Поиск

            recv(newS, buf, sizeof(buf), 0);
            puts(buf);
            char property = buf[0];
            bool foundedStudentsMarks[100];
            int foundedStudentsLength = 0;
            p = buf[0];
            recv(newS, buf, sizeof(buf), 0);
            puts(buf);
            switch (p)
            {
            case '1':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].name, buf) == 0 ? 1 : 0;
                }
                break;
            case '2':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].lastname, buf) == 0 ? 1 : 0;
                }
                break;
            case '3':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].birthday, buf) == 0 ? 1 : 0;
                }
                break;
            case '4':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].number, buf) == 0 ? 1 : 0;
                }
                break;

            default:
                break;
            }
            for (int i = 0; i < 100; i++)
            {
                if (foundedStudentsMarks[i])
                {
                    foundedStudents[foundedStudentsLength++] = students[i];
                }
            }
            puts("Строка 83");
            send(newS, &foundedStudentsLength, sizeof(int), 0);
            send(newS, foundedStudents, 100 * sizeof(struct Student), 0);

            break;
        }
        case '2':
            recv(newS, buf, sizeof(buf), 0); // Номер
            num = atoi(buf);
            printf("%d\n", num);
            recv(newS, buf, sizeof(buf), 0);
            p1 = buf[0];
            switch (p1)
            {
            case '1':
                recv(newS, buf, sizeof(buf), 0); // Имя
                strcpy(students[num].name, buf);
                break;
            case '2':
                recv(newS, buf, sizeof(buf), 0); // Таб.номер
                strcpy(students[num].lastname, buf);
                break;
            case '3':
                recv(newS, buf, sizeof(buf), 0); // Доход
                strcpy(students[num].birthday, buf);
                break;
            case '4':
                recv(newS, buf, sizeof(buf), 0); // Ставка налога
                strcpy(students[num].number, buf);
            }
            break;
        case '3':
            for (i = 1; i <= 5; i++)
            {
                buf[0] = '\0';
                strcat(buf, students[i].name);
                strcat(buf, " ");
                strcat(buf, students[i].lastname);
                strcat(buf, " ");
                strcat(buf, students[i].birthday);
                strcat(buf, " ");
                strcat(buf, students[i].number);
                strcat(buf, "\n");
                send(newS, buf, sizeof(buf), 0);
            }
            break;
        case '4':
            exit(0);
        }
    }
}

void reaper(int sig)
{
    int status;
    while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0)
        ;
}
int main()
{
    strcpy(students[0].name, "Sergei");
    strcpy(students[0].lastname, "Sergeev");
    strcpy(students[0].birthday, "25/05/2005");
    strcpy(students[0].number, "67745");
    strcpy(students[1].name, "Ivan");
    strcpy(students[1].lastname, "Ivanov");
    strcpy(students[1].birthday, "17/02/2004");
    strcpy(students[1].number, "67256");
    strcpy(students[2].name, "Vladimir");
    strcpy(students[2].lastname, "Vladimirov");
    strcpy(students[2].birthday, "12/09/2003");
    strcpy(students[2].number, "67865");
    strcpy(students[3].name, "Sidor");
    strcpy(students[3].lastname, "Sidorov");
    strcpy(students[3].birthday, "02/12/2002");
    strcpy(students[3].number, "67123");
    strcpy(students[4].name, "Vasilii");
    strcpy(students[4].lastname, "Vasilev");
    strcpy(students[4].birthday, "25/05/2001");
    strcpy(students[4].number, "67532");
    studentsLength = 5;
    struct sockaddr_in local;
    int s,
        newS, rc;
    local.sin_family = AF_INET;
    local.sin_port = htons(7500);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    s = socket(AF_INET, SOCK_STREAM, 0);
    rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    rc = listen(s, 5);
    (void)signal(SIGCHLD, reaper);
    while (true)
    {
        newS = accept(s, NULL, NULL);
        switch (fork())
        {
        case 0:
            (void)close(s);
            exit(Func(newS));
        default:
            (void)close(newS);
        }
    }
    return 0;
}