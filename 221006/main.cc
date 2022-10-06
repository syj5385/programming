#include <stdio.h>
#include <utility>
#include <string.h>

using namespace std; 

#define rotR(i) (i==3 ? 0 : i+1)
#define rotL(i) (i==0 ? 3 : i-1)
int action[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

int N, M, max_block=0, remain_in_max;
int m[15][15] = {0, };
int v[15][15] = {0, };

bool isInside(int row, int col){
    if(row>=0 && row<N && col>=0 && col<N)
        return true;
    return false; 
}

void search(int row, int col, int dir, int num, int remain, int depth){
    int i;
    int n_row = row + action[dir][0], n_col = col + action[dir][1];
    if(m[row][col] == 1){
        if (isInside(n_row, n_col) == true && v[n_row][n_col] == 0){
            v[row][col] = 1;
            search(n_row, n_col, dir, num+1, remain, depth+1);
            v[row][col] = 0;
        }
    }
    else if (m[row][col] == 0 && remain){
        int dir_list[3] = {rotL(dir), dir, rotR(dir)};
        for(i=0; i<3; i++){
            int n_row = row + action[dir_list[i]][0], n_col = col + action[dir_list[i]][1];
            if(isInside(n_row, n_col) == false || v[n_row][n_col] == 1)
                continue; 
            v[row][col] = 1;
            search(n_row, n_col, dir_list[i], num, remain-1, depth+1);
            v[row][col] = 0;
        }
    }

    if(num > max_block){
        m[row][col] == 0 ? max_block = num-1: max_block= num; 
        remain_in_max = remain; 
    }
    
    return;
}

int main(){
    int tc, i;
    freopen("input.txt", "r", stdin);
    scanf("%d", &tc);

    for(i=1; i<=tc; i++){
        int j, k;
        
        memset(m, 0, sizeof(int)*255);
        memset(v, 0, sizeof(int)*255);
        max_block = 0;
        remain_in_max = 0;
        scanf("%d%d", &N, &M);

        for(j=0; j<N; j++){
            for (k=0; k<N; k++)
                scanf("%d", &m[j][k]);
        }

        search(0, 0, 0, 0, M,0);
        printf("#%d %d\n", i, max_block+1);
    }
}