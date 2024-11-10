#include  <iostream>
using namespace std;

int newton(int ordemAtual,int qntPontos,float** vetorOrdem,float** vetorPontos){//Função recursiva 
    //Verificar se o vetor inserido está completamente zerado, se estiver, retorna;
    if(qntPontos>1){
        int qntZeros(0);
        vetorOrdem[ordemAtual] = (float*)malloc((qntPontos-1)*sizeof(float));//Vai criando até chegar em um vetor com uma posição
        cout << "\nOrdem: " << ordemAtual << endl;
        for(int i = 0;i<qntPontos-1;i++){
            vetorOrdem[ordemAtual][i] = (vetorOrdem[ordemAtual-1][i+1]-vetorOrdem[ordemAtual-1][i])/(vetorPontos[i+1][0]-vetorPontos[i][0]);//Calculo OK
            cout << "F(X"<< i <<"): " << vetorOrdem[ordemAtual][i] << endl;
            if(vetorOrdem[ordemAtual][i] == 0){
                qntZeros++;
            }
        }
        //Verificar se o vetor de resposta atual esta vazio ou não para parar com a recursividade
        if(qntZeros == qntPontos-1){
            return 0;
        }else{
            newton(ordemAtual+1,qntPontos-1,vetorOrdem,vetorPontos);
        }
    }
    return 0;
}

int main(){//Utilizar a main para criar 

    int qntPontos(0),ordemSolicitada(0);
    float **pontos = nullptr;
    float **ordem = nullptr;//Ponteiro onde as ordens serão guardada

    cout << "Quantidade de pontos a ser inserida: ";
    cin >> qntPontos;
    pontos = new float*[qntPontos];//O * de ponteiro tem que ser depois do tipo por algum motivo

    //cout << "Digite a ordem solicitada: ";
    //cin >> ordemSolicitada;
    ordem = (float**)malloc(qntPontos * sizeof(float*));
    ordem[0] = (float*)malloc(qntPontos*sizeof(float));

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

    for(int i = 0;i<qntPontos;i++){//Copia os pontos de X0 para a primeira fileira(ordem 0) para o vetor ordem
        ordem[0][i] = pontos[i][1];//Copiando certo
    }
    
    //Abrir função recursiva
    newton(1,qntPontos,ordem,pontos);

    return 0;
}
