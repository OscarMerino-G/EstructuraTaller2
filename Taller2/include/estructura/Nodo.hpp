template <typename N>
class Nodo {
public:
    N info;
    
    // Nodo doble enlace
    Nodo<N>* next;
    Nodo<N>* prev; 
    // :trollface:
    Nodo();
    explicit Nodo(const N& info);
    Nodo(const N& data, Nodo<N>* next, Nodo<N>* prev = nullptr);
    
    
    ~Nodo();
};
