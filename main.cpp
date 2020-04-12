#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

//NECESSARIO DEFINIR AQUI A CAPACIDADE+1
#define CAP 101

using namespace std;

int alfa_fb = 0;
int alfa_pd = 0;

//algoritmo de força bruta
int FB(int M,int *p,int *v,int n){
    alfa_fb++;
    if (n==0 || M==0) return 0;

    if(p[n-1]>M) return FB(M,p,v,n-1);

    return max(FB(M-p[n-1],p,v,n-1)+v[n-1],FB(M,p,v,n-1));
}


//algoritmo top-down
int PD(int M,int *p,int *v,int n, int memo[][CAP]){
    alfa_pd++;

    if (M<=0 || n<=0){
            return 0;
    }
    if (memo[n-1][M]!=-1){
            return memo[n-1][M];
    }
    if (p[n-1]>M){
            return PD(M,p,v,n-1, memo);
    }
    else {
        memo[n-1][M]= max(v[n-1]+PD(M-p[n-1],p,v,n-1,memo),PD(M,p,v,n-1,memo));
    }
    return memo[n-1][M];
}


int main(void){

    clock_t tInicio_FB, tFim_FB, tDecorrido_FB, tInicio_PD, tFim_PD, tDecorrido_PD;
    int capacidade,num_itens;

    ifstream arquivo;
    arquivo.open("instancias/knapsack_n10_R1.txt");

    if(arquivo.is_open());
    arquivo >> num_itens; //le o num de itens da mochila
    arquivo >> capacidade; //le a capacidade da mochila


    int pesos[num_itens];
    int valores[num_itens];
    int memo[num_itens+1][CAP];

    //inicializa a tabela
    for(int i=0;i<num_itens+1;i++){
            for(int j=0;j<(capacidade+1);j++){
                    memo[i][j]=-1;
            }
    }


    //lendo o peso e o valor de cada item
    for(int i=0;i<num_itens;i++){
            arquivo >> pesos[i]; //lendo o arquivo e colocando no array de vertices
            arquivo >> valores[i]; //lendo o arquivo e colocando no array de vertices
    }

    arquivo.close();

    // printando informacoes da mochila//
    cout<<"Informacoes da mochila!"<<endl;
    cout<<"capacidade: "<<capacidade<<endl;
    cout<<"numero de itens: "<<num_itens<<endl;


    tInicio_FB = clock();
    int resultado_FB = FB(capacidade,pesos,valores,num_itens);
    tFim_FB = clock();
    tInicio_PD = clock();
    int resultado_PD = PD(capacidade,pesos,valores,num_itens, memo);
    tFim_PD = clock();

    tDecorrido_PD = ((tFim_PD - tInicio_PD) / (CLOCKS_PER_SEC / 1000));

    cout<<endl<<"resultado FB = "<<resultado_FB<<endl;
    cout<<"tempo FB = "<<tDecorrido_FB<<" ms"<<endl;
    cout<<"alfa_fb = "<<alfa_fb<<endl;
    cout<<endl<<"resultado PD = "<<resultado_PD<<endl;
    cout<<"tempo PD = "<<tDecorrido_PD<<" ms"<<endl;
    cout<<"alfa_pd = "<<alfa_pd<<endl;
    return 0;
}
