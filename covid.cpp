#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iterator>

using namespace std;

class Dado{
    string regiao;
    string estado;
    string municipio;
    int coduf;
    int codnum;
    int codRegiaoSaude;
    string nomeRegiaoSaude;
    string data;
    int semanaEpi;
    int populacaoTCU2019;
    int casosAcumulado;
    int casosNovos;
    int obitosAcumulado;
    int obitosNovos;
    int Recuperadosnovos;
    int emAcompanhamentoNovos;
    int interiorMetropolitana;
public:
    Dado(){
        interiorMetropolitana = -1;
    }
    friend int leitura(vector<Dado*> &v, string nome);
    friend void numCasos(vector<Dado*> &v, int op, int i, string s, string dataI, string dataF);
    friend float mediaM(vector<Dado*> &v,int op1, int op2, string s, string data, int janela);
    friend int TotalReg(vector<Dado*> &v, string s, int opcao);
    ~ Dado(){}
};

string PassaS( string &v,int in)
{
	string resp="";
	string respf="";
	char c;
	int j=in;
	int k=0;
	int i;
	while((v[j]!=';')&&(j>-1))
	{
		resp=resp+v[j];
		k=k+1;
		j=j-1;
	}
	for(i=0;i<k;i=i+1)//invertendo a string
	{
		respf=respf+resp[k-1-i];
	}
    if (k==0)
        return "*";
	return respf;
}

int PassaI( string &v,int in)
{
	char c;
	int j=in;
	int k=0;
    int resp = 0;
	while((v[j]!=';')&&(j>-1)){
		resp = resp + (v[j]-48)*pow(10,k);
		k=k+1;
		j=j-1;
	}
    if (k==0)
        return -1;
    return resp;
}

int leitura(vector<Dado*> &v, string nome){
    // Abertura do arquivo
	ifstream arq(nome);
	if(!arq.is_open())
	{
		cout << "Problema na abertura" << endl;
		return -1;
	}
	
	string s;
    //Pega a primeira linha
    getline(arq,s);

    //Pega as proximas
	while (!arq.eof()){
        getline(arq,s);
        if (s.size()<16)
            break;
	    int i=0; //Contador de caracteres na linha
        int j=0; //Contador de ;
        Dado* obj = new Dado; //Instanciacao do novo objeto
        v.push_back(obj); //Adicionando no vector
        while(i<s.size()){
            if (j==16){
                obj->interiorMetropolitana = PassaI(s,i);
            }
            if(s[i]==';'){
                if (j==0)
                    obj->regiao = PassaS(s,i-1);
                if (j==1)
                    obj->estado = PassaS(s,i-1);
                if (j==2)
                    obj->municipio = PassaS(s,i-1);
                if (j==3)
                    obj->coduf = PassaI(s,i-1);
                if (j==4)
                    obj->codnum = PassaI(s,i-1);
                if (j==5)
                    obj->codRegiaoSaude = PassaI(s,i-1);
                if (j==6)
                    obj->nomeRegiaoSaude = PassaS(s,i-1);
                if (j==7)
                    obj->data = PassaS(s,i-1);
                if (j==8)
                    obj->semanaEpi = PassaI(s,i-1);
                if (j==9)
                    obj->populacaoTCU2019 = PassaI(s,i-1);
                if (j==10)
                    obj->casosAcumulado = PassaI(s,i-1);
                if (j==11)
                    obj->casosNovos = PassaI(s,i-1);
                if (j==12)
                    obj->obitosAcumulado = PassaI(s,i-1);
                if (j==13)
                    obj->obitosNovos = PassaI(s,i-1);
                if (j==14)
                    obj->Recuperadosnovos = PassaI(s,i-1);
                if (j==15)
                    obj->emAcompanhamentoNovos = PassaI(s,i-1);
                j=j+1;
            }
            i=i+1;
        }
    }
    arq.close();
    return 1;
}      

void numCasos( vector<Dado*> &v,int op, int i, string s, string dataI, string dataF){
    vector<Dado*>::const_iterator it;
    vector<Dado*>::const_iterator it2;
    int n1 = 0;
    int n2 = 0;
    int q = 0;
    int k = 0;
    for (it=v.begin();it!=v.end();it++){
        if (op==1){ // Total de casos
            if (i==1){ // Total de casos no pais
                if ((*it)->regiao == "Brasil" && (*it)->data == dataI){
                    n1 = (*it)->casosAcumulado;
                    q++;
                }
                if ((*it)->regiao == "Brasil" && (*it)->data == dataF && q==1){
                    n2 = (*it)->casosAcumulado;
                    k++;
                    cout << "O total de novos casos no Brasil entre " << dataI << " e " << dataF << " eh: " << n2-n1 << endl;
                }
            }
            if (i==2){ // Total de caos no estado
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == dataI && (*it)->codnum == -1){
                    n1 = (*it)->casosAcumulado;
                    q++;
                }
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == dataF && q==1 && (*it)->codnum == -1){
                    n2 = (*it)->casosAcumulado;
                    k++;
                    cout << "O total de novos casos no " << s << " entre " << dataI << " e " << dataF << " eh: " << n2-n1 << endl;
                    break;
                }
            }
            if (i==3){ // Total de caos no municipio
                if ((*it)->municipio == s && (*it)->data == dataI){
                    n1 = (*it)->casosAcumulado;
                    q++;
                }
                if ((*it)->municipio == s && (*it)->data == dataF && q==1){
                    n2 = (*it)->casosAcumulado;
                    k++;
                    cout << "O total de novos casos em " << s << " entre " << dataI << " e " << dataF << " eh: " << n2-n1 << endl;
                }
            }
        }
        if (op==2){ // Total de obitos
            if (i==1){ // Total de casos no pais
                if ((*it)->regiao == "Brasil" && (*it)->data == dataI){
                    n1 = (*it)->obitosAcumulado;
                    q++;
                }
                if ((*it)->regiao == "Brasil" && (*it)->data == dataF && q==1){
                    n2 = (*it)->obitosAcumulado;
                    k++;
                    cout << "O total de obitos no Brasil entre " << dataI << " e " << dataF << " eh: " << n2-n1 << endl;
                }
            }
            if (i==2){ // Total de caos no estado
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == dataI && (*it)->codnum == -1){
                    n1 = (*it)->obitosAcumulado;
                    q++;
                }
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == dataF && q==1 && (*it)->codnum == -1){
                    n2 = (*it)->obitosAcumulado;
                    k++;
                    cout << "O total de obitos no " << s << " entre " << dataI << " e " << dataF << " eh: " << n2-n1 << endl;
                    break;
                }
            }
            if (i==3){ // Total de caos no municipio
                if ((*it)->municipio == s && (*it)->data == dataI){
                    n1 = (*it)->obitosAcumulado;
                    q++;
                }
                if ((*it)->municipio == s && (*it)->data == dataF && q==1){
                    n2 = (*it)->obitosAcumulado;
                    k++;
                    cout << "O total de obitos em " << s << " entre " << dataI << " e " << dataF << " eh: " << n2-n1 << endl;
                }
            }
        }
    }
    if (k==0){
        cout << "Informacoes incoerentes" << endl;
    }
}

float mediaM(vector<Dado*> &v,int op1, int op2, string s, string data, int janela){
    vector<Dado*>::const_iterator it;
    vector<Dado*>::const_iterator aux;
    int jan_max = 0;
    int cont = 0;
    string memory="";
    float mm;
    for (it=v.begin();it!=v.end();it++){
        cont = 0;
        if (op1 == 1){ // Mm casos
            if (op2 == 1){ // Mm casos pais
                if ((*it)->regiao == "Brasil" && (*it)->data == "2021-01-01"){
                    jan_max=1;
                }
                if(memory==(*it)->data){
                    jan_max--;
                }
                memory=(*it)->data;
                if ((*it)->regiao == "Brasil" && (*it)->data == data){
                    aux = it;
                    if (janela<=jan_max){
                        for (int i=janela; i>0; i--){
                            cont = cont + (*aux)->casosNovos;
                            aux--;
                        }
                        mm = (float)cont/janela;
                        return mm;
                    }
                    else{
                        return -5;
                    }
                }
                jan_max++;
            }
            if (op2 == 2){ // Mm casos estado
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == "2021-01-01"){
                    jan_max=1;
                }
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == data){
                    aux = it;
                    if (janela<=jan_max){
                        for (int i=janela; i>0; i--){
                            cont = cont + (*aux)->casosNovos;
                            aux--;
                        }
                        mm = (float)cont/janela;
                        return mm;
                    }
                    else
                        return -5;
                }
                jan_max++;
            }
            if (op2 == 3){ // Mm casos municipio
                if ((*it)->municipio == s && (*it)->data == "2021-01-01"){
                    jan_max=1;
                }
                if ((*it)->municipio == s && (*it)->data == data){
                    aux = it;
                        if (janela<=jan_max){
                        for (int i=janela; i>0; i--){
                            cont = cont + (*aux)->casosNovos;
                            aux--;
                        }
                        mm = (float)cont/janela;
                        return mm;
                    }
                    else
                        return -5;
                }
                jan_max++;
            }
        }
        if (op1 == 2){ // Mm mortes
            if (op2 == 1){ // Mm mortes pais
                if ((*it)->regiao == "Brasil" && (*it)->data == "2021-01-01"){
                    jan_max=1;
                }
                if(memory==(*it)->data){
                    jan_max--;
                }
                memory=(*it)->data;
                if ((*it)->regiao == "Brasil" && (*it)->data == data){
                    aux = it;
                        if (janela<=jan_max){
                        for (int i=janela; i>0; i--){
                            cont = cont + (*aux)->obitosNovos;
                            aux--;
                        }
                        mm = (float)cont/janela;
                        return mm;
                    }
                    else
                        return -5;
                }
                jan_max++;
            }
            if (op2 == 2){ // Mm mortes estado
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == "2021-01-01"){
                    jan_max=1;
                }
                if ((*it)->estado == s && (*it)->municipio == "*" && (*it)->data == data){
                    aux = it;
                    if (janela<=jan_max){
                        for (int i=janela; i>0; i--){
                            cont = cont + (*aux)->obitosNovos;
                            aux--;
                        }
                        mm = (float)cont/janela;
                        return mm;
                    }
                    else
                        return -5;
                }
                jan_max++;
            }
            if (op2 == 3){ // Mm mortes municipio
                if ((*it)->municipio == s && (*it)->data == "2021-01-01"){
                    jan_max=1;
                }
                if ((*it)->municipio == s && (*it)->data == data){
                    aux = it;
                    if (janela<=jan_max){
                        for (int i=janela; i>0; i--){
                            cont = cont + (*aux)->obitosNovos;
                            aux--;
                        }
                        mm = (float)cont/janela;
                        return mm;
                    }
                    else
                        return -5;
                }
                jan_max++;
            }
        }
    }
    return -5;
}

int TotalReg( vector<Dado*> &v, string s, int opcao){
    vector<Dado*>::const_iterator it;

    int cont = 0;
    int resp=0;
    int i=0;
    string date;
    //Pegando a ultima data do arquivo
    while(v[i]->regiao == "Brasil"){
        date=v[i]->data;
        i=i+1;
    }
    if(opcao==1){
        for (it=v.begin();it!=v.end();it++){
            if((*it)->regiao == s && (*it)->data == date && (*it)->codnum == -1){
                resp=resp+(*it)->casosAcumulado;
            }
        }
        return resp;
    }
    if(opcao==2){
        for (it=v.begin();it!=v.end();it++){
            if((*it)->regiao == s && (*it)->data == date && (*it)->codnum == -1){
                resp=resp+(*it)->obitosAcumulado;
            }
        }
        return resp;
    }
    return -1;
}

int menu(vector<Dado*> &v){
    int opcao;
    int opcao1;
    int opcao2;
    int janela;
    int janela1;
    int escolha;
    string dataIn1;
    string dataFim1;
    string uf;
    string mun;
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "Qual das informoacoes deseja acessar?\n1 - Total de casos\n2 - Total de obitos\n3 - Media movel\n4 - Tendencia de crescimento\n5 - Dados por regiao" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cin >> opcao;
    if (opcao >= 1 && opcao <= 5){
        if (opcao==1){ // Total de casos
            cout << "Digite a data inicial (no formato ano-mes-dia): ";
            cin >> dataIn1;
            cout << "Digite a data final (no formato ano-mes-dia): ";
            cin >> dataFim1;
            cout << "Se quiser saber dados do pais, digite 1, para dados de um estado, 2 e para municipio, 3: ";
            cin >> opcao1;
            if (opcao1>=1 && opcao1<=3){
                if (opcao1 == 1){ // Brasil
                    numCasos(v, opcao, opcao1, "Brasil", dataIn1, dataFim1);
                }
                if (opcao1 == 2){ // Estado
                    cout << "Digite o UF do estado: ";
                    cin >> uf;
                    numCasos(v, opcao, opcao1, uf, dataIn1, dataFim1);
                }
                if (opcao1 == 3){ // Municipio
                    cout << "Digite o nome do municipio: ";
                    cin.ignore();
                    getline(cin,mun);
                    numCasos(v, opcao, opcao1, mun, dataIn1, dataFim1);
                }
            }
            else{
                cout << "Opcao invalida" << endl;
            }
        }
        if (opcao==2){ // Total de obitos
            cout << "Digite a data inicial (no formato ano-mes-dia): ";
            // criar excecao pra data futura e fora de 2021
            cin >> dataIn1;
            cout << "Digite a data final (no formato ano-mes-dia): ";
            cin >> dataFim1;
            cout << "Se quiser saber dados do pais, digite 1, para dados de um estado, 2 e para municipio, 3: ";
            cin >> opcao1;
            if (opcao1>=1 && opcao1<=3){
                if (opcao1 == 1){ // Brasil
                    numCasos(v, opcao, opcao1, "Brasil", dataIn1, dataFim1);
                }
                if (opcao1 == 2){ // Estado
                    cout << "Digite o UF do estado: ";
                    cin.ignore();
                    cin >> uf;
                    numCasos(v, opcao, opcao1, uf, dataIn1, dataFim1);
                }
                if (opcao1 == 3){ // Municipio
                    cout << "Digite o nome do municipio: ";
                    cin.ignore();
                    getline(cin,mun);
                    numCasos(v, opcao, opcao1, mun, dataIn1, dataFim1);
                }
            }
            else{
                cout << "Opcao invalida" << endl;
            }
        }
        if (opcao==3){ // Media movel
            cout << "Entre com a data (no formato ano-mes-dia): ";
            cin >> dataIn1;
            cout << "Entre com o intervalo de dias: ";
            cin >> janela;
            if (janela>=0){
                cout << "Para consultar a media movel de casos, digite 1. Para obitos, digite 2: ";
                cin >> opcao1;
                if (opcao1==1 || opcao1==2){
                    if (opcao1==1){
                        cout << "Se quiser saber dados do pais, digite 1, para dados de um estado, 2 e para municipio, 3: ";
                        cin >> opcao2;
                        if (opcao2>=1 && opcao2<=3){
                            if (opcao2 == 1){
                                if ((int)mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)!=-5){
                                    cout << "A media movel de casos no Brasil em " << dataIn1 << ", considerando uma janela de " << janela << " dias eh: " << (int)mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela) << endl;
                                }
                                else{
                                    cout << "Dados incoerentes" << endl;
                                }
                            }
                            if (opcao2 == 2){
                                cout << "Digite o UF do estado: ";
                                cin >> uf;
                                if ((int)mediaM(v, opcao1, opcao2, uf, dataIn1, janela)!=-5){
                                    cout << "A media movel de casos no " << uf << " em " << dataIn1 << ", considerando uma janela de " << janela << " dias eh: " << (int)mediaM(v, opcao1, opcao2, uf, dataIn1, janela) << endl;        
                                }
                                else
                                    cout << "Dados incoerentes" << endl;
                            }
                            if (opcao2== 3){
                                cout << "Digite o nome do municipio: ";
                                cin.ignore();
                                getline(cin,mun);
                                if ((int)mediaM(v, opcao1, opcao2, mun, dataIn1, janela)!=-5){
                                    cout << "A media movel de casos em " << mun << " em " << dataIn1 << ", considerando uma janela de " << janela << " dias eh: " << (int)mediaM(v, opcao1, opcao2, mun, dataIn1, janela) << endl;
                                }
                                else
                                    cout << "Dados incoerentes" << endl;
                            }
                        }
                        else{
                            cout << "Opcao invalida" << endl;
                        }
                    }
                    if (opcao1==2){
                        cout << "Se quiser saber dados do pais, digite 1, para dados de um estado, 2 e para municipio, 3: ";
                        cin >> opcao2;
                        if (opcao1>=1 && opcao1<=3){
                            if (opcao2 == 1){
                                if ((int)mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)!=-5){
                                    cout << "A media movel de obitos no Brasil em " << dataIn1 << ", considerando uma janela de " << janela << " dias eh: " << (int)mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela) << endl;
                                }
                                else
                                    cout << "Dados incoerentes" << endl;
                            }
                            if (opcao2 == 2){
                                cout << "Digite o UF do estado: ";
                                cin >> uf;
                                if ((int)mediaM(v, opcao1, opcao2, uf, dataIn1, janela)!=-5){
                                    cout << "A media movel de obitos no " << uf << " em " << dataIn1 << ", considerando uma janela de " << janela << " dias eh: " << (int)mediaM(v, opcao1, opcao2, uf, dataIn1, janela) << endl;
                                }
                                else
                                    cout << "Dados incoerentes" << endl;
                            }
                            if (opcao2== 3){
                                cout << "Digite o nome do municipio: ";
                                cin.ignore();
                                getline(cin,mun);
                                if ((int)mediaM(v, opcao1, opcao2, mun, dataIn1, janela)!=-5){
                                    cout << "A media movel de obitos em " << mun << " em " << dataIn1 << ", considerando uma janela de " << janela << " dias eh: " << (int)mediaM(v, opcao1, opcao2, mun, dataIn1, janela) << endl;
                                }
                                else
                                    cout << "Dados incoetentes" << endl;
                            }
                        }
                        else{
                            cout << "Opcao invalida" << endl;
                        }
                    }
                }
                else{
                    cout << "Opcao invalida" << endl;
                }
            }
            else
                cout << "A janela deve ser um inteiro positivo" << endl;
        }
        if (opcao==4){
            cout << "Entre com a data da media movel: ";
            cin >> dataIn1;
            cout << "Entre com a janela da primeira media movel: ";
            cin >> janela;
            cout << "Entre com a janela da segunda media movel: ";
            cin >> janela1;
            if (janela>=0 && janela1>=0){
                cout << "Para consultar tendencia de casos, digite 1. Para obitos, digite 2: ";
                cin >> opcao1;
                if (opcao1==1 || opcao1==2){
                    if (opcao1==1){ // Tendência de casos
                        cout << "Se quiser saber dados do pais, digite 1, para dados de um estado, 2 e para municipio, 3: ";
                        cin >> opcao2;
                        if (opcao2>=1 && opcao2<=3){
                            if (opcao2 == 1){
                                if (janela>janela1){
                                    if (mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1)!=-5 && mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)!=-5){
                                        cout << "A tendencia de crescimento no numero de casos no Brasil para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1)/mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                                else{
                                    if (mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1)!=-5 && mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)!=-5){
                                        cout << "A tendencia de crescimento no numero de casos no Brasil para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)/mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                            }
                            if (opcao2 == 2){
                                cout << "Digite o UF do estado: ";
                                cin >> uf;
                                if (janela>janela1){
                                    if (mediaM(v, opcao1, opcao2, uf, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, uf, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de casos no " << uf << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, uf, dataIn1, janela1)/mediaM(v, opcao1, opcao2, uf, dataIn1, janela))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                                else{
                                    if (mediaM(v, opcao1, opcao2, uf, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, uf, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de casos no " << uf << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, uf, dataIn1, janela)/mediaM(v, opcao1, opcao2, uf, dataIn1, janela1))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                            }
                            if (opcao2== 3){
                                cout << "Digite o nome do municipio: ";
                                cin.ignore();
                                getline(cin,mun);
                                if (janela>janela1){
                                    if (mediaM(v, opcao1, opcao2, mun, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, mun, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de casos em " << mun << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, mun, dataIn1, janela1)/mediaM(v, opcao1, opcao2, mun, dataIn1, janela))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                                else{
                                    if (mediaM(v, opcao1, opcao2, mun, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, mun, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de casos em " << mun << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, mun, dataIn1, janela)/mediaM(v, opcao1, opcao2, mun, dataIn1, janela1))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                            }
                        }
                        else{
                            cout << "Opcao invalida" << endl;
                        }
                    }
                    if (opcao1==2){ // Tendeência de mortes
                        cout << "Se quiser saber dados do pais, digite 1, para dados de um estado, 2 e para municipio, 3: ";
                        cin >> opcao2;
                        if (opcao2>=1 && opcao2<=3){
                            if (opcao2 == 1){
                                if (janela>janela1){
                                    if (mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de obitos no Brasil para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1)/mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                                else{
                                    if (mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de obitos no Brasil para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela)/mediaM(v, opcao1, opcao2, "Brasil", dataIn1, janela1))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }                            
                            }
                            if (opcao2 == 2){
                                cout << "Digite o UF do estado: ";
                                cin >> uf;
                                if (janela>janela1){
                                    if (mediaM(v, opcao1, opcao2, uf, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, uf, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de obitos no " << uf << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, uf, dataIn1, janela1)/mediaM(v, opcao1, opcao2, uf, dataIn1, janela))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                                else{
                                    if (mediaM(v, opcao1, opcao2, uf, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, uf, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de obitos no " << uf << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, uf, dataIn1, janela)/mediaM(v, opcao1, opcao2, uf, dataIn1, janela1))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                            }
                            if (opcao2== 3){
                                cout << "Digite o nome do municipio: ";
                                cin.ignore();
                                getline(cin,mun);
                                if (janela>janela1){
                                    if (mediaM(v, opcao1, opcao2, mun, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, mun, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de obitos em " << mun << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, mun, dataIn1, janela1)/mediaM(v, opcao1, opcao2, mun, dataIn1, janela))-1)*100 << "%" << endl;
                                    }
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                                else{
                                    if (mediaM(v, opcao1, opcao2, mun, dataIn1, janela)!=-5 && mediaM(v, opcao1, opcao2, mun, dataIn1, janela1)!=-5){
                                        cout << "A tendencia de crescimento no numero de obitos em " << mun << " para as janelas " << janela << " e " << janela1 << " eh: " << ((mediaM(v, opcao1, opcao2, mun, dataIn1, janela)/mediaM(v, opcao1, opcao2, mun, dataIn1, janela1))-1)*100 << "%" << endl;
                                    } 
                                    else
                                        cout << "Dados incoerentes" << endl;
                                }
                            }
                        }
                        else{
                            cout << "Opcao invalida" << endl;
                        }
                    }
                }
                else{
                    cout << "Opcao invalida" << endl;
                }
            }
            else
                cout << "As janelas devem ser inteiros positivos" << endl;
        }

        if (opcao==5){
            cout << "Para consultar total de casos, digite 1. Para obitos, digite 2: ";
            cin >> opcao1;
            if (opcao1==1 || opcao1==2){
                cout << "Digite o nome da regiao (com hifem em \"Centro-Oeste\"): ";
                cin >> uf;
                if (opcao1==1){ // Total de casos
                    if (TotalReg(v, uf, opcao1)!=0){
                        cout << "O total de casos na regiao "<< uf << " eh: " << TotalReg(v, uf, opcao1) << endl;
                    }
                    else
                        cout << "Dados incoerentes" << endl;
                }
                if (opcao1==2){ // Total de obitos
                    if (TotalReg(v, uf, opcao1)!=0){
                        cout<< "O total de obitos na regiao " << uf << " eh: " << TotalReg(v, uf, opcao1) << endl;
                    }
                    else
                        cout << "Dados incoerentes" << endl;
                }
            }
            else{
                cout << "Opcao invalida" << endl;
            }
        }
    }
    else{
        cout << "Opcao invalida" << endl;
    }

    cout << "Digite 0 pra sair e 1 para consultar novos dados: ";
    cin >> escolha;
    if (escolha==0 || escolha==1){
        if (escolha == 0){
            return 0;
        }
        else
            menu(v);
    }
    else{
        cout << "Opcao invalida" << endl;
        menu(v);
    }
    return 1;
}

int main(){
	vector<Dado*> v;
    leitura(v,"parte3.txt");
    menu(v);
    //Deletando os componentes do vector
    vector<Dado*>::const_iterator it;
    for (it=v.begin();it!=v.end();it++){
        delete (*it);
    }
    return 0;
}
