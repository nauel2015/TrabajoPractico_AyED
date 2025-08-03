
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

struct ProductoContador
{
    int codigoProducto;
    int cantidad;
};

const int MAX_PRODUCTOS = 100;


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

    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    
    if(archivo==NULL)
    {
        cout << "\n\tError al abrir el archivo de ventas_diarias.dat" << endl;

        cout <<"\nVolviendo al menu.. " << endl;
        system("PAUSE");
        return;
    }

    Venta ventas;
    int montosVendedores [100] = {0};
    while(fread(&ventas, sizeof(Venta), 1, archivo)==1)
    {
        for(int i=0; i<cantVendedores; i++)
        {
            if(ventas.codigoVendedor==vendedor[i].codigo)
            {
                montosVendedores[i] += ventas.monto;
            }
        }
    }

    fclose(archivo);

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
                montosPorSucursal[codigoSucursal] += ventas.monto;
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
    FILE* archVentas = fopen("ventas_diarias.dat", "rb");
    if (archVentas == NULL)
    {
        cout << "Error al abrir archivo de ventas." << endl;
        return;
    }
    
    ProductoContador productos[MAX_PRODUCTOS];
    int lenProductos = 0;
    
    Venta venta;
    while (fread(&venta, sizeof(Venta), 1, archVentas) == 1)
    {
        int pos = -1;
        for (int i = 0; i < lenProductos; i++)
        {
            if (productos[i].codigoProducto == venta.codigoProducto)
            {
                pos = i;
                break;
            }
        }
        
        if ( pos != -1)
        {
          productos[pos].cantidad++;
        } else if (lenProductos < MAX_PRODUCTOS)
                {
                    productos[lenProductos].codigoProducto = venta.codigoProducto;
                    productos[lenProductos].cantidad = 1;
                    lenProductos++;
                }
    }

    fclose(archVentas);

    //Ordenar el array de prod x cantidad de mayor a menor
    // ...
    //Mostrar Ranking
    // ...
}