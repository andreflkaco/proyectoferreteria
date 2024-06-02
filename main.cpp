	#include <iostream>
	#include <string>
	#include <mysql.h>
	#include <sstream> 
	#include <conio.h> 
	#include <cstdio>  
	#include <iomanip>
	
	using namespace std;
	 // Declaración de la función iniciarSesion
	// Función para iniciar sesión
	bool iniciarSesion(MYSQL* obj) {
	    cout << "==============================================" << endl;
	    cout << "           INICIO DE SESION" << endl;
	    cout << "==============================================" << endl;
	
	    string usuario = "", contrasena = "";
	    string usuarioCorrecto = "Administrador1";
	    string contrasenaCorrecta = "ing123";
	    int intentos = 3;
	
	    // Bucle para permitir múltiples intentos de inicio de sesión
	    while (intentos > 0) {
	        cout << "Usuario: ";
	        cin >> usuario;
	
	        // Ocultar la entrada de la contraseña
	        cout << "Contraseña: ";
	        char ch;
	        while ((ch = _getch()) != '\r') { // Leer caracteres hasta que se presione Enter
	            if (ch == '\b') { // Si se presiona la tecla retroceso
	                if (contrasena.length() > 0) {
	                    cout << "\b \b"; // Borra el último carácter de la pantalla
	                    contrasena.erase(contrasena.length() - 1); // Borra el último carácter del string
	                }
	            } else {
	                cout << 	""; // Muestra '' en lugar del carácter real de la contraseña
	                contrasena += ch; // Agrega el carácter al string de la contraseña
	            }
	        }
	
	        // Verificar las credenciales de inicio de sesión
	        if (usuario == usuarioCorrecto && contrasena == contrasenaCorrecta) {
	            cout << "\n\n¡Inicio de sesión exitoso!" << endl;
	            cout << "¡Bienvenido, Administrador1!\n" << endl;
	            return true; // Credenciales correctas
	        } else {
	            cout << "\n\nCredenciales incorrectas. Por favor, intentelo de nuevo.\n" << endl;
	            intentos--;
	            cout << "Intentos restantes: " << intentos << endl;
	        }
	    }
	
	    cout << "\n¡Has excedido el numero de intentos permitidos! Saliendo del programa.\n" << endl;
	    return false; // Excedió el número de intentos
	}
	// Enumeración para los diferentes perfiles de usuario
	enum Perfil {
	    Consulta,
	    Ventas,
	    Administrador
	};
	// Función para convertir un entero a una cadena
	string intToString(int num) {
	    stringstream ss;
	    ss << num;
	    return ss.str();
	}
	
	
	// Función para convertir una cadena a Perfil
	Perfil stringToPerfil(const string& perfilStr) {
	    if (perfilStr == "Consulta") {
	        return Consulta;
	    } else if (perfilStr == "Ventas") {
	        return Ventas;
	    } else if (perfilStr == "Administrador") {
	        return Administrador;
	    } else {
	        return Consulta; // Perfil por defecto
	    }
	}
	
	// Función para convertir un Perfil a cadena
	string perfilToString(Perfil perfil) {
	    switch (perfil) {
	        case Consulta:
	            return "Consulta";
	        case Ventas:
	            return "Ventas";
	        case Administrador:
	            return "Administrador";
	        default:
	            return "Consulta"; // Perfil por defecto
	    }
	}
	
	// Función para ejecutar una consulta SQL y manejar errores
	void executeQuery(MYSQL* obj, const string& query, const string& successMessage) {
	    if (mysql_query(obj, query.c_str())) {
	        cout << "Error: " << mysql_error(obj) << endl;
	    } else {
	        // Manejo de conjunto de resultados
	        MYSQL_RES *result = mysql_store_result(obj);
	        if (result) {
	            mysql_free_result(result);
	        }
	        cout << successMessage << endl;
	    }
	}
	
	// Función para crear las tablas necesarias
	void createTables(MYSQL* obj) {
	    string createUsuariosTable = "CREATE TABLE IF NOT EXISTS usuarios ("
	                                 "id INT AUTO_INCREMENT PRIMARY KEY, "
	                                 "nombre_usuario VARCHAR(100), "
	                                 "nombre_completo VARCHAR(100), "
	                                 "correo_electronico VARCHAR(100), "
	                                 "numero_telefono VARCHAR(20), "
	                                 "contrasena VARCHAR(100), " // Nueva columna para la contraseña
	                                 "perfil ENUM('Consulta', 'Ventas', 'Administrador'), "
	                                 "fecha_ingreso DATE)";
	    executeQuery(obj, createUsuariosTable, "Tabla 'usuarios' creada exitosamente");
	
	string createArticulosTable =  "CREATE TABLE IF NOT EXISTS articulos ("
	                                  "id INT AUTO_INCREMENT PRIMARY KEY, "
	                                  "codigo_producto VARCHAR(50) UNIQUE, "
	                                  "nombre_articulo VARCHAR(100), "
	                                  "unidad_medida VARCHAR(50), "
	                                  "cantidad INT, "
	                                  "precio DECIMAL(10,2), "
	                                  "fecha_ingreso DATE)";
	executeQuery(obj, createArticulosTable, "Tabla 'articulos' creada exitosamente");
	
	    string createPersonalTable ="CREATE TABLE IF NOT EXISTS personal ("
	                             "id INT AUTO_INCREMENT PRIMARY KEY, "
	                             "codigo_empleado VARCHAR(20), "
	                             "nombre VARCHAR(100), "
	                             "genero ENUM('Masculino', 'Femenino', 'Otro'), "
	                             "edad INT, "
	                             "puesto VARCHAR(100), " // Campo para almacenar el nombre del puesto
	                             "salario DECIMAL(10, 2), "
	                             "fecha_ingreso DATE)";
	    executeQuery(obj, createPersonalTable, "Tabla 'personal' creada exitosamente");
	
	    string createPuestoTable =  "CREATE TABLE IF NOT EXISTS puesto ("
	                               "id INT AUTO_INCREMENT PRIMARY KEY, "
	                               "puesto VARCHAR(100), "
	                               "fecha_ingreso DATE)"; // Agregamos el campo 'fecha_ingreso'
	    executeQuery(obj, createPuestoTable, "Tabla 'puesto' creada exitosamente");
	    
	    string createClientesTable = "CREATE TABLE IF NOT EXISTS clientes ("
	                                 "id INT AUTO_INCREMENT PRIMARY KEY, "
	                                 "codigo_cliente VARCHAR(50) UNIQUE, "
	                                 "nombre_cliente VARCHAR(100), "
	                                 "contacto VARCHAR(100), "
	                                 "correo_electronico VARCHAR(100), "
	                                 "articulo_comprado VARCHAR(100), "
	                                 "cantidad_comprada INT, "
	                                 "precio DECIMAL(10,2), "
	                                 "total DECIMAL(10,2), "
	                                 "fecha_ingreso DATE)";
	    executeQuery(obj, createClientesTable, "Tabla 'clientes' creada exitosamente");
	
	    string createProveedoresTable =   "CREATE TABLE IF NOT EXISTS proveedores ("
	                                "id INT AUTO_INCREMENT PRIMARY KEY, "
	                                "nombre VARCHAR(100), "
	                                "contacto VARCHAR(100), "
	                                "codigo_proveedor VARCHAR(20), "
	                                "codigo_producto VARCHAR(50) UNIQUE, "
	                                "nombre_articulo VARCHAR(100), "
	                                "unidad_medida VARCHAR(50), "
	                                "cantidad INT, "
	                                "precio DECIMAL(10,2), "
	                                "fecha_ingreso DATE)";
	    executeQuery(obj, createProveedoresTable, "Tabla 'proveedores' creada exitosamente");
	
	    string createComprasTable = "CREATE TABLE IF NOT EXISTS compras ("
	                            "id INT AUTO_INCREMENT PRIMARY KEY, "
	                            "nombre_proveedor VARCHAR(100), "
	                            "codigo_producto VARCHAR(50), "
	                            "producto VARCHAR(100), "
	                            "cantidad INT, "
	                            "unidad_medida VARCHAR(50), "
	                            "precio_unitario DECIMAL(10,2), "
	                            "total DECIMAL(10,2), "
	                            "fecha_ingreso DATE)";
	    executeQuery(obj, createComprasTable, "Tabla 'compras' creada exitosamente");
	
	     string createVentasTable = "CREATE TABLE IF NOT EXISTS ventas ("
	                               "id INT AUTO_INCREMENT PRIMARY KEY, "
	                               "nombre_articulo VARCHAR(100), "
	                               "nombre_cliente VARCHAR(100), "
	                               "cantidad INT, "
	                               "precio DECIMAL(10,2), "
	                               "total DECIMAL(10,2), "
	                               "fecha_ingreso DATE)";
	    executeQuery(obj, createVentasTable, "Tabla 'ventas' creada exitosamente");
	}
	
	// Función para registrar un nuevo usuario
	void registrarUsuario(MYSQL* obj) {
	    string nombre_usuario, nombre_completo, correo_electronico, numero_telefono, contrasena, perfilStr;
	    int opcion;
	
	    cout << "Ingrese el nombre de usuario: ";
	    cin.ignore();
	    getline(cin, nombre_usuario);
	    cout << "Ingrese el nombre completo: ";
	    getline(cin, nombre_completo);
	    cout << "Ingrese el correo electronico: ";
	    getline(cin, correo_electronico);
	    cout << "Ingrese el numero de telefono: ";
	    getline(cin, numero_telefono);
	    cout << "Ingrese la contraseña: ";
	    getline(cin, contrasena); // Solicitar la contraseña
	
	    cout << "Seleccione el perfil del usuario:" << endl;
	    cout << "1. Consulta" << endl;
	    cout << "2. Ventas" << endl;
	    cout << "3. Administrador" << endl;
	    cout << "Seleccione una opcion: ";
	    cin >> opcion;
	
	    switch (opcion) {
	        case 1:
	            perfilStr = "Consulta";
	            break;
	        case 2:
	            perfilStr = "Ventas";
	            break;
	        case 3:
	            perfilStr = "Administrador";
	            break;
	        default:
	            cout << "Opción no valida. Se asignará el perfil por defecto (Consulta)." << endl;
	            perfilStr = "Consulta";
	            break;
	    }
	
	    Perfil perfil = stringToPerfil(perfilStr);
	
	    // Actualizar la consulta para incluir la contraseña
	    string query = "INSERT INTO usuarios (nombre_usuario, nombre_completo, correo_electronico, numero_telefono, contrasena, perfil, fecha_ingreso) VALUES ('" 
	                    + nombre_usuario + "', '" + nombre_completo + "', '" + correo_electronico + "', '" + numero_telefono + "', '" + contrasena + "', '"  + perfilToString(perfil) + "', CURDATE())";
	    executeQuery(obj, query, "Usuario registrado exitosamente");
	}
	// Función para registrar un nuevo puesto
	void registrarPuesto(MYSQL* obj) {
	    string nombrePuesto;
	
	    cout << "Ingrese el nombre del puesto: ";
	    cin.ignore();
	    getline(cin, nombrePuesto);
	
	    string query = "INSERT INTO puesto (puesto, fecha_ingreso) VALUES ('" + nombrePuesto + "', CURDATE())";
	    executeQuery(obj, query, "Puesto registrado exitosamente");
	}
	void registrarPersonal(MYSQL* obj) {
	    string nombre, codigoEmpleado, genero;
	    int edad, puesto_id;
	    double salario;
	
	    cout << "Ingrese el nombre del personal: ";
	    cin.ignore();
	    getline(cin, nombre);
	    cout << "Ingrese el codigo del empleado: ";
	    getline(cin, codigoEmpleado);
	
	    cout << "Ingrese la edad: ";
	    cin >> edad;
	
	    cout << "Seleccione el genero:" << endl;
	    cout << "1. Masculino" << endl;
	    cout << "2. Femenino" << endl;
	    cout << "3. Otro" << endl;
	    cout << "Seleccione una opción: ";
	    int opcion;
	    cin >> opcion;
	
	    switch (opcion) {
	        case 1:
	            genero = "Masculino";
	            break;
	        case 2:
	            genero = "Femenino";
	            break;
	        case 3:
	            genero = "Otro";
	            break;
	        default:
	            cout << "Opcion no valida. Se asignara 'Otro' por defecto." << endl;
	            genero = "Otro";
	            break;
	    }
	
	    cout << "Ingrese el ID del puesto: ";
	    cin >> puesto_id;
	    cout << "Ingrese el salario: ";
	    cin >> salario;
	
	    // Convertir el entero de la edad y salario a string usando stringstream
	    stringstream ss_edad, ss_salario;
	    ss_edad << edad;
	    ss_salario << salario;
	    string edadStr, salarioStr;
	    ss_edad >> edadStr;
	    ss_salario >> salarioStr;
	
	    // Construir la consulta para obtener el nombre del puesto asociado al puesto_id
	    stringstream queryPuestoStream;
	    queryPuestoStream << "SELECT puesto FROM puesto WHERE id = " << puesto_id;
	    string queryPuesto = queryPuestoStream.str();
	
	    // Ejecutar la consulta
	    if (mysql_query(obj, queryPuesto.c_str())) {
	        cout << "Error al ejecutar la consulta: " << mysql_error(obj) << endl;
	        return;
	    }
	
	    // Obtener el resultado de la consulta
	    MYSQL_RES* resultPuesto = mysql_store_result(obj);
	    if (!resultPuesto) {
	        cout << "Error al obtener el resultado de la consulta: " << mysql_error(obj) << endl;
	        return;
	    }
	
	    MYSQL_ROW rowPuesto = mysql_fetch_row(resultPuesto);
	    if (rowPuesto) {
	        // Si se encontró el nombre del puesto, usarlo en la consulta de inserción
	        string nombrePuesto = rowPuesto[0];
	
	        // Insertar registro en la tabla personal usando el nombre del puesto en lugar de la ID
	        stringstream queryStream;
	        queryStream << "INSERT INTO personal (nombre, codigo_empleado, edad, genero, puesto, salario, fecha_ingreso) VALUES ('" 
	                    << nombre << "', '" << codigoEmpleado << "', '" << edadStr << "', '" << genero << "', '" << nombrePuesto << "', '" << salarioStr << "', CURDATE())";
	        string query = queryStream.str();
	
	        if (mysql_query(obj, query.c_str())) {
	            cout << "Error al ejecutar la consulta de insercion: " << mysql_error(obj) << endl;
	        } else {
	            cout << "Personal registrado exitosamente" << endl;
	        }
	    } else {
	        cout << "No se encontro un puesto con el ID proporcionado." << endl;
	    }
	
	    // Liberar resultado
	    mysql_free_result(resultPuesto);
	}
	
	// Función para registrar un nuevo artículo
	// Función para registrar un nuevo artículo
	void registrarArticulo(MYSQL* obj) {
	  std::string codigo_producto, nombre_articulo, unidad_medida;
	    int cantidad;
	    double precio;
	
	    std::cout << "Ingrese el codigo del articulo: ";
	    std::cin.ignore();
	    std::getline(std::cin, codigo_producto);
	    std::cout << "Ingrese el nombre del articulo: ";
	    std::getline(std::cin, nombre_articulo);
	    std::cout << "Ingrese la unidad de medida: ";
	    std::getline(std::cin, unidad_medida);
	    std::cout << "Ingrese la cantidad: ";
	    std::cin >> cantidad;
	    std::cout << "Ingrese el precio: ";
	    std::cin >> precio;
	
	    // Construir la consulta SQL utilizando el operador de inserción <<
	    std::ostringstream queryStream;
	    queryStream << "INSERT INTO articulos (codigo_producto, nombre_articulo, unidad_medida, cantidad, precio, fecha_ingreso) "
	                << "VALUES ('" << codigo_producto << "', '" << nombre_articulo << "', '" << unidad_medida << "', "
	                << cantidad << ", " << precio << ", CURDATE())";
	    std::string query = queryStream.str();
	
	    // Ejecutar la consulta y mostrar mensajes de éxito o error
	    executeQuery(obj, query, "No se pudo registrar el articulo.");
	
	    // Verificar si la consulta fue exitosa
	    if (mysql_affected_rows(obj) > 0) {
	        std::cout << "Artículo registrado exitosamente." << std::endl;
	    }
	}
	
	// Función para registrar un nuevo cliente
	void registrarCliente(MYSQL* obj) {
	  string codigoCliente, nombre_cliente, contacto, correoElectronico;
	    
	    cout << "Ingrese el codigo del cliente: ";
	    cin.ignore();
	    getline(cin, codigoCliente);
	    
	    cout << "Ingrese el nombre del cliente: ";
	    getline(cin, nombre_cliente);
	    
	    cout << "Ingrese el contacto del cliente: ";
	    getline(cin, contacto);
	
	    cout << "Ingrese el correo electronico del cliente: ";
	    getline(cin, correoElectronico);
	
	    // Agrega la fecha actual a la consulta de inserción
	    string query = "INSERT INTO clientes (codigo_cliente, nombre_cliente, contacto, correo_electronico, fecha_ingreso) VALUES ('" 
	                   + codigoCliente + "', '" + nombre_cliente + "', '" + contacto + "', '" + correoElectronico + "', CURDATE())";
	    
	    executeQuery(obj, query, "Cliente registrado exitosamente");
	}
	void registrarProveedor(MYSQL* obj) {
	    string nombre, contacto, codigo_proveedor, codigo_producto, nombre_articulo, unidad_medida;
	    int cantidad;
	    double precio;
	
	    cout << "Ingrese el nombre del proveedor: ";
	    cin.ignore();
	    getline(cin, nombre);
	    cout << "Ingrese el contacto del proveedor: ";
	    getline(cin, contacto);
	    cout << "Ingrese el codigo del proveedor: ";
	    getline(cin, codigo_proveedor);
	    cout << "Ingrese el codigo del producto: ";
	    getline(cin, codigo_producto);
	    cout << "Ingrese el nombre del articulo: ";
	    getline(cin, nombre_articulo);
	    cout << "Ingrese la unidad de medida: ";
	    getline(cin, unidad_medida);
	    cout << "Ingrese la cantidad: ";
	    cin >> cantidad;
	    cout << "Ingrese el precio: ";
	    cin >> precio;
	
	 // Construir la consulta SQL utilizando el operador de inserción <<
	std::ostringstream queryStream;
	queryStream << "INSERT INTO proveedores (nombre, contacto, codigo_proveedor, codigo_producto, nombre_articulo, unidad_medida, cantidad, precio, fecha_ingreso) "
	            << "VALUES ('" << nombre << "', '" << contacto << "', '" << codigo_proveedor << "', '"
	            << codigo_producto << "', '" << nombre_articulo << "', '" << unidad_medida << "', "
	            << cantidad << ", " << precio << ", CURDATE())";
	std::string query = queryStream.str();
	
	// Ejecutar la consulta y mostrar mensaje de éxito o error
	executeQuery(obj, query, "Proveedor registrado exitosamente.");
	}
	
	
	void registrarCompra(MYSQL* obj) {
	 int proveedorId;
	    int cantidadComprada;
	    char query[1024];
	
	    cout << "Ingrese el ID del proveedor: ";
	    cin >> proveedorId;
	    cin.ignore();
	
	    // Obtener el nombre del proveedor y otros datos usando el ID
	    sprintf(query, "SELECT nombre, codigo_producto, nombre_articulo, unidad_medida, cantidad, precio FROM proveedores WHERE id = %d", proveedorId);
	    if (mysql_query(obj, query)) {
	        cout << "Error al ejecutar la consulta: " << mysql_error(obj) << endl;
	        return;
	    }
	
	    MYSQL_RES* result = mysql_store_result(obj);
	    if (result == NULL) {
	        cout << "Error al obtener el resultado: " << mysql_error(obj) << endl;
	        return;
	    }
	
	    MYSQL_ROW row = mysql_fetch_row(result);
	    if (row == NULL) {
	        cout << "No se encontro el proveedor con el ID proporcionado." << endl;
	        mysql_free_result(result);
	        return;
	    }
	
	    // Mostrar la información del proveedor
	    string nombreProveedor = row[0];
	    string codigoProducto = row[1];
	    string productoDistribuido = row[2];
	    string unidadMedida = row[3];
	    int cantidadDisponible = atoi(row[4]);
	    double precioUnitario = atof(row[5]);
	
	    cout << "Nombre del proveedor: " << nombreProveedor << endl;
	    cout << "Código del producto: " << codigoProducto << endl;
	    cout << "Producto distribuido: " << productoDistribuido << endl;
	    cout << "Unidad de medida: " << unidadMedida << endl;
	    cout << "Cantidad disponible: " << cantidadDisponible << endl;
	    cout << "Precio unitario: " << precioUnitario << endl;
	
	    // Pedir la cantidad a comprar
	    cout << "Ingrese la cantidad a comprar: ";
	    cin >> cantidadComprada;
	
	    // Calcular el total
	    double total = cantidadComprada * precioUnitario;
	
	    // Registrar la compra
	    sprintf(query, "INSERT INTO compras (nombre_proveedor, codigo_producto, producto, cantidad, unidad_medida, precio_unitario, total, fecha_ingreso) "
	                   "VALUES ('%s', '%s', '%s', %d, '%s', %f, %f, CURDATE())",
	            nombreProveedor.c_str(), codigoProducto.c_str(), productoDistribuido.c_str(), cantidadComprada, unidadMedida.c_str(), precioUnitario, total);
	    if (mysql_query(obj, query)) {
	        cout << "Error al registrar la compra: " << mysql_error(obj) << endl;
	    } else {
	        cout << "Compra registrada exitosamente." << endl;
	
	        // Actualizar la cantidad del proveedor
	        int nuevaCantidadProveedor = cantidadDisponible - cantidadComprada;
	        sprintf(query, "UPDATE proveedores SET cantidad = %d WHERE id = %d", nuevaCantidadProveedor, proveedorId);
	        if (mysql_query(obj, query)) {
	            cout << "Error al actualizar la cantidad del proveedor: " << mysql_error(obj) << endl;
	        } else {
	            cout << "Cantidad del proveedor actualizada exitosamente." << endl;
	
	            // Verificar si el artículo ya existe en la tabla artículos
	            sprintf(query, "SELECT cantidad FROM articulos WHERE codigo_producto = '%s'", codigoProducto.c_str());
	            if (mysql_query(obj, query)) {
	                cout << "Error al verificar el artículo en la tabla articulos: " << mysql_error(obj) << endl;
	            } else {
	                MYSQL_RES* articuloResult = mysql_store_result(obj);
	                MYSQL_ROW articuloRow = mysql_fetch_row(articuloResult);
	                if (articuloRow != NULL) {
	                    // El artículo ya existe, actualizar la cantidad
	                    int cantidadExistente = atoi(articuloRow[0]);
	                    int nuevaCantidadArticulo = cantidadExistente + cantidadComprada;
	                    sprintf(query, "UPDATE articulos SET cantidad = %d WHERE codigo_producto = '%s'", nuevaCantidadArticulo, codigoProducto.c_str());
	                    if (mysql_query(obj, query)) {
	                        cout << "Error al actualizar la cantidad del artciculo: " << mysql_error(obj) << endl;
	                    } else {
	                        cout << "Cantidad del articulo actualizada exitosamente." << endl;
	                    }
	                } else {
	                    // El artículo no existe, insertarlo
	                    sprintf(query, "INSERT INTO articulos (codigo_producto, nombre_articulo, unidad_medida, cantidad, precio, fecha_ingreso) "
	                                   "VALUES ('%s', '%s', '%s', %d, %f, CURDATE())",
	                            codigoProducto.c_str(), productoDistribuido.c_str(), unidadMedida.c_str(), cantidadComprada, precioUnitario);
	                    if (mysql_query(obj, query)) {
	                        cout << "Error al insertar el articulo en la tabla articulos: " << mysql_error(obj) << endl;
	                    } else {
	                        cout << "Articulo insertado en la tabla articulos exitosamente." << endl;
	                    }
	                }
	                mysql_free_result(articuloResult);
	            }
	        }
	    }
	
	    mysql_free_result(result);
	}

void registrarVenta(MYSQL* obj) {
      int articuloId, clienteId, cantidad;
    std::string query;

    std::cout << "Ingrese el ID del articulo: ";
    std::cin >> articuloId;

    // Obtener información del artículo
    std::stringstream queryStream;
    queryStream << "SELECT nombre_articulo, codigo_producto, unidad_medida, cantidad, precio FROM articulos WHERE id = " << articuloId;
    query = queryStream.str();
    if (mysql_query(obj, query.c_str())) {
        std::cout << "Error: No se pudo obtener informacion del articulo." << std::endl;
        return;
    }
    MYSQL_RES* resultArticulo = mysql_store_result(obj);
    MYSQL_ROW rowArticulo = mysql_fetch_row(resultArticulo);
    if (!rowArticulo) {
        std::cout << "Error: No se pudo obtener informacion del articulo." << std::endl;
        mysql_free_result(resultArticulo);
        return;
    }
    std::string nombreArticulo = rowArticulo[0] ? rowArticulo[0] : "";
    std::string codigoProducto = rowArticulo[1] ? rowArticulo[1] : "";
    std::string unidadMedida = rowArticulo[2] ? rowArticulo[2] : "";
    int cantidadDisponible = rowArticulo[3] ? atoi(rowArticulo[3]) : 0;
    double precioUnitario = rowArticulo[4] ? atof(rowArticulo[4]) : 0.0;
    mysql_free_result(resultArticulo);

    // Mostrar información del artículo
    std::cout << "Datos del articulo:" << std::endl;
    if (!nombreArticulo.empty()) std::cout << "Nombre: " << nombreArticulo << std::endl;
    if (!codigoProducto.empty()) std::cout << "Código de producto: " << codigoProducto << std::endl;
    if (!unidadMedida.empty()) std::cout << "Unidad de medida: " << unidadMedida << std::endl;
    if (cantidadDisponible != 0) std::cout << "Cantidad disponible: " << cantidadDisponible << std::endl;
    if (precioUnitario != 0.0) std::cout << "Precio unitario: " << precioUnitario << std::endl;

    std::cout << "Ingrese el ID del cliente: ";
    std::cin >> clienteId;

    // Obtener información del cliente
    queryStream.str("");
    queryStream << "SELECT codigo_cliente, nombre_cliente, contacto, correo_electronico, articulo_comprado, cantidad_comprada, precio, total, fecha_ingreso FROM clientes WHERE id = " << clienteId;
    query = queryStream.str();
    if (mysql_query(obj, query.c_str())) {
        std::cout << "Error: No se pudo obtener informacion del cliente." << std::endl;
        return;
    }
    MYSQL_RES* resultCliente = mysql_store_result(obj);
    MYSQL_ROW rowCliente = mysql_fetch_row(resultCliente);
    if (!rowCliente) {
        std::cout << "Error: No se pudo obtener informacion del cliente." << std::endl;
        mysql_free_result(resultCliente);
        return;
    }

    std::string codigoCliente = rowCliente[0] ? rowCliente[0] : "";
    std::string nombreCliente = rowCliente[1] ? rowCliente[1] : "";
    std::string contactoCliente = rowCliente[2] ? rowCliente[2] : "";
    std::string correoCliente = rowCliente[3] ? rowCliente[3] : "";
    std::string articuloComprado = rowCliente[4] ? rowCliente[4] : "";
    int cantidadComprada = rowCliente[5] ? atoi(rowCliente[5]) : 0;
    double precio = rowCliente[6] ? atof(rowCliente[6]) : 0.0;
    double total = rowCliente[7] ? atof(rowCliente[7]) : 0.0;
    std::string fechaIngreso = rowCliente[8] ? rowCliente[8] : "";
    mysql_free_result(resultCliente);

    // Mostrar información del cliente
    std::cout << "Datos del cliente:" << std::endl;
    if (!codigoCliente.empty()) std::cout << "Código: " << codigoCliente << std::endl;
    if (!nombreCliente.empty()) std::cout << "Nombre: " << nombreCliente << std::endl;
    if (!contactoCliente.empty()) std::cout << "Contacto: " << contactoCliente << std::endl;
    if (!correoCliente.empty()) std::cout << "Correo electronico: " << correoCliente << std::endl;
    if (!articuloComprado.empty()) std::cout << "Articulo comprado: " << articuloComprado << std::endl;
    if (cantidadComprada != 0) std::cout << "Cantidad comprada: " << cantidadComprada << std::endl;
    if (precio != 0.0) std::cout << "Precio: " << precio << std::endl;
    if (total != 0.0) std::cout << "Total: " << total << std::endl;
    if (!fechaIngreso.empty()) std::cout << "Fecha de ingreso: " << fechaIngreso << std::endl;

    // Ingresar la cantidad a vender
    std::cout << "Ingrese la cantidad a vender: ";
    std::cin >> cantidad;

    // Verificar si hay suficiente cantidad de artículo
    if (cantidad > cantidadDisponible) {
        std::cout << "Error: No hay suficiente cantidad del articulo para realizar la venta." << std::endl;
        return;
    }

    // Calcular el total de la venta
    double totalVenta = precioUnitario * cantidad;

    // Registrar la venta
    queryStream.str("");
    queryStream << "INSERT INTO ventas (nombre_articulo, nombre_cliente, cantidad, precio, total, fecha_ingreso) VALUES ('"
                << nombreArticulo << "', '" << nombreCliente << "', " << cantidad << ", " << precioUnitario << ", " << totalVenta << ", CURDATE())";
    query = queryStream.str();
    if (mysql_query(obj, query.c_str())) {
        std::cout << "Error: No se pudo registrar la venta." << std::endl;
        return;
    }
    std::cout << "Venta registrada exitosamente." << std::endl;

    // Actualizar la cantidad de artículo disponible
    int nuevaCantidad = cantidadDisponible - cantidad;
    queryStream.str("");
    queryStream << "UPDATE articulos SET cantidad = " << nuevaCantidad << " WHERE id = " << articuloId;
    query = queryStream.str();
    if (mysql_query(obj, query.c_str())) {
        std::cout << "Error: No se pudo actualizar la cantidad de artículo disponible." << std::endl;
        return;
    }
       std::cout << "Cantidad de articulo actualizada exitosamente." << std::endl;
       // Actualizar la información del cliente
queryStream.str("");
queryStream << "UPDATE clientes SET articulo_comprado = '" << nombreArticulo << "', cantidad_comprada = " << cantidad
            << ", precio = " << precioUnitario << ", total = " << totalVenta << ", fecha_ingreso = CURDATE() WHERE id = " << clienteId;
query = queryStream.str();
if (mysql_query(obj, query.c_str())) {
    std::cout << "Error: No se pudo actualizar la informacion del cliente." << std::endl;
    return;
}
std::cout << "Informacion del cliente actualizada exitosamente." << std::endl;
}
void mostrarPlanillaLaboral(MYSQL* obj) {
     string mes, ano;
    cout << "Ingrese el mes (MM): ";
    cin >> mes;
    cout << "Ingrese el año (YYYY): ";
    cin >> ano;

    // Consulta SQL para obtener el personal filtrado por mes y año
    string query = "SELECT * FROM personal WHERE MONTH(fecha_ingreso) = '" + mes + "' AND YEAR(fecha_ingreso) = '" + ano + "'";

    // Ejecutar la consulta
    if (mysql_query(obj, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(obj);

        if (result) {
            // Encabezado de la tabla
            cout << left << setw(5) << "ID" << setw(8) << "Codigo" << setw(15) << "Nombre" << setw(10) << "Genero" << setw(5) << "Edad"
                 << setw(20) << "Puesto" << setw(10) << "Salario" << setw(15) << "Fecha Ingreso" << endl;

            // Iterar sobre los resultados y mostrar cada fila
            while (MYSQL_ROW row = mysql_fetch_row(result)) {
                cout << left << setw(5) << row[0] << setw(8) << row[1] << setw(15) << row[2] << setw(10) << row[3] << setw(5) << row[4]
                     << setw(20) << row[5] << setw(10) << row[6] << setw(15) << row[7] << endl;
            }

            // Liberar el resultado
            mysql_free_result(result);
        } else {
            cout << "No se encontró informacion para el mes y año proporcionados." << endl;
        }
    } else {
        cout << "Error al ejecutar la consulta." << endl;
    }
}
void mostrarComprasVentas(MYSQL* obj) {
    int opcion;
    cout << "Seleccione una opción:" << endl;
    cout << "1. Buscar por ID de transaccion" << endl;
    cout << "2. Buscar por rango de fechas" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        int idTransaccion;
        cout << "Ingrese el ID de transaccion: ";
        cin >> idTransaccion;

        stringstream ss;
        ss << idTransaccion;
        string strIDTransaccion = ss.str();

        string queryCompras = "SELECT * FROM compras WHERE id = " + strIDTransaccion;
        if (mysql_query(obj, queryCompras.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Compras:" << endl;
                cout << setw(5) << "ID" << setw(20) << "Nombre Proveedor" << setw(15) << "CódigoProducto" << setw(15) << "Producto" << setw(10) << "Cantidad" << setw(15) << "Unidad Medida" << setw(15) << "Precio Unitario" << setw(10) << "Total" << setw(20) << "Fecha Ingreso" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    for (int i = 0; i < mysql_num_fields(result); i++) {
                        cout << setw(15) << row[i];
                    }
                    cout << endl;
                }
                mysql_free_result(result);
            }
        }

        string queryVentas = "SELECT * FROM ventas WHERE id = " + strIDTransaccion;
        if (mysql_query(obj, queryVentas.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Ventas:" << endl;
                cout << setw(5) << "ID" << setw(20) << "Nombre Artículo" << setw(15) << "Nombre Cliente" << setw(10) << "Cantidad" << setw(10) << "Precio" << setw(10) << "Total" << setw(20) << "Fecha Ingreso" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    for (int i = 0; i < mysql_num_fields(result); i++) {
                        cout << setw(15) << row[i];
                    }
                    cout << endl;
                }
                mysql_free_result(result);
            }
        }
    } else if (opcion == 2) {
        string fechaInicio, fechaFin;
        cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
        cin >> fechaInicio;
        cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
        cin >> fechaFin;

        string queryCompras = "SELECT * FROM compras WHERE fecha_ingreso BETWEEN '" + fechaInicio + "' AND '" + fechaFin + "'";
        if (mysql_query(obj, queryCompras.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Compras:" << endl;
                cout << setw(5) << "ID" << setw(20) << "Nombre Proveedor" << setw(15) << "Código Producto" << setw(15) << "Producto" << setw(10) << "Cantidad" << setw(15) << "Unidad Medida" << setw(15) << "Precio Unitario" << setw(10) << "Total" << setw(20) << "Fecha Ingreso" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    for (int i = 0; i < mysql_num_fields(result); i++) {
                        cout << setw(15) << row[i];
                    }
                    cout << endl;
                }
                 mysql_free_result(result);
            }
        }

        string queryVentas = "SELECT * FROM ventas WHERE fecha_ingreso BETWEEN '" + fechaInicio + "' AND '" + fechaFin + "'";
        if (mysql_query(obj, queryVentas.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Ventas:" << endl;
                cout << setw(5) << "ID" << setw(20) << "Nombre Artículo" << setw(15) << "Nombre Cliente" << setw(10) << "Cantidad" << setw(10) << "Precio" << setw(10) << "Total" << setw(20) << "Fecha Ingreso" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    for (int i = 0; i < mysql_num_fields(result); i++) {
                        cout << setw(15) << row[i];
                    }
                    cout << endl;
                }
                mysql_free_result(result);
            }
        }
    } else {
        cout << "Opcion no válida." << endl;
    }
}


// Función para mostrar el kardex
void mostrarKardex(MYSQL* obj) {
    int opcion;
    cout << "Seleccione una opcion:" << endl;
    cout << "1. Buscar por ID de articulo" << endl;
    cout << "2. Buscar por rango de fechas" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        // Búsqueda por ID de artículo
        string idArticulo;
        cout << "Ingrese el ID del articulo: ";
        cin >> idArticulo;

        string queryCompras = "SELECT c.id, c.codigo_producto, c.producto, c.cantidad, c.unidad_medida, c.precio_unitario, c.total, c.fecha_ingreso, c.nombre_proveedor FROM compras c WHERE c.id = '" + idArticulo + "'";
        if (mysql_query(obj, queryCompras.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Compras en kardex:" << endl;
                cout << "ID | Código Producto | Producto | Cantidad | Unidad Medida | Precio Unitario | Total | Proveedor | Fecha Ingreso" << endl;
                cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    cout << setw(5) << row[0] << " | " << setw(15) << row[1] << " | " << setw(15) << row[2] << " | " << setw(8) << row[3] << " | " << setw(13) << row[4] << " | " << setw(15) << row[5] << " | " << setw(10) << row[6] << " | " << setw(13) << row[8] << " | " << setw(5) << row[7] << endl;
                }
                mysql_free_result(result);
            }
        }

        string queryVentas = "SELECT v.id, v.nombre_articulo, v.nombre_cliente, v.cantidad, v.precio, v.total, v.fecha_ingreso FROM ventas v WHERE v.id = '" + idArticulo + "'";
        if (mysql_query(obj, queryVentas.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Ventas en kardex:" << endl;
                cout << "ID | Articulo | Cliente | Cantidad | Precio | Total | Fecha Ingreso" << endl;
                cout << "------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    cout << setw(5) << row[0] << " | " << setw(15) << row[1] << " | " << setw(10) << row[2] << " | " << setw(8) << row[3] << " | " << setw(8) << row[4] << " | " << setw(8) << row[5] << " | " << setw(13) << row[6] << endl;
                }
                mysql_free_result(result);
            }
        }
    } else if (opcion == 2) {
        // Búsqueda por rango de fechas
        string fechaInicio, fechaFin;
        cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
        cin >> fechaInicio;
        cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
        cin >> fechaFin;

        string queryCompras = "SELECT c.id, c.codigo_producto, c.producto, c.cantidad, c.unidad_medida, c.precio_unitario, c.total, c.fecha_ingreso, c.nombre_proveedor FROM compras c WHERE c.fecha_ingreso BETWEEN '" + fechaInicio + "' AND '" + fechaFin + "'";
        if (mysql_query(obj, queryCompras.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Compras en kardex:" << endl;
                cout << "ID | Codigo Producto | Producto | Cantidad | Unidad Medida | Precio Unitario | Total | Proveedor | Fecha Ingreso" << endl;
                cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    cout << setw(5) << row[0] << " | " << setw(15) << row[1] << " | " << setw(15) << row[2] << " | " << setw(8) << row[3] << " | " << setw(13) << row[4] << " | " << setw(15) << row[5] << " | " << setw(10) << row[6] << " | " << setw(13) << row[8] << " | " << setw(5) << row[7] << endl;
                }
                mysql_free_result(result);
            }
        }

        string queryVentas = "SELECT v.id, v.nombre_articulo, v.nombre_cliente, v.cantidad, v.precio, v.total, v.fecha_ingreso FROM ventas v WHERE v.fecha_ingreso BETWEEN '" + fechaInicio + "' AND '" + fechaFin + "'";
        if (mysql_query(obj, queryVentas.c_str())) {
            cout << "Error: " << mysql_error(obj) << endl;
        } else {
            MYSQL_RES *result = mysql_store_result(obj);
            if (result) {
                MYSQL_ROW row;
                cout << "Ventas en kardex:" << endl;
                cout << "ID | Articulo | Cliente | Cantidad | Precio | Total | Fecha Ingreso" << endl;
                cout << "------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(result))) {
                    cout << setw(5) << row[0] << " | " << setw(15) << row[1] << " | " << setw(10) << row[2] << " | " << setw(8) << row[3] << " | " << setw(8) << row[4] << " | " << setw(8) << row[5] << " | " << setw(13) << row[6] << endl;
                }
                mysql_free_result(result);
            }
        }
    } else {
        cout << "Opcion no valida." << endl;
        return;
    }
}
// Función para mostrar el menú principal
void menu(MYSQL* obj) {
int opcion;
    do {
        cout << "\n==============================================" << endl;
        cout << "       SISTEMA DE FERRETERiA Y PUNTO DE VENTA       " << endl;
        cout << "==============================================" << endl;
        cout << "1.  Registrar Usuario" << endl;
        cout << "2.  Registrar Personal" << endl;
        cout << "3.  Registrar Puesto" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "4.  Registrar Cliente" << endl;
        cout << "5.  Registrar Proveedor" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "6.  Registrar Articulo" << endl;
        cout << "7.  Registrar Compra" << endl;
        cout << "8.  Registrar Venta" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "9.  Mostrar Planilla Laboral" << endl;
        cout << "10. Mostrar Compras y Ventas" << endl;
        cout << "11. Mostrar Kardex" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "12. Salir" << endl;
        cout << "==============================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Validar que la opción sea un número entero válido
        while (cin.fail() || opcion < 1 || opcion > 12) {
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(INT_MAX, '\n'); // Ignorar el resto de la línea
            cout << "Opcion no valida. Intente nuevamente: ";
            cin >> opcion;
        }

        switch (opcion) {
            case 1:
                registrarUsuario(obj);
                break;
            case 2:
                registrarPersonal(obj);
                break;
            case 3:
                registrarPuesto(obj);
                break;
            case 4:
                registrarCliente(obj);
                break;
            case 5:
                registrarProveedor(obj);
                break;
            case 6:
                registrarArticulo(obj);
                break;
            case 7:
                registrarCompra(obj);
                break;
            case 8:
                registrarVenta(obj);
                break;
            case 9:
                mostrarPlanillaLaboral(obj);
                break;
            case 10:
                mostrarComprasVentas(obj);
                break;
            case 11:
                mostrarKardex(obj);
                break;
            case 12:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 12);
}
int main() {
    MYSQL *obj;

    // Inicializar objeto MYSQL
    obj = mysql_init(NULL);
    if (obj == NULL) {
        cout << "Error al crear objeto: " << mysql_error(obj) << endl;
        return 1;
    }

    // Conectar a la base de datos
    if (mysql_real_connect(obj, "localhost", "root", "ing123", "FERRETERIA1", 3306, NULL, 0) == NULL) {
        cout << "Error de conexion: " << mysql_error(obj) << endl;
        mysql_close(obj);
        return 1;
    } else {
        cout << "Conexion exitosa" << endl;
    }
 // Verificar las credenciales de inicio de sesión
    if (!iniciarSesion(obj)) {
        cout << "Credenciales incorrectas. Saliendo del programa." << endl;
        mysql_close(obj);
        return 1;
    }
    // Crear las tablas necesarias
    createTables(obj);

    // Mostrar menú
    menu(obj);

    // Cerrar conexión
    mysql_close(obj);

    return 0;
}
