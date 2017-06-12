#include<stdio.h>
#include<stdlib.h>

#define MAP_MAX_X 30    //맵 가로 최대 크기
#define MAP_MAX_Y 30    //맵 세로 최대 크기

char user_name[11] = "";//입력받은 사용자 이름
int storage_cnt[5];     //스테이지 별 보관장소(O) 개수
int box_cnt[5];         //스테이지 별 박스($) 개수
int stage_num=-1;       //스테이지 번호
int MAP[5][MAP_MAX_Y][MAP_MAX_X];   //맵

void input_name();      //사용자의 이름을 입력받는 함수
void open_map();        //map.txt 파일로부터 맵을 불러들이는 함수
void draw_map(int);     //불러들인 맵을 출력하는 함수

int main(void)  //아아
{
    printf("Start\n");

    input_name();
    open_map();

    for(int i=0; i<5; i++)
        if(storage_cnt[i]!=box_cnt[i])
        {
            printf("박스의 개수와 보관장소의 개수가 다릅니다. 게임을 종료합니다.\n");
            exit(1);
        }

    printf("이름 : %s\n",user_name);

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
            printf("사용자 이름은 영문 최대 10문자까지 가능합니다. 다시 입력하세요 : ");
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
        printf("파일을 열 수 없습니다.\n");
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
