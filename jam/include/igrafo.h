#ifndef IGRAFO_H
#define IGRAFO_H
#include <memory>
#include <vector>



class IGrafo {
public:
    virtual ~IGrafo() = default;
    virtual void agregar_arista(int origen, int destino) = 0;
    virtual bool existe_arista(int origen, int destino) const = 0;
    virtual size_t obtener_num_vertices() const = 0;
    virtual const std::vector<int> obtener_adyacentes(int vertice) const = 0;
    [[nodiscard]] virtual std::vector<std::vector<int>> obtener_lista_adyacencia() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IGrafo> obtener_transpuesto() const = 0;


};

#endif //IGRAFO_H
