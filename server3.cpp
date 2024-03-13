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
    char birthday[12];
    char number[6];
} students[100], foundedStudents[100];
int studentsLength = 0;
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
            recv(newS, buf, sizeof(buf), 0);
            switch (property)
            {
            case '1':
            case '1':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].name, buf) == 0 ? 1 : 0;
                    foundedStudentsMarks[i] = strcmp(students[i].name, buf) == 0 ? 1 : 0;
                }
                break;
            case '2':
            case '2':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].lastname, buf) == 0 ? 1 : 0;
                    foundedStudentsMarks[i] = strcmp(students[i].lastname, buf) == 0 ? 1 : 0;
                }
                break;
            case '3':
            case '3':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].birthday, buf) == 0 ? 1 : 0;
                    foundedStudentsMarks[i] = strcmp(students[i].birthday, buf) == 0 ? 1 : 0;
                }
                break;
            case '4':
            case '4':
                for (int i = 0; i < studentsLength; i++)
                {
                    foundedStudentsMarks[i] = strcmp(students[i].number, buf) == 0 ? 1 : 0;
                    foundedStudentsMarks[i] = strcmp(students[i].number, buf) == 0 ? 1 : 0;
                }
                break;

            default:
                break;
            }
            for (int i = 0; i < 100; i++)
            {
                if (foundedStudentsMarks[i] == 1)
                {
                    foundedStudents[foundedStudentsLength++] = students[i];
                }
            }
            send(newS, &foundedStudentsLength, sizeof(int), 0);
            send(newS, foundedStudents, sizeof(struct Student) * 100, 0);
            break;
        }
        case '2':
            struct Student student;
            recv(newS, &student, sizeof(Student), 0);
            students[studentsLength++] = student;
            break;
        case '3':
            strcpy(students[studentsLength - 1].name, "");
            strcpy(students[studentsLength - 1].lastname, "");
            strcpy(students[studentsLength - 1].birthday, "");
            strcpy(students[studentsLength - 1].number, "");
            studentsLength--;
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