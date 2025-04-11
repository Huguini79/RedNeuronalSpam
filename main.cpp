// Autor: Huguini79
// Este programa usa la lógica de las redes neuronales ANN
// Este programa lo hice yo solo

#include<iostream>
#include<cmath>
#include<string>
#include<vector>

using namespace std;

vector<string> compras_posibles_dominios;
vector<string> ofertas_posibles_dominios;
vector<string> cargos_posibles_dominios;

float peso = 0.1;
float lr = 0.01;
float porcentaje_completo;
float sesgo_compras = -4.0;
float sesgo_ofertas = -1.0;
float sesgo_cargos = 0.0;
float salidaEsperada = 0;

string categoria;
string dominio;

float longitud_mensaje;

float sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

float derivadaSigmoid(float x) {
    float s = sigmoid(x);
    return s * (1 - s);
}

void rellenar_vectores() {
    compras_posibles_dominios.push_back("hiperdino.es");
    compras_posibles_dominios.push_back("mercadona.es");
    compras_posibles_dominios.push_back("carrefour.es");
    compras_posibles_dominios.push_back("lidl.es");
    compras_posibles_dominios.push_back("ikea.es");

    ofertas_posibles_dominios.push_back("hiperdino.es");
    ofertas_posibles_dominios.push_back("mercadona.es");
    ofertas_posibles_dominios.push_back("carrefour.es");
    ofertas_posibles_dominios.push_back("lidl.es");
    ofertas_posibles_dominios.push_back("ikea.es");

    cargos_posibles_dominios.push_back("bbva.es");
    cargos_posibles_dominios.push_back("caixabank.es");
    cargos_posibles_dominios.push_back("paypal.com");
    cargos_posibles_dominios.push_back("bankinter.com");
    cargos_posibles_dominios.push_back("ing.es");
}

void entrenar(float cantidad, float sesgo) {
    float entrada = cantidad * peso + sesgo;
    float salida = sigmoid(entrada);

    for(int i = 0; i < 11; i++) {
        float error = salidaEsperada - salida;
        float derivada = derivadaSigmoid(entrada);
        peso += lr * error * derivada * cantidad;
        sesgo += lr * error * derivada;

        entrada = cantidad * peso + sesgo;
        salida = sigmoid(entrada);

    }

    porcentaje_completo = salida * 100;
    
    cout << "La Inteligencia Artificial dice que la probabilidad de que el mensaje sea un spam es: " << endl << porcentaje_completo << "%" << endl;

}

int main() {
    rellenar_vectores();
    cout << "Introduce la categoría del mensaje (Compras, Ofertas, Cargos):" << endl;
    cin >> categoria;
    cout << "Introduce el dominio que te escribió, solo el dominio, sin el @gmail ni @hotmail:" << endl;
    cin >> dominio;
    cout << "Introduce la longitud del mensaje:" << endl;
    cin >> longitud_mensaje;
    if(categoria == "Compras") {
        for(auto a_compras : compras_posibles_dominios) {
            if(dominio == a_compras) {
                entrenar(longitud_mensaje, sesgo_compras);
                break;

            } else {
                sesgo_compras += 4;
                entrenar(longitud_mensaje, sesgo_compras);
                break;
            }
        }

    } else if(categoria == "Ofertas") {
        for(auto a_ofertas : ofertas_posibles_dominios) {
            if(dominio == a_ofertas) {
                entrenar(longitud_mensaje, sesgo_ofertas);
                break;

            } else {
                sesgo_ofertas += 2;
                entrenar(longitud_mensaje, sesgo_ofertas);
                break;
            }
        }
    } else if(categoria == "Cargos") {
        for(auto a_cargos : cargos_posibles_dominios) {
            if(dominio == a_cargos) {
                entrenar(longitud_mensaje, sesgo_cargos);
                break;

            } else {
                sesgo_cargos += 2;
                entrenar(longitud_mensaje, sesgo_cargos);
                break;
            }
        }
    } else {
        cout << "Categoría inválida, debes introducir Compras, Ofertas o Cargos." << endl;
    }
}
