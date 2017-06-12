#include<stdio.h>
#include<stdlib.h>

#define MAP_MAX_X 30    //�� ���� �ִ� ũ��
#define MAP_MAX_Y 30    //�� ���� �ִ� ũ��

char user_name[11] = "";//�Է¹��� ����� �̸�
int storage_cnt[5];     //�������� �� �������(O) ����
int box_cnt[5];         //�������� �� �ڽ�($) ����
int stage_num=-1;       //�������� ��ȣ
int MAP[5][MAP_MAX_Y][MAP_MAX_X];   //��

void input_name();      //������� �̸��� �Է¹޴� �Լ�
void open_map();        //map.txt ���Ϸκ��� ���� �ҷ����̴� �Լ�
void draw_map(int);     //�ҷ����� ���� ����ϴ� �Լ�

int main(void)
{
    printf("Start\n");

    input_name();
    open_map();

    for(int i=0; i<5; i++)
        if(storage_cnt[i]!=box_cnt[i])
        {
            printf("�ڽ��� ������ ��������� ������ �ٸ��ϴ�. ������ �����մϴ�.\n");
            exit(1);
        }

    printf("�̸� : %s\n",user_name);

    draw_map(stage_num);

    return 0;
}
void input_name()
{
    int i=0, c;
    printf("Input name : ");

    while(1)
    {
        c=getchar();
        if(c<'\n'||(c>'\n'&&c<'A')||(c>'Z'&&c<'a')||c>'z'||i==11)
        {
            while((c=getchar())!='\n')
                ;
            printf("����� �̸��� ���� �ִ� 10���ڱ��� �����մϴ�. �ٽ� �Է��ϼ��� : ");
            i=0;
            continue;
        }
        if(c=='\n')
        {
            user_name[i++]='\0';
            break;
        }
        user_name[i++]=c;
    }
}
void open_map()
{
    FILE *map;
    int x, y;
    char data;
    map=fopen("map.txt","r");
    if(map==NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        exit(1);
    }
    while(fscanf(map, "%c", &data)!=EOF)
    {
        if(data=='m')
        {
            stage_num++;
            x=0;
            y=-1;
            continue;
        }else if(data=='a' || data=='p')
        {
            continue;
        }

        if(data=='e')
            break;

        if(data=='\n')
        {
            y++;
            x=0;
            continue;
        }

        if(data=='O')
            storage_cnt[stage_num]++;

        else if(data=='$')
            box_cnt[stage_num]++;

        MAP[stage_num][y][x]=data;
        x++;
    }
    fclose(map);
}
void draw_map(int stage_num)
{
    for(int i=0; i<MAP_MAX_X; i++)
    {
        for(int j=0; j<MAP_MAX_Y; j++)
            printf("%c", MAP[stage_num][i][j]);
        printf("\n");
    }
}