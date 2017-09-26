// O que FALTA!!

// O numero só pode conter apenas digitos
// Passar por referencia na hora de desfavoritar
// Att fav quando add um novo numero


#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

struct Fone{
    string foneId;
    string number;
    Fone(string _foneId = "", string _number = ""){
        foneId = _foneId;
        number = _number;
    }

    string getFoneId(){
        return foneId;
    }
    string getNumber(){
        return number;
    }
};

class Contato{
    string name;
    vector<Fone> fones;
    bool isFavorited{false};
  public:
    Contato(string _nome){
        name = _nome;
    }

    string getNome(){
        return name;
    }

    void setFavotiro(){
        isFavorited = !isFavorited;
    }

    bool getFavorito(){
        return isFavorited;
    }

    vector<Fone> getFones(){
        return fones;
    }


    bool addFone(Fone _fone){
        fones.push_back(_fone);
        return true;
    }

    bool rmFone(string _id){
        for(int i = 0; i < (int) this->fones.size(); i++){
            if(fones[i].getFoneId() == _id){
                fones.erase(fones.begin() + i);
                return true;
            }

        }
        return false;
    }

    bool match(string _pattern){
        for(Fone elemento : fones){
            if((_pattern == elemento.getFoneId()) || (_pattern == elemento.getNumber()))
                return true;
        }
        return false;
    }
};

bool comparaContatos(Contato a, Contato b){
    return a.getNome() < b.getNome();
}

class Agenda{
    vector<Contato> contatos;
    vector<Contato> favoritos;
  public:
    Agenda(){}

    bool addContato(Contato _contato){
        for(Contato elemento : contatos){
            if(elemento.getNome() == _contato.getNome()){
                return false;
            }
        }
        contatos.push_back(_contato);
        return true;
    }

    bool rmContato(string _nome){
        for(int i = 0; i < (int) contatos.size(); i++){
            if(_nome == contatos[i].getNome()){
                contatos.erase(contatos.begin() + i);
                return true;
            }
        }
        return false;
    }

    //FAzer para qualquer parte de uma string
   string search(string _pattern){
       stringstream ss;
       for(Contato elemento : contatos){
           vector<Fone> fones = elemento.getFones();
           if(elemento.getNome() == _pattern){
               ss << "- " << elemento.getNome() << " ";
               for(Fone elemento2 : fones){
                   ss << "[" << elemento2.foneId << " " << elemento2.getNumber() << "] ";
               }
               ss << endl;
           }
           if(elemento.match(_pattern)){
               ss << "- " << elemento.getNome() << " ";
               for(Fone elemento2 : fones){
                   ss << "[" << elemento2.foneId << " " << elemento2.getNumber() << "] ";
               }
               ss << endl;
           }
       }
       return ss.str();
    }

    bool favoritar(string _nome){
        for(Contato& elemento : contatos){
            if(elemento.getNome() == _nome){
                elemento.setFavotiro();
                favoritos.push_back(elemento); // Se eu add um numero depois de add a pessoa a fav, n aparece no vetor de fav
                return true;
            }
        }
        return false;
    }

    bool desfavoritar(string _nome){
        for(int i = 0; i < (int) favoritos.size(); i++){
            if(favoritos[i].getNome() == _nome){
                //passar por referencia pra dar certo mudar
                favoritos[i].setFavotiro();
                favoritos.erase(favoritos.begin() + i);
                return true;
            }
        }
        return false;
    }
    string showFav(){
        stringstream ss;
        std::sort(favoritos.begin(), favoritos.end(), comparaContatos);
        for(Contato elemento : favoritos){
            vector<Fone> fones = elemento.getFones();
            ss << "@ " << elemento.getNome() << " ";
            for(Fone elemento2 : fones){
                ss << "[" << elemento2.getFoneId() << " " << elemento2.getNumber() << "] ";
            }
            ss << endl;
        }
        return ss.str();
    }

    string showContatos(){
        stringstream ss;
        std::sort(contatos.begin(), contatos.end(), comparaContatos);
        for(Contato elemento : contatos){
            vector<Fone> fones = elemento.getFones();
            if(elemento.getFavorito()){
                ss << "@ " << elemento.getNome() << " ";
                for(Fone elemento2 : fones){
                    ss << "[" << elemento2.foneId << " " << elemento2.getNumber() << "] ";
                }
            }else {
                ss << "- " << elemento.getNome() << " ";
                for(Fone elemento2 : fones){
                    ss << "[" << elemento2.foneId << " " << elemento2.getNumber() << "] ";
                }
            }
            ss << endl;
        }
        return ss.str();
    }

    int addFone(string _nome, string _foneId, string _number){
        for(Contato& elemento : contatos){
            if(elemento.getNome() == _nome){
                vector<Fone> fones = elemento.getFones();
                for(Fone& elemento2 : fones){
                    if(elemento2.getFoneId() == _foneId){
                        return -1;
                    }
                    //Precisamos saber o que é esse numero invalido!!
                }
                elemento.addFone(Fone(_foneId, _number));
                return 1;
            }
        }
        return -3;
    }

    int rmFone(string _nome, string _foneId){
        for(Contato& elemento : contatos){
            if(elemento.getNome() == _nome){
                vector<Fone> fones = elemento.getFones();
                for(Fone& elemento2 : fones){
                    if(elemento2.getFoneId() == _foneId){
                        elemento.rmFone(_foneId);
                        return 1;
                    }
                }
                return -2;
            }
        }
        return -1;
    }

};

void inicializar(Agenda& _agenda){
    _agenda.addContato(Contato("Felipe"));
    _agenda.addContato(Contato("Iago"));
    _agenda.addContato(Contato("Iury"));
    _agenda.addContato(Contato("Rafa"));
    _agenda.addFone("Felipe", "oi", "4321");
    _agenda.addFone("Felipe", "tim", "1234");
    _agenda.addFone("Iago", "fixo", "3343");
    _agenda.addFone("Iury", "recado", "6789");
    _agenda.addFone("Rafa", "casa", "9876");
}

void commandLine(Agenda& _agenda){

    string op = "";
    inicializar(_agenda);
    while(op != "fim"){
        cout << "Digite help ou comando: ";
        cin >> op;
        if(op == "help"){
            cout << "addContato $name" << endl
                 << "rmContato" << endl
                 << "showC" << endl
                 << "addFone $nome $foneid $number" << endl
                 << "rmFone $nome $foneid" << endl
                 << "fav $nome" << endl
                 << "desfav $nome" << endl
                 << "showFav" << endl
                 << "search $pattern" << endl

                 << "fim" << endl;
        }

        if(op == "addContato"){
            string nome = read<string>();
            if(_agenda.addContato(Contato(nome))){
                cout << "Contato Adicionado!" << endl;
            }else{
                cout << "Contato ja existe!" << endl;
            }
        }

        if(op == "rmContato"){
            if(_agenda.rmContato(read<string>())){
                cout << "Contato Removido!" << endl;
            }else
                cout << "Contato não existe!" << endl;
        }

        if(op == "showC"){
            cout << _agenda.showContatos() << endl;
        }

        if("addFone" == op){
            string nome = read<string>();
            string foneId = read<string>();
            string number = read<string>();
            int s = _agenda.addFone(nome, foneId, number);

            if(s == -1){
                cout << "FoneId já existe!" << endl;
            }else if(s == -2){
                cout << "Número invalido!" << endl;
            }else if(s == 1){
                cout << "Número adicionado!" << endl;
            }
        }

        if(op == "rmFone"){
            string name = read<string>();
            string foneID = read<string>();
            int s = _agenda.rmFone(name, foneID);
            if(s == 1){
                cout << "Telefone removido!" << endl;
            }else if(s == -1){
                cout << "Nome não encontrado!" << endl;
            }else if(s == -2){
                cout << "FoneId não existe!" << endl;
            }
        }

        if(op == "fav"){
            string nome = read<string>();
            if(_agenda.favoritar(nome))
                cout << nome << " Adicionado aos favoritos!" << endl;
            else
                cout << nome << " não encontrado!" << endl;
        }

        if(op == "desfav"){
            string nome = read<string>();
            if(_agenda.desfavoritar(nome)){
                cout << "Ok" << endl;
            }else{
                cout << nome << " não encontrado/não é favorito!" << endl;
            }
        }

        if(op == "showFav"){
            cout << _agenda.showFav() << endl;
        }

        if(op == "search"){
            cout << _agenda.search(read<string>()) << endl;
        }

    }
}

int main()
{
    Agenda agenda;

    commandLine(agenda);
    return 0;
}