
#include <iostream>
#include <stdlib.h>

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



void insertarSucursal(Sucursal sucursales[], int &len, Sucursal sucursal, int pos);
void insertarSucursalOrdenado(Sucursal sucursales[], int &len, Sucursal sucursal);
int busquedaBinaria(Sucursal sucursales[], int len, int valor);
bool codigoVendedorExiste(Vendedor vendedores[], int len, int codigo);
Vendedor ingresarVendedor(Sucursal sucursales[], int lenSucursales, Vendedor vendedores[], int lenVendedores);
void insertarVendedor(Vendedor vendedores[], int &len, Vendedor vendedor, int pos);
void insertarVendedorOrdenado(Vendedor vendedores[], int &len, Vendedor vendedor);
Sucursal ingresarSucursal();

int main()
{
    int cantidadSucursales = 3, cantidadVendedores = 15;
    Sucursal sucursales[cantidadSucursales];
    int lenSucursales = 0;
    for(int i = 0; i < cantidadSucursales; i++) {
        const Sucursal sucursal = ingresarSucursal();
        insertarSucursalOrdenado(sucursales, lenSucursales, sucursal);
    }

    int lenVendedores = 0;
    Vendedor vendedores[cantidadVendedores];
    for(int i =0; i < cantidadVendedores; i++) {
        const Vendedor vendedor = ingresarVendedor(sucursales, lenSucursales, vendedores, lenVendedores);
        insertarVendedorOrdenado(vendedores, lenVendedores, vendedor);
    }

    FILE* archivo = fopen("vendedores.dat", "wb");
    if(archivo != NULL) {
        fwrite(vendedores, sizeof(Vendedor), lenVendedores, archivo);
        fclose(archivo);
        cout << " Vendedores guardados exitosamente en 'vendedores.dat'. " << endl;
    }else {
        cout << "No se pudo crear el archivo" << endl;
    }

    return 0;
}


Sucursal ingresarSucursal() {
    Sucursal sucursal;
    cout << "Ingrese el codigo de la sucursal: ";
    cin >> sucursal.codigoSucursal;
    cout << "Ingrese el nombre de la sucursal: ";
    cin.ignore();
    cin.getline(sucursal.nombreSucursal, 30);
    return sucursal;
}


void insertarSucursal(Sucursal sucursales[], int &len, Sucursal sucursal, int pos) {
    for (int i = len; i > pos; i--) {
        sucursales[i] = sucursales[i - 1];
    }
    sucursales[pos] = sucursal;
    len++;
}

void insertarSucursalOrdenado(Sucursal sucursales[], int &len, Sucursal sucursal) {
    int i = 0;
    while (i < len && sucursales[i].codigoSucursal <= sucursal.codigoSucursal) {
        i++;
    }
    insertarSucursal(sucursales, len, sucursal, i);
}

int busquedaBinaria(Sucursal sucursales[], int len, int valor) {
    int izquierda = 0;
    int derecha = len - 1;
    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        if (sucursales[medio].codigoSucursal == valor) {
            return medio;
        } else if (sucursales[medio].codigoSucursal < valor) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return -1;
}

bool codigoVendedorExiste(Vendedor vendedores[], int len, int codigo) {
    for (int i = 0; i < len; i++) {
        if (vendedores[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}

Vendedor ingresarVendedor(Sucursal sucursales[], int lenSucursales, Vendedor vendedores[], int lenVendedores) {
    Vendedor vendedor;

    int codigoSucursal;
    int pos = -1;
    while (pos == -1) {
        cout << "Ingrese el codigo de la sucursal del vendedor:";
        cin >> codigoSucursal;
        pos = busquedaBinaria(sucursales, lenSucursales, codigoSucursal);
        if (pos == -1) {
            cout << "Sucursal no encontrada. Intente de nuevo." << endl;
        }
    }
    vendedor.sucursal = sucursales[pos];

    bool valido = false;
    while (!valido) {
        cout << "Ingrese el codigo del vendedor: ";
        cin >> vendedor.codigo;
        if (codigoVendedorExiste(vendedores, lenVendedores, vendedor.codigo)) {
            cout << "Ese código de vendedor ya existe. Ingrese uno distinto." << endl;
        } else {
            valido = true;
        }
    }

    cout << "Ingrese el nombre del vendedor: ";
    cin.ignore();
    cin.getline(vendedor.nombre, 30);

    return vendedor;
}

void insertarVendedor(Vendedor vendedores[], int &len, Vendedor vendedor, int pos) {
    for (int i = len; i > pos; i--) {
        vendedores[i] = vendedores[i - 1];
    }
    vendedores[pos] = vendedor;
    len++;
}

void insertarVendedorOrdenado(Vendedor vendedores[], int &len, Vendedor vendedor) {
    int i = 0;
    while (i < len && vendedores[i].codigo <= vendedor.codigo) {
        i++;
    }
    insertarVendedor(vendedores, len, vendedor, i);
}