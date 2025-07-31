
// Comision: K1153.
// Profesor: Federico maidan.
// Correo: fedemaidan@frba.utn.edu.ar

// Analisis.cpp

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Sucursal {
    int codigoSucursal;
    char nombreSucursal[30];
};

struct Vendedor {
    int codigo;
    char nombre[30];
    Sucursal sucursal;
};

struct Venta {
    int fecha;
    int codigoVendedor;
    int codigoProducto;
    int monto;
};

int main() {
    vector<Vendedor> vendedores;
    FILE* archVendedores = fopen("vendedores.dat", "rb");
    if (archVendedores) {
        Vendedor v;
        while (fread(&v, sizeof(Vendedor), 1, archVendedores)) {
            vendedores.push_back(v);
        }
        fclose(archVendedores);
    } else {
        cout << "Error al abrir vendedores.dat" << endl;
        return 1;
    }

    map<int, int> ventasPorVendedor;
    map<string, int> ventasPorSucursal;
    map<int, int> rankingProductos;


    FILE* archVentas = fopen("ventas_diarias.dat", "rb");
    if (archVentas) {
        Venta ve;
        while (fread(&ve, sizeof(Venta), 1, archVentas)) {
            ventasPorVendedor[ve.codigoVendedor] += ve.monto;
            rankingProductos[ve.codigoProducto]++;

            for (const auto& v : vendedores) {
                if (v.codigo == ve.codigoVendedor) {
                    ventasPorSucursal[v.sucursal.nombreSucursal] += ve.monto;
                    break;
                }
            }
        }
        fclose(archVentas);
    } else {
        cout << "Error al abrir ventas_diarias.dat" << endl;
        return 1;
    }


    int maxMonto = 0;
    int mejorVendedor = -1;
    for (const auto& par : ventasPorVendedor) {
        if (par.second > maxMonto) {
            maxMonto = par.second;
            mejorVendedor = par.first;
        }
    }
    for (const auto& v : vendedores) {
        if (v.codigo == mejorVendedor) {
            cout << "\nVendedor que más vendió: " << v.nombre << " ($" << maxMonto << ")" << endl;
            break;
        }
    }

    string mejorSucursal;
    int montoMaxSucursal = 0;
    for (const auto& par : ventasPorSucursal) {
        if (par.second > montoMaxSucursal) {
            montoMaxSucursal = par.second;
            mejorSucursal = par.first;
        }
    }
    cout << "Sucursal que más vendió: " << mejorSucursal << " ($" << montoMaxSucursal << ")" << endl;

    vector<pair<int, int>> productosVec(rankingProductos.begin(), rankingProductos.end());
    sort(productosVec.begin(), productosVec.end(), [](auto& a, auto& b) {
        return b.second < a.second;
    });

    cout << "\nRanking de productos más vendidos (por cantidad de ventas):" << endl;
    for (const auto& p : productosVec) {
        cout << "Producto " << p.first << " - Vendido " << p.second << " veces" << endl;
    }

    return 0;
}
