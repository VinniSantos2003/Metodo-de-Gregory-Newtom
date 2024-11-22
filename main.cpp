#include  <iostream>
#include <math.h>
using namespace std;

int newton(int ordemAtual, int qntPontos, float** vetorOrdem, float** vetorPontos) {
    if (qntPontos > 1) {
        int qntZeros = 0;
        vetorOrdem[ordemAtual] = (float*)malloc((qntPontos - 1) * sizeof(float));
        cout << "\nOrdem: " << ordemAtual << endl;

        for (int i = 0; i < qntPontos - 1; i++) {
            vetorOrdem[ordemAtual][i] = 
                (vetorOrdem[ordemAtual - 1][i + 1] - vetorOrdem[ordemAtual - 1][i]) /
                (vetorPontos[i + ordemAtual][0] - vetorPontos[i][0]);

            cout << "F(X" << i << "): " << vetorOrdem[ordemAtual][i] << endl;

            if (vetorOrdem[ordemAtual][i] == 0) {
                qntZeros++;
            }
        }

        // Verifica se todos os valores da ordem atual são zero, caso positivo, para a recursividade
        if (qntZeros == qntPontos - 1) {
            return 0;
        } else {
            newton(ordemAtual + 1, qntPontos - 1, vetorOrdem, vetorPontos);
        }
    }
    return 0;
}


int main(){//Utilizar a main para criar 
    system("cls");
    int qntPontos(0),grau(0);
    float **pontos = nullptr;
    float **ordem = nullptr;//Ponteiro onde as ordens serão guardada
    float x(0),base(0),preRes(0),fxGrau(0),somatorioX(1),res(0);

    cout << "Quantidade de pontos a ser inserida: ";
    cin >> qntPontos;


    pontos = new float*[qntPontos];//O * de ponteiro tem que ser depois do tipo por algum motivo
    ordem = (float**)malloc(qntPontos * sizeof(float*));
    ordem[0] = (float*)malloc(qntPontos*sizeof(float));
    system("cls");
    for(int i = 0; i<qntPontos;i++){//Armazenar pontos
        pontos[i] = new float[2];
        cout << "Insira o Xi do ponto " << i << ": ";
        cin >> pontos[i][0];    
        cout << "Insira o F(Xi) do ponto " << i <<": "; 
        cin >> pontos[i][1];

    }
    system("cls");//Limpar console
    for(int i = 0; i<qntPontos;i++){//Mostrar pontos
        cout << "Ponto: " << i << endl;
        cout << "Xi: " << pontos[i][0] << " | ";
        cout << "F(xi): " << pontos[i][1] <<endl;
    }
    for(int i = 0;i <qntPontos-1;i++){//Calculo de base
        base = pontos[i+1][0] - pontos[i][0];
    }
    for(int i = 0;i<qntPontos;i++){//Copia os pontos de X0 para a primeira fileira(ordem 0) para o vetor ordem
        ordem[0][i] = pontos[i][1];//Copiando certo
    }
    
    //Abrir função recursiva
    newton(1,qntPontos,ordem,pontos);
    cout << "Insira o valor do X: ";
    cin >> x;
    cout << "Digite grau solicitado: ";
    cin >> grau;
    //Calculo do polinomio
    //O tamanho do calculo vai depender do grau solicitado

    /*Pn(X) = f(X0) + [Primeira ordem]F(X0)/h * (X-X0) + ...*/
    //Somar f(X0) no final de tudo
    for(int i = 0;i<grau;i++){
        fxGrau = ordem[i+1][0];
        for(int j = 0;j<=i;j++){
            somatorioX *= (x-pontos[j][0]);
        }
        //preRes guarda o somatório disso tudo
        preRes += fxGrau * somatorioX;
        fxGrau = 0;
        somatorioX = 1;
    }

    res = ordem[0][0] + preRes;
    
    cout << "Resultado: " << res <<endl;
    //Corrigir resultado: Deu uma unidade acima do esperado
    //Res = 2 ao inves de 1.25
    return 0;
}