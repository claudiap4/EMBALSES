#include <stdio.h>
#include <string.h>

#define MAX 50
#define MAX_INTENTOS 3

int registrarUsuario(const char* nuevoUsuario);
int iniciarSesion();
int usuarioExiste(const char* usuario);

void main() {
    int opcion = 0;
    char opcionTexto[MAX];

    while (1) {
        printf(" Bienvenido/a! \n");
        printf("1. Registrarse\n");
        printf("2. Iniciar sesion\n");
        printf("Seleccione una opcion: ");
        if (!fgets(opcionTexto, MAX, stdin)) {
            printf("Error. Intentelo de nuevo.\n\n");
            continue;
        }

        if (sscanf(opcionTexto, "%d", &opcion) != 1) {
            printf("Esa opcion no es valida. Por favor, ingrese un numero (1 o 2).\n\n");
            continue;
        }

        switch (opcion) {
            case 1: {
                int intentos = 0;
                while (1) {
                    char usuario[MAX];
                    printf("Ingrese nombre de usuario para registrarse: ");
                    if (!fgets(usuario, MAX, stdin)) {
                        printf("Error leyendo el nombre de usuario.\n");
                        continue;
                    }
                    usuario[strcspn(usuario, "\n")] = '\0';

                    if (registrarUsuario(usuario)) break;

                    if (++intentos >= MAX_INTENTOS) {
                        printf("Demasiados intentos fallidos para registrarse.\n");
                        return;
                    }

                    printf("Intente registrarse nuevamente...\n");
                }

                intentos = 0;
                while (!iniciarSesion()) {
                    if (++intentos >= MAX_INTENTOS) {
                        printf("Demasiados intentos fallidos para iniciar sesion.\n");
                        return;
                    }
                    printf("Intentemos iniciar sesion nuevamente...\n");
                }
                break;
            }
            case 2: {
                char usuario[MAX];
                printf("Escriba su nombre de usuario para inicio de sesion: ");
                if (!fgets(usuario, MAX, stdin)) {
                    printf("Ha habido un error leyendo el usuario.\n");
                    continue;
                }
                usuario[strcspn(usuario, "\n")] = '\0';

                if (!usuarioExiste(usuario)) {
                    printf("El usuario no esta registrado. Registrese.\n");

                    int intentos = 0;
                    while (1) {
                        printf("Ingrese un nuevo nombre de usuario para registrar: ");
                        if (!fgets(usuario, MAX, stdin)) {
                            printf("Error leyendo nombre de usuario.\n");
                            continue;
                        }
                        usuario[strcspn(usuario, "\n")] = '\0';

                        if (registrarUsuario(usuario)) break;

                        if (++intentos >= MAX_INTENTOS) {
                            printf("Demasiados intentos fallidos para registrarse.\n");
                            return;
                        }

                        printf("Registrese nuevamente\n");
                    }
                }

                int intentos = 0;
                while (!iniciarSesion()) {
                    if (++intentos >= MAX_INTENTOS) {
                        printf("Has intentado iniciar sesion demasiadas veces. Intentelo mas tarde\n");
                        return;
                    }
                    printf("Intentemos iniciar sesion nuevamente...\n");
                }
                break;
            }
            default:
                printf("Opcion no valida. Por favor, ingrese 1 o 2.\n\n");
                continue;
        }
        break;  // Salir del bucle si todo fue bien
    }

    printf("\n Bienvenido a la aplicacion de embalses!\n");
}

int usuarioExiste(const char* usuario) {
    FILE *archivo;
    char usuarioArchivo[MAX], contrasenaArchivo[MAX];

    archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) return 0;

    while (fscanf(archivo, "%s %s", usuarioArchivo, contrasenaArchivo) != EOF) {
        if (strcmp(usuario, usuarioArchivo) == 0) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

int registrarUsuario(const char* nuevoUsuario) {
    FILE *archivo;
    char contrasena[MAX];

    if (usuarioExiste(nuevoUsuario)) {
        printf("Ese nombre de usuario ya esta registrado.\n");
        return 0;
    }

    printf("Ingrese una contrasenya para %s: ", nuevoUsuario);
    if (!fgets(contrasena, MAX, stdin)) {
        printf("Error leyendo contrasenya.\n");
        return 0;
    }
    contrasena[strcspn(contrasena, "\n")] = '\0';

    archivo = fopen("usuarios.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para registrar usuario.\n");
        return 0;
    }

    fprintf(archivo, "%s %s\n", nuevoUsuario, contrasena);
    fclose(archivo);

    printf("Registro exitoso. Ahora puede iniciar sesion.\n");
    return 1;
}

int iniciarSesion() {
    FILE *archivo;
    char usuario[MAX], contrasena[MAX];
    char usuarioArchivo[MAX], contrasenaArchivo[MAX];

    printf("Ingrese su nombre de usuario: ");
    if (!fgets(usuario, MAX, stdin)) {
        printf("Error leyendo nombre de usuario.\n");
        return 0;
    }
    usuario[strcspn(usuario, "\n")] = '\0';

    printf("Ingrese su contrasenya: ");
    if (!fgets(contrasena, MAX, stdin)) {
        printf("Error leyendo contrasenya.\n");
        return 0;
    }
    contrasena[strcspn(contrasena, "\n")] = '\0';

    archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        printf("Error: No hay usuarios registrados.\n");
        return 0;
    }

    while (fscanf(archivo, "%s %s", usuarioArchivo, contrasenaArchivo) != EOF) {
        if (strcmp(usuario, usuarioArchivo) == 0 && strcmp(contrasena, contrasenaArchivo) == 0) {
            fclose(archivo);
            printf("Inicio de sesion exitoso.\n");
            return 1;
        }
    }

    fclose(archivo);
    printf("Nombre de usuario o contrasenya incorrectos.\n");
    return 0;
}
