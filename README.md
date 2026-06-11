# Aplicación de la Teoría y Operaciones de Conjuntos en la Gestión de Base de Datos 🎓

Este proyecto es una aplicación en consola desarrollada en C++ que aplica conceptos fundamentales de la **Matemática Discreta** (específicamente la Teoría de Conjuntos) para gestionar y analizar registros de estudiantes universitarios. El sistema permite administrar dos grupos de estudiantes (Conjunto A y Conjunto B) y realizar operaciones de conjuntos en tiempo real para evaluar redundancias, encontrar estudiantes comunes y medir el rendimiento de dichas operaciones.

## 🧮 Base Matemática Discreta

El motor del sistema (`MotorConjuntos`) utiliza la estructura de datos `std::set` de C++, la cual garantiza internamente que no existan elementos duplicados y que los elementos estén ordenados. Las operaciones matemáticas implementadas son:

* **Cardinalidad (|A|):** Representa el número de estudiantes únicos dentro de un conjunto. El sistema lo calcula constantemente mediante el tamaño del conjunto.
* **Unión (A ∪ B):** Combina todos los estudiantes del Conjunto A y del Conjunto B. Si un estudiante existe en ambos, la propiedad del conjunto descarta el duplicado matemáticamente.
* **Intersección (A ∩ B):** Genera un nuevo conjunto compuesto únicamente por los estudiantes que están matriculados *tanto* en el Conjunto A *como* en el Conjunto B.
* **Diferencia (A - B):** Retorna a los estudiantes que pertenecen exclusivamente al Conjunto A, excluyendo a aquellos que también forman parte del Conjunto B.
* **Ley de Idempotencia (A ∪ A = A):** El sistema incluye una prueba explícita para demostrar este axioma, comprobando que la unión de un conjunto consigo mismo no altera su cardinalidad ni sus elementos.

## 🚀 Instrucciones de Instalación y Ejecución

### Prerrequisitos

* Un compilador de C++ que soporte el estándar C++11 o superior (ej. `g++`, `clang`, o MSVC en Windows).
* Terminal o línea de comandos.

### Pasos para compilar y ejecutar

1. **Clonar el repositorio:**
```bash
git clone https://github.com/luiiss123/Aplicaci-n-de-la-Teor-a-y-Operaciones-de-Conjuntos-en-la-Gesti-n-de-Base-de-Datos.git

```



```

2. **Compilar el código fuente:**
   ```bash
   g++ "Proyecto MD.cpp" -o gestion_estudiantes -std=c++11

```

3. **Ejecutar el programa:**
* En Windows: `gestion_estudiantes.exe`
* En Linux / macOS: `./gestion_estudiantes`



## ⚙️ Guía para Ejecutar las Pruebas Automatizadas

El proyecto incluye módulos de *testing* integrados directamente en su menú interactivo:

1. **Prueba Lógica (Validación de Idempotencia):**
* Selecciona la opción `8` en el menú principal.
* El sistema ejecutará automáticamente la operación A ∪ A y comparará las cardinalidades.
* **Resultado esperado:** El sistema debe imprimir `VALIDADO: A U A = A`.


2. **Pruebas de Estrés y Rendimiento:**
* Selecciona la opción `10` en el menú.
* El motor ejecutará un bucle de **1,000,000 de iteraciones** para cada operación matemática (Unión, Intersección, Diferencia).
* Utiliza la librería `<chrono>` para medir el tiempo total en nanosegundos (ns).
* **Propósito:** Evaluar la complejidad algorítmica y la eficiencia en memoria de las operaciones sobre `std::set`.


3. **Análisis de Datos (Métricas del Modelo):**
* Selecciona la opción `9`.
* El sistema calculará automáticamente los registros totales y detectará las colisiones (duplicados) evaluando A ∩ B.
* Mostrará el **Índice de Redundancia (R)** en formato de porcentaje.



## 👥 Contribuidores

| Nombre | Rol / Contribución |
| --- | --- |
| **Ximena Elizabeth Orozco Sanchez** | Metodología de Desarrollo |
| **Luis Elian Ulcuango Changoluisa (Lucho)** | Implementación, Pruebas y Verificación Formal |
| **Josseph Elias Ordonez Chamik** | Implementación, Pruebas y Verificación Formal |
| **Stiven Paul Vizuete Toctaquiza** | Resultados y Análisis |
| **Xavier David Fuenmayor Cumbicos** | Resultados y Análisis |
| **Katherine Mishell Chuquisala Carrasco** | Conclusiones y Trabajo Futuro |
