#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#define MAXSIZE 1000
void printfcopmare(char a[], char b[])
{
    char aa[10][10];
    char bb[10][10];
    const char s[4] = " ";
    char *tok;
    tok = strtok(a, s);

    int y = 0;
    while (tok != 0)
    {
        strcpy(aa[y], tok);
        tok = strtok(0, s);
        y++;
    }
    char *tok2;
    tok2 = strtok(b, s);
    int yy = 0;
    while (tok2 != 0)
    {
        strcpy(bb[yy], tok2);
        tok2 = strtok(0, s);
        yy++;
    }
    int tafavot = 0, saver;
    for (int i = 0; i < y; i++)
    {
        if (strcmp(aa[i], bb[i]) != 0)
        {
            saver = i;
            tafavot++;
        }
    }
    if (tafavot == 1 && y == yy)
    {
        for (int i = 0; i < y; i++)
        {
            if (i == saver)
                printf(">>%s<< ", aa[saver]);
            else
                printf("%s ", aa[i]);
        }
        printf("\n");
        for (int i = 0; i < yy; i++)
        {
            if (i == saver)
                printf(">>%s<< ", bb[saver]);
            else
                printf("%s ", bb[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < y; i++)
        {
            printf("%s ", aa[i]);
        }
        printf("\n");
        for (int i = 0; i < yy; i++)
        {
            printf("%s ", bb[i]);
        }
        printf("\n");
    }
}
char *replaceWord(const char *s, const char *oldW, const char *newW, int type, int countnumber)
{
    char *result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;
            i += oldWlen - 1;
        }
    }
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);
    i = 0;
    int count = 0;
    if (countnumber == 0)
    {
        while (*s)
        {
            if (strstr(s, oldW) == s && count == 0)
            {
                strcpy(&result[i], newW);
                i += newWlen;
                s += oldWlen;
                if (type == 0) // faghat yek replace
                    count++;
                if (type == 1) // hame replace
                    count = 0;
            }
            else
                result[i++] = *s++;
        }
    }
    if (countnumber > 0)
    {
        int countat = 0;
        while (*s)
        {
            if (strstr(s, oldW) == s)
            {
                countat++;
            }
            if (strstr(s, oldW) == s && count == 0 && countat == countnumber)
            {
                strcpy(&result[i], newW);
                i += newWlen;
                s += oldWlen;
                if (type == 0) // faghat yek replace
                    count++;
                if (type == 1) // hame replace
                    count = 0;
            }
            else
                result[i++] = *s++;
        }
    }
    result[i] = '\0';
    return result;
}
void tree(char *basePath, const int root, int o)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (o == 0)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i = 0; i < root; i++)
            {
                if (i % 2 == 0 || i == 0)
                    printf("%c", 179);
                else
                    printf(" ");
            }
            printf("%c%c%s\n", 195, 196, dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root + 2, o - 1);
        }
    }
    closedir(dir);
}
int match(char *first, char *second)
{
    if (*first == '\0' && *second == '\0')
        return 1;
    if (*first == '*')
    {
        while (*(first + 1) == '*')
            first++;
    }
    if (*first == '*' && *(first + 1) != '\0' && *second == '\0')
        return 0;
    if (*first == *second)
        return match(first + 1, second + 1);
    if (*first == '*')
        return match(first + 1, second) || match(first, second + 1);
    return 0;
}
int countergrep = 0;
void grep(char filename[], DIR *folder, char word[], int type)
{
    if (filename[0] == '/')
    {
        for (int i = 0;; i++)
        {
            if (filename[i] == '\0')
                break;
            filename[i] = filename[i + 1];
        }
    }
    char str[1000], c;
    int flag1 = 0, j = 0, flag2 = 0;
    while (1)
    {
        for (int i = 0;; i++)
        {
            c = filename[j];
            j++;
            if (c == '/')
            {
                flag1++; // baraye check sakhtan folder
                break;
            }
            if (c == '\0')
            {
                goto l11;
            }
            str[i + 1] = '\0'; // baraye khali kardan string
            str[i] = c;
        }
        if (flag1 > 0)
        {
            int x = chdir(str);
            if (x == -1)
            {
                for (int b = 0; b < flag2; b++)
                    chdir("../");
                printf("INVALID DIRECTORY: %s\n", str);
                char cwd[1000];
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                {
                    char *u = strstr(cwd, "root");
                    if (u != 0)
                    {
                        chdir("../");
                    }
                }
                return;
            }
            flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
        }
        if (0)
        {
        l11:
            folder = fopen(str, "r");
            if (folder == NULL)
            {
                printf("Error! opening file\n");
                for (int b = 1; b < flag2; b++)
                    chdir("../");
                char cwd[1000];
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                {
                    char *u = strstr(cwd, "root");
                    if (u != 0)
                    {
                        chdir("../");
                    }
                }
                break;
            }
            else
            {
                char strsave[MAXSIZE];
                int y = 0;
                c = fgetc(folder);
                while (c != EOF)
                {
                    strsave[y + 1] = '\0';
                    strsave[y] = c;
                    c = fgetc(folder);
                    y++;
                }
                char *p = strstr(strsave, word);
                if (type == 1 && p > 0)
                    printf("%s\n", str);
                char ch, after[MAXSIZE], before[MAXSIZE], search[MAXSIZE];
                int pointer = 0, j = 0, saver;
                if (p != 0)
                {
                    while (p - strsave <= strlen(strsave))
                    {
                        int place = (int)(p - strsave);
                        after[0] = '\0';
                        for (int i = place;; i++)
                        {
                            if (strsave[i] == '\n' || strsave[i] == '\0')
                                break;
                            after[j + 1] = '\0';
                            after[j] = strsave[i];
                            j++;
                        }
                        j = 0;
                        for (int i = place;; i--)
                        {
                            if (strsave[i] == '\n' || i == -1)
                            {
                                saver = i + 1;
                                break;
                            }
                        }
                        before[0] = '\0';
                        for (int i = saver; i < place; i++)
                        {
                            before[j + 1] = '\0';
                            before[j] = strsave[i];
                            j++;
                        }
                        j = 0;
                        if (type == 0)
                            printf("%s: %s%s\n", str, before, after);
                        if (type == 2)
                            countergrep++;
                        p = strstr(p + (char)strlen(word), word); // edame file search shavad
                    }
                }
                fclose(folder);
                for (int b = 1; b < flag2; b++)
                    chdir("../");
                char cwd[1000];
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                {
                    char *u = strstr(cwd, "root");
                    if (u != 0)
                    {
                        chdir("../");
                    }
                }
                break;
            }
        }
    }
}
char clipboard[MAXSIZE];
int main()
{
    DIR *folder;
    int counterenter = 0;
    int counter = 0;
    int flag1 = 0;
    int flag2 = 0;
    int i = 0;
    char c;
    char str[MAXSIZE];
    char filename[MAXSIZE];
    str[0] = '\0';
    char arr[] = "file";  //"createfile--file";
    char arr2[] = "exit"; //
    char arr3[] = "insert";
    char arr4[] = "cat";
    char arr5[] = "copystr";
    char arr6[] = "removestr";
    char arr7[] = "cutstr";
    char arr8[] = "pastestr";
    char arr9[] = "find";
    while (1)
    {
        scanf("%s", str);
        if (strcmp(str, "grep") == 0)
        {
            char adress[1000], word[1000], cc;
            scanf(" -");
            scanf("%c", &c);
            if (c == '-')
            {                  // first
                scanf("str "); // for "
                scanf("%c", &cc);
                if (cc == '"')
                {
                    scanf("%[^\"]s", word);
                    scanf("\" --files /");
                }
                else
                {
                    word[0] = cc;
                    word[1] = '\0';
                    for (int i = 1;; i++)
                    {
                        scanf("%c", &cc);
                        if (cc == ' ')
                            break;
                        word[i + 1] = '\0';
                        word[i] = cc;
                    }
                    scanf("--files /");
                }
                scanf("%[^\n]s", filename);
                int j = 0;
                for (int i = 0;; i++)
                {
                    if (filename[i] == ' ')
                    {
                        j = 0;
                        grep(adress, folder, word, 0);
                        continue;
                    }
                    if (filename[i] == '\0')
                    {
                        grep(adress, folder, word, 0);
                        break;
                    }
                    adress[j + 1] = '\0';
                    adress[j] = filename[i];
                    j++;
                }
            }
            if (c == 'l')
            {
                scanf(" --str "); // for "
                scanf("%c", &cc);
                if (cc == '"')
                {
                    scanf("%[^\"]s", word);
                    scanf("\" --files /");
                }
                else
                {
                    word[0] = cc;
                    word[1] = '\0';
                    for (int i = 1;; i++)
                    {
                        scanf("%c", &cc);
                        if (cc == ' ')
                            break;
                        word[i + 1] = '\0';
                        word[i] = cc;
                    }
                    scanf("--files /");
                }
                scanf("%[^\n]s", filename);
                int j = 0;
                for (int i = 0;; i++)
                {
                    if (filename[i] == ' ')
                    {
                        j = 0;
                        grep(adress, folder, word, 1);
                        continue;
                    }
                    if (filename[i] == '\0')
                    {
                        grep(adress, folder, word, 1);
                        break;
                    }
                    adress[j + 1] = '\0';
                    adress[j] = filename[i];
                    j++;
                }
            }
            if (c == 'c')
            {
                scanf(" --str "); // for "
                scanf("%c", &cc);
                if (cc == '"')
                {
                    scanf("%[^\"]s", word);
                    scanf("\" --files /");
                }
                else
                {
                    word[0] = cc;
                    word[1] = '\0';
                    for (int i = 1;; i++)
                    {
                        scanf("%c", &cc);
                        if (cc == ' ')
                            break;
                        word[i + 1] = '\0';
                        word[i] = cc;
                    }
                    scanf("--files /");
                }
                scanf("%[^\n]s", filename);
                int j = 0;
                for (int i = 0;; i++)
                {
                    if (filename[i] == ' ')
                    {
                        j = 0;
                        grep(adress, folder, word, 2);
                        continue;
                    }
                    if (filename[i] == '\0')
                    {
                        grep(adress, folder, word, 2);
                        break;
                    }
                    adress[j + 1] = '\0';
                    adress[j] = filename[i];
                    j++;
                }
                printf("%d\n", countergrep);
                countergrep = 0;
            }
        }
        // ------create a new folder & new file------
        else if (strcmp(arr, str) == 0)
        {
            scanf(" ");
            scanf("%c", &c); // scan " or /
            if (c == '"')
            {
                counter++; // bataye halat " "
                scanf("/");
            }
            int j = 0;
            scanf("%[^\n]s", filename);
            while (1)
            {
                if (counter > 0) // file "/root/file.txt"
                {
                    for (int i = 0;; i++)
                    {
                        c = filename[j];
                        j++;
                        if (c == '/')
                        {
                            flag1++; // baraye check sakhtan folder
                            break;
                        }
                        if (c == '"')
                        {
                            goto l;
                        }
                        str[i + 1] = '\0';
                        str[i] = c;
                    }
                    if (flag1 > 0)
                    {
                        if (mkdir(str) == -1)
                        {
                        }
                        chdir(str);
                        flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                    }
                    if (0)
                    {
                    l:
                        if ((folder = fopen(str, "rb")) == NULL)
                        {
                            fclose(folder);
                            folder = fopen(str, "w");
                            fclose(folder);
                            for (int b = 0; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                        else
                        {
                            printf("file already exists\n");
                            fclose(folder);
                            for (int b = 0; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                    }
                    flag1 = 0;
                }
                if (counter == 0) // file /root/file.txt
                {
                    for (int i = 0;; i++)
                    {
                        c = filename[j];
                        j++;
                        if (c == '/')
                        {
                            flag1++; // baraye check sakhtan folder
                            break;
                        }
                        if (c == '\0')
                        {
                            goto l1;
                        }
                        if (c == ' ')
                        {
                            i--;
                            continue;
                        }
                        str[i + 1] = '\0';
                        str[i] = c;
                    }
                    if (flag1 > 0)
                    {
                        if (mkdir(str) == -1)
                        {
                        }
                        chdir(str);
                        flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                    }
                    if (0)
                    {
                    l1:
                        if ((folder = fopen(str, "rb")) == NULL)
                        {
                            fclose(folder);
                            folder = fopen(str, "w");
                            fclose(folder);
                            for (int b = 0; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                        else
                        {
                            printf("file already exists\n");
                            fclose(folder);
                            for (int b = 0; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                    }
                }
            }
            flag1 = 0;
            flag2 = 0;
            counter = 0;
        }
        //------exit------///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr2, str) == 0)
        {
            break;
        }
        //-----insert------/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr3, str) == 0)
        {
            char filename2[MAXSIZE];
            scanf(" ");
            scanf("%c", &c); // scan " or /
            if (c == '"')
            {
                counter++; // bataye halat " "
                scanf("/");
            }
            int j = 0;
            scanf("%[^|]s", filename);
            for (int i = 0;; i++)
            {
                if (filename[i] == '-')
                    break;
                filename2[i + 1] = '\0';
                filename2[i] = filename[i];
            }
            scanf("|pos");
            int line, pos;
            scanf("%d:%d", &line, &pos); // sacn for pos
            while (1)
            { // insert /root/file1.txt--abcd|pos1:2
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '-')
                    {
                        goto l2;
                    }
                    str[i + 1] = '\0';
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l2:
                    if ((folder = fopen(str, "rb")) == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        char strsave[MAXSIZE];
                        int k = 0;
                        folder = fopen(str, "r");
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            strsave[k + 1] = '\0';
                            strsave[k] = c;
                            if (c == '\n')
                                counterenter++;
                            c = fgetc(folder);
                            k++;
                        }
                        strsave[k] = '\0';
                        fclose(folder);
                        int oo;
                        folder = fopen(str, "w");
                        int check = 0;
                        for (oo = 0;; oo++)
                        {
                            if (strsave[oo] == '\n')
                                check++;
                            if (check == line - 1)
                                break;
                        }
                        if (line > 1)
                            oo++; // baraye dar nazar gereftan \n akhar khat
                        for (int b = 0; b <= oo + pos - 1; b++)
                            fputc(strsave[b], folder);
                        int y = 0;
                        while (1)
                        {
                            j++;
                            c = filename[j];
                            if (c == '\0')
                                break;
                            if (c == '\\')
                            {
                                if (filename[j + 1] == 'n')
                                {
                                    if (filename[j - 1] != '\\')
                                    {
                                        c = '\n';
                                        j++;
                                    }
                                }
                            }
                            str[y + 1] = '\0';
                            str[y] = c;
                            y++;
                        }
                        fputs(str, folder);
                        for (int b = oo + pos;; b++)
                        {
                            fputc(strsave[b], folder);
                            if (strsave[b] == '\0')
                                break;
                        }
                        fclose(folder);
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        for (int i = 0;; i++)
                        {
                            if (filename2[i] == '\0')
                                break;
                            if (filename2[i] == '/')
                                filename2[i] = '+';
                        }
                        folder = fopen(filename2, "w");
                        fputs(strsave, folder);
                        fclose(folder);
                        break;
                    }
                }
                flag1 = 0;
            }
        end1:
            flag1 = 0;
            flag2 = 0;
            counter = 0;
        }
        //------cat------///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr4, str) == 0)
        {
            scanf(" --file ");
            scanf("%c", &c); // scan " or /
            if (c == '"')
            {
                counter++; // bataye halat " "
                scanf("/");
            }
            scanf("%[^\n]s", filename);
            int j = 0;
            while (1)
            {
                if (counter == 0) // cat --file /root/filename.txt
                {
                    for (int i = 0;; i++)
                    {
                        c = filename[j];
                        j++;
                        if (c == '/')
                        {
                            flag1++; // baraye check sakhtan folder
                            break;
                        }
                        if (c == '\0')
                        {
                            goto l3;
                        }
                        if (c == ' ')
                        {
                            i--;
                            continue;
                        }
                        str[i + 1] = '\0'; // baraye khali kardan string
                        str[i] = c;
                    }
                    if (flag1 > 0)
                    {
                        int x = chdir(str);
                        if (x == -1)
                        {
                            for (int b = 0; b < flag2; b++)
                                chdir("../");
                            printf("INVALID DIRECTORY: %s\n", str);
                            goto end1;
                        }
                        flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                    }
                    if (0)
                    {
                    l3:
                        folder = fopen(str, "r");
                        if (folder == NULL)
                        {
                            printf("Error! opening file\n");
                            for (int b = 1; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                        else
                        {
                            c = fgetc(folder);
                            while (c != EOF)
                            {
                                printf("%c", c);
                                c = fgetc(folder);
                            }
                            printf("\n");
                            fclose(folder);
                            for (int b = 1; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                    }
                    flag1 = 0;
                }
                if (counter > 0) // file "/root/file.txt"
                {
                    for (int i = 0;; i++)
                    {
                        c = filename[j];
                        j++;
                        if (c == '/')
                        {
                            flag1++; // baraye check sakhtan folder
                            break;
                        }
                        if (c == '"')
                        {
                            goto l4;
                        }
                        str[i + 1] = '\0';
                        str[i] = c;
                    }
                    if (flag1 > 0)
                    {
                        chdir(str);
                        flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                    }
                    if (0)
                    {
                    l4:
                        folder = fopen(str, "r");
                        if (folder == NULL)
                        {
                            printf("Error! opening file\n");
                            for (int b = 1; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                        else
                        {
                            c = fgetc(folder);
                            while (c != EOF)
                            {
                                printf("%c", c);
                                c = fgetc(folder);
                            }
                            printf("\n");
                            fclose(folder);
                            for (int b = 1; b < flag2; b++)
                                chdir("../");
                            break;
                        }
                    }
                    flag1 = 0;
                }
            }
            flag2 = 0;
            counter = 0;
        }
        //-----copy-----///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr5, str) == 0)
        {
            scanf(" ");
            scanf("%c", &c); // scan " or /
            if (c == '"')
            {
                counter++; // bataye halat " "
                scanf("/");
            }
            int j = 0;
            scanf("%[^|]s", filename);
            scanf("|pos");
            int line, pos, size;
            char o;
            scanf("%d:%d-size %d-%c", &line, &pos, &size, &o); // copystr /root/file.txt|pos1:2-size 3-f
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l6;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l6:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        char strsave[MAXSIZE];
                        int k = 0;
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            strsave[k] = c;
                            c = fgetc(folder);
                            k++;
                        }
                        strsave[k] = '\0';
                        int oo;
                        int check = 0;
                        for (oo = 0;; oo++)
                        {
                            if (strsave[oo] == '\n')
                                check++;
                            if (check == line - 1)
                                break;
                        }
                        if (line > 1)
                            oo++; // baraye dar nazar gereftan \n akhar khat
                        if (o == 'f')
                        { // forward
                            int u;
                            for (u = oo + pos; u < oo + pos + size; u++)
                                clipboard[u - oo - pos] = strsave[u];
                            clipboard[u - oo - pos + 1] = '\0';
                        }
                        if (o == 'b')
                        { // backward
                            int u;
                            for (u = oo + pos - size + 1; u < oo + pos + 1; u++)
                                clipboard[u - oo - pos + size - 1] = strsave[u];
                            clipboard[u - oo - pos + size] = '\0';
                        }
                        printf("data in clipboard is : %s\n", clipboard);
                        fclose(folder);
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
        }
        //-----remove-----///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr6, str) == 0)
        {
            char filename2[MAXSIZE], strsave3[MAXSIZE];
            scanf(" ");
            scanf("%c", &c); // scan " or /
            if (c == '"')
            {
                counter++; // bataye halat " "
                scanf("/");
            }
            int j = 0;
            scanf("%[^|]s", filename);
            for (int i = 0;; i++)
            {
                if (filename[i] == '-')
                    break;
                filename2[i + 1] = '\0';
                filename2[i] = filename[i];
            }
            scanf("|pos");
            int line, pos, size;
            char o;
            scanf("%d:%d-size %d-%c", &line, &pos, &size, &o); // removestr /root/file.txt|pos1:2-size 3-f
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l7;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l7:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        char strsave[1000];
                        int k = 0;
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            strsave[k + 1] = '\0';
                            strsave[k] = c;
                            if (c == '\n')
                                counterenter++;
                            c = fgetc(folder);
                            k++;
                        }
                        strsave[k] = '\0';
                        strcpy(strsave3, strsave);
                        int oo;
                        int check = 0;
                        for (oo = 0;; oo++)
                        {
                            if (strsave[oo] == '\n')
                                check++;
                            if (check == line - 1)
                                break;
                        }
                        if (line > 1)
                            oo++; // baraye dar nazar gereftan \n akhar khat
                        fclose(folder);
                        folder = fopen(str, "w+");
                        if (o == 'f')
                        { // forward
                            int u;
                            for (u = oo + pos + size;; u++)
                            {
                                if (strsave[u] == '\0')
                                    break;
                                strsave[u - size] = strsave[u];
                            }
                            strsave[u - size] = '\0';
                        }
                        if (o == 'b')
                        { // backward
                            int u;
                            for (u = oo + pos - size + 1;; u++)
                            {
                                if (strsave[u] == '\0')
                                    break;
                                strsave[u] = strsave[u + size];
                            }
                            strsave[u] = '\0';
                        }
                        fputs(strsave, folder);
                        fclose(folder);
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        chdir("../");
                        for (int i = 0;; i++)
                        {
                            if (filename2[i] == '\0')
                                break;
                            if (filename2[i] == '/')
                                filename2[i] = '+';
                        }
                        folder = fopen(filename2, "w");
                        fputs(strsave3, folder);
                        fclose(folder);
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
        }
        //-----cut-----///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr7, str) == 0)
        {
            char filename2[10000], strsave3[10000];
            scanf(" ");
            scanf("%c", &c); // scan " or /
            if (c == '"')
            {
                counter++; // bataye halat " "
                scanf("/");
            }
            int j = 0;
            scanf("%[^|]s", filename);
            for (int i = 0;; i++)
            {
                if (filename[i] == '-')
                    break;
                filename2[i + 1] = '\0';
                filename2[i] = filename[i];
            }
            scanf("|pos");
            int line, pos, size;
            char o;
            scanf("%d:%d-size %d-%c", &line, &pos, &size, &o); // cutstr /root/file.txt|pos1:2-size 3-f
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l8;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l8:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        char strsave[1000];
                        int k = 0;
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            strsave[k + 1] = '\0';
                            strsave[k] = c;
                            if (c == '\n')
                                counterenter++;
                            c = fgetc(folder);
                            k++;
                        }
                        strsave[k] = '\0';
                        strcpy(strsave3, strsave);
                        int oo;
                        int check = 0;
                        for (oo = 0;; oo++)
                        {
                            if (strsave[oo] == '\n')
                                check++;
                            if (check == line - 1)
                                break;
                        }
                        if (line > 1)
                            oo++; // baraye dar nazar gereftan \n akhar khat
                        /// baraye copy cardan matn///
                        if (o == 'f')
                        { // forward
                            int u;
                            for (u = oo + pos; u < oo + pos + size; u++)
                                clipboard[u - oo - pos] = strsave[u];
                            clipboard[u - oo - pos + 1] = '\0';
                        }
                        if (o == 'b')
                        { // backward
                            int u;
                            for (u = oo + pos - size + 1; u < oo + pos + 1; u++)
                                clipboard[u - oo - pos + size - 1] = strsave[u];
                            clipboard[u - oo - pos + size] = '\0';
                        }
                        printf("data in clipboard is %s\n", clipboard);
                        fclose(folder);
                        /// baraye remove kardan matn
                        folder = fopen(str, "w+");
                        if (o == 'f')
                        { // forward
                            int u;
                            for (u = oo + pos + size;; u++)
                            {
                                if (strsave[u] == '\0')
                                    break;
                                strsave[u - size] = strsave[u];
                            }
                            strsave[u - size] = '\0';
                        }
                        if (o == 'b')
                        { // backward
                            int u;
                            for (u = oo + pos - size + 1;; u++)
                            {
                                if (strsave[u] == '\0')
                                    break;
                                strsave[u] = strsave[u + size];
                            }
                            strsave[u] = '\0';
                        }
                        fputs(strsave, folder);
                        fclose(folder);
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        chdir("../");
                        for (int i = 0;; i++)
                        {
                            if (filename2[i] == '\0')
                                break;
                            if (filename2[i] == '/')
                                filename2[i] = '+';
                        }
                        folder = fopen(filename2, "w");
                        fputs(strsave3, folder);
                        fclose(folder);
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
        }
        //-----paste-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr8, str) == 0)
        {
            char filename2[10000], strsave3[10000];
            scanf(" ");
            scanf("%c", &c); // scan " or /
            if (c == '"')
            {
                counter++; // bataye halat " "
                scanf("/");
            }
            int j = 0;
            scanf("%[^|]s", filename);
            for (int i = 0;; i++)
            {
                if (filename[i] == '-')
                    break;
                filename2[i + 1] = '\0';
                filename2[i] = filename[i];
            }
            scanf("|pos");
            int line, pos;
            scanf("%d:%d", &line, &pos); // pastestr /root/file.txt|pos1:2
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l9;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l9:
                    if ((folder = fopen(str, "rb")) == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        char strsave[1000];
                        int k = 0;
                        folder = fopen(str, "r");
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            strsave[k + 1] = '\0';
                            strsave[k] = c;
                            if (c == '\n')
                                counterenter++;
                            c = fgetc(folder);
                            k++;
                        }
                        strsave[k] = '\0';
                        strcpy(strsave3, strsave);
                        fclose(folder);
                        if (counterenter < line)
                        { // dar ghesmat khali file bayad benevisim
                            folder = fopen(str, "a+");
                            for (int o = 0; o < line - counterenter - 1; o++)
                            {
                                fputc('\n', folder);
                            }
                            for (int o = 0; o < pos; o++)
                                fputc(' ', folder);
                            int y = 0;
                            fputs(clipboard, folder);
                            fclose(folder);
                        }
                        else if (counterenter >= line - 1)
                        { // dat khat por bayad benevisim
                            int oo;
                            folder = fopen(str, "w");
                            int check = 0;
                            for (oo = 0;; oo++)
                            {
                                if (strsave[oo] == '\n')
                                    check++;
                                if (check == line - 1)
                                    break;
                            }
                            if (line > 1)
                                oo++; // baraye dar nazar gereftan \n akhar khat
                            for (int b = 0; b <= oo + pos - 1; b++)
                                fputc(strsave[b], folder);
                            fputs(clipboard, folder);
                            for (int b = oo + pos;; b++)
                            {
                                fputc(strsave[b], folder);
                                if (strsave[b] == '\0')
                                    break;
                            }
                            fclose(folder);
                        }
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        for (int i = 0;; i++)
                        {
                            if (filename2[i] == '\0')
                                break;
                            if (filename2[i] == '/')
                                filename2[i] = '+';
                        }
                        folder = fopen(filename2, "w");
                        fputs(strsave3, folder);
                        fclose(folder);
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
        }
        //-----find-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(arr9, str) == 0)
        {
            int count = 0, all = 0, byword = 0, at = 0, atnumber = 0, wildcard = 0, withcot = 0;
            char word[1000], cc;
            int type = 10;
            char strr[1000];
            scanf(" --str "); // find --str word --file -count -at 3
            scanf("%c", &cc);
            if (cc == '"')
            {
                scanf("%[^\"]s", word);
                scanf("\" --file /");
                withcot++;
            }
            else
            {
                word[0] = cc;
                word[1] = '\0';
                for (int i = 1;; i++)
                {
                    scanf("%c", &cc);
                    if (cc == ' ')
                        break;
                    word[i + 1] = '\0';
                    word[i] = cc;
                }
                scanf("--file /");
            }
            for (int i = 0;; i++)
            {
                if (word[i] == '\0')
                    break;
                if (word[i] == '*' && word[i - 1] != '\\')
                    wildcard++;
                if (word[i] == '*' && word[i - 1] == '\\')
                {
                    for (int j = i;; j++)
                    {
                        if (word[j] == '\0')
                        {
                            word[j - 1] = '\0';
                            break;
                        }
                        word[j - 1] = word[j];
                    }
                }
            }
            scanf("%[^\n]s", strr);
            const char s[4] = " - ";
            char *tok;
            tok = strtok(strr, s);
            int h = 0;
            while (tok != 0)
            {
                if (h == 0)
                    strcpy(filename, tok);
                h++;
                if (strcmp(tok, "count") == 0)
                    count++;
                if (strcmp(tok, "all") == 0)
                    all++;
                if (strcmp(tok, "at") == 0)
                {
                    at++;
                    tok = strtok(0, s);
                    for (int i = 0;; i++)
                    {
                        if (tok[i] == '\0')
                            break;
                        atnumber = atnumber * 10 + (tok[i] - '0');
                    }
                }
                if (strcmp(tok, "byword") == 0)
                    byword++;
                tok = strtok(0, s);
            }
            if (count == 0 && at == 0 && byword == 0 && all == 0) // without option
                type = -1;
            else if (count == 1 && at == 0 && byword == 0 && all == 0) // count
                type = 0;
            else if (count == 0 && at == 1 && byword == 0 && all == 0) // at(be tanhaee kari nmikone)
                type = 1;
            else if (count == 0 && at == 0 && byword == 1 && all == 0) // byword
                type = 2;
            else if (count == 0 && at == 0 && byword == 0 && all == 1) // all
                type = 3;
            else if (count == 0 && at == 1 && byword == 1 && all == 0) // at && byword
                type = 4;
            else if (count == 0 && at == 0 && byword == 1 && all == 1) // all && byword
                type = 5;
            else
            {
                printf("Unknown type\n");
                goto endofcommand;
            }
            int j = 0;
            while (1)
            { // find string --file /root/filename.txt
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l34;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                }
                if (0)
                {
                l34:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        char strsave[MAXSIZE];
                        int y = 0;
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            strsave[y] = c;
                            c = fgetc(folder);
                            y++;
                        }
                        if (wildcard > 0 && withcot > 0)
                        { // complex wildcard
                            int shoamrande1 = 0, shoamrande2 = 1, loop = 0, wordnumber = 0;
                            char beforestar[1000][1000], afterstar[1000][1000];
                            char savestar[1000];
                            int savestarindex = 0;
                            const char s1[4] = " ";
                            char *tok1;
                            tok1 = strtok(word, s1);
                            int beforecounter = 0, aftercounter = 0, sign = 0, before = 0;
                            while (tok1 != 0)
                            {
                                for (int i = 0;; i++)
                                {
                                    if (tok1[i] == '\0')
                                        break;
                                    if (tok1[i] == '*')
                                    {
                                        sign++;
                                        before++;
                                    }
                                }
                                if (sign > 0)
                                { // starword
                                    strcpy(savestar, tok1);
                                }
                                if (sign == 0 && before == 0)
                                { // before starword
                                    strcpy(beforestar[beforecounter], tok1);
                                    beforecounter++;
                                }
                                if (sign == 0 && before > 0)
                                { // after starword
                                    strcpy(afterstar[aftercounter], tok1);
                                    aftercounter++;
                                }
                                tok1 = strtok(0, s1);
                                sign = 0;
                            }
                            const char s[4] = " \n";
                            char *tok;
                            char strsave2[MAXSIZE];
                            strcpy(strsave2, strsave);
                            tok = strtok(strsave2, s);
                            char filewordsaver[100][100];
                            int u = 0, eror = 0;
                            while (tok != 0)
                            {
                                strcpy(filewordsaver[u], tok);
                                tok = strtok(0, s);
                                u++;
                            }
                            for (int i = 0; i < u; i++)
                            {
                                if (match(savestar, filewordsaver[i]))
                                {
                                    if (beforecounter > 0)
                                    {
                                        for (int j = beforecounter - 1; j >= 0; j--)
                                        {
                                            if (strcmp(filewordsaver[i + j - beforecounter], beforestar[j]) != 0)
                                                eror++;
                                        }
                                    }
                                    if (aftercounter > 0)
                                    {
                                        for (int j = 0; j < aftercounter; j++)
                                        {
                                            if (strcmp(filewordsaver[i + j + 1], afterstar[j]) != 0)
                                                eror++;
                                        }
                                    }
                                    if (eror == 0)
                                    {
                                        if (wordnumber == 0) // first word that we find
                                        {
                                            if (type == -1 && beforecounter == 0)
                                            { // without option && staword is the first word
                                                char *p = strstr(strsave, filewordsaver[i]);
                                                printf("%d\n", (p - strsave));
                                            }
                                            else if (type == -1 && beforecounter >= 0)
                                            { // without option && starword isn't rhe first word
                                                char *p = strstr(strsave, beforestar[0]);
                                                printf("%d\n", (p - strsave));
                                            }
                                            if (type == 2) // byword
                                                printf("%d\n", i - beforecounter + 1);
                                        }
                                        if (wordnumber == atnumber - 1 && type == 4)
                                        { // byword , at
                                            printf("%d\n", i - beforecounter + 1);
                                        }
                                        if (type == 5) // byword , all
                                            printf("%d\n", i - beforecounter + 1);
                                        shoamrande1++;
                                        wordnumber++;
                                    }
                                }
                                eror = 0;
                            }
                            if (type == 4 && atnumber > shoamrande1)
                                printf("at number is not valid\n");
                            if (wordnumber == 0)
                                printf("-1\n");
                            if (type == 0 && wordnumber > 0) // count
                                printf("%d\n", shoamrande1);
                        }
                        else if (wildcard > 0 && withcot == 0)
                        { // wildcard
                            int shoamrande1 = 0, shoamrande2 = 1, loop = 0, wordnumber = 0;
                            int x = 0;
                            int length = 0;
                            const char s[4] = " \n";
                            char *tok;
                            char strsave2[MAXSIZE];
                            strcpy(strsave2, strsave);
                            tok = strtok(strsave2, s);
                            while (tok != 0)
                            {
                                x = match(word, tok);
                                if (x == 1)
                                {
                                    if (wordnumber == 0) // first word that we find
                                    {
                                        char *p = strstr(strsave, tok);
                                        if (type == -1) // without option
                                            printf("%d\n", (p - strsave));
                                        if (type == 2) // byword
                                            printf("%d\n", loop + 1);
                                    }
                                    if (wordnumber == atnumber - 1 && type == 4)
                                    { // byword , at
                                        printf("%d\n", loop + 1);
                                    }
                                    char *p = strstr(strsave, tok);
                                    if (type == 3) // all
                                        printf("%d\n", (p - strsave) + (char)length);
                                    if (type == 5) // byword , all
                                        printf("%d\n", loop + 1);
                                    shoamrande1++;
                                    wordnumber++;
                                }
                                length += strlen(tok) + 1;
                                tok = strtok(0, s);
                                loop++;
                            }
                            if (type == 4 && atnumber > shoamrande1)
                                printf("at number is not valid\n");
                            if (wordnumber == 0)
                                printf("-1\n");
                            if (type == 0 && wordnumber > 0) // count
                                printf("%d\n", shoamrande1);
                        }
                        else
                        {
                            int shoamrande1 = 0, shoamrande2 = 1, loop = 0;
                            char *p = strstr(strsave, word);
                            if (p == 0)
                                printf("-1\n");
                            if (p != 0)
                            {
                                if (type == -1) // without option
                                    printf("%d\n", (p - strsave));
                                while (p - strsave <= strlen(strsave))
                                {
                                    for (int i = p - strsave; i >= 0; i--)
                                    {
                                        if (strsave[i] == ' ' || strsave[i] == '\n')
                                            shoamrande2++;
                                    }
                                    if (type == 5) // byword , all
                                        printf("%d\n", shoamrande2);
                                    if (type == 2 && atnumber == 0 && loop == 0) // byword
                                        printf("%d\n", shoamrande2);
                                    if (type == 4)
                                    { // byword , at
                                        if (atnumber == loop + 1)
                                            printf("%d\n", shoamrande2);
                                    }
                                    int place = p - strsave;
                                    if (type == 3)
                                        printf("%d\n", place);
                                    shoamrande1++;
                                    p = strstr(p + (char)strlen(word), word);
                                    loop++;
                                    shoamrande2 = 1;
                                }
                                if (type == 0) // count
                                    printf("%d\n", shoamrande1);
                                if ((type == 1 || type == 4) && atnumber > shoamrande1)
                                    printf("-1\n");
                            }
                        }
                        fclose(folder);
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    flag1 = 0;
                }
            }
            flag2 = 0;
            counter = 0;
        endofcommand:
            printf("");
        }
        //-----str compare-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp("compare", str) == 0)
        {
            int enter1 = 0;
            int enter2 = 0;
            char save[1000][1000];
            char save2[1000][1000];
            char filename2[1000];
            scanf(" /%s /%s", filename, filename2);
            int j = 0;
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l12;
                    }
                    if (c == ' ')
                    {
                        i--;
                        continue;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l12:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        int y = 1;
                        int l = 0;
                        c = fgetc(folder);
                        save[0][0] = c;
                        while (c != EOF)
                        {
                            c = fgetc(folder);
                            if (c == '\n')
                            {
                                enter1++;
                                l++;
                                save[l][y + 1] = '\0';
                                y = 0;
                                continue;
                            }
                            save[l][y + 1] = '\0';
                            save[l][y] = c;
                            y++;
                        }
                        save[l][y - 1] = '\0';
                        fclose(folder);
                        for (int b = 1; b < flag2 + 1; b++)
                            chdir("../");
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
            j = 0;
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename2[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l13;
                    }
                    if (c == ' ')
                    {
                        i--;
                        continue;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l13:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        int y = 1;
                        int l = 0;
                        c = fgetc(folder);
                        save2[0][0] = c;
                        while (c != EOF)
                        {
                            c = fgetc(folder);
                            if (c == '\n')
                            {
                                enter2++;
                                l++;
                                save2[l][y + 1] = '\0';
                                y = 0;
                                continue;
                            }
                            save2[l][y + 1] = '\0';
                            save2[l][y] = c;
                            y++;
                        }
                        save2[l][y - 1] = '\0';
                        fclose(folder);
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
            ////end of saving data
            if (enter1 == enter2)
            {
                for (int l = 0; l <= enter1; l++)
                {
                    if (strcmp(save[l], save2[l]) != 0)
                    {
                        printf("============ #%d ============\n", l + 1);
                        printfcopmare(save[l], save2[l]);
                    }
                }
            }
            if (enter1 > enter2)
            {
                for (int l = 0; l <= enter2; l++)
                {
                    if (strcmp(save[l], save2[l]) != 0)
                    {
                        printf("============ #%d ============\n", l + 1);
                        printfcopmare(save[l], save2[l]);
                    }
                }
                printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", enter2 + 2, enter1 + 1);
                for (int l = enter2 + 1; l <= enter1; l++)
                    printf("%s\n", save[l]);
            }
            if (enter2 > enter1)
            {
                for (int l = 0; l <= enter1; l++)
                {
                    if (strcmp(save[l], save2[l]) != 0)
                    {
                        printf("============ #%d ============\n", l + 1);
                        printfcopmare(save[l], save2[l]);
                    }
                }
                printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", enter1 + 2, enter2 + 1);
                for (int l = enter1 + 1; l <= enter2; l++)
                    printf("%s\n", save2[l]);
            }
        }
        //-----auto indent-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(str, "auto-indent") == 0)
        {
            char saveinfo[10000];
            scanf(" /%s", filename);
            int j = 0;
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l70;
                    }
                    if (c == ' ')
                    {
                        i--;
                        continue;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l70:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        FILE *opentoRead = fopen("temp.txt", "w"); // sakhtan file baraye zakhire data fileasli ke dar akhar hazf mishavad
                        char a = getc(folder);
                        while (a != EOF)
                        { // por kardan file temp ke badan az in data bardarim va tooye file asli berizim
                            fputc(a, opentoRead);
                            a = getc(folder);
                        }
                        fclose(folder);
                        fclose(opentoRead);
                        opentoRead = fopen("temp.txt", "r");
                        folder = fopen(str, "w");
                        int akoladcounter = 0; // shomaresh akolad ha ke har bar be tedad akolad haye baz shode bayad *4 space biyad
                        int spacecounter = 0;
                        char prechar = '\0';
                        a = getc(opentoRead);
                        while (a != EOF)
                        {
                            if (a == '}')
                            {
                                akoladcounter--;
                                if (prechar != '\n')
                                    fputc('\n', folder);
                                for (int i = 0; i < 4 * akoladcounter; i++)
                                {
                                    fputc(' ', folder);
                                }
                                fputc(a, folder);
                                prechar = '}';
                            }
                            else if (a == '{')
                            {
                                if (prechar == '\n')
                                    for (int i = 0; i < 4 * akoladcounter; i++)
                                    {
                                        fputc(' ', folder);
                                    }
                                if (prechar != ' ' && prechar != SEEK_SET && prechar != '\n')
                                    fputc(' ', folder);
                                if (prechar == '}')
                                    fputc('\n', folder);
                                akoladcounter++;
                                fputc(a, folder);
                                fputc('\n', folder);
                                prechar = '\n';
                            }
                            else if (a == ' ')
                            {
                                char b;
                                if (prechar == '}')
                                {
                                    fputc('\n', folder);
                                    prechar = '\n';
                                    continue;
                                }
                                if (prechar == '\n' || prechar == '{')
                                {
                                    while ((b = getc(opentoRead)) == ' ')
                                        ;
                                    a = b;
                                    continue;
                                }
                                spacecounter++;
                                while ((b = getc(opentoRead)) == ' ')
                                {
                                    spacecounter++;
                                }
                                if (b == '{')
                                {
                                    a = b;
                                    spacecounter = 0;
                                    continue;
                                }
                                else if (b == '}')
                                {
                                    a = b;
                                    spacecounter = 0;
                                    continue;
                                }
                                else if (prechar == '\n')
                                {
                                    for (int i = 0; i < 4 * akoladcounter; i++)
                                    {
                                        fputc(' ', folder);
                                    }
                                    for (int i = 0; i < spacecounter; i++)
                                    {
                                        fputc(' ', folder);
                                    }
                                    a = b;
                                    prechar = ' ';
                                    spacecounter = 0;
                                    continue;
                                }
                                else
                                {
                                    for (int i = 0; i < spacecounter; i++)
                                    {
                                        fputc(' ', folder);
                                    }
                                    a = b;
                                    prechar = ' ';
                                    spacecounter = 0;
                                    continue;
                                }
                                spacecounter = 0;
                            }
                            else
                            {
                                if (prechar == '}')
                                    fputc('\n', folder);
                                if (prechar == '}' || prechar == '\n')
                                {
                                    for (int i = 0; i < 4 * akoladcounter; i++)
                                    {
                                        fputc(' ', folder);
                                    }
                                }
                                fputc(a, folder);
                                prechar = a;
                            }
                            a = getc(opentoRead);
                        }
                        fclose(folder);
                        fclose(opentoRead);
                        remove("temp.txt");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
        }
        //-----repalce-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(str, "replace") == 0)
        {
            char cc;
            int type = 10, wildcard = 0;
            int at = 0, atnumber = 0, all = 0;
            char strr[MAXSIZE];
            char str1[MAXSIZE];
            char str2[MAXSIZE];
            scanf(" --str1 ");
            scanf("%c", &cc);
            if (cc == '"')
            {
                scanf("%[^\"]s", str1);
                scanf("\" ");
            }
            else
            {
                str1[0] = cc;
                str1[1] = '\0';
                for (int i = 1;; i++)
                {
                    scanf("%c", &cc);
                    if (cc == ' ')
                        break;
                    str1[i + 1] = '\0';
                    str1[i] = cc;
                }
            }
            scanf("--str2 ");
            scanf("%c", &cc);
            if (cc == '"')
            {
                scanf("%[^\"]s", str2);
                scanf("\" --file /");
            }
            else
            {
                str2[0] = cc;
                str2[1] = '\0';
                for (int i = 1;; i++)
                {
                    scanf("%c", &cc);
                    if (cc == ' ')
                        break;
                    str2[i + 1] = '\0';
                    str2[i] = cc;
                }
                scanf("--file /");
            }
            for (int i = 0;; i++)
            {
                if (str1[i] == '\0')
                    break;
                if (str1[i] == '*')
                    wildcard++;
            }
            scanf("%[^\n]s", strr);
            for (int i = 0;; i++)
            { // remove [] for using strtok
                if (strr[i] == '\0')
                    break;
                if (strr[i] == '[' || strr[i] == ']')
                {
                    for (int j = i;; j++)
                    {
                        if (strr[j] == '\0')
                            break;
                        strr[j] = strr[j + 1];
                    }
                }
            }
            const char s[4] = " - ";
            char *tok;
            tok = strtok(strr, s);
            int h = 0;
            while (tok != 0)
            {
                if (h == 0)
                    strcpy(filename, tok);
                h++;
                if (strcmp(tok, "all") == 0)
                    all++;
                if (strcmp(tok, "at") == 0)
                {
                    at++;
                    tok = strtok(0, s);
                    for (int i = 0;; i++)
                    {
                        if (tok[i] == '\0')
                            break;
                        atnumber = atnumber * 10 + (tok[i] - '0');
                    }
                }
                tok = strtok(0, s);
            }
            if (at == 1 && all == 0) // at
                type = 0;
            else if (at == 0 && all == 1) // all
                type = 1;
            else if (at == 0 && all == 0) // without option
                type = 2;
            else
            {
                printf("Unknown type\n");
                goto endofcommand1;
            }
            int j = 0;
            while (1)
            { // find string --file /root/filename.txt
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l35;
                    }
                    if (c == ' ')
                    {
                        i--;
                        continue;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l35:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        char strsave[MAXSIZE];
                        int y = 0;
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            strsave[y + 1] = '\0';
                            strsave[y] = c;
                            c = fgetc(folder);
                            y++;
                        }
                        char *strsave2 = NULL;
                        char strsave3[MAXSIZE];
                        if (wildcard > 0)
                        { // wildcard
                            int shoamrande1 = 0, shoamrande2 = 1, loop = 0, wordnumber = 0;
                            int x = 0;
                            const char s[4] = " \n";
                            char *tok;
                            strcpy(strsave3, strsave);
                            tok = strtok(strsave3, s);
                            int length = 0;
                            while (tok != 0)
                            {
                                length += strlen(tok) + 1;
                                x = match(str1, tok);
                                if (x == 1)
                                {
                                    if (type == 1 && wordnumber == 0) // all 1
                                    {
                                        strsave2 = replaceWord(strsave, tok, str2, 0, 0);
                                    }
                                    if (type == 1 && wordnumber > 0)
                                    {
                                        strsave2 = replaceWord(strsave2, tok, str2, 0, 0); // all 2
                                    }
                                    if (wordnumber == 0) // first word that we find // without option
                                    {
                                        if (type == 2)
                                            strsave2 = replaceWord(strsave, tok, str2, 0, 0);
                                    }
                                    if (wordnumber == atnumber - 1 && type == 0)
                                    { // at
                                        int repeat = 0;
                                        char *z = strstr(strsave, tok);
                                        while (z - strsave <= (char *)(length - 1))
                                        {
                                            repeat++;
                                            z = strstr(z + (char)strlen(tok), tok);
                                        }
                                        // printf("%d",repeat);
                                        if (repeat == 1)
                                            strsave2 = replaceWord(strsave, tok, str2, 0, 0);
                                        else
                                            strsave2 = replaceWord(strsave, tok, str2, 0, repeat); // be tedad tekrar baraye tekrari ha
                                    }
                                    wordnumber++;
                                }
                                tok = strtok(0, s);
                            }
                            if (wordnumber == 0)
                                printf("str1 does not exist in the file\n");
                            else
                            {
                                printf("replaced successfully :)\n");
                                fclose(folder);
                                folder = fopen(str, "w");
                                fprintf(folder, "%s", strsave2);
                            }
                        }
                        else
                        {
                            char *p = strstr(strsave, str1);
                            if (p == 0)
                                printf("str1 does not exist in the file\n");
                            else
                            {
                                if (type == 1)
                                    strsave2 = replaceWord(strsave, str1, str2, 1, 0); // all
                                if (type == 2)
                                    strsave2 = replaceWord(strsave, str1, str2, 0, 0); // without option
                                if (type == 0)
                                    strsave2 = replaceWord(strsave, str1, str2, 0, atnumber); // at
                                printf("replaced successfully :)\n");
                                fclose(folder);
                                folder = fopen(str, "w");
                                fprintf(folder, "%s", strsave2);
                            }
                        }
                        fclose(folder);
                        free(strsave2);
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        chdir("../");
                        for (int i = 0;; i++)
                        {
                            if (filename[i] == '\0')
                                break;
                            if (filename[i] == '/')
                                filename[i] = '+';
                        }
                        folder = fopen(filename, "w");
                        fputs(strsave, folder);
                        fclose(folder);
                        break;
                    }
                    flag1 = 0;
                }
            }
        endofcommand1:
            printf("");
            flag2 = 0;
            counter = 0;
        }
        //-----tree-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(str, "tree") == 0)
        {
            int depth;
            scanf("%d", &depth);
            if (depth < 1)
                printf("invalid amount for depth it should be greater than 0\n");
            else
                tree("root", 0, depth);
        }
        //-----undo-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(str, "undo") == 0)
        {
            char saveinfo[10000], saveinfo2[10000];
            char filename2[10000];
            scanf(" --file /");
            scanf("%s", filename);
            for (int i = 0;; i++)
            {
                if (filename[i] == '\0')
                    break;
                filename2[i + 1] = '\0';
                if (filename[i] == '/')
                    filename2[i] = '+';
                else
                    filename2[i] = filename[i];
            }
            folder = fopen(filename2, "r");
            c = fgetc(folder);
            int k = 0;
            while (c != EOF)
            {
                saveinfo[k + 1] = '\0';
                saveinfo[k] = c;
                c = fgetc(folder);
                k++;
            }
            int j = 0;
            while (1)
            {
                for (int i = 0;; i++)
                {
                    c = filename[j];
                    j++;
                    if (c == '/')
                    {
                        flag1++; // baraye check sakhtan folder
                        break;
                    }
                    if (c == '\0')
                    {
                        goto l71;
                    }
                    if (c == ' ')
                    {
                        i--;
                        continue;
                    }
                    str[i + 1] = '\0'; // baraye khali kardan string
                    str[i] = c;
                }
                if (flag1 > 0)
                {
                    int x = chdir(str);
                    if (x == -1)
                    {
                        for (int b = 0; b < flag2; b++)
                            chdir("../");
                        printf("INVALID DIRECTORY: %s\n", str);
                        goto end1;
                    }
                    flag2++; // baraye shoamresh tedad bargasht ta residen dobare re root
                }
                if (0)
                {
                l71:
                    folder = fopen(str, "r");
                    if (folder == NULL)
                    {
                        printf("Error! opening file\n");
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        break;
                    }
                    else
                    {
                        int k = 0;
                        c = fgetc(folder);
                        while (c != EOF)
                        {
                            saveinfo2[k + 1] = '\0';
                            saveinfo2[k] = c;
                            c = fgetc(folder);
                            k++;
                        }
                        fclose(folder);
                        folder = fopen(str, "w");
                        fputs(saveinfo, folder);
                        fclose(folder);
                        for (int b = 1; b < flag2; b++)
                            chdir("../");
                        chdir("../");
                        for (int i = 0;; i++)
                        {
                            if (filename[i] == '\0')
                                break;
                            if (filename[i] == '/')
                                filename[i] = '+';
                        }
                        folder = fopen(filename, "w");
                        fputs(saveinfo2, folder);
                        fclose(folder);
                        break;
                    }
                }
                flag1 = 0;
            }
            flag2 = 0;
            counter = 0;
        }
        //-----invlid-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else
        {
            char g;
            scanf("%c", &g);
            if (g == '\n')
                goto error;
            while (g != '\n')
                scanf("%c", &g);
        error:
            printf("Invalid input\n");
        }
        //-----set correct directory-----////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        char cwd[1000];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            char *u = strstr(cwd, "root");
            if (u != 0)
            {
                chdir("../");
            }
        }
    }
    return 0;
}
