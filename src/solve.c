#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "city.h"
#include "map.h"
#include "solve.h"

void shuffle(int *array, int num) //適当に配列を並べ替える関数
{
    for (int i = 1; i < num; i++)
    {
        int r;
        r = rand() % (num - i) + i;
        int tmp = array[i];
        array[i] = array[r];
        array[r] = tmp;
    }
}

double solve(const City *city, int n, int *route)
{
    const int smaple_num = 100000;                   //このくらいの回数で求まってくれればうれしいっす
    route[0] = 0;                                    // 循環した結果を避けるため、常に0番目からスタート
    srand((unsigned int)time(NULL));                 //shuffleで使う乱数のシード生成
    Answer ans = (Answer){.dist = 0, .route = NULL}; //ホントはいらないけど一応…
    int *tmp_route = (int *)malloc(sizeof(int) * n); //とりあえずこれをつかって山登りする
    for (int i = 0; i < smaple_num; ++i)             //sample_numだけ初期解を比べる
    {

        for (int j = 0; j < n; ++j) //tmp_routeの初期化
        {
            tmp_route[j] = j;
        }
        shuffle(tmp_route, n); //適当にシャッフル
        double min = -1;
        search(city, n, tmp_route, &min); //山登り法で最小値を求める
        if (i == 0)                       //始めは、一番最初の山登りの結果を最小に設定しておく
        {
            int *retarg = (int *)malloc(sizeof(int) * n);
            memcpy(retarg, tmp_route, sizeof(int) * n);
            ans.dist = min;
            ans.route = retarg;
        }
        else if (ans.dist > min) //複数回の山登りで最小のものを保持
        {
            free(ans.route); //今保持しているものを破棄して更新
            int *retarg = (int *)malloc(sizeof(int) * n);
            memcpy(retarg, tmp_route, sizeof(int) * n);
            ans.dist = min;
            ans.route = retarg;
        }
    }
    memcpy(route, ans.route, sizeof(int) * n);
    free(ans.route);
    return ans.dist;
}

void search(const City *city, int n, int *route, double *min_sum)
{

    int update_flag = 0;                             //min_sumが更新されたらflagを建てる。
    int *tmp_route = (int *)malloc(sizeof(int) * n); //暫定的な最小値を取るルートを格納
    memcpy(tmp_route, route, sizeof(int) * n);
    for (int i = 0; i < n - 1; ++i)
    {
        if (i != 0) //0番目は固定しておく
        {
            int tmp;
            tmp = route[i];
            route[i] = route[i + 1];
            route[i + 1] = tmp;
        }
        double sum_d = 0;
        for (int j = 0; j < n; j++) //経路合計を計算
        {
            const int c0 = route[j];
            const int c1 = route[(j + 1) % n]; // nは0に戻る
            sum_d += distance(city[c0], city[c1]);
        }

        if (*min_sum < 0) //最初はsolveからmin_sumが負で渡される
        {
            update_flag = 1;
            *min_sum = sum_d;
            memcpy(tmp_route, route, sizeof(int) * n);
        }
        else if (*min_sum > sum_d) //最小値更新
        {
            update_flag = 1;
            *min_sum = sum_d;
            memcpy(tmp_route, route, sizeof(int) * n);
        }
    }
    memcpy(route, tmp_route, sizeof(int) * n);
    if (!update_flag) //これ以上更新の余地がないときは終わり
    {
        return;
    }
    {
        search(city, n, route, min_sum);
    }
    free(tmp_route);
    return;
}
