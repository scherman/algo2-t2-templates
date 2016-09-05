#include <ostream>
#include "TiposBasicos.h"

/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 * 
 * ATENCION: Las únicas cosas que se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template<typename T>
class Pila {
public:

    // Constructor sin parámetros. Crea una pila vacía.
    Pila();

    // Constructor por pila. Crea una nueva instancia de una Pila
    // que debe ser igual a la pasada por parámetro.
    Pila(const Pila &otra);

    // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
    ~Pila();

    // El constructor puede ser visto como un generador
    void apilar(const T &elem);

    // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
    // PRE: la pila no es vacía
    void desapilar();

    // Observadores básicos

    // Devuelve true si la Pila es vacía, false en caso contrario.
    bool esVacia() const;

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    T &tope();

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    const T &tope() const;

    // Otras operaciones

    // Devuelve la cantidad de elementos que hay en la pila.
    aed2::Nat tamanio() const;

    // Modifica esta instancia de Pila de tal manera que termine
    // siendo una pila de la Pila pasada por parámetro.
    // Devuelve una referencia a si misma.
    Pila &operator=(const Pila &otra);

    // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
    // Compara dos instancias de Pila. Devuelve true si son iguales
    // y false en caso contrario.
    bool operator==(const Pila &otra) const;

    /**
     * Muestra la lista en un ostream.
     * formato de salida:
     *   [e_0, e_1, e_2, ...]
     * donde e_i es el resultado del "mostrar" el elemento i.
     * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
     *
     * Nota: imprimir sobre os, es decir: os << "[" << ...
     * 
     * ATENCION:
     * 
     *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
     * 
     *  - El primer elemento que se muestra representa al tope de la pila, es
     *    decir, los elementos se muestran en orden inverso al que fueron apilados.
     */
    template<typename S>
    friend std::ostream &operator<<(std::ostream &os, const Pila<S> &pila);

private:

    struct Nodo {
        Nodo(T e, Nodo* n) : elem(e), sig(n) {};

        T elem;
        Nodo *sig;
    };

    Nodo *tope_;
    aed2::Nat tamanio_;
};

template<typename T>
Pila<T>::Pila() {
    tamanio_ = 0;
    tope_ = NULL;
}

template<typename T>
Pila<T>::Pila(const Pila &otra) {
    tamanio_ = 0;
    tope_ = NULL;
    if (!otra.esVacia()) {
        // Copio todo en una pila auxiliar, porque de entrada me quedan al revez los elementos
        Pila<T> aux;
        for (Nodo* actual = otra.tope_; actual != NULL; actual =  actual->sig) {
            aux.apilar(actual->elem);
        }

        // Voy apilando los nuevos nodos a la nueva pila, en efecto los invierte
        while (aux.tamanio() > 0){
            apilar(aux.tope());
            aux.desapilar();
        }
    }
}

template<typename T>
Pila<T>::~Pila() {
    Nodo* actual = tope_;
    while(actual != NULL){
        Nodo* aux = actual->sig;
        delete actual;
        actual = aux;
    }
}

template<typename T>
void Pila<T>::apilar(const T &elem) {
    tope_ = new Nodo(elem, tope_);
    tamanio_++;
}

template<typename T>
void Pila<T>::desapilar() {
    Nodo* desapilado = tope_;
    tope_ = desapilado->sig;
    delete desapilado;
    this->tamanio_--;
}

template<typename T>
bool Pila<T>::esVacia() const {
    return tamanio_ == 0;
}

template<typename T>
T &Pila<T>::tope() {
    return tope_->elem;
}

template<typename T>
const T &Pila<T>::tope() const {
    return tope_->elem;
}

template<typename T>
aed2::Nat Pila<T>::tamanio() const {
    return this->tamanio_;
}

template<typename T>
Pila<T> &Pila<T>::operator=(const Pila &otra) {
    while(!esVacia()){
        desapilar();
    }
    if (!otra.esVacia()) {
        // Copio todo en una pila auxiliar, porque de entrada me quedan al revez los elementos
        Pila<T> aux;
        for (Nodo* actual = otra.tope_; actual != NULL; actual =  actual->sig) {
            aux.apilar(actual->elem);
        }

        // Voy apilando los nuevos nodos a la nueva pila, en efecto los invierte
        while (aux.tamanio() > 0){
            apilar(aux.tope());
            aux.desapilar();
        }
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Pila<T> &pila) {
    Pila<T> copia (pila);
    os << "[";
    if (!copia.esVacia()){
        os << copia.tope();
        copia.desapilar();
    }
    while(!copia.esVacia()) {
        os << ", " << copia.tope();
        copia.desapilar();
    }
    os << "]";
}
