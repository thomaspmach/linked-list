// Copyright 2016 Thomas Machado

//! Um método contante
/*!
    \param data
    \return bool
    indica se a lista contém o parâmetro data
*/



#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions


namespace structures {

//! Uma classe
    /*!
    Descreve comportamento de uma lista encadeada
*/
template<typename T>
class LinkedList {
 public:
        //! Contrutor
        /*!
            Construtor default
        */
        LinkedList();

        //! Destrutor
        /*!
            Destrutor default
        */
        ~LinkedList();

        //! Um método
        /*!
            Limpa a lista deletando todos os nodes
        */
        void clear();

        //! Um método
        /*!
            \param data
            Adiona elemento no fim da fila
        */
        void push_back(const T& data);

        //! Um método
        /*!
            \param data
            Adiona elemento no início da fila
        */
        void push_front(const T& data);

        //! Um método
        /*!
            \param data
            \param index
            Adiona elemento na posição indicada por index
        */
        void insert(const T& data, std::size_t index);

        //! Um método
        /*!
            \param data
            Adiona elemento em ordem crescente
        */
        void insert_sorted(const T& data);

        //! Um método
        /*!
            \param index
            Acessa elemento na posição index
        */
        T& at(std::size_t index);

        //! Um método
        /*!
            \param index
            \return T
            Retira elemento da posição index e o retorna
        */
        T pop(std::size_t index);

        //! Um método
        /*!
            \param index
            \return T
            Retira elemento do fim da lista e o retorna
        */
        T pop_back();

        //! Um método
        /*!
            \param index
            \return T
            Retira elemento do início da lista e o retorna
        */
        T pop_front();

        //! Um método
        /*!
            \param data
            Retira elemento data da lista
        */
        void remove(const T& data);  // remover específico

        //! Um método constante
        /*!
            \return bool
            Indica se a lista está vazia ou não
        */
        bool empty() const;  // lista vazia

        //! Um método constante
        /*!
            \param data
            \return bool
            Indica se a lista possui elemento data ou não
        */
        bool contains(const T& data) const;  // contém

        //! Um método constante
        /*!
            \param data
            \return size_t
            Indica posição do elemento data
        */
        std::size_t find(const T& data) const;  // posição do dado

        //! Um método constante
        /*!
            \return size_t
            Indica posição tamanho da lista
        */
        std::size_t size() const;  // tamanho da lista

 private:
        class Node {  // Elemento
         public:
            explicit Node(const T& data):
                data_{data}
            {}

            Node(const T& data, Node* next):
                data_{data},
                next_{next}
            {}

            T& data() {  // getter: dado
                return data_;
            }

            const T& data() const {  // getter const: dado
                return data_;
            }

            Node* next() {  // getter: próximo
                return next_;
            }

            const Node* next() const {  // getter const: próximo
                return next_;
            }

            void next(Node* node) {  // setter: próximo
                next_ = node;
            }

         private:
            T data_;
            Node* next_{nullptr};
        };

        Node* end() {  // último nodo da lista
            auto it = head;
            for (auto i = 1u; i < size(); ++i) {
                it = it->next();
            }
            return it;
        }

        Node* head{nullptr};
        std::size_t size_{0u};
};

template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <class T>
void LinkedList<T>::push_front(const T& data) {
    Node* newNode;
    newNode = new Node(data, head);
    if (newNode == nullptr) {
        throw std::out_of_range("Full List");
    } else {
        head = newNode;
        size_ = size_ + 1;
    }
}

template <class T>
T LinkedList<T>::pop_front() {
    Node* quit;
    T back;
    if (empty()) {
        throw std::out_of_range("Empty List");
    } else {
        quit = head;
        back = quit->data();
        head = quit->next();
        size_ = size_ - 1;
        delete quit;
        return back;
    }
}

template <class T>
bool LinkedList<T>::empty() const {
    return size_ == 0;
}

template <class T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
    Node* newNode;
    Node* previousNode;
    if (index > size_) {
        throw std::out_of_range("Not permitted position");
    } else {
        if (index == 0) {
            push_front(data);
        } else {
            newNode = new Node(data);
            if (newNode == nullptr) {
                throw std::out_of_range("Full List");
            } else {
                previousNode = head;
                for (int i = 0; i < index-1; ++i) {
                    previousNode = previousNode->next();
                }
                newNode->next(previousNode->next());
                previousNode->next(newNode);
                size_ = size_ + 1;
            }
        }
    }
}

template <class T>
T LinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Empty List");
    }
    Node* previousNode;
    Node* deleteNode;
    T back;
    if (index > size_ - 1 || index < 0) {
        throw std::out_of_range("Not permitted position");
    } else {
        if (index == 0) {
            return pop_front();
        } else {
            previousNode = head;
            for (int i = 0; i < index - 1; ++i) {
                previousNode = previousNode->next();
            }
            deleteNode = previousNode->next();
            back = deleteNode->data();
            previousNode->next(deleteNode->next());
            size_ = size_ - 1;
            delete deleteNode;
            return back;
        }
    }
}
template <class T>
void LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template <class T>
T LinkedList<T>::pop_back() {
    return pop(size_-1);
}

template <class T>
void LinkedList<T>::insert_sorted(const T& data) {
    Node* current;
    int position;
    if (empty()) {
        push_front(data);
    } else {
        current = head;
        position = 0;
        while (current->next() != nullptr && data > current->data()) {
            current = current->next();
            ++position;
        }
        if (data > current->data()) {
            return insert(data, position + 1);
        } else {
            return insert(data, position);
        }
    }
}

template <class T>
bool LinkedList<T>::contains(const T& data) const {
    Node* current = head;
    while (current->next() != nullptr) {
        if (current->data() == data) {
            return true;
        }
        current = current->next();
    }
    return false;
}

template <class T>
void LinkedList<T>::clear() {
    Node* current = head;
    Node* previous;
    head = nullptr;
    size_ = 0;
    while (current != nullptr) {
        previous = current;
        current = current->next();
        delete previous;
    }
}

template <class T>
std::size_t LinkedList<T>::find(const T& data) const {
    Node* current = head;
    size_t i = 0;
    while (current != nullptr) {
        if (current->data() == data) {
            return i;
        }
        ++i;
        current = current->next();
    }
    return i;
}

template <class T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

template <class T>
void LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

template <class T>
T& LinkedList<T>::at(std::size_t index)  {
    if (index < 0 || index > size_ - 1) {
        throw std::out_of_range("Out of bounds");
    } else {
        size_t i = 0;
        Node* current = head;
        while (i < index) {
            current = current->next();
            ++i;
        }
        return current->data();
    }
}
}  // namespace structures

#endif


