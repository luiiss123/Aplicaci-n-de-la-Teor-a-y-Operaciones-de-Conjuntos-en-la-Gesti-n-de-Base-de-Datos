#include <iostream>
#include <set>
#include <string>
#include <chrono>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;
using namespace chrono;

//==================================================
// ESTRUCTURA ESTUDIANTE
//==================================================

struct Estudiante {
    int codigo;
    string nombre;
    string carrera;
    int semestre;

    bool operator<(const Estudiante& otro) const {
        return codigo < otro.codigo;
    }
};

//==================================================
// MOTOR DE CONJUNTOS
//==================================================

class MotorConjuntos {

public:

    static set<Estudiante> unir(
        const set<Estudiante>& A,
        const set<Estudiante>& B) {

        set<Estudiante> resultado = A;

        for (const auto& e : B)
            resultado.insert(e);

        return resultado;
    }

    static set<Estudiante> interseccion(
        const set<Estudiante>& A,
        const set<Estudiante>& B) {

        set<Estudiante> resultado;

        for (const auto& e : A) {

            if (B.find(e) != B.end())
                resultado.insert(e);
        }

        return resultado;
    }

    static set<Estudiante> diferencia(
        const set<Estudiante>& A,
        const set<Estudiante>& B) {

        set<Estudiante> resultado;

        for (const auto& e : A) {

            if (B.find(e) == B.end())
                resultado.insert(e);
        }

        return resultado;
    }
};

//==================================================
// FUNCIONES DE APOYO
//==================================================

void linea() {
    cout << "\n============================================================\n";
}

void mostrarTitulo(string titulo) {

    linea();
    cout << titulo;
    linea();
}

void mostrarEstudiantes(const set<Estudiante>& conjunto)
{
    cout << left
         << setw(10) << "CODIGO"
         << setw(40) << "NOMBRE COMPLETO"
         << setw(15) << "CARRERA"
         << setw(10) << "SEMESTRE"
         << endl;

    cout << string(80,'-') << endl;

    for(const auto& e : conjunto)
    {
        cout << left
             << setw(10) << e.codigo
             << setw(40) << e.nombre
             << setw(15) << e.carrera
             << setw(10) << e.semestre
             << endl;
    }

    cout << "\nCardinalidad (N): "
         << conjunto.size()
         << endl;
}

string formatearNombre(string texto)
{
    bool nuevaPalabra = true;

    for(char &c : texto)
    {
        if(nuevaPalabra && isalpha((unsigned char)c))
        {
            c = toupper((unsigned char)c);
            nuevaPalabra = false;
        }
        else
        {
            c = tolower((unsigned char)c);
        }

        if(c == ' ')
            nuevaPalabra = true;
    }

    return texto;
}

int leerCodigo() {

    string codigo;

    while(true) {

        cout << "\nCodigo (4 digitos): ";
        cin >> codigo;

        bool valido = true;

        if(codigo.length() != 4)
            valido = false;

        for(char c : codigo) {

            if(!isdigit(c))
                valido = false;
        }

        if(valido)
            return stoi(codigo);

        cout << "\n Debe ingresar exactamente 4 numeros.\n";
    }
}

int leerSemestre() {

    int semestre;

    while(true) {

        cout << "Semestre (0-8): ";
        cin >> semestre;

        if(cin.fail()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n Solo se permiten numeros.\n";
            continue;
        }

        if(semestre >= 0 && semestre <= 8)
            return semestre;

        cout << "\n El semestre debe estar entre 0 y 8.\n";
    }
}

int leerOpcion() {

    int opcion;

    while(true) {

        cin >> opcion;

        if(cin.fail()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nOpcion invalida. Ingrese un numero entre 0 y 10: ";
            continue;
        }

        if(opcion >= 0 && opcion <= 10)
            return opcion;

        cout << "\nOpcion invalida. Ingrese un numero entre 0 y 10: ";
    }
}

bool nombreValido(const string& nombre)
{
    for(char c : nombre)
    {
        if(!isalpha((unsigned char)c) && c != ' ')
        {
            return false;
        }
    }

    return true;
}

void agregarEstudiante(set<Estudiante>& conjunto)
{
    Estudiante nuevo;

    nuevo.codigo = leerCodigo();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while(true)
    {
    cout << "Nombre completo (2 nombres y 2 apellidos): ";
    getline(cin, nuevo.nombre);

    if(!nombreValido(nuevo.nombre))
    {
        cout << "\n Solo se permiten letras y espacios.\n\n";
        continue;
    }

    int palabras = 0;
    bool dentroPalabra = false;

    for(char c : nuevo.nombre)
    {
        if(c != ' ' && !dentroPalabra)
        {
            palabras++;
            dentroPalabra = true;
        }
        else if(c == ' ')
        {
            dentroPalabra = false;
        }
    }

    if(palabras == 4)
        break;

    cout << "\n Debe ingresar exactamente 2 nombres y 2 apellidos.\n\n";
    }   

    nuevo.nombre = formatearNombre(nuevo.nombre);

    nuevo.carrera = "Software";

    nuevo.semestre = leerSemestre();

    auto resultado = conjunto.insert(nuevo);

    if(resultado.second)
    {
        cout << "\n Estudiante agregado correctamente.\n";

        cout << "\n";
        cout << string(70,'-') << endl;

        cout << left
             << setw(10) << "CODIGO"
             << setw(40) << "NOMBRE COMPLETO"
             << setw(10) << "SEMESTRE"
             << endl;

        cout << string(70,'-') << endl;

        cout << left
             << setw(10) << nuevo.codigo
             << setw(40) << nuevo.nombre
             << setw(10) << nuevo.semestre
             << endl;
    }
    else
    {
        cout << "\n Es invalido ya que el codigo esta duplicado.\n";
        cout << "Ley de Idempotencia aplicada (A U A = A).\n";
    }
}

void mostrarMetricas(
    const set<Estudiante>& A,
    const set<Estudiante>& B,
    const set<Estudiante>& interseccion) {

    int total = A.size() + B.size();

    int duplicados = interseccion.size();

    double redundancia = 0;

    if(total > 0)
        redundancia =
            (double)duplicados /
            total * 100;

    cout << fixed << setprecision(2);

    cout << "\nTotal registros: "
         << total;

    cout << "\nDuplicados detectados: "
         << duplicados;

    cout << "\nIndice de Redundancia (R): "
         << redundancia
         << "%\n";
}

//==================================================
// MAIN
//==================================================

int main() {

    set<Estudiante> A = {

        {1001,"Katherine Mishell Chuquisala Carrasco","Software",3},
        {1002,"Xavier David Fuenmayor Cumbicos","Software",3},
        {1003,"Josseph Elias Ordonez Chamik","Software",3},
        {1004,"Ximena Elizabeth Orozco Sanchez","Software",3},
        {1005,"Luis Elian Ulcuango Changoluisa","Software",3},
        {1006,"Stiven Paul Vizuete Toctaquiza","Software",3}
    };
    
    set<Estudiante> B = {

        {1004,"Ximena Elizabeth Orozco Sanchez","Software",3},
        {1005,"Luis Elian Ulcuango Changoluisa","Software",3},
        {1007,"Andrea Carolina Perez Lopez","Software",2},
        {1008,"Carlos Alberto Mena Ruiz","Software",4},
        {1009,"Valeria Sofia Andrade Flores","Software",1}
    };

    int opcion;

    do {

        mostrarTitulo(
            "SISTEMA DE GESTION DE ESTUDIANTES BASADO EN TEORIA DE CONJUNTOS");

        cout << "\n1. Ver Conjunto A";
        cout << "\n2. Ver Conjunto B";
        cout << "\n3. Agregar estudiante a Conjunto A";
        cout << "\n4. Agregar estudiante a Conjunto B";
        cout << "\n5. Mostrar Union (A U B)";
        cout << "\n6. Mostrar Interseccion (A ∩ B)";
        cout << "\n7. Mostrar Diferencia (A - B)";
        cout << "\n8. Validar Ley de Idempotencia";
        cout << "\n9. Mostrar Metricas";
        cout << "\n10. Medir Tiempo de Respuesta";
        cout << "\n0. Salir";

        cout << "\n\nSeleccione una opcion: ";
        opcion = leerOpcion();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {

        case 1:

            mostrarTitulo("CONJUNTO A");
            mostrarEstudiantes(A);
            break;

        case 2:

            mostrarTitulo("CONJUNTO B");
            mostrarEstudiantes(B);
            break;

        case 3:

            agregarEstudiante(A);
            break;

        case 4:

            agregarEstudiante(B);
            break;

        case 5: {

            auto U =
                MotorConjuntos::unir(A,B);

            mostrarTitulo("UNION (A U B)");
            mostrarEstudiantes(U);

            break;
        }

        case 6: {

            auto I =
                MotorConjuntos::interseccion(A,B);

            mostrarTitulo("INTERSECCION (A ∩ B)");
            mostrarEstudiantes(I);

            break;
        }

        case 7: {

            auto D =
                MotorConjuntos::diferencia(A,B);

            mostrarTitulo("DIFERENCIA (A - B)");
            mostrarEstudiantes(D);

            break;
        }

        case 8: {

            auto idempotencia =
                MotorConjuntos::unir(A,A);

            mostrarTitulo(
                "LEY DE IDEMPOTENCIA");

            cout << "\nCardinalidad A: "
                 << A.size();

            cout << "\nCardinalidad A U A: "
                 << idempotencia.size();

            if(idempotencia.size()
               == A.size()) {

                cout << "\n\n VALIDADO: ";
                cout << "\nA U A = A";
            }

            break;
        }

        case 9: {

            auto I =
                MotorConjuntos::interseccion(A,B);

            mostrarTitulo(
                "METRICAS DEL MODELO");

            mostrarMetricas(A,B,I);

            break;
        }
        
        case 10: {

    // UNION
    auto inicioUnion = high_resolution_clock::now();

    for(int i = 0; i < 1000000; i++)
    {
        auto U = MotorConjuntos::unir(A,B);
    }

    auto finUnion = high_resolution_clock::now();

    auto tiempoUnion =
        duration_cast<nanoseconds>(
            finUnion - inicioUnion);

    // INTERSECCION
    auto inicioInter = high_resolution_clock::now();

    for(int i = 0; i < 1000000; i++)
    {
        auto I = MotorConjuntos::interseccion(A,B);
    }

    auto finInter = high_resolution_clock::now();

    auto tiempoInter =
        duration_cast<nanoseconds>(
            finInter - inicioInter);

    // DIFERENCIA
    auto inicioDif = high_resolution_clock::now();

    for(int i = 0; i < 1000000; i++)
    {
        auto D = MotorConjuntos::diferencia(A,B);
    }

    auto finDif = high_resolution_clock::now();

    auto tiempoDif =
        duration_cast<nanoseconds>(
            finDif - inicioDif);

    mostrarTitulo("TIEMPOS DE RESPUESTA");

    cout << "\nOperacion                 Tiempo\n";
    cout << "------------------------------------------------\n";

    cout << left
         << setw(25)
         << "Union (A U B)"
         << tiempoUnion.count()
         << " ns\n";

    cout << left
         << setw(25)
         << "Interseccion (A ∩ B)"
         << tiempoInter.count()
         << " ns\n";

    cout << left
         << setw(25)
         << "Diferencia (A - B)"
         << tiempoDif.count()
         << " ns\n";

    break;
	}

        case 0:

            cout << "\nFin del programa.\n";
            break;

        default:

            cout << "\nOpcion invalida.\n";
        }

        cout << "\n\n";
        system("pause");

    } while(opcion != 0);

    return 0;
}