#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "menu.h"

void clear_menu() {
    system("cls");
}

void any_key() {
    printf("\nPressiona qualquer tecla para continuar...");
    _getch();
}

int initial_menu(NODE* utilizadores, USER** auth) {
    int opc = 1;

    do {
        clear_menu();
        printf("+--------------------------------------------------------------+\n");
        printf("|        SOFTWARE GESTAO DOS MEIOS DE MOBILIDADE ELETRICA      |\n");
        printf("+--------------------------------------------------------------+\n\n");
        printf("[ 1 ] Autenticar\n");
        printf("[ 0 ] Sair\n\n");
        printf("Opcao:");
        scanf("%d", &opc);
        fflush(stdin);

        clear_menu();

        if (opc == 1) {
            if (login_menu(utilizadores, auth) == 0) {
                return 0;
            }
        }
    } while (opc != 0);

    return -1;
}


int login_menu(NODE* utilizadores, USER** auth) {
    char username[100], password[100];
    int opc = 1;

    clear_menu();
    do {
        printf("+------------------------+\n");
        printf("|      AUTENTICACAO      |\n");
        printf("+------------------------+\n\n");

        printf("| Username: ");
        scanf("%s", username);
        fflush(stdin);

        printf("| Password: ");
        scanf("%s", password);
        fflush(stdin);
        clear_menu();

        *auth = login(utilizadores, username, password);
        clear_menu();

        if (*auth != NULL) return 0;

        if (*auth == NULL) {
            do {
                printf("----------------------------------\n");
                printf(" Dados de autenticação inválidos! \n");
                printf("----------------------------------\n\n");
                printf("[1] Tenta Novamente!\n[0] Sair\n\nOpcao: ");
                scanf("%d", &opc);
                fflush(stdin);
                clear_menu();
            } while (opc < 0 || opc > 1);
        }
    } while (*auth == NULL && opc != 0);

    return -1;
}


int menu_cliente(USER auth, NODE** utilizadores, NODE** vertices) {
    int escolha;

    do {
        clear_menu();
        printf("+----------------------------------------+\n");
        printf("|              MENU CLIENTE              |\n");
        printf("+----------------------------------------+\n\n");

        printf("[ 1 ] Alugar Meio de Mobilidade Eletrica\n");
        printf("[ 2 ] Listar Meios Disponiveis (Ordem decrescente de autonomia)\n");
        printf("[ 3 ] Listar Meios Disponiveis por Geocode\n");
        printf("[ 4 ] Listar Meios Proximos Disponiveis por Geocode\n");
        printf("[ 5 ] Alterar Dados Cliente\n");
        printf("[ 6 ] Carregar Saldo\n");
        printf("[ 7 ] Guardar clientes\n");
        printf("[ 0 ] Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        fflush(stdin);

        clear_menu();

        switch (escolha) {

        case 1:
            //alugar_meio(meios, utilizadores, auth);
            any_key();
            break;

        case 2:
            //listar_meios_disponiveis_desc_autonomia(*meios);
            any_key();
            break;

        case 3: 
            listar_meios_geocode(*vertices);
            any_key();
            break;
            
        case 4: 
            //listar_meios_proximos(*meios); 
            any_key();
            break;

        case 5:
            alterar_dados_proprio_cliente(utilizadores, auth);
            any_key();
            break;
            
        case 6:
            carregar_saldo(auth, utilizadores);
            any_key();
            break;

        case 7: 
            guardar_users(*utilizadores);
            printf("Utilizadores guardados com sucesso!\n");
            any_key();
            break;

        case 9:
            return -4;
        }

    } while (escolha != 0);
    return 0;
}

int menu_gestor(USER auth, NODE** utilizadores, NODE** meios, NODE** vertices) {
    int escolha;

    do {
        clear_menu();
        printf("+--------------------------------------+\n");
        printf("|              MENU GESTOR             |\n");
        printf("+--------------------------------------+\n\n");

        printf("[ 1 ] Gerir Gestores\n");
        printf("[ 2 ] Gerir Clientes\n");
        printf("[ 3 ] Gerir Grafo\n");
        printf("[ 9 ] Terminar a Sessao\n");
        printf("[ 0 ] Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        fflush(stdin);

        clear_menu();

        switch (escolha) {
        case 1:
            menu_gerir_gestores(auth, utilizadores);
            break;

        case 2:
            menu_gerir_clientes(auth, utilizadores);
            break;
        /*
        case 3:
            //menu_gerir_meios(auth, utilizadores, meios, vertices);
            break;
        */
        case 3:
            menu_gerir_grafo(auth, utilizadores, vertices);
            break;
         
        case 9:
            return -4;
        default:
            break;
        }
    } while (escolha != 0);
    return 0;
}

void menu_gerir_gestores(USER auth, NODE** utilizadores) {
    int escolha;

    do {
        clear_menu();
        printf("+----------------------------------+\n");
        printf("|        MENU GERIR GESTORES       |\n");
        printf("+----------------------------------+\n\n");

        printf("[1] Registar Gestor\n");
        printf("[2] Alterar Dados do Gestor\n");
        printf("[3] Listar Gestores Registados\n");
        printf("[4] Guardar Gestores\n");
        printf("[0] Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        fflush(stdin);
        clear_menu();

        switch (escolha) {

        case 1:
            criar_gestor(utilizadores);
            any_key();
            break;

        case 2:
            alterar_dados_gestor(utilizadores);
            any_key();
            break;

        case 3:
            listar_gestores_registados(*utilizadores);
            any_key();
            break;

        case 4:
            guardar_users(*utilizadores);
            printf("Utilizadores guardados com sucesso!\n");
            any_key();
            break;

        case 0:
            printf("A sair do menu...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente...\n");
            break;
        }
    } while (escolha != 0);
}

void menu_gerir_clientes(USER auth, NODE** utilizadores) {
    int escolha;

    do {
        clear_menu();

        printf("+----------------------------------+\n");
        printf("|        MENU GERIR CLIENTES       |\n");
        printf("+----------------------------------+\n\n");

        printf("[1] Registar Cliente\n");
        printf("[2] Alterar Dados do Cliente\n");
        printf("[3] Listar Clientes Registados\n");
        printf("[4] Remover Cliente\n");
        printf("[5] Guardar Clientes\n");
        printf("[0] Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        fflush(stdin);

        clear_menu();

        switch (escolha) {

        case 1:
            criar_cliente(utilizadores);
            any_key();
            break;

        case 2:
            alterar_dados_cliente(utilizadores);
            any_key();
            break;

        case 3:
            listar_clientes_registados(*utilizadores);
            any_key();
            break;

        case 4:
            remover_cliente(utilizadores);
            any_key();
            break;

        case 5:
            guardar_users(*utilizadores);
            printf("Utilizadores guardados com sucesso!\n");
            any_key();
            break;

        case 0:
            printf("A Sair do menu...\n");
            break;
        default:
            printf("Opcao invalida, tente novamente...\n");
        }

    } while (escolha != 0);
}

void menu_gerir_meios(USER auth, NODE** utilizadores, NODE** meios, NODE** vertice) {
    int escolha;

    do {
        clear_menu();
        printf("+-----------------------------------------------------+\n");
        printf("|        MENU GERIR MEIOS DE MOBILIDADE ELETRICA      |\n");
        printf("+-----------------------------------------------------+\n\n");

        printf("[1] Alterar Dados do Meio de Mobilidade\n");
        printf("[2] Listar Meios Disponiveis (Ordem decrescente de Autonomia)\n");
        printf("[3] Listar Meios Disponiveis numa Localizacao com Geocode\n");
        printf("[4] Remover Meio\n");
        printf("[5] Guardar Meios\n");
        printf("[0] Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        fflush(stdin);

        clear_menu();

        switch (escolha) {

        case 1:
            alterar_dados_meios(meios);
            any_key();
            break;

        case 2:
            listar_meios_disponiveis_desc_autonomia(*meios);
            any_key();
            break;

        case 3:
            listar_meios_geocode(*vertice);
            any_key();
            break;

        case 4:
            remover_meio(meios);
            any_key();
            break;

        case 5:
            guardar_meios(*meios);
            printf("Meios de mobilidade guardados com sucesso!\n");
            any_key();
            break;

        case 0:
            printf("A sair do menu...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente...\n");
            break;
        }
    } while (escolha != 0);
}

int menu_gerir_grafo(USER auth, NODE** utilizadores, NODE** vertices) {
    int escolha;
    char geocode[TAM];
    VERTICE* verticeEscolhido;

    do {
        clear_menu();
        printf("+------------------------------+\n");
        printf("|        MENU GERIR GRAFO      |\n");
        printf("+------------------------------+\n\n");

        printf("[1] Adicionar Meio de Mobilidade Eletrica\n");
        printf("[2] Conectar Vertices\n");
        printf("[3] Gerir Meios de Mobilidade Eletrica no Vértice\n");
        printf("[4] Listar Vertices\n");
        printf("[5] Guardar Grafo\n");
        printf("[0] Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        fflush(stdin);

        clear_menu();

        switch (escolha) {

        case 1: 
            criar_meio(vertices); 
            any_key();
            break;

        case 2:
            ligar_vertices(vertices);
            any_key();
            break;

        case 3:
            printf("Escolha o Vertice através do Geocode: ");
            scanf("%s", geocode); 
            verticeEscolhido = find_vertice_by_geocode(vertices, geocode);
            menu_gerir_meios(auth, utilizadores, verticeEscolhido->meios, vertices);
            break;
        /*
        case 3:
            guardar_grafo();
            printf("Grafo guardado com sucesso!\n");
            any_key();
            break;
         */
        case 0:
            printf("A sair do menu...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente...\n");
            break;
        }
    } while (escolha != 0);
}

int criar_gestor(NODE** utilizadores) {
    int opc, res;

    USER* user = malloc(sizeof(USER));

    if (user == NULL) return -3;
    do {
        clear_menu();
        printf("| NOVO GESTOR:\n\n");

        printf("  | Username: ");
        scanf(" %[^\n]", user->username);
        fflush(stdin);

        printf("  | Password: ");
        scanf(" %[^\n]", user->password);
        fflush(stdin);

        printf("  | Nome: ");
        scanf(" %[^\n]", user->nome);
        fflush(stdin);

        printf("  | Email: ");
        scanf(" %[^\n]", user->email);
        fflush(stdin);

        printf("  | NIF: ");
        scanf(" %i", &user->NIF);
        fflush(stdin);

        printf("  | Saldo: ");
        scanf(" %f", &user->saldo);
        fflush(stdin);

        user->role = 1;

        res = add_user(utilizadores, user);

        switch (res) {
        case 0:
            guardar_users(*utilizadores);
            printf("Gestor criado com sucesso");
            return 0;
        case -1:
            do {
                clear_menu();
                printf("Username já existe\n");
                printf("[1] Tentar novamente!\n");
                printf("[0] Cancelar\n\n");
                printf("Opcao:");
                scanf("%i", &opc);
                while (getchar() != '\n');
            } while (opc < 0 || opc > 1);
            break;
        default: break;
        }
    } while (opc != 0);

    free(user);
    return -1;
}
int criar_cliente(NODE** utilizadores) {
    int opc, res;

    USER* user = malloc(sizeof(USER));

    if (user == NULL) return -3;
    do {
        clear_menu();
        fflush(stdin);
        printf("| NOVO CLIENTE:\n\n");

        printf("  | Username: ");
        scanf(" %[^\n]", user->username);
        fflush(stdin);

        printf("  | Password: ");
        scanf(" %[^\n]", user->password);
        fflush(stdin);

        printf("  | Nome: ");
        scanf(" %[^\n]", user->nome);
        fflush(stdin);

        printf("  | Email: ");
        scanf(" %[^\n]", user->email);
        fflush(stdin);

        printf("  | NIF: ");
        scanf(" %i", &user->NIF);
        fflush(stdin);

        printf("  | Saldo: ");
        scanf(" %f", &user->saldo);
        fflush(stdin);

        user->role = 0; //Role = Cliente

        res = add_user(utilizadores, user);

        switch (res) {
        case 0:
            guardar_users(*utilizadores);
            printf("\nCliente criado com sucesso!\n");
            return 0;

        case -1:
            do {
                clear_menu();
                printf("Username já existe\n");
                printf("[1] Tentar novamente!\n");
                printf("[0] Cancelar\n\n");
                printf("Opcao:");
                scanf("%i", &opc);
                while (getchar() != '\n');
            } while (opc < 0 || opc > 1);
            break;
        default: break;
        }
    } while (opc != 0);

    free(user);
    return -1;
}
int criar_meio_e_vertice(NODE** vertices) {
    int opc, res;
    MEIO* meio = malloc(sizeof(MEIO)); // Aloca memória para um novo meio de mobilidade
    VERTICE* vertice;

    if (meio == NULL) return -3; // Erro na alocação de memória para o meio

    do {
        clear_menu();
        printf("| NOVO MEIO DE MOBILIDADE ELETRICA:\n\n");

        printf("  | Codigo: ");
        scanf("%d", &meio->codigo);
        fflush(stdin);

        printf("  | Tipo: ");
        scanf("%s", meio->tipo);
        fflush(stdin);

        printf("  | Bateria: ");
        scanf("%f", &meio->bateria);
        fflush(stdin);

        printf("  | Autonomia: ");
        scanf("%f", &meio->autonomia);
        fflush(stdin);

        printf("  | Custo: ");
        scanf("%f", &meio->custo);
        fflush(stdin);

        printf("  | Geocode: ");
        scanf("%s", meio->geocode);
        fflush(stdin);

        printf("  | Latitude: ");
        scanf("%lf", &meio->latitude);
        fflush(stdin);

        printf("  | Longitude: ");
        scanf("%lf", &meio->longitude);
        fflush(stdin);

        meio->status = 0;

        vertice = find_vertice_by_geocode(*vertices, meio->geocode); // Verifica se o vértice já existe com base no geocódigo

        if (vertice == NULL) { // Se o vértice não existe, cria um novo
            vertice = malloc(sizeof(VERTICE));
            if (vertice == NULL) {
                free(meio);
                return -4; // Erro na alocação de memória para o vértice
            }

            // Preenche os dados do vértice
            strcpy(vertice->geocode, meio->geocode);
            vertice->latitude = meio->latitude;
            vertice->longitude = meio->longitude;
            vertice->arestas = NULL;
            vertice->meios = NULL;

            res = add_vertice(vertices, vertice); // Adiciona o vértice à lista de vértices
            if (res == -1) {// Se ocorreu algum erro ao adicionar o vértice, libera a memória alocada
                free(vertice);
                free(meio);
                return -2; // Erro ao adicionar o vértice
            }
        }

        // Adiciona o meio à lista de meios do vértice
        res = add_meio(&(vertice->meios), meio);

        switch (res) {
        case 0:
            //save_vertices() -> Tenho de criar função!
            printf("\nMeio de mobilidade eletrica adicionado com sucesso.\n");
            return 0;

        case -1:
            do {
                clear_menu();
                printf("Código de meio de mobilidade eletrica já existe.\n");
                printf("[1] Tentar novamente!\n");
                printf("[0] Cancelar\n\n");
                printf("Opção:");
                scanf("%i", &opc);
                while (getchar() != '\n');
            } while (opc < 0 || opc > 1);
            break;
        default:
            break;
        }
    } while (opc != 0);

    free(meio); // Libera a memória alocada para o meio
    return -1;
}
int criar_meio(NODE** vertices) {
    int opc, res;
    MEIO* meio = malloc(sizeof(MEIO)); // Aloca memória para um novo meio de mobilidade
    VERTICE* vertice;

    if (meio == NULL) return -3; // Erro na alocação de memória para o meio

    do {
        clear_menu();
        printf("| NOVO MEIO DE MOBILIDADE ELETRICA:\n\n");

        printf("  | Codigo: ");
        scanf("%d", &meio->codigo);
        fflush(stdin);

        printf("  | Tipo: ");
        scanf("%s", meio->tipo);
        fflush(stdin);

        printf("  | Bateria: ");
        scanf("%f", &meio->bateria);
        fflush(stdin);

        printf("  | Autonomia: ");
        scanf("%f", &meio->autonomia);
        fflush(stdin);

        printf("  | Custo: ");
        scanf("%f", &meio->custo);
        fflush(stdin);

        printf("  | Geocode: ");
        scanf("%s", meio->geocode);
        fflush(stdin);

        printf("  | Latitude: ");
        scanf("%lf", &meio->latitude);
        fflush(stdin);

        printf("  | Longitude: ");
        scanf("%lf", &meio->longitude);
        fflush(stdin);

        meio->status = 0;

        vertice = find_vertice_by_geocode(*vertices, meio->geocode); // Verifica se o vértice já existe com base no geocódigo

        if (vertice == NULL) { // Se o vértice não existe, cria um novo
            free(meio); // Libera a memória alocada para o meio
            return -1; // O vértice não existe, não é possível vincular o meio
        }

        // Adiciona o meio à lista de meios do vértice
        res = add_meio(&(vertice->meios), meio);

        switch (res) {
        case 0:
            //save_vertices() -> Tenho de criar função!
            printf("\nMeio de mobilidade eletrica adicionado com sucesso.\n");
            return 0;

        case -1:
            do {
                clear_menu();
                printf("Código de meio de mobilidade eletrica já existe.\n");
                printf("[1] Tentar novamente!\n");
                printf("[0] Cancelar\n\n");
                printf("Opção:");
                scanf("%i", &opc);
                while (getchar() != '\n');
            } while (opc < 0 || opc > 1);
            break;
        default:
            break;
        }
    } while (opc != 0);

    free(meio); // Libera a memória alocada para o meio
    return -1;
}

int ligar_vertices(NODE** vertices) {
    char origem[TAM];
    char destino[TAM];
    float peso = 0.0;

    printf("Vertice de Origem: ");
    scanf("%s", origem);
    printf("Vertice de Destino: ");
    scanf("%s", destino);

    int res = criar_aresta(vertices, origem, destino, peso);

    switch (res) {
    case 1:
        printf("\nVertices Conectados com Sucesso.\n");
        return 0;
    case -1:
        printf("\nVertice de Origem ou Destino não Encontrado.\n");
        return -1;
    case -2:
        printf("\nAresta já Existe.\n");
        return -1;
    default:
        return -1;
    }
}

void listar_gestores_registados(NODE* utilizadores) {
    NODE* aux = NULL;
    USER* user = NULL;

    aux = utilizadores;
    while (aux != NULL) {
        user = (USER*)aux->data;

        if (user->role == 1 && strcmp(user->username, "root") != 0) {
            printf("%s\n", user->nome);
        }

        aux = aux->next;
    }
}
void listar_clientes_registados(NODE* utilizadores) {
    NODE* aux = NULL;
    USER* user = NULL;

    aux = utilizadores;
    while (aux != NULL) {
        user = (USER*)aux->data;

        if (user->role == 0 && strcmp(user->username, "root") != 0) {
            printf("%s\n", user->nome);
        }

        aux = aux->next;
    }
}
void listar_meios_disponiveis_decrescente_autonomia(NODE* vertices) {
    NODE* aux_vertice = vertices;
    MEIO* meio = NULL;
    MEIO temp;
    int pos = 0, size = 0, i, j;

    MEIO* lista = NULL;
    NODE* aux = NULL;

    // Conta o número de meios de mobilidade disponíveis
    while (aux_vertice != NULL) {
        aux = ((VERTICE*)aux_vertice->data)->meios;
        while (aux != NULL) {
            meio = (MEIO*)aux->data;
            if (meio->status == 0) {
                size++;
            }
            aux = aux->next;
        }
        aux_vertice = aux_vertice->next;
    }   

    if (size == 0) {
        printf("Nenhum meio disponivel!\n");
        return;
    }

    lista = (MEIO*)calloc(size, sizeof(MEIO));
    aux_vertice = vertices;
    pos = 0;

    // Cria a lista de meios de mobilidade disponíveis
    while (aux_vertice != NULL) {
        aux = ((VERTICE*)aux_vertice->data)->meios;
        while (aux != NULL) {
            meio = (MEIO*)aux->data;
            if (meio->status == 0) {
                lista[pos] = *meio;
                pos++;
            }
            aux = aux->next;
        }
        aux_vertice = aux_vertice->next;
    }

    // INSERTION SORT
    for (i = 1; i < pos; i++) {
        temp = lista[i];
        j = i - 1;
        while (j >= 0 && lista[j].autonomia < temp.autonomia) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = temp;
    }

    printf("Meios disponiveis:\n");
    for (i = 0; i < pos; i++) {
        temp = lista[i];
        printf("Codigo: %d\n", temp.codigo);
        printf("Tipo: %s\n", temp.tipo);
        printf("Autonomia: %.2f\n", temp.autonomia);
        printf("Custo: %.2f\n", temp.custo);
        printf("Localizacao: %s\n", temp.geocode);
        printf("Latitude: %lf\n", temp.latitude);
        printf("Longitude: %lf\n", temp.longitude);
        printf("------------------------\n");
    }

    free(lista);
}
void listar_meios_proximos(NODE* vertices) {
    NODE* aux = NULL;
    MEIO* meio = NULL;
    VERTICE* vertice = NULL; 
    char geocode[100];
    double latitude, longitude;

    printf("Introduza a sua Localizacao:");
    scanf("%s", geocode);
    fflush(stdin);

    printf("Introduza as Coordenadas:\n");
    printf("  | Latitude: ");
    scanf("%lf", &latitude);
    fflush(stdin);

    printf("  | Longitude: ");
    scanf("%lf", &longitude);
    fflush(stdin);
    printf("------------------------------");

    vertice = find_vertice_by_geocode(vertices, geocode);

    if (vertice == NULL) {
        printf("Erro: Vértice não encontrado com o geocódigo fornecido.\n");
        return;
    }

    int tamanho = 0;
    aux = vertice->meios;
    while (aux != NULL) {
        meio = (MEIO*)aux->data;
        if (meio->status == 0) {
            tamanho++;
        }
        aux = aux->next;
    }

    if (tamanho == 0) {
        printf("Nenhum Meio Disponivel!\n");
        return;
    }

    MEIO* lista = (MEIO*)calloc(tamanho, sizeof(MEIO));

    int pos = 0;
    aux = vertice->meios;
    while (aux != NULL) {
        meio = (MEIO*)aux->data;
        if (meio->status == 0) {
            lista[pos] = *meio;
            pos++;
        }
        aux = aux->next;
    }

    // Bubble sort para ordenar a lista por distância
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            double distancia1 = calcular_distancia(latitude, longitude, lista[j].latitude, lista[j].longitude);
            double distancia2 = calcular_distancia(latitude, longitude, lista[j + 1].latitude, lista[j + 1].longitude);
            if (distancia1 > distancia2) {
                MEIO temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    int encontrou = 0;
    printf("\nMeios Proximos Disponiveis:\n");
    for (int i = 0; i < tamanho; i++) {
        if (strstr(lista[i].geocode, geocode) != NULL) {
            printf("Codigo: %d\n", lista[i].codigo);
            printf("Tipo: %s\n", lista[i].tipo);
            printf("Autonomia: %.2f\n", lista[i].autonomia);
            printf("Custo: %.2f\n", lista[i].custo);
            printf("Localizacao: %s\n", lista[i].geocode);
            printf("Distancia: %.2f\n", calcular_distancia(latitude, longitude, lista[i].latitude, lista[i].longitude));
            printf("------------------------------\n");
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum meio encontrado com o geocode fornecido.\n");
    }

    free(lista);
}
void listar_meios_vertice_geocode(NODE* vertices) {
    NODE* aux = NULL;
    NODE* aux_meio = NULL;
    VERTICE* vertice = NULL;
    MEIO* meio = NULL;

    char geocode[100];

    printf("Introduza a sua Localizacao:");
    scanf("%s", geocode);
    fflush(stdin);

    int encontrou = 0;
    aux = vertices;
    while (aux != NULL) {
        vertice = (VERTICE*)aux->data;

        if (strstr(vertice->geocode, geocode) != NULL) {

            aux_meio = vertice->meios;
            while (aux_meio != NULL) {
                meio = (MEIO*)aux_meio->data;

                printf("Codigo: %d\n", meio->codigo);
                printf("Tipo: %s\n", meio->tipo);
                printf("Autonomia: %.2f\n", meio->autonomia);
                printf("Custo: %.2f\n", meio->custo);
                printf("Localizacao: %s\n", meio->geocode);
                printf("Latitude: %f\n", meio->latitude);
                printf("Longitude: %f\n", meio->longitude);
                printf("------------------------\n");

                aux_meio = aux_meio->next;
            }
            encontrou = 1;
        }

        aux = aux->next;
    }
    if (!encontrou) {
        printf("Nao foram encontrados meios de mobilidade nessa localizacao.\n");
    }
}


void alterar_dados_gestor(NODE** utilizadores) {
    int opc = 1, selected;
    char username[100];
    USER* user = NULL;

    do {
        printf("Username do gestor:");
        scanf("%s", username);
        fflush(stdin);

        user = find_user_by_username(*utilizadores, username);

        if (user == NULL) {
            do {
                clear_menu();
                printf("Utilizador nao encontrado!\n\n");
                printf("[1]Tentar novamente\n");
                printf("[0] Sair\n");
                printf("Opcao:");
                scanf("%i", &opc);
                fflush(stdin);
                clear_menu();
            } while (opc < 0 || opc > 1);
        }
        else {
            do {
                clear_menu();
                printf("Que campo deseja alterar?\n");
                printf("[1] Nome\n");
                printf("[2] Password\n");
                printf("[0] Sair\n");
                printf("Opcao:");
                scanf("%i", &selected);
                fflush(stdin);

                clear_menu();

                switch (selected) {
                case 0:
                    return;
                case 1:
                    printf("| Novo nome: ");
                    scanf(" %[^\n]", user->nome);
                    fflush(stdin);
                    guardar_users(*utilizadores);
                    printf("\nNome alterado com sucesso!\n");
                    break;
                case 2:
                    printf("| Nova password: ");
                    scanf(" %[^\n]", user->password);
                    fflush(stdin);
                    guardar_users(*utilizadores);
                    printf("\nPassword alterada com sucesso!\n");
                    break;
                default:
                    printf("\nOpcao invalida! Tente novamente.");
                    break;
                }

                if (selected != 0) {
                    do {
                        printf("\nDeseja continuar a alterar dados deste utilizador?");
                        printf("\n[1] Sim");
                        printf("\n[0] Nao");
                        printf("\nOpcao:");
                        scanf("%i", &opc);
                        fflush(stdin);
                        clear_menu();
                    } while (opc < 0 || opc > 1);
                }

            } while (selected != 0 && opc != 0);
        }
    } while (opc != 0);
}
void alterar_dados_proprio_cliente(NODE** utilizadores, USER auth) {
    int selected = 0;
    USER* user = NULL;

    user = find_user_by_username(*utilizadores, auth.username);

    do {
        clear_menu();
        printf("Que campo deseja alterar?\n");
        printf("[1] Nome\n");
        printf("[2] Password\n");
        printf("[3] Email\n");
        printf("[4] NIF\n");
        printf("[0] Sair\n");
        printf("Opcao:");
        scanf("%i", &selected);
        fflush(stdin);

        clear_menu();

        switch (selected) {
        case 0:
            return;
        case 1:
            printf("Novo nome: ");
            scanf(" %[^\n]", user->nome);
            fflush(stdin);
            guardar_users(*utilizadores);
            printf("Nome alterado com sucesso!\n");
            break;
        case 2:
            printf("Nova password: ");
            scanf(" %[^\n]", user->password);
            fflush(stdin);
            guardar_users(*utilizadores);
            printf("Password alterada com sucesso!\n");
            break;
        case 3:
            printf("Novo Email: ");
            scanf(" %[^\n]", user->email);
            fflush(stdin);
            guardar_users(*utilizadores);
            printf("Email alterado com sucesso!\n");
            break;
        case 4:
            printf("Novo NIF: ");
            scanf(" %i", &user->NIF);
            fflush(stdin);
            guardar_users(*utilizadores);
            printf("NIF alterado com sucesso!\n");
            break;

        default:
            break;
        }
    } while (selected != 0);
    guardar_users(*utilizadores);
}
void alterar_dados_cliente(NODE** utilizadores) {
    int opc, selected;
    char username[100];
    USER* user = NULL;

    do {
        printf("Username do cliente:");
        scanf("%s", username);
        fflush(stdin);

        user = find_user_by_username(*utilizadores, username);

        if (user == NULL) {
            do {
                clear_menu();
                printf("Utilizador nao encontado!\n\n");
                printf("[1]Tentar novamente\n");
                printf("[0] Sair\n");
                printf("Opcao:");
                scanf("%i", &opc);
                fflush(stdin);
                clear_menu();
            } while (opc < 0 || opc > 1);
        }
        else {
            do {
                clear_menu();
                printf("Que campo deseja alterar?\n");
                printf("[1] Nome\n");
                printf("[2] Password\n");
                printf("[3] Email\n");
                printf("[4] NIF\n");
                printf("[0] Sair\n");
                printf("Opcao:");
                scanf("%i", &selected);
                fflush(stdin);

                clear_menu();

                switch (selected) {
                case 0:
                    return;
                case 1:
                    printf("Novo nome: ");
                    scanf(" %[^\n]", user->nome);
                    fflush(stdin);
                    guardar_users(*utilizadores);
                    printf("Nome alterado com sucesso!\n");
                    break;
                case 2:
                    printf("Nova password: ");
                    scanf(" %[^\n]", user->password);
                    fflush(stdin);
                    guardar_users(*utilizadores);
                    printf("Password alterada com sucesso!\n");
                    break;
                case 3:
                    printf("Novo Email: ");
                    scanf(" %[^\n]", user->email);
                    fflush(stdin);
                    guardar_users(*utilizadores);
                    printf("Email alterado com sucesso!\n");
                    break;
                case 4:
                    printf("Novo NIF: ");
                    scanf(" %i", &user->NIF);
                    fflush(stdin);
                    guardar_users(*utilizadores);
                    printf("NIF alterado com sucesso!\n");
                    break;

                default:
                    break;
                }

            } while (selected != 0);
        }
    } while (opc != 0);

    guardar_users(*utilizadores);
}
void alterar_dados_meios(NODE** vertices) {
    int opc = 1, selected;
    int codigo;
    MEIO* meio = NULL;

    do {
        printf("Código do meio de mobilidade elétrica: ");
        scanf("%d", &codigo);
        fflush(stdin);

        NODE* aux_vertice = *vertices;
        while (aux_vertice != NULL) {
            NODE* aux_meio = ((VERTICE*)aux_vertice->data)->meios;
            while (aux_meio != NULL) {
                meio = (MEIO*)aux_meio->data;
                if (meio->codigo == codigo) {
                    break;
                }
                aux_meio = aux_meio->next;
            }
            if (aux_meio != NULL) {
                break;
            }
            aux_vertice = aux_vertice->next;
        }

        if (meio == NULL) {
            do {
                clear_menu();
                printf("Meio de mobilidade elétrica não encontrado!\n\n");
                printf("[1] Tentar novamente\n");
                printf("[0] Sair\n");
                printf("Opção: ");
                scanf("%i", &opc);
                fflush(stdin);
                clear_menu();
            } while (opc < 0 || opc > 1);
        }
        else {
            do {
                clear_menu();
                printf("Que campo deseja alterar?\n");
                printf("[1] Tipo\n");
                printf("[2] Bateria\n");
                printf("[3] Autonomia\n");
                printf("[4] Custo\n");
                printf("[5] Geocode\n");
                printf("[6] Latitude\n");
                printf("[7] Longitude\n");
                printf("[0] Sair\n");
                printf("Opção: ");
                scanf("%i", &selected);
                fflush(stdin);

                clear_menu();

                switch (selected) {
                case 0:
                    return;

                case 1:
                    printf("| Novo tipo: ");
                    scanf(" %[^\n]", meio->tipo);
                    fflush(stdin);
                    save_meios(*vertices);
                    printf("\nTipo alterado com sucesso!\n");
                    break;

                case 2:
                    printf("| Nova bateria: ");
                    scanf("%f", &meio->bateria);
                    fflush(stdin);
                    save_meios(*vertices);
                    printf("\nBateria alterada com sucesso!\n");
                    break;

                case 3:
                    printf("| Nova autonomia: ");
                    scanf("%f", &meio->autonomia);
                    fflush(stdin);
                    save_meios(*vertices);
                    printf("\nAutonomia alterada com sucesso!\n");
                    break;

                case 4:
                    printf("| Novo custo: ");
                    scanf("%f", &meio->custo);
                    fflush(stdin);
                    save_meios(*vertices);
                    printf("\nCusto alterado com sucesso!\n");
                    break;

                case 5:
                    printf("| Novo geocode: ");
                    scanf("%f", &meio->geocode);
                    fflush(stdin);
                    save_meios(*vertices);
                    printf("\nGeocode alterado com sucesso!\n");
                    break;

                case 6:
                    printf("| Nova Latitude: ");
                    scanf("%lf", &meio->latitude);
                    fflush(stdin);
                    save_meios(*vertices);
                    printf("\nLatitude alterada com sucesso!\n");
                    break;

                case 7:
                    printf("| Nova Longitude: ");
                    scanf("%lf", &meio->longitude);
                    fflush(stdin);
                    save_meios(*vertices);
                    printf("\nLongitude alterada com sucesso!\n");
                    break;

                default:
                    printf("\nOpção inválida! Tente novamente.\n");
                    break;
                }

                if (selected != 0) {
                    do {
                        printf("\nDeseja continuar a alterar dados deste meio de mobilidade elétrica?");
                        printf("\n[1] Sim");
                        printf("\n[0] Não");
                        printf("\nOpção: ");
                        scanf("%i", &opc);
                        fflush(stdin);
                        clear_menu();
                    } while (opc < 0 || opc > 1);
                }

            } while (selected != 0 && opc != 0);
        }
    } while (opc != 0);
}

void remover_cliente(NODE** utilizadores) {
    int opc = 0;

    USER* user = malloc(sizeof(USER));

    // Verificar se o utilizador existe
    if (user == NULL) {
        printf("Utilizador nao existe!\n");
        return;
    }

    do {
        clear_menu();

        printf("Username do utilizador: ");
        scanf("%s", user->username);
        fflush(stdin);

        user = find_user_by_username(*utilizadores, user->username);

        // Verificar se é cliente
        if (user->role != 0) {
            printf("O Utilizador nao e um cliente!\n");
            printf("Tente novamente\n 0 - cancelar, ou 1!\n");
            scanf("%i", &opc);
            fflush(stdin);
        }

        switch (remove_user_by_username(utilizadores, user->username)) {
        case 0:
            printf("Uitlizador removido com sucesso!\n");
            guardar_users(*utilizadores);
            return;
            break;

        case -1:
            printf("Utilizador nao existe!\n");
            printf("Tentar novamente? 0 - cancelar, ou 1!\n");
            scanf("%i", &opc);
            fflush(stdin);
            break;
        }
    } while (opc != 0);
}
void remover_meio(NODE** vertices) {
    int opc = 0;
    int codigo;
    MEIO* meio = NULL;

    do {
        clear_menu();

        printf("Código do meio: ");
        scanf("%i", &codigo);
        fflush(stdin);

        // Procurar o meio pelo código nos vértices
        NODE* aux_vertice = *vertices;
        while (aux_vertice != NULL) {
            NODE** meios = &((VERTICE*)aux_vertice->data)->meios;
            meio = find_meio_by_codigo(meios, codigo);
            if (meio != NULL) {
                break;
            }
            aux_vertice = aux_vertice->next;
        }

        if (meio == NULL) {
            printf("Meio não existe!\n");
            printf("Tentar novamente? 0 - Cancelar, ou 1!\n");
            scanf("%i", &opc);
            fflush(stdin);
        }
        else {
            switch (remove_meio_by_codigo(&((VERTICE*)aux_vertice->data)->meios, codigo)) {
            case 0:
                printf("Meio removido com sucesso!\n");
                save_meios(*vertices);
                return;
                break;

            case -1:
                printf("Meio não existe!\n");
                printf("Tentar novamente? 0 - Cancelar, ou 1!\n");
                scanf("%i", &opc);
                fflush(stdin);
                break;
            }
        }

    } while (opc != 0);
}

void alugar_meio(NODE** meios, NODE** utilizadores, USER auth) {
    int codigo, opc = 0;
    float custo, saldo, new_saldo;
    USER* user = NULL;


    // Mostra o saldo do usuário
    printf("Saldo atual: %.2f\n\n", auth.saldo);

    // Lista os meios disponíveis
    listar_meios_disponiveis_descaa_autonomia(*meios);

    do {
        printf("Codigo do meio a alugar: ");
        scanf("%d", &codigo);
        fflush(stdin);

        // Encontra o meio pelo código
        MEIO* meio = find_meio_by_codigo(*meios, codigo);

        if (meio == NULL) {
            printf("Meio nao existe!\n");
            printf("Tentar novamente? 0 - cancelar, ou 1!\n");
            scanf("%i", &opc);
            fflush(stdin);
            continue;
        }

        // Verifica se o meio já está alugado
        if (meio->status == 1) {
            printf("Meio ja se encontra alugado!\n");
            printf("Tentar novamente? 0 - cancelar, ou 1!\n");
            scanf("%i", &opc);
            fflush(stdin);
            continue;
        }

        // Calcula o custo do aluguer
        custo = meio->custo;

        // Verifica se o usuário tem saldo suficiente
        saldo = auth.saldo;
        if (saldo < custo) {
            printf("Saldo insuficiente para alugar este meio de mobilidade!\n");
            printf("Tentar novamente? 0 - cancelar, ou 1!\n");
            scanf("%i", &opc);
            fflush(stdin);
            continue;
        }

        // Atualiza o saldo do usuário
        new_saldo = saldo - custo;

        user = find_user_by_username(*utilizadores, auth.username);
        user->saldo = user->saldo;

        // Atualiza o status do meio
        meio->status = 1;

        // Mostra o sucesso do aluguer
        printf("Meio de mobilidade alugado com sucesso!\n\n");
        printf("Novo saldo: %.2f\n", saldo);

        // Salva as alterações
        guardar_users(*utilizadores);
        guardar_meios(*meios);

        return;
    } while (opc != 0);
}

void carregar_saldo(USER auth, NODE** utilizadores) {
    float saldo_atual, valor_carregamento;
    USER* user = NULL;

    printf("Seu saldo atual: %.2f\n", auth.saldo);
    printf("Digite o valor que deseja carregar: ");
    scanf("%f", &valor_carregamento);
    fflush(stdin);

    // Verificar se o valor é válido
    if (valor_carregamento <= 0) {
        printf("Valor inválido!\n");
        return;
    }

    saldo_atual = auth.saldo + valor_carregamento;
    user = find_user_by_username(*utilizadores, auth.username);

    user->saldo = saldo_atual;

    // Atualizar o ficheiro com as informações do utilizador
    guardar_users(*utilizadores);

    printf("\nSaldo atualizado com sucesso!\n");
    printf("Saldo atual: %.2f\n", saldo_atual);
}

