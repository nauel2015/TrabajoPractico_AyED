
// Comision: K1153.
// Profesor: Federico maidan.
// Correo: fedemaidan@frba.utn.edu.ar

// Analisis.cpp

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Sucursal 
{
    int codigoSucursal;
    char nombreSucursal[30];
};

struct Vendedor 
{
    int codigo;
    char nombre[30];
    Sucursal sucursal;
};

struct Venta 
{
    int fecha;
    int codigoVendedor;
    int codigoProducto;
    int monto;
};

// Declaracion de las funciones.
void mejorVendedor();
void mejorSucursal();
void rankingProductosMasVendidos();

int main()
{
    int opcion;

    do{
        cout <<"\n\tAnalisis de ventas. " << endl;
        cout <<"\nOpcion 1: Ver vendedor que mas dinero genero. ";
        cout <<"\nOpcion 2: Ver sucursal que mas dinero genero. ";
        cout <<"\nOpcion 3: Ver ranking de productos mas vendidos. ";
        cout <<"\nOpcion 4: Salir. " << endl;
        
        cout <<"\nSeleccione su opcion: "; cin >> opcion;

        switch(opcion)
        {
            case 1: system("CLS"); mejorVendedor(); system("CLS"); break;
            case 2: system("CLS"); mejorSucursal(); system("CLS"); break;
            case 3: system("CLS"); rankingProductosMasVendidos(); system("CLS"); break;
            case 4: cout <<"\nHasta luego. " << endl; break;
        }
        
    }while(opcion!=4);


    system("PAUSE");
    return 0;
}

// Definicion de las funciones.
void mejorVendedor()
{
    FILE* archivo = fopen("vendedores.dat", "rb");
    
    if(archivo==NULL)
    {
        cout << "\n\tError al abrir el archivo de vendedores.dat" << endl;

        cout <<"\nVolviendo al menu.. " << endl;
        system("PAUSE");
        return;
    }

    Vendedor vendedor[100];
    int cantVendedores=0;
    while(fread(&vendedor[cantVendedores], sizeof(Vendedor), 1, archivo)==1)
    {
        cantVendedores++;
    }

    fclose(archivo);

    FILE* archivoVentas = fopen("ventas_diarias.dat", "rb");
    
    if(archivoVentas==NULL)
    {
        cout << "\n\tError al abrir el archivo de ventas_diarias.dat" << endl;

        cout <<"\nVolviendo al menu.. " << endl;
        system("PAUSE");
        return;
    }

    Venta ventas;
    int montosVendedores [100] = {0};
    while(fread(&ventas, sizeof(Venta), 1, archivoVentas)==1)
    {
        for(int i=0; i<cantVendedores; i++)
        {
            if(ventas.codigoVendedor==vendedor[i].codigo)
            {
                montosVendedores[i] += ventas.monto;
            }
        }
    }

    fclose(archivoVentas);

    int posMejorVendedor=0;
    for(int i=1; i<cantVendedores; i++)
    {
        if(montosVendedores[i]>montosVendedores[posMejorVendedor])
        {
            posMejorVendedor = i;
        }
    }

    cout << "Vendedor que mas dinero genero: " << vendedor[posMejorVendedor].nombre << endl;
    cout << "Total generado: $" << montosVendedores[posMejorVendedor] << endl;

    cout <<"\nVolviendo al menu.. " << endl;
    system("PAUSE");
}

void mejorSucursal()
{
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL)
    {
        cout << "\n\tError al abrir el archivo vendedores.dat" << endl;

        cout <<"\nVolviendo al menu.. " << endl;
        system("PAUSE");
        return;
    }

    Vendedor vendedores[100];
    int cantVendedores = 0;

    while (fread(&vendedores[cantVendedores], sizeof(Vendedor), 1, archivo)==1)
    {
        cantVendedores++;
    }

    fclose(archivo);

    int cantSucursales=10; 
    int montosPorSucursal[cantSucursales] = {0};
    char nombresSucursal[cantSucursales][30] = {0};

    for (int i=0; i<cantVendedores; i++)
    {
        int codigoSucursal = vendedores[i].sucursal.codigoSucursal;
        strcpy(nombresSucursal[codigoSucursal], vendedores[i].sucursal.nombreSucursal);
    }

    FILE* archivoVentas = fopen("ventas_diarias.dat", "rb");
    if (archivoVentas == NULL)
    {
        cout << "\n\tError al abrir el archivo ventas_diarias.dat" << endl;

        cout <<"\nVolviendo al menu.. " << endl;
        system("PAUSE");
        return;
    }

    Venta ventas;
    while(fread(&ventas, sizeof(Venta), 1, archivoVentas)==1)
    {
        for (int i=0; i<cantVendedores; i++)
        {
            if(ventas.codigoVendedor==vendedores[i].codigo)
            {
                int codigoSucursal = vendedores[i].sucursal.codigoSucursal;
                if (codigoSucursal >= 0 && codigoSucursal < cantSucursales)
                {
                    montosPorSucursal[codigoSucursal] += ventas.monto;
                }

                break;
            }
        }
    }

    fclose(archivoVentas);

    int mejorSucursal=0;
    for (int i=1; i<cantSucursales; i++)
    {
        if (montosPorSucursal[i]>montosPorSucursal[mejorSucursal])
        {
            mejorSucursal = i;
        }
    }

    cout << "\nSucursal que más dinero generó: " << nombresSucursal[mejorSucursal] << endl;
    cout << "Total generado: $" << montosPorSucursal[mejorSucursal] << endl;

    cout <<"\nVolviendo al menu.. " << endl;
    system("PAUSE");
}

void rankingProductosMasVendidos()
{
    
}


/*
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
*/