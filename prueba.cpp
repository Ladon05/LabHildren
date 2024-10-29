#include <iostream>
#include <string>

using namespace std;

struct Fecha
{
    int dia, mes, ano;
};

struct Empleado
{
    int CI;
    string nombre;
    double sueldo;
    Fecha ingreso, nacimiento, ultimoAscenso;
    Empleado *siguiente;
};

// Función para insertar un nuevo empleado de forma ordenada
void insertar(Empleado **primero, Empleado *nuevo)
{
    Empleado *actual = *primero;
    Empleado *anterior = nullptr;

    while (actual != nullptr && nuevo->sueldo < actual->sueldo)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual;
    if (anterior == nullptr)
    {
        *primero = nuevo;
    }
    else
    {
        anterior->siguiente = nuevo;
    }
}

// Función para mostrar la lista
void mostrarLista(Empleado *primero)
{
    Empleado *actual = primero;
    while (actual != nullptr)
    {
        cout << "CI: " << actual->CI << ", Nombre: " << actual->nombre << ", Sueldo: " << actual->sueldo << endl;
        // Imprimir las fechas en un formato legible
        cout << "Ingreso: " << actual->ingreso.dia << "/" << actual->ingreso.mes << "/" << actual->ingreso.ano << endl;
        // ... imprimir las otras fechas
        actual = actual->siguiente;
    }
}

// Función para buscar un empleado por CI
Empleado *buscarPorCI(Empleado *primero, int CIbuscada)
{
    Empleado *actual = primero;
    while (actual != nullptr && actual->CI != CIbuscada)
    {
        actual = actual->siguiente;
    }
    return actual;
}

// Función para buscar un empleado por sueldo
Empleado *buscarPorSueldo(Empleado *primero, double sueldoBuscado)
{
    Empleado *actual = primero;
    while (actual != nullptr && actual->sueldo != sueldoBuscado)
    {
        actual = actual->siguiente;
    }
    return actual;
}

// Función para buscar empleados por rango de fechas (simplificada para una fecha)
Empleado *buscarPorFechaIngreso(Empleado *primero, Fecha fechaBuscada)
{
    Empleado *actual = primero;
    while (actual != nullptr)
    {
        if (actual->ingreso.dia == fechaBuscada.dia &&
            actual->ingreso.mes == fechaBuscada.mes &&
            actual->ingreso.ano == fechaBuscada.ano)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Función para eliminar un empleado por CI
void eliminarPorCI(Empleado **primero, int CIbuscada)
{
    Empleado *actual = *primero;
    Empleado *anterior = nullptr;

    while (actual != nullptr && actual->CI != CIbuscada)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr)
    {
        if (anterior == nullptr)
        {
            *primero = actual->siguiente;
        }
        else
        {
            anterior->siguiente = actual->siguiente;
        }
        delete actual;
    }
}

void eliminarPorSueldo(Empleado **primero, double sueldoBuscado)
{
    Empleado *actual = *primero;
    Empleado *anterior = nullptr;

    while (actual != nullptr && actual->sueldo != sueldoBuscado)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr)
    {
        // Eliminar el nodo
        if (anterior == nullptr)
        {
            *primero = actual->siguiente;
        }
        else
        {
            anterior->siguiente = actual->siguiente;
        }
        delete actual;
    }
}

// Función para validar si una fecha es válida
bool esFechaValida(int dia, int mes, int ano)
{
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (ano <= 0 || mes <= 0 || mes > 12 || dia <= 0)
    {
        return false;
    }

    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
    {
        diasEnMes[1] = 29; // Febrero tiene 29 días en años bisiestos
    }

    return dia <= diasEnMes[mes - 1];
}
// Función para eliminar un empleado por sueldo (similar a eliminarPorCI)

int main()
{
    Empleado *primero = nullptr;

    // Código para ingresar empleados, buscar, eliminar, etc.
    int opcion;
    do
    {
        cout << "\nMenu de opciones:\n";
        cout << "1. Insertar un nuevo empleado\n";
        cout << "2. Mostrar la lista de empleados\n";
        cout << "3. Buscar un empleado por CI\n";
        cout << "4. Buscar un empleado por sueldo\n";
        cout << "5. Buscar empleados por rango de fechas de ingreso\n";
        cout << "6. Eliminar un empleado por CI\n";
        cout << "7. Eliminar un empleado por sueldo\n";
        cout << "8. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            Empleado *nuevo = new Empleado;

            cout << "Ingrese los datos del nuevo empleado:" << endl;

            cout << "CI: ";
            cin >> nuevo->CI;

            cout << "Nombre: ";
            cin.ignore(); // Limpiar el buffer de entrada
            getline(cin, nuevo->nombre);

            cout << "Sueldo: ";
            cin >> nuevo->sueldo;
            while (nuevo->sueldo <= 0)
            {
                cout << "El sueldo debe ser positivo. Ingrese nuevamente: ";
                cin >> nuevo->sueldo;
            }

            cout << "Fecha de ingreso (dd mm aaaa): ";
            cin >> nuevo->ingreso.dia >> nuevo->ingreso.mes >> nuevo->ingreso.ano;
            while (!esFechaValida(nuevo->ingreso.dia, nuevo->ingreso.mes, nuevo->ingreso.ano))
            {
                cout << "Fecha de ingreso invalida. Ingrese nuevamente (dd mm aaaa): ";
                cin >> nuevo->ingreso.dia >> nuevo->ingreso.mes >> nuevo->ingreso.ano;
            }

            cout << "Fecha de nacimiento (dd mm aaaa): ";
            cin >> nuevo->nacimiento.dia >> nuevo->nacimiento.mes >> nuevo->nacimiento.ano;
            while (!esFechaValida(nuevo->nacimiento.dia, nuevo->nacimiento.mes, nuevo->nacimiento.ano))
            {
                cout << "Fecha de nacimiento inválida. Ingrese nuevamente (dd/mm/aaaa): ";
                cin >> nuevo->nacimiento.dia >> nuevo->nacimiento.mes >> nuevo->nacimiento.ano;
            }

            cout << "Fecha del último ascenso (dd mm aaaa): ";
            cin >> nuevo->ultimoAscenso.dia >> nuevo->ultimoAscenso.mes >> nuevo->ultimoAscenso.ano;
            while (!esFechaValida(nuevo->ultimoAscenso.dia, nuevo->ultimoAscenso.mes, nuevo->ultimoAscenso.ano))
            {
                cout << "Fecha del ultimo ascenso invalida. Ingrese nuevamente (dd mm aaaa): ";
                cin >> nuevo->ultimoAscenso.dia >> nuevo->ultimoAscenso.mes >> nuevo->ultimoAscenso.ano;
            }

            insertar(&primero, nuevo);
            cout << "Empleado agregado correctamente." << endl;
            break;
        }

        case 2:
            mostrarLista(primero);
            break;
        case 3:
        {
            int CIbuscada;
            cout << "Ingrese el CI a buscar: ";
            cin >> CIbuscada;
            Empleado *encontrado = buscarPorCI(primero, CIbuscada);
            if (encontrado)
            {
                cout << "Empleado encontrado:\n";
                cout << "CI: " << encontrado->CI << ", Nombre: " << encontrado->nombre << ", Sueldo: " << encontrado->sueldo << endl;
            }
            else
            {
                cout << "Empleado no encontrado.\n";
            }
            break;
        }
        case 4:
        {
            double sueldoBuscado;
            cout << "Ingrese el sueldo a buscar: ";
            cin >> sueldoBuscado;
            Empleado *encontrado = buscarPorSueldo(primero, sueldoBuscado);
            if (encontrado)
            {
                cout << "Empleado encontrado:\n";
                cout << "CI: " << encontrado->CI << ", Nombre: " << encontrado->nombre << ", Sueldo: " << encontrado->sueldo << endl;
                // Imprimir las fechas del empleado encontrado
                cout << "Ingreso: " << encontrado->ingreso.dia << "/" << encontrado->ingreso.mes << "/" << encontrado->ingreso.ano << endl;
                cout << "Nacimiento: " << encontrado->nacimiento.dia << "/" << encontrado->nacimiento.mes << "/" << encontrado->nacimiento.ano << endl;
                cout << "Último ascenso: " << encontrado->ultimoAscenso.dia << "/" << encontrado->ultimoAscenso.mes << "/" << encontrado->ultimoAscenso.ano << endl;
            }
            else
            {
                cout << "Empleado no encontrado.\n";
            }
            break;
        }
        case 5:
        {
            Fecha fechaInicio, fechaFin;
            cout << "Ingrese el rango de fechas de ingreso (dd mm aaaa):\n";
            // Leer las fechas de inicio y fin
            Empleado *actual = primero;
            while (actual != nullptr)
            {
                if (actual->ingreso.ano >= fechaInicio.ano &&
                    actual->ingreso.ano <= fechaFin.ano &&
                    (actual->ingreso.ano != fechaInicio.ano || actual->ingreso.mes >= fechaInicio.mes) &&
                    (actual->ingreso.ano != fechaFin.ano || actual->ingreso.mes <= fechaFin.mes) &&
                    (actual->ingreso.ano != fechaInicio.ano || actual->ingreso.mes != fechaInicio.mes || actual->ingreso.dia >= fechaInicio.dia) &&
                    (actual->ingreso.ano != fechaFin.ano || actual->ingreso.mes != fechaFin.mes || actual->ingreso.dia <= fechaFin.dia))
                {
                    cout << "Empleado encontrado en el rango:\n";
                }
                actual = actual->siguiente;
            }
            break;
        }
        case 6:
        {
            int CIbuscada;
            cout << "Ingrese el CI del empleado a eliminar: ";
            cin >> CIbuscada;

            eliminarPorCI(&primero, CIbuscada);

            cout << "Empleado eliminado" << endl;
            break;
        }
        case 7:
        {
            double sueldoBuscado;
            cout << "Ingrese el sueldo del empleado a eliminar: ";
            cin >> sueldoBuscado;

            // Modificar la función eliminarPorSueldo para que elimine el primer empleado encontrado
            eliminarPorSueldo(&primero, sueldoBuscado);

            cout << "Empleado eliminado" << endl;
            break;
        }
        case 8:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 8);

    Empleado *actual = primero;
    while (actual != nullptr)
    {
        Empleado *siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    return 0;
}