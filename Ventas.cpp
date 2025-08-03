
#include <iostream>
#include <stdlib.h>

using namespace std;

struct Venta {
    int fecha;
    int codigoVendedor;
    int codigoProducto;
    int monto;
};

struct Sucursal {
    int codigoSucursal;
    char nombreSucursal[30];
};

struct Vendedor {
    int codigo;
    char nombre[30];
    Sucursal sucursal;
};

bool validarVendedor(int codigoVendedor);
bool puedeAgregarVenta(int fecha);
void guardarVentaEnArchivo(Venta venta);

int main() {
    int opcion;
    do {
        cout << "\n\t----- REGISTRO DE VENTAS -----" << endl;
        cout << "\nOpcion 1: Cargar nueva venta." << endl;
        cout << "Opcion 2: Salir." << endl;
        cout << "\nMarque su opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                system("CLS");
                Venta nuevaVenta;
                cout << "\nIngrese fecha de venta (AAAAMMDD): ";
                cin >> nuevaVenta.fecha;

                if (!puedeAgregarVenta(nuevaVenta.fecha)) {
                    cout << "Ya hay 1000 ventas registradas para esa fecha. No se pueden agregar más." << endl;
                    break;
                }

                cout << "Ingrese código de vendedor: ";
                cin >> nuevaVenta.codigoVendedor;

                if (!validarVendedor(nuevaVenta.codigoVendedor)) {
                    cout << "El vendedor no existe. Venta no registrada." << endl;
                    break;
                }

                cout << "Ingrese código de producto: ";
                cin >> nuevaVenta.codigoProducto;
                cout << "Ingrese monto: ";
                cin >> nuevaVenta.monto;

                guardarVentaEnArchivo(nuevaVenta);
                cout << "Venta registrada correctamente." << endl;
                break;
            }
            case 2:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
        }
    } while (opcion != 2);

    return 0;
}

bool puedeAgregarVenta(int fecha) {
    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    int contador = 0;

    if (archivo != NULL) {
        Venta venta;
        while (fread(&venta, sizeof(Venta), 1, archivo)) {
            if (venta.fecha == fecha) {
                contador++;
                if (contador >= 1000) {
                    fclose(archivo);
                    return false;
                }
            }
        }
        fclose(archivo);
    }

    return true;
}

bool validarVendedor(int codigoVendedor) {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL) {
        cout << "No se pudo abrir 'vendedores.dat'." << endl;
        return false;
    }

    Vendedor vendedor;
    while (fread(&vendedor, sizeof(Vendedor), 1, archivo)) {
        if (vendedor.codigo == codigoVendedor) {
            fclose(archivo);
            return true;
        }
    }

    fclose(archivo);
    return false;
}

void guardarVentaEnArchivo(Venta venta) {
    FILE* archivo = fopen("ventas_diarias.dat", "ab");
    if (archivo == NULL) {
        cout << "No se pudo abrir 'ventas_diarias.dat' para escribir." << endl;
        return;
    }

    fwrite(&venta, sizeof(Venta), 1, archivo);
    fclose(archivo);
}
