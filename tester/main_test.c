#include "minishell.h"

#include "lexer.h"

static const char *quote_str(t_quote_type quote_type)
{
    switch (quote_type)
    {
        case NO_QUOTE:
            return "NONE";
        case SINGLE_QUOTE:
            return "SINGLE";
        case DOUBLE_QUOTE:
            return "DOUBLE";
        default:
            return "UNKNOWN";
    }
}

static const char *tok_type_str(t_token_type type)
{
    switch (type)
    {
        case T_WORD:
            return "WORD";
        case T_PIPE:
            return "PIPE";
        case T_REDIR_IN:
            return "REDIR_IN";
        case T_REDIR_OUT:
            return "REDIR_OUT";
        case T_APPEND:
            return "APPEND";
        case T_HEREDOC:
            return "HEREDOC";
        default:
            return "UNKNOWN";
    }
}

static void print_segments(const t_token_segment *seg)
{
    int i = 0;

    if (!seg)
    {
        printf("      (no segments)\n");
        return;
    }

    while (seg)
    {
        printf("      segment[%d]: quote=%s text=\"%s\"\n",
               i, quote_str(seg->quote_type), seg->text ? seg->text : "(null)");
        seg = seg->next;
        i++;
    }
}

static void print_tokens(const t_token *tokens)
{
    int i = 0;

    if (!tokens)
    {
        printf("  (no tokens)\n");
        return;
    }

    while (tokens)
    {
        printf("  token[%d]: type=%s", i, tok_type_str(tokens->type));
        if (tokens->value)
            printf(" value=\"%s\"", tokens->value);
        printf("\n");
        
        if (tokens->type == T_WORD)
            print_segments(tokens->segments);
        
        tokens = tokens->next;
        i++;
    }
}

static void test_case(const char *input, const char *description)
{
    t_token *tokens;
    
    printf("\n=== TEST: %s ===\n", description);
    printf("Input: '%s'\n", input);
    
    tokens = lexer(input);
    
    if (!tokens)
    {
        printf("Result: NULL (error or empty)\n");
    }
    else
    {
        printf("Result:\n");
        print_tokens(tokens);
        free_tokens(tokens);
    }
    printf("========================================\n");
}

static void run_predefined_tests(void)
{
    printf("\n🧪 EJECUTANDO TESTS PREDEFINIDOS...\n");
    
    // Tests básicos
    test_case("", "Input vacío");
    test_case("   ", "Solo espacios");
    test_case("echo", "Comando simple");
    test_case("echo hello", "Comando con argumento");
    test_case("echo hello world", "Comando con múltiples argumentos");
    
    // Tests con quotes
    test_case("echo 'hello'", "Comillas simples");
    test_case("echo \"hello\"", "Comillas dobles");
    test_case("echo 'hello world'", "Comillas simples con espacios");
    test_case("echo \"hello world\"", "Comillas dobles con espacios");
    test_case("echo hello'world'", "Palabra con comillas simples");
    test_case("echo hello\"world\"", "Palabra con comillas dobles");
    test_case("echo 'hello'world", "Mezcla comillas y texto");
    
    // Tests con pipes
    test_case("ls | grep test", "Pipe simple");
    test_case("echo hello | cat | wc", "Múltiples pipes");
    test_case("ls|grep test", "Pipe sin espacios");
    
    // Tests con redirecciones
    test_case("echo hello > file", "Redirección salida");
    test_case("cat < file", "Redirección entrada");
    test_case("echo hello >> file", "Redirección append");
    test_case("cat << EOF", "Heredoc");
    test_case("echo hello>file", "Redirección sin espacios");
    
    // Tests complejos
    test_case("echo 'hello | world' | grep test", "Pipe dentro de comillas");
    test_case("echo \"$USER\" > file", "Variable en comillas dobles");
    test_case("ls -la | grep '.txt' > files.txt", "Comando complejo");
    
    // Tests de error
    test_case("echo 'hello", "Comilla simple sin cerrar");
    test_case("echo \"hello", "Comilla doble sin cerrar");
}

static void interactive_mode(void)
{
    char buf[4096];
    t_token *tokens;

    printf("\n🖥️  MODO INTERACTIVO\n");
    printf(">>> Escribe una línea a tokenizar (Ctrl+D para salir)\n");
    printf(">>> Comandos especiales: 'test' para ejecutar tests, 'quit' para salir\n");
    
    while (1)
    {
        printf("\nlexer> ");
        fflush(stdout);
        
        if (!fgets(buf, sizeof(buf), stdin))
        {
            printf("\nSaliendo...\n");
            break;
        }

        // Quitar '\n' final
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';

        // Comandos especiales
        if (strcmp(buf, "quit") == 0 || strcmp(buf, "exit") == 0)
            break;
        if (strcmp(buf, "test") == 0)
        {
            run_predefined_tests();
            continue;
        }
        if (strlen(buf) == 0)
            continue;

        // Procesar input
        printf("Procesando: '%s'\n", buf);
        
        tokens = lexer(buf);
        
        if (!tokens)
        {
            printf("❌ lexer() devolvió NULL\n");
        }
        else
        {
            printf("✅ Tokens generados:\n");
            print_tokens(tokens);
            free_tokens(tokens);
        }
    }
}

int main(int argc, char **argv)
{
    printf("🚀 LEXER TESTER - Minishell\n");
    printf("==========================\n");

    if (argc > 1)
    {
        // Modo test con argumentos
        for (int i = 1; i < argc; i++)
        {
            char description[256];
            snprintf(description, sizeof(description), "Argumento %d", i);
            test_case(argv[i], description);
        }
    }
    else
    {
        // Ejecutar tests automáticos primero
        run_predefined_tests();
        
        // Luego modo interactivo
        interactive_mode();
    }

    printf("\n👋 Programa terminado.\n");
    return 0;
}
