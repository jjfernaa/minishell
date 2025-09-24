#include "minishell.h"

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
        printf("        (no segments)\n");
        return;
    }

    while (seg)
    {
        printf("        segment[%d]: quote=%s text=\"%s\"\n",
               i, quote_str(seg->quote_type), seg->text ? seg->text : "(null)");
        seg = seg->next;
        i++;
    }
}

static void print_tokens_detailed(const t_token *tokens, const char *phase)
{
    int i = 0;

    printf("  🔍 %s:\n", phase);
    if (!tokens)
    {
        printf("    (no tokens)\n");
        return;
    }

    while (tokens)
    {
        printf("    token[%d]: type=%s", i, tok_type_str(tokens->type));
        
        if (tokens->value)
            printf(" value=\"%s\"", tokens->value);
        else
            printf(" value=(null)");
        
        printf("\n");
        
        if (tokens->type == T_WORD && tokens->segments)
            print_segments(tokens->segments);
        
        tokens = tokens->next;
        i++;
    }
    printf("\n");
}

static void test_lexer_only(const char *input, const char *description)
{
    t_token *tokens;
    
    printf("\n=== LEXER TEST: %s ===\n", description);
    printf("Input: '%s'\n", input);
    
    tokens = lexer(input);
    
    if (!tokens)
    {
        printf("❌ Lexer returned NULL\n");
    }
    else
    {
        printf("✅ Lexer successful:\n");
        print_tokens_detailed(tokens, "AFTER LEXER");
        free_tokens(tokens);
    }
    printf("========================================\n");
}

static void test_expansion_complete(const char *input, const char *description)
{
    t_token *tokens;
    t_shell shell;
    char *envp[] = {
        "USER=testuser",
        "HOME=/home/testuser", 
        "PATH=/usr/bin:/bin",
        "SHELL=/bin/bash",
        NULL
    };
    
    printf("\n=== COMPLETE TEST: %s ===\n", description);
    printf("Input: '%s'\n", input);
    
    // Inicializar shell manualmente
    shell.env = init_env(envp);
    if (!shell.env)
    {
        printf("❌ Failed to initialize environment\n");
        return;
    }
    shell.input = NULL;
    shell.tokens = NULL;
    shell.cmd = NULL;
    shell.infile_fd = -1;
    shell.outfile_fd = -1;
    shell.exit_status = 42;  // Para testear $?
    
    // Paso 1: Lexer
    tokens = lexer(input);
    if (!tokens)
    {
        printf("❌ Lexer failed\n");
        free_env(shell.env);
        return;
    }
    
    shell.tokens = tokens;
    print_tokens_detailed(shell.tokens, "AFTER LEXER (before expansion)");
    
    // Paso 2: Expansion
    expand_var(&shell);
    print_tokens_detailed(shell.tokens, "AFTER EXPANSION");
    
    printf("✅ Test completed successfully\n");
    
    // Cleanup manual
    free_tokens(shell.tokens);
    free_env(shell.env);
    printf("========================================\n");
}

static void run_lexer_tests(void)
{
    printf("\n🔧 TESTING LEXER ONLY...\n");
    printf("=======================\n");
    
    // Tests básicos del lexer
    test_lexer_only("", "Empty input");
    test_lexer_only("   ", "Only spaces");
    test_lexer_only("echo", "Simple command");
    test_lexer_only("echo hello", "Command with argument");
    test_lexer_only("echo hello world", "Command with multiple arguments");
    
    // Tests con quotes
    test_lexer_only("echo 'hello'", "Single quotes");
    test_lexer_only("echo \"hello\"", "Double quotes");
    test_lexer_only("echo 'hello world'", "Single quotes with spaces");
    test_lexer_only("echo \"hello world\"", "Double quotes with spaces");
    test_lexer_only("echo hello'world'", "Mixed text and single quotes");
    test_lexer_only("echo hello\"world\"", "Mixed text and double quotes");
    
    // Tests con símbolos
    test_lexer_only("ls | grep test", "Simple pipe");
    test_lexer_only("echo hello > file", "Output redirection");
    test_lexer_only("cat < file", "Input redirection");
    test_lexer_only("echo hello >> file", "Append redirection");
    test_lexer_only("cat << EOF", "Heredoc");
    test_lexer_only("ls|grep test", "Pipe without spaces");
    test_lexer_only("echo hello>file", "Redirection without spaces");
}

static void run_expansion_tests(void)
{
    printf("\n🔄 TESTING LEXER + EXPANSION...\n");
    printf("===============================\n");
    
    // Tests básicos de expansión
    test_expansion_complete("echo hello", "No expansion needed");
    test_expansion_complete("echo $USER", "Simple variable expansion");
    test_expansion_complete("echo $HOME", "HOME variable expansion");
    test_expansion_complete("echo $?", "Exit status expansion");
    
    // Tests con quotes
    test_expansion_complete("echo '$USER'", "Single quotes (no expansion)");
    test_expansion_complete("echo \"$USER\"", "Double quotes (with expansion)");
    test_expansion_complete("echo \"Hello $USER\"", "Mixed text and variable in double quotes");
    test_expansion_complete("echo '$USER and $HOME'", "Multiple vars in single quotes (no expansion)");
    test_expansion_complete("echo \"$USER and $HOME\"", "Multiple vars in double quotes");
    
    // Tests complejos
    test_expansion_complete("echo $HOME/file", "Variable with path");
    test_expansion_complete("echo ${USER}test", "Variable with braces (if supported)");
    test_expansion_complete("ls $HOME | grep $USER", "Variables with pipe");
    test_expansion_complete("echo $USER > $HOME/file", "Variables with redirection");
    test_expansion_complete("echo \"Status: $?\"", "Exit status in double quotes");
    
    // Tests de casos especiales
    test_expansion_complete("echo $NONEXISTENT", "Non-existent variable");
    test_expansion_complete("echo $", "Just dollar sign");
    test_expansion_complete("echo $$", "Double dollar (if supported)");
}

static void interactive_mode(void)
{
    char buf[4096];
    
    printf("\n🖥️  INTERACTIVE MODE\n");
    printf("==================\n");
    printf("Commands:\n");
    printf("  'l' - Test lexer only\n");
    printf("  'e' - Test lexer + expansion\n");
    printf("  'q' - Quit\n");
    printf("  Any other input - Test complete process\n");
    
    while (1)
    {
        printf("\ninteractive> ");
        fflush(stdout);
        
        if (!fgets(buf, sizeof(buf), stdin))
        {
            printf("\nExiting...\n");
            break;
        }

        // Quitar '\n' final
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';

        if (strlen(buf) == 0)
            continue;

        // Comandos especiales
        if (buf[0] == 'q' && strlen(buf) == 1)
            break;
        
        if (buf[0] == 'l' && strlen(buf) == 1)
        {
            printf("Enter input for lexer test: ");
            fflush(stdout);
            if (fgets(buf, sizeof(buf), stdin))
            {
                len = strlen(buf);
                if (len > 0 && buf[len - 1] == '\n')
                    buf[len - 1] = '\0';
                test_lexer_only(buf, "Interactive lexer test");
            }
            continue;
        }
        
        if (buf[0] == 'e' && strlen(buf) == 1)
        {
            printf("Enter input for expansion test: ");
            fflush(stdout);
            if (fgets(buf, sizeof(buf), stdin))
            {
                len = strlen(buf);
                if (len > 0 && buf[len - 1] == '\n')
                    buf[len - 1] = '\0';
                test_expansion_complete(buf, "Interactive expansion test");
            }
            continue;
        }

        // Test completo por defecto
        test_expansion_complete(buf, "Interactive complete test");
    }
}

int main(int argc, char **argv)
{
    printf("🚀 MINISHELL LEXER & EXPANSION TESTER\n");
    printf("=====================================\n");

    if (argc > 1)
    {
        // Modo con argumentos de línea de comandos
        for (int i = 1; i < argc; i++)
        {
            char description[256];
            snprintf(description, sizeof(description), "Command line argument %d", i);
            test_expansion_complete(argv[i], description);
        }
    }
    else
    {
        // Modo automático: ejecutar todas las pruebas
        printf("Choose test mode:\n");
        printf("  1 - Run all automatic tests\n");
        printf("  2 - Interactive mode\n");
        printf("  3 - Lexer tests only\n");
        printf("  4 - Expansion tests only\n");
        printf("Choice (default 1): ");
        
        int choice = getchar();
        while (getchar() != '\n'); // Limpiar buffer
        
        switch (choice)
        {
            case '2':
                interactive_mode();
                break;
            case '3':
                run_lexer_tests();
                break;
            case '4':
                run_expansion_tests();
                break;
            case '1':
            case '\n':
            default:
                run_lexer_tests();
                run_expansion_tests();
                break;
        }
    }

    printf("\n👋 Testing completed.\n");
    return 0;
}