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
struct Employee
{
    char name[35];
    char lastname[10];
    char birthday[10];
    char number[4];
} students[5];
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
        p = buf[0];
        switch (p)
        {
        case '1':
            buf[0] = '\0';
            sum = 0;
            recv(newS, buf, sizeof(buf), 0);
            mon = atoi(buf);
            recv(newS, buf, sizeof(buf), 0);
            s = buf[0];
            for (i = 1; i <= 5; i++)
                if (students[i].name[0] == s)
                {
                    nal = atoi(students[i].number);
                    doh = atoi(students[i].birthday);
                    printf("mon %d\n", mon);
                    sum = sum + (nal * doh * mon) / 100.0;
                }
            int *decpt, *sgn;
            printf("%f\n", sum);
            sprintf(buf, "%.3f", sum);
            send(newS, buf, sizeof(buf), 0);
            puts(buf);
            break;
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
    strcpy(students[0].name, "Sergeev Sergei Sergeevich");
    strcpy(students[0].lastname, "1");
    strcpy(students[0].birthday, "100000");
    strcpy(students[0].number, "10");
    strcpy(students[1].name, "Ivanov Ivan Ivanovich");
    strcpy(students[1].lastname, "2");
    strcpy(students[1].birthday, "200000");
    strcpy(students[1].number, "20");
    strcpy(students[2].name, "Vladimirov Vladimir Vladimirovich");
    strcpy(students[2].lastname, "3");
    strcpy(students[2].birthday, "300000");
    strcpy(students[2].number, "30");
    strcpy(students[3].name, "Sidorov Sidor Sidorovich ");
    strcpy(students[3].lastname, "4");
    strcpy(students[3].birthday, "400000");
    strcpy(students[3].number, "40");
    strcpy(students[4].name, "Vasilev Vasilii Vasilievich");
    strcpy(students[4].lastname, "5");
    strcpy(students[4].birthday, "500000");
    strcpy(students[4].number, "50");
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